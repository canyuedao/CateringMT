#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CJinhuodlg �Ի���

class CJinhuodlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJinhuodlg)

public:
	CJinhuodlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJinhuodlg();

// �Ի�������
	enum { IDD = IDD_jinhuodlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	//CString m_Num;
	_RecordsetPtr m_pRs;
	CString str_total;
	double total_price;
	CEdit m_Time;
	CEdit m_TotalPay;
	CListCtrl m_Foodlist;
	CListCtrl m_Foodbill;
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtonremove();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonreset();
	afx_msg void OnBnClickedCancel();
	
	CComboBox m_SearchCombo;
	afx_msg void OnCbnSelchangeCombosearch();
	afx_msg void OnCbnEditchangeCombosearch();
};
