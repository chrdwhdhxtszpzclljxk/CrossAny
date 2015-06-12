#include "appbase.h"
#include <Windows.h>
#include <stdint.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include <math.h>
#include "log.h"
#include "ui/img9.h"
#include "ui/ime.h"


NS_CROSSANY_BEGIN

// 全局变量: 
static HINSTANCE hInst;								// 当前实例
const static TCHAR* szTitle = L"crossany_wnd";					// 标题栏文本
const static TCHAR* tcWndClass = L"opengl_crossany_wnd1.0";			// 主窗口类名


int64_t frames = 0;
HGLRC hRC = NULL;     // 永久着色描述表  
HDC hDC = NULL;           // 私有GDI设备描述表  
HWND hWnd = NULL;     // 保存我们的窗口句柄  
HINSTANCE hInstance;    // 保存程序的实例  
bool keys[256];         // 用于键盘例程的数组  
bool active = TRUE;       // 窗口的活动标志，缺省为TRUE  
bool fullscreen = TRUE;   // 全屏标志缺省设定成全屏模式  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);// WndProc的定义 
GLsizei gwidth, gheight;
appbase* pThis = nullptr;

#define NEAR_PLANE    1.0
#define FAR_PLANE    20.0
#define FIELD_OF_VIEW    60.0

GLvoid ReSizeGLScene(appbase* pThis,GLsizei width, GLsizei height){// 重置并初始化GL窗口大小  
	//GLfloat    fAspectRatio;
	if (height == 0) height = 1;
	gwidth = width; gheight = height;
	glViewport(0, 0, width, height);	// Set the new view port:
	glMatrixMode(GL_PROJECTION);		// Setup the projection matrix:
	glLoadIdentity();
	//fAspectRatio = ((GLfloat)width) / ((GLfloat)height);
	//gluPerspective(FIELD_OF_VIEW, fAspectRatio,	NEAR_PLANE, FAR_PLANE);
	//gluOrtho2D(-1, 1, -1, 1);
	//glOrtho(0 - width / 2 , width / 2,0 - height/2, height/2, -1, 1);
	glOrtho(0, width , 0 , height , -1, 1); // 取第一象限坐标标示。
	//glOrtho(-1, 1 , -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0f, 0.0f,20, 0.0f, 0.0f, 0, 0.0, 1.0, 0.0);	// Place the camera: // 世界坐标系世界坐标系以屏幕中心为原点(0, 0, 0)。你面对屏幕，你的右边是x正轴，上面是y正轴，屏幕指向你的为z正轴。长度单位这样来定： 窗口范围按此单位恰好是(-1,-1)到(1,1)。
	//if (height == 0) height = 1;// 防止被零除 // 将Height设为1  
	//glViewport(0, 0, width, height);// 重置当前的视口(Viewport)  
	//glMatrixMode(GL_PROJECTION); //选择投影矩阵
	//glLoadIdentity();   //重置投影矩阵

	//计算窗口的比率
	//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	//glMatrixMode(GL_MODELVIEW); //选择模型视图矩阵
	//glLoadIdentity();    //重设模型视图矩阵
	////glMatrixMode(GL_PROJECTION);// 选择投影矩阵  
	////glLoadIdentity();// 重置投影矩阵  
	//////gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);	// 计算窗口的外观比例  
	////gluOrtho2D(0, width, 0, height);
	////glMatrixMode(GL_MODELVIEW);// 选择模型观察矩阵  
	//////glLoadIdentity();// 重置模型观察矩阵  
	pThis->resize(size(width, height));
}
int InitGL(GLvoid){// 此处开始对OpenGL进行所有设置  
	glShadeModel(GL_SMOOTH);// 启用阴影平滑  
	glClearColor(0.65f, 0.65f, 0.65f, 0.0f);// 黑色背景  
	glClearDepth(1.0f);// 设置深度缓存  
	glEnable(GL_DEPTH_TEST);// 启用深度测试  
	glDepthFunc(GL_LEQUAL);// 所作深度测试的类型  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// 真正精细的透视修正  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// 这里的src_alpha就是纹理的alpha通道的数据了
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_BLEND);

	//glEnable(GL_TEXTURE_2D);
	return TRUE;// 初始化 OK  
}

