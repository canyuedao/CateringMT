// Jinhuocxdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Jinhuocxdlg.h"
#include "afxdialogex.h"
#include <regex>
using namespace std;

extern CCateringMTApp theApp;
// CJinhuocxdlg 对话框

IMPLEMENT_DYNAMIC(CJinhuocxdlg, CDialogEx)

CJinhuocxdlg::CJinhuocxdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJinhuocxdlg::IDD, pParent)
	, m_Year(_T(""))
	, m_Month(_T(""))
	, m_Day(_T(""))
{

}

CJinhuocxdlg::~CJinhuocxdlg()
{
}

void CJinhuocxdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_year, m_Year);
	DDX_Text(pDX, IDC_EDIT_month, m_Month);
	DDX_Text(pDX, IDC_EDIT_day, m_Day);
	DDX_Control(pDX, IDC_LIST_jinhuo, m_List);
}


BEGIN_MESSAGE_MAP(CJinhuocxdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_check, &CJinhuocxdlg::OnBnClickedButtoncheck)
	ON_BN_CLICKED(IDCANCEL, &CJinhuocxdlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_year, &CJinhuocxdlg::OnEnChangeEdityear)
	ON_EN_CHANGE(IDC_EDIT_month, &CJinhuocxdlg::OnEnChangeEditmonth)
	ON_EN_CHANGE(IDC_EDIT_day, &CJinhuocxdlg::OnEnChangeEditday)
END_MESSAGE_MAP()


// CJinhuocxdlg 消息处理程序
BOOL CJinhuocxdlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	m_List.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_HEADERDRAGDROP);
	m_List.InsertColumn(0, CString("商品名"),LVCFMT_LEFT,180);
	m_List.InsertColumn(1, CString("数量"),LVCFMT_LEFT,45);
	m_List.InsertColumn(2, CString("价格"),LVCFMT_LEFT,45);
	return TRUE;
}


void CJinhuocxdlg::OnBnClickedButtoncheck()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_Year.IsEmpty() | m_Month.IsEmpty() | m_Day.IsEmpty()){
		AfxMessageBox(CString("请输入一个时间"));
		return;
	}
	m_List.DeleteAllItems();
	//输入日期格式处理
	regex r("^0[1-9]$");
	smatch d_results;
	int i_day = atoi((char*)(_bstr_t)m_Day);
	string str_day = (char*)(_bstr_t)(m_Day);
	CString cstr_day;
	if (i_day < 10){
		if (regex_search(str_day, d_results, r)){
			cstr_day = m_Day;
		}
		else{
			cstr_day = CString("0") + m_Day;
		}
		
	}
	else
		cstr_day = m_Day;
	smatch m_results;
	int i_month = atoi((char*)(_bstr_t)m_Month);
	string str_month = (char*)(_bstr_t)(m_Month);
	CString cstr_month;
	if (i_month < 10){
		if (regex_search(str_month, m_results, r)){
			cstr_month = m_Month;
		}
		else{
			cstr_month = CString("0") + m_Month;
		}

	}
	else
		cstr_month = m_Month;
	//处理结束
	CString str_time = m_Year + "-" + cstr_month + "-" + cstr_day;
	CString sql = CString("select * from jinhuoinfo where 进货时间='") + str_time + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_name, str_num, str_price;
	if (m_pRs->adoEOF){
		MessageBox(CString("没有数据！"), CString("进货查询"));
	}
	while (!m_pRs->adoEOF){
		str_name = m_pRs->GetCollect("商品名");
		str_num = m_pRs->GetCollect("商品数量");
		str_price = m_pRs->GetCollect("商品价格");
		m_List.InsertItem(0, CString(""));
		m_List.SetItemText(0, 0, str_name);
		m_List.SetItemText(0, 1, str_num);
		m_List.SetItemText(0, 2, str_price);
		m_pRs->MoveNext();
	}		
}


void CJinhuocxdlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CJinhuocxdlg::OnEnChangeEdityear()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CTime time = CTime::GetCurrentTime();
	CString str_year = time.Format("%Y");
	int inow_year = atoi((char*)(_bstr_t)str_year);
	int iin_year = atoi((char*)(_bstr_t)m_Year);
	if (inow_year < iin_year){
		AfxMessageBox(CString("请输入一个有效日期"));
		m_Year = "";
		UpdateData(false);
	}
}


void CJinhuocxdlg::OnEnChangeEditmonth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CTime time = CTime::GetCurrentTime();
	CString str_month = time.Format("%m");
	int inow_month = atoi((char*)(_bstr_t)str_month);
	int iin_month = atoi((char*)(_bstr_t)m_Month);
	CString str_year = time.Format("%Y");
	int inow_year = atoi((char*)(_bstr_t)str_year);
	int iin_year = atoi((char*)(_bstr_t)m_Year);
	if (iin_year == inow_year){
		if (inow_month < iin_month){
			AfxMessageBox(CString("请输入一个有效日期"));
			m_Month = "";
			UpdateData(false);
		}
	}
	else {
		if (iin_month > 12){
			AfxMessageBox(CString("请输入一个有效日期"));
			m_Month = "";
			UpdateData(false);
		}
	}
}


void CJinhuocxdlg::OnEnChangeEditday()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CTime time = CTime::GetCurrentTime();
	CString str_day = time.Format("%d");
	int inow_day = atoi((char*)(_bstr_t)str_day);
	int iin_day = atoi((char*)(_bstr_t)m_Day);
	CString str_month = time.Format("%m");
	int inow_month = atoi((char*)(_bstr_t)str_month);
	int iin_month = atoi((char*)(_bstr_t)m_Month);
	CString str_year = time.Format("%Y");
	int inow_year = atoi((char*)(_bstr_t)str_year);
	int iin_year = atoi((char*)(_bstr_t)m_Year);
	if ((iin_month == inow_month) && (iin_year == inow_year)){
		if (inow_day < iin_day){
			AfxMessageBox(CString("请输入一个有效日期"));
			m_Day = "";
			UpdateData(false);
		}
	}
	else {
		if (iin_day > 31){
			AfxMessageBox(CString("请输入一个有效日期"));
			m_Day = "";
			UpdateData(false);
		}
	}
}
