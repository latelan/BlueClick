// DlgSplash.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgSplash.h"
#include "BlueClickDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSplash dialog


CDlgSplash::CDlgSplash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSplash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSplash)
	m_width = 400;
	m_height = 250;
	m_timeQuery = 0;
	//}}AFX_DATA_INIT
}


void CDlgSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSplash)
	DDX_Control(pDX, IDC_STATIC_SPLASH_MSG, m_staticSplashMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSplash, CDialog)
	//{{AFX_MSG_MAP(CDlgSplash)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSplash message handlers

BOOL CDlgSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HDC hDC = ::GetDC(HWND(NULL));		// 得到屏幕DC  
	int x = ::GetDeviceCaps(hDC,HORZRES); // 屏幕宽  
	int y = ::GetDeviceCaps(hDC,VERTRES);	// 屏幕高   
	::ReleaseDC(HWND(NULL),hDC);		// 释放DC
	
	MoveWindow((x-m_width)/2, (y-m_height)/2, m_width, m_height, TRUE);
	m_staticSplashMsg.SetWindowPos(NULL, 10, 210, 200, 30, SWP_SHOWWINDOW); 
	
	CRect rcRect;
	GetClientRect(&rcRect);	
	
	CString themePath = ((CBlueClickDlg*)m_pParentWnd)->m_themePath;
	CString bmpBgPath = themePath + _T("splash-bg.bmp");
	HBITMAP hBmpBg = CBlueClickApp::LoadBmpFromFile(bmpBgPath);
	CBitmap bmpBg;
	bmpBg.Attach(hBmpBg);
	m_brushBg.CreatePatternBrush(&bmpBg);
	bmpBg.Detach();
	DeleteObject(hBmpBg);

	DWORD dwStyle = AW_BLEND;
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	typedef BOOL (WINAPI MYFUNC(HWND, DWORD, DWORD));
	MYFUNC* AnimateWindow;
	AnimateWindow = (MYFUNC*)::GetProcAddress(hInst, "AnimateWindow");
	AnimateWindow(this->m_hWnd, 750, dwStyle);
	FreeLibrary(hInst);

	m_staticSplashMsg.SetWindowText("正在初始化...");
	m_udpSocket = new CUdpSocket(this);

	if(!m_udpSocket->Create(0, SOCK_DGRAM, NULL)) {
		m_staticSplashMsg.SetWindowText("网络环境初始化失败...");
		CDlgSplash::OnClose();
		return FALSE;
	}

	BOOL bBroadCast = true;
	m_udpSocket->SetSockOpt(SO_BROADCAST, &bBroadCast, sizeof(BOOL));

	SetTimer(1, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgSplash::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcRect;
	GetClientRect(&rcRect);
	pDC->FillRect(&rcRect, &m_brushBg);
	
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CDlgSplash::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
    if((CTLCOLOR_STATIC==nCtlColor) && (pWnd==&m_staticSplashMsg))
    {
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(255,255,255));
        return  m_brushBg;// (HBRUSH)::GetStockObject(NULL_BRUSH);
    }
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CDlgSplash::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_timeQuery++;
//	CRect rect;
//	GetClientRect(&rect);
//	CRect staticRect;
//	m_staticSplashMsg.GetClientRect(&staticRect);

	m_staticSplashMsg.SetWindowText("正在搜索服务器...");
	CString hostIP;
	CBlueClickApp::GetHostAddress(hostIP);
	char out[1024];
	memset(out, 0, 1024);
	cJSON *pRoot;
	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType",     "MsgOnline");   
	cJSON_AddStringToObject(pRoot,"IP",        hostIP.GetBuffer(0));   
	cJSON_AddNumberToObject(pRoot,"port",       1080);

	strcpy(out, cJSON_Print(pRoot));

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_BROADCAST;
	addr.sin_port = htons(6666);

	m_udpSocket->SendTo(out, 1024, (SOCKADDR*)&addr, sizeof(addr));

//	CString csMac;
//	CBlueClickApp::GetHostMAC(csMac);
//	AfxMessageBox(csMac);

	cJSON_Delete(pRoot);

	if (m_timeQuery >= 4) {
		CDlgSplash::OnClose();
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgSplash::OnReceive()
{
	CDlgSplash::OnClose();
}

void CDlgSplash::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	Sleep(1000);
	DWORD dwStyle = AW_BLEND;
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	typedef BOOL (WINAPI MYFUNC(HWND, DWORD, DWORD));
	MYFUNC* AnimateWindow;
	AnimateWindow = (MYFUNC*)::GetProcAddress(hInst, "AnimateWindow");
	AnimateWindow(this->m_hWnd, 750, AW_HIDE | dwStyle);
	FreeLibrary(hInst);		
	
	CDialog::OnCancel();
}
