// OPENGL��װ��ĳ��ش��ڣ������ࡣ
#ifndef __CROSSANY_GLVIEW_H_
#define __CROSSANY_GLVIEW_H_
#include "macro.h"

//NS_CROSSANY_BEGIN
namespace crossany{

	class glview{
	private:
		glview();
		~glview();

		virtual bool init(){ return true; };
	public:
		static glview* me();
	};

}
//NS_CROSSANY_END
#endif