// BlueClickDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BlueClickDlg.h"
#include "DlgSplash.h"
#include "DlgNewShare.h"
#include "DlgSystemSetting.h"
#include "DlgThemeSelecter.h"
#include "BuffreeMessageBox.h"
#include "FileMD5.h"
#include "Converter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	CBrush m_brushBg;
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CAnimateButton	m_btnOk;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg UINT OnNcHitTest(CPoint point);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CBlueClickDlg *mainWnd = (CBlueClickDlg*)AfxGetMainWnd();
	CString themePath = mainWnd->m_themePath;
	CString okBtnBmpPath = themePath + "btn-ok.bmp";
	
	CenterWindow();
	
	CRect rcRect;
	GetClientRect(&rcRect);
	m_btnOk.SetWindowPos(NULL, rcRect.Width()/2-30, rcRect.Height()-35, 60, 27, SWP_SHOWWINDOW);
	m_btnOk.LoadBitmap(okBtnBmpPath);
	
	CString bmpBgPath = themePath + _T("dlg-bg.bmp");
	HBITMAP hBmpBg = CBlueClickApp::LoadBmpFromFile(bmpBgPath);
	CBitmap bmpBg;
	bmpBg.Attach(hBmpBg);
	m_brushBg.CreatePatternBrush(&bmpBg);
	bmpBg.Detach();
	DeleteObject(hBmpBg);
	
	CFont font;
	font.CreatePointFont(120, "宋体");
	//	m_staticMsg.SetFont(&font);
	
	DWORD dwStyle = AW_BLEND;
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	typedef BOOL (WINAPI MYFUNC(HWND, DWORD, DWORD));
	MYFUNC* AnimateWindow;
	AnimateWindow = (MYFUNC*)::GetProcAddress(hInst, "AnimateWindow");
	AnimateWindow(this->m_hWnd, 500, dwStyle);
	FreeLibrary(hInst);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if((CTLCOLOR_STATIC==nCtlColor))
    {
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(255,255,255));
		
        return  m_brushBg;// (HBRUSH)::GetStockObject(NULL_BRUSH);
    }
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcRect;
	GetClientRect(&rcRect);
	pDC->FillRect(&rcRect, &m_brushBg);
	
	return TRUE;	
	//return CDialog::OnEraseBkgnd(pDC);
}

UINT CAboutDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ScreenToClient(&point);
	
	CRect rc;
	GetClientRect(&rc);
	if (rc.PtInRect(point)) {
		//UpdateData(FALSE);
		return HTCAPTION;
	} else {
		return CDialog::OnNcHitTest(point);
	}
}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	DWORD dwStyle = AW_BLEND;
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	typedef BOOL (WINAPI MYFUNC(HWND, DWORD, DWORD));
	MYFUNC* AnimateWindow;
	AnimateWindow = (MYFUNC*)::GetProcAddress(hInst, "AnimateWindow");
	AnimateWindow(this->m_hWnd, 750, AW_HIDE | dwStyle);
	FreeLibrary(hInst);		
	
	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CBlueClickDlg dialog

CBlueClickDlg::CBlueClickDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlueClickDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlueClickDlg)
	m_csKeyword = _T("");
	m_width = 780;
	m_height = 550;
	m_listItemHeight = 50;
	m_csServerAddr = "0.0.0.0";
	m_nServerPort = 5566;
	m_clientNum = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for (int i = 0; i < BUFFREE_MAX_SYN_NUM; i++) {
		m_downloadSocket[i] = NULL;
	}
}


void CBlueClickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlueClickDlg)
	DDX_Control(pDX, IDC_STATIC_LOGO, m_staticLogo);
	DDX_Control(pDX, IDC_STATIC_CAPTION, m_staticCaption);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_editSearch);
	DDX_Control(pDX, IDC_STATIC_TAB, m_staticListTab);
	DDX_Control(pDX, IDC_TREE_IDC_TREE_DOWNLOAD, m_treeDownload);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_BUTTON_UPLOAD_LIST_TAB, m_btnUploadListTab);
	DDX_Control(pDX, IDC_BUTTON_THEME, m_btnTheme);
	DDX_Control(pDX, IDC_BUTTON_RESOURCE_LIST_TAB, m_btnResourceListTab);
	DDX_Control(pDX, IDC_BUTTON_MIN, m_btnMin);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btnSysMenu);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOAD_LIST_TAB, m_btnDownloadListTab);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_csKeyword);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBlueClickDlg, CDialog)
	//{{AFX_MSG_MAP(CBlueClickDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_MIN, OnButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_MENU, OnButtonMenu)
	ON_BN_CLICKED(IDC_BUTTON_THEME, OnButtonTheme)
	ON_BN_CLICKED(IDC_BUTTON_RESOURCE_LIST_TAB, OnButtonResourceListTab)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_LIST_TAB, OnButtonDownloadListTab)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD_LIST_TAB, OnButtonUploadListTab)
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_COMMAND(ID_MENUITEM_SYSTEM_SETTING, OnMenuitemSystemSetting)
	ON_COMMAND(ID_MENUITEM_ABOUT_US, OnMenuitemAboutUs)
	ON_COMMAND(ID_MENUITEM_QUIT_PROG, OnMenuitemQuitProg)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlueClickDlg message handlers

