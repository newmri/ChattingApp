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
	
	

		

}

