// DlgUploadList.cpp : implementation file
//

#include "stdafx.h"
#include "BlueClick.h"
#include "DlgUploadList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUploadList dialog


CDlgUploadList::CDlgUploadList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUploadList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUploadList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgUploadList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUploadList)
	DDX_Control(pDX, IDC_LIST_UPLOAD, m_listUpload);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUploadList, CDialog)
	//{{AFX_MSG_MAP(CDlgUploadList)
	ON_COMMAND(ID_MENUITEM_NEW_SHARE, OnMenuitemNewShare)
	ON_COMMAND(ID_MENUITEM_DELETE_SHARE, OnMenuitemDeleteShare)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUploadList message handlers

BOOL CDlgUploadList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd *pParentWnd = GetParent();
	CRect parentRect;
	pParentWnd->GetClientRect(&parentRect);
	SetWindowPos(NULL, 0, 0, parentRect.Width(), parentRect.Height(), SWP_SHOWWINDOW); 
	
	CRect listRect;
	GetClientRect(&listRect);
	m_listUpload.SetWindowPos(NULL, 0, 0, listRect.Width(), listRect.Height(), SWP_SHOWWINDOW); 
	
	m_listUpload.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_FULLROWSELECT |
		LVS_EX_ONECLICKACTIVATE |LVS_EX_GRIDLINES | LVS_OWNERDRAWFIXED );
	//设置资源列表视图行高，前提是需要设置自绘风格，即LVS_OWNERDRAWFIXED
	m_listUpload.SetItemHeight(40);
	m_listUpload.ModifyStyle( LVS_OWNERDRAWFIXED, 0, 0 );//去掉自绘风格
	m_listUpload.SetColumnType(1, BUFFREE_COLUMN_ICON);//设置第二列显示图标
	m_listUpload.SetColumnType(3, BUFFREE_COLUMN_PROGRESS);//设置第四列显示进度条
	m_listUpload.SetRightMenuID(IDR_MENU_UPLOAD);//设置右键菜单
	
	//这块需要注意的是，第一列宽度设置为0，即不使用第一列，因为第一列不能设置居中对齐
	//并且通过GetClientRect()获取到的第一列宽度并不是真正的第一列宽度，而是整个列表的宽度
	m_listUpload.InsertColumn(0, "第一列，已废弃", LVCFMT_LEFT, 0, 0);
	m_listUpload.InsertColumn(1, "类型", LVCFMT_LEFT, 80, 1);//第二列
	m_listUpload.InsertColumn(2, "文件名", LVCFMT_LEFT, 200, 2);
	m_listUpload.InsertColumn(3, "进度", LVCFMT_LEFT, listRect.Width()-298, 3);//通过计算，使得最后一列刚好填满列表宽度
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgUploadList::PreTranslateMessage(MSG* pMsg) 
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

void CDlgUploadList::OnMenuitemNewShare() 
{
	// TODO: Add your command handler code here
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "ALL Files(*.*)|*.*||", AfxGetMainWnd());
	
	if (dlgFile.DoModal() == IDOK) {
		CString csFileType = dlgFile.GetFileExt();
		CString csFilename = dlgFile.GetFileName();
		int count = m_listUpload.GetItemCount();
		m_listUpload.InsertItem(count, "");
		m_listUpload.SetItemText(count, 1, "rmvb");
		m_listUpload.SetItemText(count, 2, csFilename);
		m_listUpload.SetItemText(count, 3, "");
		m_listUpload.SetItemData(count, 0);
		//	UpdateData(FALSE);
	}	
}

void CDlgUploadList::OnMenuitemDeleteShare() 
{
	// TODO: Add your command handler code here
	int nItem = m_listUpload.GetNextItem(-1, LVNI_SELECTED);
	m_listUpload.DeleteItem(nItem);
	
	UpdateData(TRUE);	
}