BOOL CBlueClickDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//成员变量初始化
	CBlueClickApp::GetWorkSpacePath(m_csWorkSpace);
	m_csConfigFilename = m_csWorkSpace + "/Config.ini";
	m_csResListFilename = m_csWorkSpace + "/ResList.bc";
	m_themePath = m_csWorkSpace + "/resource/theme/";
	for (int i = 0; i < BUFFREE_MAX_SYN_NUM; i++) {
		m_hThreadDownload[i] = NULL;
		m_hThreadUpload[i] = NULL;
	}

	CDlgSplash dlgSplash(this);
	if (dlgSplash.DoModal() != IDOK) {
		CDialog::OnCancel();
	}

	//设置资源路径
	CString bgBmpPath = m_themePath + "bg.bmp";
	CString cancelBtnBmpPath = m_themePath + "close-btn.bmp";
	CString minBtnBmpPath = m_themePath + "min-btn.bmp";
	CString menuBtnBmpPath = m_themePath + "menu-btn.bmp";
	CString themeBtnBmpPath = m_themePath + "theme-btn.bmp";
	CString searchBtnBmpPath = m_themePath + "search-btn.bmp";
	CString resouceBtnBmpPath = m_themePath + "resource-list-btn.bmp";
	CString downloadBtnBmpPath = m_themePath + "download-list-btn.bmp";
	CString uploadBtnBmpPath = m_themePath + "upload-list-btn.bmp";
	CString insertBtnBmpPath = m_themePath + "insert-btn.bmp";
	//设置控件坐标位置	
	HDC hDC = ::GetDC(HWND(NULL));		// 得到屏幕DC  
	m_screenWidth = ::GetDeviceCaps(hDC,HORZRES); // 屏幕宽  
	m_screenHeight = ::GetDeviceCaps(hDC,VERTRES);	// 屏幕高   
	::ReleaseDC(HWND(NULL),hDC);		// 释放DC
	
	MoveWindow((m_screenWidth-m_width)/2, (m_screenHeight-m_height)/2, m_width, m_height, TRUE);
	
	m_staticCaption.SetWindowPos(NULL, 10, 8, 200, 29, SWP_SHOWWINDOW);
	m_staticLogo.SetWindowPos(NULL, 20, 25, 50, 50, SWP_SHOWWINDOW);
	m_btnCancel.SetWindowPos(NULL, CBlueClickDlg::m_width-45, 0, 45, 20, SWP_SHOWWINDOW);
	m_btnMin.SetWindowPos(NULL, CBlueClickDlg::m_width-80, 0, 35, 29, SWP_SHOWWINDOW);
	m_btnSysMenu.SetWindowPos(NULL, CBlueClickDlg::m_width-115, 0, 35, 29, SWP_SHOWWINDOW);
	m_btnTheme.SetWindowPos(NULL, CBlueClickDlg::m_width-150, 0, 35, 29, SWP_SHOWWINDOW);
	m_editSearch.SetWindowPos(NULL, CBlueClickDlg::m_width-150, 45, 120, 20, SWP_SHOWWINDOW);
	m_btnSearch.SetWindowPos(NULL, CBlueClickDlg::m_width-30, 45, 20, 20, SWP_SHOWWINDOW);
	m_staticListTab.SetWindowPos(NULL, 10, 80, CBlueClickDlg::m_width-20, this->m_height-110, SWP_SHOWWINDOW); 
	m_treeDownload.SetWindowPos(NULL, 10, 70, 0, this->m_height-80, SWP_SHOWWINDOW); 
	m_btnResourceListTab.SetWindowPos(NULL, 150, 36, 35, 29, SWP_SHOWWINDOW);
	m_btnDownloadListTab.SetWindowPos(NULL, 200, 36, 35, 29, SWP_SHOWWINDOW);
	m_btnUploadListTab.SetWindowPos(NULL, 250, 36, 35, 29, SWP_SHOWWINDOW);
//	m_btnInsert.SetWindowPos(NULL, 10, 20, 35, 29, SWP_SHOWWINDOW);

	//LIST TREE
//	m_treeDownload.SetBkMode( CBuffreeTreeCtrl::BK_MODE_FILL );

	//添加列表子窗口
	CWnd *pTabPage = GetDlgItem(IDC_STATIC_TAB);
	m_dlgResourceList.Create(IDD_DLGRESOURCELIST_DIALOG, pTabPage);
	m_dlgResourceList.ShowWindow(SW_SHOW);
	
	m_dlgDownloadList.Create(IDD_DLGDOWNLOADLIST_DIALOG, pTabPage);
	m_dlgDownloadList.ShowWindow(SW_HIDE);
	
	m_dlgUploadList.Create(IDD_DLGUPLOADLIST_DIALOG, pTabPage);
	m_dlgUploadList.ShowWindow(SW_HIDE);
	
	//加载主窗口背景主题
	CString bmpBgPath = m_themePath + _T("bg.bmp");
	HBITMAP hBmpBg = CBlueClickApp::LoadBmpFromFile(bmpBgPath);
	CBitmap bmpBg;
	bmpBg.Attach(hBmpBg);
	m_brushBg.CreatePatternBrush(&bmpBg);
	bmpBg.Detach();
	DeleteObject(hBmpBg);

	//加载控件主题资源
	m_btnCancel.LoadBitmap(cancelBtnBmpPath);
	m_btnMin.LoadBitmap(minBtnBmpPath);
	m_btnSysMenu.LoadBitmap(menuBtnBmpPath);
	m_btnTheme.LoadBitmap(themeBtnBmpPath);
	m_btnSearch.LoadBitmap(searchBtnBmpPath);
	m_btnResourceListTab.LoadBitmap(resouceBtnBmpPath);
	m_btnDownloadListTab.LoadBitmap(downloadBtnBmpPath);
	m_btnUploadListTab.LoadBitmap(uploadBtnBmpPath);
//	m_btnInsert.LoadBitmap(insertBtnBmpPath);
	UpdateData(FALSE);

	//初始化悬浮窗
	m_dlgSuspension = new CDlgSuspension();
	m_dlgSuspension->Create(IDD_DLGSUSPENSION_DIALOG,this);
	m_dlgSuspension->ShowWindow(SW_HIDE);

	m_dlgSuspension->OnUpdateTransparent(220);
