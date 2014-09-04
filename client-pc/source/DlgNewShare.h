#if !defined(AFX_DLGNEWSHARE_H__E3A3DEA9_B4BB_440F_947A_7C87DD048148__INCLUDED_)
#define AFX_DLGNEWSHARE_H__E3A3DEA9_B4BB_440F_947A_7C87DD048148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewShare.h : header file
//

#include "AnimateButton.h"
#include "BuffreeEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgNewShare dialog

class CDlgNewShare : public CDialog
{
// Construction
public:
	CBrush m_brushBg;
	CDlgNewShare(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewShare)
	enum { IDD = IDD_DLGNEWSHARE_DIALOG };
	CBuffreeEdit	m_editFileName;
	CBuffreeEdit	m_editFileTags;
	CBuffreeEdit	m_editFilePath;
	CAnimateButton	m_btnOk;
	CAnimateButton	m_btnCancel;
	CAnimateButton	m_btnScan;
	CString	m_csFilename;
	CString	m_csFilePath;
	CString	m_csFileTags;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewShare)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewShare)
	afx_msg void OnButtonScan();
	afx_msg UINT OnNcHitTest(CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWSHARE_H__E3A3DEA9_B4BB_440F_947A_7C87DD048148__INCLUDED_)
