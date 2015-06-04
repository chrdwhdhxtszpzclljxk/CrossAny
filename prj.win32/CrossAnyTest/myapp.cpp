#include "stdafx.h"
#include "myapp.h"
#include <ui/button.h>
#include <ui/img9.h>

myapp::myapp(){}
myapp::~myapp(){}
void myapp::run(){ appbase::run(); };
bool myapp::init(){
	//crossany::ui::button* btn = new crossany::ui::button();
	//addChild(btn);
	crossany::ui::img* img0 = crossany::ui::img::create(crossany::rect::ZERO, "D:\\DEVTOOLS\\Cocos\\project\\HotVA3\\Resources\\HelloWorld.png", "");
	addChild(img0);
	return true;
}
