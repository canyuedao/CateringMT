#pragma once


// CZhucedlg 对话框

class CZhucedlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZhucedlg)

public:
	CZhucedlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZhucedlg();

	_RecordsetPtr m_pRs;
	CString m_Name;
	CString m_Pwd;
	CString m_Pwd1;
// 对话框数据
	enum { IDD = IDD_Zhuce };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonreset();	
};
