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
#include "SearchSocket.h"
#include "ListenSocket.h"
#include "DownloadSocket.h"
#include "DlgSuspension.h"
#include "BuffreeEdit.h"
#include "BlueClick.h"	// Added by ClassView

#define WM_SHOWTASK (WM_USER +1)

#define BLUECLICK_MAX_SYN_COUNT 5
#define BLUECLICK_MAX_SERVICE_COUNT 5

typedef struct {
	CWnd *m_mainWnd;
	CBuffreeListCtrl *m_listResource;
	CBuffreeListCtrl *m_listDownload;
	CBuffreeListCtrl *m_listUpload;
	UINT m_nResourceItem;
	UINT m_nDownloadItem;
	UINT m_nUploadItem;
	UINT m_nThreadIndex;
	UINT m_nPieceCount;
	char m_csResMD5[33];
} STRUCT_THREAD_PARAMETER;


DWORD _stdcall InitThreadProc(LPVOID lpParameter);
DWORD _stdcall SearchThreadProc(LPVOID lpParameter);
DWORD _stdcall DownloadThreadProc(LPVOID lpParameter);
DWORD _stdcall ServiceThreadProc(LPVOID lpParameter);
DWORD _stdcall UploadThreadProc(LPVOID lpParameter);
/////////////////////////////////////////////////////////////////////////////
// CBlueClickDlg dialog

class CBlueClickDlg : public CDialog
{
// Construction
public:
	HBITMAP m_hBmpLogo;
	void DeleteShare(UINT nItem);
	UINT	m_screenHeight;
	UINT	m_screenWidth;
	int		m_width;
	int		m_height;
	int		m_listItemHeight;

	CString m_csServerAddr;
	UINT	m_nServerPort;
	CString m_csHostAddr;
	CString m_csHostMAC;
	UINT	m_nHostPort;

	CString m_csWorkSpace;
	CString m_themePath;
	CString	m_csConfigFilename;
	CString m_csResListFilename;
	CBrush	m_brushBg;

	CDlgSuspension * m_dlgSuspension;	

	CSearchSocket		*m_searchSocket;
	CListenSocket		*m_listenSocket;
	CDownloadSocket		*m_downloadSocket[BLUECLICK_MAX_SYN_COUNT];

	UINT   m_clientNum;
	UINT   m_serviceNum;
	HANDLE m_hThreadSearch;
	HANDLE m_hThreadDownload[BLUECLICK_MAX_SYN_COUNT];
	HANDLE m_hThreadService[BLUECLICK_MAX_SERVICE_COUNT];
	HANDLE m_hThreadUpload[BLUECLICK_MAX_SYN_COUNT];
	STRUCT_THREAD_PARAMETER m_uploadInfo[BLUECLICK_MAX_SYN_COUNT];
	STRUCT_THREAD_PARAMETER m_downloadInfo[BLUECLICK_MAX_SYN_COUNT];

	CBlueClickDlg(CWnd* pParent = NULL);	// standard constructor
	void AnimateWindow(UINT flag);
	void ReceiveDownloadRequest(CDownloadSocket *downloadSocket);
	void ReceiveResourceList();
	void AcceptClient();
	void StartDownload(UINT nItem);
	void AddNewShare();
	void ToTray();
	void DeleteTray();

// Dialog Data
	//{{AFX_DATA(CBlueClickDlg)
	enum { IDD = IDD_BLUECLICK_DIALOG };
	CStatic		m_staticStatus;
	CStatic		m_staticPeerNumOnline;
	CStatic		m_staticLogo;
	CStatic		m_staticCaption;
	CString		m_csKeyword;
	CStatic		m_staticListTab;
	CTreeCtrl	m_treeDownload;
	CBuffreeEdit	m_editSearch;
	CAnimateButton	m_btnSearch;
	CAnimateButton	m_btnUploadListTab;
	CAnimateButton	m_btnTheme;
	CAnimateButton	m_btnResourceListTab;
	CAnimateButton	m_btnMin;
	CAnimateButton	m_btnSysMenu;
	CAnimateButton	m_btnDownloadListTab;
	CAnimateButton	m_btnCancel;
	CDlgUploadList		m_dlgUploadList;
	CDlgResourceList	m_dlgResourceList;
	CDlgDownloadList	m_dlgDownloadList;
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
	afx_msg void OnButtonSearch();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLUECLICKDLG_H__A10AEEC6_E3D9_489E_93F9_18E75F774088__INCLUDED_)