/*
	int count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "rmvb");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "桃花侠大战菊花怪.rmvb");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 90);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "zip");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "你懂得.zip");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 50);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "exe");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "360傻瓜专用杀毒软件.exe");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 72);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "txt");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "【乌托邦】工作日程.txt");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 10);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "rmvb");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "桃花侠大战菊花怪.rmvb");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 90);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "zip");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "你懂得.zip");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 50);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "exe");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "360傻瓜专用杀毒软件.exe");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 72);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "txt");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "【乌托邦】工作日程.txt");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 10);

	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "rmvb");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "桃花侠大战菊花怪.rmvb");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 90);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "zip");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "你懂得.zip");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 50);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "exe");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "360傻瓜专用杀毒软件.exe");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 72);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "txt");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "【乌托邦】工作日程.txt");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "1035M");
	m_dlgResourceList.m_listResource.SetItemText(count, 4, "65A7CC070BEFAB5A6AE94A174BC8878B");
	m_dlgResourceList.m_listResource.SetItemData(count, 10);

	count = m_dlgUploadList.m_listUpload.GetItemCount();
	m_dlgUploadList.m_listUpload.InsertItem(count, "");
	m_dlgUploadList.m_listUpload.SetItemText(count, 1, "rmvb");
	m_dlgUploadList.m_listUpload.SetItemText(count, 2, "欢乐斗地主.rmvb");
	m_dlgUploadList.m_listUpload.SetItemText(count, 3, "20%");
	m_dlgUploadList.m_listUpload.SetItemData(count, 20);
*/
	m_listenSocket = new CListenSocket(this);
	
	if (m_listenSocket->Create(6666, SOCK_STREAM) == NULL) {
		CBuffreeMessageBox dlgMessageBox("错误001：网络初始化失败");
		dlgMessageBox.DoModal();

		return 0;
	}
	
	BOOL bRet = m_listenSocket->Listen();
	if (!bRet) {
		CBuffreeMessageBox dlgMessageBox("错误002：网络初始化失败");
		dlgMessageBox.DoModal();

		return 0;
	}

	m_hThreadSearch = CreateThread(NULL, 0, InitThreadProc, this, 0, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBlueClickDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBlueClickDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBlueClickDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CBlueClickDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcRect;
	GetClientRect(&rcRect);
	pDC->FillRect(&rcRect, &m_brushBg);
	
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

UINT CBlueClickDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ScreenToClient(&point);
	
	CRect rc;
	GetClientRect(&rc);
	if (rc.PtInRect(point)) {
		//UpdateData(FALSE);
		return HTCAPTION;
	} else {
		return CDialog::OnNcHitTest(point);
	}
}

BOOL CBlueClickDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN) {  
        if(pMsg->wParam == VK_ESCAPE) {  
            return true;  
        }

//		if(pMsg->wParam == VK_RETURN) {  
//            return true;  
//      }  
    }
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CBlueClickDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
//	this->ShowWindow(SW_HIDE);
	AnimateWindow(0);
	m_dlgSuspension->ShowWindow(SW_SHOW);
}

void CBlueClickDlg::OnButtonMin() 
{
	// TODO: Add your control notification handler code here
	AnimateWindow(0);
	ToTray();
}

LRESULT CBlueClickDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if(wParam!=IDR_MAINFRAME)
		return 1;
	switch(lParam) {
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
		{
			LPPOINT lpoint=new tagPOINT;
			::GetCursorPos(lpoint);//得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();//声明一个弹出式菜单
			menu.AppendMenu(MF_STRING,WM_DESTROY,"关闭"); //增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已隐藏），将程序结束。
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); //确定弹出式菜单的位置
			HMENU hmenu=menu.Detach();
			menu.DestroyMenu(); //资源回收
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK: //双击左键的处理
		{
//			this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿
			DeleteTray();
			AnimateWindow(1);
		}
		break;
	default:
		break;
	}
	return 0;
}

void CBlueClickDlg::ToTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	
	strcpy(nid.szTip,"蓝点下载器"); //信息提示条
	Shell_NotifyIcon(NIM_ADD,&nid); //在托盘区添加图标
//	ShowWindow(SW_HIDE); //隐藏主窗口
}

void CBlueClickDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK; //自定义的消息名称
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	
	strcpy(nid.szTip,"蓝点下载器"); //信息提示条为“计划任务提醒”
	Shell_NotifyIcon(NIM_DELETE,&nid); //在托盘区删除图标
}

void CBlueClickDlg::OnButtonMenu() 
{
	// TODO: Add your control notification handler code here
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU_SYSTEM);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint);
	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, myPoint.x, myPoint.y+10, this);		
}

void CBlueClickDlg::OnButtonTheme() 
{
	// TODO: Add your control notification handler code here
	CDlgThemeSelecter dlgThemeSelector;
	dlgThemeSelector.DoModal();
}

void CBlueClickDlg::OnButtonResourceListTab() 
{
	// TODO: Add your control notification handler code here
	m_dlgDownloadList.ShowWindow(SW_HIDE);
	m_dlgUploadList.ShowWindow(SW_HIDE);	
	m_dlgResourceList.ShowWindow(SW_SHOW);		
}

void CBlueClickDlg::OnButtonDownloadListTab() 
{
	// TODO: Add your control notification handler code here
	m_dlgResourceList.ShowWindow(SW_HIDE);
	m_dlgUploadList.ShowWindow(SW_HIDE);
	m_dlgDownloadList.ShowWindow(SW_SHOW);
}

void CBlueClickDlg::OnButtonUploadListTab() 
{
	// TODO: Add your control notification handler code here
	m_dlgResourceList.ShowWindow(SW_HIDE);
	m_dlgDownloadList.ShowWindow(SW_HIDE);
	m_dlgUploadList.ShowWindow(SW_SHOW);	
}

void CBlueClickDlg::OnMenuitemSystemSetting() 
{
	// TODO: Add your command handler code here
	CDlgSystemSetting dlgSysSetting;
	dlgSysSetting.DoModal();
}

void CBlueClickDlg::OnMenuitemAboutUs() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CBlueClickDlg::OnMenuitemQuitProg() 
{
	// TODO: Add your command handler code here
	AnimateWindow(0);
	CDialog::OnCancel();
}


void CBlueClickDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	if (m_hThreadSearch != NULL) {
		TerminateThread(m_hThreadSearch, 0);
	}

	UpdateData(TRUE);

	m_hThreadSearch = CreateThread(NULL, 0, SearchThreadProc, this, 0, NULL);
}

