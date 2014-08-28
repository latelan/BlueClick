// BlueClickDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BlueClickDlg.h"
#include "DlgSplash.h"

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

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlueClickDlg dialog

CBlueClickDlg::CBlueClickDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlueClickDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlueClickDlg)
	m_width = 780;
	m_height = 550;
	m_listItemHeight = 50;
	m_clientConnectNum = 0;
	m_ServerIP = "192.168.0.115";
	m_ServerPort = 7788;
	m_themePath = "./resource/theme/";
	m_csKeyword = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlueClickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlueClickDlg)
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_editSearch);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_STATIC_TAB, m_staticListTab);
	DDX_Control(pDX, IDC_TREE_IDC_TREE_DOWNLOAD, m_treeDownload);
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
	int x = ::GetDeviceCaps(hDC,HORZRES); // 屏幕宽  
	int y = ::GetDeviceCaps(hDC,VERTRES);	// 屏幕高   
	::ReleaseDC(HWND(NULL),hDC);		// 释放DC
	
	MoveWindow((x-m_width)/2, (y-m_height)/2, m_width, m_height, TRUE);
	
	m_btnCancel.SetWindowPos(NULL, CBlueClickDlg::m_width-45, 0, 45, 29, SWP_SHOWWINDOW);
	m_btnMin.SetWindowPos(NULL, CBlueClickDlg::m_width-80, 0, 35, 29, SWP_SHOWWINDOW);
	m_btnSysMenu.SetWindowPos(NULL, CBlueClickDlg::m_width-115, 0, 35, 29, SWP_SHOWWINDOW);
	m_btnTheme.SetWindowPos(NULL, CBlueClickDlg::m_width-150, 0, 35, 29, SWP_SHOWWINDOW);
	m_editSearch.SetWindowPos(NULL, CBlueClickDlg::m_width-150, 45, 120, 20, SWP_SHOWWINDOW);
	m_btnSearch.SetWindowPos(NULL, CBlueClickDlg::m_width-30, 45, 20, 20, SWP_SHOWWINDOW);
	m_staticListTab.SetWindowPos(NULL, 150, 70, CBlueClickDlg::m_width-160, this->m_height-80, SWP_SHOWWINDOW); 
	m_treeDownload.SetWindowPos(NULL, 10, 70, 130, this->m_height-80, SWP_SHOWWINDOW); 
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

	int count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "rmvb");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "桃花侠大战菊花怪.rmvb");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "2014-08-25");
	m_dlgResourceList.m_listResource.SetItemData(count, 90);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "zip");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "你懂得.zip");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "2014-08-25");
	m_dlgResourceList.m_listResource.SetItemData(count, 50);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "exe");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "360傻瓜专用杀毒软件.exe");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "2014-08-25");
	m_dlgResourceList.m_listResource.SetItemData(count, 72);
	
	count = m_dlgResourceList.m_listResource.GetItemCount();
	m_dlgResourceList.m_listResource.InsertItem(count, "");
	m_dlgResourceList.m_listResource.SetItemText(count, 1, "txt");
	m_dlgResourceList.m_listResource.SetItemText(count, 2, "【乌托邦】工作日程.txt");
	m_dlgResourceList.m_listResource.SetItemText(count, 3, "2014-08-25");
	m_dlgResourceList.m_listResource.SetItemData(count, 10);
	
	count = m_dlgDownloadList.m_listDownload.GetItemCount();
	m_dlgDownloadList.m_listDownload.InsertItem(count, "");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 1, "rmvb");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 2, "桃花侠大战菊花怪.rmvb");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 3, "90%");
	m_dlgDownloadList.m_listDownload.SetItemData(count, 90);
	
	count = m_dlgDownloadList.m_listDownload.GetItemCount();
	m_dlgDownloadList.m_listDownload.InsertItem(count, "");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 1, "film");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 2, "桃花侠大战菊花怪.rmvb");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 3, "50%");
	m_dlgDownloadList.m_listDownload.SetItemData(count, 50);
	
	count = m_dlgDownloadList.m_listDownload.GetItemCount();
	m_dlgDownloadList.m_listDownload.InsertItem(count, "");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 1, "film");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 2, "桃花侠大战菊花怪.rmvb");
	m_dlgDownloadList.m_listDownload.SetItemText(count, 3, "50%");
	m_dlgDownloadList.m_listDownload.SetItemData(count, 50);
	
	count = m_dlgUploadList.m_listUpload.GetItemCount();
	m_dlgUploadList.m_listUpload.InsertItem(count, "");
	m_dlgUploadList.m_listUpload.SetItemText(count, 1, "rmvb");
	m_dlgUploadList.m_listUpload.SetItemText(count, 2, "欢乐斗地主.rmvb");
	m_dlgUploadList.m_listUpload.SetItemText(count, 3, "20%");
	m_dlgUploadList.m_listUpload.SetItemData(count, 20);

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

void CBlueClickDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();	
}

void CBlueClickDlg::OnButtonMin() 
{
	// TODO: Add your control notification handler code here
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
			this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿
			DeleteTray();
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
	ShowWindow(SW_HIDE); //隐藏主窗口
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

BOOL CBlueClickDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN) {  
        if(pMsg->wParam == VK_ESCAPE) {  
            return true;  
        }
		if(pMsg->wParam == VK_RETURN) {  
            return true;  
        }  
    }		
	return CDialog::PreTranslateMessage(pMsg);
}

void CBlueClickDlg::Accept()
{

}

void CBlueClickDlg::OnMenuitemSystemSetting() 
{
	// TODO: Add your command handler code here
	
}

void CBlueClickDlg::OnMenuitemAboutUs() 
{
	// TODO: Add your command handler code here
	
}

void CBlueClickDlg::OnMenuitemQuitProg() 
{
	// TODO: Add your command handler code here
	CDialog::OnOK();
}
