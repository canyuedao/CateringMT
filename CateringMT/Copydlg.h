#pragma once
#include "afxwin.h"


// CCopydlg �Ի���

class CCopydlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCopydlg)

public:
	CCopydlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCopydlg();

// �Ի�������
	enum { IDD = IDD_copydlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	CEdit m_Edit;
	CString m_Name;
	afx_msg void OnBnClickedButtonview();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
