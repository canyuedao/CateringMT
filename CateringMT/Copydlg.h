#pragma once
#include "afxwin.h"


// CCopydlg 对话框

class CCopydlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCopydlg)

public:
	CCopydlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCopydlg();

// 对话框数据
	enum { IDD = IDD_copydlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	CEdit m_Edit;
	CString m_Name;
	afx_msg void OnBnClickedButtonview();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
