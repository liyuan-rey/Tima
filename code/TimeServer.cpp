#include "StdAfx.h"
#include ".\timeserver.h"

CTimeServer::CTimeServer(void) : m_hwndReceiver(NULL)
{
}

CTimeServer::~CTimeServer(void)
{
	// we must ensure monitor thread was finished
	DWORD dwStatus = -2;
	::GetExitCodeThread(m_hMonitorThread, &dwStatus);
	if (STILL_ACTIVE == dwStatus)
	{
		//TODO: Add some notify to user

		if (WAIT_TIMEOUT == ::WaitForSingleObject(m_hMonitorThread, TIMA_THREAD_TIMEOUT))
		{
			ATLASSERT( FALSE && _T("Wait ntp monitor thread timeout!") );
			::TerminateThread(m_hMonitorThread, -1);
		}

		m_hMonitorThread = NULL;
	}
}

BOOL CTimeServer::IsValidServerName(LPCTSTR szSvrName)
{
	if (NULL == szSvrName)
		return FALSE;

	// Do not allow repeated server
	CNtpContextPtr spContext = m_mapServer.Lookup(CString(szSvrName));
	if (spContext)
		return FALSE;

	//TODO: Add more syntax checking, we take "a.com" and "1.2.3.4" now

	return TRUE;
}

BOOL CTimeServer::AddServer(LPCTSTR szSvrName)
{
	if (!IsValidServerName(szSvrName))
		return FALSE;

	int nReason = 0;
	if (!IsReady(&nReason) && (1 != nReason))
		return FALSE;

	CString strSvrName = szSvrName;
	CNtpContextPtr spContext = new CNtpContext(strSvrName);

	return m_mapServer.Add(strSvrName, spContext);
}

BOOL CTimeServer::RemoveServer(LPCTSTR szSvrName)
{
	if (!IsReady())
		return FALSE;

	return m_mapServer.Remove(CString(szSvrName));
}

BOOL CTimeServer::RemoveAllServer()
{
	if (!IsReady())
		return FALSE;

	m_mapServer.RemoveAll();

	return TRUE;
}

CTimeServer::CNtpContextPtr CTimeServer::GetServerInfo(LPCTSTR szSvrName) const
{
	return m_mapServer.Lookup(CString(szSvrName));
}

BOOL CTimeServer::IsReady(int* pnReason/* = NULL*/)
{
	if (pnReason)
		*pnReason = 0;

	// We need at least one server
	INT_PTR nSize = m_mapServer.GetSize();
	if (nSize < 1)
	{
		if (pnReason)
			*pnReason = 1;

		return FALSE;
	}

	// Monitor thread needs to be stopped
	DWORD dwStatus = 0;
	::GetExitCodeThread(m_hMonitorThread, &dwStatus);
	if (STILL_ACTIVE == dwStatus)
	{
		if (pnReason)
			*pnReason = 2;

		return FALSE;
	}

	m_hMonitorThread = NULL;

	return TRUE;
}

