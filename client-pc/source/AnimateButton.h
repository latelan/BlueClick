/***************************************************************************/
/*                        类名：CAnimateButton                             */
/*				 	   (C)CopyRight www.cguage.com		     			   */
/***************************************************************************/

/////////////////////////////////////////////////////////////////////////////
//基类：CButton
//功能：1、从资源或者外部导入图片，抠除mask色，实现按钮异形;
//		2、支持按钮3态、4态、5态，支持文字在按钮下方、右方,支持动态创建;
//		3、实现按钮的透明渐变效果;
//		4、3D按钮文字效果;
//		5、按钮Hover、点击声音效果;
//		6、设置按钮鼠标光标;
//		7、得到按钮左上角位置.
//作者：C瓜哥
//		blog:	www.cguage.com 
//		Email:	tangcraig@gmail.com 
//		QQ:		1019714877
//版本：
//		V1.0(2010年6月14日22:16:59)
//		v1.1(2010年7月26日12:33:02) 
//			优化了透明异形图的做法，增加实现了得到焦点状态，增加了增加了文字可以在
//			按钮外面的属性，增加了动态创建功能等
//主要方法：
//		见下
//注意:	按钮各状态在一张图片上，且每状态的宽度应一致，各状态顺序：Normal、
//		Hovered、Pressed、(Focused、disabled) 最后两个为可选, LoadBitmap的时
//		候要指定后两状态的有无(默认为5态按钮)		
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ANIMATEBUTTON_H__FDD30F99_A0DC_4004_9A70_DA0F83338D28__INCLUDED_)
#define AFX_ANIMATEBUTTON_H__FDD30F99_A0DC_4004_9A70_DA0F83338D28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimateButton.h : header file
//

#include <afxtempl.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

enum 
{
	TEXT3D_NONE,	//无3D效果
	TEXT3D_STROKE,	//描边
	TEXT3D_SHADOW,	//阴影
	TXTPOS_IN = 1,	//字在按钮图像内
	TXTPOS_DOWN,	//字在按钮下方
	TXTPOS_RIGHT	//字在按钮右方
};

struct AnibtnTextOpinion
{
	int nPosition;			//文字所处区域(内部、下面、右边?)
	int nDistance;			//下方、右方文字与按钮图片的距离(文字在内部时,此标志位无效)
	UINT nFormat;			//文字对齐方式(和CDC::DrawText中的nFormat一个含义)
	LOGFONT* pLf;			//存放字体信息
//	CFont* pFont;			//字体
	COLORREF clrText;		//文字颜色
	COLORREF clrTextHovered;//Hover下文字颜色
	UINT n3DStyle;			//3D效果种类(可合成)
	COLORREF clrBorder;		//描边颜色(如果n3DStyle中无TEXT3D_STROKE,将忽略此参数)
	UINT nBorderThickness;	//边缘厚度(如果n3DStyle中无TEXT3D_STROKE,将忽略此参数)
	UINT nOffsetShadow;		//阴影距离(如果n3DStyle中无TEXT3D_SHADOW,将忽略此参数)

	AnibtnTextOpinion()
	{
		nPosition = TXTPOS_IN;
		nDistance = 5;
		nFormat = 37;//即DT_SINGLELINE | DT_CENTER | DT_VCENTER
		pLf = NULL;
//		pFont = NULL;
		clrText = 0;
		clrTextHovered = clrText;
		n3DStyle = TEXT3D_NONE;
		clrBorder = 0;
		nBorderThickness = 1;
		nOffsetShadow = 2;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CAnimateButton window

class CAnimateButton : public CButton
{
// Construction
public:
	CAnimateButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimateButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint GetWindowPos();													//取得按钮位置(left, top)
	BOOL Create(DWORD dwStyle,const POINT& pos, CWnd* pParentWnd, UINT nID);//动态创建,pos:按钮位置,注:按钮大小依图像大小而定
	void SetBtnText(LPCTSTR lpszString);									//设置按钮文字
	void SetBtnText(LPCTSTR lpszString, AnibtnTextOpinion ato);				//设置按钮文字,ato:字体样式struct AnibtnTextOpinion
	void SetCursor(LPCTSTR lpszAniCur);										//设置光标,lpszAniCur光标资源文件(*.cur、*.ani)
	void SetCursor(UINT nIDCursor);											//设置光标,nIDCursor光标资源ID
	//导入图像,各参数:图片文件名、透明色、是否有得到焦点状态、是否有失效状态
	BOOL LoadBitmap(CString szFileName, COLORREF clrTrans = RGB(255, 0, 255));
	//导入图像,各参数:图片资源ID、透明色、是否有得到焦点状态、是否有失效状态
	BOOL LoadBitmap(UINT nIDBmp, COLORREF clrTrans = RGB(255, 0, 255));		
	virtual ~CAnimateButton();

	// Generated message map functions
protected:
	void DrawBtnText(CDC* pDC);
	void AlphaBitmap(int nItem);
	//{{AFX_MSG(CAnimateButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
		
	HRGN BitmapToRegion(HBITMAP hBmp, int nSplit, int n, COLORREF cTransparentColor, COLORREF);
	void PrepareBitmap(HBITMAP hBitmap);

private:
	int m_aniBtnHeight;
	int m_aniBtnWidth;
	int m_aniBtnState;
	CBrush m_brushNull;
	CFont m_fontTxt;
	CRect m_rcTextBox;
	AnibtnTextOpinion m_ato;
	COLORREF m_clrTrans;
	CArray<HRGN, HRGN> m_arBmpRgn;
	CString m_strSndClick;
	CString m_strSndHover;
	UINT m_nIDSndClick;
	UINT m_nIDSndHover;
	CString m_strBtnText;
	HCURSOR m_hCursor;
	BOOL m_bEnable;
	int m_nTrans;
	BLENDFUNCTION m_bf;
	BOOL m_bAllowTrack;
	CDC* m_pMemDC;
 	enum 
	{
		TIMER_ELAPSE = 15,		//TIMER时间
		TRANS_INCREMENT = 10,	//每一次的透明度增加量
		STATE_NORMAL = 0,		//按钮普通状态
		STATE_HOVERED,			//鼠标进入按钮状态
		STATE_PRESSED,			//按钮被按下的状态
		STATE_DISABLED,			//按钮失效状态
		STATE_FOCUSED,			//按钮得到焦点状态
	};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATEBUTTON_H__FDD30F99_A0DC_4004_9A70_DA0F83338D28__INCLUDED_)
