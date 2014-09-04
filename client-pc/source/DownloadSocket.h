#if !defined(AFX_DOWNLOADSOCKET_H__80042E91_2A1A_4596_BED9_275FB93A1CBB__INCLUDED_)
#define AFX_DOWNLOADSOCKET_H__80042E91_2A1A_4596_BED9_275FB93A1CBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DownloadSocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDownloadSocket command target

class CDownloadSocket : public CSocket
{
// Attributes
public:
	CWnd *m_pParentWnd;
	UINT m_nSocketIndex;
	CString m_csResName;
	CString m_csResMD5;
	UINT	m_nResPieceCount;
	UINT	m_nListItem;
// Operations
public:
	CDownloadSocket(CWnd *pParentWnd, UINT nSocketIndex, CString csResName, CString csResMD5, UINT nResPieceCount, UINT nListItem);//CWnd *pParent);
	virtual ~CDownloadSocket();


// Overrides
public:
	void DownloadRes(UINT nResPieceId);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownloadSocket)
	public:
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDownloadSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNLOADSOCKET_H__80042E91_2A1A_4596_BED9_275FB93A1CBB__INCLUDED_)