/*********************************************************
函数名称：StartDownload
功能描述：用户选定资源，触发下载事件。创建新线程。
作者：	  张永军
创建时间：2014-08-29
参数说明：nItem：选定资源在资源列表中的索引
返 回 值：无
*********************************************************/
void CBlueClickDlg::StartDownload(UINT nItem) 
{
	// TODO: Add your command handler code here
	
	CString fileMD5 = m_dlgResourceList.m_listResource.GetItemText(nItem, 0);
	CString fileExt = m_dlgResourceList.m_listResource.GetItemText(nItem, 1);
	CString fileName = m_dlgResourceList.m_listResource.GetItemText(nItem, 2);
	CString fileSize = m_dlgResourceList.m_listResource.GetItemText(nItem, 3);

	int count = m_dlgDownloadList.m_listDownload.GetItemCount();
	m_dlgDownloadList.m_listDownload.InsertItem(count, fileMD5);
	m_dlgDownloadList.m_listDownload.SetItemText(count, 1, fileExt);
	m_dlgDownloadList.m_listDownload.SetItemText(count, 2, fileName);
	m_dlgDownloadList.m_listDownload.SetItemText(count, 3, fileSize);
	m_dlgDownloadList.m_listDownload.SetItemData(count, 0);

	CBuffreeMessageBox dlgMessageBox("已加入下载列表");

	OnButtonDownloadListTab();

	dlgMessageBox.DoModal();

	STRUCT_THREAD_PARAMETER param;
	param.m_mainWnd = this;
	param.m_list = &(m_dlgDownloadList.m_listDownload);
	param.m_nItem = count;

	for (int i = 0; i < BUFFREE_MAX_SYN_NUM; i++) {
		if (m_hThreadDownload[i] == NULL) {
			m_dlgDownloadList.m_listDownload.SetItemText(count, 5, "dwonloading");
			param.m_nThreadIndex = i;
			m_hThreadDownload[i] = CreateThread(NULL, 0, DownloadThreadProc, &param, 0, NULL);
			break;
		}
	}

	if (i >= 5) {
		m_dlgDownloadList.m_listDownload.SetItemText(count, 5, "pause");
	}
}

void CBlueClickDlg::DeleteShare(UINT nItem)
{
	m_dlgUploadList.m_listUpload.DeleteItem(nItem);

	CFile fileResList(m_csResListFilename, CFile::modeWrite);
	fileResList.Seek(nItem, CFile::SeekPosition::begin);
	char buf[1] = {'\0'};
	fileResList.Write(buf, 1);
	fileResList.Close();

	CBuffreeMessageBox dlgMessageBox("已取消分享");
	dlgMessageBox.DoModal();
}

void CBlueClickDlg::ReceiveResourceList()
{
	char buf[BLUECLICK_MSG_BUF_LENGTH];
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	int nRet = m_searchSocket->Receive(buf, BLUECLICK_MSG_BUF_LENGTH);

	if (nRet <= 0) {
		return;
	}

	cJSON *pRoot;
	pRoot=cJSON_Parse(buf);

	if (!pRoot) {
		//AfxMessageBox("解析JSON失败");
		return;
	}

	CString msgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (msgType != "MsgOnlineResponse") {
		//AfxMessageBox("错误的信息类型");
		return;
	}

	m_csServerAddr = cJSON_GetObjectItem(pRoot, "ServerIP")->valuestring;
	cJSON_Delete(pRoot);

	CBuffreeMessageBox dlgMessageBox(m_csServerAddr);
	dlgMessageBox.DoModal();
}

/*********************************************************
函数名称：AcceptClient
功能描述：接收资源下载客户端的连接请求，如果当前列表中的连接数少于5， 并将新的连接加入客户列表中
作者：	  张永军
创建时间：2014-08-29
参数说明：无
返 回 值：无
*********************************************************/
void CBlueClickDlg::AcceptClient()
{
	for (int i = 0; i < BUFFREE_MAX_SYN_NUM; i++) {
		if (m_downloadSocket[m_clientNum++] == NULL) {
			m_downloadSocket[m_clientNum] = new CDownloadSocket(this);
			if (!m_listenSocket->Accept(*m_downloadSocket[m_clientNum])) {
			//	AfxMessageBox("客户端连接失败");
			} else {
			//	AfxMessageBox("客户端连接成功");
				return;
			}
		}
	}
}

/*********************************************************
函数名称：ReceiveDownloadRequest
功能描述：处理资源下载客户端的下载请求，并返回所请求的数据
作者：	  张永军
创建时间：2014-08-29
参数说明：downloadSocket：接收请求消息的SOCKET指针
返 回 值：无
*********************************************************/
void CBlueClickDlg::ReceiveDownloadRequest(CDownloadSocket *downloadSocket)
{
	char buf[BLUECLICK_MSG_BUF_LENGTH];

	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	int nRet = downloadSocket->Receive(buf, BLUECLICK_MSG_BUF_LENGTH);
	if (nRet <= 0) {
		return;
	}

	AfxMessageBox(buf);

	cJSON *pRoot;
	pRoot=cJSON_Parse(buf);
	
	if (!pRoot) {
		//AfxMessageBox("解析JSON失败");
		return;
	}
	
	CString msgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (msgType != "MsgDownloadRes") {
		CBuffreeMessageBox dlgMessageBox("错误的信息类型");
		dlgMessageBox.DoModal();

		return;
	}
	CString resMD5 = cJSON_GetObjectItem(pRoot, "ResMD5")->valuestring;
	cJSON_Delete(pRoot);

	CBuffreeMessageBox dlgMessageBox(resMD5);
	dlgMessageBox.DoModal();

	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType", "MsgDownloadResponse");   
	cJSON_AddStringToObject(pRoot,"ResMD5", "1C7D74B459AB47C0403BD27A2DEC77E2");
	cJSON_AddNumberToObject(pRoot, "ResSize", 122222);
	
	char *strJson = cJSON_Print(pRoot);
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	strcpy(buf, strJson);
	cJSON_Delete(pRoot);
	delete strJson;
	
	downloadSocket->Send(buf, BLUECLICK_MSG_BUF_LENGTH);	
}

