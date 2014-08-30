#if !defined(AFX_BUFFREELISTCTRL_H__1250FD7F_F6EA_4F8D_84D4_E119092AC088__INCLUDED_)
#define AFX_BUFFREELISTCTRL_H__1250FD7F_F6EA_4F8D_84D4_E119092AC088__INCLUDED_

#include "BuffreeHeaderCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuffreeListCtrl.h : header file
//
#define LVS_EX_DOUBLEBUFFER 0x00010000
#define BUFFREE_MAX_COLUMN 256
#define BUFFREE_COLUMN_NORMAL 0
#define BUFFREE_COLUMN_PROGRESS 1
#define BUFFREE_COLUMN_ICON 2
#define BUFFREE_INVALID_MENUID -1

typedef struct {
	int m_subItem;
	int m_type;
} BUFFREE_COLUMN;

/////////////////////////////////////////////////////////////////////////////
// CBuffreeListCtrl window

class CBuffreeListCtrl : public CListCtrl
{
// Construction
public:
	CBuffreeListCtrl();

// Attributes
public:	
	int m_columnCount;
	int m_iItemHeight;
	BOOL m_bStriped;
	int m_columnType[BUFFREE_MAX_COLUMN];
	int m_crProgressBg;
	int m_crProgressText;
	int m_crProgress;
	int m_crSelectedSingleBg;
	int m_crSelectedDoubleBg;
	int m_crNormalSingleBg;
	int m_crNormalDoubleBg;
	int m_crSelectedSingleText;
	int m_crSelectedDoubleText;
	int m_crNormalSingleText;
	int m_crNormalDoubleText;
	CBuffreeHeaderCtrl m_listHeader;
	CString m_typeSet;
	
// Operations
public:
void DrawText(int nItem, int nSubItem, CDC *pDC, COLORREF crText, COLORREF crBkgnd);
void OnCustomDraw(NMHDR *pNMHDR, LRESULT *pResult);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuffreeListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetRightMenuID(int menuID);
	int m_rightClickMenuID;
	void SetColumnType(int subItem, int type);
	void SetItemHeight(int height);
	virtual ~CBuffreeListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBuffreeListCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFREELISTCTRL_H__1250FD7F_F6EA_4F8D_84D4_E119092AC088__INCLUDED_)
