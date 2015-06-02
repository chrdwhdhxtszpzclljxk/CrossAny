#include "stdafx.h"
#include "myapp.h"
#include <ui/button.h>

myapp::myapp(){}
myapp::~myapp(){}
void myapp::run(){ appbase::run(); };
bool myapp::init(){
	crossany::ui::button* btn = new crossany::ui::button();
	addChild(btn);
	return true;
}
