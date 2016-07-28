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
	class appbase{
	public:
		
		static void updateui();
		appbase(){};
		virtual ~appbase(){};
		virtual void run();
		virtual void addChild(node* _node, int32_t z = 0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		static HWND hWnd;
		virtual void onevent(const UINT&, const WPARAM&, const LPARAM&);
#endif
		static void ontimer();
		static double getw(){ return msize.getw(); }
		static double geth(){ return msize.geth(); }
	private:
		virtual bool init(){ return true; };
		node orz;
		
		static size msize;
		static bool painted;
		static node::nodelist mtimer;
	public:
		static node* mfocus;
	public:
		static void timeradd(const node*);
		static void timerremove(const node*);
		static int64_t alert(std::wstring msg, std::wstring title = L"msg", int64_t type = 0){ return 0; };
		virtual void draw(){ orz.draw(); };
		virtual void resize(const size& _s) { msize = _s; orz.resize(_s);  };

	};
	
};


//NS_CROSSANY_END;
#endif