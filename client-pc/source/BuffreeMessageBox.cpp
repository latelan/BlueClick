// BuffreeMessageBox.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BlueClickDlg.h"
#include "BuffreeMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuffreeMessageBox dialog


CBuffreeMessageBox::CBuffreeMessageBox(CString csMsg, CWnd* pParent /*=NULL*/)
	: CDialog(CBuffreeMessageBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuffreeMessageBox)
	m_csMsg = csMsg;
	//}}AFX_DATA_INIT
}


void CBuffreeMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuffreeMessageBox)
	DDX_Control(pDX, IDC_STATIC_MSG, m_staticMsg);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Text(pDX, IDC_STATIC_MSG, m_csMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuffreeMessageBox, CDialog)
	//{{AFX_MSG_MAP(CBuffreeMessageBox)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuffreeMessageBox message handlers

BOOL CBuffreeMessageBox::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	m_bmpBg.loadBmpFromFile(_T("./resource/theme/bg.bmp"));
	

	CBlueClickDlg *mainWnd = (CBlueClickDlg*)AfxGetMainWnd();
	CString themePath = mainWnd->m_themePath;
	CString okBtnBmpPath = themePath + "msg-ok-btn.bmp";
	
	CRect rcRect;
	GetClientRect(&rcRect);
	m_btnOk.SetWindowPos(NULL, rcRect.Width()/2-30, rcRect.Height()-35, 60, 27, SWP_SHOWWINDOW);
	m_btnOk.LoadBitmap(okBtnBmpPath);

	CString bmpBgPath = themePath + _T("bg.bmp");
	HBITMAP hBmpBg = CBlueClickApp::LoadBmpFromFile(bmpBgPath);
	CBitmap bmpBg;
	bmpBg.Attach(hBmpBg);
	m_brushBg.CreatePatternBrush(&bmpBg);
	bmpBg.Detach();
	DeleteObject(hBmpBg);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBuffreeMessageBox::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CBuffreeMessageBox::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcRect;
	GetClientRect(&rcRect);
	pDC->FillRect(&rcRect, &m_brushBg);
	
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CBuffreeMessageBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
    if((CTLCOLOR_STATIC==nCtlColor) && (pWnd==&m_staticMsg))
    {
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(255,255,255));
        return  m_brushBg;// (HBRUSH)::GetStockObject(NULL_BRUSH);
    }
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
