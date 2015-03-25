// prj.win32.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "prj.win32.h"


// 这是导出变量的一个示例
PRJWIN32_API int nprjwin32=0;

// 这是导出函数的一个示例。
PRJWIN32_API int fnprjwin32(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 prj.win32.h
Cprjwin32::Cprjwin32()
{
	return;
}
