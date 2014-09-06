// ServiceThread.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "ServiceThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServiceThread

IMPLEMENT_DYNCREATE(CServiceThread, CWinThread)

CServiceThread::CServiceThread()
{
}

CServiceThread::~CServiceThread()
{
	m_nResSize = -1;
	m_nThreadIndex = -1;
	m_nPieceSize = -1;
	m_nPieceOffset = -1;
}

BOOL CServiceThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here

	if (!AfxSocketInit()) {
		SetThreadPriority(THREAD_PRIORITY_HIGHEST);
		PostThreadMessage(WM_QUIT,0,0);	
		return 0;
	}
	m_serviceSocket.Attach(m_hSocket);
	return TRUE;
}

int CServiceThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	CBlueClickDlg *pMainWnd = (CBlueClickDlg*)m_pWnd;
	
	//从线程链表中删除当前线程
	POSITION pos = pMainWnd->m_serviceThrdList.Find(this);
	if (pos!=NULL)
	{	
		pMainWnd->m_serviceThrdList.RemoveAt(pos);
	}
	//关闭Socket
	if (m_serviceSocket != NULL)
	{
		m_serviceSocket.Close();
	}
	
	//	dlg->m_completedThread++;
	return CWinThread::ExitInstance();
}

void CServiceThread::GetPieceOffset(int nThreadNum, int nThreadIndex, DWORD nResSize, DWORD &nPieceOffset, DWORD &nPieceSize)
{
	DWORD nLastPieceSize;
	//获得文件块平均大小
	nPieceSize = nResSize / nThreadNum;
	//还剩下的文件大小
	nLastPieceSize = nResSize;
	
	nPieceOffset = 0;
	//获得第ThreadIndex块文件的开始位和大小
	for (int i=1; i<= nThreadIndex-1; i++) {
		nLastPieceSize = nLastPieceSize - nPieceSize;
		nPieceOffset += nPieceSize;
	}
	
	//如果是文件最后一块，取得最后一块大小
	if(nThreadIndex == nThreadNum)
	{
		nPieceSize = nLastPieceSize;
	}

	return;	
}

void CServiceThread::SetMainWnd(CWnd *pWnd)
{
	m_pWnd = pWnd;
}

int CServiceThread::Run() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinThread::Run();
}


BEGIN_MESSAGE_MAP(CServiceThread, CWinThread)
	//{{AFX_MSG_MAP(CServiceThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServiceThread message handlers
