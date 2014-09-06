// DownloadThread.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DownloadThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDownloadThread

IMPLEMENT_DYNCREATE(CDownloadThread, CWinThread)

CDownloadThread::CDownloadThread()
{
	m_nThreadIndex = -1;
	m_nPieceSize = 0;
	m_nPieceOffset = 0;
	m_nSaveSize = 0;
}

CDownloadThread::~CDownloadThread()
{
}

BOOL CDownloadThread::InitInstance()
{

	return TRUE;
}

int CDownloadThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	CBlueClickDlg *mainWnd=(CBlueClickDlg*)m_pWnd;
	//从线程链表中删除当前线程
	POSITION pos=mainWnd->m_downloadThrdList.Find(this);
	if (pos!=NULL)
	{	
		mainWnd->m_downloadThrdList.RemoveAt(pos);
	}
	
	//关闭Socket
	if (m_downloadSocket!=NULL)
	{
		m_downloadSocket.Close();
	}
	
	//判断如果文件发送完成,即线程列表为0
	if (mainWnd->m_downloadThrdList.GetCount()==0 && m_downloadSocket.m_nRecvSize!=0)
	{
		//给主窗口发送消息 
		PostMessage(mainWnd->m_hWnd, WM_DOWNLOAD_COMPLETE, 0, 0);
	}

	return CWinThread::ExitInstance();
}

void CDownloadThread::SetMainWnd(CWnd *pWnd)
{
	m_pWnd = pWnd;
}


int CDownloadThread::Run() 
{
	CBlueClickDlg *mainWnd=(CBlueClickDlg*)m_pWnd;
	CSocket querySocket;

	if (!AfxSocketInit()) {
		return 0;
	}

	if (querySocket.Create() == FALSE) {
		return 0;
	} 

	if (querySocket.Connect(m_csServerAddr, m_nServerPort) == TRUE) {
		mainWnd->m_staticStatus.SetWindowText("服务器连接成功");
	} else {
		mainWnd->m_staticStatus.SetWindowText("服务器连接失败");
		return 0;
	}

	cJSON *pRoot;
	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot, "MsgType", "MsgDownloadRes");
	cJSON_AddStringToObject(pRoot, "ClientIP", m_csHostAddr);
	cJSON_AddStringToObject(pRoot,"ResMD5", m_csResMD5);
	cJSON_AddStringToObject(pRoot, "Event", "start");
	cJSON_AddNumberToObject(pRoot, "NumWant", 1);
	
	char msgBuf[BLUECLICK_MSG_BUF_SIZE];
	memset(msgBuf, 0, BLUECLICK_MSG_BUF_SIZE);
	char *strJson = cJSON_Print(pRoot);
	strcpy(msgBuf, strJson);		
	cJSON_Delete(pRoot);
	delete strJson;

	querySocket.Send(msgBuf, BLUECLICK_MSG_BUF_SIZE);

	memset(msgBuf, 0, BLUECLICK_MSG_BUF_SIZE);
	querySocket.Receive(msgBuf, BLUECLICK_MSG_BUF_SIZE);

	pRoot=cJSON_Parse(msgBuf);
	if (!pRoot) {
		return 0;
	}
	
	CString csMsgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (csMsgType != "MsgClientList") {
		return 0;
	}
	
	cJSON  *pClientList = cJSON_GetObjectItem(pRoot, "Client");
	UINT    nClientCount = cJSON_GetObjectItem(pRoot, "ClientCount")->valueint;
	if (nClientCount <= 0) {
		return 0;		
	}

	cJSON  *pClient = cJSON_GetArrayItem(pClientList, 0);
	CString csPeerAddr = cJSON_GetObjectItem(pClient, "ClientIP")->valuestring;
	UINT	nPeerPort = cJSON_GetObjectItem(pClient, "ClientPort")->valueint;
	delete strJson;

	if (csPeerAddr == m_csHostAddr) {
		mainWnd->m_staticStatus.SetWindowText("资源已在本地，无需下载");
		return 0;
	}

	if (m_downloadSocket.Create() == FALSE) {
		mainWnd->m_staticStatus.SetWindowText("网络连接失败");
	}

	m_downloadSocket.SetMainWnd(mainWnd);
	if (m_downloadSocket.Connect(csPeerAddr, nPeerPort) == TRUE) {
		mainWnd->m_staticStatus.SetWindowText("资源客户端连接成功");
	} else {
		mainWnd->m_staticStatus.SetWindowText("资源客户端连接失败");
		PostThreadMessage(WM_QUIT,0,0);	
		return 0;
	}

	pRoot=cJSON_CreateObject();
	cJSON_AddStringToObject(pRoot,"MsgType", "MsgResPieceQuery");   
	cJSON_AddStringToObject(pRoot,"QueryResMD5", m_csResMD5);
	cJSON_AddNumberToObject(pRoot, "QueryPieceId", 0);
	
	strJson = cJSON_Print(pRoot);
	memset(msgBuf, 0, BLUECLICK_MSG_BUF_SIZE);
	strncpy(msgBuf, strJson, BLUECLICK_MSG_BUF_SIZE);
	cJSON_Delete(pRoot);
	delete strJson;

	// 发送资源片段请求
	m_downloadSocket.Send(msgBuf, BLUECLICK_MSG_BUF_SIZE);
/*
	memset(msgBuf, 0, BLUECLICK_MSG_BUF_SIZE);
	m_downloadSocket.Receive(msgBuf, BLUECLICK_MSG_BUF_SIZE);

	AfxMessageBox(msgBuf);

	pRoot = cJSON_Parse(msgBuf);
	if (!pRoot) {
		return 0;
	}

	csMsgType = cJSON_GetObjectItem(pRoot, "MsgType")->valuestring;
	if (csMsgType != "MsgPieceQueryResponse") {
		return 0;
	}
	
	//	UINT nQueryPieceId = cJSON_GetObjectItem(pResPiece, "QueryPieceId")->valueint;
	UINT nQueryPieceSize = cJSON_GetObjectItem(pRoot, "QueryPieceSize")->valueint;
	cJSON_Delete(pRoot);
	
	mainWnd->m_staticStatus.SetWindowText("请求的片段信息已接收");
*/
	return CWinThread::Run();
}
BEGIN_MESSAGE_MAP(CDownloadThread, CWinThread)
	//{{AFX_MSG_MAP(CDownloadThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDownloadThread message handlers
