#ifndef __CROSSANY_UI_LABEL_H_
#define __CROSSANY_UI_LABEL_H_

#include "macro.h"
#include "node.h"
#include "img9.h"

namespace crossany{
	namespace ui{
		class CROSSANY_API txtchar{
		public:
			GLuint	texid;
			wchar_t ch;
			int     m_Width;
			int     m_Height;
			int     m_adv_x;
			int     m_adv_y;
			int     m_delta_x;
			int     m_delta_y;
		public:
			txtchar(){
				texid = 0;
				ch = 0;
				m_Width = 0;
				m_Height = 0;
			}
		};
		class CROSSANY_API label : public node{
		public:
			label();
			~label();
			bool create(const wchar_t* _txt,const char* fontfile,const int32_t fontsize);
			virtual void customdraw();
		private:
			std::vector<txtchar> mtex;
		};
	}
}

#endif