const int n = 100;
GLfloat R = 250.0f;
const GLfloat Pi = 3.1415926536f;

int DrawGLScene(appbase* pThis){// 从这里开始进行所有的绘制  
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除屏幕和深度缓存  
	//glLoadIdentity();// 重置当前的模型观察矩阵  
	// 增加新的物体  
	//glColor4f(1.0f, 0.0f, 0.0f,0.5f);
	//uibase ui;
	//ui.drawrc(20,20,200,200);
	//ui.drawln(200, 200, 400, 400);
	//ui.drawpt(300, 300);
	//ui.fillrc(20, 20, 300, 300);
	//GLfloat     rtri = 50;
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色和深度缓存
	///glLoadIdentity(); //重置模型视图矩阵
	//glTranslatef(-1.5f, 0.0f, -6.0f); //向左移动1.5个单位，向屏幕里移动6.0个单位
	//glRotatef(rtri, 0.0f, 1.0f, 0.0f);   // 沿y轴旋转三角形( 新加代码 )
	//glBegin(GL_TRIANGLES);     //使用GL_TRIANGLES参数绘制三角形
	//glColor3f(1.0f, 0.0f, 0.0f);  //设置颜色为红色
	//glVertex3f(0.0f, 1.0f, 0.0f);// 从中点向上移动一个单位 (上顶点）
	//我们已经把第一个顶点绘制在了屏幕上，并设置它的颜色为红色。在我们绘制第二个顶点之前，我们把颜色值改为绿色。这样三角形的左下顶点会被绘制成绿色。
	//	glColor3f(0.0f, 1.0f, 0.0f); //设置颜色为绿色
	//glVertex3f(-1.0f, -1.0f, 0.0f); //左下顶点
	//然后我们绘制第三个也是最后一个顶点。在我们绘制之前，把颜色值改为蓝色。它是三角形的右下顶点。glEnd()函数执行之后，多边形将被填充。因为每个顶点的颜色不同，和只有一种固定颜色相比，颜色将会从每一个顶点扩散开来，然后杂中心汇合，所有的颜色混合在一起。这就是平滑着色。
	//	glColor3f(0.0f, 0.0f, 1.0f);         //设置颜色为蓝色
	//glVertex3f(1.0f, -1.0f, 0.0f);    // 右下顶点
	//glEnd();  //绘制三角形完成

	/*
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 1, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1, 0, 0.0f);
	glEnd();
	
	// Draw the scene:
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 1.0f, 0.0f);
	glVertex3f(0.5f, -1, 0.0f);
	glEnd();

	R = (GLfloat)gheight/2;
	glBegin(GL_POLYGON);//OpenGL要求：指定顶点的命令必须包含在glBegin函数之后，
	//glEnd函数之前（否则指定的顶点将被忽略）。并由glBegin来指明如何使用这些点
	//GL_POLYGON表示画多边形（由点连接成多边形）
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i<n; ++i)
		glVertex2f(R*cos(2 * Pi / n*i) + gwidth / 2, R*sin(2 * Pi / n*i) + gheight /2);

	glEnd();
*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the screen.
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);

	pThis->draw();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	return TRUE;// 一切OK  
}
GLvoid KillGLWindow(GLvoid){// 正常销毁窗口  
	if (fullscreen){// 处于全屏模式吗  
		ChangeDisplaySettings(NULL, 0);// 是的话，切换回桌面  
		ShowCursor(TRUE);// 显示鼠标指针  
	}
	if (hRC){// 拥有着色描述表吗  
		if (!wglMakeCurrent(NULL, NULL)) MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);// 能否释放DC和RC描述表  
		if (!wglDeleteContext(hRC))	MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);// 能否删除RC  
		hRC = NULL;// 将RC设为NULL  
	}
	if (hDC && !ReleaseDC(hWnd, hDC)){// 能否释放DC  
		MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;// 将DC设为NULL  
	}
	if (hWnd && !DestroyWindow(hWnd)){// 能否销毁窗口  
		MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;// 将hWnd设为NULL  
	}
	if (!UnregisterClass(tcWndClass, hInstance)){// 能否注销窗口类  
		MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;// 将hInstance设为NULL  
	}
}

BOOL CreateGLWindow(appbase* pThis,const TCHAR* title, int width, int height, int bits, bool fullscreenflag){
	GLuint PixelFormat; RECT rc;          // 保存查找匹配的结果  
	WNDCLASS wc; DWORD dwExStyle, dwStyle; // 窗口风格  
	rc.left = rc.top = (long)0; rc.right = (long)width; rc.bottom = (long)height; 
	fullscreen = fullscreenflag;              // 设置全局全屏标志  
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // 移动时重画，并为窗口取得DC  
	wc.lpfnWndProc = (WNDPROC)WndProc;                         // WndProc处理消息  
	wc.cbClsExtra = 0; wc.cbWndExtra = 0; wc.hInstance = hInstance = GetModuleHandle(NULL);  // 设置实例  
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);                     // 装入缺省图标  
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);                   // 装入鼠标指针  
	wc.hbrBackground = NULL; wc.lpszMenuName = NULL;                                                // GL不需要背景  
	wc.lpszClassName = tcWndClass;                                        // 设定类名字  

	if (!RegisterClass(&wc)){                                                    // 尝试注册窗口类  
		appbase::alert(L"RegisterClass fail");
		return FALSE;// 退出并返回FALSE  
	}
	if (fullscreen){// 要尝试全屏模式吗  
		DEVMODE dmScreenSettings;                                           // 设备模式  
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));   // 确保内存分配  
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);           // Devmode 结构的大小  
		dmScreenSettings.dmPelsWidth = width;                           // 所选屏幕宽度  
		dmScreenSettings.dmPelsHeight = height;                         // 所选屏幕高度  
		dmScreenSettings.dmBitsPerPel = bits;                               // 每象素所选的色彩深度  
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		// 尝试设置显示模式并返回结果。注: CDS_FULLSCREEN 移去了状态条。  
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL){
			// 若模式失败，提供两个选项：退出或在窗口内运行。  
			if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By/nYour Video Card. Use Windowed Mode Instead?", L"NeHe GL",
				MB_YESNO | MB_ICONEXCLAMATION) == IDYES){
				fullscreen = FALSE;// 选择窗口模式(Fullscreen=FALSE)  
			}
			else{
				// Pop Up A Message Box Letting User Know The Program Is Closing.  
				MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;//退出并返回FALSE  
			}
		}
	}
	if (fullscreen){// 仍处于全屏模式吗  
		dwExStyle = WS_EX_APPWINDOW;  // 扩展窗体风格  
		dwStyle = WS_POPUP;                   // 窗体风格  
		ShowCursor(FALSE);                      // 隐藏鼠标指针  
	}
	else{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // 扩展窗体风格  
		dwStyle = WS_OVERLAPPEDWINDOW;                                // 窗体风格  
	}
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);// 调整窗口达到真正要求的大小  
	if (!(hWnd = CreateWindowEx(dwExStyle,           // 扩展窗体风格  
		tcWndClass,                                           // 类名字  
		title,                                                      // 窗口标题  
		WS_CLIPSIBLINGS |                                   // 必须的窗体风格属性  
		WS_CLIPCHILDREN |                                   // 必须的窗体风格属性  
		dwStyle,                                                    // 选择的窗体属性  
		0, 0,                                                        // 窗口位置  
		rc.right - rc.left,               // 计算调整好的窗口宽度  
		rc.bottom - rc.top,           // 计算调整好的窗口高度  
		NULL,                                                       // 无父窗口  
		NULL,                                                       // 无菜单  
		hInstance,                                              // 实例  
		NULL)))                                                 // 不向WM_CREATE传递任何东东  
	{
		KillGLWindow();// 重置显示区  
		MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// 返回 FALSE  
	}
	static PIXELFORMATDESCRIPTOR pfd = {//pfd 告诉窗口我们所希望的东东  
		sizeof(PIXELFORMATDESCRIPTOR),          //上述格式描述符的大小  
		1,                                                      // 版本号  
		PFD_DRAW_TO_WINDOW |                        // 格式必须支持窗口  
		PFD_SUPPORT_OPENGL |                        // 格式必须支持OpenGL  
		PFD_DOUBLEBUFFER,                               // 必须支持双缓冲  
		PFD_TYPE_RGBA,                                  // 申请 RGBA 格式  
		bits,                                                   // 选定色彩深度  
		0, 0, 0, 0, 0, 0,                                   // 忽略的色彩位  
		0,                                                      // 无Alpha缓存  
		0,                                                      // 忽略Shift Bit  
		0,                                                      // 无聚集缓存  
		0, 0, 0, 0,                                         // 忽略聚集位  
		16,                                                 // 16位 Z-缓存 (深度缓存)  
		0,                                                      // 无模板缓存  
		0,                                                      // 无辅助缓存  
		PFD_MAIN_PLANE,                             // 主绘图层  
		0,                                                      // 保留  
		0, 0, 0                                             // 忽略层遮罩  
	};
	if (!(hDC = GetDC(hWnd))){// 取得设备描述表了么  
		KillGLWindow();// 重置显示区  
		MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// 返回 FALSE  
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))){// Windows 找到相应的象素格式了吗  
		KillGLWindow();// 重置显示区  
		MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// 返回 FALSE  
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd)){// 能够设置象素格式么  
		KillGLWindow();// 重置显示区  
		MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// 返回 FALSE  
	}
	if (!(hRC = wglCreateContext(hDC))){// 能否取得着色描述表  
		KillGLWindow();// 重置显示区  
		MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// 返回 FALSE  
	}
	if (!wglMakeCurrent(hDC, hRC)){// 尝试激活着色描述表  
		KillGLWindow();// 重置显示区  
		MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// 返回 FALSE  
	}

	const char* ver = (char*)glGetString(GL_VERSION);

	ShowWindow(hWnd, SW_SHOW);       // 显示窗口  
	SetForegroundWindow(hWnd);      // 略略提高优先级  
	SetFocus(hWnd);                         // 设置键盘的焦点至此窗口  
	ReSizeGLScene(pThis,width, height);       // 设置透视 GL 屏幕  
	if (!InitGL()){// 初始化新建的GL窗口  
		KillGLWindow();// 重置显示区  
		MessageBox(NULL, L"Initialization Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// 返回 FALSE  
	}
	return TRUE;// 成功  
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {                // 附加的消息内容  
	switch (uMsg){// 检查Windows消息  
	case WM_ACTIVATE:{// 监视窗口激活消息  
		if (!HIWORD(wParam)) active = TRUE;// 检查最小化状态  // 程序处于激活状态  
		else active = FALSE;// 程序不再激活  
		OutputDebugString(L"WM_ACTIVATE\r\n");
		return 0;// 返回消息循环  
	}break;
	case WM_SYSCOMMAND:{// 中断系统命令Intercept System Commands  
		OutputDebugString(L"WM_SYSCOMMAND\r\n");
		switch (wParam){// 检查系统调用Check System Calls  
		case SC_SCREENSAVE:// 屏保要运行?  
		case SC_MONITORPOWER:// 显示器要进入节电模式?  
			return 0;// 阻止发生  
		}
		break;// 退出  
	}break;
	case WM_CLOSE:{// 收到Close消息?  
		OutputDebugString(L"WM_CLOSE\r\n");
		PostQuitMessage(0);// 发出退出消息  
		return 0;
	}break;
	case WM_KEYDOWN:{// 有键按下么?  
		OutputDebugString(L"WM_KEYDOWN\r\n");
		keys[wParam] = TRUE;// 如果是，设为TRUE  
		//painted = TRUE;
		return 0;// 返回  
	}break;
	case WM_KEYUP:{// 有键放开么?  
		OutputDebugString(L"WM_KEYUP\r\n");
		keys[wParam] = FALSE;// 如果是，设为FALSE  
		return 0;// 返回  
	}break;
	case WM_SIZE:{
		ReSizeGLScene(pThis,LOWORD(lParam), HIWORD(lParam));
		return 0;
	}break;
	case WM_LBUTTONUP:{
		ReleaseCapture();
		pThis->onevent(uMsg, wParam, lParam);
		appbase::updateui();
	}break;
	case WM_LBUTTONDOWN:{
		SetCapture(hWnd);
		pThis->onevent(uMsg, wParam, lParam);
		appbase::updateui();
	}break;
	case WM_MOUSEMOVE:{
		//pThis->onevent(uMsg, wParam, lParam);
	}break;
	case WM_CHAR:{
		wchar_t* txt = (wchar_t*)&wParam;
		wchar_t msg[128] = { 0 };
		char utf8[128] = { 0 };
		msg[0] = txt[0];
		WideCharToMultiByte(CP_UTF8, 0, msg, -1, utf8, sizeof(utf8), nullptr, nullptr);
		crossany::ui::ime::me()->insert(utf8);
		crossany::log::otprint("ddd");
	}break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 向DefWindowProc传递所有未处理的消息。  
}


//appbase::appbase(){}
//appbase::~appbase(){}
void appbase::run(){
	MSG msg; BOOL done = FALSE; // 用来退出循环的Bool 变量  
	pThis = this;
	// 提示用户选择运行模式  
	//if (MessageBox(NULL, _T("Would You Like To Run In Fullscreen Mode?"), _T("Start FullScreen?"), MB_YESNO | MB_ICONQUESTION) == IDNO)
	fullscreen = FALSE; // 窗口模式  
	// 创建OpenGL窗口  
	if (!CreateGLWindow(this,szTitle, 640, 480, 16, fullscreen)) return;// 失败退出  
	if (init()){
		while (!done){// 保持循环直到 done=TRUE  
			painted = false;
			if (GetMessage(&msg, NULL, 0, 0) == 0)	break;		// WM_QUIT 有消息在等待吗?  
			if (msg.message == WM_PAINT){ painted = true; }
			TranslateMessage(&msg); // 翻译消息  
			DispatchMessage(&msg);  // 发送消息 
			//OutputDebugString(L"message\r\n");
			if (active){// 程序激活的么?  		// 绘制场景。监视ESC键和来自DrawGLScene()的退出消息  
				if (keys[VK_ESCAPE]) done = TRUE;// ESC 按下了么?  // ESC 发出退出信号  
				else{// 不是退出的时候，刷新屏幕  
					if (painted){// 如果没有消息 		
						//OutputDebugString(L"Paint\r\n");
						crossany::log::otprint("painted %d", painted);
						DrawGLScene(this);// 绘制场景  
						frames++;
						SwapBuffers(hDC);// 交换缓存 (双缓存)  
					}
				}
			}
			if (keys[VK_F1]){// 允许用户按下F1键在全屏模式和窗口模式间切换  
				keys[VK_F1] = FALSE;// 若是，使对应的Key数组中的值为 FALSE  
				KillGLWindow();// 销毁当前的窗口  
				fullscreen = !fullscreen; // 切换 全屏 / 窗口 模式  
				// 重建 OpenGL 窗口  
				if (!CreateGLWindow(this,szTitle, 640, 480, 16, fullscreen))	return;// 如果窗口未能创建，程序退出  
				painted = true;
			}
		}
	}
	// 关闭程序  
	KillGLWindow();// 销毁窗口  
	delete this;
	return ;// 退出程序  
};

void appbase::onevent(const UINT& msg, const WPARAM& w, const LPARAM& l){
	orz.onevent(msg, w, l);
}

void appbase::updateui(){
	RedrawWindow(hWnd, NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
	painted = true;
}

#include "appbase.hpp"

NS_CROSSANY_END