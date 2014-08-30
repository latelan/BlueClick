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
	m_bStriped = FALSE;
	m_rightClickMenuID = BUFFREE_INVALID_MENUID;
	m_crNormalSingleText = RGB(100, 100, 100);
	m_crNormalDoubleText = RGB(100, 100, 100);
	m_crNormalSingleBg = RGB(255, 255, 255);
	m_crNormalDoubleBg = RGB(220, 230, 255);
	m_crSelectedSingleBg = RGB(200, 220, 255);
	m_crSelectedDoubleBg = RGB(150, 200, 255);
	m_crSelectedSingleText = RGB(255, 255, 255);
	m_crSelectedDoubleText = RGB(255, 255, 255);
	m_crProgress = RGB(35, 122, 174);
	m_crProgressBg = RGB(200, 220, 220);
	m_crProgressText = RGB(255, 255, 255);
	memset(m_columnType, 0, BUFFREE_MAX_COLUMN);
	m_typeSet = "text.txt|doc.doc|audio.mp3|image.jpg.bmp.png.gif.psd|video.mp4.avi.mkv.rmvb.flv.3gp|pack.zip.tar.7z.rar|";
}

CBuffreeListCtrl::~CBuffreeListCtrl()
{
}


BEGIN_MESSAGE_MAP(CBuffreeListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CBuffreeListCtrl)
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	ON_WM_NCCALCSIZE()
	ON_WM_MEASUREITEM_REFLECT()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_WM_PAINT()
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

void CBuffreeListCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    CRect rect;
    CRect headerRect;
    CDC menDC;//内存ID表   
    CBitmap memMap;

    GetClientRect(&rect);    
    GetDlgItem(0)->GetWindowRect(&headerRect);   
    menDC.CreateCompatibleDC(&dc);   
    memMap.CreateCompatibleBitmap(
        &dc,   
        rect.Width(),   
        rect.Height()); 
    menDC.SelectObject(&memMap);
    menDC.FillSolidRect(&rect,RGB(255,255,255));   

    //这一句是调用默认的OnPaint(),把图形画在内存DC表上   
    DefWindowProc(WM_PAINT,(WPARAM)menDC.m_hDC,(LPARAM)0);   
    
    //输出   
    dc.BitBlt(0,
        headerRect.Height(),   
        rect.Width(),   
        rect.Height(),   
        &menDC,   
        0,     
        headerRect.Height(),   
        SRCCOPY);   
    menDC.DeleteDC();
    memMap.DeleteObject();	
	// Do not call CListCtrl::OnPaint() for painting messages
}

BOOL CBuffreeListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
	//return CListCtrl::OnEraseBkgnd(pDC);
}

void CBuffreeListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcItem = lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	INT nItemID = lpDrawItemStruct->itemID;


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

void CBuffreeListCtrl::OnCustomDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	//获取列数，第一列废弃，有效列为1~m_columnCount
	m_columnCount = m_listHeader.GetItemCount();

	//draw each item.set txt color,bkcolor....
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;
 
	// First thing - check the draw stage. If it’s the control’s prepaint
	// stage, then tell Windows we want messages for every item.
 
	if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT) {
		*pResult = CDRF_NOTIFYITEMDRAW;
	} else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT) {
		// This is the notification message for an item.  We’ll request
		// notifications before each subitem’s prepaint stage.
  
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	} else if (pLVCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM)) {
		// This is the prepaint stage for a subitem. Here’s where we set the
		// item’s text and background colors. Our return value will tell
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here.

		int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);
		int nSubItem = pLVCD->iSubItem;

		COLORREF crText  = ::GetSysColor(COLOR_WINDOWFRAME);
		COLORREF crBkgnd = ::GetSysColor(COLOR_WINDOW);
  
		CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);

		if (GetItemState(nItem, LVIS_SELECTED)) {
			if (m_bStriped == TRUE && nItem % 2 == 0) {
				DrawText(nItem, nSubItem, pDC, m_crSelectedDoubleText, m_crSelectedDoubleBg);
			} else {
				DrawText(nItem, nSubItem, pDC, m_crSelectedSingleText, m_crSelectedSingleBg);			
			}
		}
		else {
			if (m_bStriped == TRUE && nItem % 2 == 0) {
				DrawText(nItem, nSubItem, pDC, m_crNormalDoubleText, m_crNormalDoubleBg);
			} else {
				DrawText(nItem, nSubItem, pDC, m_crNormalSingleText, m_crNormalSingleBg);			
			}
		}
		*pResult = CDRF_SKIPDEFAULT; // We’ve painted everything.
	}
}

