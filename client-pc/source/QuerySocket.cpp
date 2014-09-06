// QuerySocket.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "QuerySocket.h"
#include "DownloadSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct {
	char m_dataBuf[BLUECLICK_MSG_BUF_SIZE];
	CSocket *m_socket;
	char m_resName[MAX_PATH];
	char m_resMD5[33];
	UINT m_resPieceCount;
	UINT m_nListItem;
}QueryThreadParam;

DWORD _stdcall QueryThreadProc(LPVOID lpParameter);


/////////////////////////////////////////////////////////////////////////////
// CQuerySocket

CQuerySocket::CQuerySocket(CWnd *pParentWnd, UINT nSocketIndex, CString csResName, CString csResMD5, UINT nResPieceCount, UINT nListItem)
{
	m_pParentWnd = pParentWnd;
	m_nSocketIndex = nSocketIndex;
	m_csResName = csResName;
	m_csResMD5 = csResMD5;
	m_nResPieceCount = nResPieceCount;
	m_nListItem = nListItem;
}

CQuerySocket::~CQuerySocket()
{
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CQuerySocket, CSocket)
	//{{AFX_MSG_MAP(CQuerySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CQuerySocket member functions
