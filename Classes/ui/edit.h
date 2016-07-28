#ifndef __CROSSANY_UI_EDIT_H_
#define __CROSSANY_UI_EDIT_H_
#include "macro.h"
#include "node.h"
#include "img9.h"
#include "label.h"
#include <chrono>

namespace crossany{
	namespace ui{
		class edit : public node{
		public:
			edit();
			~edit();
			bool create(const wchar_t* _placehoder,const char* file, const int32_t& _size);
			virtual void customdraw();
			virtual void onsetfocus(const bool&);
			virtual void ontimer();
		private:
			std::wstring mplaceholder,mtxtval;
			std::vector<txtchar> mtex,mtexplaceholder;
			
			bool mcaret;
			std::chrono::system_clock::time_point mlast;
			
		};
	}
}

#endif

