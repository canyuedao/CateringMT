#pragma once


// CSLdlg �Ի���

class CSLdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSLdlg)

public:
	CSLdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSLdlg();

// �Ի�������
	enum { IDD = IDD_shuliang };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_ShuLiang;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonreturn();
};
