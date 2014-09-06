#if !defined(AFX_DOWNLOADSOCKET1_H__C64C170A_E4C3_4A2F_AA32_19AD634BB7EE__INCLUDED_)
#define AFX_DOWNLOADSOCKET1_H__C64C170A_E4C3_4A2F_AA32_19AD634BB7EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DownloadSocket1.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDownloadSocket command target

class CDownloadSocket : public CSocket
{
// Attributes
public:
	CWnd *m_pWnd;
	CList<PIECE_DATA, PIECE_DATA>m_pieceDataList;
	CString m_csResName;
	CString m_csTmpResName;
	DWORD   m_nPieceSize;
	DWORD   m_nRecvSize;

	void SetMainWnd(CWnd *pWnd);
// Operations
public:
	CDownloadSocket();
	virtual ~CDownloadSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownloadSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
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

#endif // !defined(AFX_DOWNLOADSOCKET1_H__C64C170A_E4C3_4A2F_AA32_19AD634BB7EE__INCLUDED_)
