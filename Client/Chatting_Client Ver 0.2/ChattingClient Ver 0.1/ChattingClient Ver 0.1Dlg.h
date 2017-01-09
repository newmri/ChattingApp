
// ChattingClient Ver 0.1Dlg.h : header file
//

#pragma once
#include "afxext.h"


// CChattingClientVer01Dlg dialog
class CChattingClientVer01Dlg : public CDialogEx
{
// Construction
public:
	CChattingClientVer01Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATTINGCLIENTVER01_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedExit();

	afx_msg void OnBnClickedLogin();

	
	CBitmapButton m_bLogin;
	afx_msg void OnBnClickedExit();
	afx_msg void OnEnChangeId();
	afx_msg void OnBnClickedLgoin();
	afx_msg void OnBnClickednewmember();
	afx_msg void OnBnClickedEexit();
};
