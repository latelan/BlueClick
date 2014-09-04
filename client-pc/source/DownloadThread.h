#if !defined(AFX_DOWNLOADTHREAD_H__4DA1573C_036F_4094_B8F5_84EE46573ECF__INCLUDED_)
#define AFX_DOWNLOADTHREAD_H__4DA1573C_036F_4094_B8F5_84EE46573ECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DownloadThread.h : header file
//

#include "DownloadSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CDownloadThread thread

class CDownloadThread : public CWinThread
{
	DECLARE_DYNCREATE(CDownloadThread)
protected:
	CDownloadThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CWnd   *m_pWnd;
	CDownloadSocket m_downloadSocket;
	SOCKET  m_hSocket;
	CString m_csResMD5;
	CString m_csSavePath;
	CString m_csServerAddr;
	UINT    m_nServerPort;
	CString m_csHostAddr;
	UINT    m_nThreadIndex;
	UINT    m_nListItem;
	__int64 m_nPieceSize;
	__int64 m_nPieceOffset;
	__int64 m_nSaveSize;
// Operations
public:
	void SetMainWnd(CWnd *pWnd);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownloadThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDownloadThread();

	// Generated message map functions
	//{{AFX_MSG(CDownloadThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNLOADTHREAD_H__4DA1573C_036F_4094_B8F5_84EE46573ECF__INCLUDED_)
