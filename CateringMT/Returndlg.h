#pragma once
#include "afxwin.h"


// CReturndlg �Ի���

class CReturndlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReturndlg)

public:
	CReturndlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReturndlg();

// �Ի�������
	enum { IDD = IDD_returndlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	afx_msg void OnBnClickedButtonview();
	afx_msg void OnBnClickedButtonreturn();
	afx_msg void OnBnClickedCancel();
};