/*********************************************************
函数名称：AddNewShare
功能描:   获取共享文件基本信息，添加共享列表，写入共享列表文件
作者：	  张永军
创建时间：2014-08-29
参数说明：无
返 回 值：无
*********************************************************/
void CBlueClickDlg::AddNewShare() 
{
	CDlgNewShare dlgNewShare;
	if (dlgNewShare.DoModal() != IDOK) {
		return;
	}

	CString csResName = dlgNewShare.m_csFilename;
	CString csResPath = dlgNewShare.m_csFilePath;
	CString csResTag = dlgNewShare.m_csFileTags;
	CString csResExt = csResName.Right(csResName.GetLength() - csResName.Find("."));

	CFileFind finder;
	BOOL bRet = finder.FindFile(csResPath);  
	if( !bRet ) {  
		CBuffreeMessageBox dlgMessageBox("文件不存在，请重新选择");
		dlgMessageBox.DoModal();
		
		return;
	}

	//上传列表：
	// 0：弃用，这里用来存储资源路径；
	// 1：文件后缀；
	// 2：文件名；
	// 3：文件大小
	// 4：进度条，字串无效，这里用来存储资源标签；
	// 5：文件MD5
	// data：进度条进度
	int count = m_dlgUploadList.m_listUpload.GetItemCount();
	m_dlgUploadList.m_listUpload.InsertItem(count, "");
	m_dlgUploadList.m_listUpload.SetItemText(count, 0, csResPath);
	m_dlgUploadList.m_listUpload.SetItemText(count, 1, csResExt);
	m_dlgUploadList.m_listUpload.SetItemText(count, 2, csResName);
	m_dlgUploadList.m_listUpload.SetItemText(count, 3, "");//文件大小字串，在线程中计算添加
	m_dlgUploadList.m_listUpload.SetItemText(count, 4, csResTag);
	m_dlgUploadList.m_listUpload.SetItemText(count, 5, "");//MD5: 由于计算大文件的MD5比较耗时，所以放在线程中计算并填写这个字段

	m_dlgUploadList.m_listUpload.SetItemData(count, 0);

//	CBuffreeMessageBox dlgMessageBox("已加入分享列表");
//	dlgMessageBox.DoModal();
	
	STRUCT_THREAD_PARAMETER param;
	param.m_mainWnd = this;
	param.m_list = &(m_dlgUploadList.m_listUpload);
	param.m_nItem = count;
	
	for (int i = 0; i < BUFFREE_MAX_SYN_NUM; i++) {
		if (m_hThreadUpload[i] == NULL) {
			param.m_nThreadIndex = i;
			m_hThreadUpload[i] = CreateThread(NULL, 0, UploadThreadProc, &param, 0, NULL);
			break;
		}
	}
}

/*********************************************************
函数名称：InitThreadProc
功能描:
作者：	  张永军
创建时间：2014-08-29
参数说明：lpParameter：主窗口指针
返 回 值：无
*********************************************************/
DWORD _stdcall InitThreadProc(LPVOID lpParameter) {
	CBlueClickDlg *pDlg = (CBlueClickDlg*)lpParameter;
	CBuffreeListCtrl *listResource = &(pDlg->m_dlgResourceList.m_listResource);
	CBuffreeListCtrl *listUpload = &(pDlg->m_dlgUploadList.m_listUpload);
	CString csKeyWord = pDlg->m_csKeyword;
	char buf[BLUECLICK_MSG_BUF_LENGTH];
	CSearchSocket searchSocket(pDlg);

	if (!AfxSocketInit())
	{
		return 0;
	}

//	pDlg->m_listenSocket = new CListenSocket(pDlg);

//	if (pDlg->m_listenSocket->Create(6667, SOCK_STREAM) == NULL) {
//		AfxMessageBox("网络初始化失败");
//		return 0;
//	}

//	BOOL bRet = pDlg->m_listenSocket->Listen();
//	if (!bRet) {
//		AfxMessageBox("绑定端口失败");
//		return 0;
//	}

	if (searchSocket.Create() == FALSE) {
		return 0;
	}

//	CString msg;
//	msg.Format("ip:%s, port:%d", pDlg->m_csServerAddr, pDlg->m_nServerPort);
//	AfxMessageBox(msg);
	if (!searchSocket.Connect(pDlg->m_csServerAddr, pDlg->m_nServerPort)) {
		CBuffreeMessageBox dlgMessageBox("网络连接失败，请重试");
		dlgMessageBox.DoModal();
	
		return 0;
	}
	
	cJSON *pRoot, *pResArray, *pRes;
	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType", "MsgGetPush");   
	cJSON_AddNumberToObject(pRoot,"NumWanted", 10);
	
	char *strJson = cJSON_Print(pRoot);
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	strcpy(buf, strJson);		
	cJSON_Delete(pRoot);
	delete strJson;
	
	searchSocket.Send(buf, BLUECLICK_MSG_BUF_LENGTH);
	
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	int nRet = searchSocket.Receive(buf, BLUECLICK_MSG_BUF_LENGTH);

	if (nRet <= 0) {
		return 0;
	}

	pRoot=cJSON_Parse(buf);
	
	if (!pRoot) {
		//AfxMessageBox("解析JSON失败");
		return 0;
	}

	CString msgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (msgType != "ResList") {
		CBuffreeMessageBox dlgMessageBox("错误的信息类型");
		dlgMessageBox.DoModal();

		return 0;
	}
	
	//正确返回搜索结果，关闭套接字
	searchSocket.Close();

	pResArray = cJSON_GetObjectItem(pRoot, "Resource");
	if (pResArray == NULL) {
		return 0;
	}
	UINT resCount = cJSON_GetObjectItem(pRoot, "ResCount")->valueint;//cJSON_GetArraySize(pResArray);

	for (UINT i = 0; i < resCount; i++) {
		
		pRes = cJSON_GetArrayItem(pResArray, i);
		if (pRes == NULL) {
			continue;
		}

		char *json = cJSON_Print(pRes);
		delete json;
		
		CString resName = cJSON_GetObjectItem(pRes, "ResName")->valuestring;
		CConverter::UTF8toANSI(resName);
		CString resExt = resName.Right(resName.GetLength()-resName.Find("."));
		CString resSize = cJSON_GetObjectItem(pRes, "ResSize")->valuestring;
		CString resMD5 = cJSON_GetObjectItem(pRes, "ResMD5")->valuestring;
		UINT resPiece= cJSON_GetObjectItem(pRes, "ResPieceCount")->valueint;

		int count = listResource->GetItemCount();
		listResource->InsertItem(count, "");
		listResource->SetItemText(count, 0, resMD5);
		listResource->SetItemText(count, 1, resExt);
		listResource->SetItemText(count, 2, resName);
		listResource->SetItemText(count, 3, resSize);
		listResource->SetItemText(count, 4, resMD5);
	}
	cJSON_Delete(pRoot);

	//上传列表：
	// 0：弃用，这里用来存储资源路径；
	// 1：文件后缀；
	// 2：文件名；
	// 3：文件大小
	// 4：进度条，字串无效，这里用来存储资源标签；
	// 5：文件MD5
	// data：进度条进度
	CFile file(pDlg->m_csResListFilename, CFile::modeRead);
	char status[BLUECLICK_MAX_SHARE_COUNT] = {'\0'};
	file.Read(status, BLUECLICK_MAX_SHARE_COUNT);

	STRUCT_SHARE_FILE_INFO fileInfo;
	for (i = 0; i < BLUECLICK_MAX_SHARE_COUNT; i++) {
		if (status[i] != '\0') {
			file.Read(&fileInfo, sizeof(STRUCT_SHARE_FILE_INFO));
			
			int count = listUpload->GetItemCount();
			listUpload->InsertItem(count, "");
			listUpload->SetItemText(count, 0, fileInfo.m_resPath);
			listUpload->SetItemText(count, 1, fileInfo.m_resExt);
			listUpload->SetItemText(count, 2, fileInfo.m_resName);
			listUpload->SetItemText(count, 3, fileInfo.m_resSize);
			listUpload->SetItemText(count, 4, fileInfo.m_resTag);
			listUpload->SetItemText(count, 5, fileInfo.m_resMD5);
			listUpload->SetItemData(count, 100);
		} else {
			file.Seek(sizeof(STRUCT_SHARE_FILE_INFO), CFile::SeekPosition::current);
		}
	}

	return 0;
}

