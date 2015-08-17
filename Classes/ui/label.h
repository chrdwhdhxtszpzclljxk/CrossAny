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
			int32_t mw;
			int32_t mh;
			int32_t top;
			int32_t m_adv_x;
			int32_t m_adv_y;
			int32_t m_delta_x;
			int32_t	m_delta_y;
			int32_t mbase;
		public:
			txtchar(){
				texid = 0;
				ch = 0;
				mw = 0;
				mh = 0;
			}
		};
		class CROSSANY_API label : public node{
		public:
			label();
			~label();
			bool create(const wchar_t* _txt,const char* fontfile,const int32_t fontsize);
			virtual void customdraw();
		private:
			//std::vector<txtchar> mtex;
			txtchar mtex;
			GLfloat r, g, b;
		};
	}
}

#endif