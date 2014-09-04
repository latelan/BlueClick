// DownloadSocket.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BlueClickDlg.h"
#include "DownloadSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct {
	CDownloadSocket *m_socket;
	char m_resName[MAX_PATH];
	char m_resMD5[33];
	UINT m_pieceID;
	UINT m_listItem;
	UINT m_socketIndex;
}DownloadThreadParam;

typedef struct {
	CDownloadSocket *m_socket;
	char m_buf[BLUECLICK_MSG_BUF_SIZE];
	char m_fileName[BLUECLICK_MAX_FILENAME_LENGTH];
}ReceiveThreadParam;

/////////////////////////////////////////////////////////////////////////////
// CDownloadSocket

CDownloadSocket::CDownloadSocket(CWnd *pParentWnd, UINT nSocketIndex, CString csResName, CString csResMD5, UINT nResPieceCount, UINT nListItem)//CWnd *pParent)
{
	m_pParentWnd = pParentWnd;
	m_nSocketIndex = nSocketIndex;
	m_csResName = csResName;
	m_csResMD5 = csResMD5;
	m_nResPieceCount = nResPieceCount;
	m_nListItem = nListItem;
}

CDownloadSocket::~CDownloadSocket()
{
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CDownloadSocket, CSocket)
	//{{AFX_MSG_MAP(CDownloadSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CDownloadSocket member functions

void CDownloadSocket::OnClose(int nErrorCode) {

}

void CDownloadSocket::DownloadRes(UINT nResPieceId)
{
	DownloadThreadParam *param = new DownloadThreadParam;
	strcpy(param->m_resMD5, m_csResMD5);
	strcpy(param->m_resName, m_csResName);
	param->m_pieceID = nResPieceId;
	param->m_socket = this;
	param->m_listItem = m_nListItem;
	param->m_socketIndex = m_nSocketIndex;
	CreateThread(NULL, 0, DownloadThreadProc, param, 0, NULL);
}

