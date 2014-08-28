#if !defined(AFX_UDPSOCKET_H__D29F2D3D_9D7D_4EBE_AA0C_D040D36BE253__INCLUDED_)
#define AFX_UDPSOCKET_H__D29F2D3D_9D7D_4EBE_AA0C_D040D36BE253__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UdpSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CUdpSocket command target

class CUdpSocket : public CSocket
{
// Attributes
public:
	CWnd *m_pParentWnd;

// Operations
public:
	CUdpSocket(CWnd *pParentWnd);
	virtual ~CUdpSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUdpSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CUdpSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSOCKET_H__D29F2D3D_9D7D_4EBE_AA0C_D040D36BE253__INCLUDED_)
