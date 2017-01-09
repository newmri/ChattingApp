#pragma once


// CDEnroll dialog

class CDEnroll : public CDialogEx
{
	DECLARE_DYNAMIC(CDEnroll)

public:
	CDEnroll(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDEnroll();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDEnroll };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEok();
};
