#pragma once
#include "afxwin.h"
#include "Client.h"
#define WM_SOCKETMSG WM_USER+1
// CMain dialog

class CMain : public CDialog
{
	DECLARE_DYNAMIC(CMain)

public:
	CMain(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMain();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// 이벤트가 발생하여 WM_SOCKETMSG를 받으면 이 함수가 실행.
	// WParam이 이벤트가 발생한 소켓이고 lParam은 이벤트 종류와 에러코드 보유
	LRESULT OnSocketMsg(WPARAM wParam, LPARAM lParam);

	afx_msg void OnMadeby();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// 소켓 버퍼
	char m_szSocketBuf[1024];


	CListBox chattingvar;
	virtual BOOL OnInitDialog();
	CListBox UserList;
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
protected:
	afx_msg LRESULT On27001(WPARAM wParam, LPARAM lParam);
};
