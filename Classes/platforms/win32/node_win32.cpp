#include "node.h"
#include "msg.h"
#include <Windows.h>
#include <stdint.h>
#include <gl/GL.h>
#include <gl/GLU.h>

NS_CROSSANY_BEGIN


void node::customevent(const UINT& _msg, const pos2& _p){
	switch (_msg){
	case WM_LBUTTONDOWN:{
		msg m(_p, this, nullptr);
		ontouchbegin(&m);
	}break;
	case WM_LBUTTONUP:{
		msg m(_p, this, nullptr);
		ontouchend(&m);
	}break;
	}
}

void node::onevent(const UINT& msg, const WPARAM& w, const LPARAM& l){
	double x, y;
	x = LOWORD(l); y = HIWORD(l);
	pos2 pos(x, y);
	if (mrc.ptinrect(pos) || msg == WM_LBUTTONUP){
		customevent(msg, pos);
	}
		node::nodez::iterator z; node::nodelist::iterator iter;
		for (z = mnodes.begin(); z != mnodes.end(); z++){
			node::nodelist* nlist = (*z);
			for (iter = nlist->begin(); iter != nlist->end(); iter++){

				(*iter)->onevent(msg, w, l);
			}
		}
}

#include "node.hpp"


NS_CROSSANY_END