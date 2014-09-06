#if !defined(AFX_DlgSuspension_H__34B2E147_B7BD_4F41_AA9D_6C6FC1EB51A5__INCLUDED_)
#define AFX_DlgSuspension_H__34B2E147_B7BD_4F41_AA9D_6C6FC1EB51A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSuspension.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSuspension dialog

class CDlgSuspension : public CDialog
{
// Construction
public:
	CDlgSuspension(CWnd* pParent = NULL);   // standard constructor
	void OnUpdateTransparent(int iTransparent);
// Dialog Data
	//{{AFX_DATA(CDlgSuspension)
	enum { IDD = IDD_DLGSUSPENSION_DIALOG };
	CStatic	m_Logo;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSuspension)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSuspension)
	virtual BOOL OnInitDialog();
	afx_msg UINT OnNcHitTest(CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnExit();
	afx_msg void OnShow();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnNcLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DlgSuspension_H__34B2E147_B7BD_4F41_AA9D_6C6FC1EB51A5__INCLUDED_)
