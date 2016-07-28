#ifndef __CROSSANY_UI_BUTTON_H_
#define __CROSSANY_UI_BUTTON_H_
#include "macro.h"
#include "node.h"
#include "img9.h"
#include <vector>

//NS_CROSSANY_BEGIN
namespace crossany{
	namespace ui{
		class button :public node{
		private:
			button();
			~button();
		public:
			static button* create(const rect& rc, const char*, ...);
			virtual void customdraw();
			virtual int32_t ontouchmove(const msg*);
		protected:
			//pos2 mpos;
			//size msize;
		private:
			std::vector<img*> mimgs;
			int32_t midx;

		};
	}
}

#endif