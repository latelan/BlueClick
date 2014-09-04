// ServiceSocket.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "ServiceSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct {
	CServiceSocket *m_socket;
	UINT m_socketIndex;
	char m_buf[BLUECLICK_MSG_BUF_SIZE];
}ServiceThreadParam;

/////////////////////////////////////////////////////////////////////////////
// CServiceSocket

CServiceSocket::CServiceSocket(CWnd *pParentWnd, UINT nSocketIndex)
{
	m_pParentWnd = pParentWnd;
	m_nSocketIndex = nSocketIndex;
}

CServiceSocket::~CServiceSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServiceSocket, CSocket)
	//{{AFX_MSG_MAP(CServiceSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServiceSocket member functions
#if 0
void CServiceSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char buf[BLUECLICK_MSG_BUF_SIZE];
	
	memset(buf, 0, BLUECLICK_MSG_BUF_SIZE);
	UINT nRet = Receive(buf, BLUECLICK_MSG_BUF_SIZE);
	if (nRet <= 0) {
		return;
	}

	ServiceThreadParam *param = new ServiceThreadParam;
	param->m_socket = this; 
	param->m_socketIndex = m_nSocketIndex;
	strcpy(param->m_buf, buf);

	m_hThreadService = CreateThread(NULL, 0, ServiceThreadProc, param, 0, NULL);
}

