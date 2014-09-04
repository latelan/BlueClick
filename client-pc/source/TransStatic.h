#if !defined(AFX_TRANSSTATIC_H__F1E58D5C_A09D_43C4_B054_C333D6EF9B4D__INCLUDED_)
#define AFX_TRANSSTATIC_H__F1E58D5C_A09D_43C4_B054_C333D6EF9B4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransStatic window

class CTransStatic : public CStatic
{
// Construction
public:
	CTransStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF m_iTextColor;
	virtual ~CTransStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransStatic)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSSTATIC_H__F1E58D5C_A09D_43C4_B054_C333D6EF9B4D__INCLUDED_)
