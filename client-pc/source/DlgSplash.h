#if !defined(AFX_DLGSPLASH_H__8F53BBC8_D17E_4F0B_86EC_37740E763176__INCLUDED_)
#define AFX_DLGSPLASH_H__8F53BBC8_D17E_4F0B_86EC_37740E763176__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSplash.h : header file
//
#include "UdpSocket.h"

#define AW_BLEND 0x00080000
#define AW_HIDE  0x00010000
/////////////////////////////////////////////////////////////////////////////
// CDlgSplash dialog

class CDlgSplash : public CDialog
{
// Construction
public:
	void OnReceive();
	CDlgSplash(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	int m_width;
	int m_height;
	int m_timeQuery;
	CBrush m_brushBg;
	CUdpSocket* m_udpSocket;


	//{{AFX_DATA(CDlgSplash)
	enum { IDD = IDD_DLGSPLASH_DIALOG };
	CStatic	m_staticSplashMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSplash)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPLASH_H__8F53BBC8_D17E_4F0B_86EC_37740E763176__INCLUDED_)
