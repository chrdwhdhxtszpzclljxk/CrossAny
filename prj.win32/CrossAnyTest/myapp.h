#pragma once
#include <CrossAny.h>
//#include "appbase.h"
USE_NS_CROSSANY
class myapp :
	public appbase
{
public:
	myapp();
	virtual ~myapp();
	virtual void run();
};

