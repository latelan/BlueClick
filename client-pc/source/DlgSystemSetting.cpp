// DlgSystemSetting.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgSystemSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSystemSetting dialog


CDlgSystemSetting::CDlgSystemSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSystemSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSystemSetting)
	m_serverPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgSystemSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSystemSetting)
	DDX_Control(pDX, IDC_SERVER_IPADDRESS, m_ipAddressCtrl);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_serverPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSystemSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgSystemSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSystemSetting message handlers

void CDlgSystemSetting::OnOK() 
{
	// TODO: Add extra validation here
	

	CDialog::OnOK();
}
