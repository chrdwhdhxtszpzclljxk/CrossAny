#include "button.h"
#include <math.h>

NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN
button::button(){
}
button::~button(){
}

void button::customdraw(){
	if (midx >= 0 && midx < mimgs.size()){
		mimgs[midx]->customdraw();
	}
}

button* button::create(const rect& _rc, const char* path, ...){
	button* ret = new button(); std::list<std::string> filelist;std::list<std::string>::iterator iter; std::string filepath;
	if (ret != nullptr){ // 分配img成功！
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
			img* i = img::create(_rc.getpos(),filepath.c_str());
			ret->mimgs.push_back(i);
		}
	}
	return ret;
}


NS_CROSSANY_UI_END
NS_CROSSANY_END