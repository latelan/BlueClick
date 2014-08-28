///////////////////////////////////////////////////////////////////////////
// CBuffreeTreeCtrl.cpp : Implementation of Class CBuffreeTreeCtrl
///////////////////////////////////////////////////////////////////////////
//
// Copyright(C) 2005 Jim Alsup  All rights reserved
//              email: ja.alsup@gmail.com
//
// License: This code is provided "as is" with no expressed or implied 
//          warranty. You may use, or derive works from this file without
//          any restrictions except those listed below.
//
//        - This original header must be kept in the derived work.
//
//        - If your derived work is distributed in any form, you must
//          notify the author via the email address above and provide a 
//          short description of the product and intended audience.  
//
//        - You may not sell this code or a derived version of it as part of 
//          a comercial code library. 
//
//        - Offering the author a free licensed copy of any end product 
//          using this code is not required, but does endear you with a 
//          bounty of good karma.
//
///////////////////////////////////////////////////////////////////////////

//
// This owner draw tree control allows for the creation of a tree control
// that loosely resembles the user interface used by Skype's main window.
//
// Beside demonstrating the basics of creating an ownerdrawn tree control,
// but more importantly, demonstrates gradient backgrounds fills, bitmap 
// backgrounds, flicker free drawing, and how to deal with these in a 
// scrollable and resizable dialog.
//
// The underlying gradient or bitmap image is sized according the natural
// size of the visible (on screen or not) tree data.  This can be more
// readily understood and seen by opening and collasping the tree leaf
// with a long text name.  Notice the bmp or gradient resizes to the
// actual screen content.  
//
// Version History
//
// Sept 1, 2005  1.0.0  Initial Version

#include "stdafx.h"
#include "BlueClick.h"
#include "BuffreeTreeCtrl.h"
//#include ".\CBuffreeTreeCtrl.h"

#define _OWNER_DRAWN 1  // Set to 0 to use Windows draw code.  


// Gradient Filling Helper Routine
void GradientFillRect( CDC *pDC, CRect &rect, COLORREF crGradientFrom, COLORREF crGradientTo, bool bVertGrad )
{
	TRIVERTEX        vert[2];
	GRADIENT_RECT    mesh;
	crGradientFrom = RGB(35, 122, 174);
	crGradientTo = RGB(35, 122, 174);

	vert[0].x      = rect.left;
	vert[0].y      = rect.top;
	vert[0].Alpha  = 0x0000;
	vert[0].Blue   = GetBValue(crGradientFrom) << 8;
	vert[0].Green  = GetGValue(crGradientFrom) << 8;
	vert[0].Red    = GetRValue(crGradientFrom) << 8;

	vert[1].x      = rect.right;
	vert[1].y      = rect.bottom; 
	vert[1].Alpha  = 0x0000;
	vert[1].Blue   = GetBValue(crGradientTo) << 8;
	vert[1].Green  = GetGValue(crGradientTo) << 8;
	vert[1].Red    = GetRValue(crGradientTo) << 8;

	mesh.UpperLeft  = 0;
	mesh.LowerRight = 1;
#if _MSC_VER >= 1300  // only VS7 and above has GradientFill as a pDC member
	pDC->GradientFill( vert, 2, &mesh, 1, bVertGrad ? GRADIENT_FILL_RECT_V : 
		GRADIENT_FILL_RECT_H );
#else
	GradientFill( pDC->m_hDC, vert, 2, &mesh, 1, bVertGrad ? GRADIENT_FILL_RECT_V : 
		GRADIENT_FILL_RECT_H );
#endif
}



// CTreeCtrlEx

IMPLEMENT_DYNAMIC(CBuffreeTreeCtrl, CTreeCtrl)

