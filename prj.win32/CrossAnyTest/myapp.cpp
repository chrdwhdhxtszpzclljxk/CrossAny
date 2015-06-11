#include "stdafx.h"
#include "myapp.h"
#include <ui/button.h>
#include <ui/img9.h>
#include <ui/div.h>

myapp::myapp(){}
myapp::~myapp(){}
void myapp::run(){ appbase::run(); };
bool myapp::init(){
	//crossany::ui::div* img0 = crossany::ui::button::create(crossany::rect(crossany::pos2(0, 80), crossany::size(30, 30)), "ui/button.png", "ui/buttonp.png", "");
	crossany::ui::div* div0 = new crossany::ui::div();
	div0->create(crossany::rect(crossany::pos2(0, 80), crossany::size(30, 30)), "ui/button.png", "ui/buttonp.png", "");
	addChild(div0);

	//crossany::ui::button* img1 = crossany::ui::button::create(crossany::rect(crossany::pos2(80, 160), crossany::size(30, 30)), "ui/button.png", "");
	//addChild(img1);
	//crossany::ui::img* img1 = crossany::ui::img::create(crossany::pos2(250, 250), "ui/a1.png");
//	addChild(img1);
	return true;
}
