// Login.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingClient Ver 0.1.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Client.h"


// Login dialog

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHATTINGCLIENTVER01_DIALOG, pParent)
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDC_LGOIN, &Login::OnBnClickedOk)
END_MESSAGE_MAP()


// Login message handlers
void Login::OnBnClickedOk()
{
	UserS user;
	GetDlgItemText(IDC_EEID, user.id);
	GetDlgItemText(IDC_EEPWD, user.pwd);
	/*extern Sock sock;
	sock.SendType(SECESSION);
	char buf[128];
	wsprintf(buf, "%s %s", user.id.Trim(), user.pwd);
	sock.Send(buf, 128);
	bool result{};
	sock.Recv((char*)&result, 0);
	if (true == result)
		MessageBox(_T("������ �� ������!"), _T("Ż�� ����"), MB_OK);
	else
		MessageBox(_T("Ż�� �Ϸ��ϴ� ���߿� ������ �߻��Ͽ����ϴ�."), _T("Ż�� ����"));
*/
	MessageBox(_T("Ż�� �Ϸ��ϴ� ���߿� ������ �߻��Ͽ����ϴ�."), _T("Ż�� ����"));


	CDialogEx::OnOK();
}

