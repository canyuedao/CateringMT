// Quanxiandlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Quanxiandlg.h"
#include "afxdialogex.h"
#include <string>
using namespace std;

extern CCateringMTApp theApp;
// CQuanxiandlg 对话框

IMPLEMENT_DYNAMIC(CQuanxiandlg, CDialogEx)

CQuanxiandlg::CQuanxiandlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQuanxiandlg::IDD, pParent)
{

}

CQuanxiandlg::~CQuanxiandlg()
{
}

void CQuanxiandlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_select, m_SelectCombo);
}


BEGIN_MESSAGE_MAP(CQuanxiandlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CQuanxiandlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CQuanxiandlg::OnBnClickedCancel)
	ON_CBN_EDITCHANGE(IDC_COMBO_select, &CQuanxiandlg::OnCbnEditchangeComboselect)
	ON_BN_CLICKED(IDC_RADIO_0, &CQuanxiandlg::OnBnClickedRadio0)
	ON_BN_CLICKED(IDC_RADIO_1, &CQuanxiandlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO_2, &CQuanxiandlg::OnBnClickedRadio2)	
END_MESSAGE_MAP()


// CQuanxiandlg 消息处理程序
BOOL CQuanxiandlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	CString sql_1 = CString("select Power from Login where Uname='") + theApp.name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql_1), NULL, adCmdText);
	CString str_power;	
	if (!m_pRs->adoEOF){		
		str_power = m_pRs->GetCollect("Power");
		i_power = atoi((char*)(_bstr_t)str_power);
		CWnd *pWnd = GetDlgItem(IDC_RADIO_0);
		if (i_power == 0){
			pWnd->ShowWindow(SW_HIDE);
		}
		if (i_power == 9){
			pWnd->ShowWindow(SW_SHOW);
		}
	}	
	
	CString sql = CString("select * from Login where Power<>9");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_name;
	CString str_power_2;
	int i_power_2;
	while (!m_pRs->adoEOF){
		str_name = m_pRs->GetCollect("Uname");
		str_power_2 = m_pRs->GetCollect("Power");
		i_power_2 = atoi((char*)(_bstr_t)str_power_2);
		if (i_power == 9){
			m_SelectCombo.AddString(str_name);					
		}
		else{
			if (i_power_2 != 0){
				m_SelectCombo.AddString(str_name);
			}
		}		
		m_pRs->MoveNext();
	}
	
	return TRUE;
}


void CQuanxiandlg::OnCbnEditchangeComboselect()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CString cstr_name;
	m_SelectCombo.GetWindowText(cstr_name);

	//数据初始化开始
	int sel = m_SelectCombo.GetCount();
	for (int i = 0; i <sel; i++){
		m_SelectCombo.DeleteString(0);
	}
	//初始化结束
	if (cstr_name.IsEmpty()){
		return;
	}

	/*
	m_SearchCombo.ResetContent();
	m_SearchCombo.SetWindowText(cstr_search);
	m_SearchCombo.SetFocus();
	m_SearchCombo.SetCurSel(sel);
	*/
	CString sql = CString("select * from Login where Power<>9");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);	
	string str_name = (_bstr_t)(cstr_name);
	CString cstr_power_2, cstr_name_2;	
	string str_power_2, str_name_2;
	int i_power_2;
	while (!m_pRs->adoEOF){
		cstr_name_2 = m_pRs->GetCollect("Uname");
		cstr_power_2 = m_pRs->GetCollect("Power");
		str_name_2 = (_bstr_t)(cstr_name_2);
		str_power_2 = (_bstr_t)(cstr_power_2);
		i_power_2 = atoi((char*)(_bstr_t)cstr_power_2);
		if (i_power == 9){
			if (str_name_2.find(str_name) != string::npos){
				m_SelectCombo.AddString(cstr_name_2);
			}						
		}
		else{
			if (i_power_2 != 0){
				if (str_name_2.find(str_name) != string::npos){
					m_SelectCombo.AddString(cstr_name_2);
				}				
			}
		}
		m_pRs->MoveNext();
	}	
	m_SelectCombo.ShowDropDown();
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	UpdateData(false);
}


void CQuanxiandlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str_name;
	m_SelectCombo.GetWindowText(str_name);
	if (str_name.IsEmpty()){
		AfxMessageBox(CString("请选择一个用户"));
		return;
	}
	CString sql_0 = CString("select * from Login where Uname='") + str_name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql_0), NULL, adCmdText);
	if (m_pRs->adoEOF){
		AfxMessageBox(CString("没有该用户"));
		return;
	}
	if (!b_checked){
		AfxMessageBox(CString("请选择一个权限"));
		return;
	}
	CString str_power = (CString)(char*)(_bstr_t)(i_power);
	CString sql = CString("update Login set Power=") + str_power + " where Uname='" + str_name + "'";
	theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	AfxMessageBox(CString("设置成功！"));	
	CDialogEx::OnOK();
}


void CQuanxiandlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}





void CQuanxiandlg::OnBnClickedRadio0()
{
	// TODO:  在此添加控件通知处理程序代码
	i_power = 0;
	b_checked = true;
}


void CQuanxiandlg::OnBnClickedRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
	i_power = 1;
	b_checked = true;
}


void CQuanxiandlg::OnBnClickedRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	i_power = 2;
	b_checked = true;
}



