#pragma once


// CChangepwddlg 对话框

class CChangepwddlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangepwddlg)

public:
	CChangepwddlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangepwddlg();

// 对话框数据
	enum { IDD = IDD_changepwd };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int i_limint;
	_RecordsetPtr m_pRs;
	CString m_Old;
	CString m_Pwd;
	CString m_Pwd1;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonreset();
};
