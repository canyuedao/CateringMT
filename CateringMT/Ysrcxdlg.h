#pragma once


// CYsrcxdlg �Ի���

class CYsrcxdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYsrcxdlg)

public:
	CYsrcxdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYsrcxdlg();

// �Ի�������
	enum { IDD = IDD_ysrcxdlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	CString m_Year;
	CString m_Month;
	CString m_Day;
	afx_msg void OnBnClickedButtoncheck();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdityear();
	afx_msg void OnEnChangeEditmonth();
	afx_msg void OnEnChangeEditday();
};
