#pragma once

#include <SmartPtr.h>
#include "include\w3mfc\sntp.h"

class CTimeServer
{
public:
	class CNtpContext
	{
	public:
		CNtpContext(LPCTSTR szSvrUrl) : m_strSvrUrl(szSvrUrl),
			m_bHasResult(FALSE) {};

		~CNtpContext() {};

		CString m_strSvrUrl;
		BOOL m_bHasResult;
		NtpServerResponse m_ntpResponse;
	};

	typedef Loki::SmartPtr<CNtpContext, Loki::RefCountedMTAdj<Loki::ClassLevelLockable>::RefCountedMT> CNtpContextPtr;
//	typedef Loki::SmartPtr<CNtpContext, Loki::RefCountedMTAdj<Loki::ObjectLevelLockable>::RefCountedMT, Loki::DisallowConversion, Loki::AssertCheck, Loki::LockedStorage> CNtpContextPtr;
	typedef CSimpleMap<CString, CNtpContextPtr> CNtpServerMap;

public:
	CTimeServer(void);
	virtual ~CTimeServer(void);

public:
	BOOL IsValidServerUrl(LPCTSTR szSvrUrl);
	BOOL AddServer(LPCTSTR szSvrUrl);
	BOOL RemoveServer(LPCTSTR szSvrUrl);
	BOOL RemoveAllServer();
	CNtpContextPtr GetServerInfo(LPCTSTR szSvrUrl) const;

	AFX_INLINE const CNtpServerMap& GetServerMap() {
		return m_mapServer;
	}

	BOOL IsReady(int* pnReason = NULL);
	BOOL StartCheck(HWND hwndReceiver);
	BOOL GetDifference(double& dDiff);

protected:
	static UINT NtpMonitorProc(LPVOID pParam);
	static int AddNtpClientThread(CNtpServerMap& mapServer, int nStartIndex, CSimpleArray<HANDLE>& arrWaitThreadHandle);
	static UINT NtpClientProc(LPVOID pParam);

protected:
	CNtpServerMap m_mapServer;
	HANDLE m_hMonitorThread;
	HWND m_hwndReceiver;
	CEvent m_evtMonitorContinue;
};
