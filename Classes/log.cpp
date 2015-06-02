#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <process.h>
#include <time.h>
#include "log.h"
#include "tls.h"
#pragma warning (disable:4996) 
#include <Windows.h>

namespace crossany{
	namespace log{
		bool bout = true;
		int32_t otprint(const char* format, ...){
			if (!bout) return 0;
			va_list args; int len; char* buffer; time_t now = time(NULL); tm tm1; localtime_s(&tm1, &now);
			buffer = xiny120::_tlsget0();//new char[(len * sizeof(char))];
			sprintf(buffer, "%02d-%02d %02d:%02d:%02d ", tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
			//printf(buffer);
			OutputDebugStringA(buffer);
			va_start(args, format);	// retrieve the variable arguments
			len = _vscprintf(format, args) + 1; // _vscprintf doesn't count// terminating '\0'
			vsprintf_s(buffer, len, format, args); // C4996
			//puts(buffer);
			OutputDebugStringA(buffer); OutputDebugStringA("\r\n");
			//delete [] buffer;
			return 0;
		}
	}

}
