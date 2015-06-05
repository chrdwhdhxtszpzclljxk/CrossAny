#include "stdafx.h"
#include "myapp.h"
#include <ui/button.h>
#include <ui/img9.h>

myapp::myapp(){}
myapp::~myapp(){}
void myapp::run(){ appbase::run(); };
bool myapp::init(){
	crossany::ui::img* img0 = crossany::ui::img::create(crossany::pos2(0,80), "ui/button.png",
		"ui/buttonp.png",
		"");
	addChild(img0);

	crossany::ui::img* img1 = crossany::ui::img::create(crossany::pos2(250, 250), "ui/a1.png", "");
	addChild(img1);
	return true;
}
