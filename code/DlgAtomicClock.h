#pragma once


// CDlgAtomicClock �Ի���

class CDlgAtomicClock : public CDialog
{
	DECLARE_DYNAMIC(CDlgAtomicClock)

public:
	CDlgAtomicClock(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAtomicClock();

// �Ի�������
	enum { IDD = IDD_ATOMICCLOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
