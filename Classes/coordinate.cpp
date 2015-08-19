#include "coordinate.h"

NS_CROSSANY_BEGIN
const rect rect::ZERO;
const size size::ZERO;
const pos2 pos2::ZERO;

bool rect::ptinrect(const pos2& _p) { 
	if (_p.getx() >= getleft() && _p.getx() <= getright() && _p.gety() >= gettop() && _p.gety() <= getbottom()) 
		return true; 
	return false; 
};

NS_CROSSANY_END