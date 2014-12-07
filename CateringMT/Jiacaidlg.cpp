// Jiacaidlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Jiacaidlg.h"
#include "afxdialogex.h"
#include "SLdlg.h"
#include <string>
using namespace std;

extern CCateringMTApp theApp;
// CJiacaidlg �Ի���


IMPLEMENT_DYNAMIC(CJiacaidlg, CDialogEx)

CJiacaidlg::CJiacaidlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJiacaidlg::IDD, pParent)
{

}

CJiacaidlg::~CJiacaidlg()
{
}

void CJiacaidlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_caidan, m_Caidan);
	DDX_Control(pDX, IDC_LIST_caidancheck, m_CaidanCheck);
	DDX_Control(pDX, IDC_COMBO_zhuohao, m_ZhuoHaoCombo);
	DDX_Control(pDX, IDC_EDIT_totalpay, m_TotalPay);
	DDX_Control(pDX, IDC_COMBO_search2, m_SearchCombo);
}


BEGIN_MESSAGE_MAP(CJiacaidlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_add, &CJiacaidlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_sub, &CJiacaidlg::OnBnClickedButtonsub)
	ON_BN_CLICKED(IDOK, &CJiacaidlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CJiacaidlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_zhuohao, &CJiacaidlg::OnCbnSelchangeCombozhuohao)
	ON_BN_CLICKED(IDC_BUTTON_reset, &CJiacaidlg::OnBnClickedButtonreset)
	ON_CBN_EDITCHANGE(IDC_COMBO_zhuohao, &CJiacaidlg::OnCbnEditchangeCombozhuohao)
	ON_CBN_SELCHANGE(IDC_COMBO_search2, &CJiacaidlg::OnCbnSelchangeCombosearch2)
	ON_CBN_EDITCHANGE(IDC_COMBO_search2, &CJiacaidlg::OnCbnEditchangeCombosearch2)
END_MESSAGE_MAP()


// CJiacaidlg ��Ϣ�������

BOOL CJiacaidlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_diancai)), TRUE);
	CString sql = CString("select * from caishiinfo");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	m_Caidan.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_Caidan.InsertColumn(0, CString("����"), LVCFMT_LEFT, 110, 0);
	m_Caidan.InsertColumn(1, CString("�˼ۣ�Ԫ��"), LVCFMT_LEFT, 80, 1);
	int i = 0;
	while (!m_pRs->adoEOF){
		CString str = (CString)(m_pRs->GetCollect("����")); //(CString)(char *)(_bstr_t)(m_pRs->GetCollect("����"));
		CString str2 = (CString)(m_pRs->GetCollect("�˼�")); //(CString)(char *)(_bstr_t)(m_pRs->GetCollect("�˼�"));
		m_Caidan.InsertItem(i, CString(""));
		m_Caidan.SetItemText(i, 0, str);
		m_Caidan.SetItemText(i, 1, str2);
		i++;
		m_pRs->MoveNext();
	}
	m_CaidanCheck.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_CaidanCheck.InsertColumn(0, CString("����"), LVCFMT_LEFT, 110, 0);
	m_CaidanCheck.InsertColumn(1, CString("�������̣�"), LVCFMT_LEFT, 80, 1);

	CString str = CString("select distinct ���� from paybill");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(str), NULL, adCmdText);
	while (!m_pRs->adoEOF){
		CString str = m_pRs->GetCollect("����");
		m_ZhuoHaoCombo.AddString(str);
		m_pRs->MoveNext();
	}
	m_TotalPay.SetWindowText(str_total);
	UpdateData(false);
	return TRUE;
}

