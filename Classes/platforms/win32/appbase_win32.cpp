#include "appbase.h"
#include <Windows.h>
#include <stdint.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include <math.h>
#include "log.h"


NS_CROSSANY_BEGIN

// ȫ�ֱ���: 
static HINSTANCE hInst;								// ��ǰʵ��
const static TCHAR* szTitle = L"crossany_wnd";					// �������ı�
const static TCHAR* tcWndClass = L"opengl_crossany_wnd1.0";			// ����������

static BOOL painted = FALSE;
int64_t frames = 0;
HGLRC hRC = NULL;     // ������ɫ������  
HDC hDC = NULL;           // ˽��GDI�豸������  
HWND hWnd = NULL;     // �������ǵĴ��ھ��  
HINSTANCE hInstance;    // ��������ʵ��  
bool keys[256];         // ���ڼ������̵�����  
bool active = TRUE;       // ���ڵĻ��־��ȱʡΪTRUE  
bool fullscreen = TRUE;   // ȫ����־ȱʡ�趨��ȫ��ģʽ  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);// WndProc�Ķ��� 
GLsizei gwidth, gheight;
appbase* pThis = nullptr;

#define NEAR_PLANE    1.0
#define FAR_PLANE    20.0
#define FIELD_OF_VIEW    60.0

GLvoid ReSizeGLScene(appbase* pThis,GLsizei width, GLsizei height){// ���ò���ʼ��GL���ڴ�С  
	GLfloat    fAspectRatio;
	if (height == 0) height = 1;
	gwidth = width; gheight = height;
	glViewport(0, 0, width, height);	// Set the new view port:
	glMatrixMode(GL_PROJECTION);		// Setup the projection matrix:
	glLoadIdentity();
	fAspectRatio = ((GLfloat)width) / ((GLfloat)height);
	//gluPerspective(FIELD_OF_VIEW, fAspectRatio,	NEAR_PLANE, FAR_PLANE);
	//gluOrtho2D(-1, 1, -1, 1);
	glOrtho(0 - width / 2 , width / 2,0 - height/2, height/2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0f, 0.0f,20, 0.0f, 0.0f, 0, 0.0, 1.0, 0.0);	// Place the camera: // ��������ϵ��������ϵ����Ļ����Ϊԭ��(0, 0, 0)���������Ļ������ұ���x���ᣬ������y���ᣬ��Ļָ�����Ϊz���ᡣ���ȵ�λ���������� ���ڷ�Χ���˵�λǡ����(-1,-1)��(1,1)��
	//if (height == 0) height = 1;// ��ֹ����� // ��Height��Ϊ1  
	//glViewport(0, 0, width, height);// ���õ�ǰ���ӿ�(Viewport)  
	//glMatrixMode(GL_PROJECTION); //ѡ��ͶӰ����
	//glLoadIdentity();   //����ͶӰ����

	//���㴰�ڵı���
	//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	//glMatrixMode(GL_MODELVIEW); //ѡ��ģ����ͼ����
	//glLoadIdentity();    //����ģ����ͼ����
	////glMatrixMode(GL_PROJECTION);// ѡ��ͶӰ����  
	////glLoadIdentity();// ����ͶӰ����  
	//////gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);	// ���㴰�ڵ���۱���  
	////gluOrtho2D(0, width, 0, height);
	////glMatrixMode(GL_MODELVIEW);// ѡ��ģ�͹۲����  
	//////glLoadIdentity();// ����ģ�͹۲����  
	pThis->resize(size(width, height));
}
int InitGL(GLvoid){// �˴���ʼ��OpenGL������������  
	glShadeModel(GL_SMOOTH);// ������Ӱƽ��  
	glClearColor(0.65f, 0.65f, 0.65f, 0.0f);// ��ɫ����  
	glClearDepth(1.0f);// ������Ȼ���  
	glEnable(GL_DEPTH_TEST);// ������Ȳ���  
	glDepthFunc(GL_LEQUAL);// ������Ȳ��Ե�����  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// ������ϸ��͸������  
	return TRUE;// ��ʼ�� OK  
}

const int n = 100;
GLfloat R = 250.0f;
const GLfloat Pi = 3.1415926536f;

