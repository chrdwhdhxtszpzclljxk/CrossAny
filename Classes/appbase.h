#ifndef __CROSSANY_APPBASE_H_
#define __CROSSANY_APPBASE_H_
#include "macro.h"

//NS_CROSSANY_BEGIN
namespace crossany{

	class CROSSANY_API appbase{
	public:
		appbase();
		virtual ~appbase();
		virtual void run();
	};

}
//NS_CROSSANY_END;
#endif