void CJiacaidlg::OnBnClickedButtonadd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_Caidan.GetSelectionMark() == -1){
		//AfxMessageBox(CString("û�в�Ʒ�ɼӣ�"));
		return;
	}
	CSLdlg SLdlg;
	if (SLdlg.DoModal() == IDOK){
		int i = m_Caidan.GetSelectionMark();
		CString str = m_Caidan.GetItemText(i, 0);
		m_CaidanCheck.InsertItem(0, CString(""));
		m_CaidanCheck.SetItemText(0, 0, str);
		m_CaidanCheck.SetItemText(0, 1, SLdlg.m_ShuLiang);	

		CString sql = CString("select * from caishiinfo where ����='") + str + CString("'");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str_price = m_pRs->GetCollect("�˼�");
		double each_total = atof((char*)(_bstr_t)str_price)*atof((char*)(_bstr_t)SLdlg.m_ShuLiang);
		total_price += each_total;
		str_total = CString((char*)(_bstr_t)total_price);
		m_TotalPay.SetWindowText(str_total);
		UpdateData(false);
	}
}


void CJiacaidlg::OnBnClickedButtonsub()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	if (m_CaidanCheck.GetSelectionMark() == -1){
		//AfxMessageBox(CString("û�в�Ʒ�ɼӣ�"));
		return;
	}
	int i = m_CaidanCheck.GetSelectionMark();
	CString str = m_CaidanCheck.GetItemText(i, 0);
	CString str_num = m_CaidanCheck.GetItemText(i, 1);
	m_CaidanCheck.DeleteItem(m_CaidanCheck.GetSelectionMark());
	CString sql = CString("select * from caishiinfo where ����='") + str + CString("'");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_price = m_pRs->GetCollect("�˼�");
	double each_total = atof((char*)(_bstr_t)str_price)*atof((char*)(_bstr_t)str_num);
	total_price -= each_total;
	str_total = CString((char*)(_bstr_t)total_price);
	m_TotalPay.SetWindowText(str_total);
	UpdateData(false);
}


void CJiacaidlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();	
	
	m_ZhuoHaoCombo.GetWindowText(m_ZhuoHao);
	if (m_ZhuoHao.IsEmpty()){
		AfxMessageBox(CString("��ѡ��Ҫ�Ӳ˵�����"));
		return;
	}
	int i = m_CaidanCheck.GetItemCount();
	if (i == 0){
		AfxMessageBox(CString("����"));
		return;
	}
	CString str2 = CString("delete from paybill where ����=") + m_ZhuoHao;
	theApp.m_pCon->Execute(_bstr_t(str2), NULL, adCmdText);
	CString sql, str_name, str_num, str1, str_value;
	double value = 0;
	for (int k = 0; k < i; k++){
		str_name = m_CaidanCheck.GetItemText(k, 0);
		str_num = m_CaidanCheck.GetItemText(k, 1);
		sql = CString("select * from caishiinfo where ����='") + str_name + CString("'");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		str1 = m_pRs->GetCollect("�˼�");
		value = atof(_bstr_t(str_num))*atof(_bstr_t(str1));
		str_value = (CString)(char *)(_bstr_t)value;
		sql = CString("insert into paybill(����,����,����,����) values(")
			+ m_ZhuoHao + ",'" + str_name + "'," + str_num + "," + str_value + CString(")");
		theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	}
	AfxMessageBox(CString("��˳ɹ�"));
	CString str = CString("update TableUSE set TableUSEID=1 where ����=") + m_ZhuoHao;
	theApp.m_pCon->Execute(_bstr_t(str), NULL, adCmdText);
	CDialogEx::OnOK();
}


void CJiacaidlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CJiacaidlg::OnCbnSelchangeCombozhuohao()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CString str;
	m_ZhuoHaoCombo.GetLBText(m_ZhuoHaoCombo.GetCurSel(), m_ZhuoHao);
	CString sql = CString("select * from paybill where ����=") + m_ZhuoHao;
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);	
	CString str_name, str_num, str_value;
	double total = 0;
	m_CaidanCheck.DeleteAllItems();
	
	while (!m_pRs->adoEOF){
		
		str_name = m_pRs->GetCollect("����");
		str_num = m_pRs->GetCollect("����");
		str_value = m_pRs->GetCollect("����");
		total += atof((char *)(_bstr_t)str_value);
		m_CaidanCheck.InsertItem(0, CString(""));
		m_CaidanCheck.SetItemText(0, 0, str_name);
		m_CaidanCheck.SetItemText(0, 1, str_num);	
		m_CaidanCheck.SetItemText(0, 2, str_value);
		m_pRs->MoveNext();
	}
	CString str_total = (CString)(char *)(_bstr_t)(total);
	m_TotalPay.SetWindowText(str_total);
	total_price = total;
	UpdateData(false);
}


