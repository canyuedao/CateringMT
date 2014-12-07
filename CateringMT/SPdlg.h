#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSPdlg 对话框

class CSPdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSPdlg)
	
public:
	CSPdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSPdlg();

// 对话框数据
	enum { IDD = IDD_SPinfodlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	CListCtrl m_SpList;
	CString m_Name;
	CString m_Price;
	afx_msg void OnNMDblclkListshangpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtonedit();
	afx_msg void OnBnClickedButtondelete();
	afx_msg void OnBnClickedButtoncancel();
	CComboBox m_SearchCombo;
	afx_msg void OnCbnSelchangeCombosearch();
	afx_msg void OnCbnEditchangeCombosearch();
	afx_msg void OnEnChangeEditname();
};
