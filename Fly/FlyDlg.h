// FlyDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CFlyDlg dialog

class CFlyDlg : public CDialog
{
// Construction
public:
	CFlyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FLY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrFr;
public:
	CEdit m_ctrTd;
public:
	afx_msg void OnBnClickedBfr();
public:
	afx_msg void OnBnClickedBtd();
public:
	afx_msg void OnBnClickedBrnm();
public:
	afx_msg void OnBnClickedBcp();
public:
	void Krename(CString strDir);
public:
	void Kcopy(CString strFromPath, CString strToPath);
public:
	int GetRenameFileCount(CString strDir);
public:
	int GetCopyFileCount(CString strDir);
public:
	long long int m_iFilecount;
public:
	int m_iFilecurcount;
public:
	CStatic m_ctrSt;
};
