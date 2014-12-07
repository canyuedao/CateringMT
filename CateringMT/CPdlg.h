#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCPdlg 对话框

class CCPdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCPdlg)

public:
	CCPdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCPdlg();

// 对话框数据
	enum { IDD = IDD_CPinfodlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	CString m_Name;
	CString m_Price;
	CListCtrl m_CpList;
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtonedit();
	afx_msg void OnBnClickedButtondelete();
	afx_msg void OnBnClickedButtoncancel();	
	afx_msg void OnNMDblclkListcaishi(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_SearchCombo;
	afx_msg void OnCbnSelchangeCombosearch();
	afx_msg void OnCbnEditchangeCombosearch();
	afx_msg void OnEnChangeEditname();
};
