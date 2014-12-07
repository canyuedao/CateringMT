#pragma once
#include "afxcmn.h"


// CJinhuocxdlg 对话框

class CJinhuocxdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJinhuocxdlg)

public:
	CJinhuocxdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJinhuocxdlg();

// 对话框数据
	enum { IDD = IDD_jinhuocxdlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	CString m_Year;
	CString m_Month;
	CString m_Day;
	CListCtrl m_List;
	afx_msg void OnBnClickedButtoncheck();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdityear();
	afx_msg void OnEnChangeEditmonth();
	afx_msg void OnEnChangeEditday();
};
