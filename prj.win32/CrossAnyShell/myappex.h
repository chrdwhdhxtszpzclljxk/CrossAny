#pragma once
#include <CrossAny.h>

USE_NS_CROSSANY

class myappex :
	public appbase
{
public:
	myappex();
	~myappex();
	virtual bool init();// { return true; };
};

