#if !defined(AFX_DLGTHEMESELECTER_H__162FC162_416B_4441_849A_240C22E23BB0__INCLUDED_)
#define AFX_DLGTHEMESELECTER_H__162FC162_416B_4441_849A_240C22E23BB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgThemeSelecter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgThemeSelecter dialog

class CDlgThemeSelecter : public CDialog
{
// Construction
public:
	CDlgThemeSelecter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgThemeSelecter)
	enum { IDD = IDD_DLGTHEMESELECTER_DIALOG };
	CStatic	m_staticTheme1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgThemeSelecter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgThemeSelecter)
	virtual BOOL OnInitDialog();
	afx_msg void OnStaticTheme1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTHEMESELECTER_H__162FC162_416B_4441_849A_240C22E23BB0__INCLUDED_)
