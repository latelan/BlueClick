#if !defined(AFX_BUFFREEEDIT_H__FE321BB2_7469_4B02_8056_90FC6E1FCAA5__INCLUDED_)
#define AFX_BUFFREEEDIT_H__FE321BB2_7469_4B02_8056_90FC6E1FCAA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuffreeEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuffreeEdit window

class CBuffreeEdit : public CEdit
{
// Construction
public:
	CBuffreeEdit();

// Attributes
public:
	CRect m_rectNCBottom;
	CRect m_rectNCTop;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuffreeEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBuffreeEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBuffreeEdit)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFREEEDIT_H__FE321BB2_7469_4B02_8056_90FC6E1FCAA5__INCLUDED_)
