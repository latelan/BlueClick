#if !defined(AFX_BUFFREEHEADERCTRL_H__8D83AC70_906C_40EE_A1BB_8B565609B07D__INCLUDED_)
#define AFX_BUFFREEHEADERCTRL_H__8D83AC70_906C_40EE_A1BB_8B565609B07D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuffreeHeaderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuffreeHeaderCtrl window

class CBuffreeHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	CBuffreeHeaderCtrl();

// Attributes
public:
	HBITMAP m_bmpHeaderList;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuffreeHeaderCtrl)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	CFont m_textFont;
	int m_spColor;
	int m_textColor;
	int m_bgColor;
	int m_height;
	int m_colNormalText;
	CFont m_themeFont;
	virtual ~CBuffreeHeaderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBuffreeHeaderCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnLayout(WPARAM wParam, LPARAM lParam);

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFREEHEADERCTRL_H__8D83AC70_906C_40EE_A1BB_8B565609B07D__INCLUDED_)
