#if !defined(AFX_SERVICESOCKET_H__6D5BF871_1253_4FF9_9A52_B26DBE6A83F8__INCLUDED_)
#define AFX_SERVICESOCKET_H__6D5BF871_1253_4FF9_9A52_B26DBE6A83F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiceSocket.h : header file
//

//DWORD _stdcall ServiceThreadProc(LPVOID lpParameter);

///////e//////////////////////////////////////////////////////////////////////
// CServiceSocket command target

class CServiceSocket : public CSocket
{
// Attributes
public:
	CWnd *m_pParentWnd;
	UINT m_nSocketIndex;
	HANDLE m_hThreadService;

// Operations
public:
	CServiceSocket(CWnd *pParentWnd, UINT nSocketIndex);
	virtual ~CServiceSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceSocket)
	public:
//	virtual void OnReceive(int nErrorCode);
//	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServiceSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICESOCKET_H__6D5BF871_1253_4FF9_9A52_B26DBE6A83F8__INCLUDED_)
