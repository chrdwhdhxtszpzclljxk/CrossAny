#ifndef __CROSSANY_UI_DIV_H_
#define __CROSSANY_UI_DIV_H_
#include "macro.h"
#include "node.h"
#include "img9.h"

namespace crossany{
	namespace ui{
		class CROSSANY_API div : public node{
		public:
			div();
			~div();
			bool create(const rect&,const char*,...);
			int32_t setidx(const int32_t& _idx){ if (_idx >= mimgs.size() || _idx < 0) return midx = 0; return (midx = _idx); };

			virtual void customdraw();
			virtual int32_t ontouchbegin(const msg*);
			virtual int32_t ontouchend(const msg*);
			virtual int32_t ontouchmove(const msg*);

		private:
			std::vector<img*> mimgs;
			int32_t midx;
		};
	}
}

#endif