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
}


BEGIN_MESSAGE_MAP(CMain, CDialog)
	ON_COMMAND(ID_MadeBy, &CMain::OnMadeby)
END_MESSAGE_MAP()


// CMain message handlers


void CMain::OnMadeby()
{
	CAboutDlg Dlg;
	Dlg.DoModal();
}

enum { CHATTINGDATA = 4 };
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
			sock.SendType(CHATTINGDATA);
			char buf[128];
			wsprintf(buf, "%s",str.Trim());
			sock.Send(buf, 128);
			sock.Recv(buf, 0);
			str = buf;
			chattingvar.InsertString(-1, str);
			SetDlgItemText(IDC_ChattingInput, _T(""));
			return TRUE;
		}
	}
	// 그외의 경우는 리턴

	return CDialog::PreTranslateMessage(pMsg);
}
