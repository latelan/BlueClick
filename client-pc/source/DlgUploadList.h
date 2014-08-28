#if !defined(AFX_DLGUPLOADLIST_H__F10D0C9C_4250_490E_831E_08FAAEFD4DAF__INCLUDED_)
#define AFX_DLGUPLOADLIST_H__F10D0C9C_4250_490E_831E_08FAAEFD4DAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUploadList.h : header file
//
#include "BuffreeListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgUploadList dialog

class CDlgUploadList : public CDialog
{
// Construction
public:
	CDlgUploadList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUploadList)
	enum { IDD = IDD_DLGUPLOADLIST_DIALOG };
	CBuffreeListCtrl	m_listUpload;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUploadList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUploadList)
	virtual BOOL OnInitDialog();
	afx_msg void OnMenuitemNewShare();
	afx_msg void OnMenuitemDeleteShare();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPLOADLIST_H__F10D0C9C_4250_490E_831E_08FAAEFD4DAF__INCLUDED_)
