// UdpSocket.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "UdpSocket.h"
#include "DlgSplash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket

CUdpSocket::CUdpSocket(CWnd *pParentWnd)
{
	m_pParentWnd = pParentWnd;
}

CUdpSocket::~CUdpSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUdpSocket, CSocket)
	//{{AFX_MSG_MAP(CUdpSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket member functions

void CUdpSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	((CDlgSplash*)m_pParentWnd)->OnReceive();
//	CSocket::OnReceive(nErrorCode);
}
