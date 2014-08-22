// BlueClickDlg.h : header file
//

#if !defined(AFX_BLUECLICKDLG_H__CBBAC37B_0FC7_4D37_A4E2_3D344041D985__INCLUDED_)
#define AFX_BLUECLICKDLG_H__CBBAC37B_0FC7_4D37_A4E2_3D344041D985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAIN_WINDOW_WIDTH 502
#define MAIN_WINDOW_HEIGHT 337

#include "BmpPicture.h"
#include "AnimateButton.h"
#include "BuffreeListCtrl.h"

#define WM_SHOWTASK (WM_USER +1)

/////////////////////////////////////////////////////////////////////////////
// CBlueClickDlg dialog

class CBlueClickDlg : public CDialog
{
private:
	static int m_width, m_height;
	CbmpPicture		m_bmpBg;
	CAnimateButton	m_btnCancel;
	CAnimateButton	m_btnMin;
	CAnimateButton	m_btnMenu;
	CAnimateButton	m_btnTheme;
	CBuffreeListCtrl	m_listResource;

// Construction
public:
	void DeleteTray();
	void ToTray();
	int m_listItemHeight;
	CBlueClickDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBlueClickDlg)
	enum { IDD = IDD_BLUECLICK_DIALOG };
	CTreeCtrl	m_treeDownload;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlueClickDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBlueClickDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCancel();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnInsert();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg void OnMin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLUECLICKDLG_H__CBBAC37B_0FC7_4D37_A4E2_3D344041D985__INCLUDED_)
