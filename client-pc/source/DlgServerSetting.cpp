// DlgServerSetting.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgServerSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgServerSetting dialog


CDlgServerSetting::CDlgServerSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgServerSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgServerSetting)
	m_serverPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgServerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgServerSetting)
	DDX_Control(pDX, IDC_SERVER_IPADDRESS, m_ipAddressCtrl);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_serverPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgServerSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgServerSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgServerSetting message handlers

void CDlgServerSetting::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	m_ipAddressCtrl.GetWindowText(m_serverAddr);
	
	CDialog::OnOK();
}
