// bmpPicture.h: interface for the CbmpPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPPICTURE_H__19F0C118_9229_4DFF_BF92_5A0791573222__INCLUDED_)
#define AFX_BMPPICTURE_H__19F0C118_9229_4DFF_BF92_5A0791573222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
函数原型：BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest, 
	HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)；
参数：
hdcDest：指向目标设备环境的句柄。
nXOriginDest：指定目标矩形左上角的X轴坐标，坐标以逻辑单位表示。
nYOriginDest：指定目标矩形左上角的Y轴坐标，坐标以逻辑单位表示。
nWidthDest：指定目标矩形的宽度。
nHeightDest：指定目标矩形的高度。
hdcsrc：指向源设备环境的句柄。
nXOriginSrc：指定源矩形（左上角）的X轴坐标，坐标以逻辑单位表示。
nYOriginsrc：指定源矩形（左上角）的Y轴坐标，坐标以逻辑单位表示。
nWidthSrc：指定源矩形的宽度。
nHeightSrc：指定源矩形的高度。
crTransparent：源位图中的RGB值当作透明颜色。(用RGB(0,0,0)也就是黑色不行)返回值：如果函数执行成功，那么返回值为TRUE；如果函数执行失败，那么返回值为FALSE。
*/

#pragma comment(lib, "msimg32.lib")
//#pragma comment(lib, "lib/AtlImage.lib")


//typedef HBITMAP (*LoadAtlImageFunc)(const char *pStrFileName);

class CbmpPicture  
{
public:
	CBitmap * getBitmap();
	HBITMAP getHBitmap();
	BOOL loadBmpFromFile(CString &path);
	BOOL TansParentBlt(CDC &desDc, RECT rectPos, COLORREF color);
	BOOL PaintZoom(CDC &dc, RECT &rectPos);
	BOOL Paint(CDC &dc, const RECT &rcPos);
	BOOL loadBmpFromFile(char *path);
	bool loadBmpPicture(UINT resID);
	int getWidth();
	int getHeight();

	void unLoad();

	CbmpPicture();
	virtual ~CbmpPicture();
private:
	BITMAP Bitmap;
	CBitmap bmp;
	HBITMAP hBmp;
	int bmpWidth, bmpHeight;
};

#endif // !defined(AFX_BMPPICTURE_H__19F0C118_9229_4DFF_BF92_5A0791573222__INCLUDED_)
