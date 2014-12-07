#pragma once
#include "afxwin.h"


// CReturndlg 对话框

class CReturndlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReturndlg)

public:
	CReturndlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReturndlg();

// 对话框数据
	enum { IDD = IDD_returndlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	afx_msg void OnBnClickedButtonview();
	afx_msg void OnBnClickedButtonreturn();
	afx_msg void OnBnClickedCancel();
};
