// userExit.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingClient Ver 0.1.h"
#include "userExit.h"
#include "afxdialogex.h"


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

class User {
public:
	CString id;
	CString pwd;

};
void userExit::OnBnClickedOk()
{
	User user;
	// TODO: Add your control notification handler code here
	char Query[256];
	int Query_Status;
	CString Sqlstr;
	// TODO: Add your control notification handler code here
	// DB ����
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0))

	{

		MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);

	}
	else {
		// DB�� ������ ����

		GetDlgItemText(IDC_EID, user.id);
		GetDlgItemText(IDC_EPWD, user.pwd);


		sprintf_s(Query, "delete from chattingdb.userinfo where ID = '%ls' and PWD = '%ls' ", user.id,user.pwd);
		Query_Status = mysql_query(&mysql, Query);
		if (Query_Status)
		{
			MessageBox(_T("ȸ�������� �Ϸ��ϴ� ���߿� ������ �߻��Ͽ����ϴ�."), _T("�����ͺ��̽� ����"));

		}
		else
		{
			MessageBox(_T("Ż��Ǿ����ϴ�."));

			CDialogEx::OnOK();
		}
	}

	CDialogEx::OnOK();
}
