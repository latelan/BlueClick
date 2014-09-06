#if !defined(AFX_SERVICETHREAD_H__BFC92D5D_2A72_4887_B40B_ECAB5818C83A__INCLUDED_)
#define AFX_SERVICETHREAD_H__BFC92D5D_2A72_4887_B40B_ECAB5818C83A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiceThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServiceThread thread

class CServiceThread : public CWinThread
{
	DECLARE_DYNCREATE(CServiceThread)
protected:
	CServiceThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CServiceSocket m_serviceSocket;
	CWnd *m_pWnd;
	SOCKET m_hSocket;
	CString m_csResName;
	CString m_csResPath;
	DWORD  m_nPieceSize;
	DWORD  m_nPieceOffset;
	DWORD  m_nResSize;
	UINT   m_nThreadIndex;
// Operations
public:
	void SetMainWnd(CWnd *pWnd);
	void GetPieceOffset(int nThreadNum, int nThreadIndex, DWORD nResSize, DWORD &nPieceOffset, DWORD &nPieceSize);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CServiceThread();

	// Generated message map functions
	//{{AFX_MSG(CServiceThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICETHREAD_H__BFC92D5D_2A72_4887_B40B_ECAB5818C83A__INCLUDED_)
