#ifndef __CROSSANY_UI_LABEL_H_
#define __CROSSANY_UI_LABEL_H_

#include "macro.h"
#include "node.h"
#include "img9.h"

namespace crossany{
	namespace ui{
		class CROSSANY_API bmptex{
		public :
			GLuint id;
			int32_t mw, mh;	// 
			int32_t mwo, mho; // the output draw width,height.
		public:
			bmptex() {
				mw = mh = mwo = mho = 0;
				id = 0;
			}
		};
		class CROSSANY_API txtchar{
		public:
			GLuint	texid;
			wchar_t ch;
			int32_t mw,mwr;
			int32_t mh,mhr;
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
		protected:
			int32_t mmaxh;
		private:
			txtchar mtex;
			bmptex mbmp;
			size mtxtsize;
			GLfloat r, g, b;
		};
	}
}

#endif