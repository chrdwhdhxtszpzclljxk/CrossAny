#ifndef CROSSANY_LOG_H__
#define CROSSANY_LOG_H__
#pragma once
#include "macro.h"
#include <string>
#include <stdint.h>

namespace crossany{
	namespace log{
		int32_t otprint(const char* fmt, ...);
	}
}
#endif