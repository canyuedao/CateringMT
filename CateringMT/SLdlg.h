#pragma once


// CSLdlg 对话框

class CSLdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSLdlg)

public:
	CSLdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSLdlg();

// 对话框数据
	enum { IDD = IDD_shuliang };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_ShuLiang;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonreturn();
};
