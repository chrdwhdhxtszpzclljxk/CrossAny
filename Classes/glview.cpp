#include "glview.h"
NS_CROSSANY_BEGIN

glview::glview(){}
glview::~glview(){}

glview* glview::me(){
	static glview* pv = 0;
	if (pv == 0){
		pv = new glview();
		if (pv != 0 && !pv->init()){ // �����ɹ����ǳ�ʼ��ʧ�ܡ�
			delete pv; pv = 0;
		}
	}
	return pv;
}

NS_CROSSANY_END