/*********************************************************
函数名称：ServiceThreadProc
功能描述：资源服务线程，负责向资源请求方发送数据
作者：	  张永军
创建时间：2014-09-02
参数说明：lpParameter：数据指针
返 回 值：无
*********************************************************/
DWORD _stdcall ServiceThreadProc(LPVOID lpParameter)
{
	ServiceThreadParam *param = (ServiceThreadParam*)lpParameter;
	CServiceSocket *serviceSocket = (CServiceSocket*)param->m_socket;
	UINT nSocketIndex = param->m_socketIndex;
	char msgBuf[BLUECLICK_MSG_BUF_SIZE];
	strncpy(msgBuf, param->m_buf, BLUECLICK_MSG_BUF_SIZE);
	delete param;

	cJSON *pQueryMsgJson=cJSON_Parse(msgBuf);
	if (!pQueryMsgJson) {
		return 0;
	}

	CString csMsgType = cJSON_GetObjectItem(pQueryMsgJson, "MsgType")->valuestring;
	if (csMsgType != "MsgResPieceQuery") {
		return 0;
	}

	CString csQueryResMD5 = cJSON_GetObjectItem(pQueryMsgJson, "QueryResMD5")->valuestring;	
	UINT nQueryPieceId = cJSON_GetObjectItem(pQueryMsgJson, "QueryPieceId")->valueint;
	cJSON_Delete(pQueryMsgJson);

	// 读取分享列表项，获取请求文件信息
	// 0：弃用，这里用来存储资源路径；
	// 1：文件后缀；
	// 2：文件名；
	// 3：文件大小
	// 4：进度条，字串无效，这里用来存储资源标签；
	// 5：文件MD5
	// data：进度条进度
	CBlueClickDlg*	  mainWnd = (CBlueClickDlg*)AfxGetMainWnd();
	CBuffreeListCtrl* listUpload = &mainWnd->m_dlgUploadList.m_listUpload;

	CString csQueryResPath;
	CString csQueryResName;
	UINT nShareResCount = listUpload->GetItemCount();
	for (UINT i = 0; i < nShareResCount; i++) {
		CString csResMD5 = listUpload->GetItemText(i, 5);
		if (csResMD5 == csQueryResMD5) {
			csQueryResPath = listUpload->GetItemText(i, 0);
			csQueryResName = listUpload->GetItemText(i, 2);
			break;
		}
	}

	if (i >= nShareResCount) {
		mainWnd->m_staticStatus.SetWindowText("请求的文件没有找到");
		return 0;
	}

	// 打开请求文件，读取文件信息，以及发送的片段数据
	CFile queryFile(csQueryResPath, CFile::modeRead);
	UINT nQueryResSize = queryFile.GetLength();
	UINT nQueryPieceSize = BLUECLICK_RES_PIECE_SIZE;
	UINT nResPieceCount = (nQueryResSize % nQueryPieceSize == 0) ? (nQueryResSize/nQueryPieceSize) : (nQueryResSize/nQueryPieceSize) + 1;
	
	//如果请求的片段不存在， 则返回
	if (nQueryPieceId >= nResPieceCount || nQueryPieceId < 0) {
		mainWnd->m_staticStatus.SetWindowText("请求的文件片段不存在");
		queryFile.Close();
		return 0;
	}

	//如果请求的是最后一个片段
	if (nQueryPieceId == nResPieceCount - 1) {
		nQueryPieceSize = nQueryResSize % nQueryPieceSize;
	}

	//读取请求片段数据
	char queryPieceBuf[BLUECLICK_RES_PIECE_SIZE];
	memset(queryPieceBuf, 0, BLUECLICK_RES_PIECE_SIZE);
	UINT nFileOffset = nQueryPieceId*BLUECLICK_RES_PIECE_SIZE;
	queryFile.Seek(nFileOffset, CFile::SeekPosition::begin);
	queryFile.Read(queryPieceBuf, nQueryPieceSize);	
	queryFile.Close();
/*
	//发送片段信息
	cJSON *pResPiece = cJSON_CreateObject();
	cJSON_AddStringToObject(pResPiece, "MsgType", "MsgPieceQueryResponse");
	cJSON_AddNumberToObject(pResPiece, "QueryPieceId", nQueryPieceId);
	cJSON_AddNumberToObject(pResPiece, "QueryPieceSize", nQueryPieceSize);

	char *cpJson = cJSON_PrintUnformatted(pResPiece);
	char buf[BLUECLICK_MSG_BUF_SIZE];
	strcpy(buf, cpJson);
	free(cpJson);
	cJSON_Delete(pResPiece);

	serviceSocket->Send(buf, BLUECLICK_MSG_BUF_SIZE);
	mainWnd->m_staticStatus.SetWindowText("请求的片段信息已发送");
*/
	//发送请求片段数据
	UINT nQueryPackCount = ((nQueryPieceSize%1024) == 0) ? (nQueryPieceSize/1024) : (nQueryPieceSize/1024)+1;
	UINT nQueryPackSize = 1024;
	for (UINT nQueryPackId = 0; nQueryPackId < nQueryPackCount; nQueryPackId++) {
		//最后一个包需要单独计算大小
		if (nQueryPackId == nQueryPackCount-1) {
			nQueryPackSize = ((nQueryPieceSize%1024) == 0) ? 1024 : (nQueryPieceSize % 1024);
		}
		serviceSocket->Send(queryPieceBuf+nQueryPackId*1024, nQueryPackSize);
		
		//显示发送状态信息
		CString csMsg;
		csMsg.Format("第%u个包已发送", nQueryPackId+1);
		mainWnd->m_staticStatus.SetWindowText(csMsg);
	}

	PostMessage(mainWnd->m_hWnd, MSG_CLOSE_SERVICE_SOCKET, nSocketIndex, NULL);

	return 0;
}

/*********************************************************
函数名称：OnClose
功能描述：调用主线程的CloseServiceSocket函数，关闭套接字并释放空间
作者：	  张永军
创建时间：2014-09-02
参数说明：lpParameter：数据指针
返 回 值：无
*********************************************************/
void CServiceSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CBlueClickDlg *mainWnd = (CBlueClickDlg*)AfxGetMainWnd();

	PostMessage(mainWnd->m_hWnd, MSG_CLOSE_SERVICE_SOCKET, m_nSocketIndex, NULL);

	CSocket::OnClose(nErrorCode);
}

#endif