/*********************************************************
函数名称：SearchThreadProc
功能描述：资源搜索线程，负责向服务端发出搜索请求，并处理返回数据
作者：	  张永军
创建时间：2014-08-29
参数说明：lpParameter：主窗口指针
返 回 值：无
*********************************************************/
DWORD _stdcall SearchThreadProc(LPVOID lpParameter) {
	CBlueClickDlg *pDlg = (CBlueClickDlg*)lpParameter;
	CBuffreeListCtrl *listResource = &(pDlg->m_dlgResourceList.m_listResource);
	CString csKeyWord = pDlg->m_csKeyword;
	char buf[BLUECLICK_MSG_BUF_LENGTH];
	CSearchSocket searchSocket(pDlg);

	if (!AfxSocketInit())
	{
		return 0;
	}

	if (searchSocket.Create() == FALSE) {
		return 0;
	}

	if (!searchSocket.Connect(pDlg->m_csServerAddr, pDlg->m_nServerPort)) {
		CBuffreeMessageBox dlgMessageBox("搜索失败，请重试");
		dlgMessageBox.DoModal();
		
		return 0;
	}
	
	CConverter::ANSItoUTF8(csKeyWord);

	cJSON *pRoot, *pResArray, *pRes;
	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType", "MsgQueryRes");   
	cJSON_AddStringToObject(pRoot,"QueryKey", csKeyWord.GetBuffer(0));

	char *strJson = cJSON_PrintUnformatted(pRoot);
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	strcpy(buf, strJson);
	cJSON_Delete(pRoot);
	delete strJson;

	searchSocket.Send(buf, BLUECLICK_MSG_BUF_LENGTH);

	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	int nRet = searchSocket.Receive(buf, BLUECLICK_MSG_BUF_LENGTH);
	
	searchSocket.Close();
	
	if (nRet <= 0) {
		return 0;
	}

	pRoot=cJSON_Parse(buf);
	
	if (!pRoot) {
		//AfxMessageBox("解析JSON失败");
		return 0;
	}
	
	CString msgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (msgType != "ResList") {
//		CBuffreeMessageBox dlgMessageBox("错误的信息类型");
//		dlgMessageBox.DoModal();

		return 0;
	}
	
	pResArray = cJSON_GetObjectItem(pRoot, "Resource");
	if (pResArray == NULL) {
		return 0;
	}
	
	listResource->DeleteAllItems();
	UINT resCount = cJSON_GetArraySize(pResArray);
	for (UINT i = 0; i < resCount; i++) {
		pRes = cJSON_GetArrayItem(pResArray, i);
		if (pRes == NULL) {
			continue;
		}

		CString resName = cJSON_GetObjectItem(pRes, "ResName")->valuestring;
		CConverter::UTF8toANSI(resName);
		CString resExt = resName.Right(resName.GetLength()-resName.Find("."));
		CString resSize = cJSON_GetObjectItem(pRes, "ResSize")->valuestring;
		CString resMD5 = cJSON_GetObjectItem(pRes, "ResMD5")->valuestring;
		CString resPiece = cJSON_GetObjectItem(pRes, "ResPieceCount")->valuestring;
		
		int count = listResource->GetItemCount();
		listResource->InsertItem(count, "");
		listResource->SetItemText(count, 0, resMD5);
		listResource->SetItemText(count, 1, resExt);
		listResource->SetItemText(count, 2, resName);
		listResource->SetItemText(count, 3, resSize);
		listResource->SetItemText(count, 4, resMD5);
	}
	cJSON_Delete(pRoot);

	return 0;
}

