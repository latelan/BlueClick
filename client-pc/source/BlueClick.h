// BlueClick.h : main header file for the BLUECLICK application
//

#if !defined(AFX_BLUECLICK_H__F1DB34CC_ADE0_425E_B4EE_6EBDE3495921__INCLUDED_)
#define AFX_BLUECLICK_H__F1DB34CC_ADE0_425E_B4EE_6EBDE3495921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBlueClickApp:
// See BlueClick.cpp for the implementation of this class
//

class CBlueClickApp : public CWinApp
{
public:
	CBlueClickApp();

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

#endif // !defined(AFX_BLUECLICK_H__F1DB34CC_ADE0_425E_B4EE_6EBDE3495921__INCLUDED_)