BOOL CTimeServer::StartCheck(HWND hwndReceiver)
{
	if (!::IsWindow(hwndReceiver))
		return FALSE;

	if (!IsReady())
		return FALSE;

	m_hwndReceiver = hwndReceiver;

	CWinThread* pMonitorThread = AfxBeginThread(CTimeServer::NtpMonitorProc,
		this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	ATLASSERT( NULL != pMonitorThread );

	m_hMonitorThread = pMonitorThread->m_hThread;
	pMonitorThread->ResumeThread();

	return TRUE;
}

UINT CTimeServer::NtpMonitorProc(LPVOID pParam)
{
	ATLASSERT(pParam);
	CTimeServer* pTimeServer = static_cast<CTimeServer*>(pParam);

	int nCurrentIndex = 0;
	CSimpleArray<HANDLE> arrWaitThreadHandle;

	do
	{
		nCurrentIndex = CTimeServer::AddNtpClientThread(
			pTimeServer->m_mapServer, nCurrentIndex, arrWaitThreadHandle);

		int nSize = arrWaitThreadHandle.GetSize();
		DWORD dwResult = ::WaitForMultipleObjects(nSize, arrWaitThreadHandle.GetData(),
							FALSE, TIMA_THREAD_TIMEOUT);

		if (WAIT_TIMEOUT == dwResult)
		{
			ATLASSERT( FALSE && _T("Wait ntp worker thread timeout!") );

			for (int i = 0; i < nSize; i++)
				::TerminateThread(arrWaitThreadHandle[i], -1);

			arrWaitThreadHandle.RemoveAll();
		}
		else if (dwResult >= WAIT_OBJECT_0 && dwResult < WAIT_OBJECT_0 + nSize)
		{
			arrWaitThreadHandle.RemoveAt(dwResult - WAIT_OBJECT_0);
		}
		else if (WAIT_FAILED == dwResult)
		{
			DWORD dwExitCode;
			for (int i = 0; i < arrWaitThreadHandle.GetSize(); i++)
			{
				dwExitCode = 0;
				::GetExitCodeThread(arrWaitThreadHandle[i], &dwExitCode);
				if (STILL_ACTIVE != dwExitCode)
					arrWaitThreadHandle.RemoveAt(i--);
			}
		}
		else
			ATLASSERT( FALSE && _T("Should never been here!") );
	}
	while(arrWaitThreadHandle.GetSize() > 0
			|| pTimeServer->m_mapServer.GetSize() > nCurrentIndex);

	// Post Message
	HWND hwndReceiver = pTimeServer->m_hwndReceiver;
	pTimeServer->m_hwndReceiver = NULL;

	if (::IsWindow(hwndReceiver))
		::PostMessage(hwndReceiver, WM_TIMA_NTPRESPONSED, NULL, NULL);

	return 0L;
}

int CTimeServer::AddNtpClientThread(CNtpServerMap& mapServer, int nStartIndex, CSimpleArray<HANDLE>& arrWaitThreadHandle)
{
	const int MAX_RUNNING_THREAD_NUM = 3;

	int nCurrentIndex = nStartIndex;
	CWinThread* pWinThread = NULL;
	INT_PTR nSize = mapServer.GetSize();

	for (; nCurrentIndex < nSize; nCurrentIndex++)
	{
		CNtpContextPtr& rspContext = mapServer.GetValueAt(nCurrentIndex);

		pWinThread = AfxBeginThread(CTimeServer::NtpClientProc,
						&rspContext, THREAD_PRIORITY_NORMAL,
						0, CREATE_SUSPENDED, NULL);
		ATLASSERT( NULL != pWinThread );

		arrWaitThreadHandle.Add(pWinThread->m_hThread);

		pWinThread->ResumeThread();

		if (arrWaitThreadHandle.GetSize() >= MAX_RUNNING_THREAD_NUM)
		{
			nCurrentIndex++;
			break;
		}
	}

	return nCurrentIndex;
}

UINT CTimeServer::NtpClientProc(LPVOID pParam)
{
	ATLASSERT(pParam);

	CNtpContextPtr spContext = *(static_cast<CNtpContextPtr*>(pParam));
	ATLASSERT( spContext);

	CSNTPClient sntp;
	spContext->m_bHasResult = sntp.GetServerTime(spContext->m_strSvrName,
									spContext->m_ntpResponse);

	return 0L;
}

BOOL CTimeServer::GetDifference(double& dDiff)
{
	// Wait util monitor thread quit
	int nReason;
	BOOL bReady = IsReady(&nReason);
	if (!bReady)
	{
		while (2 == nReason)
		{
			Sleep(50);
			bReady = IsReady(&nReason);
		}

		if (!bReady)
			return FALSE;
	}

	dDiff = 0;
	int nSuccess = 0;

	CNtpContextPtr spContext;
	BOOL bAtLeastOneSuccess = FALSE;

	INT_PTR nSize = m_mapServer.GetSize();
	for (int i = 0; i < nSize; i++)
	{
		spContext = m_mapServer.GetValueAt(i);

		if (spContext->m_bHasResult)
		{
			dDiff += spContext->m_ntpResponse.m_LocalClockOffset;
			nSuccess++;
		}
	}

	if (nSuccess)
	{
		dDiff = dDiff / nSuccess;
		return TRUE;
	}

	return FALSE;
}
