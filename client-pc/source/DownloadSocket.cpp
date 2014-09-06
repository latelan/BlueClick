// DownloadSocket1.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DownloadSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDownloadSocket

CDownloadSocket::CDownloadSocket()
{
	m_nPieceSize = 0;
	m_nRecvSize = 0;
}

CDownloadSocket::~CDownloadSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CDownloadSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CDownloadSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CDownloadSocket member functions

void CDownloadSocket::SetMainWnd(CWnd *pWnd)
{
	m_pWnd = pWnd;
}

void CDownloadSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnConnect(nErrorCode);
}

void CDownloadSocket::OnReceive(int nErrorCode) 
{
	CDownloadThread *pThread=(CDownloadThread*)AfxGetThread();
	CBlueClickDlg *pMainWnd=(CBlueClickDlg*)m_pWnd;
	PIECE_DATA cPieceData;
	RES_HEADER cResHeader;
	UINT nRet = 0;
	memset(&cPieceData, 0, sizeof(PIECE_DATA));

	CFile fileTmp;
	CFile fileRes;
	CFileFind fileFinder;
	CFileException e;

	CString csTmpFilePath;
	CBlueClickApp::GetWorkSpacePath(csTmpFilePath);
	csTmpFilePath += "/temp/";
	
	if (!CBlueClickApp::MakeDiectory(csTmpFilePath)) {
		return;
	}

	CString csDownloadPath = pThread->m_csSavePath + "\\";

	//接收包头
	if (!fileFinder.FindFile(m_csTmpResName)) {
		memset(cResHeader.m_csResName, 0, sizeof(RES_HEADER));
		nRet = Receive(&cResHeader, sizeof(RES_HEADER));
		if (nRet == sizeof(RES_HEADER)) {
			m_csTmpResName.Format("%s%d.tmp", csTmpFilePath, cResHeader.m_nThreadIndex);
			//创建临时标志文件
			if(!fileTmp.Open(m_csTmpResName, CFile::modeCreate | CFile::modeReadWrite)) {
				pMainWnd->m_staticStatus.SetWindowText("临时文件创建失败");
				return;
			}
			fileTmp.Close();

			////////////////////////////////////////////////
			m_csResName = cResHeader.m_csResName;
			m_csResName = csDownloadPath+m_csResName;

			//保存信息
			pThread->m_nPieceOffset = cResHeader.m_nResOffset;
			pThread->m_nThreadIndex = cResHeader.m_nThreadIndex;
			pThread->m_nPieceSize = cResHeader.m_nPieceSize;
			m_nPieceSize = cResHeader.m_nPieceSize;
			if (pThread->m_nThreadIndex==1) {
				//创建保存文件
				if (!fileRes.Open(m_csResName, CFile::modeCreate | CFile::modeReadWrite)) {
					pMainWnd->m_staticStatus.SetWindowText("文件创建失败");
					return;
				}
				
				//保存文件总长度
				pMainWnd->m_nResSize = cResHeader.m_nResSize;
				fileRes.Close();
			}	
		}
		
	} else { // 接收片段数据
		//接收数据	
		nRet = Receive(cPieceData.m_csData, BLUECLICK_RES_PIECE_SIZE * sizeof(char));
		//保存收到的单个包数据量
		cPieceData.m_nSize = nRet;
		//保存接收总的数目
		pMainWnd->m_nRecvSize += nRet;
		//单个线程接收的数目
		m_nRecvSize += nRet;
		//速度保存变量
		pMainWnd->m_nSpeedDownload += nRet;	
		//如果数据包小于10（5M）
		if (m_pieceDataList.GetCount() < 20)
		{
			m_pieceDataList.AddTail(cPieceData);	
		}
		//大于5M时，写入文件
		else {	
			m_pieceDataList.AddTail(cPieceData);	
			//打开保存文件
			if(!fileRes.Open(m_csResName, CFile::modeReadWrite | CFile::shareDenyNone, &e)) {
				if (e.m_cause==CFileException::sharingViolation) {
					pMainWnd->m_staticStatus.SetWindowText("文件打开失败");	
				}
				return;
			}	
			//将链表内容写入到文件中
			//走到合适的位置
			//file.Seek(pThread->m_threadBgPos+pThread->m_saveNum,CFile::begin);
			//自己写的支持64位的Seek函数
			CustomFileSeek((HWND)fileRes.m_hFile, pThread->m_nPieceOffset+pThread->m_nSaveSize, FILE_BEGIN);
			POSITION pos= m_pieceDataList.GetHeadPosition();
			while(pos != NULL) {	
				PIECE_DATA cData= m_pieceDataList.GetHead();
				//写入文件
				fileRes.Write(cData.m_csData, cData.m_nSize);
				//存入文件计数
				pThread->m_nSaveSize += cData.m_nSize;
				
				m_pieceDataList.RemoveHead();
				pos=m_pieceDataList.GetHeadPosition();
			}			

			fileRes.Close();
			/////////////////////////
		}	
		
	}
	
	//2010.3.29修改
	//*这里很关键，对方（发送端）关闭Socket的时候，
	//*这边还不一定接收完成
	//*所以不能马上关闭
	if (m_nRecvSize == m_nPieceSize) {				
		if (m_pieceDataList.GetCount()!=0) {
			if (!fileRes.Open(m_csResName, CFile::modeReadWrite | CFile::shareDenyNone,&e)) {
				if (e.m_cause==CFileException::sharingViolation) {
					pMainWnd->m_staticStatus.SetWindowText("文件打开失败");	
				}
				return;
			}
			
			//将链表内容写入到文件中
			//走到合适的位置
			//file.Seek(pThread->m_threadBgPos+pThread->m_saveNum,CFile::begin);
			//自己写的支持64位的Seek函数
			CustomFileSeek((HWND)fileRes.m_hFile, pThread->m_nPieceOffset+pThread->m_nSaveSize, FILE_BEGIN);
	
			//将链表内容写入到文件中
			POSITION pos= m_pieceDataList.GetHeadPosition();
			while (pos != NULL) {	
				PIECE_DATA cData= m_pieceDataList.GetHead();
				//写入文件
				fileRes.Write(cData.m_csData, cData.m_nSize);
				//存入文件计数
				pThread->m_nSaveSize += cData.m_nSize;
				
				m_pieceDataList.RemoveHead();
				pos=m_pieceDataList.GetHeadPosition();
			}
			
			fileRes.Close();
			
		}

		//通知此线程停止
		AfxGetThread()->PostThreadMessage(WM_QUIT,0,0);		
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
