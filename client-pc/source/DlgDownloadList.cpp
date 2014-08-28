// DlgDownloadList.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgDownloadList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDownloadList dialog


CDlgDownloadList::CDlgDownloadList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDownloadList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDownloadList)
	//}}AFX_DATA_INIT
}


void CDlgDownloadList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDownloadList)
	DDX_Control(pDX, IDC_LIST_UPLOAD, m_listDownload);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDownloadList, CDialog)
	//{{AFX_MSG_MAP(CDlgDownloadList)
	ON_COMMAND(ID_MENUITEM_CONTINUE_DOWNLOAD, OnMenuitemContinueDownload)
	ON_COMMAND(ID_MENUITEM_PAUSE_DOWNLOAD, OnMenuitemPauseDownload)
	ON_COMMAND(ID_MENUITEM_DELETE_DOWNLOAD, OnMenuitemDeleteDownload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDownloadList message handlers

BOOL CDlgDownloadList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd *pParentWnd = GetParent();
	CRect parentRect;
	pParentWnd->GetClientRect(&parentRect);
	SetWindowPos(NULL, 0, 0, parentRect.Width(), parentRect.Height(), SWP_SHOWWINDOW); 
	
	CRect listRect;
	GetClientRect(&listRect);
	m_listDownload.SetWindowPos(NULL, 0, 0, listRect.Width(), listRect.Height(), SWP_SHOWWINDOW); 
	
	m_listDownload.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_FULLROWSELECT |
		LVS_EX_ONECLICKACTIVATE |LVS_EX_GRIDLINES | LVS_OWNERDRAWFIXED );
	//设置资源列表视图行高，前提是需要设置自绘风格，即LVS_OWNERDRAWFIXED
	m_listDownload.SetItemHeight(40);
	m_listDownload.ModifyStyle( LVS_OWNERDRAWFIXED, 0, 0 );//去掉自绘风格
	m_listDownload.SetColumnType(1, BUFFREE_COLUMN_ICON);//设置第二列显示图标
	m_listDownload.SetColumnType(3, BUFFREE_COLUMN_PROGRESS);//设置第四列显示进度条
	m_listDownload.SetRightMenuID(IDR_MENU_DOWNLOAD);
	
	//这块需要注意的是，第一列宽度设置为0，即不使用第一列，因为第一列不能设置居中对齐
	//并且通过GetClientRect()获取到的第一列宽度并不是真正的第一列宽度，而是整个列表的宽度
	m_listDownload.InsertColumn(0, "第一列，已废弃", LVCFMT_LEFT, 0, 0);
	m_listDownload.InsertColumn(1, "类型", LVCFMT_LEFT, 80, 1);//第二列
	m_listDownload.InsertColumn(2, "文件名", LVCFMT_LEFT, 200, 2);
	m_listDownload.InsertColumn(3, "进度", LVCFMT_LEFT, listRect.Width()-298, 3);//通过计算，使得最后一列刚好填满列表宽度
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgDownloadList::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN) {  
        if(pMsg->wParam == VK_ESCAPE) {  
            return true;  
        }
		if(pMsg->wParam == VK_RETURN) {  
            return true;  
        }  
    }	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgDownloadList::OnMenuitemContinueDownload() 
{
	// TODO: Add your command handler code here
	
}

void CDlgDownloadList::OnMenuitemPauseDownload() 
{
	// TODO: Add your command handler code here
	
}

void CDlgDownloadList::OnMenuitemDeleteDownload() 
{
	// TODO: Add your command handler code here
	int nItem = m_listDownload.GetNextItem(-1, LVNI_SELECTED);
	m_listDownload.DeleteItem(nItem);
	
	UpdateData(TRUE);	
}
