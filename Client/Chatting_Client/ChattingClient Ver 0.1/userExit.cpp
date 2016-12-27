// userExit.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingClient Ver 0.1.h"
#include "userExit.h"
#include "afxdialogex.h"
#include "Client.h"

// userExit dialog

IMPLEMENT_DYNAMIC(userExit, CDialogEx)

userExit::userExit(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EXIT, pParent)
{

}

userExit::~userExit()
{
}

void userExit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(userExit, CDialogEx)
	ON_BN_CLICKED(IDOK, &userExit::OnBnClickedOk)
END_MESSAGE_MAP()


// userExit message handlers


enum { SECESSION = 2 };
void userExit::OnBnClickedOk()
{
	UserS user;
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EEID, user.id);
	GetDlgItemText(IDC_EEPWD, user.pwd);
	extern Sock sock;
	sock.SendType(SECESSION);
	char buf[128];
	wsprintf(buf, "%s %s", user.id.Trim(), user.pwd);
	sock.Send(buf, 128);

	

	CDialogEx::OnOK();
}
