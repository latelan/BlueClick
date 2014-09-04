// TransStatic.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "TransStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransStatic

CTransStatic::CTransStatic()
{
	m_iTextColor = RGB(255, 255, 255);
}

CTransStatic::~CTransStatic()
{
}


BEGIN_MESSAGE_MAP(CTransStatic, CStatic)
	//{{AFX_MSG_MAP(CTransStatic)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransStatic message handlers

BOOL CTransStatic::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default

//	Invalidate(TRUE);

	return TRUE;
	//return CStatic::OnEraseBkgnd(pDC);
}

HBRUSH CTransStatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

HBRUSH CTransStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT); //设备背景透明模式
		pDC->SetTextColor(m_iTextColor); //设置控件中显示的文本颜色
	}

//	HBRUSH hBr = CreateSolidBrush(RGB(255, 255, 255));

//	return hBr;
	return (HBRUSH)GetStockObject(NULL_BRUSH);	
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
}
