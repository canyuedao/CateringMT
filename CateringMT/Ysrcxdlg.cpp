// Ysrcxdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Ysrcxdlg.h"
#include "afxdialogex.h"


extern CCateringMTApp theApp;
// CYsrcxdlg �Ի���

IMPLEMENT_DYNAMIC(CYsrcxdlg, CDialogEx)

CYsrcxdlg::CYsrcxdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYsrcxdlg::IDD, pParent)
	, m_Year(_T(""))
	, m_Month(_T(""))	
{

}

CYsrcxdlg::~CYsrcxdlg()
{
}

void CYsrcxdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_year, m_Year);
	DDX_Text(pDX, IDC_EDIT_month, m_Month);
	
}


BEGIN_MESSAGE_MAP(CYsrcxdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_check, &CYsrcxdlg::OnBnClickedButtoncheck)
	ON_BN_CLICKED(IDCANCEL, &CYsrcxdlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_year, &CYsrcxdlg::OnEnChangeEdityear)
	ON_EN_CHANGE(IDC_EDIT_month, &CYsrcxdlg::OnEnChangeEditmonth)	
END_MESSAGE_MAP()


// CYsrcxdlg ��Ϣ�������
BOOL CYsrcxdlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}


void CYsrcxdlg::OnBnClickedButtoncheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_Year.IsEmpty() | m_Month.IsEmpty()){
		AfxMessageBox(CString("������һ��ʱ��"));
		return;
	}
		
	
	
	CString sql = CString("select * from shouru where Year(ʱ��)=") + m_Year + " and Month(ʱ��)=" + m_Month;
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_temp;
	double value_total = 0;
	if (m_pRs->adoEOF){
		MessageBox(m_Year + "��" + m_Month + "�µ�����Ϊ��0", CString("�������ѯ"));
		return;
	}
	while (!m_pRs->adoEOF){
		str_temp = m_pRs->GetCollect("������");
		value_total += atof((char*)(_bstr_t)str_temp);
		m_pRs->MoveNext();
		
	}
	CString str_total = (CString)(char*)(_bstr_t)(value_total);
	MessageBox(m_Year + "��" + m_Month + "�µ�����Ϊ��" + str_total, CString("�������ѯ"));
	
		
	
}


void CYsrcxdlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CYsrcxdlg::OnEnChangeEdityear()
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


void CYsrcxdlg::OnEnChangeEditmonth()
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
	if (iin_year == inow_year){
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



