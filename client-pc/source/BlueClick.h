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

#define BLUECLICK_MAX_FILE_PATH 256
#define BLUECLICK_PROFILE_VAL_LENGTH 256
#define BLUECLICK_MSG_BUF_LENGTH 2048
#define BLUECLICK_MAX_CLIENT_NUM 5
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
	static BOOL CBlueClickApp::GetWorkSpacePath(CString &csPath);
	static void CBlueClickApp::ConvertANSIToUTF8(CString &strANSI);
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
