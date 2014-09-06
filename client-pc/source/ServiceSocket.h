#if !defined(AFX_SERVICESOCKET_H__F2280558_CE65_403B_8D54_766CDE228AF1__INCLUDED_)
#define AFX_SERVICESOCKET_H__F2280558_CE65_403B_8D54_766CDE228AF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiceSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServiceSocket command target

class CServiceSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CServiceSocket();
	virtual ~CServiceSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceSocket)
	public:
	virtual void OnReceive(int nErrorCode);
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

#endif // !defined(AFX_SERVICESOCKET_H__F2280558_CE65_403B_8D54_766CDE228AF1__INCLUDED_)
