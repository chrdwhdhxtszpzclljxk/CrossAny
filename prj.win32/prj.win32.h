// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PRJWIN32_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PRJWIN32_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef PRJWIN32_EXPORTS
#define PRJWIN32_API __declspec(dllexport)
#else
#define PRJWIN32_API __declspec(dllimport)
#endif


// �����Ǵ� prj.win32.dll ������
class PRJWIN32_API Cprjwin32 {
public:
	Cprjwin32(void);
	// TODO:  �ڴ�������ķ�����
};

extern PRJWIN32_API int nprjwin32;

PRJWIN32_API int fnprjwin32(void);