/*********************************************************
函数名称：DownloadThreadProc
功能描述：资源下载线程，负责向资源提供方发出请求，并处理返回数据
作者：	  张永军
创建时间：2014-08-29
参数说明：lpParameter：主窗口指针
返 回 值：无
*********************************************************/
DWORD _stdcall DownloadThreadProc(LPVOID lpParameter) {
	STRUCT_THREAD_PARAMETER *param = (STRUCT_THREAD_PARAMETER*)lpParameter;
	CBuffreeListCtrl *listDownload = param->m_list;
	UINT nItem = param->m_nItem;
	UINT nThreadIndex = param->m_nThreadIndex;
	CBlueClickDlg *pDlg = param->m_mainWnd;
	CDownloadSocket downloadSocket(pDlg);
	char buf[BLUECLICK_MSG_BUF_LENGTH];

	UINT nProgress = listDownload->GetItemData(nItem);
/*
	for (int i = nProgress; i <= 99; i++) {
		listDownload->SetItemData(nItem, i);
		Sleep(100);
	}
*/
	if (!AfxSocketInit()) {
		pDlg->m_hThreadDownload[nThreadIndex] = NULL;
		return 0;
	}
	
	if (downloadSocket.Create() == FALSE) {
		pDlg->m_hThreadDownload[nThreadIndex] = NULL;
		return 0;
	}

	if (!downloadSocket.Connect(pDlg->m_csServerAddr, pDlg->m_nServerPort)) {
		CBuffreeMessageBox dlgMessageBox("错误003：网络连接失败");
		dlgMessageBox.DoModal();
		pDlg->m_hThreadDownload[nThreadIndex] = NULL;
		return 0;
	}

	CBuffreeListCtrl *listResource = &(pDlg->m_dlgResourceList.m_listResource);
	CString fileMD5 = listResource->GetItemText(nItem, 4);

	cJSON *pRoot;
	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType", "MsgDownloadRes");   
	cJSON_AddStringToObject(pRoot,"ResMD5", fileMD5);
	
	char *strJson = cJSON_Print(pRoot);
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	strcpy(buf, strJson);		
	cJSON_Delete(pRoot);
	delete strJson;
	
	downloadSocket.Send(buf, BLUECLICK_MSG_BUF_LENGTH);
	
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	int nRet = downloadSocket.Receive(buf, BLUECLICK_MSG_BUF_LENGTH);
	
	if (nRet <= 0) {
		pDlg->m_hThreadDownload[nThreadIndex] = NULL;
		return 0;
	}
	
	pRoot=cJSON_Parse(buf);
	
	if (!pRoot) {
		//AfxMessageBox("解析JSON失败");
		pDlg->m_hThreadDownload[nThreadIndex] = NULL;
		return 0;
	}
	
	CString msgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (msgType != "MsgDownloadResponse") {
		CBuffreeMessageBox dlgMessageBox("错误的消息类型");
		dlgMessageBox.DoModal();
		pDlg->m_hThreadDownload[nThreadIndex] = NULL;
		return 0;
	}
	
	AfxMessageBox(msgType);
	
	cJSON_Delete(pRoot);
	
	pDlg->m_hThreadDownload[nThreadIndex] = NULL;
	return 0;
}

