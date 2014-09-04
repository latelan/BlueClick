// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "ListenSocket.h"
#include "BlueClickDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket(CWnd *pParentWnd)
{
	m_pParentWnd = pParentWnd;
}

CListenSocket::~CListenSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pWnd = AfxGetMainWnd();
	CBlueClickDlg *pMainWnd = (CBlueClickDlg*)m_pWnd;
	
	if (nErrorCode==0)
	{	
		CServiceSocket serviceSocket;
		pMainWnd->m_listenSocket->Accept(serviceSocket);
		//创建一个发送线程
		CServiceThread *pThread = (CServiceThread*)AfxBeginThread(RUNTIME_CLASS(CServiceThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		
		//添加到线程列表中
		pMainWnd->m_criticalSection.Lock();
		pMainWnd->m_serviceThrdList.AddTail(pThread);
		pMainWnd->m_criticalSection.Unlock();

		pThread->SetMainWnd(pMainWnd);
		// 线程保存socket指针
		pThread->m_hSocket=serviceSocket.Detach();
		//保存线程编号
		pThread->m_nThreadIndex = pMainWnd->m_nServiceThrdIndex;

		//保存文件名
		pThread->m_csResName;// = pMainWnd->m_csResName;
		//启动线程		
		pThread->ResumeThread();
		//线程编号增一
		pMainWnd->m_nServiceThrdIndex++;
		//当开始一个新任务时，m_threadIndex置为1
		if (pMainWnd->m_nServiceThrdIndex==BLUECLICK_MAX_SYN_COUNT+1)
		{
			pMainWnd->m_nServiceThrdIndex = 1;
		}
	}
	
	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::SetMainWnd(CWnd *pWnd)
{
	m_pWnd = pWnd;
}