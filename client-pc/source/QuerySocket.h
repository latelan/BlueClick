#if !defined(AFX_QUERYSOCKET_H__A03DAF92_BB89_441F_AFA0_0245769F1A63__INCLUDED_)
#define AFX_QUERYSOCKET_H__A03DAF92_BB89_441F_AFA0_0245769F1A63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuerySocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuerySocket command target

class CQuerySocket : public CSocket
{
// Attributes
public:
	CWnd	*m_pParentWnd;
	UINT	m_nSocketIndex;
	CString m_csResName;
	CString m_csResMD5;
	UINT	m_nResPieceCount;
	UINT	m_nListItem;
// Operations
public:
	CQuerySocket(CWnd *pParentWnd, UINT nSocketIndex, CString csResName, CString csResMD5, UINT nResPieceCount, UINT nListItem);
	virtual ~CQuerySocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuerySocket)
	public:
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CQuerySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYSOCKET_H__A03DAF92_BB89_441F_AFA0_0245769F1A63__INCLUDED_)
