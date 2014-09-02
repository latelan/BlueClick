// BlueClick.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BlueClickDlg.h"
#include "DownloadSocket.h"

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

BOOL CBlueClickApp::GetWorkSpacePath(CString &csPath) 
{  
	char pFileName[MAX_PATH]; 
	int nPos = GetCurrentDirectory( MAX_PATH, pFileName); 
 
	CString csFullPath(pFileName);  
	
	if( nPos < 0 ) {
		csPath = "";
		return FALSE;
	} else { 
		csPath = csFullPath;
		return TRUE;
	}
}


void CBlueClickApp::ConvertANSIToUTF8(CString &strANSI) 
{ 
	int nLen = ::MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,(LPCTSTR)strANSI,-1,NULL,0); 
	unsigned short * wszUTF_8 = new unsigned short[nLen+1]; 
	memset(wszUTF_8, 0, nLen * 2 + 2); 
	nLen = MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strANSI, -1, wszUTF_8, nLen); 
	
	nLen = WideCharToMultiByte(CP_UTF8, 0, wszUTF_8, -1, NULL, 0, NULL, NULL); 
    char *szUTF8=new char[nLen + 1]; 
    memset(szUTF8, 0, nLen + 1); 
    WideCharToMultiByte (CP_UTF8, 0, wszUTF_8, -1, szUTF8, nLen, NULL,NULL); 
	strANSI = szUTF8; 
	delete wszUTF_8; 
	delete szUTF8; 
} 

CString CBlueClickApp::GetFileSizeStr(UINT fileLength)
{
	CString csFileSize;

	if (fileLength >= BLUECLICK_GB_SIZE) {
		FLOAT fFileSize = fileLength / (FLOAT)BLUECLICK_GB_SIZE;
		csFileSize.Format("%.2fG", fFileSize);
	} else if (fileLength >= BLUECLICK_MB_SIZE) {
		FLOAT fFileSize = fileLength / (FLOAT)BLUECLICK_MB_SIZE;
		csFileSize.Format("%.2fMB", fFileSize);
	} else if (fileLength >= BLUECLICK_KB_SIZE) {
		FLOAT fFileSize = fileLength / (FLOAT)BLUECLICK_KB_SIZE;
		csFileSize.Format("%.2fKB", fFileSize);
	} else if (fileLength >= 0){
		csFileSize.Format("%dB", fileLength);
	} else {
		csFileSize = "0Btye";
	}

	return csFileSize;
}

BOOL CBlueClickApp::GetPeerList(CString *resAddr, UINT *resPort, UINT &resCount, STRUCT_DOWNLOAD_QUERY_PARAM &queryParam)
{
	CDownloadSocket serverSocket(NULL);
	
	if (serverSocket.Create() == FALSE) {
		return FALSE;
	}
	
	if (serverSocket.Connect(queryParam.m_csServerAddr, queryParam.m_nServerPort) == FALSE) {
		return FALSE;
	}

	cJSON *pRoot;
	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot, "MsgType", "MsgDownloadRes");
	cJSON_AddStringToObject(pRoot, "ClientIP", queryParam.m_csHostAddr);
	cJSON_AddStringToObject(pRoot,"ResMD5", queryParam.m_csResMD5);
	cJSON_AddStringToObject(pRoot, "Event", queryParam.m_csEvent);
	cJSON_AddNumberToObject(pRoot, "NumWant", queryParam.m_nPeerNumWanted);
	
	char buf[BLUECLICK_MSG_BUF_SIZE];
	memset(buf, 0, BLUECLICK_MSG_BUF_SIZE);
	char *strJson = cJSON_Print(pRoot);
	strcpy(buf, strJson);		
	cJSON_Delete(pRoot);
	delete strJson;
	
	serverSocket.Send(buf, BLUECLICK_MSG_BUF_SIZE);

	memset(buf, 0, BLUECLICK_MSG_BUF_SIZE);
	int nRet = serverSocket.Receive(buf, BLUECLICK_MSG_BUF_SIZE);
	
	serverSocket.Close();

	if (nRet <= 0) {
		return FALSE;
	}
	
	pRoot=cJSON_Parse(buf);
	
	if (!pRoot) {
		//AfxMessageBox("解析服务器JSON返回值失败");
		return FALSE;
	}

	CString msgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (msgType != "MsgClientList") {
		//CBuffreeMessageBox dlgMessageBox("错误的服务器消息类型");
		//dlgMessageBox.DoModal();
		return FALSE;
	}
	
	cJSON *pResArray = cJSON_GetObjectItem(pRoot, "Client");
	if (pResArray == NULL) {
		return FALSE;
	}
	
	resCount = cJSON_GetObjectItem(pRoot, "ClientCount")->valueint;//cJSON_GetArraySize(pResArray);
	
	for (UINT i = 0; i < resCount; i++) {
		cJSON *pRes = cJSON_GetArrayItem(pResArray, 0);
		if (pRes == NULL) {
			continue;
		}
	
		resAddr[i] = cJSON_GetObjectItem(pRes, "ClientAddr")->valuestring;
		resPort[i] = cJSON_GetObjectItem(pRes, "ClientPort")->valueint;
		cJSON_Delete(pRes);
	}

	cJSON_Delete(pResArray);
	cJSON_Delete(pRoot);
	return TRUE;
}

BOOL CBlueClickApp::GetResPiece(char *pieceBuf, UINT nPieceId, CString csResAddr, UINT nResPort, CString csResMD5) {
	CDownloadSocket resSocket(NULL);

	if (resSocket.Create() == NULL) {
			return FALSE;
	}

	if (resSocket.Connect(csResAddr, nResPort) == NULL) {
		return FALSE;
	}

	AfxMessageBox("已连接到资源服务器");

	cJSON *pRoot;
	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType", "MsgGetResPiece");   
	cJSON_AddStringToObject(pRoot,"ResMD5", csResMD5);
	cJSON_AddNumberToObject(pRoot, "PieceWant", nPieceId);

	char *strJson = cJSON_Print(pRoot);
	char buf[BLUECLICK_MSG_BUF_SIZE];
	memset(buf, 0, BLUECLICK_MSG_BUF_SIZE);
	strcpy(buf, strJson);
	cJSON_Delete(pRoot);
	delete strJson;

	resSocket.Send(buf, BLUECLICK_MSG_BUF_SIZE);

	memset(pieceBuf, 0, BLUECLICK_RES_PIECE_SIZE);
	UINT nPackCount = BLUECLICK_RES_PIECE_SIZE / BLUECLICK_RES_PACK_SIZE;
	UINT *nPackStatus = new UINT(nPackCount);
	memset(nPackStatus, 0, nPackCount);
	for (UINT i = 0; i < nPackCount; i++) {
		memset(buf, 0, BLUECLICK_MSG_BUF_SIZE);
		int nRet = resSocket.Receive(buf, BLUECLICK_MSG_BUF_SIZE);

		cJSON *pRes = cJSON_Parse(buf);
		char *data = cJSON_GetObjectItem(pRes, "ResData")->valuestring;
		UINT offset = cJSON_GetObjectItem(pRes, "ResOffset")->valueint;
		cJSON_Delete(pRes);

		strncpy(pieceBuf+offset*BLUECLICK_RES_PACK_SIZE, data, BLUECLICK_RES_PACK_SIZE);
		nPackStatus[offset] = 1;
	}

	for (i = 0; i < nPackCount; i++) {
		if (nPackStatus[i] != 1) {
			return FALSE;
		}
	}

	//片段完整性校验

	delete nPackStatus;
	resSocket.Close();
	return TRUE;
}