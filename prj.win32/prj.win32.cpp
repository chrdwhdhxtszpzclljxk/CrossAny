// prj.win32.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "prj.win32.h"


// ���ǵ���������һ��ʾ��
PRJWIN32_API int nprjwin32=0;

// ���ǵ���������һ��ʾ����
PRJWIN32_API int fnprjwin32(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� prj.win32.h
Cprjwin32::Cprjwin32()
{
	return;
}
