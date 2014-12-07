// Zhucedlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Zhucedlg.h"
#include "afxdialogex.h"
#include <regex>
using namespace std;

extern CCateringMTApp theApp;
// CZhucedlg �Ի���

IMPLEMENT_DYNAMIC(CZhucedlg, CDialogEx)

CZhucedlg::CZhucedlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZhucedlg::IDD, pParent)
	, m_Name(_T(""))
{

}

CZhucedlg::~CZhucedlg()
{
}

void CZhucedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_name, m_Name);
	DDX_Text(pDX, IDC_EDIT_pwd, m_Pwd);
	DDX_Text(pDX, IDC_EDIT_pwd1, m_Pwd1);
}


BEGIN_MESSAGE_MAP(CZhucedlg, CDialogEx)	
	ON_BN_CLICKED(IDC_BUTTON_OK, &CZhucedlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_reset, &CZhucedlg::OnBnClickedButtonreset)
END_MESSAGE_MAP()


// CZhucedlg ��Ϣ�������


BOOL CZhucedlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}


void CZhucedlg::OnBnClickedButtonOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_Name.IsEmpty()){
		AfxMessageBox(CString("�û�������Ϊ��"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		return;
	}
	try{
		//regex r("^[\\u4e00-\\u9fa5]|([[:alpha:]]\\w{5,17})$");
		CString str = CString("^([\\u4e00-\\u9fa5]{1,9}\\w{1,6}?)|([a-zA-Z]\\w{5,17})$");
		wregex r(str);
		wsmatch n_results;
		wstring str_name = (CString)(char*)(_bstr_t)(m_Name);
		if (!regex_search(str_name, n_results, r)){
			AfxMessageBox(CString("�������Ժ��ֿ�ͷ(������������)������ɽӳ���Ϊ1-6����ĸ�������»������\n������ĸ��ͷ������6-18����ĸ�����֡��»������"));
			m_Name = "";
			m_Pwd = "";
			m_Pwd1 = "";
			UpdateData(false);
			return;
		}
	}
	catch (regex_error e){
		AfxMessageBox(CString("������Ϣ��") + e.what());
		return;
	}
	
	if (m_Pwd.IsEmpty()){
		AfxMessageBox(CString("���벻��Ϊ��"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		return;
	}
	smatch p_results;
	string str_pwd = (char*)(_bstr_t)(m_Pwd);
	string str_1 = "^[A-Za-z]\\w{7,17}$";
	regex reg(str_1);
	if (!regex_search(str_pwd, p_results, reg)){
		AfxMessageBox(CString("����������ĸ��ͷ������8-18����ĸ�����֡��»������"));		
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		return;
	}
	if (m_Pwd1.IsEmpty()){
		AfxMessageBox(CString("���ظ���������"));
		return;
	}
	if (m_Pwd != m_Pwd1){
		AfxMessageBox(CString("���벻һ��!"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		return;
	}
	m_pRs = theApp.m_pCon->Execute((_bstr_t)(CString("select * from Login where Uname='")+m_Name+"'"), NULL, adCmdText);
	if (m_pRs->adoEOF){
		theApp.m_pCon->Execute((_bstr_t)(CString("insert into Login(Uname,Upasswd,Power) values('") + m_Name + "','"
			+ m_Pwd + "',2)"), NULL, adCmdText);
		m_Name = "";
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		AfxMessageBox(CString("ע��ɹ�!"));
		CDialog::OnOK();
	}
	else{
		AfxMessageBox(CString("�û����Ѵ���!"));
		/*���Կ����������
		m_Pwd = "";
		m_Pwd1 = "";
		*/		
		return;
	}
}


void CZhucedlg::OnBnClickedButtonreset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_Name = "";
	m_Pwd = "";
	m_Pwd1 = "";
	UpdateData(false);
}