int DrawGLScene(appbase* pThis){// �����￪ʼ�������еĻ���  
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// �����Ļ����Ȼ���  
	//glLoadIdentity();// ���õ�ǰ��ģ�͹۲����  
	// �����µ�����  
	//glColor4f(1.0f, 0.0f, 0.0f,0.5f);
	//uibase ui;
	//ui.drawrc(20,20,200,200);
	//ui.drawln(200, 200, 400, 400);
	//ui.drawpt(300, 300);
	//ui.fillrc(20, 20, 300, 300);
	//GLfloat     rtri = 50;
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����ɫ����Ȼ���
	///glLoadIdentity(); //����ģ����ͼ����
	//glTranslatef(-1.5f, 0.0f, -6.0f); //�����ƶ�1.5����λ������Ļ���ƶ�6.0����λ
	//glRotatef(rtri, 0.0f, 1.0f, 0.0f);   // ��y����ת������( �¼Ӵ��� )
	//glBegin(GL_TRIANGLES);     //ʹ��GL_TRIANGLES��������������
	//glColor3f(1.0f, 0.0f, 0.0f);  //������ɫΪ��ɫ
	//glVertex3f(0.0f, 1.0f, 0.0f);// ���е������ƶ�һ����λ (�϶��㣩
	//�����Ѿ��ѵ�һ���������������Ļ�ϣ�������������ɫΪ��ɫ�������ǻ��Ƶڶ�������֮ǰ�����ǰ���ɫֵ��Ϊ��ɫ�����������ε����¶���ᱻ���Ƴ���ɫ��
	//	glColor3f(0.0f, 1.0f, 0.0f); //������ɫΪ��ɫ
	//glVertex3f(-1.0f, -1.0f, 0.0f); //���¶���
	//Ȼ�����ǻ��Ƶ�����Ҳ�����һ�����㡣�����ǻ���֮ǰ������ɫֵ��Ϊ��ɫ�����������ε����¶��㡣glEnd()����ִ��֮�󣬶���ν�����䡣��Ϊÿ���������ɫ��ͬ����ֻ��һ�̶ֹ���ɫ��ȣ���ɫ�����ÿһ��������ɢ������Ȼ�������Ļ�ϣ����е���ɫ�����һ�������ƽ����ɫ��
	//	glColor3f(0.0f, 0.0f, 1.0f);         //������ɫΪ��ɫ
	//glVertex3f(1.0f, -1.0f, 0.0f);    // ���¶���
	//glEnd();  //�������������

	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Draw the scene:
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
*/
	R = (GLfloat)gheight/2;
	glBegin(GL_POLYGON);//OpenGLҪ��ָ�������������������glBegin����֮��
	//glEnd����֮ǰ������ָ���Ķ��㽫�����ԣ�������glBegin��ָ�����ʹ����Щ��
	//GL_POLYGON��ʾ������Σ��ɵ����ӳɶ���Σ�
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i<n; ++i)
		glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));

	glEnd();


	pThis->draw();

	return TRUE;// һ��OK  
}
GLvoid KillGLWindow(GLvoid){// �������ٴ���  
	if (fullscreen){// ����ȫ��ģʽ��  
		ChangeDisplaySettings(NULL, 0);// �ǵĻ����л�������  
		ShowCursor(TRUE);// ��ʾ���ָ��  
	}
	if (hRC){// ӵ����ɫ��������  
		if (!wglMakeCurrent(NULL, NULL)) MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);// �ܷ��ͷ�DC��RC������  
		if (!wglDeleteContext(hRC))	MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);// �ܷ�ɾ��RC  
		hRC = NULL;// ��RC��ΪNULL  
	}
	if (hDC && !ReleaseDC(hWnd, hDC)){// �ܷ��ͷ�DC  
		MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;// ��DC��ΪNULL  
	}
	if (hWnd && !DestroyWindow(hWnd)){// �ܷ����ٴ���  
		MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;// ��hWnd��ΪNULL  
	}
	if (!UnregisterClass(tcWndClass, hInstance)){// �ܷ�ע��������  
		MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;// ��hInstance��ΪNULL  
	}
}

