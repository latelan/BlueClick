// BlueClick.cpp : Defines the class behaviors for the application.
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
// CBlueClickApp

BEGIN_MESSAGE_MAP(CBlueClickApp, CWinApp)
	//{{AFX_MSG_MAP(CBlueClickApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlueClickApp construction

CBlueClickApp::CBlueClickApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBlueClickApp object

CBlueClickApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBlueClickApp initialization

BOOL CBlueClickApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CBlueClickDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


HBITMAP CBlueClickApp::LoadBmpFromFile(CString &bmpPath)
{
	return (HBITMAP)::LoadImage(NULL, bmpPath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
}	

BOOL CBlueClickApp::GetHostAddress(CString &csAddr)
{
	char    HostName[100];
	gethostname(HostName, sizeof(HostName));// 获得本机主机名.

	hostent* hn;

	hn = gethostbyname(HostName);//根据本机主机名得到本机ip
	
	if (!hn) {
		return FALSE;
	}

	csAddr = inet_ntoa(*(struct in_addr *)hn->h_addr_list[0]);

	return TRUE;
}


BOOL CBlueClickApp::GetHostMAC(CString &csMac)   
{   
	NCB ncb;
	typedef struct _ASTAT_
	{
		ADAPTER_STATUS  adapt; 
		NAME_BUFFER  NameBuff  [30];   
	}ASTAT,  *  PASTAT;   
	ASTAT Adapter;   
	
	typedef struct _LANA_ENUM   
	{  //  le 
		UCHAR  length; 
		UCHAR  lana[MAX_LANA];   
	}LANA_ENUM  ;   
	LANA_ENUM lana_enum;   
	
	UCHAR uRetCode;   
	memset(&ncb, 0, sizeof(ncb));   
	memset(&lana_enum, 0, sizeof(lana_enum));   
	
	ncb.ncb_command = NCBENUM;   
	ncb.ncb_buffer = (unsigned char *)&lana_enum;   
	ncb.ncb_length = sizeof(LANA_ENUM);   
	uRetCode = Netbios(&ncb);   
	if(uRetCode != NRC_GOODRET)   
		return FALSE;   
	
	for(int lana=0; lana<lana_enum.length; lana++) {
		ncb.ncb_command = NCBRESET; 
		ncb.ncb_lana_num = lana_enum.lana[lana]; 
		uRetCode = Netbios(&ncb);  
		if(uRetCode == NRC_GOODRET) 
			break; 
	} 
	if(uRetCode != NRC_GOODRET)
		return FALSE;   
	
	memset(&ncb, 0, sizeof(ncb)); 
	ncb.ncb_command = NCBASTAT; 
	ncb.ncb_lana_num = lana_enum.lana[0];
	strcpy((char*)ncb.ncb_callname, "*"); 
	ncb.ncb_buffer = (unsigned char *)&Adapter;
	ncb.ncb_length = sizeof(Adapter);
	uRetCode = Netbios(&ncb); 
	if(uRetCode != NRC_GOODRET)  
		return FALSE;   
	csMac.Format("%02X-%02X-%02X-%02X-%02X-%02X",   
		Adapter.adapt.adapter_address[0],   
		Adapter.adapt.adapter_address[1],   
		Adapter.adapt.adapter_address[2],   
		Adapter.adapt.adapter_address[3],   
		Adapter.adapt.adapter_address[4],   
		Adapter.adapt.adapter_address[5] 
		); 
	return TRUE;  
}