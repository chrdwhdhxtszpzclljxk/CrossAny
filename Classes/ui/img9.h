#ifndef __CROSSANY_UI_IMG9_H_
#define __CROSSANY_UI_IMG9_H_
#pragma once
#include <vector>
#include <string>
#include "macro.h"
#include "node.h"

namespace crossany{
	namespace ui{
		class img9 : public node{
		public:
			img9();
			~img9();
		private:
			std::vector<std::string> mimgs;
		};
	}
}
#endif

