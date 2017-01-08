
// ChattingServer Ver 0.2Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CChattingServerVer02Dlg dialog
class CChattingServerVer02Dlg : public CDialogEx
{
// Construction
public:
	CChattingServerVer02Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATTINGSERVERVER02_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	// 출력 메세지
	void OutputMsg(char* szOutputString, ...);
	// 유저 로그 출력 메세지
	void OutputUserLogMsg(char* szOutputString, ...);
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

	iocp iocps;
	afx_msg void OnBnClickedStartserver();
	CListBox m_ctOutput;
	CListBox userlog;
};
