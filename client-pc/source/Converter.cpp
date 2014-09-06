// Converter.cpp: implementation of the CConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BlueClick.h"
#include "Converter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConverter::CConverter()
{

}

CConverter::~CConverter()
{

}

/*********************************************************
函数名称：ANSItoUTF8
功能描述：ANSI字符串转化UTF8编码
作者：	  张永军
引用：    软件架构农 http://blog.csdn.net/charlessimonyi/article/details/8722859
创建时间：2014-08-30
参数说明：strAnsi：需要转换的字符串，同时用来接收转换结果
返 回 值：无
*********************************************************/
void CConverter::ANSItoUTF8(CString &strAnsi)
{
    //获取转换为宽字节后需要的缓冲区大小，创建宽字节缓冲区，936为简体中文GB2312代码页
    UINT nLen = MultiByteToWideChar(936,NULL,strAnsi,-1,NULL,NULL);
    WCHAR *wszBuffer = new WCHAR[nLen+1];
    nLen = MultiByteToWideChar(936,NULL,strAnsi,-1,wszBuffer,nLen);
    wszBuffer[nLen] = 0;
    //获取转为UTF8多字节后需要的缓冲区大小，创建多字节缓冲区
    nLen = WideCharToMultiByte(CP_UTF8,NULL,wszBuffer,-1,NULL,NULL,NULL,NULL);
    CHAR *szBuffer = new CHAR[nLen+1];
    nLen = WideCharToMultiByte(CP_UTF8,NULL,wszBuffer,-1,szBuffer,nLen,NULL,NULL);
    szBuffer[nLen] = 0;

    strAnsi = szBuffer;
    //内存清理
    delete []wszBuffer;
    delete []szBuffer;
}

/*********************************************************
函数名称：UTF8toANSI
功能描述：UTF8字符串转化编码ANSI
作者：	  张永军
引用：    软件架构农 http://blog.csdn.net/charlessimonyi/article/details/8722859
创建时间：2014-08-30
参数说明：strUTF8：需要转换的字符串，同时用来接收转换结果
返 回 值：无
*********************************************************/
void CConverter::UTF8toANSI(CString &strUTF8)
{
    //获取转换为多字节后需要的缓冲区大小，创建多字节缓冲区
    UINT nLen = MultiByteToWideChar(CP_UTF8,NULL,strUTF8,-1,NULL,NULL);
    WCHAR *wszBuffer = new WCHAR[nLen+1];
    nLen = MultiByteToWideChar(CP_UTF8,NULL,strUTF8,-1,wszBuffer,nLen);
    wszBuffer[nLen] = 0;

    nLen = WideCharToMultiByte(936,NULL,wszBuffer,-1,NULL,NULL,NULL,NULL);
    CHAR *szBuffer = new CHAR[nLen+1];
    nLen = WideCharToMultiByte(936,NULL,wszBuffer,-1,szBuffer,nLen,NULL,NULL);
    szBuffer[nLen] = 0;

    strUTF8 = szBuffer;
    //清理内存
    delete []szBuffer;
    delete []wszBuffer;
}