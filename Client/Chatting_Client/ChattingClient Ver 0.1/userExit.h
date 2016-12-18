#pragma once


// userExit dialog

class userExit : public CDialogEx
{
	DECLARE_DYNAMIC(userExit)

public:
	userExit(CWnd* pParent = NULL);   // standard constructor
	virtual ~userExit();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
