#ifndef __CROSSANY_UI_IME_H_
#define __CROSSANY_UI_IME_H_
#include "macro.h"
#include "node.h"

namespace crossany{
	namespace ui{
		class ime
		{
		public:
			static ime* me();
			bool attach();
			bool detach();
			void insert(const wchar_t*);
			void remove();
			void setpos(const int32_t&);
		private:
			ime();
			~ime();
			std::wstring mtxt;
			int32_t mpos;
		};

	}
}
#endif