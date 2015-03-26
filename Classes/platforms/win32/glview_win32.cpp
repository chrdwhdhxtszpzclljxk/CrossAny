#include "../../glview.h"
#include <Windows.h>
#include <stdint.h>

NS_CROSSANY_BEGIN

// ȫ�ֱ���: 
static HINSTANCE hInst;								// ��ǰʵ��
const static TCHAR* szTitle = L"crossany_wnd";					// �������ı�
const static TCHAR* szWindowClass = L"crossany_wnd";			// ����������

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

#define NEAR_PLANE    1.0
#define FAR_PLANE    200.0
#define FIELD_OF_VIEW    60.0

glview::glview(){}
glview::~glview(){}

glview* glview::me(){
	static glview* pv = 0;
	if (pv == 0){
		pv = new glview();
		if (pv != 0 && !pv->init()){ // �����ɹ����ǳ�ʼ��ʧ�ܡ�
			delete pv; pv = 0;
		}
	}
	return pv;
}

NS_CROSSANY_END