CBuffreeTreeCtrl::CBuffreeTreeCtrl()
{
	m_gradientBgSel = RGB( 0, 150, 200 );	//Blueish
	m_gradientBgFrom = RGB( 0, 150, 200 );	//White
	m_gradientBgTo = RGB( 0, 150, 200 );	//Light Greyish Blue
	m_crBg = RGB(255, 255, 255);
	m_bgMode = BK_MODE_FILL;
	m_bmpTreeTiled = false;
	m_bGradientHorz = true;

	CString treeOpenPath = "./resource/theme/tree-closed.bmp";
	HBITMAP hBmpTreeOpen = CBlueClickApp::LoadBmpFromFile(treeOpenPath);

	m_bmpTreeOpen.Attach(hBmpTreeOpen);
	m_bmpTreeClosed.Attach(hBmpTreeOpen);
   // VERIFY( m_bmpTreeClosed.LoadBitmap( IDB_TREE_CLOSED ) ) ; 
    //m_bmpTreeClosed.GetSafeHandle();
   // VERIFY( m_bmpTreeOpen.LoadBitmap( IDB_TREE_OPENED ) ) ; 
   // m_bmpTreeOpen.GetSafeHandle();
	m_icon = NULL;
	GetClientRect(&m_treeRect);
}


CBuffreeTreeCtrl::~CBuffreeTreeCtrl()
{
    if (m_bmpBg.GetSafeHandle())
        m_bmpBg.DeleteObject();
    if (m_bmpTreeClosed.GetSafeHandle())
        m_bmpTreeClosed.DeleteObject();
    if (m_bmpTreeOpen.GetSafeHandle())
        m_bmpTreeOpen.DeleteObject();
}


BEGIN_MESSAGE_MAP(CBuffreeTreeCtrl, CTreeCtrl)
	ON_WM_ERASEBKGND()
#if _OWNER_DRAWN
	ON_WM_PAINT()
#endif
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnTvnItemexpanding)
//	ON_WM_CREATE()
END_MESSAGE_MAP()



// CCBuffreeTreeCtrl message handlers


BOOL CBuffreeTreeCtrl::OnEraseBkgnd(CDC* pDC)
{
    // nothing to do here -- see OnPaint
	return TRUE;
}


#if _OWNER_DRAWN
void CBuffreeTreeCtrl::OnPaint()
{
	CPaintDC dc(this);	// Device context for painting
	CDC dcFlickerFree;			// Memory base device context for flicker free painting
	CBitmap bmpFlickerFree;		// The bitmap we paint into
	CBitmap *bmpOld;
	CFont font, *oldFont;
	CFont fontDC;
	int oldMode;

	CRect rcRect;
	GetClientRect(&rcRect);
	SCROLLINFO scrollInfo;
	// Determine window portal to draw into taking into account
	// scrolling position
	if ( GetScrollInfo( SB_HORZ, &scrollInfo, SIF_POS | SIF_RANGE ) )
	{
		m_offsetHorz = -scrollInfo.nPos;
		m_sizeHorz = max( scrollInfo.nMax+1, rcRect.Width());
	}
	else
	{
		m_offsetHorz = rcRect.left;
		m_sizeHorz = rcRect.Width();
	}
	if ( GetScrollInfo( SB_VERT, &scrollInfo, SIF_POS | SIF_RANGE ) )
	{
		if ( scrollInfo.nMin == 0 && scrollInfo.nMax == 100) 
			scrollInfo.nMax = 0;
		m_offsetVertical = -scrollInfo.nPos * GetItemHeight();
		m_sizeVertical = max( (scrollInfo.nMax+2)*((int)GetItemHeight()+1), rcRect.Height() );
	}
	else
	{
		m_offsetVertical = rcRect.top;
		m_sizeVertical = rcRect.Height();
	}

	// Create an offscreen dc to paint with (prevents flicker issues)
	dcFlickerFree.CreateCompatibleDC( &dc );
    bmpFlickerFree.CreateCompatibleBitmap( &dc, rcRect.Width(), rcRect.Height() );
    // Select the bitmap into the off-screen DC.
	bmpOld = (CBitmap *)dcFlickerFree.SelectObject( &bmpFlickerFree );
	// Default font in the DC is not the font used by 
	// the tree control, so grab it and select it in.
	font.CreatePointFont(120, "Î¢ÈíÑÅºÚ");//GetFont();
	oldFont = dcFlickerFree.SelectObject( &font );
	// We're going to draw text transparently
	oldMode = dcFlickerFree.SetBkMode( TRANSPARENT );

	DrawBackGround( &dcFlickerFree );
	DrawItems( &dcFlickerFree );

	// Now Blt the changes to the real device context - this prevents flicker.
	dc.BitBlt( rcRect.left, rcRect.top, rcRect.Width(), rcRect.Height(), &dcFlickerFree, 0, 0, SRCCOPY);

	dcFlickerFree.SelectObject( oldFont );
	dcFlickerFree.SetBkMode( oldMode );
	dcFlickerFree.SelectObject( bmpOld );
}
#endif

