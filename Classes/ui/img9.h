#ifndef __CROSSANY_UI_IMG9_H_
#define __CROSSANY_UI_IMG9_H_

#pragma once
#include <vector>
#include <map>
#include <string>
#include "macro.h"
#include "node.h"
#include "../coordinate.h"

namespace crossany{
	namespace ui{
		class img : public node{
		private:
			img(){};
			~img(){};
		public:
			static img* create(const rect& _rc , const char*, ...); // 参数都是std::string类型的图片路径。
			virtual void customdraw();
		private:
			std::vector<GLuint> mimgs;
			rect mrcshow;
			static std::map < std::string, int64_t > mtexs;
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

