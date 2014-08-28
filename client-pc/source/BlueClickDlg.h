// BlueClickDlg.h : header file
//

#if !defined(AFX_BLUECLICKDLG_H__A10AEEC6_E3D9_489E_93F9_18E75F774088__INCLUDED_)
#define AFX_BLUECLICKDLG_H__A10AEEC6_E3D9_489E_93F9_18E75F774088__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AnimateButton.h"
#include "BuffreeListCtrl.h"
#include "BuffreeTreeCtrl.h"
#include "DlgDownloadList.h"	// Added by ClassView
#include "DlgResourceList.h"	// Added by ClassView
#include "DlgUploadList.h"	// Added by ClassView
#include "IndexSocket.h"
#include "ListenSocket.h"
#include "DownloadSocket.h"

#define WM_SHOWTASK (WM_USER +1)
#define BUFFREE_MAX_CLIENT_NUM 5 //客户端支持的最大连接数

/////////////////////////////////////////////////////////////////////////////
// CBlueClickDlg dialog

class CBlueClickDlg : public CDialog
{
// Construction
public:
	void Accept();
	CIndexSocket		*m_indexSocket;
	CListenSocket		*m_listenSocket;
	CDownloadSocket		*m_downloadSocket[BUFFREE_MAX_CLIENT_NUM];
	CDlgUploadList m_dlgUploadList;
	CDlgResourceList m_dlgResourceList;
	CDlgDownloadList m_dlgDownloadList;
	CBrush m_brushBg;
	CBlueClickDlg(CWnd* pParent = NULL);	// standard constructor
	void ToTray();
	void DeleteTray();

// Dialog Data
	int m_width;
	int m_height;
	int m_listItemHeight;
	int m_clientConnectNum;
	CString m_ServerIP;
	int m_ServerPort;
	CString m_themePath;
	//{{AFX_DATA(CBlueClickDlg)
	enum { IDD = IDD_BLUECLICK_DIALOG };
	CEdit	m_editSearch;
	CStatic	m_staticListTab;
	CTreeCtrl	m_treeDownload;
	CAnimateButton	m_btnSearch;
	CAnimateButton	m_btnUploadListTab;
	CAnimateButton	m_btnTheme;
	CAnimateButton	m_btnResourceListTab;
	CAnimateButton	m_btnMin;
	CAnimateButton	m_btnSysMenu;
	CAnimateButton	m_btnDownloadListTab;
	CAnimateButton	m_btnCancel;
	CString	m_csKeyword;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlueClickDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBlueClickDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonMin();
	afx_msg void OnButtonMenu();
	afx_msg void OnButtonTheme();
	afx_msg void OnButtonResourceListTab();
	afx_msg void OnButtonDownloadListTab();
	afx_msg void OnButtonUploadListTab();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg void OnMenuitemSystemSetting();
	afx_msg void OnMenuitemAboutUs();
	afx_msg void OnMenuitemQuitProg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLUECLICKDLG_H__A10AEEC6_E3D9_489E_93F9_18E75F774088__INCLUDED_)
