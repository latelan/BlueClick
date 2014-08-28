#if !defined(AFX_BUFFREEMESSAGEBOX_H__EEE21FBC_98E9_42D6_9953_EB82328298C0__INCLUDED_)
#define AFX_BUFFREEMESSAGEBOX_H__EEE21FBC_98E9_42D6_9953_EB82328298C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuffreeMessageBox.h : header file
//
#include "AnimateButton.h"
/////////////////////////////////////////////////////////////////////////////
// CBuffreeMessageBox dialog

class CBuffreeMessageBox : public CDialog
{
// Construction
public:
	CBuffreeMessageBox(CString csMsg, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBuffreeMessageBox)
	enum { IDD = IDD_BUFFREEMESSAGEBOX_DIALOG };
	CStatic	m_staticMsg;
	CAnimateButton	m_btnOk;
	CString	m_csMsg;
	CBrush	m_brushBg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuffreeMessageBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuffreeMessageBox)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFREEMESSAGEBOX_H__EEE21FBC_98E9_42D6_9953_EB82328298C0__INCLUDED_)
