
// ChattingServer Ver 0.2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChattingServer Ver 0.2.h"
#include "ChattingServer Ver 0.2Dlg.h"
#include "afxdialogex.h"

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


// CChattingServerVer02Dlg dialog



CChattingServerVer02Dlg::CChattingServerVer02Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHATTINGSERVERVER02_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChattingServerVer02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctOutput);
	DDX_Control(pDX, IDC_LIST2, userlog);
}

BEGIN_MESSAGE_MAP(CChattingServerVer02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_SERVERSTART, OnBnClickedStartserver)
END_MESSAGE_MAP()

// 출력 메세지
void CChattingServerVer02Dlg::OutputMsg(char* szOutputString, ...)
{
	char szOutStr[1024];
	va_list argptr;
	va_start(argptr, szOutputString);
	vsprintf(szOutStr, szOutputString, argptr);
	va_end(argptr);
	m_ctOutput.SetCurSel(m_ctOutput.AddString(szOutStr));


}
// 유저 로그 출력 메세지
void CChattingServerVer02Dlg::OutputUserLogMsg(char* szOutputString, ...)
{
	char szOutStr[1024];
	va_list argptr;
	va_start(argptr, szOutputString);
	vsprintf(szOutStr, szOutputString, argptr);
	va_end(argptr);
	m_ctOutput.SetCurSel(userlog.AddString(szOutStr));


}
void CChattingServerVer02Dlg::OnBnClickedStartserver()
{
	// Mysql 초기화
	bool retval=iocps.MysqlInit();
	if(retval) this->OutputMsg("DB 접속 성공");
	else this->OutputMsg("DB 접속 실패");
	// 소켓 메세지를 윈도우에 뿌리기 위해 현재 다이얼로그 포인터를 넘겨준다
	iocps.SetMainDlg(this);
	// 소켓을 초기화
	iocps.InitSocket();
	// 소켓과 주소를 연결, 등록
	iocps.BindandListen(8000);
	//  서버 시작
	iocps.StartServer();


}

// CChattingServerVer02Dlg message handlers

BOOL CChattingServerVer02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChattingServerVer02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChattingServerVer02Dlg::OnPaint()
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
HCURSOR CChattingServerVer02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

