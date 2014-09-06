// IndexSocket.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "IndexSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIndexSocket

CIndexSocket::CIndexSocket(CWnd *pParent)
{
	m_pWnd = pParent;
}

CIndexSocket::~CIndexSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CIndexSocket, CSocket)
	//{{AFX_MSG_MAP(CIndexSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CIndexSocket member functions

void CIndexSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnReceive(nErrorCode);
}

void CIndexSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnClose(nErrorCode);
}
