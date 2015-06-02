#ifndef __CROSSANY_UI_BUTTON_H_
#define __CROSSANY_UI_BUTTON_H_
#include "macro.h"
#include "node.h"
#pragma once

//NS_CROSSANY_BEGIN
namespace crossany{
	namespace ui{
		class CROSSANY_API button :public node{
		public:
			button();
			~button();
			virtual void draw();

		};
	}
}

#endif