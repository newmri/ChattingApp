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

	if (pMsg->wParam == VK_ESCAPE)   //ESC Ű�� ����..
		return TRUE;

	else if (pMsg->message == WM_SYSKEYDOWN)
	{
		//Alt+F4Ű�� ����(AltŰ�� VK_KEYDOWN�� �ƴ϶� VK_SYSKEYDOWN���� �˾Ƴ�����
		if(pMsg->wParam == VK_F4)   
		{
		 return TRUE;
		}
		else
		return CDialog::PreTranslateMessage(pMsg);
	}

	// EnterŰ�� ������ ����
	else if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN)){
		if (GetDlgItem(IDC_ChattingInput) == GetFocus()){
			MessageBox(_T("�׽�Ʈ�� �ڽ�"), _T("�׽�Ʈ ����"), MB_OK);
			return TRUE;
		}
	}
	// �׿��� ���� ����

	return CDialog::PreTranslateMessage(pMsg);
}
