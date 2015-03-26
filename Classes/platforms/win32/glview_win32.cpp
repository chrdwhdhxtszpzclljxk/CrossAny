#include "../../glview.h"
#include <Windows.h>
#include <stdint.h>

NS_CROSSANY_BEGIN

// 全局变量: 
static HINSTANCE hInst;								// 当前实例
const static TCHAR* szTitle = L"crossany_wnd";					// 标题栏文本
const static TCHAR* szWindowClass = L"crossany_wnd";			// 主窗口类名

static BOOL painted = FALSE;
int64_t frames = 0;
HGLRC hRC = NULL;     // 永久着色描述表  
HDC hDC = NULL;           // 私有GDI设备描述表  
HWND hWnd = NULL;     // 保存我们的窗口句柄  
HINSTANCE hInstance;    // 保存程序的实例  
bool keys[256];         // 用于键盘例程的数组  
bool active = TRUE;       // 窗口的活动标志，缺省为TRUE  
bool fullscreen = TRUE;   // 全屏标志缺省设定成全屏模式  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);// WndProc的定义 

#define NEAR_PLANE    1.0
#define FAR_PLANE    200.0
#define FIELD_OF_VIEW    60.0

glview::glview(){}
glview::~glview(){}

glview* glview::me(){
	static glview* pv = 0;
	if (pv == 0){
		pv = new glview();
		if (pv != 0 && !pv->init()){ // 创建成功但是初始化失败。
			delete pv; pv = 0;
		}
	}
	return pv;
}

NS_CROSSANY_END