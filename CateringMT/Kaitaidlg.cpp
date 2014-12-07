// Kaitaidlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Kaitaidlg.h"
#include "afxdialogex.h"
#include "Diancaidlg.h"

extern CCateringMTApp theApp;
// CKaitaidlg 对话框

IMPLEMENT_DYNAMIC(CKaitaidlg, CDialogEx)

CKaitaidlg::CKaitaidlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKaitaidlg::IDD, pParent)
	, m_ZhuoHao(_T(""))
{

}

CKaitaidlg::~CKaitaidlg()
{
}

void CKaitaidlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Zhuolist);
	DDX_Text(pDX, IDC_EDIT1, m_ZhuoHao);
}


BEGIN_MESSAGE_MAP(CKaitaidlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CKaitaidlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_return, &CKaitaidlg::OnBnClickedButtonreturn)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CKaitaidlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CKaitaidlg 消息处理程序
BOOL CKaitaidlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_kaitai)), TRUE);
	m_Zhuolist.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_Zhuolist.InsertColumn(0, CString("桌号"), LVCFMT_LEFT, 140, 0);
	m_Zhuolist.InsertColumn(1, CString("状态"), LVCFMT_LEFT, 140, 1);
	CString sql = CString("select * from TableUSE");
	int i = 0;
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	while (m_pRs->adoEOF == 0){
		CString str = (CString)(m_pRs->GetCollect("桌号"));//(CString)(char *)(_bstr_t)(m_pRs->GetCollect("桌号"));
		int tableuseid = atoi((char*)(_bstr_t)(m_pRs->GetCollect("TableUSEID")));
		m_Zhuolist.InsertItem(i, CString(""));
		m_Zhuolist.SetItemText(i, 0, str);
		if (tableuseid == 0){
			m_Zhuolist.SetItemText(i, 1, CString("空闲"));
		}
		if (tableuseid == 1){
			m_Zhuolist.SetItemText(i, 1, CString("有人"));
		}
		i++;
		m_pRs->MoveNext();
	}
	return TRUE;
}

void CKaitaidlg::OnBnClickedButtonOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_ZhuoHao.IsEmpty()){
		AfxMessageBox(CString("桌号不能为空"));
	}
	else{
		CString str = CString("select * from TableUSE where TableUSEID=1");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(str), NULL, adCmdText);
		while (!m_pRs->adoEOF){
			if (m_ZhuoHao == CString(m_pRs->GetCollect("桌号"))){
				AfxMessageBox(CString("有人了"));
				m_ZhuoHao = "";
				UpdateData(false);
				return;
			}
			m_pRs->MoveNext();
		}
		m_pRs = NULL;
		CString sql = CString("select * from TableUSE where 桌号=") + m_ZhuoHao;
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		if (m_pRs->adoEOF){
			AfxMessageBox(CString("没有这种餐台"));
			m_ZhuoHao = "";
			UpdateData(false);
			return;
		}
		CDiancaidlg dlg;		
		dlg.m_ZhuoHao = m_ZhuoHao;
		dlg.DoModal();
		CDialogEx::OnOK();
		m_pRs = NULL;
	}
}


void CKaitaidlg::OnBnClickedButtonreturn()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CKaitaidlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	str = m_Zhuolist.GetItemText(m_Zhuolist.GetSelectionMark(), 0);
	m_ZhuoHao = str;
	UpdateData(false);
	*pResult = 0;
}
