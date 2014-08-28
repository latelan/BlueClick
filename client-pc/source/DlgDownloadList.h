#if !defined(AFX_DLGDOWNLOADLIST_H__206C9EFD_881B_4C92_B537_F7DC58A36E7B__INCLUDED_)
#define AFX_DLGDOWNLOADLIST_H__206C9EFD_881B_4C92_B537_F7DC58A36E7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDownloadList.h : header file
//
#include "BuffreeListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDownloadList dialog

class CDlgDownloadList : public CDialog
{
// Construction
public:
	CDlgDownloadList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDownloadList)
	enum { IDD = IDD_DLGDOWNLOADLIST_DIALOG };
	CBuffreeListCtrl	m_listDownload;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDownloadList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDownloadList)
	virtual BOOL OnInitDialog();
	afx_msg void OnMenuitemContinueDownload();
	afx_msg void OnMenuitemPauseDownload();
	afx_msg void OnMenuitemDeleteDownload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDOWNLOADLIST_H__206C9EFD_881B_4C92_B537_F7DC58A36E7B__INCLUDED_)