// Draw TreeCtrl Background - 
void CBuffreeTreeCtrl::DrawBackGround( CDC* pDC )
{
	CRect rcRect;
	GetClientRect(&rcRect);
	BkMode mode = m_bgMode;

	if ( mode == BK_MODE_BMP )
	{
		if ( !m_bmpBg.GetSafeHandle() )
			mode = BK_MODE_FILL;
	}
	if ( mode == BK_MODE_GRADIENT )
	{
		GradientFillRect( pDC, 
			CRect( m_offsetHorz, m_offsetVertical, m_sizeHorz + m_offsetHorz, m_sizeVertical + m_offsetVertical ), 
			m_gradientBgFrom, m_gradientBgTo, !m_bGradientHorz );
	}
	else if ( mode == BK_MODE_FILL )
		pDC->FillSolidRect( rcRect, m_crBg);
	else if ( mode == BK_MODE_BMP )
	{
		BITMAP bm;
		CDC dcMem;
	      
		VERIFY(m_bmpBg.GetObject(sizeof(bm), (LPVOID)&bm));
		dcMem.CreateCompatibleDC(NULL);
		CBitmap* bmpOld = (CBitmap*)dcMem.SelectObject( &m_bmpBg ); 
		
		if ( m_bmpTreeTiled ) 	// BitMap Tile Mode
		{
			for ( int y = 0; y <= (m_sizeVertical / bm.bmHeight); y++ )
			{
				for ( int x = 0; x <= (m_sizeHorz / bm.bmWidth); x++ )
				{
					pDC->BitBlt((x*bm.bmWidth) + m_offsetHorz, (y*bm.bmHeight) + m_offsetVertical,
						bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);
				}
			}
		}
		else  // BITMAP Stretch Mode
		{
			pDC->StretchBlt( m_offsetHorz, m_offsetVertical, m_sizeHorz, m_sizeVertical, 
				&dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY );
		}
		// CleanUp
		dcMem.SelectObject( bmpOld );
	}
	else
		ASSERT( 0 );  // Unknown BackGround Mode
}



