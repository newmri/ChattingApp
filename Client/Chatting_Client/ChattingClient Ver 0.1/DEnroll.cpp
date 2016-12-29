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


enum { ENROLL = 1 };
void CDEnroll::OnBnClickedEok()
{

	User newuser;
	GetDlgItemText(IDC_EID,newuser.id);
	GetDlgItemText(IDC_EPWD, newuser.pwd);
	GetDlgItemText(IDC_ENIC, newuser.nickname);
	extern Sock sock;
	sock.SendType(ENROLL);
	char buf[128];
	wsprintf(buf, "%s %s %s", newuser.id.Trim(), newuser.pwd.Trim(), newuser.nickname);
	sock.Send(buf,128);
	bool result{};
	sock.Recv((char*)&result, 0);
	if(true==result)
		MessageBox( _T("회원가입을 환영합니다 호갱님."),_T("가입 성공"), MB_OK);
	else
		MessageBox(_T("회원가입을 완료하는 도중에 오류가 발생하였습니다."), _T("가입 실패"));
	

		

}

