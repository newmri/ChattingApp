// DEnroll.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingClient Ver 0.1.h"
#include "DEnroll.h"
#include "afxdialogex.h"
#include "Client.h"
#include "User.h"
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
	//sock.Send((char*)&newuser, sizeof(newuser));
	//char Query[600];
	//int Query_Status;
	//CString Sqlstr;
	//// TODO: Add your control notification handler code here
	//// DB ����
	//mysql_init(&mysql);
	//if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0))

	//{

	//	MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);

	//}
	//else {
	//	// DB�� ������ ����

	//	GetDlgItemText(IDC_EID,newuser.id);
	//	GetDlgItemText(IDC_EPWD, newuser.pwd);
	//	GetDlgItemText(IDC_ENIC, newuser.name);
	//	
	//	char *a = (char *)(LPCTSTR)newuser.id;
	//	sprintf_s(Query, "insert into chattingdb.userinfo values ('%ls','%ls','%ls')", newuser.id, newuser.pwd, newuser.name);
	//		
	//
	//		Query_Status = mysql_query(&mysql, Query);
	//		if (Query_Status)
	//		{
	//			MessageBox(_T("ȸ�������� �Ϸ��ϴ� ���߿� ������ �߻��Ͽ����ϴ�."), _T("�����ͺ��̽� ����"));
	//		
	//		}
	//		else
	//		{
	//			
	//			MessageBox(_T("ȸ�������� ȯ���մϴ�."));
	//		
	//			CDialogEx::OnOK();
	//		}
	//	}

		

	}

