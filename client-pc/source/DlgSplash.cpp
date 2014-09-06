// DlgSplash.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgSplash.h"
#include "BlueClickDlg.h"
#include "DlgServerSetting.h"


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
	m_csConfigFilename = ((CBlueClickDlg*)m_pParentWnd)->m_csConfigFilename;
	m_csResListFilename = ((CBlueClickDlg*)m_pParentWnd)->m_csResListFilename;
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
	DeleteDC(hDC);
	
	MoveWindow((x-m_width)/2, (y-m_height)/2, m_width, m_height, TRUE);
	m_staticSplashMsg.SetWindowPos(NULL, 10, 210, 300, 30, SWP_SHOWWINDOW); 
	
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

	m_udpSocket = new COnlineSocket(this);

	if(!m_udpSocket->Create(0, SOCK_DGRAM, NULL)) {
		m_staticSplashMsg.SetWindowText("网络环境初始化失败，正在退出...");
		Close();
		return FALSE;
	}

	BOOL bBroadCast = true;
	m_udpSocket->SetSockOpt(SO_BROADCAST, &bBroadCast, sizeof(BOOL));

	m_hThreadInit = CreateThread(NULL, 0, SplashInitProc, this, 0, NULL);

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

void CDlgSplash::OnReceive()
{
	char buf[BLUECLICK_MSG_BUF_SIZE];
	memset(buf, 0, BLUECLICK_MSG_BUF_SIZE);
	int nRet = m_udpSocket->Receive(buf, BLUECLICK_MSG_BUF_SIZE);

	if (nRet <= 0) {
		return;
	}

	cJSON *pRoot;
	pRoot=cJSON_Parse(buf);

	if (!pRoot) {
		//AfxMessageBox("解析JSON失败");
		return;
	}

	CString csMsgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (csMsgType != "MsgOnlineResponse") {
		//AfxMessageBox("错误的信息类型");
		return;
	}

	CString csMsgReserved = cJSON_GetObjectItem(pRoot, "Reserved")->valuestring;
	if (csMsgReserved != "null") {
		//AfxMessageBox("错误的信息类型");
		return;
	}

	m_staticSplashMsg.SetWindowText("已发现服务器，正在连接...");

	//解析JSON获取
	m_csServerAddr = cJSON_GetObjectItem(pRoot, "ServerIP")->valuestring;
	cJSON_Delete(pRoot);

	//AfxMessageBox(m_csServerAddr);

	WritePrivateProfileString("服务端配置", "IP", m_csServerAddr, m_csConfigFilename);
	
	((CBlueClickDlg*)m_pParentWnd)->m_csServerAddr = m_csServerAddr;
	((CBlueClickDlg*)m_pParentWnd)->m_nServerPort = m_nServerPort;
	((CBlueClickDlg*)m_pParentWnd)->m_csHostAddr = m_csHostAddr;
	((CBlueClickDlg*)m_pParentWnd)->m_csHostMAC = m_csHostMAC;
	((CBlueClickDlg*)m_pParentWnd)->m_nHostPort = m_nHostPort;
	
	Sleep(2000);

	CDlgSplash::OnOK();
}

void CDlgSplash::OnOK() {
	if (m_hThreadInit != NULL) {
		TerminateThread(m_hThreadInit, 0);
	}

	CDialog::OnOK();
}

void CDlgSplash::Close()
{
	Sleep(2000);

	DWORD dwStyle = AW_BLEND;
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	typedef BOOL (WINAPI MYFUNC(HWND, DWORD, DWORD));
	MYFUNC* AnimateWindow;
	AnimateWindow = (MYFUNC*)::GetProcAddress(hInst, "AnimateWindow");
	AnimateWindow(this->m_hWnd, 750, AW_HIDE | dwStyle);
	FreeLibrary(hInst);		

	//if (m_hThreadInit != NULL) {
	//	TerminateThread(m_hThreadInit, 0);
	//	m_hThreadInit = NULL;
	//}

	CDialog::OnCancel();
}

