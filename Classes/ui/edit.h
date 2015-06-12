#ifndef __CROSSANY_UI_EDIT_H_
#define __CROSSANY_UI_EDIT_H_
#include "macro.h"
#include "node.h"
#include "img9.h"
#include "label.h"

namespace crossany{
	namespace ui{
		class CROSSANY_API edit : public node{
		public:
			edit();
			~edit();
			bool create(const wchar_t* _placehoder,const char* file, const int32_t& _size);
			virtual void customdraw();
			virtual void ontouchbegin(const msg*);
			virtual void ontouchend(const msg*);
		private:
			std::wstring mplaceholder,mtxtval;
			std::vector<txtchar> mtex,mtexplaceholder;
			
		};
	}
}

#endif

