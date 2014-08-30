#if !defined(AFX_DLGSYSTEMSETTING_H__F50EA792_BA9E_4A0D_BAE2_28575359C281__INCLUDED_)
#define AFX_DLGSYSTEMSETTING_H__F50EA792_BA9E_4A0D_BAE2_28575359C281__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSystemSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSystemSetting dialog

class CDlgSystemSetting : public CDialog
{
// Construction
public:
	CDlgSystemSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSystemSetting)
	enum { IDD = IDD_DLGSYSTEMSETTING_DIALOG };
	CIPAddressCtrl	m_ipAddressCtrl;
	UINT	m_serverPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSystemSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSystemSetting)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSYSTEMSETTING_H__F50EA792_BA9E_4A0D_BAE2_28575359C281__INCLUDED_)