DWORD _stdcall SplashInitProc(LPVOID lpParameter) {
	CDlgSplash *pDlg = (CDlgSplash*)lpParameter;
	CString csConfigFilename = pDlg->m_csConfigFilename;
	CString csServerAddr, csHostAddr, csHostMAC;
	UINT nServerPort, nHostPort;
	char jsonOnline[BLUECLICK_MSG_BUF_SIZE];

	//查找是否存在配置文件，若不存在，则生成一个新的默认设置的ini文件
	CFileFind finder;
	BOOL bRet = finder.FindFile(pDlg->m_csConfigFilename);  
	if( !bRet ) {
		CBlueClickApp::GetHostAddress(csHostAddr);
		CBlueClickApp::GetHostMAC(csHostMAC);
		WritePrivateProfileString("服务端配置", "IP", "0.0.0.0", csConfigFilename);
		WritePrivateProfileString("服务端配置", "Port", "5566", csConfigFilename);
		WritePrivateProfileString("客户端配置", "IP", csHostAddr, csConfigFilename);
		WritePrivateProfileString("客户端配置", "MAC", csHostMAC, csConfigFilename);
		WritePrivateProfileString("客户端配置", "Port", "6666", csConfigFilename);
	}

	//读写本地配置文件
	GetPrivateProfileString("服务端配置", "IP", "0.0.0.0", csServerAddr.GetBuffer(BLUECLICK_PROFILE_VAL_LENGTH), BLUECLICK_PROFILE_VAL_LENGTH, csConfigFilename);
	nServerPort = GetPrivateProfileInt("服务端配置", "Port", 5566, csConfigFilename);
	GetPrivateProfileString("客户端配置", "IP", "0.0.0.0", csHostAddr.GetBuffer(BLUECLICK_PROFILE_VAL_LENGTH), BLUECLICK_PROFILE_VAL_LENGTH, csConfigFilename);
	GetPrivateProfileString("客户端配置", "MAC", "00-00-00-00-00-00", csHostMAC.GetBuffer(BLUECLICK_PROFILE_VAL_LENGTH), BLUECLICK_PROFILE_VAL_LENGTH, csConfigFilename);
	nHostPort = GetPrivateProfileInt("客户端配置", "Port", 6666, csConfigFilename);
	csServerAddr.ReleaseBuffer();
	csHostAddr.ReleaseBuffer();
	csHostMAC.ReleaseBuffer();

	//获取本机信息
	//CBlueClickApp::GetHostAddress(csHostAddr);
	//CBlueClickApp::GetHostMAC(csHostMAC);

	//查找是否存在资源列表文件，若不存在，则生成一个新的默认列表文件
	//资源列表读取放在主窗口初始化线程里，即发现服务器之后
	bRet = finder.FindFile(pDlg->m_csResListFilename);  
	if( !bRet ) {
		CFile file(pDlg->m_csResListFilename, CFile::modeCreate|CFile::modeWrite);
		char buf[BLUECLICK_MAX_SHARE_COUNT] = {'\0'};

		file.Write(buf, BLUECLICK_MAX_SHARE_COUNT);
		file.Close();
	}

	//splash窗口成员变量赋值 
	pDlg->m_csServerAddr = csServerAddr;
	pDlg->m_nServerPort = nServerPort;
	pDlg->m_csHostAddr = csHostAddr;
	pDlg->m_csHostMAC = csHostMAC;
	pDlg->m_nHostPort = nHostPort;

	cJSON *pRoot;
	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType", "MsgOnline");   
	cJSON_AddStringToObject(pRoot,"ClientIP", csHostAddr.GetBuffer(0));   
	cJSON_AddStringToObject(pRoot,"ClientMAC", csHostMAC.GetBuffer(0));
	cJSON_AddNumberToObject(pRoot,"ClientListenPort", nHostPort);

	char *strJson = cJSON_Print(pRoot);
	memset(jsonOnline, 0, BLUECLICK_MSG_BUF_SIZE);
	strcpy(jsonOnline, strJson);		
	delete strJson;

	/*
	//初始化网络环境
	if (!AfxSocketInit())
	{
		pDlg->m_staticSplashMsg.SetWindowText("网络环境初始化失败，正在退出...");
		pDlg->Close();
	}

	//pDlg->m_udpSocket = new COnlineSocket(pDlg);

	if(!pDlg->m_udpSocket->Create(0, SOCK_DGRAM, NULL)) {
		pDlg->m_staticSplashMsg.SetWindowText("网络环境初始化失败，正在退出...");
		pDlg->Close();
		return FALSE;
	}

	BOOL bBroadCast = true;
	pDlg->m_udpSocket->SetSockOpt(SO_BROADCAST, &bBroadCast, sizeof(BOOL));
	*/

	//连接服务器
	for (int i = 1; i <= 3; i++) {
		pDlg->m_staticSplashMsg.SetWindowText("正在连接服务器...");
		pDlg->m_udpSocket->SendTo(jsonOnline, BLUECLICK_MSG_BUF_SIZE, nServerPort, csServerAddr);
		Sleep(1000);
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_BROADCAST;
	addr.sin_port = htons(nServerPort);
	
	//局域网网络地址获取，即取本机IP地址第三个'.'之前的字串
	UINT nDotPos = csHostAddr.Find(".");
	nDotPos = csHostAddr.Find(".", nDotPos+1);
	nDotPos = csHostAddr.Find(".", nDotPos+1);
	CString csAddrPrefix = csHostAddr.Left(nDotPos+1);
	
	//连接服务器超时, 自动发现服务器
	for (i = 1; i <= 5; i++) {
		CString csMsg = "连接服务器失败，正在搜索服务器...";
		pDlg->m_staticSplashMsg.SetWindowText(csMsg);
	
		//采用局域网广播的方式发现服务器，但在实测中发送太慢
		//for (int j = 1; j < 255; j++) {
		//	csServerAddr.Format("%s%d", csAddrPrefix, j);
		//	pDlg->m_udpSocket->SendTo(jsonOnline, BLUECLICK_MSG_BUF_SIZE, nServerPort, csServerAddr, 0);
		//}
		
		//采用局域网广播的方式发现服务器，//但在实测中发现有的局域网内发送广播消息无效，因此改用一个循环向局域网内所有主机发送上线请求
		pDlg->m_udpSocket->SendTo(jsonOnline, BLUECLICK_MSG_BUF_SIZE, (SOCKADDR*)&addr, sizeof(addr));
		Sleep(1000*i);
	}

	//CDlgServerSetting dlgServerSetting(pDlg);
	//if (dlgServerSetting.DoModal() == IDOK) {
	//	m_csServerAddr = dlgServerSetting.m_csServerAddr;
	//	m_nServerPort = dlgServerSetting.m_nServerPort;
	//	SetTimer(1, 0, NULL);
	//} else {
	pDlg->m_staticSplashMsg.SetWindowText("未找到服务器，程序正在退出...");
	pDlg->Close();
	//}
	return 0;
}
