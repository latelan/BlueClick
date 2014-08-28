// DlgResourceList.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgResourceList.h"
#include "BlueClickDlg.h"
#include "BuffreeMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgResourceList dialog


CDlgResourceList::CDlgResourceList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgResourceList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgResourceList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgResourceList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgResourceList)
	DDX_Control(pDX, IDC_LIST_RESOURCE, m_listResource);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgResourceList, CDialog)
	//{{AFX_MSG_MAP(CDlgResourceList)
	ON_COMMAND(ID_MENUITEM_START_DOWNLOAD, OnMenuitemStartDownload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgResourceList message handlers

BOOL CDlgResourceList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd *pParentWnd = GetParent();
	CRect parentRect;
	pParentWnd->GetClientRect(&parentRect);
	SetWindowPos(NULL, 0, 0, parentRect.Width(), parentRect.Height(), SWP_SHOWWINDOW); 
	
	CRect listRect;
	GetClientRect(&listRect);
	m_listResource.SetWindowPos(NULL, 0, 0, listRect.Width(), listRect.Height(), SWP_SHOWWINDOW); 
	
	m_listResource.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_FULLROWSELECT |
		LVS_EX_ONECLICKACTIVATE |LVS_EX_GRIDLINES | LVS_OWNERDRAWFIXED | LVS_EX_DOUBLEBUFFER);
	//设置资源列表视图行高，前提是需要设置自绘风格，即LVS_OWNERDRAWFIXED
	m_listResource.SetItemHeight(40);
	m_listResource.ModifyStyle( LVS_OWNERDRAWFIXED, 0, 0 );//去掉自绘风格
	m_listResource.SetColumnType(1, BUFFREE_COLUMN_ICON);//设置第二列显示图标
	//	m_listResource.SetColumnType(3, BUFFREE_COLUMN_PROGRESS);//设置第四列显示进度条
	m_listResource.SetRightMenuID(IDR_MENU_RESOURCE);
	
	
	//这块需要注意的是，第一列宽度设置为0，即不使用第一列，因为第一列不能设置居中对齐
	//并且通过GetClientRect()获取到的第一列宽度并不是真正的第一列宽度，而是整个列表的宽度
	m_listResource.InsertColumn(0, "第一列，已废弃", LVCFMT_LEFT, 0, 0);
	m_listResource.InsertColumn(1, "类型", LVCFMT_LEFT, 80, 1);//第二列
	m_listResource.InsertColumn(2, "文件名", LVCFMT_LEFT, 200, 2);
	m_listResource.InsertColumn(3, "时间", LVCFMT_LEFT, listRect.Width()-298, 3);//通过计算，使得最后一列刚好填满列表宽度
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgResourceList::PreTranslateMessage(MSG* pMsg) 
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
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgResourceList::OnMenuitemStartDownload() 
{
	// TODO: Add your command handler code here
	int nItem = m_listResource.GetNextItem(-1, LVNI_SELECTED);
	CString csFileType = m_listResource.GetItemText(nItem, 1);
	CString csFilename = m_listResource.GetItemText(nItem, 2);
	
	CBuffreeListCtrl *listDownload = &(((CBlueClickDlg*)(this->GetParent()->GetParent()))->m_dlgDownloadList.m_listDownload);
	
	int count = listDownload->GetItemCount();
	listDownload->InsertItem(count, "");
	listDownload->SetItemText(count, 1, csFileType);
	listDownload->SetItemText(count, 2, csFilename);
	listDownload->SetItemText(count, 3, "");
	listDownload->SetItemData(count, 0);
	
	CBuffreeMessageBox dlgMessage("已加入下载队列");
	dlgMessage.DoModal();
}
