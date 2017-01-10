
// ChattingServer Ver 0.2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ChattingServer Ver 0.2.h"
#include "ChattingServer Ver 0.2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChattingServerVer02App

BEGIN_MESSAGE_MAP(CChattingServerVer02App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChattingServerVer02App construction

CChattingServerVer02App::CChattingServerVer02App()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CChattingServerVer02App object

CChattingServerVer02App theApp;


// CChattingServerVer02App initialization

BOOL CChattingServerVer02App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CChattingServerVer02Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
// WSARecv�� WSASend�� Overlapped I/O �۾� ó���� ���� ������
unsigned int WINAPI CallWorkerThread(LPVOID p)
{
	iocp* pOverlappedEvent = (iocp*)p;
	pOverlappedEvent->WokerThread();
	return 0;
}

// Client�� ������ �ޱ� ���� ������
unsigned int WINAPI CallAccepterThread(LPVOID p)
{
	iocp* pOverlappedEvent = (iocp*)p;
	pOverlappedEvent->AccepterThread();
	return 0;
}
iocp::iocp(void)
{
	// ��� ��� ������ �ʱ�ȭ
	m_pMainDlg = NULL;
	m_bWorkerRun = true;
	m_bAccepterRun = true;
	m_nClientCnt = 0;
	m_hAccepterThread = NULL;
	m_hIOCP = NULL;
	m_socketListen = INVALID_SOCKET;	
	user.type = 0;
	users.type = 0;
	ZeroMemory(user.id, MAX_STRINGLEN);
	ZeroMemory(user.pwd, MAX_STRINGLEN);
	ZeroMemory(user.nickname, MAX_STRINGLEN);
	ZeroMemory(users.id, MAX_STRINGLEN);
	ZeroMemory(users.pwd, MAX_STRINGLEN);
	m_retval = false;
	ZeroMemory(m_szSocketBuf, MAX_BUFSIZE);
	for (int i = 0; i < MAX_WORKERTHREAD; i++)
		m_hWorkerThread[i] = NULL;

	// client ������ ������ ����ü�� ����
	m_pClientInfo = new stClientInfo[MAX_CLIENT];

}
iocp::~iocp(void)
{
	// ���� ����� ������
	WSACleanup();
	// ����� ��ü�� ����
	if (m_pClientInfo) {
		delete[] m_pClientInfo;
		m_pClientInfo = NULL;
	}
}
// ���� �ʱ�ȭ �Լ�
bool iocp::InitSocket()
{
	WSADATA wsaData;
	// ���� ������ 2.2�� �ʱ�ȭ
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (0 != nRet) {
		m_pMainDlg->OutputMsg("[����] WSAStartup()�Լ� ����: %d", WSAGetLastError());
		return false;
	}
	// TCP Overlapped I/O ���� ����
	m_socketListen = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_socketListen) {
		m_pMainDlg->OutputMsg("[����] socket()�Լ� ����: %d", WSAGetLastError());
		return false;
	}

	// ������ �ڵ� ����
	m_pMainDlg->OutputMsg("���� �ʱ�ȭ ����");
	return true;
}

