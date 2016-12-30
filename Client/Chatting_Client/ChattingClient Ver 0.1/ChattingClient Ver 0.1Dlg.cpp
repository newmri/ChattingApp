
// ChattingClient Ver 0.1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingClient Ver 0.1.h"
#include "ChattingClient Ver 0.1Dlg.h"
#include "afxdialogex.h"
#include "Client.h"
#include "DEnroll.h"
#include "userExit.h"
#include "Main.h"
#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CChattingClientVer01Dlg dialog



CChattingClientVer01Dlg::CChattingClientVer01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHATTINGCLIENTVER01_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChattingClientVer01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);



	DDX_Control(pDX, IDC_LGOIN, m_bLogin);
}

BEGIN_MESSAGE_MAP(CChattingClientVer01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDExit, &CChattingClientVer01Dlg::OnBnClickedExit)

ON_BN_CLICKED(IDC_EXIT, &CChattingClientVer01Dlg::OnBnClickedExit)
ON_EN_CHANGE(IDC_ID, &CChattingClientVer01Dlg::OnEnChangeId)
ON_BN_CLICKED(IDC_LGOIN, &CChattingClientVer01Dlg::OnBnClickedLgoin)
ON_BN_CLICKED(IDC_newMember, &CChattingClientVer01Dlg::OnBnClickednewmember)
ON_BN_CLICKED(IDC_EEXIT, &CChattingClientVer01Dlg::OnBnClickedEexit)
END_MESSAGE_MAP()


// CChattingClientVer01Dlg message handlers
Sock sock;
BOOL CChattingClientVer01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	sock.Init();
	sock.Connect();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//m_bLogin.LoadBitmaps(IDB_LOGIN);
	//m_bLogin.SizeToContent();
 // �̹��� �ε�

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChattingClientVer01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChattingClientVer01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChattingClientVer01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CChattingClientVer01Dlg::OnBnClickedExit()
//{
//	// TODO: Add your control notification handler code here
//	this->OnClose();
//}






void CChattingClientVer01Dlg::OnBnClickedExit()
{
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}


void CChattingClientVer01Dlg::OnEnChangeId()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

enum { LOGIN = 3 };
void CChattingClientVer01Dlg::OnBnClickedLgoin()
{

		
	UserS user;
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_ID, user.id);
	GetDlgItemText(IDC_PWD, user.pwd);
	extern Sock sock;
	sock.SendType(LOGIN);
	char buf[128];
	wsprintf(buf, "%s %s", user.id.Trim(), user.pwd);
	sock.Send(buf, 128);
	bool result{};
	sock.Recv((char*)&result, 0);
	if (true == result){
		MessageBox(_T("ȯ���մϴ�"), _T("�α��� ����"), MB_OK);
		::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
		CMain Main;
		Main.DoModal();
	}
	else
		MessageBox(_T("�α����� �Ϸ��ϴ� ���߿� ������ �߻��Ͽ����ϴ�."), _T("�α��� ����"));

	

	



}


void CChattingClientVer01Dlg::OnBnClickednewmember()
{
	// TODO: Add your control notification handler code here

		
		// ���ο� â ���
		CDEnroll Enroll;
		Enroll.DoModal();

	
}


void CChattingClientVer01Dlg::OnBnClickedEexit()
{
	// TODO: Add your control notification handler code here
	userExit userexit;
	userexit.DoModal();
}
