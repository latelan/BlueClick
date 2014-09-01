#if !defined(AFX_DLGSPLASH_H__8F53BBC8_D17E_4F0B_86EC_37740E763176__INCLUDED_)
#define AFX_DLGSPLASH_H__8F53BBC8_D17E_4F0B_86EC_37740E763176__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSplash.h : header file
//

#include "StdAfx.h"
#include "OnlineSocket.h"

#define AW_BLEND 0x00080000
#define AW_HIDE  0x00010000

DWORD _stdcall SplashInitProc(LPVOID lpParameter);
/////////////////////////////////////////////////////////////////////////////
// CDlgSplash dialog

class CDlgSplash : public CDialog
{
// Construction
public:
	int		m_width;
	int		m_height;
	
	CString m_csConfigFilename;
	CString m_csResListFilename;
	CString m_csServerAddr;
	UINT	m_nServerPort;
	CString m_csHostAddr;
	CString m_csHostMAC;
	UINT	m_nHostPort;
	
	CBrush	m_brushBg;

	HANDLE m_hThreadInit;
	COnlineSocket *m_udpSocket;

	void OnReceive();
	void Close();
	CDlgSplash(CWnd* pParent = NULL);   // standard constructor
	~CDlgSplash() {
		delete m_udpSocket;
	}

// Dialog Data
	//{{AFX_DATA(CDlgSplash)
	enum { IDD = IDD_DLGSPLASH_DIALOG };
	CStatic	m_staticSplashMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSplash)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPLASH_H__8F53BBC8_D17E_4F0B_86EC_37740E763176__INCLUDED_)
