#pragma once
#include "afxwin.h"


// CLogindlg �Ի���

class CLogindlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogindlg)

public:
	CLogindlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogindlg();

// �Ի�������
	enum { IDD = IDD_Logindlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��		
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Uname;	
	CString m_Upasswd;
	_RecordsetPtr m_pRs;
	int i;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
