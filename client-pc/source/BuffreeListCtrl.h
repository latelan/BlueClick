#if !defined(AFX_BUFFREELISTCTRL_H__1250FD7F_F6EA_4F8D_84D4_E119092AC088__INCLUDED_)
#define AFX_BUFFREELISTCTRL_H__1250FD7F_F6EA_4F8D_84D4_E119092AC088__INCLUDED_

#include "BuffreeHeaderCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuffreeListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuffreeListCtrl window

class CBuffreeListCtrl : public CListCtrl
{
// Construction
public:
	CBuffreeListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuffreeListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	CBuffreeHeaderCtrl m_listHeader;
	virtual ~CBuffreeListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBuffreeListCtrl)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFREELISTCTRL_H__1250FD7F_F6EA_4F8D_84D4_E119092AC088__INCLUDED_)
