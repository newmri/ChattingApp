// Main.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingClient Ver 0.1.h"
#include "Main.h"
#include "afxdialogex.h"
#include "resource.h"

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
			MessageBox(_T("테스트용 박스"), _T("테스트 성공"), MB_OK);
			return TRUE;
		}
	}
	// 그외의 경우는 리턴

	return CDialog::PreTranslateMessage(pMsg);
}
