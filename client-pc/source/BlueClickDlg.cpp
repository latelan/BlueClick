// BlueClickDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BlueClickDlg.h"


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

int CBlueClickDlg::m_width = 780;
int CBlueClickDlg::m_height = 550;

CBlueClickDlg::CBlueClickDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlueClickDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlueClickDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_listItemHeight = 30;
}

void CBlueClickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlueClickDlg)
	DDX_Control(pDX, IDC_TREE_DOWNLOAD, m_treeDownload);
	DDX_Control(pDX, IDC_LIST_RESOURCE, m_listResource);
	DDX_Control(pDX, IDC_THEME_BUTTON, m_btnTheme);
	DDX_Control(pDX, IDC_CANCEL_BUTTON, m_btnCancel);
	DDX_Control(pDX, IDC_MIN_BUTTON, m_btnMin);
	DDX_Control(pDX, IDC_MENU_BUTTON, m_btnMenu);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBlueClickDlg, CDialog)
	//{{AFX_MSG_MAP(CBlueClickDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_MESSAGE(WM_MEASUREITEM, OnMeasureItem)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnInsert)
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, OnCancel)
	ON_BN_CLICKED(IDC_MIN_BUTTON, OnMin)
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

	//设置资源路径
	CString cancelBtnBmpPath = "./resource/theme/close-btn.bmp";
	CString minBtnBmpPath = "./resource/theme/min-btn.bmp";
	CString menuBtnBmpPath = "./resource/theme/menu-btn.bmp";
	CString themeBtnBmpPath = "./resource/theme/theme-btn.bmp";
	CString headListBmpPath = "./resource/theme/list-header.bmp";
	//设置控件坐标位置
	MoveWindow(100, 100, CBlueClickDlg::m_width, CBlueClickDlg::m_height, TRUE);

	m_btnCancel.SetWindowPos(NULL, CBlueClickDlg::m_width-45, 0, 45, 29, SWP_SHOWWINDOW);
	m_btnMin.SetWindowPos(NULL, CBlueClickDlg::m_width-80, 0, 35, 29, SWP_SHOWWINDOW);
	m_btnMenu.SetWindowPos(NULL, CBlueClickDlg::m_width-115, 0, 35, 29, SWP_SHOWWINDOW);
	m_btnTheme.SetWindowPos(NULL, CBlueClickDlg::m_width-150, 0, 35, 29, SWP_SHOWWINDOW);
	m_listResource.SetWindowPos(NULL, 150, 70, CBlueClickDlg::m_width-160, this->m_height-80, SWP_SHOWWINDOW); 
	m_treeDownload.SetWindowPos(NULL, 10, 70, 130, this->m_height-80, SWP_SHOWWINDOW); 

	//设置资源列表视图
	CRect rcRect;
	m_listResource.GetClientRect(&rcRect);
	int width = rcRect.Width();
	m_listResource.InsertColumn(0, "类型", LVCFMT_LEFT, 130, 0);
	m_listResource.InsertColumn(1, "文件名", LVCFMT_LEFT, 130, 1);
	m_listResource.InsertColumn(2, "进度", LVCFMT_LEFT, width-278, 2);
	
	m_listResource.ModifyStyle( LVS_OWNERDRAWFIXED, 0, 0 );
	m_listResource.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT |
		LVS_EX_ONECLICKACTIVATE |LVS_EX_GRIDLINES);


	//加载主题资源并设置控件主题
	m_bmpBg.loadBmpFromFile(_T("./resource/theme/bg.bmp"));

	COLORREF maskColor = RGB(90, 90, 90);
	m_btnCancel.LoadBitmap(cancelBtnBmpPath);
	m_btnMin.LoadBitmap(minBtnBmpPath);
	m_btnMenu.LoadBitmap(menuBtnBmpPath);
	m_btnTheme.LoadBitmap(themeBtnBmpPath);


	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBlueClickDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if(nID==SC_MINIMIZE) {
		ToTray(); //最小化到托盘的函数
	}

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
//	CDialog::OnPaint();

	CPaintDC dc(this); // device context for painting

	// Center icon in client rectangle
	int cxIcon = GetSystemMetrics(SM_CXICON);
	int cyIcon = GetSystemMetrics(SM_CYICON);
	CRect rect;
	GetClientRect(&rect);
//	int x = (rect.Width() - cxIcon + 1) / 2;
//	int y = (rect.Height() - cyIcon + 1) / 2;

	m_bmpBg.Paint(dc, rect);

	// Draw the icon
//	dc.DrawIcon(x, y, m_hIcon);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBlueClickDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBlueClickDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
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

void CBlueClickDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{
    if (nIDCtl == IDC_LIST_RESOURCE)
    {
       lpMeasureItemStruct->itemHeight = m_listItemHeight;
    }
}

void CBlueClickDlg::OnInsert() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int count = m_listResource.GetItemCount();

	m_listResource.InsertItem(count, "");
	m_listResource.SetItemText(count, 0, "电影");
	m_listResource.SetItemText(count, 1, "后会无期.rmvb");
	m_listResource.SetItemText(count, 2, "100");
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

void CBlueClickDlg::OnMin() 
{
	// TODO: Add your control notification handler code here
	ToTray();	
}
