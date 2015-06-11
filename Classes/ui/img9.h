#ifndef __CROSSANY_UI_IMG9_H_
#define __CROSSANY_UI_IMG9_H_

#pragma once
#include <vector>
#include <map>
#include <string>
#include <atomic>
#include "macro.h"
#include "node.h"
#include "../coordinate.h"

namespace crossany{
	namespace ui{
		class tex{
		private:
			tex():mref(0){};
			~tex(){};
		public:
			static tex* create(const GLuint& _id,const size& _size);
			int32_t inc(){ if (mref <= 0){ delete this; return 0; } else mref++; return mref; };
			int32_t dec(){ mref--; if (mref <= 0){ delete this; }; return mref; };

		public:
			GLuint mid;		// texture id。glGenTextures 。
			size msize;
			std::atomic_int32_t mref;
		};
		class img{
		private:
			img(){};
			~img(){};
		public:
			static img* create(const pos2& _pos , const char*); // const char* filepath。
			virtual void customdraw();
			const rect getrect() const { return mrc; };
		private:
			//std::vector<GLuint> mimgs;
			GLuint mimg;
			rect mrc;
			//int32_t midx;
			//rect mrcshow;
			static std::map < std::string, tex* > mtexs;
		public:
			
		};

		class img9 {
		public:
			img9();
			~img9();
			virtual void customdraw();
		private:
			std::vector<std::string> mimgs;
			int64_t midx;
		};
	}
}

#endif

