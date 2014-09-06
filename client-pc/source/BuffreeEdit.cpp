// BuffreeEdit.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BuffreeEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuffreeEdit

// VEdit.cpp : implementation file
//

CBuffreeEdit::CBuffreeEdit() 
	: m_rectNCBottom(0, 0, 0, 0)
	, m_rectNCTop(0, 0, 0, 0)
{
}

CBuffreeEdit::~CBuffreeEdit()
{
}


BEGIN_MESSAGE_MAP(CBuffreeEdit, CEdit)
	//{{AFX_MSG_MAP(CBuffreeEdit)
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuffreeEdit message handlers

void CBuffreeEdit::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CRect rectWnd, rectClient;
	
	//calculate client area height needed for a font
	CFont *pFont = GetFont();
	CRect rectText;
	rectText.SetRectEmpty();
	
	CDC *pDC = GetDC();
	
	CFont *pOld = pDC->SelectObject(pFont);
	pDC->DrawText("Ky", rectText, DT_CALCRECT | DT_LEFT);
	UINT uiVClientHeight = rectText.Height();
	
	pDC->SelectObject(pOld);
	ReleaseDC(pDC);
	
	//calculate NC area to center text.
	
	GetClientRect(rectClient);
	GetWindowRect(rectWnd);

	ClientToScreen(rectClient);

	UINT uiCenterOffset = (rectClient.Height() - uiVClientHeight) / 2;
	UINT uiCY = (rectWnd.Height() - rectClient.Height()) / 2;
	UINT uiCX = (rectWnd.Width() - rectClient.Width()) / 2;

	rectWnd.OffsetRect(-rectWnd.left, -rectWnd.top);
	m_rectNCTop = rectWnd;

	m_rectNCTop.DeflateRect(uiCX, uiCY, uiCX, uiCenterOffset + uiVClientHeight + uiCY);

	m_rectNCBottom = rectWnd;

	m_rectNCBottom.DeflateRect(uiCX, uiCenterOffset + uiVClientHeight + uiCY, uiCX, uiCY);

	lpncsp->rgrc[0].top +=uiCenterOffset;
	lpncsp->rgrc[0].bottom -= uiCenterOffset;

	lpncsp->rgrc[0].left +=uiCX;
	lpncsp->rgrc[0].right -= uiCY;

}

void CBuffreeEdit::OnNcPaint() 
{
	Default();

	CWindowDC dc(this);
	CBrush Brush(GetSysColor(COLOR_WINDOW));

	dc.FillRect(m_rectNCBottom, &Brush);
	dc.FillRect(m_rectNCTop, &Brush);
}

HBRUSH CBuffreeEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	if(m_rectNCTop.IsRectEmpty())
	{
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
	}
	
	return NULL;
}
