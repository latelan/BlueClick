// BuffreeListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "BuffreeListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuffreeListCtrl

CBuffreeListCtrl::CBuffreeListCtrl()
{
}

CBuffreeListCtrl::~CBuffreeListCtrl()
{
}


BEGIN_MESSAGE_MAP(CBuffreeListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CBuffreeListCtrl)
	ON_WM_DRAWITEM()
	ON_WM_NCCALCSIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuffreeListCtrl message handlers

void CBuffreeListCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (GetHeaderCtrl()) {
		CHeaderCtrl *listHeader = GetHeaderCtrl();
		m_listHeader.SubclassWindow(listHeader->GetSafeHwnd());
//		m_listHeader.EnableWindow(false);
//		m_SkinHeaderCtrl.Subclass
	}

	CListCtrl::PreSubclassWindow();
}

void CBuffreeListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcItem = lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	INT nItemID = lpDrawItemStruct->itemID;
	INT nColumnCount = m_listHeader.GetItemCount();

	CRect rcClipBox;

	CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CBuffreeListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// TODO: Add your message handler code here and/or call default
    ModifyStyle( WS_HSCROLL | WS_VSCROLL, 0 ); // 去掉水平滚动条和竖直滚动条                   
    CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);  	
	
	InitializeFlatSB(this->m_hWnd);                                                 
    FlatSB_EnableScrollBar(this->m_hWnd, SB_BOTH, ESB_DISABLE_BOTH); 
	
	CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}
