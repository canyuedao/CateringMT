#pragma once
#include "afxwin.h"


// CQuanxiandlg �Ի���

class CQuanxiandlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQuanxiandlg)

public:
	CQuanxiandlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQuanxiandlg();

// �Ի�������
	enum { IDD = IDD_quanxiandlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int i_power;
	bool b_checked = false;
	_RecordsetPtr m_pRs;
	CComboBox m_SelectCombo;	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnEditchangeComboselect();
	afx_msg void OnBnClickedRadio0();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnCbnDropdownComboselect();
};
