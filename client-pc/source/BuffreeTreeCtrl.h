///////////////////////////////////////////////////////////////////////////
// CBuffreeTreeCtrl.h : Definition of Class CBuffreeTreeCtrl
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

#pragma once

#include "resource.h"


// Helper Routine
extern void GradientFillRect( CDC *pDC, CRect &rect, COLORREF col_from, COLORREF col_to, bool vert_grad );


class CBuffreeTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CBuffreeTreeCtrl)

public:
	int m_crBg;
	CBuffreeTreeCtrl();
	virtual ~CBuffreeTreeCtrl();

// Attributes
	void SetBkGradients( COLORREF from, COLORREF to ){	m_gradientBgFrom = from; 
	                                                    m_gradientBgTo = to; }
	COLORREF GetBkGradientFrom( ){	return m_gradientBgFrom; }
	COLORREF GetBkGradientTo( ){ return m_gradientBgTo; }

	enum BkMode { BK_MODE_BMP = 0, BK_MODE_GRADIENT, BK_MODE_FILL };
	BkMode GetBkMode( ) { return m_bgMode; }
	void SetBkMode( BkMode bkgd_mode ) { m_bgMode = bkgd_mode; }

	bool GetBitmapTiledMode() { return m_bmpTreeTiled;}
	void SetBitmapTiledMode( bool tiled ) {	m_bmpTreeTiled = tiled; }
	void SetBitmapID( UINT id );

	bool GetGradientHorz() { return m_bGradientHorz; }
	void SetGradientHorz( bool horz ) { m_bGradientHorz = horz; } 

	
	virtual void  SetItemIcon( HICON icon ) { m_icon = icon; }; // Overridable
	virtual HICON GetItemIcon( HTREEITEM item ); // Overridable

// Operations
	bool ItemIsVisible( HTREEITEM item );


private:
	COLORREF m_gradientBgFrom;		// Gradient variables
	COLORREF m_gradientBgTo;
	COLORREF m_gradientBgSel;
	bool     m_bGradientHorz;			// horz or vertical gradient

	BkMode  m_bgMode;				// Current Background mode
    CBitmap m_bmpBg;			// Background bitmap image
	CBitmap m_bmpTreeClosed;			// Tree open image (marker)
	CBitmap m_bmpTreeOpen;			// Tree closed image (marker)
	bool    m_bmpTreeTiled;			// Tile background image

	int   m_offsetHorz;					// 0... -x (scroll offset)
	int   m_sizeHorz;						// width of unclipped window
	int   m_offsetVertical;					// 0... -y (scroll offset)
	int   m_sizeVertical;						// height of unclipped window
	CRect m_treeRect;

	HICON m_icon;

	void DrawBackGround( CDC* pDC );	// Background Paint code
	void DrawItems( CDC* pDC );  // Item Paint Code

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};


