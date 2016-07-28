#include "stdafx.h"
#include "myappex.h"
#include <log.h>
#include <ui/button.h>


myappex::myappex()
{
}


myappex::~myappex()
{
}


bool myappex::init() {
	crossany::log::otprint("hello %s","abc");
	crossany::rect rc;
	rc.set(crossany::pos2(10, 10), crossany::size(100, 100));
	crossany::ui::button* bnlogin = crossany::ui::button::create(rc, "µÇÂ¼");
	this->addChild(bnlogin);

	return true; 
}