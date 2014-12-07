// SPdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "SPdlg.h"
#include "afxdialogex.h"
#include <regex>
using namespace std;
extern CCateringMTApp theApp;
// CSPdlg �Ի���

IMPLEMENT_DYNAMIC(CSPdlg, CDialogEx)

CSPdlg::CSPdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSPdlg::IDD, pParent)
	, m_Name(_T(""))
	, m_Price(_T(""))
{
	 
}

CSPdlg::~CSPdlg()
{
}

void CSPdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_shangpin, m_SpList);
	DDX_Text(pDX, IDC_EDIT_name, m_Name);
	DDX_Text(pDX, IDC_EDIT_price, m_Price);
	DDX_Control(pDX, IDC_COMBO_search, m_SearchCombo);
}


BEGIN_MESSAGE_MAP(CSPdlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_shangpin, &CSPdlg::OnNMDblclkListshangpin)
	ON_BN_CLICKED(IDC_BUTTON_add, &CSPdlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_edit, &CSPdlg::OnBnClickedButtonedit)
	ON_BN_CLICKED(IDC_BUTTON_delete, &CSPdlg::OnBnClickedButtondelete)
	ON_BN_CLICKED(IDC_BUTTON_cancel, &CSPdlg::OnBnClickedButtoncancel)
	ON_CBN_SELCHANGE(IDC_COMBO_search, &CSPdlg::OnCbnSelchangeCombosearch)
	ON_CBN_EDITCHANGE(IDC_COMBO_search, &CSPdlg::OnCbnEditchangeCombosearch)
	ON_EN_CHANGE(IDC_EDIT_name, &CSPdlg::OnEnChangeEditname)
END_MESSAGE_MAP()


