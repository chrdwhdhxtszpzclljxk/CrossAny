#include "stdafx.h"
#include "myapp.h"
#include <ui/button.h>
#include <ui/img9.h>
#include <ui/div.h>
#include <ui/label.h>
#include <ui/edit.h>
#include <log.h>

myapp::myapp(){}
myapp::~myapp(){}
void myapp::run(){ appbase::run(); };
bool myapp::init(){
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	log::otprint("GL_MAX_TEXTURE_SIZE:%d",max);
	//MessageBoxA(NULL,(char*)OpenGLVersion,"hello",MB_OK);
	//crossany::ui::div* img0 = crossany::ui::button::create(crossany::rect(crossany::pos2(0, 80), crossany::size(30, 30)), "ui/button.png", "ui/buttonp.png", "");
	//crossany::ui::div* div0 = new crossany::ui::div();
	//div0->create(crossany::rect(crossany::pos2(0, 80), crossany::size(30, 30)), "ui/button.png", "ui/buttonp.png", "");
	//addChild(div0);
	crossany::ui::label* label0 = new crossany::ui::label();
	label0->create(L"hello", "ui\\fonts/msyh.ttf", 20);
	addChild(label0);
	label0->setrect(crossany::pos2(100, 200), crossany::size(500, 100));

	crossany::ui::edit* edit0 = new crossany::ui::edit();
	edit0->create(L"hello", "ui\\fonts/msyh.ttf", 20);
	addChild(edit0);
	edit0->setrect(crossany::pos2(100, 300), crossany::size(500, 100));

	crossany::ui::button* bn0 = crossany::ui::button::create(crossany::rect(crossany::pos2(0, 80), crossany::size(30, 30)), "ui/40.png", "ui/buttonp.png", "");
	addChild(bn0);

	//crossany::ui::button* img1 = crossany::ui::button::create(crossany::rect(crossany::pos2(80, 160), crossany::size(30, 30)), "ui/button.png", "");
	//addChild(img1);
	//crossany::ui::img* img1 = crossany::ui::img::create(crossany::pos2(250, 250), "ui/a1.png");
//	addChild(img1);
	return true;
}
