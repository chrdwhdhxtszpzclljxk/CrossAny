#include "node.h"
#include "msg.h"
#include <Windows.h>
#include <stdint.h>
#include <gl/GL.h>
#include <gl/GLU.h>

NS_CROSSANY_BEGIN


int32_t node::customevent(const UINT& _msg, const pos2& _p){
	switch (_msg){
	case WM_LBUTTONDOWN:{
		msg m(_p, this, nullptr);
		ontouchbegin(&m);
	}break;
	case WM_LBUTTONUP:{
		msg m(_p, this, nullptr);
		ontouchend(&m);
	}break;
	case WM_MOUSEMOVE:{
		msg m(_p, this, nullptr);
		ontouchmove(&m);
	}break;
	}
	return 0;
}

int32_t node::onevent(const UINT& msg, const WPARAM& w, const LPARAM& l) { // ����0��ʾ�¼���nodeû�д��������ĸ�node��������1��ʾ�¼���node����ֹͣ��node�ɷ���
	int32_t ret = 0; double x, y; x = LOWORD(l); y = HIWORD(l);
	pos2 pos(x, y);
	if (!mrc.ptinrect(pos)) return ret; // �¼�����û���ڱ�node
	node::nodez::reverse_iterator z; node::nodelist::iterator iter; 
	for (z = mnodes.rbegin(); z != mnodes.rend(); z++) { // ��z-order��Ŀ�ʼ���ɷ��¼���
		node::nodelist* nlist = (*z);
		for (iter = nlist->begin(); iter != nlist->end(); iter++) {
			ret = (*iter)->onevent(msg, w, l);
			if (ret != 0) break;
		}
	}
	if (ret == 0) {
		//if (mrc.ptinrect(pos)/* || (msg == WM_LBUTTONUP && mtouchbegin)*/) {
			ret = customevent(msg, pos);
		//}
	}
	return ret;
}



NS_CROSSANY_END

#include "node.hpp"
