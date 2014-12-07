// Rsrcxdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Rsrcxdlg.h"
#include "afxdialogex.h"
#include <regex>
using namespace std;

extern CCateringMTApp theApp;
// CRsrcxdlg �Ի���

IMPLEMENT_DYNAMIC(CRsrcxdlg, CDialogEx)

CRsrcxdlg::CRsrcxdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRsrcxdlg::IDD, pParent)
	, m_Year(_T(""))
	, m_Month(_T(""))
	, m_Day(_T(""))
{

}

CRsrcxdlg::~CRsrcxdlg()
{
}

void CRsrcxdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_year, m_Year);
	DDX_Text(pDX, IDC_EDIT_month, m_Month);
	DDX_Text(pDX, IDC_EDIT_day, m_Day);
}


BEGIN_MESSAGE_MAP(CRsrcxdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_check, &CRsrcxdlg::OnBnClickedButtoncheck)
	ON_BN_CLICKED(IDCANCEL, &CRsrcxdlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_year, &CRsrcxdlg::OnEnChangeEdityear)
	ON_EN_CHANGE(IDC_EDIT_month, &CRsrcxdlg::OnEnChangeEditmonth)
	ON_EN_CHANGE(IDC_EDIT_day, &CRsrcxdlg::OnEnChangeEditday)
END_MESSAGE_MAP()


// CRsrcxdlg ��Ϣ�������
BOOL CRsrcxdlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}


void CRsrcxdlg::OnBnClickedButtoncheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_Year.IsEmpty() | m_Month.IsEmpty() | m_Day.IsEmpty()){
		AfxMessageBox(CString("������һ��ʱ��"));
		return;
	}
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
	CString str_time = m_Year + "-" + cstr_month + "-" + cstr_day;
	CString sql = CString("select * from shouru where ʱ��='") + str_time + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_total;
	if (!m_pRs->adoEOF){
		str_total = m_pRs->GetCollect("������");
		MessageBox(m_Year + "��" + m_Month + "��" + m_Day + "�յ�����Ϊ��" + str_total, CString("�������ѯ"));
	}
	else{
		MessageBox(m_Year + "��" + m_Month + "��" + m_Day + "�յ�����Ϊ��0", CString("�������ѯ"));
	}
}


void CRsrcxdlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CRsrcxdlg::OnEnChangeEdityear()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CTime time = CTime::GetCurrentTime();
	CString str_year = time.Format("%Y");
	int inow_year = atoi((char*)(_bstr_t)str_year);
	int iin_year = atoi((char*)(_bstr_t)m_Year);
	if (inow_year < iin_year){
		AfxMessageBox(CString("������һ����Ч����"));
		m_Year = "";
		UpdateData(false);
	}
}


void CRsrcxdlg::OnEnChangeEditmonth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CTime time = CTime::GetCurrentTime();
	CString str_month = time.Format("%m");
	int inow_month = atoi((char*)(_bstr_t)str_month);
	int iin_month = atoi((char*)(_bstr_t)m_Month);
	CString str_year = time.Format("%Y");
	int inow_year = atoi((char*)(_bstr_t)str_year);
	int iin_year = atoi((char*)(_bstr_t)m_Year);
	if (iin_year==inow_year){
		if (inow_month < iin_month){
			AfxMessageBox(CString("������һ����Ч����"));
			m_Month = "";
			UpdateData(false);
		}
	}
	else {
		if (iin_month > 12){
			AfxMessageBox(CString("������һ����Ч����"));
			m_Month = "";
			UpdateData(false);
		}
	}
}


void CRsrcxdlg::OnEnChangeEditday()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	if ((iin_month == inow_month)&&(iin_year==inow_year)){
		if (inow_day < iin_day){
			AfxMessageBox(CString("������һ����Ч����"));
			m_Day = "";
			UpdateData(false);
		}
	}
	else {
		if (iin_day > 31){
			AfxMessageBox(CString("������һ����Ч����"));
			m_Day = "";
			UpdateData(false);
		}
	}
	
}
