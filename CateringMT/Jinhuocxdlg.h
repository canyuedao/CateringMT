#pragma once
#include "afxcmn.h"


// CJinhuocxdlg �Ի���

class CJinhuocxdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJinhuocxdlg)

public:
	CJinhuocxdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJinhuocxdlg();

// �Ի�������
	enum { IDD = IDD_jinhuocxdlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
