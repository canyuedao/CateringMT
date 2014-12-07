// Jinhuodlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Jinhuodlg.h"
#include "afxdialogex.h"
#include "SLdlg.h"
#include <string>
using namespace std;

extern CCateringMTApp theApp;
// CJinhuodlg 对话框

IMPLEMENT_DYNAMIC(CJinhuodlg, CDialogEx)

CJinhuodlg::CJinhuodlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJinhuodlg::IDD, pParent)
{

}

CJinhuodlg::~CJinhuodlg()
{
}

void CJinhuodlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_foodlist, m_Foodlist);
	DDX_Control(pDX, IDC_LIST_foodbill, m_Foodbill);
	DDX_Control(pDX, IDC_EDIT_jinhuotime, m_Time);
	DDX_Control(pDX, IDC_EDIT_totalpay, m_TotalPay);
	DDX_Control(pDX, IDC_COMBO_search, m_SearchCombo);
}


BEGIN_MESSAGE_MAP(CJinhuodlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_add, &CJinhuodlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_remove, &CJinhuodlg::OnBnClickedButtonremove)
	ON_BN_CLICKED(IDOK, &CJinhuodlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_reset, &CJinhuodlg::OnBnClickedButtonreset)
	ON_BN_CLICKED(IDCANCEL, &CJinhuodlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_search, &CJinhuodlg::OnCbnSelchangeCombosearch)
	ON_CBN_EDITCHANGE(IDC_COMBO_search, &CJinhuodlg::OnCbnEditchangeCombosearch)
END_MESSAGE_MAP()


// CJinhuodlg 消息处理程序


BOOL CJinhuodlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)),TRUE);
	CTime time = CTime::GetCurrentTime();
	CString str_time = time.Format("%Y-%m-%d");
	m_Time.SetWindowText(str_time);
	m_Foodlist.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_Foodlist.InsertColumn(0, CString("商品名"), LVCFMT_LEFT,110,0);
	m_Foodlist.InsertColumn(1, CString("单价（元）"), LVCFMT_LEFT,80,1);
	m_Foodbill.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_Foodbill.InsertColumn(0, CString("商品名"), LVCFMT_LEFT,110,0);
	m_Foodbill.InsertColumn(1, CString("数量（斤）"), LVCFMT_LEFT,80,1);
	CString sql = CString("select * from shangpininfo");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_name, str_price;
	while (!m_pRs->adoEOF){
		str_name = m_pRs->GetCollect("商品名");
		str_price = m_pRs->GetCollect("商品单价");
		m_Foodlist.InsertItem(0, CString(""));
		m_Foodlist.SetItemText(0, 0, str_name);
		m_Foodlist.SetItemText(0, 1, str_price);
		m_pRs->MoveNext();
	}
	m_TotalPay.SetWindowText(CString(""));	
	return TRUE;

}


void CJinhuodlg::OnBnClickedButtonadd()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_Foodlist.GetSelectionMark() == -1){
		//AfxMessageBox(CString("没有菜品可加！"));
		return;
	}
	CSLdlg SLdlg;
	if (SLdlg.DoModal() == IDOK){
		int i = m_Foodlist.GetSelectionMark();
		CString str = m_Foodlist.GetItemText(i, 0);
		m_Foodbill.InsertItem(0, CString(""));
		m_Foodbill.SetItemText(0, 0, str);
		m_Foodbill.SetItemText(0, 1, SLdlg.m_ShuLiang);
		
		CString sql = CString("select * from shangpininfo where 商品名='") + str + CString("'");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);		
		CString str_price = m_pRs->GetCollect("商品单价");
		double each_total = atof((char*)(_bstr_t)str_price)*atof((char*)(_bstr_t)SLdlg.m_ShuLiang);		
		total_price += each_total;
		str_total = CString((char*)(_bstr_t)total_price);
		m_TotalPay.SetWindowText(str_total);
		UpdateData(false);
		//m_Num = SLdlg.m_ShuLiang;
	}
}


void CJinhuodlg::OnBnClickedButtonremove()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_Foodlist.GetSelectionMark() == -1){
		//AfxMessageBox(CString("没有菜品可加！"));
		return;
	}
	int i = m_Foodbill.GetSelectionMark();
	CString str = m_Foodbill.GetItemText(i, 0);
	CString str_num = m_Foodbill.GetItemText(i, 1);
	m_Foodbill.DeleteItem(m_Foodbill.GetSelectionMark());
	CString sql = CString("select * from shangpininfo where 商品名='") + str + CString("'");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_price = m_pRs->GetCollect("商品单价");
	double each_total = atof((char*)(_bstr_t)str_price)*atof((char*)(_bstr_t)str_num);
	total_price -= each_total;
	str_total = CString((char*)(_bstr_t)total_price);
	m_TotalPay.SetWindowText(str_total);
	UpdateData(false);
}


void CJinhuodlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData();
	int k = m_Foodbill.GetItemCount();
	if (k <= 0){
		AfxMessageBox(CString("请选择商品!"));
		return;
	}
	else{
		CString sql;
		CString str_name, str_num, str_price;
		
		for (int i = 0; i < k; i++){
			str_name = m_Foodbill.GetItemText(i, 0);
			str_num = m_Foodbill.GetItemText(i, 1);
			sql = CString("select * from shangpininfo where 商品名='") + str_name + CString("'");
			m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
			CString str_time;
			m_Time.GetWindowText(str_time);
			if (!m_pRs->adoEOF){
				str_price = m_pRs->GetCollect("商品单价");
				double value_eachtotal = atof((char*)(_bstr_t)str_num)*atof((char*)(_bstr_t)str_price);
				CString str_eachtotal = (CString)(char*)(_bstr_t)(value_eachtotal);
				CString sql_1 = CString("select * from jinhuoinfo where 进货时间='") + str_time + "' and 商品名='" + str_name + "'";
				m_pRs = theApp.m_pCon->Execute(_bstr_t(sql_1), NULL, adCmdText);
				if (!m_pRs->adoEOF){					
					CString sql = CString("update jinhuoinfo set 商品数量=商品数量+") + str_num + ",商品价格=商品价格+" 
						+ str_eachtotal + " where 进货时间='" + str_time + "' and 商品名='" + str_name + "'";
					theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
				}
				else{
					CString sql = CString("insert into jinhuoinfo(进货时间,商品名,商品数量,商品价格) values('") + str_time + "','"
						+ str_name + "'," + str_num + "," + str_eachtotal + ")";
					theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
				}				
			}
			else{
				MessageBox(CString("数据错误：无法获取商品---") + str_name 
					+ CString(" 的单价！/n请检查数据文件！"), CString("系统提示"), MB_OK | MB_ICONEXCLAMATION);

				return;
			}
		}
		AfxMessageBox(CString("操作成功！"));
		
	}	
	CDialogEx::OnOK();
}


void CJinhuodlg::OnBnClickedButtonreset()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Foodbill.DeleteAllItems();
	total_price = 0;
	str_total = "";
	m_TotalPay.SetWindowText(str_total);
	UpdateData(false);
}


void CJinhuodlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CJinhuodlg::OnCbnSelchangeCombosearch()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_SearchCombo.GetCurSel() == CB_ERR){
		//AfxMessageBox(CString("没有菜品可加！"));
		return;
	}

	//CString sql = CString("select * from caishiinfo")
	CSLdlg SLdlg;
	if (SLdlg.DoModal() == IDOK){
		CString str_selection;
		m_SearchCombo.GetLBText(m_SearchCombo.GetCurSel(), str_selection);
		m_Foodbill.InsertItem(0, CString(""));
		m_Foodbill.SetItemText(0, 0, str_selection);
		m_Foodbill.SetItemText(0, 1, SLdlg.m_ShuLiang);

		CString sql = CString("select * from shangpininfo where 商品名='") + str_selection + CString("'");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str_price = m_pRs->GetCollect("商品单价");
		double each_total = atof((char*)(_bstr_t)str_price)*atof((char*)(_bstr_t)SLdlg.m_ShuLiang);
		total_price += each_total;
		str_total = CString((char*)(_bstr_t)total_price);
		m_TotalPay.SetWindowText(str_total);
		UpdateData(false);
	}
}


void CJinhuodlg::OnCbnEditchangeCombosearch()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CString cstr_search;
	m_SearchCombo.GetWindowText(cstr_search);

	//数据初始化开始
	int sel = m_SearchCombo.GetCount();
	for (int i = 0; i <sel; i++){
		m_SearchCombo.DeleteString(0);
	}
	//初始化结束
	if (cstr_search.IsEmpty()){
		return;
	}

	/*
	m_SearchCombo.ResetContent();
	m_SearchCombo.SetWindowText(cstr_search);
	m_SearchCombo.SetFocus();
	m_SearchCombo.SetCurSel(sel);
	*/

	CString sql = CString("select * from shangpininfo");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString cstr_list;
	string str_search = (_bstr_t)(cstr_search);
	string str_list;
	while (!m_pRs->adoEOF){
		cstr_list = m_pRs->GetCollect("商品名");
		str_list = (_bstr_t)(cstr_list);
		if (str_list.find(str_search) != string::npos){
			m_SearchCombo.AddString(cstr_list);
		}
		m_pRs->MoveNext();
	}
	m_SearchCombo.ShowDropDown();
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	UpdateData(false);
}
