#pragma once


// CZhucedlg �Ի���

class CZhucedlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZhucedlg)

public:
	CZhucedlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZhucedlg();

	_RecordsetPtr m_pRs;
	CString m_Name;
	CString m_Pwd;
	CString m_Pwd1;
// �Ի�������
	enum { IDD = IDD_Zhuce };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonreset();	
};
