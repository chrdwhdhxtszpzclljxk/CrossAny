#include "img9.h"
#include <png.h>

NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN

std::map < std::string, int64_t > img::mtexs;

img* img::create(const rect& _rc,  const char* path,...){
	img* ret = new img(); std::list<std::string> filelist; int32_t idx = 0; std::list<std::string>::iterator iter;
	GLuint texid[2];
	if (ret != nullptr){
		ret->mrcshow = _rc;
		filelist.push_back(path);
		va_list argp; int argno = 0; char* para;
		va_start(argp, path);
		while (1){
			para = va_arg(argp, char*);
			if (strlen(para) <= 1) break;
			filelist.push_back(para);
			argno++;
		}
		va_end(argp);

		/*
		static GLubyte T0[64][64][4];
		int i, j, c;    // 第一个纹理，渐变绿色，*64  
		for (i = 0; i < 64; i++) {   
			for (j = 0; j < 64; j++) {    
				T0[i][j][0] = (GLubyte) 0;     T0[i][j][1] = (GLubyte) i * 5 + j * 5;    T0[i][j][2] = (GLubyte) 0;    T0[i][j][3] = (GLubyte) 255;    }   }

				*/
		for (iter = filelist.begin(); iter != filelist.end(); iter++){
			png_image png = { 0 };
			memset(&png, 0, sizeof(png));
			png.version = PNG_IMAGE_VERSION;
			png_image_begin_read_from_file(&png, (*iter).c_str());
			png.format = PNG_FORMAT_RGBA;
			int64_t tmp = PNG_IMAGE_SAMPLE_SIZE(png.format);
			GLint interformat = PNG_IMAGE_SAMPLE_CHANNELS(png.format);
			tmp = PNG_IMAGE_SAMPLE_COMPONENT_SIZE(png.format);
			int32_t buffersize = PNG_IMAGE_SIZE(png);
			char* buffer = new char[buffersize];
			png_image_finish_read(&png, nullptr, buffer, 0, nullptr);
			//glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			glGenTextures(1, texid);
			glBindTexture(GL_TEXTURE_2D, texid[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, interformat, png.width, png.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, T0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);
			delete[] buffer;
			png_image_free(&png);
			ret->mimgs.resize(idx+1);
			ret->mimgs[idx] = texid[0];
		}

	}
	return ret;
}
void img::customdraw(){
	glEnable(GL_TEXTURE_2D);
	//glColor3f(1.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	//glBindTexture(GL_TEXTURE_2D, mimgs[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,1.0f);//glVertex3f(-0.5f, -0.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(200, 0, 1.0f);//glVertex3f(0.50f, -0.50f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(200, 200, 1.0f);//glVertex3f(0.50f, 0.50f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,200 , 1.0f);//glVertex3f(-0.50f, 0.50f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
img9::img9(){
}

img9::~img9(){
}

void img9::customdraw(){

}

NS_CROSSANY_UI_END
NS_CROSSANY_END
