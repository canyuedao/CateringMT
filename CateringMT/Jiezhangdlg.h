#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CJiezhangdlg 对话框

class CJiezhangdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJiezhangdlg)

public:
	CJiezhangdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJiezhangdlg();

// 对话框数据
	enum { IDD = IDD_jiezhangdlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	_RecordsetPtr m_pRs;
	CComboBox m_ZhuoHaoCombo;
	CEdit m_YingShou;
	CEdit m_ShiShou;
	CEdit m_ZhaoLing;
	CListCtrl m_MingXi;
	afx_msg void OnCbnSelchangeCombozhuohao();
	afx_msg void OnCbnEditchangeCombozhuohao();
	afx_msg void OnEnChangeEditshishou();
	afx_msg void OnBnClickedButtonjiezhang();
	afx_msg void OnBnClickedButtonreturn();
};
