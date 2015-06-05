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
			GLuint mid;		// texture 编号。glGenTextures 获得的。
			//rect mrc,mrcv;	// texture的实际大小、可见大小。
			size msize;
			std::atomic_int32_t mref;
		};
		class img : public node{
		private:
			img(){};
			~img(){};
		public:
			static img* create(const pos2& _pos , const char*, ...); // 参数都是std::string类型的图片路径。
			int32_t setidx(const int32_t& _idx){ if (_idx >= mimgs.size() || _idx < 0) return midx = 0; return (midx = _idx); };
			virtual void customdraw();
			virtual void ontouchbegin(const msg*);
			virtual void ontouchend(const msg*);
		private:
			std::vector<GLuint> mimgs;
			int32_t midx;
			//rect mrcshow;
			static std::map < std::string, tex* > mtexs;
		};

		class img9 : public node{
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

