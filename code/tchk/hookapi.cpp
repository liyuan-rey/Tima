//

#include "stdafx.h"
#include "tchk.h"
#include "hookapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//

extern HHOOK g_hHook;
extern DWORD g_dwTimaThreadId;

//

LRESULT WINAPI GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	static BOOL bFirstTime = TRUE;

	if (bFirstTime)
	{
		bFirstTime = FALSE;

		//todo: subclass target window

		// Tell tima we are ready to handle requests
		::PostThreadMessage(g_dwTimaThreadId, WM_NULL, 0, 0);
	}

	return (CallNextHookEx(g_hHook, nCode, wParam, lParam));
}

//

BOOL WINAPI InstallTrayClockHook(HWND hWndHook)
{
	ATLASSERT( ::IsWindow(hWndHook) );

	if (NULL != g_hHook)
	{
		ATLASSERT( FALSE && "Hook have already set." );
		return FALSE;
	}

	// 
	g_dwTimaThreadId = ::GetCurrentThreadId();

	DWORD dwHookThreadId = ::GetWindowThreadProcessId(hWndHook, NULL);
	g_hHook = ::SetWindowsHookEx(WH_GETMESSAGE, 
				GetMsgProc, theApp.m_hInstance, dwHookThreadId);

	BOOL bSuccess = (NULL != g_hHook);
	if (bSuccess)
	{
		bSuccess = PostThreadMessage(dwHookThreadId, NULL, 0, 0);
		theApp.m_hWndHook = hWndHook;
	}

	return bSuccess;
}

BOOL WINAPI UninstallTrayClockHook()
{
	if (NULL == g_hHook)
	{
		ATLASSERT( FALSE && "Hook is not been set yet." );
		return FALSE;
	}

	BOOL bSuccess = UnhookWindowsHookEx(g_hHook);
	g_hHook = NULL;

	return bSuccess;
}
