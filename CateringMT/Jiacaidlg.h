#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CJiacaidlg �Ի���

class CJiacaidlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJiacaidlg)

public:
	CJiacaidlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJiacaidlg();

// �Ի�������
	enum { IDD = IDD_jiacai };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:	
	double total_price;
	CString str_total;
	CListCtrl m_Caidan;
	CListCtrl m_CaidanCheck;
	CComboBox m_ZhuoHaoCombo;
	_RecordsetPtr m_pRs;
	CString m_ZhuoHao;
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtonsub();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeCombozhuohao();
	
	CEdit m_TotalPay;
	afx_msg void OnBnClickedButtonreset();

	afx_msg void OnCbnEditchangeCombozhuohao();
	CComboBox m_SearchCombo;
	afx_msg void OnCbnSelchangeCombosearch2();
	afx_msg void OnCbnEditchangeCombosearch2();
};
