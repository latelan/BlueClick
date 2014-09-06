// stdafx.cpp : source file that includes just the standard includes
//	BlueClick.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

__int64 CustomFileSeek (HANDLE hf, __int64 distance, DWORD MoveMethod)
{
	LARGE_INTEGER li;
	
	li.QuadPart = distance;
	
	li.LowPart = SetFilePointer (hf, li.LowPart, &li.HighPart, MoveMethod);
	
	if (li.LowPart ==-1 && GetLastError() != NO_ERROR)
	{
		li.QuadPart = -1;
	}
	
	return li.QuadPart;
}