/*********************************************************
函数名称：UploadThreadProc
功能描述：资源上传线程，负责向服务端发送资源分享数据
作者：	  张永军
创建时间：2014-09-01
参数说明：lpParameter：资源相关信息结构体（资源在主窗口列表中所在的位置）
返 回 值：无
*********************************************************/
DWORD _stdcall UploadThreadProc(LPVOID lpParameter) {
	STRUCT_THREAD_PARAMETER *param = (STRUCT_THREAD_PARAMETER*)lpParameter;
	CBuffreeListCtrl *listUpload = param->m_list;
	UINT nItem = param->m_nItem;
	UINT nThreadIndex = param->m_nThreadIndex;
	CBlueClickDlg *pDlg = param->m_mainWnd;
	CDownloadSocket uploadSocket(pDlg);
	char buf[BLUECLICK_MSG_BUF_LENGTH];

	for (int i = 0; i < 30; i++) {
		listUpload->SetItemData(nItem, i);
		Sleep(10);
	}

	//上传列表：
	// 0：弃用，这里用来存储资源路径；
	// 1：文件后缀；
	// 2：文件名；
	// 3：文件大小
	// 4：进度条，字串无效，这里用来存储资源标签；
	// 5：文件MD5
	// data：进度条进度
	CString csResPath = listUpload->GetItemText(nItem, 0);
	CFile file(csResPath, CFile::modeRead);
	UINT nFileLength = file.GetLength();
	file.Close();

	CString csResName = listUpload->GetItemText(nItem, 2);
	CString csResExt = listUpload->GetItemText(nItem, 1);
	CString csResSize = CBlueClickApp::GetFileSizeStr(nFileLength);
	CString csResTag = listUpload->GetItemText(nItem, 4);
	CString csResMD5 = CFileMD5::GetFileMD5(csResPath);
	CString csResOwner = pDlg->m_csHostMAC;
	UINT nResPieceCount = (nFileLength % (1024*256) == 0) ? (nFileLength / 1024 / 256) : ((nFileLength / 1024 / 256) + 1);

	//之前没有设置分享列表项的以下两个字段，在这里补填
	listUpload->SetItemText(nItem, 3, csResSize);
	listUpload->SetItemText(nItem, 5, csResMD5);

	//编码转换
	csResTag.Replace("，", ",");
	csResTag.Replace(" ", ",");
	CConverter::ANSItoUTF8(csResName);
	CConverter::ANSItoUTF8(csResTag);

	cJSON *pRoot, *pRes;
	pRoot= cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType", "MsgShareRes"); 

	pRes = cJSON_CreateObject();
	cJSON_AddStringToObject(pRes, "ResName", csResName);
	cJSON_AddStringToObject(pRes, "ResTag", csResTag);
	cJSON_AddStringToObject(pRes, "ResSize", csResSize);
	cJSON_AddStringToObject(pRes, "ResMD5", csResMD5);
	cJSON_AddStringToObject(pRes, "ResOwner", csResOwner);
	cJSON_AddNumberToObject(pRes, "ResPieceCount", nResPieceCount);

	cJSON_AddItemToObject(pRoot, "Resource", pRes);

	char *strJson = cJSON_PrintUnformatted(pRoot);
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	strcpy(buf, strJson);
	cJSON_Delete(pRoot);
	delete strJson;

	if (!AfxSocketInit()) {
		pDlg->m_hThreadUpload[nThreadIndex] = NULL;
		return 0;
	}
	
	if (uploadSocket.Create() == FALSE) {
		pDlg->m_hThreadUpload[nThreadIndex] = NULL;
		return 0;
	}

	if (!uploadSocket.Connect(pDlg->m_csServerAddr, pDlg->m_nServerPort)) {
		CBuffreeMessageBox dlgMessageBox("错误003：网络连接失败");
		dlgMessageBox.DoModal();
		pDlg->m_hThreadUpload[nThreadIndex] = NULL;
		return 0;
	}
	
	uploadSocket.Send(buf, BLUECLICK_MSG_BUF_LENGTH);

	//上传列表：
	// 0：弃用，这里用来存储资源路径；
	// 1：文件后缀；
	// 2：文件名；
	// 3：文件大小
	// 4：进度条，字串无效，这里用来存储资源标签；
	// 5：文件MD5
	// data：进度条进度

	CConverter::UTF8toANSI(csResName);
	CConverter::UTF8toANSI(csResTag);

	STRUCT_SHARE_FILE_INFO fileInfo;
	strcpy(fileInfo.m_resPath, csResPath.GetBuffer(0));
	strcpy(fileInfo.m_resName, csResName.GetBuffer(0));
	strcpy(fileInfo.m_resExt, csResExt.GetBuffer(0));
	strcpy(fileInfo.m_resSize, csResSize.GetBuffer(0));
	strcpy(fileInfo.m_resTag, csResTag.GetBuffer(0));
	strcpy(fileInfo.m_resMD5, csResMD5.GetBuffer(0));

	//写入本地分享文件列表文件
	CFile fileResList(pDlg->m_csResListFilename, CFile::modeReadWrite);
	char status[BLUECLICK_MAX_SHARE_COUNT] = {'\0'};
	fileResList.Read(status, BLUECLICK_MAX_SHARE_COUNT);
	
	for (i = 0; i < BLUECLICK_MAX_SHARE_COUNT; i++) {
		if (status[i] == '\0') {
			fileResList.Seek(i * sizeof(STRUCT_SHARE_FILE_INFO), CFile::SeekPosition::current);
			fileResList.Write(&fileInfo, sizeof(STRUCT_SHARE_FILE_INFO));

			fileResList.Seek(i, CFile::SeekPosition::begin);
			fileResList.Write((void*)"1", 1);
			break;
		}
	}
	fileResList.Close();

	//更新分享进度条
	for (i = 30; i <= 100; i++) {
		listUpload->SetItemData(nItem, i);
		if (i < 85) {
			if (nFileLength >= BLUECLICK_GB_SIZE) {
				Sleep(50);
			} else if (nFileLength >= BLUECLICK_MB_SIZE) {
				Sleep(30);
			} else {
				Sleep(20);
			}
		} else {
			Sleep(10);
		}
	}

	/*
	memset(buf, 0, BLUECLICK_MSG_BUF_LENGTH);
	int nRet = uploadSocket.Receive(buf, BLUECLICK_MSG_BUF_LENGTH);
	
	if (nRet <= 0) {
		pDlg->m_hThreadUpload[nThreadIndex] = NULL;
		return 0;
	}
	
	pRoot=cJSON_Parse(buf);
	
	if (!pRoot) {
		//AfxMessageBox("解析JSON失败");
		pDlg->m_hThreadUpload[nThreadIndex] = NULL;
		return 0;
	}
	
	CString msgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (msgType != "MsgDownloadResponse") {
		CBuffreeMessageBox dlgMessageBox("错误的消息类型");
		dlgMessageBox.DoModal();
		pDlg->m_hThreadUpload[nThreadIndex] = NULL;
		return 0;
	}
	
	cJSON_Delete(pRoot);
	*/

	uploadSocket.Close();
	pDlg->m_hThreadUpload[nThreadIndex] = NULL;
	return 0;
}

/*********************************************************
函数名称：AnimateWindow
功能描述：创建窗口动画：主窗口打开或关闭时创建动画
作者：	  张永军
创建时间：2014-08-30
参数说明：flag：标识窗口打开(1)或者关闭(0)
返 回 值：无
*********************************************************/
void CBlueClickDlg::AnimateWindow(UINT flag)
{
	if (flag == 0) {
		CRect rcRect;

		GetClientRect(&rcRect);
		while (rcRect.Height() > 10) {
			GetClientRect(&rcRect);

			int width = rcRect.Width();
			int height = rcRect.Height() - 30;
			height = (height > 10) ? height : 10;
			int left = (m_screenWidth - width) / 2;
			int top = (m_screenHeight - height) / 2;
			MoveWindow(left, top, width, height, TRUE);

			Sleep(15);
		}
		Sleep(100);

		while (rcRect.Width() > 0 ) {
			GetClientRect(&rcRect);
			
			int width = rcRect.Width() - 50;
			int height = rcRect.Height();
			if (width < 0) {
				width = 0;
				height = 0;
			}
			int left = (m_screenWidth - width) / 2;
			int top = (m_screenHeight - height) / 2;
			MoveWindow(left, top, width, height, TRUE);

			Sleep(15);
		}
		ShowWindow(SW_HIDE);
	} else {
		CRect rcRect;

		ShowWindow(SW_SHOW);
		GetClientRect(&rcRect);
		while (rcRect.Width() < m_width ) {
			GetClientRect(&rcRect);
			
			int width = rcRect.Width() + 50;
			width = (width > m_width) ? m_width : width;
			int height = 10;
			int left = (m_screenWidth - width) / 2;
			int top = (m_screenHeight - height) / 2;
			MoveWindow(left, top, width, height, TRUE);
			
			Sleep(15);
		}

		Sleep(100);

		while (rcRect.Height() < m_height) {
			GetClientRect(&rcRect);
			
			int width = rcRect.Width();
			int height = rcRect.Height() + 30;
			height = (height > m_height) ? m_height : height;
			int left = (m_screenWidth - width) / 2;
			int top = (m_screenHeight - height) / 2;
			MoveWindow(left, top, width, height, TRUE);
			
			Sleep(15);
		}
	}

	//OnCancel();	
}