// �ش� ���� ����
void iocp::CloseSocket(stClientInfo* pClientInfo, bool bIsForce)
{
	struct linger stLinger = { 0,0 }; // SO_DONTLINGER�� ����
									  // bIsForce�� true�̸� SO_LINGER, timeout=0���� �����Ͽ� ���� ����
	if (true == bIsForce)
		stLinger.l_onoff = 1;

	// ������ �ۼ��� �ߴ�
	shutdown(pClientInfo->m_socketClient, SD_BOTH);
	// ���� �ɼ� ����
	setsockopt(pClientInfo->m_socketClient, SOL_SOCKET, SO_LINGER, (char*)&stLinger, sizeof(stLinger));
	// ���� ����
	closesocket(pClientInfo->m_socketClient);

	pClientInfo->m_socketClient = INVALID_SOCKET;
}
// ���� �ּ������� ���ϰ� ����, ���� ���
bool iocp::BindandListen(int nBindPort)
{
	SOCKADDR_IN stServerAddr;
	stServerAddr.sin_family = AF_INET;
	// ������Ʈ ����
	stServerAddr.sin_port = htons(nBindPort);
	stServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// bind
	int nRet = bind(m_socketListen, (SOCKADDR*)&stServerAddr, sizeof(SOCKADDR_IN));
	if (0 != nRet) {
		m_pMainDlg->OutputMsg("[���� bind()�Լ� ����: %d", WSAGetLastError());
		return false;
	}

	// ���� ��� ť 5
	nRet = listen(m_socketListen, 5);
	if (0 != nRet) {
		m_pMainDlg->OutputMsg("[����] listen()�Լ� ����: %d", WSAGetLastError());
		return false;
	}
	m_pMainDlg->OutputMsg("���� ��� ����..");
	return true;




}
bool iocp::CreateWokerThread()
{
	unsigned int uiThreadId = 0;

	// WaitingThread Queue�� ��� ���·� ���� ������� ����
	// ����Ǵ� ����: (cpu���� *2)+1
	for (int i = 0; i < MAX_WORKERTHREAD; i++) {
		m_hWorkerThread[i] = (HANDLE)_beginthreadex(NULL, 0, &CallWorkerThread, this, CREATE_SUSPENDED, &uiThreadId);
		if (m_hWorkerThread == NULL) {
			m_pMainDlg->OutputMsg("WorkerThread Creation Failed: %u", GetLastError());
			return false;
		}
		ResumeThread(m_hWorkerThread[i]);
	}
	m_pMainDlg->OutputMsg("WorkerThread����..");
	return true;
}
bool iocp::CreateAccepterThread()
{
	unsigned int uiThreadId = 0;
	m_hAccepterThread = (HANDLE)_beginthreadex(NULL, 0, &CallAccepterThread, this, CREATE_SUSPENDED, &uiThreadId);
	if (m_hAccepterThread == NULL) {
		m_pMainDlg->OutputMsg("AccepterThread Creation Failed: %u", GetLastError());
		return false;
	}
	ResumeThread(m_hAccepterThread);
	m_pMainDlg->OutputMsg("AccepterThread����..");
	return true;
}
bool iocp::BindIOCompletionPort(stClientInfo* pClientInfo)
{
	HANDLE hIOCP;
	// socket�� pClientInfo�� COmpletionPort��ü�� �����Ų��.
	hIOCP = CreateIoCompletionPort((HANDLE)pClientInfo->m_socketClient, m_hIOCP, reinterpret_cast<DWORD>(pClientInfo), 0);
	if (NULL == hIOCP || m_hIOCP != hIOCP) {
		m_pMainDlg->OutputMsg("[����] CreateIoCompletionPort() �Լ� ����", GetLastError());
		return false;
	}
	return true;
}
bool iocp::StartServer()
{

	bool bRet = CreateWokerThread();
	if (false == bRet)return false;
	bRet = CreateAccepterThread();
	if (false == bRet)return false;

	// CompletionPort��ü ���� ��û
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if (NULL == m_hIOCP) {
		m_pMainDlg->OutputMsg("[����] CreateIoCompletionPort() �Լ� ����", GetLastError());
		return false;
	}
	m_pMainDlg->OutputMsg("���� ����");
	return false;
}
bool iocp::BindRecv(stClientInfo* pClientInfo)
{
	DWORD dwFlag = 0;
	DWORD dwRecvNumBytes = 0;

	// Overlapped I/O�� ���� �� ������ ����
	pClientInfo->m_stRecvOverlappedEx.m_wsaBuf.len = MAX_BUFSIZE;
	pClientInfo->m_stRecvOverlappedEx.m_wsaBuf.buf = pClientInfo->m_stRecvOverlappedEx.m_szBuf;
	pClientInfo->m_stRecvOverlappedEx.m_eOperation = OP_RECV;

	int nRet = WSARecv(pClientInfo->m_socketClient, &(pClientInfo->m_stRecvOverlappedEx.m_wsaBuf), 1, &dwRecvNumBytes, &dwFlag, (LPWSAOVERLAPPED)&(pClientInfo->m_stRecvOverlappedEx), NULL);

	// socket_error�̸� Ŭ���̾�Ʈ�� �������ɷ� ó��
	if (nRet == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING)) {
		m_pMainDlg->OutputMsg("[����] WSARecv()�Լ� ����: %d", WSAGetLastError());
		return false;
	}
	return true;
}
bool iocp::SendMsg(stClientInfo* pClientInfo, char* pMsg, int nLen)
{
	DWORD dwRecvNumBytes = 0;

	// ���۵� �޽��� ����
	CopyMemory(pClientInfo->m_stSendOverlappedEx.m_szBuf, pMsg, nLen);

	// Overlapped I/O�� ���� �� ������ ����
	pClientInfo->m_stRecvOverlappedEx.m_wsaBuf.len = nLen;
	pClientInfo->m_stRecvOverlappedEx.m_wsaBuf.buf = pClientInfo->m_stSendOverlappedEx.m_szBuf;
	pClientInfo->m_stRecvOverlappedEx.m_eOperation = OP_SEND;

	int nRet = WSASend(pClientInfo->m_socketClient, &(pClientInfo->m_stRecvOverlappedEx.m_wsaBuf), 1, &dwRecvNumBytes, 0, (LPWSAOVERLAPPED)&(pClientInfo->m_stRecvOverlappedEx), NULL);

	// socket_error�̸� Ŭ���̾�Ʈ�� �������ɷ� ó��
	if (nRet == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING)) {
		m_pMainDlg->OutputMsg("[����] WSARecv()�Լ� ����: %d", WSAGetLastError());
		return false;
	}
	return true;

}
stClientInfo* iocp::GetEmptyClientInfo()
{
	for (int i = 0; i < MAX_CLIENT; i++) {
		if (INVALID_SOCKET == m_pClientInfo[i].m_socketClient)return &m_pClientInfo[i];
	}
	return NULL;
}
void iocp::AccepterThread()
{
	SOCKADDR_IN stClientAddr;
	int nAddrLen = sizeof(SOCKADDR_IN);
	while (m_bAccepterRun) {

		// ���� ���� ����ü�� �ε����� ����
		stClientInfo* pClientInfo = GetEmptyClientInfo();
		if (NULL == pClientInfo) { m_pMainDlg->OutputMsg("[����] Client Full"); return; }
		// Ŭ�� ���� ��û ���
		pClientInfo->m_socketClient = accept(m_socketListen, (SOCKADDR*)&stClientAddr, &nAddrLen);
		if (INVALID_SOCKET == pClientInfo->m_socketClient) continue;
		// Ŭ�� �ּ� ����
		memcpy(&pClientInfo->m_clientAddr, &stClientAddr,sizeof(SOCKADDR_IN));
		// I/O Completion Port ��ü�� ���� ����
		bool bRet = BindIOCompletionPort(pClientInfo);
		if (false == bRet) return;
		// Recv Overlapped I/O �۾��� ��û�� ���´�
		bRet = BindRecv(pClientInfo);
		if (false == bRet) return;
		m_pMainDlg->OutputMsg("Ŭ���̾�Ʈ ����: IP(%s) SOCKET(%d)", inet_ntoa(stClientAddr.sin_addr), pClientInfo->m_socketClient);
		// Ŭ���̾�Ʈ ���� ����
		m_nClientCnt++;
	}

}
void iocp::WokerThread()
{
	// CompletionKey�� ���� ������ ����
	stClientInfo* pClientInfo = NULL;
	// �Լ� ȣ�� ���� ����
	BOOL bSuccess = TRUE;
	// Overlapped I/O �۾����� ���۵� ������ ũ��
	DWORD dwIoSize = 0;
	// I/O �۾��� ���� ��û�� Overlapped ����ü�� ���� ������
	LPOVERLAPPED lpOverlapped = NULL;

	while (m_bWorkerRun) {
		m_pMainDlg->OutputMsg("WorkerThread is running");
		// �� �Լ��� ���� ��������� WaitingThread Queue�� ��� ���·� ��
		// �Ϸ�� Overlapped I/O �۾��� �߻��ϸ� ICPI Queue���� �Ϸ�� �۾��� ������ �� ó���� ��
		// �׸��� PostQueuedCompletionStatus() �Լ��� ���� ����� �޼����� �����Ǹ� ������ ����
		bSuccess = GetQueuedCompletionStatus(m_hIOCP,
			&dwIoSize, // ���� ���۵� ����Ʈ
			(LPDWORD)&pClientInfo, // CompletionKey
			&lpOverlapped, // Overlapped IO ��ü
			INFINITE); // ����� �ð�

		if (FALSE == bSuccess && 64 != GetLastError()) {
			m_pMainDlg->OutputMsg("[����] GetQueuedCompletionStatus()�Լ� ����: %d", WSAGetLastError());
		}

		// client�� ������ ��������
		if (FALSE == bSuccess && 0 == dwIoSize) {
			m_pMainDlg->OutputMsg("socket(%d) ���� ����",pClientInfo->m_socketClient);
			CloseSocket(pClientInfo);
			continue;
		}

		// ����� ������ ���� �޼��� ó��
		if (TRUE == bSuccess && 0 == dwIoSize && NULL == lpOverlapped) {
			m_bWorkerRun = false;
			continue;
		}

		if (NULL == lpOverlapped)continue;
		stOverlappedEx* pOverlappedEx = (stOverlappedEx*)lpOverlapped;
		// Overlapped I/O Recv �۾� ��� �� ó��
		if (OP_RECV == pOverlappedEx->m_eOperation) {
			pOverlappedEx->m_szBuf[dwIoSize] = NULL;
			m_pMainDlg->OutputMsg("[����] bytes: %d IP(%s) SOCKET(%d)", dwIoSize, inet_ntoa(pClientInfo->m_clientAddr.sin_addr),pClientInfo->m_socketClient);
			
			m_retval=DivideUserInfo(pOverlappedEx->m_szBuf,pClientInfo);

			if (CHATTINGDATA != user.type && LOGIN != user.type) {
				memcpy(&pOverlappedEx->m_szBuf[0], &m_retval, sizeof(bool));
				SendMsg(pClientInfo, &pOverlappedEx->m_szBuf[0], sizeof(bool));
			}
			else if (LOGIN == user.type) {
				memcpy(&pOverlappedEx->m_szBuf[0], &m_retval, sizeof(bool));
				SendMsg(pClientInfo, &pOverlappedEx->m_szBuf[0], sizeof(bool));
				if (true == m_retval) {
					pClientInfo->m_uLocation = ROOM;
					//char* nickname = mysql.GetUserNickName();
					/*for (int i = 0; i < MAX_CLIENT; i++) {
						if (ROOM == pClientInfo[i].m_uLocation) {
							SendMsg(&pClientInfo[i], nickname, MAX_MSGSIZE);
						}
					}*/
				}
			}
			else if (CHATTINGDATA == user.type) {
				memcpy(m_msgbuf, &pOverlappedEx->m_szBuf[sizeof(int)], MAX_MSGSIZE);
				for (int i = 0; i < MAX_CLIENT; i++) {
					if (INVALID_SOCKET != pClientInfo[i].m_socketClient) {
						if (ROOM == pClientInfo[i].m_uLocation) {
							SendMsg(&pClientInfo[i], m_msgbuf, MAX_MSGSIZE);
						}
					}
				}
			}
			
		}
		else if (OP_SEND == pOverlappedEx->m_eOperation) {
			if (CHATTINGDATA != user.type) 
			m_pMainDlg->OutputMsg("[�۽�] bytes: %d, msg: %d", dwIoSize, pOverlappedEx->m_szBuf[0]);
			else if (CHATTINGDATA == user.type)
			m_pMainDlg->OutputMsg("[�۽�] bytes: %d, msg: %s", dwIoSize, m_msgbuf);
			
			BindRecv(pClientInfo);
		}
		// ����
		else {
			m_pMainDlg->OutputMsg("socket(%d)������ ���ܻ�Ȳ", pClientInfo->m_socketClient);
		}
		
	}
}
void iocp::DestroyThread()
{
	for (int i = 0; i < MAX_WORKERTHREAD; i++) {
		// WaitingThread Queue���� ������� �����忡 ����� ���� �޼����� ����
		PostQueuedCompletionStatus(m_hIOCP, 0, 0, NULL);
	}
	for (int i = 0; i < MAX_WORKERTHREAD; i++) {
		// ������ �ڵ��� �ݰ� �����尡 ����� ������ ���
		CloseHandle(m_hWorkerThread[i]);
		WaitForSingleObject(m_hWorkerThread[i], INFINITE);
	}
	m_bAccepterRun = false;
	// Accepter �����带 ����
	closesocket(m_socketListen);
	// ������ ���� ���
	WaitForSingleObject(m_hAccepterThread, INFINITE);


}
bool iocp::MysqlInit()
{
	bool retval = mysql.Init();
	if (retval)
		return true;
	else
		return false;

}
bool iocp::DivideUserInfo(char buf[MAX_BUFSIZE], stClientInfo* pClientInfo)
{
	memcpy(&user.type, buf, sizeof(int));
	if (ENROLL == user.type) {
		memcpy(&user.id, &buf[sizeof(int)], MAX_STRINGLEN);
		memcpy(&user.pwd, &buf[sizeof(int) + MAX_STRINGLEN], MAX_STRINGLEN);
		memcpy(&user.nickname, &buf[sizeof(int) + MAX_STRINGLEN * 2], MAX_STRINGLEN);
		mysql.SetUser(user);
		m_retval = mysql.Enroll();
		if (m_retval) {
			m_pMainDlg->OutputUserLogMsg("ID: %s ���� ���� IP(%s) SOCKET(%d)", user.id, inet_ntoa(pClientInfo->m_clientAddr.sin_addr), pClientInfo->m_socketClient);
			return true;
		}
		else {
			m_pMainDlg->OutputUserLogMsg("ID: %s ���� ���� IP(%s) SOCKET(%d)", user.id, inet_ntoa(pClientInfo->m_clientAddr.sin_addr), pClientInfo->m_socketClient);
			return false;
		}
	}
	else if(SECESSION==user.type){
		memcpy(&users.id, &buf[sizeof(int)], MAX_STRINGLEN);
		memcpy(&users.pwd, &buf[sizeof(int) + MAX_STRINGLEN], MAX_STRINGLEN);
		mysql.SetUserS(users);
		m_retval = mysql.Secession();
		if (m_retval) {
			m_pMainDlg->OutputUserLogMsg("ID: %s Ż�� ���� IP(%s) SOCKET(%d)", users.id, inet_ntoa(pClientInfo->m_clientAddr.sin_addr), pClientInfo->m_socketClient);
			return true;
		}
		else {
			m_pMainDlg->OutputUserLogMsg("ID: %s Ż�� ���� IP(%s), SOCKET(%d)", users.id, inet_ntoa(pClientInfo->m_clientAddr.sin_addr), pClientInfo->m_socketClient);
			return false;
		}
	}
	else if (LOGIN == user.type) {
		memcpy(&users.id, &buf[sizeof(int)], MAX_STRINGLEN);
		memcpy(&users.pwd, &buf[sizeof(int) + MAX_STRINGLEN], MAX_STRINGLEN);
		mysql.SetUserS(users);
		m_retval = mysql.Login();
		if (m_retval) {
			m_pMainDlg->OutputUserLogMsg("ID: %s �α��� ���� IP(%s) SOCKET(%d)", users.id, inet_ntoa(pClientInfo->m_clientAddr.sin_addr), pClientInfo->m_socketClient);
			return true;
		}
		else {
			m_pMainDlg->OutputUserLogMsg("ID: %s �α��� ���� IP(%s), SOCKET(%d)", users.id, inet_ntoa(pClientInfo->m_clientAddr.sin_addr), pClientInfo->m_socketClient);
			return false;
		}
	}
	else if (CHATTINGDATA == user.type) {
		return true;
	}
	else return false;

}