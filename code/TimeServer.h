#pragma once

#include <SmartPtr.h>
#include "include\w3mfc\sntp.h"

class CTimeServer
{
public:
	class CNtpContext
	{
	public:
		CNtpContext(LPCTSTR szSvrName) : m_strSvrName(szSvrName),
			m_bHasResult(FALSE) {};

		~CNtpContext() {};

		CString m_strSvrName;
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
	BOOL IsValidServerName(LPCTSTR szSvrName);
	BOOL AddServer(LPCTSTR szSvrName);
	BOOL RemoveServer(LPCTSTR szSvrName);
	BOOL RemoveAllServer();
	CNtpContextPtr GetServerInfo(LPCTSTR szSvrName) const;

	AFX_INLINE const CNtpServerMap& GetServerInfo() {
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
};
