#include "log.h"
#include "ime.h"

NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN

ime::ime()
{
}


ime::~ime()
{
}

ime* ime::me(){
	static ime* pThis = nullptr;
	if (pThis == nullptr){
		pThis = new ime();
	}
	return pThis;
}

bool ime::attach(){
	return true;
}

bool ime::detach(){
	return true;
}

void ime::insert(const char* _txt){
	mtxt.append(_txt);
	log::otprint(mtxt.c_str());
}

void ime::remove(){

}

NS_CROSSANY_UI_END
NS_CROSSANY_END
