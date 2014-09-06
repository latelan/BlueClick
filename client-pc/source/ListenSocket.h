#if !defined(AFX_LISTENSOCKET_H__20D664E8_A9B4_4435_8DD1_4DCBC228025C__INCLUDED_)
#define AFX_LISTENSOCKET_H__20D664E8_A9B4_4435_8DD1_4DCBC228025C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//

#include "DownloadSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CSocket
{
// Attributes
public:
	CWnd *m_pWnd;
// Operations
public:
	CListenSocket(CWnd *pParentWnd);
	virtual ~CListenSocket();
	void SetMainWnd(CWnd *pWnd);

// Overrides
public:
	CWnd* m_pParentWnd;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__20D664E8_A9B4_4435_8DD1_4DCBC228025C__INCLUDED_)
