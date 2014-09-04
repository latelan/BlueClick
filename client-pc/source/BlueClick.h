// BlueClick.h : main header file for the BLUECLICK application
//

#if !defined(AFX_BLUECLICK_H__925D5AF4_63E3_4F69_8D91_55476C93B9A2__INCLUDED_)
#define AFX_BLUECLICK_H__925D5AF4_63E3_4F69_8D91_55476C93B9A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "BlueClickDlg.h"
#include "BuffreeListCtrl.h"

#define BLUECLICK_MSG_CLOSE_SERVICE 6678

#define BLUECLICK_MAX_FILE_PATH 256
#define BLUECLICK_PROFILE_VAL_LENGTH 256
#define BLUECLICK_MSG_BUF_SIZE 2048
#define BLUECLICK_RES_PACK_SIZE 1024
#define BLUECLICK_RES_PIECE_SIZE (1024*256)
#define BLUECLICK_MAX_SHARE_COUNT 1024
#define BLUECLICK_FILE_TAG_LENGTH 1024
#define BLUECLICK_GB_SIZE (1024*1024*1024)
#define BLUECLICK_MB_SIZE (1024*1024)
#define BLUECLICK_KB_SIZE (1024)
#define BLUECLICK_MAX_FILENAME_LENGTH 256

typedef struct {
	char m_resPath[MAX_PATH];
	char m_resName[MAX_PATH];
	char m_resExt[10];
	char m_resTag[BLUECLICK_FILE_TAG_LENGTH];
	char m_resSize[10];
	char m_resMD5[33];
} STRUCT_SHARE_FILE_INFO;

typedef struct {
	char m_csServerAddr[32];
	UINT m_nServerPort;
	char m_csHostAddr[32];
	char m_csResMD5[33];
	char m_csEvent[32];
	UINT m_nPeerNumWanted;
	UINT m_nUploaded;
	UINT m_nDownloaded;
	UINT m_nLeft;
} STRUCT_DOWNLOAD_QUERY_PARAM;

/////////////////////////////////////////////////////////////////////////////
// CBlueClickApp:
// See BlueClick.cpp for the implementation of this class
//

class CBlueClickApp : public CWinApp
{
public:
	CBlueClickApp();
	static HBITMAP LoadBmpFromFile(CString &bmpPath);
	static BOOL GetHostAddress(CString &csAddr);
	static BOOL GetHostMAC(CString &csMac);
	static BOOL GetWorkSpacePath(CString &csPath);
	static void ConvertANSIToUTF8(CString &strANSI);
	static CString GetFileSizeStr(UINT fileLength);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlueClickApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBlueClickApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLUECLICK_H__925D5AF4_63E3_4F69_8D91_55476C93B9A2__INCLUDED_)
