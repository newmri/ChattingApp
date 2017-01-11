// Main.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingClient Ver 0.1.h"
#include "Main.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Client.h"
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMain dialog

IMPLEMENT_DYNAMIC(CMain, CDialog)

CMain::CMain(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_Main, pParent)
{

}

CMain::~CMain()
{
}

void CMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChattingScreen, chattingvar);
	DDX_Control(pDX, IDC_UserList, UserList);
}


BEGIN_MESSAGE_MAP(CMain, CDialog)
	ON_COMMAND(ID_MadeBy, &CMain::OnMadeby)
	ON_MESSAGE(WM_SOCKETMSG, OnSocketMsg)
//	ON_WM_ACTIVATE()
	ON_MESSAGE(27001, &CMain::On27001)
END_MESSAGE_MAP()

LRESULT CMain::OnSocketMsg(WPARAM wParam, LPARAM lParam)
{

	extern Sock sock;
	//SOCKET sock = (SOCKET)wParam;
	// 에러 체크
	int nError = WSAGETSELECTERROR(lParam);
	if (0 != nError) {
		return false;
	}
	// 이벤트 체크
	int nEvent = WSAGETSELECTEVENT(lParam);
	switch (nEvent) {
	case FD_READ:
	{

		sock.Recv(m_szSocketBuf, 34, 0);
		//int nRecvLen = recv(sock, m_szSocketBuf,30, 0);
		int type{};
		char buf[30]{};
		CString str;
		memcpy(&type, m_szSocketBuf, sizeof(int));
		if (USERLIST == type) {
			memcpy(buf, &m_szSocketBuf[sizeof(int)], 10);
			str = buf;
			UserList.InsertString(-1, buf);
		}
		else if (CHATTINGDATA == type) {
			memcpy(buf, &m_szSocketBuf[sizeof(int)], 30);
			str = buf;
			chattingvar.InsertString(-1, buf);
		}
		int nRet = WSAAsyncSelect(sock.getSocket(), m_hWnd, WM_SOCKETMSG, FD_READ | FD_CLOSE);

	}
	break;


	case FD_CLOSE:
	{
		return false;
	}
	break;
	}
	return true;


}

// CMain message handlers


void CMain::OnMadeby()
{
	CAboutDlg Dlg;
	Dlg.DoModal();
}


BOOL CMain::PreTranslateMessage(MSG* pMsg)
{

	if (pMsg->wParam == VK_ESCAPE)   //ESC 키면 무시..
		return TRUE;

	else if (pMsg->message == WM_SYSKEYDOWN)
	{
		//Alt+F4키면 무시(Alt키는 VK_KEYDOWN이 아니라 VK_SYSKEYDOWN으로 알아내야함
		if(pMsg->wParam == VK_F4)   
		{
		 return TRUE;
		}
		else
		return CDialog::PreTranslateMessage(pMsg);
	}

	// Enter키를 쳤을때 무시
	else if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN)){
		if (GetDlgItem(IDC_ChattingInput) == GetFocus()){
			CString str;
			GetDlgItemText(IDC_ChattingInput, str);
			extern Sock sock;
			char buf[1024]{};
			int type= CHATTINGDATA;
			memcpy(buf,&type,sizeof(int));
			//wsprintf(buf, "%s",str.Trim());
			memcpy(&buf[sizeof(int)],str.Trim(), 30);
			sock.Send(buf, sizeof(int)+30);
			SetDlgItemText(IDC_ChattingInput, _T(""));
			return TRUE;
		}
	}
	// 그외의 경우는 리턴

	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CMain::OnInitDialog()
{
	CDialog::OnInitDialog();
	extern Sock sock;
	sock.setHandle(this);
	// 이벤트 등록
	int nRet = WSAAsyncSelect(sock.getSocket(), m_hWnd, WM_SOCKETMSG, FD_READ | FD_CLOSE);
	if (SOCKET_ERROR == nRet) {
		return false;
	}
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


//void CMain::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CDialog::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO: Add your message handler code here
//}


afx_msg LRESULT CMain::On27001(WPARAM wParam, LPARAM lParam)
{
	extern Sock sock;
	//SOCKET sock = (SOCKET)wParam;
	// 에러 체크
	int nError = WSAGETSELECTERROR(lParam);
	if (0 != nError) {
		return false;
	}
	// 이벤트 체크
	int nEvent = WSAGETSELECTEVENT(lParam);
	switch (nEvent) {
	case FD_READ:
	{

		sock.Recv(m_szSocketBuf, 30, 0);
		//int nRecvLen = recv(sock, m_szSocketBuf,30, 0);
		CString str = m_szSocketBuf;
		UserList.InsertString(-1, m_szSocketBuf);
		int nRet = WSAAsyncSelect(sock.getSocket(), m_hWnd, 27001, FD_READ | FD_CLOSE);

	}
	break;


	case FD_CLOSE:
	{
		return false;
	}
	break;
	}
	return true;


}
