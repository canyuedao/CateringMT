
// CateringMTDlg.h : 头文件
//

#pragma once


// CCateringMTDlg 对话框
class CCateringMTDlg : public CDialogEx
{
// 构造
public:
	CString str;
	//void OnCancel();
	CImageList m_Imagelist;
	CStatusBar m_Statusbar;
	CToolBar m_Toolbar;
	//virtual void OnOk();
	_RecordsetPtr m_pRs;
	CCateringMTDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CATERINGMT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuLogin();
	afx_msg void OnMenukaitai();
	afx_msg void OnMenuaddcai();
	afx_msg void OnMenujiezhang();
	afx_msg void OnMenujiesuan();
	afx_msg void OnMenuyuangong();
	afx_msg void OnMenujinhuo();
	afx_msg void OnMenuSpinfo();
	afx_msg void OnMenuCp();
	afx_msg void OnMenurishourucx();
	afx_msg void OnMenuyueshourucx();
	afx_msg void OnMenujinhuoselect();
	afx_msg void OnMenusqlcopy();
	afx_msg void OnMenusqlreturn();
	afx_msg void OnMenusqlnew();
	afx_msg void OnMenuquanxian();
	afx_msg void OnMenuabout();
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	void OnLogout();
	void OnCancel();
	afx_msg void OnMenupwd();
};
