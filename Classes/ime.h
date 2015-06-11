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
			void insert(const char*);
			void remove();
		private:
			ime();
			~ime();
			std::string mtxt;
		};

	}
}
#endif