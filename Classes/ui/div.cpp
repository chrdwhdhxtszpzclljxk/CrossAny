#include "div.h"
#include "log.h"

NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN

div::div(){
}

div::~div(){
}


bool div::create(const rect& _rc, const char* path, ...){
	std::list<std::string> filelist; std::list<std::string>::iterator iter; std::string filepath; rect rc = _rc;
	filelist.push_back(path);
	va_list argp; int argno = 0; char* para;
	va_start(argp, path);
	while (true){
		para = va_arg(argp, char*);
		if (strlen(para) <= 1) break;
		filelist.push_back(para);
		argno++;
	}
	va_end(argp);
	for (iter = filelist.begin(); iter != filelist.end(); iter++){
		filepath = (*iter);
		img* i = img::create(_rc.getpos(), filepath.c_str());
		mimgs.push_back(i);
		if (rc.getsize() == i->getrect().getsize()){

		}else{
			rc = i->getrect();
		}
	}
	mrc = rc;
	return true;
}

void div::customdraw(){
	node::customdraw();
	if (midx >= 0 && midx < mimgs.size()){
		mimgs[midx]->customdraw();
	}

}

int32_t div::ontouchbegin(const msg* _msg){
	node::ontouchbegin(_msg);
	midx = 1;
	if (midx >= mimgs.size()) midx = 0;
	mtouchbegin = true;
	return 1;
}

int32_t div::ontouchend(const msg* m){
	node::ontouchend(m);
	midx = 0;
	if (midx >= mimgs.size()) midx = 0;
	return 1;
}

int32_t div::ontouchmove(const msg* _msg){
	node::ontouchmove(_msg);
	return 1;
}


NS_CROSSANY_UI_END
NS_CROSSANY_END
