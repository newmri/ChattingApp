// DEnroll.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingClient Ver 0.1.h"
#include "DEnroll.h"
#include "afxdialogex.h"
#include "Client.h"
// CDEnroll dialog

IMPLEMENT_DYNAMIC(CDEnroll, CDialogEx)

CDEnroll::CDEnroll(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDEnroll, pParent)
{

}

CDEnroll::~CDEnroll()
{
}

void CDEnroll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDEnroll, CDialogEx)
	ON_BN_CLICKED(IDEOK, &CDEnroll::OnBnClickedEok)
END_MESSAGE_MAP()


// CDEnroll message handlers



void CDEnroll::OnBnClickedEok()
{
	extern Sock sock;
	User* newuser = &sock.getUser();
	GetDlgItemText(IDC_EID,newuser->id);
	GetDlgItemText(IDC_EPWD, newuser->pwd);
	GetDlgItemText(IDC_ENIC, newuser->nickname);

	char buf[1024]{};
	newuser->type = ENROLL;
	memcpy(buf, &newuser->type, sizeof(int));
	memcpy(&buf[sizeof(int)], newuser->id.Trim(), 10);
	memcpy(&buf[(sizeof(int)+10)], newuser->pwd.Trim(), 10);
	memcpy(&buf[(sizeof(int) + 20)], newuser->nickname.Trim(), 10);
	if (sock.CheckEnroll()){
		sock.Send(buf, sizeof(int) + 30);
		sock.Recv(&buf[0], sizeof(bool), 0);
		if (true == buf[0])
			MessageBox(_T("ȸ�������� ȯ���մϴ� ȣ����."), _T("���� ����"), MB_OK);
		else if (false == buf[0])
			MessageBox(_T("ȸ�������� �Ϸ��ϴ� ���߿� ������ �߻��Ͽ����ϴ�."), _T("���� ����"));

	}
		

}

