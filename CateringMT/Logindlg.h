#pragma once
#include "afxwin.h"


// CLogindlg 对话框

class CLogindlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogindlg)

public:
	CLogindlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogindlg();

// 对话框数据
	enum { IDD = IDD_Logindlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持		
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Uname;	
	CString m_Upasswd;
	_RecordsetPtr m_pRs;
	int i;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