void CJiacaidlg::OnBnClickedButtonreset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_CaidanCheck.DeleteAllItems();
	total_price = 0;
	str_total = "";
	m_TotalPay.SetWindowText(str_total);
	UpdateData(false);
}


void CJiacaidlg::OnCbnEditchangeCombozhuohao()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_CaidanCheck.DeleteAllItems();	
	CString str;
	m_ZhuoHaoCombo.GetWindowText(str);
	if (str.GetLength() == 4){
		UpdateData();
		CString sql = CString("select * from paybill where ����=") + str;
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str_name, str_num, str_value;
		double total = 0;
		if (m_pRs->adoEOF){			
			return;
		}
		while (!m_pRs->adoEOF){
			str_name = m_pRs->GetCollect("����");
			str_num = m_pRs->GetCollect("����");
			str_value = m_pRs->GetCollect("����");
			total += atof((char *)(_bstr_t)(str_value));
			m_CaidanCheck.InsertItem(0, CString(""));
			m_CaidanCheck.SetItemText(0, 0, str_name);
			m_CaidanCheck.SetItemText(0, 1, str_num);
			m_CaidanCheck.SetItemText(0, 2, str_value);
			m_pRs->MoveNext();
		}
		CString str_total = (CString)(char *)(_bstr_t)(total);
		m_TotalPay.SetWindowText(str_total);
		total_price = total;
		UpdateData(false);
	}
}


void CJiacaidlg::OnCbnSelchangeCombosearch2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_SearchCombo.GetCurSel() == CB_ERR){
		//AfxMessageBox(CString("û�в�Ʒ�ɼӣ�"));
		return;
	}

	//CString sql = CString("select * from caishiinfo")
	CSLdlg SLdlg;
	if (SLdlg.DoModal() == IDOK){
		CString str_selection;
		m_SearchCombo.GetLBText(m_SearchCombo.GetCurSel(), str_selection);
		m_CaidanCheck.InsertItem(0, CString(""));
		m_CaidanCheck.SetItemText(0, 0, str_selection);
		m_CaidanCheck.SetItemText(0, 1, SLdlg.m_ShuLiang);

		CString sql = CString("select * from caishiinfo where ����='") + str_selection + CString("'");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str_price = m_pRs->GetCollect("�˼�");
		double each_total = atof((char*)(_bstr_t)str_price)*atof((char*)(_bstr_t)SLdlg.m_ShuLiang);
		total_price += each_total;
		str_total = CString((char*)(_bstr_t)total_price);
		m_TotalPay.SetWindowText(str_total);
		UpdateData(false);
	}
}


void CJiacaidlg::OnCbnEditchangeCombosearch2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString cstr_search;
	m_SearchCombo.GetWindowText(cstr_search);

	//���ݳ�ʼ����ʼ
	int sel = m_SearchCombo.GetCount();
	for (int i = 0; i <sel; i++){
		m_SearchCombo.DeleteString(0);
	}
	//��ʼ������
	if (cstr_search.IsEmpty()){
		return;
	}

	/*
	m_SearchCombo.ResetContent();
	m_SearchCombo.SetWindowText(cstr_search);
	m_SearchCombo.SetFocus();
	m_SearchCombo.SetCurSel(sel);
	*/

	CString sql = CString("select * from caishiinfo");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString cstr_list;
	string str_search = (_bstr_t)(cstr_search);
	string str_list;
	while (!m_pRs->adoEOF){
		cstr_list = m_pRs->GetCollect("����");
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
