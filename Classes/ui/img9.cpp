#include "img9.h"
#include "msg.h"
#include <png.h>
#include "appbase.h"
#include "log.h"


NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN

std::map < std::string, tex* > img::mtexs;
tex* tex::create(const GLuint& _id, const size& _size){
	tex* ret = new tex();
	if (ret != nullptr){
		ret->mid = _id;
		ret->msize = _size;
		ret->mref = 1;
	}
	return ret;
}

void errout(const char* func) {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)	{
		log::otprint("%s error:%d",func,err);
	}
}

img* img::create(const pos2& _pos, const char* path){
	img* ret = new img(); size sizeimg;
	GLuint texid[2] = {0}; static std::map < std::string, tex* >::iterator i;
	if (ret != nullptr){ // 分配img成功！
		i = mtexs.find(path);
		if (i == mtexs.end()){ // 要加载的图片没有在tex缓存中，进行加载。
			png_image png = { 0 };
			memset(&png, 0, sizeof(png));
			png.version = PNG_IMAGE_VERSION;
			int a= png_image_begin_read_from_file(&png, path);
			//if (a <= 0) {	OutputDebugStringA("png_image_begin_read_from_file");	}
			png.format = PNG_FORMAT_RGBA; // 按RGBA读取文件！
			int64_t tmp = PNG_IMAGE_SAMPLE_SIZE(png.format);
			GLint interformat = PNG_IMAGE_SAMPLE_CHANNELS(png.format);
			tmp = PNG_IMAGE_SAMPLE_COMPONENT_SIZE(png.format);
			int32_t buffersize = PNG_IMAGE_SIZE(png);
			int32_t wt = png.width;
			int32_t ht = png.height;
			node::adj_w_h(wt, ht);
			//log::otprint("buffersize:%d", buffersize);
			char* buffer0 = new char[buffersize];
			char* buffer = new char[wt * ht * 4];
			memset(buffer, 0x00, wt*ht * 4);
			a = png_image_finish_read(&png, nullptr, buffer0, 0, nullptr);
			for (int z = 0; z < png.height;z++) {
				//for (int y = 0; y < png.height; y++) {
					memcpy(buffer + z * wt * 4, buffer0 + z * png.width * 4, png.width * 4);
				//}
			}

			//log::otprint("png_image_finish_read:%d",a);
			//png.opaque = 0;
			//png_image_write_to_file(&png, "ui/test.png",0 , buffer, 0, 0);
			sizeimg.set(wt, ht);
			glGenTextures(1, texid);
			//errout("glGenTextures");
			glBindTexture(GL_TEXTURE_2D, texid[0]);
			//errout("glBindTexture");
			//log::otprint("format:%d width:%d height:%d", interformat,wt,ht);
			glTexImage2D(GL_TEXTURE_2D, 0, interformat, wt, ht, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer); // ?????2?N??
			//glTexSubImage2D(GL_TEXTURE_2D, 0, 200, 200, png.width, png.height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			//errout("glTexImage2D");
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//errout("glTexParameteri"); GL_INVALID_ENUM; GL_MAX_TEXTURE_SIZE;
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			delete[] buffer;
			delete[] buffer0;
			png_image_free(&png);
			ret->mimg = texid[0];
			mtexs[path] = tex::create(texid[0], sizeimg);
		}
		else{
			if (i->second->inc() > 0){
				ret->mimg = i->second->mid;
				sizeimg.set(i->second->msize);
			}
		}

		ret->mrc.set(_pos, sizeimg);
	}
	return ret;
}

void img::customdraw(){
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glEnable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D, mimg);
	glColor4f(1.0f, 1.0f, 1.0f,1.0f); // 清除当前颜色。不然tex会变色。
	glBegin(GL_QUADS);
	// 0.0是纹理的左侧，0.5是纹理的中点，1.0是纹理的右侧 . 0.0是纹理的底部，0.5是纹理的中点，1.0是纹理的顶部。
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(mrc.getleft(), appbase::geth() - mrc.gety0(), 1.0f);//左下角
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(mrc.getx1(), appbase::geth() - mrc.gety1(), 1.0f);//左上角
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(mrc.getx2(), appbase::geth() - mrc.gety2(), 1.0f);//右上角
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(mrc.getx3(), appbase::geth() - mrc.gety3(), 1.0f);//右下角
	glEnd();
	//glDisable(GL_ALPHA_TEST); 
	//glDisable(GL_BLEND);   
	//glDisable(GL_TEXTURE_2D);
}

img9::img9(){
}

img9::~img9(){
}

void img9::customdraw(){

}

NS_CROSSANY_UI_END
NS_CROSSANY_END


/*
img* img::create(const pos2& _pos,  const char* path,...){
img* ret = new img(); std::list<std::string> filelist; int32_t idx = 0; std::list<std::string>::iterator iter; size sizeimg;
GLuint texid[2]; static std::map < std::string, tex* >::iterator i; std::string filepath;
if (ret != nullptr){ // 分配img成功！
//ret->midx = 0;
filelist.push_back(path);
va_list argp; int argno = 0; char* para;
va_start(argp, path);
while (true){ // 遍历加载的img图片。
para = va_arg(argp, char*);
if (strlen(para) <= 1) break;
filelist.push_back(para);
argno++;
}
va_end(argp);
for (iter = filelist.begin(); iter != filelist.end(); iter++){
filepath = (*iter);
i = mtexs.find(filepath);
if (i == mtexs.end()){ // 要加载的图片没有在tex缓存中，进行加载。
png_image png = { 0 };
memset(&png, 0, sizeof(png));
png.version = PNG_IMAGE_VERSION;
png_image_begin_read_from_file(&png, filepath.c_str());
png.format = PNG_FORMAT_RGBA;
int64_t tmp = PNG_IMAGE_SAMPLE_SIZE(png.format);
GLint interformat = PNG_IMAGE_SAMPLE_CHANNELS(png.format);
tmp = PNG_IMAGE_SAMPLE_COMPONENT_SIZE(png.format);
int32_t buffersize = PNG_IMAGE_SIZE(png);
char* buffer = new char[buffersize];
png_image_finish_read(&png, nullptr, buffer, 0, nullptr);
//png.opaque = 0;
//png_image_write_to_file(&png, "ui/test.png",0 , buffer, 0, 0);
sizeimg.set(png.width, png.height);
glGenTextures(1, texid);
glBindTexture(GL_TEXTURE_2D, texid[0]);
glTexImage2D(GL_TEXTURE_2D, 0, interformat, png.width, png.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
delete[] buffer;
png_image_free(&png);
ret->mimgs.resize(idx + 1);
ret->mimgs[idx] = texid[0];
mtexs[filepath] = tex::create(texid[0],sizeimg);
}else{
if (i->second->inc() > 0){
ret->mimgs.resize(idx + 1);
ret->mimgs[idx] = i->second->mid;
sizeimg.set(i->second->msize);
}
}
idx++;
}

ret->mrc.set(_pos,sizeimg);
}
return ret;
}
*/
