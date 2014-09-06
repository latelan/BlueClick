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

/////////////////////////////////////////////////////////////////////////////
// CServiceSocket

CServiceSocket::CServiceSocket()
{
}

CServiceSocket::~CServiceSocket()
{

}

void CServiceSocket::OnReceive(int nErrorCode) 
{
	CServiceThread *pThread = (CServiceThread*)AfxGetThread();
	CBlueClickDlg* pMainWnd = (CBlueClickDlg*)pThread->m_pWnd;
	CBuffreeListCtrl *listUpload = &pMainWnd->m_dlgUploadList.m_listUpload;

	char msgBuf[BLUECLICK_MSG_BUF_SIZE];	
	UINT nRet = Receive(msgBuf, BLUECLICK_MSG_BUF_SIZE);

	cJSON *pQueryMsgJson=cJSON_Parse(msgBuf);

	if (!pQueryMsgJson) {
		return;
	}

	CString csMsgType = cJSON_GetObjectItem(pQueryMsgJson, "MsgType")->valuestring;
	if (csMsgType != "MsgResPieceQuery") {
		return;
	}

	CString csQueryResMD5 = cJSON_GetObjectItem(pQueryMsgJson, "QueryResMD5")->valuestring;	
	UINT nQueryPieceId = cJSON_GetObjectItem(pQueryMsgJson, "QueryPieceId")->valueint;
	cJSON_Delete(pQueryMsgJson);

//	AfxMessageBox(csQueryResMD5);

	// 读取分享列表项，获取请求文件信息
	// 0：弃用，这里用来存储资源路径；
	// 1：文件后缀；
	// 2：文件名；
	// 3：文件大小
	// 4：进度条，字串无效，这里用来存储资源标签；
	// 5：文件MD5
	// data：进度条进度
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
		pMainWnd->m_staticStatus.SetWindowText("请求的文件没有找到");
		return;
	}

	DWORD ReadOnce, LeftToRead, nReadSize;
	CFile fileRes;
	//以共享和读方式打开文件
	if(!fileRes.Open(csQueryResPath, CFile::shareDenyWrite) | CFile::modeRead)
	{
		return;
	}
	pThread->m_nResSize = fileRes.GetLength();
	
	//获得文件起始位和文件块大小
	pThread->GetPieceOffset(BLUECLICK_MAX_SYN_COUNT, pThread->m_nThreadIndex, pThread->m_nResSize, pThread->m_nPieceOffset, pThread->m_nPieceSize);
	
	//还剩下的文件大小
	LeftToRead = pThread->m_nPieceSize;
	fileRes.Seek(pThread->m_nPieceOffset, CFile::begin);

	RES_HEADER cResHeader;
	memset(cResHeader.m_csResName, 0, MAX_PATH);
	strcpy(cResHeader.m_csResName, csQueryResName.GetBuffer(0));
	cResHeader.m_nResOffset = pThread->m_nPieceOffset;
	cResHeader.m_nResSize = pThread->m_nResSize;
	cResHeader.m_nPieceSize = pThread->m_nPieceSize;
	cResHeader.m_nThreadIndex = pThread->m_nThreadIndex;

	Send(&cResHeader, sizeof(RES_HEADER));

	PIECE_DATA cPieceData;
	//读取文件并发送文件块
	while(LeftToRead > 0) {	
		if (LeftToRead > BLUECLICK_RES_PIECE_SIZE) {
			ReadOnce = BLUECLICK_RES_PIECE_SIZE;
		}
		else
		{
			ReadOnce=LeftToRead;
		}
		//读出一块文件
		nReadSize = fileRes.Read(cPieceData.m_csData, BLUECLICK_RES_PIECE_SIZE);
		//发送文件块
		nRet = Send(cPieceData.m_csData, nReadSize);
		LeftToRead = LeftToRead - nReadSize;
	}
	
	//关闭文件
	fileRes.Close();
	pMainWnd->m_staticStatus.SetWindowText("文件已发送完毕");

	//通知此线程停止
	//SetThreadPriority(THREAD_PRIORITY_HIGHEST);
	//PostThreadMessage(pThread, WM_QUIT,0,0);	
}
// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServiceSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CServiceSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServiceSocket member functions
