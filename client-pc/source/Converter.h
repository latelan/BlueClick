// Converter.h: interface for the CConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONVERTER_H__5E164E93_A5B9_431F_A448_8161BC203E67__INCLUDED_)
#define AFX_CONVERTER_H__5E164E93_A5B9_431F_A448_8161BC203E67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConverter  
{
public:
	CConverter();
	virtual ~CConverter();
	static void ANSItoUTF8(CString &strAnsi);
	static void CConverter::UTF8toANSI(CString &strUTF8);
};

#endif // !defined(AFX_CONVERTER_H__5E164E93_A5B9_431F_A448_8161BC203E67__INCLUDED_)
