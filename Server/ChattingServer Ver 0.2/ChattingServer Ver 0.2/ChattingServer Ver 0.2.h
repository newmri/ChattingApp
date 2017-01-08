
// ChattingServer Ver 0.2.h : main header file for the PROJECT_NAME application
//

#pragma once

class CChattingServerVer02Dlg;
#define MAX_BUFSIZE 1024
#define MAX_STRINGLEN 10
#define MAX_CLIENT 100
#define MAX_WORKERTHREAD 4 // ������ ���� ���� ������ ��
#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "Mysql.h"
#pragma comment(lib, "user32.lib")
// CChattingServerVer02App:
// See ChattingServer Ver 0.2.cpp for the implementation of this class
//



enum enumOperation {OP_RECV, OP_SEND };
// WSAOVERLAPPED ����ü Ȯ��
struct stOverlappedEx {
	WSAOVERLAPPED m_wsaOverlapped; // Overlapped I/O ����ü
	SOCKET m_socketClient; // Ŭ�� ����
	WSABUF m_wsaBuf; // Overlapped I/O �۾� ����
	char m_szBuf[MAX_BUFSIZE]; // ������ ����
	enumOperation m_eOperation; // �۾� ���� ����
};

// Ŭ�� ���� ����ü
struct stClientInfo {
	SOCKADDR_IN m_clientAddr; // Client �ּ� ���� ����
	SOCKET m_socketClient; // Client�� ����Ǵ� ����
	stOverlappedEx m_stRecvOverlappedEx; // RECV Overlapped I/O �۾��� ���� ����
	stOverlappedEx m_stSendOverlappedEx; // SEND Overlapped I/O �۾��� ���� ����
										 // �����ڿ��� ��� �������� �ʱ�ȭ
	stClientInfo()
	{
		ZeroMemory(&m_stRecvOverlappedEx, sizeof(stOverlappedEx));
		ZeroMemory(&m_stSendOverlappedEx, sizeof(stOverlappedEx));
		//ZeroMemory(&m_clientAddr, sizeof(SOCKADDR_IN));
		m_socketClient = INVALID_SOCKET;
	}
};
class iocp
{
private:
	// Ŭ�� ���� ���� ����ü
	stClientInfo* m_pClientInfo;
	// ���� ����
	SOCKET m_socketListen;
	// ���ӵ� Ŭ�� ��
	int m_nClientCnt;
	// ���� ������ ������
	CChattingServerVer02Dlg* m_pMainDlg;
	// �۾������� �ڵ� -- WaitingThread Queue�� �� ������
	HANDLE m_hWorkerThread[MAX_WORKERTHREAD];
	// ���� ������ �ڵ�
	HANDLE m_hAccepterThread;
	// CompletionPort ��ü �ڵ�
	HANDLE m_hIOCP;
	// �۾� ������ ���� �÷���
	bool m_bWorkerRun;
	// ���� ������ ���� �÷���
	bool m_bAccepterRun;
	// ���� ����
	char m_szSocketBuf[MAX_BUFSIZE];
	// ������ ����
	enum { ENROLL = 1 };
	// ȸ�� ���� ���� ����ü
	User user;
	// ��Ÿ ����ü
	UserS users;
	// Mysql ��� ��ü
	Mysql mysql;
	// return ����
	bool m_retval; 

public:
	iocp(void);
	~iocp(void);

	// -- ���� Ŭ�� ���� �Լ� -- //
	bool InitSocket();
	void CloseSocket(stClientInfo* pClientInfo, bool bIsForce = false);

	// -- ������ �Լ� -- //
	bool BindandListen(int nBindPort);
	bool StartServer();
	// WaitingThread Queue���� ����� ��������� ����
	bool CreateWokerThread();
	// acceptó�� ������ ����
	bool CreateAccepterThread();
	// ������� �ʴ� Ŭ�� ���� ����ü ��ȯ
	stClientInfo* GetEmptyClientInfo();

	// CompletionPort ��ü�� ���ϰ� CompletionKey�� ����
	bool BindIOCompletionPort(stClientInfo* pClientInfo);
	// WSARecv Overlapped I/O �۾��� ��Ų��
	bool BindRecv(stClientInfo* pClientInfo);
	// WSASend Overlapped I/O �۾��� ��Ų��
	bool SendMsg(stClientInfo* pClientInfo, char* pMsg, int nLen);
	// I/O �۾� �Ϸ� �뺸�� �޾� ó���ϴ� �Լ�
	void WokerThread();
	// ���� �޴� ������
	void AccepterThread();

	// ���� �������� �����͸� ����
	void SetMainDlg(CChattingServerVer02Dlg* pMainDlg) { m_pMainDlg = pMainDlg; }
	CChattingServerVer02Dlg* GetMainDlg() { return m_pMainDlg; }

	// ---- Mysql ���� ---- //
	// ������ ���� ������ ����
	bool DivideUserInfo(char [MAX_BUFSIZE], stClientInfo* m_pClientInfo);
	// Mysql �ʱ�ȭ
	bool MysqlInit();
	// ������ �����带 �ı�
	void DestroyThread();
};

class CChattingServerVer02App : public CWinApp
{
public:
	CChattingServerVer02App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CChattingServerVer02App theApp;