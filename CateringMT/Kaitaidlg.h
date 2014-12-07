#pragma once
#include "afxcmn.h"


// CKaitaidlg 对话框

class CKaitaidlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKaitaidlg)

public:
	CKaitaidlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKaitaidlg();

// 对话框数据
	enum { IDD = IDD_kaitaidlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Zhuolist;
	CString m_ZhuoHao;
	_RecordsetPtr m_pRs;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonreturn();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
