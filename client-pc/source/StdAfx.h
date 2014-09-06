// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9681CD0F_F8BA_409A_8AC5_74A769C71DA1__INCLUDED_)
#define AFX_STDAFX_H__9681CD0F_F8BA_409A_8AC5_74A769C71DA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once

#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#pragma comment(lib, "libjson.lib")
#include <afxsock.h>		// MFC socket extensions
#include <afxmt.h>
#include "Json.h"
#include <NB30.H>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

#define WM_DOWNLOAD_COMPLETE (WM_USER+100)
#define WM_CONNECT_FAILED    (WM_USER+100)

#define BLUECLICK_MSG_CLOSE_SERVICE 6678

#define BLUECLICK_MAX_FILE_PATH 256
#define BLUECLICK_PROFILE_VAL_LENGTH 256
#define BLUECLICK_MSG_BUF_SIZE 2048
#define BLUECLICK_RES_PACK_SIZE 1024
#define BLUECLICK_RES_PIECE_SIZE (1024*32)
#define BLUECLICK_MAX_SHARE_COUNT 1024
#define BLUECLICK_FILE_TAG_LENGTH 1024
#define BLUECLICK_GB_SIZE (1024*1024*1024)
#define BLUECLICK_MB_SIZE (1024*1024)
#define BLUECLICK_KB_SIZE (1024)
#define BLUECLICK_MAX_FILENAME_LENGTH 256

#define WM_SHOWTASK (WM_USER +1)
#define BLUECLICK_MAX_SYN_COUNT 1
#define BLUECLICK_MAX_SERVICE_COUNT 5

typedef struct {
	char  m_csResName[MAX_PATH];
	DWORD m_nResSize;
	DWORD m_nPieceSize;
	DWORD m_nResOffset;
	DWORD m_nThreadIndex;
} RES_HEADER;

typedef struct {
	char  m_csData[BLUECLICK_RES_PIECE_SIZE];
	DWORD m_nSize;
} PIECE_DATA;

__int64 CustomFileSeek (HANDLE hf, __int64 distance, DWORD MoveMethod);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9681CD0F_F8BA_409A_8AC5_74A769C71DA1__INCLUDED_)
