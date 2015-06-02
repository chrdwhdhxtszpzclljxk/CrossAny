#ifndef __CROSSANY_APPBASE_H_
#define __CROSSANY_APPBASE_H_
#include "macro.h"
#include <string>
#include <stdint.h>
#include "node.h"
#include <list>
#include <vector>
#include "coordinate.h"
//NS_CROSSANY_BEGIN

namespace crossany{
	class CROSSANY_API appbase{
	public:
		appbase(){};
		virtual ~appbase(){};
		virtual void run();
		virtual void addChild(node* _node, int32_t z = 0){
			orz.addChild(_node, z);
		}
	private:
		virtual bool init(){ return true; };
		node orz;
	public:
		static int64_t alert(std::wstring msg, std::wstring title = L"ÏûÏ¢¿ò", int64_t type = 0){ return 0; };
		virtual void draw(){ orz.draw(); };
		virtual void resize(const size& _s){ orz.resize(_s); };

	};

};
//NS_CROSSANY_END;
#endif