void CBuffreeListCtrl::DrawText(int nItem, int nSubItem, CDC *pDC, COLORREF crText, COLORREF crBkgnd)
{
	ASSERT(pDC);

	CRect rect;
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);

	CBrush bgBrush(crBkgnd);
	pDC->FillRect(&rect, &bgBrush);

	CString csText = "";
	if (m_columnType[nSubItem] == BUFFREE_COLUMN_ICON) {
		csText = GetItemText(nItem, nSubItem);
		csText.MakeLower();
		int nRet = m_typeSet.Find(csText);
		csText = "";
		CString csIconPath;
		if (nRet == -1) {
			csIconPath = "./resource/theme/icon-other.bmp";	
		} else if (nRet >= m_typeSet.Find("pack")) {
			csIconPath = "./resource/theme/icon-pack.bmp";				
		} else if (nRet >= m_typeSet.Find("video")) {
			csIconPath = "./resource/theme/icon-video.bmp";			
		} else if (nRet >= m_typeSet.Find("image")) {
			csIconPath = "./resource/theme/icon-image.bmp";			
		} else if (nRet >= m_typeSet.Find("audio")) {
			csIconPath = "./resource/theme/icon-audio.bmp";			
		} else if (nRet >= m_typeSet.Find("doc")) {
			csIconPath = "./resource/theme/icon-doc.bmp";			
		} else if (nRet >= m_typeSet.Find("text")) {
			csIconPath = "./resource/theme/icon-text.bmp";				
		}

		HBITMAP hBmpIcon  = CBlueClickApp::LoadBmpFromFile(csIconPath);
		CBitmap bmpIcon;
		bmpIcon.Attach(hBmpIcon);
		BITMAP bmp;
		bmpIcon.GetBitmap(&bmp);
		CDC imageDC;
		imageDC.CreateCompatibleDC(pDC);
		imageDC.SelectObject(&bmpIcon);
		//设置图标宽度为列高的80%
		CRect iconRect = rect;
		iconRect.left += (rect.Width() - m_iItemHeight * 80 / 100) / 2;
		iconRect.top += (m_iItemHeight * 10 / 100);
		iconRect.right = iconRect.left + m_iItemHeight * 80 / 100;
		iconRect.bottom = iconRect.top + m_iItemHeight * 80 / 100;
		pDC->SetStretchBltMode(HALFTONE);
		//pDC->StretchBlt(iconRect.left, iconRect.top, 30, 30, &imageDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		TransparentBlt(pDC->m_hDC, iconRect.left, iconRect.top, 30, 30, imageDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));
		//imageDC.SelectObject(pOldImageBmp);
	} else if (m_columnType[nSubItem] == BUFFREE_COLUMN_PROGRESS) {
		int nProcess = GetItemData(nItem);

		//进度条高度为20， 长度为列宽的80%
		CRect procRect = rect;
		procRect.left += rect.Width() * 10 / 100;
		procRect.bottom -= (rect.Height() - 20) / 2;
		procRect.top += (rect.Height() - 20) / 2;
		procRect.right = procRect.left + (rect.Width() * 80 / 100) * nProcess / 100;
		CBrush brush(m_crProgress);
		pDC->FillRect(&procRect, &brush);

		CRect restRect = rect;
		restRect.left = procRect.right;
		restRect.bottom -= (rect.Height() - 20) / 2;
		restRect.top += (rect.Height() - 20) / 2;
		restRect.right = procRect.left + (rect.Width() * 80 / 100);
		CBrush bgBrush(m_crProgressBg);
		pDC->FillRect(&restRect, &bgBrush);
		
		csText.Format("%d%%", nProcess);
		pDC->SetTextColor(m_crProgressText);
	} else {
		csText = GetItemText(nItem, nSubItem);
		pDC->SetTextColor(crText);
	}
	
	if (!csText.IsEmpty()) {
		UINT nFormat;
		if (nSubItem == 0) {
			nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
		} else {
			nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
		}
		pDC->SetBkMode(TRANSPARENT);
		
		pDC->SetBkColor(crBkgnd);
		pDC->DrawText(csText, &rect, nFormat);
	}
}

void CBuffreeListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if( m_iItemHeight > 0 ) {
		lpMeasureItemStruct->itemHeight = m_iItemHeight;
	}
}

void CBuffreeListCtrl::SetItemHeight(int height)
{
	m_iItemHeight = height;
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;

	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void CBuffreeListCtrl::SetColumnType(int subItem, int type)
{
	m_columnType[subItem] = type;
}

void CBuffreeListCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (m_rightClickMenuID == BUFFREE_INVALID_MENUID || GetSelectedCount() <= 0) {
		return;
	}

	CMenu menu, *pPopup;
	menu.LoadMenu(m_rightClickMenuID);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint);
	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, GetParent());

	*pResult = 0;
}

void CBuffreeListCtrl::SetRightMenuID(int menuID)
{
	m_rightClickMenuID = menuID;
}
