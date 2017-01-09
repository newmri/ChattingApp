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



void userExit::OnBnClickedOk()
{
	UserS users;
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EEID, users.id);
	GetDlgItemText(IDC_EEPWD, users.pwd);
	extern Sock sock;
	users.type = SECESSION;
	char buf[1024]{};
	memcpy(buf, &users.type, sizeof(int));
	memcpy(&buf[sizeof(int)], users.id.Trim(), 10);
	memcpy(&buf[(sizeof(int) + 10)], users.pwd.Trim(), 10);

	sock.Send(buf, sizeof(int) + 20);
	sock.Recv(&buf[0], sizeof(bool), 0);
	if (true == buf[0])
		MessageBox(_T("������ �� ������!"), _T("Ż�� ����"), MB_OK);
	else if(false == buf[0])
		MessageBox(_T("Ż�� �Ϸ��ϴ� ���߿� ������ �߻��Ͽ����ϴ�."), _T("Ż�� ����"));


	

	CDialogEx::OnOK();
}
