#if !defined(AFX_DLGRESOURCELIST_H__4617941B_E7C5_4F30_A9FE_2F1E69090952__INCLUDED_)
#define AFX_DLGRESOURCELIST_H__4617941B_E7C5_4F30_A9FE_2F1E69090952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgResourceList.h : header file
//
#include "BuffreeListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgResourceList dialog

class CDlgResourceList : public CDialog
{
// Construction
public:
	CDlgResourceList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgResourceList)
	enum { IDD = IDD_DLGRESOURCELIST_DIALOG };
	CBuffreeListCtrl	m_listResource;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgResourceList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgResourceList)
	virtual BOOL OnInitDialog();
	afx_msg void OnMenuitemStartDownload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRESOURCELIST_H__4617941B_E7C5_4F30_A9FE_2F1E69090952__INCLUDED_)
