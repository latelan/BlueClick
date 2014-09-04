// bmpPicture.cpp: implementation of the CbmpPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bmpPicture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CbmpPicture::CbmpPicture()
{
	bmpHeight = bmpWidth = 0;
	hBmp = NULL;
}

CbmpPicture::~CbmpPicture()
{

}


void CbmpPicture::unLoad()
{
	bmp.DeleteObject();
	memset(&bmp, 0, sizeof(bmp));
}

int CbmpPicture::getHeight()
{
	return bmpHeight;
}

int CbmpPicture::getWidth()
{

	return bmpWidth;
}



bool CbmpPicture::loadBmpPicture(UINT resID)
{
	unLoad(); // 卸载已存在的位图资源

	if (! bmp.LoadBitmap(resID))
	{
		return false;
	}
	
	bmp.GetBitmap(&Bitmap);

	return true;
}


BOOL CbmpPicture::loadBmpFromFile(char *pFilePath)
{
	if (NULL == pFilePath)
	{
		return FALSE;
	}
/*	
	LoadAtlImageFunc LoadAtlImage = NULL;
	HINSTANCE hModule = ::LoadLibrary("lib/AtlImage.dll");

	if (!hModule) {
		AfxMessageBox("缺少动态链接库：AtlImage.dll");
		hModule = NULL;
	}

	LoadAtlImage = (LoadAtlImageFunc)::GetProcAddress(hModule, "LoadAtlImage");
	if (!LoadAtlImage) {
		AfxMessageBox("Function Miss: LoadAtlImage");
		LoadAtlImage = NULL;
	}

	hBmp = LoadAtlImage(pFilePath);
*/
	hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), pFilePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	if (NULL == hBmp)
	{
		return FALSE;
	}
	
	if ( ! bmp.Attach(hBmp) )
	{
		return FALSE;
	}
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);
	
	bmpWidth = bitmap.bmWidth;
	bmpHeight = bitmap.bmHeight;

	return TRUE;
}

BOOL CbmpPicture::Paint(CDC &dc, const RECT &rcPos)
{
	if (!bmp.GetSafeHandle()) //没加载或加载失败
	{
		return FALSE;
	}
	
	CDC compDc;
	compDc.CreateCompatibleDC(&dc);
	CBitmap *oldBmp = compDc.SelectObject(&bmp);
	dc.SetStretchBltMode(HALFTONE);
	
	if (!dc.BitBlt(rcPos.left, rcPos.top, rcPos.right - rcPos.left, rcPos.bottom - rcPos.top,
		&compDc, 0, 0, SRCCOPY) )
	{
		return FALSE;
	}
	compDc.SelectObject(oldBmp);
	return TRUE;
}

BOOL CbmpPicture::PaintZoom(CDC &dc, RECT &rectPos)
{
	if (!bmp.GetSafeHandle()) //没加载或加载失败
	{
		return FALSE;
	}
	
	CDC compDc;
	compDc.CreateCompatibleDC(&dc);
	CBitmap *oldBmp = compDc.SelectObject(&bmp);
	dc.SetStretchBltMode(HALFTONE);
	
	if (!dc.StretchBlt(rectPos.left, rectPos.top, rectPos.right - rectPos.left, rectPos.bottom - rectPos.top,
		&compDc, 0, 0, bmpWidth, bmpHeight, SRCCOPY) )
	{
		return FALSE;
	}
	compDc.SelectObject(oldBmp);
	return TRUE;
}

BOOL CbmpPicture::TansParentBlt(CDC &desDc, RECT rectPos, COLORREF color)
{
	if (!bmp.GetSafeHandle()) //没加载或加载失败
	{
		return FALSE;
	}
	
	CDC compDc;
	compDc.CreateCompatibleDC(&desDc);
	CBitmap *oldBmp = compDc.SelectObject(&bmp);
	compDc.SetStretchBltMode(HALFTONE);

	TransparentBlt(desDc.GetSafeHdc(), rectPos.left, rectPos.top, rectPos.right - rectPos.left, rectPos.bottom - rectPos.top,
				compDc.GetSafeHdc(), 0, 0, bmpWidth, bmpHeight, color);

	compDc.SelectObject(oldBmp);
	return TRUE;
}

BOOL CbmpPicture::loadBmpFromFile(CString &path)
{
	return loadBmpFromFile((LPSTR)(LPCTSTR)path);
}

HBITMAP CbmpPicture::getHBitmap()
{
	return hBmp;
}

CBitmap * CbmpPicture::getBitmap()
{
// 	return CBitmap::FromHandle(hBmp);
	return &bmp;
}