BOOL CreateGLWindow(appbase* pThis,const TCHAR* title, int width, int height, int bits, bool fullscreenflag){
	GLuint PixelFormat; RECT rc;          // �������ƥ��Ľ��  
	WNDCLASS wc; DWORD dwExStyle, dwStyle; // ���ڷ��  
	rc.left = rc.top = (long)0; rc.right = (long)width; rc.bottom = (long)height; 
	fullscreen = fullscreenflag;              // ����ȫ��ȫ����־  
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // �ƶ�ʱ�ػ�����Ϊ����ȡ��DC  
	wc.lpfnWndProc = (WNDPROC)WndProc;                         // WndProc������Ϣ  
	wc.cbClsExtra = 0; wc.cbWndExtra = 0; wc.hInstance = hInstance = GetModuleHandle(NULL);  // ����ʵ��  
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);                     // װ��ȱʡͼ��  
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);                   // װ�����ָ��  
	wc.hbrBackground = NULL; wc.lpszMenuName = NULL;                                                // GL����Ҫ����  
	wc.lpszClassName = tcWndClass;                                        // �趨������  

	if (!RegisterClass(&wc)){                                                    // ����ע�ᴰ����  
		appbase::alert(L"ע�ᴰ����ʧ��");
		return FALSE;// �˳�������FALSE  
	}
	if (fullscreen){// Ҫ����ȫ��ģʽ��  
		DEVMODE dmScreenSettings;                                           // �豸ģʽ  
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));   // ȷ���ڴ����  
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);           // Devmode �ṹ�Ĵ�С  
		dmScreenSettings.dmPelsWidth = width;                           // ��ѡ��Ļ���  
		dmScreenSettings.dmPelsHeight = height;                         // ��ѡ��Ļ�߶�  
		dmScreenSettings.dmBitsPerPel = bits;                               // ÿ������ѡ��ɫ�����  
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬����  
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL){
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�  
			if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By/nYour Video Card. Use Windowed Mode Instead?", L"NeHe GL",
				MB_YESNO | MB_ICONEXCLAMATION) == IDYES){
				fullscreen = FALSE;// ѡ�񴰿�ģʽ(Fullscreen=FALSE)  
			}
			else{
				// Pop Up A Message Box Letting User Know The Program Is Closing.  
				MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;//�˳�������FALSE  
			}
		}
	}
	if (fullscreen){// �Դ���ȫ��ģʽ��  
		dwExStyle = WS_EX_APPWINDOW;  // ��չ������  
		dwStyle = WS_POPUP;                   // ������  
		ShowCursor(FALSE);                      // �������ָ��  
	}
	else{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // ��չ������  
		dwStyle = WS_OVERLAPPEDWINDOW;                                // ������  
	}
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);// �������ڴﵽ����Ҫ��Ĵ�С  
	if (!(hWnd = CreateWindowEx(dwExStyle,           // ��չ������  
		tcWndClass,                                           // ������  
		title,                                                      // ���ڱ���  
		WS_CLIPSIBLINGS |                                   // ����Ĵ���������  
		WS_CLIPCHILDREN |                                   // ����Ĵ���������  
		dwStyle,                                                    // ѡ��Ĵ�������  
		0, 0,                                                        // ����λ��  
		rc.right - rc.left,               // ��������õĴ��ڿ��  
		rc.bottom - rc.top,           // ��������õĴ��ڸ߶�  
		NULL,                                                       // �޸�����  
		NULL,                                                       // �޲˵�  
		hInstance,                                              // ʵ��  
		NULL)))                                                 // ����WM_CREATE�����κζ���  
	{
		KillGLWindow();// ������ʾ��  
		MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// ���� FALSE  
	}
	static PIXELFORMATDESCRIPTOR pfd = {//pfd ���ߴ���������ϣ���Ķ���  
		sizeof(PIXELFORMATDESCRIPTOR),          //������ʽ�������Ĵ�С  
		1,                                                      // �汾��  
		PFD_DRAW_TO_WINDOW |                        // ��ʽ����֧�ִ���  
		PFD_SUPPORT_OPENGL |                        // ��ʽ����֧��OpenGL  
		PFD_DOUBLEBUFFER,                               // ����֧��˫����  
		PFD_TYPE_RGBA,                                  // ���� RGBA ��ʽ  
		bits,                                                   // ѡ��ɫ�����  
		0, 0, 0, 0, 0, 0,                                   // ���Ե�ɫ��λ  
		0,                                                      // ��Alpha����  
		0,                                                      // ����Shift Bit  
		0,                                                      // �޾ۼ�����  
		0, 0, 0, 0,                                         // ���Ծۼ�λ  
		16,                                                 // 16λ Z-���� (��Ȼ���)  
		0,                                                      // ��ģ�建��  
		0,                                                      // �޸�������  
		PFD_MAIN_PLANE,                             // ����ͼ��  
		0,                                                      // ����  
		0, 0, 0                                             // ���Բ�����  
	};
	if (!(hDC = GetDC(hWnd))){// ȡ���豸��������ô  
		KillGLWindow();// ������ʾ��  
		MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// ���� FALSE  
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))){// Windows �ҵ���Ӧ�����ظ�ʽ����  
		KillGLWindow();// ������ʾ��  
		MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// ���� FALSE  
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd)){// �ܹ��������ظ�ʽô  
		KillGLWindow();// ������ʾ��  
		MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// ���� FALSE  
	}
	if (!(hRC = wglCreateContext(hDC))){// �ܷ�ȡ����ɫ������  
		KillGLWindow();// ������ʾ��  
		MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// ���� FALSE  
	}
	if (!wglMakeCurrent(hDC, hRC)){// ���Լ�����ɫ������  
		KillGLWindow();// ������ʾ��  
		MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// ���� FALSE  
	}

	const char* ver = (char*)glGetString(GL_VERSION);

	ShowWindow(hWnd, SW_SHOW);       // ��ʾ����  
	SetForegroundWindow(hWnd);      // ����������ȼ�  
	SetFocus(hWnd);                         // ���ü��̵Ľ������˴���  
	ReSizeGLScene(pThis,width, height);       // ����͸�� GL ��Ļ  
	if (!InitGL()){// ��ʼ���½���GL����  
		KillGLWindow();// ������ʾ��  
		MessageBox(NULL, L"Initialization Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;// ���� FALSE  
	}
	return TRUE;// �ɹ�  
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {                // ���ӵ���Ϣ����  
	switch (uMsg){// ���Windows��Ϣ  
	case WM_ACTIVATE:{// ���Ӵ��ڼ�����Ϣ  
		if (!HIWORD(wParam)) active = TRUE;// �����С��״̬  // �����ڼ���״̬  
		else active = FALSE;// �����ټ���  
		OutputDebugString(L"WM_ACTIVATE\r\n");
		return 0;// ������Ϣѭ��  
	}break;
	case WM_SYSCOMMAND:{// �ж�ϵͳ����Intercept System Commands  
		OutputDebugString(L"WM_SYSCOMMAND\r\n");
		switch (wParam){// ���ϵͳ����Check System Calls  
		case SC_SCREENSAVE:// ����Ҫ����?  
		case SC_MONITORPOWER:// ��ʾ��Ҫ����ڵ�ģʽ?  
			return 0;// ��ֹ����  
		}
		break;// �˳�  
	}break;
	case WM_CLOSE:{// �յ�Close��Ϣ?  
		OutputDebugString(L"WM_CLOSE\r\n");
		PostQuitMessage(0);// �����˳���Ϣ  
		return 0;
	}break;
	case WM_KEYDOWN:{// �м�����ô?  
		OutputDebugString(L"WM_KEYDOWN\r\n");
		keys[wParam] = TRUE;// ����ǣ���ΪTRUE  
		//painted = TRUE;
		return 0;// ����  
	}break;
	case WM_KEYUP:{// �м��ſ�ô?  
		OutputDebugString(L"WM_KEYUP\r\n");
		keys[wParam] = FALSE;// ����ǣ���ΪFALSE  
		return 0;// ����  
	}break;
	case WM_SIZE:{
		ReSizeGLScene(pThis,LOWORD(lParam), HIWORD(lParam));
		return 0;
	}break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// ��DefWindowProc��������δ�������Ϣ��  
}


//appbase::appbase(){}
//appbase::~appbase(){}
void appbase::run(){
	MSG msg; BOOL done = FALSE; // �����˳�ѭ����Bool ����  
	pThis = this;
	// ��ʾ�û�ѡ������ģʽ  
	//if (MessageBox(NULL, _T("Would You Like To Run In Fullscreen Mode?"), _T("Start FullScreen?"), MB_YESNO | MB_ICONQUESTION) == IDNO)
	fullscreen = FALSE; // ����ģʽ  
	// ����OpenGL����  
	if (!CreateGLWindow(this,szTitle, 640, 480, 16, fullscreen)) return;// ʧ���˳�  
	if (init()){
		while (!done){// ����ѭ��ֱ�� done=TRUE  
			painted = FALSE;
			if (GetMessage(&msg, NULL, 0, 0) == 0)	break;		// WM_QUIT ����Ϣ�ڵȴ���?  
			if (msg.message == WM_PAINT){ painted = TRUE; }
			TranslateMessage(&msg); // ������Ϣ  
			DispatchMessage(&msg);  // ������Ϣ 
			//OutputDebugString(L"message\r\n");
			if (active){// ���򼤻��ô?  		// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ  
				if (keys[VK_ESCAPE]) done = TRUE;// ESC ������ô?  // ESC �����˳��ź�  
				else{// �����˳���ʱ��ˢ����Ļ  
					if (painted){// ���û����Ϣ 		
						//OutputDebugString(L"Paint\r\n");
						crossany::log::otprint("painted %d", painted);
						DrawGLScene(this);// ���Ƴ���  
						frames++;
						SwapBuffers(hDC);// �������� (˫����)  
					}
				}
			}
			if (keys[VK_F1]){// �����û�����F1����ȫ��ģʽ�ʹ���ģʽ���л�  
				keys[VK_F1] = FALSE;// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE  
				KillGLWindow();// ���ٵ�ǰ�Ĵ���  
				fullscreen = !fullscreen; // �л� ȫ�� / ���� ģʽ  
				// �ؽ� OpenGL ����  
				if (!CreateGLWindow(this,szTitle, 640, 480, 16, fullscreen))	return;// �������δ�ܴ����������˳�  
				painted = TRUE;
			}
		}
	}
	// �رճ���  
	KillGLWindow();// ���ٴ���  
	delete this;
	return ;// �˳�����  
};

NS_CROSSANY_END