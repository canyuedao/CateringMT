// CPdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "CPdlg.h"
#include "afxdialogex.h"
#include <regex>
using namespace std;

extern CCateringMTApp theApp;
// CCPdlg �Ի���

IMPLEMENT_DYNAMIC(CCPdlg, CDialogEx)

CCPdlg::CCPdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCPdlg::IDD, pParent)
	, m_Name(_T(""))
	, m_Price(_T(""))
{

}

CCPdlg::~CCPdlg()
{
}

void CCPdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_name, m_Name);
	DDX_Text(pDX, IDC_EDIT_price, m_Price);
	DDX_Control(pDX, IDC_LIST_caishi, m_CpList);
	DDX_Control(pDX, IDC_COMBO_search, m_SearchCombo);
}


BEGIN_MESSAGE_MAP(CCPdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_add, &CCPdlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_edit, &CCPdlg::OnBnClickedButtonedit)
	ON_BN_CLICKED(IDC_BUTTON_delete, &CCPdlg::OnBnClickedButtondelete)
	ON_BN_CLICKED(IDC_BUTTON_cancel, &CCPdlg::OnBnClickedButtoncancel)	
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_caishi, &CCPdlg::OnNMDblclkListcaishi)
	ON_CBN_SELCHANGE(IDC_COMBO_search, &CCPdlg::OnCbnSelchangeCombosearch)
	ON_CBN_EDITCHANGE(IDC_COMBO_search, &CCPdlg::OnCbnEditchangeCombosearch)
	ON_EN_CHANGE(IDC_EDIT_name, &CCPdlg::OnEnChangeEditname)
END_MESSAGE_MAP()


// CCPdlg ��Ϣ�������

BOOL CCPdlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	CString sql = CString("select * from caishiinfo");
	try{
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	}
	catch (_com_error e){
		MessageBox(CString("���ݴ���:") + CString(e.ErrorMessage()), CString("ϵͳ��ʾ!"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	m_CpList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_CpList.InsertColumn(0, CString("����"), LVCFMT_LEFT, 200, 0);
	m_CpList.InsertColumn(1, CString("���ۣ�Ԫ��"), LVCFMT_LEFT, 100, 1);
	CString str1,str2;
	while (!m_pRs->adoEOF){
		str1 = m_pRs->GetCollect("����");
		str2 = m_pRs->GetCollect("�˼�");
		m_CpList.InsertItem(0, CString(""));
		m_CpList.SetItemText(0, 0, str1);
		m_CpList.SetItemText(0, 1, str2);
		m_pRs->MoveNext();
	}
	return TRUE;
}


void CCPdlg::OnNMDblclkListcaishi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = m_CpList.GetSelectionMark();
	m_Name = m_CpList.GetItemText(i, 0);
	m_Price = m_CpList.GetItemText(i, 1);
	UpdateData(false);
	*pResult = 0;
}


void CCPdlg::OnBnClickedButtonadd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString sql = CString("select * from caishiinfo where ����='") + m_Name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	if (!m_pRs->adoEOF){
		AfxMessageBox(CString("���иò�ʽ!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	
	if (m_Name.IsEmpty()|| m_Price.IsEmpty()){
		AfxMessageBox(CString("����������͵���!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	string str_price = (char*)(_bstr_t)(m_Price);
	regex r("^(\\+?\\d+)(\\.\\d+)?$");
	smatch results;
	if (regex_search(str_price, results, r)){
		CString sql = CString("insert into caishiinfo(����,�˼�) values('") + m_Name + "'," + m_Price + ")";
		theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		AfxMessageBox(CString("�ɹ����!"));
		//�����б�����
		m_CpList.InsertItem(0, CString(""));
		m_CpList.SetItemText(0, 0, m_Name);
		m_CpList.SetItemText(0, 1, m_Price);
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


void CCPdlg::OnBnClickedButtonedit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString sql = CString("select * from caishiinfo where ����='") + m_Name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	if (m_pRs->adoEOF){
		AfxMessageBox(CString("û�иò�ʽ!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	if (m_Name.IsEmpty()||m_Price.IsEmpty()){
		AfxMessageBox(CString("�������������!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	string str_price = (char*)(_bstr_t)(m_Price);
	regex r("^(\\+?\\d+)(\\.\\d+)?$");
	smatch results;
	if (regex_search(str_price, results, r)){
		CString sql = CString("update caishiinfo set �˼�=") + m_Price + " where ����='" + m_Name + "'";
		theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		AfxMessageBox(CString("�ɹ��޸�!"));
		m_Name = "";
		m_Price = "";
		m_CpList.DeleteAllItems();
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
		UpdateData(false);
	}
	else{
		MessageBox(CString("���ݸ�ʽ������������Ч���֣�"), CString("ϵͳ��ʾ"), MB_OK | MB_ICONEXCLAMATION);
		m_Price = "";
		UpdateData(false);
	}			
}


void CCPdlg::OnBnClickedButtondelete()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_Name.IsEmpty()){
		AfxMessageBox(CString("���������!"));
		m_Price = "";
		UpdateData(false);
		return;
	}
	CString sql = CString("select * from caishiinfo where ����='") + m_Name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	if (m_pRs->adoEOF){
		AfxMessageBox(CString("û�иò�ʽ!"));
		m_Name = "";
		m_Price = "";
		UpdateData(false);
		return;
	}
	else{
		CString sql = CString("delete * from caishiinfo where ����='") + m_Name + "'";
		theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		AfxMessageBox(CString("�ɹ�ɾ��!"));
		m_Name = "";
		m_Price = "";
		m_CpList.DeleteAllItems();
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
		UpdateData(false);	
	}
}


void CCPdlg::OnBnClickedButtoncancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}








void CCPdlg::OnCbnSelchangeCombosearch()
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
	

	CString sql = CString("select * from caishiinfo where ����='") + str_selection + CString("'");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_price = m_pRs->GetCollect("�˼�");
	//double each_total = atof((char*)(_bstr_t)str_price)*atof((char*)(_bstr_t)SLdlg.m_ShuLiang);
	//total_price += each_total;
	//str_total = CString((char*)(_bstr_t)total_price);
	m_Name = str_selection;
	m_Price = str_price;
	UpdateData(false);
		
	
}


void CCPdlg::OnCbnEditchangeCombosearch()
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


void CCPdlg::OnEnChangeEditname()
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
	CString sql = CString("select * from caishiinfo where ����='") + m_Name + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);	
	if (!m_pRs->adoEOF){
		m_Price = m_pRs->GetCollect("�˼�");		
	}
	UpdateData(false);
}
