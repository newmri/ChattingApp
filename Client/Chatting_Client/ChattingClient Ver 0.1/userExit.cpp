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
	// DB 연결
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0))

	{

		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);

	}
	else {
		// DB에 데이터 생성

		GetDlgItemText(IDC_EID, user.id);
		GetDlgItemText(IDC_EPWD, user.pwd);


		sprintf_s(Query, "delete from chattingdb.userinfo where ID = '%ls' and PWD = '%ls' ", user.id,user.pwd);
		Query_Status = mysql_query(&mysql, Query);
		if (Query_Status)
		{
			MessageBox(_T("회원가입을 완료하는 도중에 오류가 발생하였습니다."), _T("데이터베이스 오류"));

		}
		else
		{
			MessageBox(_T("탈퇴되었습니다."));

			CDialogEx::OnOK();
		}
	}

	CDialogEx::OnOK();
}
