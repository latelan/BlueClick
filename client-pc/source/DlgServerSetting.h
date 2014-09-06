#if !defined(AFX_DLGSERVERSETTING_H__750DE055_1EEE_4995_8B4E_98176D7144F6__INCLUDED_)
#define AFX_DLGSERVERSETTING_H__750DE055_1EEE_4995_8B4E_98176D7144F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgServerSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgServerSetting dialog

class CDlgServerSetting : public CDialog
{
// Construction
public:
	CString m_serverAddr;
	CDlgServerSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgServerSetting)
	enum { IDD = IDD_DLGSERVERSETTING_DIALOG };
	CIPAddressCtrl	m_ipAddressCtrl;
	UINT	m_serverPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgServerSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgServerSetting)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSERVERSETTING_H__750DE055_1EEE_4995_8B4E_98176D7144F6__INCLUDED_)
