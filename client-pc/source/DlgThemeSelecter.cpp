// DlgThemeSelecter.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgThemeSelecter.h"
#include "BlueClickDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgThemeSelecter dialog


CDlgThemeSelecter::CDlgThemeSelecter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgThemeSelecter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgThemeSelecter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgThemeSelecter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgThemeSelecter)
	DDX_Control(pDX, IDC_STATIC_THEME1, m_staticTheme1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgThemeSelecter, CDialog)
	//{{AFX_MSG_MAP(CDlgThemeSelecter)
	ON_BN_CLICKED(IDC_STATIC_THEME1, OnStaticTheme1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgThemeSelecter message handlers

BOOL CDlgThemeSelecter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CBlueClickDlg *mainWnd = (CBlueClickDlg*)AfxGetMainWnd();
	
//	HBITMAP hBmpTheme1 = CBlueClickApp::LoadBmpFromFile(mainWnd->m_themePath + "bg.bmp");

//	m_staticTheme1.SetBitmap(hBmpTheme1);

//	DeleteObject(hBmpTheme1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgThemeSelecter::OnStaticTheme1() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
