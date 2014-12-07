// Changepwddlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "CateringMTDlg.h"
#include "Changepwddlg.h"
#include "afxdialogex.h"
#include <regex>
using namespace std;

extern CCateringMTApp theApp;
// CChangepwddlg �Ի���

IMPLEMENT_DYNAMIC(CChangepwddlg, CDialogEx)

CChangepwddlg::CChangepwddlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangepwddlg::IDD, pParent)
	, m_Old(_T(""))
	, m_Pwd(_T(""))
	, m_Pwd1(_T(""))
{

}

CChangepwddlg::~CChangepwddlg()
{
}

void CChangepwddlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_old, m_Old);
	DDX_Text(pDX, IDC_EDIT_pwd, m_Pwd);
	DDX_Text(pDX, IDC_EDIT_pwd1, m_Pwd1);
}


BEGIN_MESSAGE_MAP(CChangepwddlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CChangepwddlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_reset, &CChangepwddlg::OnBnClickedButtonreset)
END_MESSAGE_MAP()


// CChangepwddlg ��Ϣ�������
BOOL CChangepwddlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}


void CChangepwddlg::OnBnClickedButtonOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_Old.IsEmpty()){
		AfxMessageBox(CString("�����������"));
		m_Pwd = "";
		m_Pwd1 = "";
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
	if (m_Old != theApp.pwd){
		AfxMessageBox(CString("��������ȷ�ľ�����!"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		++i_limint;
		if (i_limint>=3){
			CDialogEx::OnCancel();
		}
		return;
	}
	theApp.m_pCon->Execute((_bstr_t)(CString("update Login set Upasswd='") + m_Pwd + "' where Uname='" + theApp.name + "'"), NULL, adCmdText);
	m_Old = "";
	m_Pwd = "";
	m_Pwd1 = "";
	UpdateData(false);
	AfxMessageBox(CString("�����޸ĳɹ�!"));		
	CDialog::OnOK();			
}


void CChangepwddlg::OnBnClickedButtonreset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_Old = "";
	m_Pwd = "";
	m_Pwd1 = "";
	UpdateData(false);
}