// Draw TreeCtrl Items
void CBuffreeTreeCtrl::DrawItems( CDC *pDC )
{
	// draw items
	HTREEITEM showItem, parent;
	CRect rcItem;
	CString name;
	COLORREF color;
	DWORD treeStyle;
	BITMAP bm;
	CDC dcMem;
	CBitmap *button;
	CRect rect;
	int count = 0;
	int state;
	bool bbSelected;
	bool bHasChildren;

	showItem = GetFirstVisibleItem();
	if ( showItem == NULL )
		return;

	dcMem.CreateCompatibleDC(NULL);
	color = pDC->GetTextColor();
	treeStyle = ::GetWindowLong( m_hWnd, GWL_STYLE ); 

	do
	{
		state = GetItemState( showItem, TVIF_STATE );
		parent = GetParentItem( showItem );
		bHasChildren = ItemHasChildren( showItem ) || parent == NULL;
		bbSelected = (state & TVIS_SELECTED) && ((this == GetFocus()) || 
				(treeStyle & TVS_SHOWSELALWAYS));

		if ( GetItemRect( showItem, rcItem, TRUE ) )
		{
			rcItem.right = m_sizeHorz + m_offsetHorz; //À©Õ¹Ñ¡È¡
			
			if (bbSelected )
			{
				COLORREF from;

				// Show
				if ( bbSelected )
					from = m_gradientBgSel;
				else
					from = m_gradientBgTo - (m_gradientBgFrom - m_gradientBgTo);
				rect.top = rcItem.top;
				rect.bottom = rcItem.bottom;
				rect.right = m_sizeHorz + m_offsetHorz;
				if ( !bHasChildren )
					rect.left = m_offsetHorz;
				else
					rect.left = m_offsetHorz;
				GradientFillRect( pDC, rect, from, m_gradientBgTo, FALSE );
				pDC->SetTextColor( RGB( 0, 0, 255 ) );

				if ( bHasChildren )
				{
				/*	//»æÖÆÕÛµþÍ¼±ê
					// Draw an Open/Close button
					if ( state & TVIS_EXPANDED )
						button = &m_bmpTreeOpen;
					else
						button = &m_bmpTreeClosed;
					VERIFY(button->GetObject(sizeof(bm), (LPVOID)&bm));
					CBitmap *bmpOld = (CBitmap*)dcMem.SelectObject(button); 
					pDC->BitBlt( rcItem.left, rcItem.top+6, bm.bmWidth, bm.bmHeight, 
						&dcMem, 0, 0, SRCAND );
					// CleanUp
					dcMem.SelectObject( bmpOld );
					*/
				}
			}
			if ( !bHasChildren )
			{
				// lookup the ICON instance (if any) and draw it
				HICON icon;
				icon = GetItemIcon( showItem );
				if ( icon != NULL )
					DrawIconEx( pDC->m_hDC, rcItem.left - 18, rcItem.top, icon, 16, 16,0,0, DI_NORMAL );
			}
			name = GetItemText( showItem );
			rcItem.DeflateRect( 0,1,0,1 );
			if ( bbSelected )
			{
			//	if ( !bHasChildren  )
					pDC->SetTextColor( GetSysColor(COLOR_HIGHLIGHTTEXT) );
				COLORREF col = pDC->GetBkColor();
			//	pDC->SetBkColor( RGB(100, 100, 100));//GetSysColor(COLOR_HIGHLIGHT) );
				pDC->DrawText( name, rcItem, DT_LEFT );
				pDC->SetTextColor( color );
			//	pDC->SetBkColor( col );
			}
			else
			{
				pDC->DrawText( name, rcItem, DT_LEFT );
				pDC->SetTextColor( color );
				COLORREF col = pDC->GetBkColor();
			//	pDC->SetBkColor( RGB(0, 0, 0));//GetSysColor(COLOR_HIGHLIGHT) );
				pDC->DrawText( name, rcItem, DT_LEFT );
				pDC->SetTextColor( color );
			//	pDC->SetBkColor( col );
			//	pDC->SetBkColor( RGB(0, 0, 0));//GetSysColor(COLOR_HIGHLIGHT) );
			}
			//if ( state & TVIS_BOLD )
			//	pDC->SelectObject( font );
		}
	} while ( (showItem = GetNextVisibleItem( showItem )) != NULL );
}



void CBuffreeTreeCtrl::SetBitmapID( UINT id )
{
	// delete any existing bitmap
    if (m_bmpBg.GetSafeHandle())
        m_bmpBg.DeleteObject();
	// add in the new bitmap
    VERIFY( m_bmpBg.LoadBitmap( id ) ) ; 
    m_bmpBg.GetSafeHandle();
}



// Determine if a referenced item is visible within the control window
bool CBuffreeTreeCtrl::ItemIsVisible( HTREEITEM item )
{
	HTREEITEM scan_item;
	scan_item = GetFirstVisibleItem();
	while ( scan_item != NULL )
	{
		if ( item == scan_item )
			return true;
		scan_item = GetNextVisibleItem( scan_item );
	}
	return false;
}


// For a given tree node return an ICON for display on the left side.
// This default implementation only returns one icon.
// This function is virtual and meant to be overriden by deriving a class
// from CBuffreeTreeCtrl and supplying your own icon images. 
HICON CBuffreeTreeCtrl::GetItemIcon( HTREEITEM item )		
{
	return m_icon;  // default implementation - overridable
}


// If the background is a bitmap, and a tree is expanded/collapsed we
// need to redraw the entire background because windows moves the bitmap
// up (on collapse) destroying the position of the background.
void CBuffreeTreeCtrl::OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	if ( GetBkMode() == CBuffreeTreeCtrl::BK_MODE_BMP && ItemIsVisible( pNMTreeView->itemNew.hItem ) )
		Invalidate();  // redraw everything
	*pResult = 0;
}




