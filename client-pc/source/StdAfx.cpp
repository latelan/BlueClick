// stdafx.cpp : source file that includes just the standard includes
//	BlueClick.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

HBITMAP LoadBmpFromFile(CString &bmpPath)
{
	return (HBITMAP)::LoadImage(NULL, bmpPath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
}	


