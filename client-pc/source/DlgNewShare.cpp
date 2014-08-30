// DlgNewShare.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgNewShare.h"
#include "BlueClickDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewShare dialog


CDlgNewShare::CDlgNewShare(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewShare::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewShare)
	m_csFilename = _T("");
	m_csFilePath = _T("");
	//}}AFX_DATA_INIT
}


void CDlgNewShare::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewShare)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BUTTON_SCAN, m_btnScan);
	DDX_Text(pDX, IDC_STATIC_FILENAME, m_csFilename);
	DDX_Text(pDX, IDC_STATIC_FILEPATH, m_csFilePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewShare, CDialog)
	//{{AFX_MSG_MAP(CDlgNewShare)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, OnButtonScan)
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewShare message handlers

BOOL CDlgNewShare::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CBlueClickDlg *mainWnd = (CBlueClickDlg*)AfxGetMainWnd();
	CString themePath = mainWnd->m_themePath;
	CString okBtnBmpPath = themePath + "btn-ok.bmp";
	CString cancelBtnBmpPath = themePath + "btn-cancel.bmp";
	CString scanBtnBmpPath = themePath + "btn-scan.bmp";
	
//	CRect rcRect;
//	GetClientRect(&rcRect);
//	m_btnOk.SetWindowPos(NULL, rcRect.Width()/2-30, rcRect.Height()-35, 60, 27, SWP_SHOWWINDOW);
	m_btnScan.LoadBitmap(scanBtnBmpPath);
	m_btnOk.LoadBitmap(okBtnBmpPath);
	m_btnCancel.LoadBitmap(cancelBtnBmpPath);

	CString bmpBgPath = themePath + _T("dlg-bg.bmp");
	HBITMAP hBmpBg = CBlueClickApp::LoadBmpFromFile(bmpBgPath);
	CBitmap bmpBg;
	bmpBg.Attach(hBmpBg);
	m_brushBg.CreatePatternBrush(&bmpBg);
	bmpBg.Detach();
	DeleteObject(hBmpBg);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CDlgNewShare::OnNcHitTest(CPoint point) 
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

BOOL CDlgNewShare::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcRect;
	GetClientRect(&rcRect);
	pDC->FillRect(&rcRect, &m_brushBg);
	
	return TRUE;	
//	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgNewShare::OnButtonScan() 
{
	// TODO: Add your control notification handler code here
//	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.cfg)|*.cfg|All Files (*.*)|*.*||"), NULL);

	//CString csFileType, csFilename;
//	if (dlgFile.DoModal()) {
	//	csFileType= dlgFile.GetFileExt();
	//	csFilename = dlgFile.GetFileName();
//	}

	OPENFILENAME ofn;
	char csFilePath[MAX_PATH], csFileName[MAX_PATH];
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = csFilePath;
	ofn.lpstrFile[0] = TEXT('\0');
	ofn.nMaxFile = sizeof(csFilePath);
	ofn.lpstrFilter = TEXT("all\0*.*\0"); //定义三个选项，all，text和exe
	ofn.nFilterIndex = 0;      //定义首选项是哪一个
	ofn.lpstrFileTitle = csFileName;
	ofn.nMaxFileTitle = sizeof(csFileName);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER |OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if(GetOpenFileName(&ofn)) {
		CBlueClickDlg *mainWnd = (CBlueClickDlg*)AfxGetMainWnd();
		CString csWorkSpace = mainWnd->m_csWorkSpace;
		SetCurrentDirectory(csWorkSpace);

		m_csFilename = csFileName;
		m_csFilePath = csFilePath;

		UpdateData(FALSE);
	} 
}

HBRUSH CDlgNewShare::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
