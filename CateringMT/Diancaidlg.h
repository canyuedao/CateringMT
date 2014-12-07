#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDiancaidlg 对话框

class CDiancaidlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDiancaidlg)

public:
	CDiancaidlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDiancaidlg();

// 对话框数据
	enum { IDD = IDD_diancai };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	double total_price;
	CString str_total;
	CString m_ZhuoHao;
	CListCtrl m_Caidan;
	CListCtrl m_CaidanCheck;
	_RecordsetPtr m_pRs;
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtonsub();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_TotalPay;
	afx_msg void OnBnClickedButtonreset();

	
	CComboBox m_SearchCombo;
	afx_msg void OnCbnSelchangeCombosearch();
	afx_msg void OnCbnEditchangeCombosearch();
};
