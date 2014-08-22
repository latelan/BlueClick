// BuffreeHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BuffreeHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuffreeHeaderCtrl

CBuffreeHeaderCtrl::CBuffreeHeaderCtrl()
{
	m_height = 25;
	m_bgColor = RGB(90, 90, 90);
	m_textColor = RGB(255, 255, 255);
	m_spColor = RGB(211, 211, 211);
	m_textFont.CreatePointFont(110, "Î¢ÈíÑÅºÚ");
	//m_textFont.CreateFont(22, 8, 0, 0, 550, 0, 0, 0, DEFAULT_CHARSET,
	//	OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Î¢ÈíÑÅºÚ");

}

CBuffreeHeaderCtrl::~CBuffreeHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CBuffreeHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CBuffreeHeaderCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuffreeHeaderCtrl message handlers

void CBuffreeHeaderCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rcRect;
	GetClientRect(&rcRect);

	dc.FillSolidRect(rcRect, m_bgColor);
	
	int nItems = GetItemCount();
	CRect rectItem;

	CPen pen(PS_SOLID, 1, m_spColor);
	CPen *pOldPen = dc.SelectObject(&pen);


	CFont *pOldFont = dc.SelectObject(&m_textFont);

	dc.SetTextColor(m_textColor);

	for (int i = 0; i < nItems; i++) {
		GetItemRect(i, &rectItem);
		rectItem.top += 2;
		rectItem.bottom += 2;
		dc.MoveTo(rectItem.right, rcRect.top);
		dc.LineTo(rectItem.right, rectItem.bottom);

		TCHAR buf[256];
		HD_ITEM hditem;
		
		hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		hditem.pszText = buf;
		hditem.cchTextMax = 255;
		GetItem(i, &hditem);

		UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_TOP | DT_CENTER | DT_END_ELLIPSIS;
		dc.DrawText(buf, &rectItem, uFormat);
	}

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldFont);

	// Do not call CHeaderCtrl::OnPaint() for painting messages
}

BOOL CBuffreeHeaderCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default

	return CHeaderCtrl::OnEraseBkgnd(pDC);
}

LRESULT CBuffreeHeaderCtrl::OnLayout(WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, wParam, lParam);
 
    HDLAYOUT& hdLayout = *reinterpret_cast<LPHDLAYOUT>(lParam);
    LPRECT lpRect = hdLayout.prc;
    LPWINDOWPOS lpWindowPos = hdLayout.pwpos;
 
    lpRect->top = lpWindowPos->cy = m_height;
 
    return lResult;
}

BOOL CBuffreeHeaderCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	// TODO: Add your specialized code here and/or call the base class

	NMHEADER * pNMHearder=(NMHEADER*)lParam;
	//ÍÏ¶¯ÏûÏ¢
	if ((pNMHearder->hdr.code==HDN_BEGINTRACKA)||(pNMHearder->hdr.code==HDN_BEGINTRACKW))
	{
		//½ûÖ¹ÍÏ¶¯
		*pLResult=TRUE;
		return TRUE;
	}

	return CHeaderCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}
