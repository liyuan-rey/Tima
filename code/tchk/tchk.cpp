// tchk.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "tchk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma data_seg(".shared")
	HHOOK g_hHook = NULL;
	DWORD g_dwTimaThreadId = 0;
#pragma data_seg()

#pragma comment(linker, "/section:.shared,rws")

//
//	ע�⣡
//
//		����� DLL ��̬���ӵ� MFC
//		DLL���Ӵ� DLL ������
//		���� MFC ���κκ����ں�������ǰ��
//		��������� AFX_MANAGE_STATE �ꡣ
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CtchkApp

BEGIN_MESSAGE_MAP(CtchkApp, CWinApp)
END_MESSAGE_MAP()


// CtchkApp ����

CtchkApp::CtchkApp() : m_hWndHook(NULL)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CtchkApp ����

CtchkApp theApp;


// CtchkApp ��ʼ��

BOOL CtchkApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
