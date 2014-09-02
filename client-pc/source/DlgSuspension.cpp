// DlgSuspension.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgSuspension.h"
#include "BlueClickDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSuspension dialog


CDlgSuspension::CDlgSuspension(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSuspension::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSuspension)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSuspension::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSuspension)
	DDX_Control(pDX, IDC_LOGO, m_Logo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSuspension, CDialog)
	//{{AFX_MSG_MAP(CDlgSuspension)	
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_SHOW, OnShow)
	ON_WM_NCLBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSuspension message handlers

BOOL CDlgSuspension::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CBlueClickDlg *mainWnd = (CBlueClickDlg*)AfxGetMainWnd();
	CString logoBmpPath = mainWnd->m_themePath + "logo.bmp";
	HBITMAP hBitmap = CBlueClickApp::LoadBmpFromFile(logoBmpPath);
	m_Logo.SetBitmap(hBitmap);
	
	CBitmap m_Bitmap;
	m_Bitmap.Attach(hBitmap);
	BITMAP bmp;
	m_Bitmap.GetBitmap(&bmp);

	int nX = bmp.bmWidth;
	int nY = bmp.bmHeight;

	HDC hDC = ::GetDC(HWND(NULL));		// 得到屏幕DC  
	int sX = ::GetDeviceCaps(hDC,HORZRES); // 屏幕宽  
	int sY = ::GetDeviceCaps(hDC,VERTRES);	// 屏幕高   
	::ReleaseDC(HWND(NULL),hDC);		// 释放DC

	m_Logo.MoveWindow(0,0,nX,nY);
	//CenterWindow();
	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
	MoveWindow(0,0,nX,nY);	
	MoveWindow((sX-nX-20), sY*20/100, nX, nY, TRUE);
	
	m_Bitmap.Detach();
	
	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CDlgSuspension::OnNcHitTest(CPoint pt)
{
	UINT nHitTest = CDialog::OnNcHitTest(pt);

	if (nHitTest == HTCLIENT &&
				::GetAsyncKeyState(MK_LBUTTON) < 0) // 如果鼠标左键按下，GetAsyncKeyState函数的返回值小于0

		nHitTest = HTCAPTION;

	return nHitTest;
}

void CDlgSuspension::OnOK()
{
	// TODO: Add extra cleanup here

	//OnOK();
}

void CDlgSuspension::OnCancel() 
{
	// TODO: Add extra cleanup here

	//	CDialog::OnCancel();
}

void CDlgSuspension::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu m_Right;
	m_Right.LoadMenu(IDR_MENU_SUSPENSION);
	CMenu *pSub = m_Right.GetSubMenu(0);

	ClientToScreen(&point);
	pSub->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this,NULL);
	
	CDialog::OnRButtonUp(nFlags, point);
}

void CDlgSuspension::OnExit() 
{
	// TODO: Add your command handler code here
	CWnd *pParent = GetParent();
	ASSERT(pParent);

	pParent->PostMessage(WM_QUIT,0,0);
}

void CDlgSuspension::OnShow() 
{
	// TODO: Add your command handler code here
	CBlueClickDlg *pParent = (CBlueClickDlg*)GetParent();
	ASSERT(pParent);
	
	if (pParent->IsWindowVisible()) {
		pParent->ShowWindow(SW_HIDE);
		this->ShowWindow(SW_SHOW);
	} else {
		//pParent->ShowWindow(SW_SHOW);
		this->ShowWindow(SW_HIDE);
		pParent->AnimateWindow(1);
	}
}

void CDlgSuspension::OnUpdateTransparent(int iTransparent)
{
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	if(hInst)
	{
		typedef BOOL (WINAPI *SLWA)(HWND,COLORREF,BYTE,DWORD);
		SLWA pFun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		pFun = (SLWA)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if(pFun)
		{
			pFun(m_hWnd,0,iTransparent,2);
		}
		FreeLibrary(hInst); 
	}
}

void CDlgSuspension::OnNcLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CWnd *pParent = GetParent();
	ASSERT(pParent);
	
	if(!pParent->IsWindowVisible())
		pParent->ShowWindow(SW_SHOW);

	pParent->SetForegroundWindow();

	CDialog::OnNcLButtonDblClk(nFlags, point);
}
