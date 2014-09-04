// SearchSocket.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BlueClickDlg.h"
#include "SearchSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchSocket

CSearchSocket::CSearchSocket(CWnd *pParentWnd)
{
	m_pParentWnd = pParentWnd;
}

CSearchSocket::~CSearchSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSearchSocket, CSocket)
	//{{AFX_MSG_MAP(CSearchSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSearchSocket member functions

void CSearchSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//((CBlueClickDlg*)m_pParentWnd)->ReceiveResourceList();	
	
	CSocket::OnReceive(nErrorCode);
}

void CSearchSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnClose(nErrorCode);
}
