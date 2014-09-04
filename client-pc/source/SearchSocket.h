#if !defined(AFX_SearchSocket_H__1F4A6A63_3A16_4112_8233_A15ADE4F5F1F__INCLUDED_)
#define AFX_SearchSocket_H__1F4A6A63_3A16_4112_8233_A15ADE4F5F1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSearchSocket command target

class CSearchSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CSearchSocket(CWnd *pParentWnd);
	virtual ~CSearchSocket();

// Overrides
public:
	CWnd * m_pParentWnd;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSearchSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SearchSocket_H__1F4A6A63_3A16_4112_8233_A15ADE4F5F1F__INCLUDED_)