// CSPdlg ��Ϣ�������
BOOL CSPdlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	CString sql = CString("select * from shangpininfo");
	try{
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	}
	catch (_com_error e){
		MessageBox(CString("���ݴ���:") + CString(e.ErrorMessage()), CString("ϵͳ��ʾ!"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	m_SpList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_SpList.InsertColumn(0, CString("��Ʒ��"), LVCFMT_LEFT, 200, 0);
	m_SpList.InsertColumn(1, CString("��Ʒ���ۣ�Ԫ��"), LVCFMT_LEFT, 100, 1);
	CString str1, str2;
	while (!m_pRs->adoEOF){
		str1 = m_pRs->GetCollect("��Ʒ��");
		str2 = m_pRs->GetCollect("��Ʒ����");
		m_SpList.InsertItem(0, CString(""));
		m_SpList.SetItemText(0, 0, str1);
		m_SpList.SetItemText(0, 1, str2);
		m_pRs->MoveNext();
	}
	return TRUE;
}


void CSPdlg::OnNMDblclkListshangpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = m_SpList.GetSelectionMark();
	m_Name = m_SpList.GetItemText(i, 0);
	m_Price = m_SpList.GetItemText(i, 1);
	UpdateData(false);
	*pResult = 0;
}


void CSPdlg::OnBnClickedButtonadd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString sql = CString("select * from shangpininfo where ��Ʒ��='") + m_Name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	if (!m_pRs->adoEOF){
		AfxMessageBox(CString("���и�����Ʒ!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	if (m_Name.IsEmpty() || m_Price.IsEmpty()){
		AfxMessageBox(CString("��������Ʒ���͵���!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	//using std::regex;				
	string str_price = (char*)(_bstr_t)(m_Price);
	regex r("^(\\+?\\d+)(\\.\\d+)?$");
	smatch results;
	if (regex_search(str_price, results, r)){
		CString sql = CString("insert into shangpininfo(��Ʒ��,��Ʒ����) values('") + m_Name + "'," + m_Price + ")";
		theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		AfxMessageBox(CString("�ɹ����!"));
		//�����б�����
		m_SpList.InsertItem(0, CString(""));
		m_SpList.SetItemText(0, 0, m_Name);
		m_SpList.SetItemText(0, 1, m_Price);
		m_Name = "";
		m_Price = "";
		/*ȫ������
		CString str = CString("select * from caishiinfo");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(str), NULL, adCmdText);
		CString str1, str2;
		while (!m_pRs->adoEOF){
		str1 = m_pRs->GetCollect("����");
		str2 = m_pRs->GetCollect("�˼�");
		m_CpList.InsertItem(0, CString(""));
		m_CpList.SetItemText(0, 0, str1);
		m_CpList.SetItemText(0, 1, str2);
		m_pRs->MoveNext();
		}
		*/
		UpdateData(false);

	}
	else{
		MessageBox(CString("���ݸ�ʽ������������Ч���֣�"), CString("ϵͳ��ʾ"), MB_OK | MB_ICONEXCLAMATION);
		m_Price = "";
		UpdateData(false);
	}		
}


void CSPdlg::OnBnClickedButtonedit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString sql = CString("select * from shangpininfo where ��Ʒ��='") + m_Name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	if (m_pRs->adoEOF){
		AfxMessageBox(CString("û�иò�ʽ!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	if (m_Name.IsEmpty() || m_Price.IsEmpty()){
		AfxMessageBox(CString("��������Ʒ���͵���!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	string str_price = (char*)(_bstr_t)(m_Price);
	regex r("^(\\+?\\d+)(\\.\\d+)?$");
	smatch results;
	if (regex_search(str_price, results, r)){
		CString sql = CString("update shangpininfo set ��Ʒ����=") + m_Price + " where ��Ʒ��='" + m_Name + "'";
		theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		AfxMessageBox(CString("�ɹ��޸�!"));
		m_Name = "";
		m_Price = "";
		m_SpList.DeleteAllItems();
		CString str = CString("select * from shangpininfo");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(str), NULL, adCmdText);
		CString str1, str2;
		while (!m_pRs->adoEOF){
			str1 = m_pRs->GetCollect("��Ʒ��");
			str2 = m_pRs->GetCollect("��Ʒ����");
			m_SpList.InsertItem(0, CString(""));
			m_SpList.SetItemText(0, 0, str1);
			m_SpList.SetItemText(0, 1, str2);
			m_pRs->MoveNext();

			UpdateData(false);

		}
	}
	else{
		MessageBox(CString("���ݸ�ʽ������������Ч���֣�"), CString("ϵͳ��ʾ"), MB_OK | MB_ICONEXCLAMATION);
		m_Price = "";
		UpdateData(false);
	}	
}


void CSPdlg::OnBnClickedButtondelete()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_Name.IsEmpty()){
		AfxMessageBox(CString("��������Ʒ��!"));
		m_Price = "";
		UpdateData(false);
		return;
	}
	CString sql = CString("select * from shangpininfo where ��Ʒ��='") + m_Name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	if (m_pRs->adoEOF){
		AfxMessageBox(CString("û�и���Ʒ!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	else{
		CString sql = CString("delete * from shangpininfo where ��Ʒ��='") + m_Name + "'";
		theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		AfxMessageBox(CString("�ɹ�ɾ��!"));
		m_Name = "";
		m_Price = "";
		m_SpList.DeleteAllItems();
		CString str = CString("select * from shangpininfo");
		m_pRs = theApp.m_pCon->Execute(_bstr_t(str), NULL, adCmdText);
		CString str1, str2;
		while (!m_pRs->adoEOF){
			str1 = m_pRs->GetCollect("��Ʒ��");
			str2 = m_pRs->GetCollect("��Ʒ����");
			m_SpList.InsertItem(0, CString(""));
			m_SpList.SetItemText(0, 0, str1);
			m_SpList.SetItemText(0, 1, str2);
			m_pRs->MoveNext();
		}
		UpdateData(false);
	}
}


void CSPdlg::OnBnClickedButtoncancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CSPdlg::OnCbnSelchangeCombosearch()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_SearchCombo.GetCurSel() == CB_ERR){
		//AfxMessageBox(CString("û�в�Ʒ�ɼӣ�"));
		return;
	}

	//CString sql = CString("select * from caishiinfo")

	CString str_selection;
	m_SearchCombo.GetLBText(m_SearchCombo.GetCurSel(), str_selection);


	CString sql = CString("select * from shangpininfo where ��Ʒ��='") + str_selection + CString("'");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_price = m_pRs->GetCollect("��Ʒ����");
	//double each_total = atof((char*)(_bstr_t)str_price)*atof((char*)(_bstr_t)SLdlg.m_ShuLiang);
	//total_price += each_total;
	//str_total = CString((char*)(_bstr_t)total_price);
	m_Name = str_selection;
	m_Price = str_price;
	UpdateData(false);
}


void CSPdlg::OnCbnEditchangeCombosearch()
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

	CString sql = CString("select * from shangpininfo");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString cstr_list;
	string str_search = (_bstr_t)(cstr_search);
	string str_list;
	while (!m_pRs->adoEOF){
		cstr_list = m_pRs->GetCollect("��Ʒ��");
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


void CSPdlg::OnEnChangeEditname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_Price = "";
	if (m_Name.IsEmpty()){
		return;
	}
	CString sql = CString("select * from shangpininfo where ��Ʒ��='") + m_Name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	if (!m_pRs->adoEOF){
		m_Price = m_pRs->GetCollect("��Ʒ����");
	}
	UpdateData(false);
}
