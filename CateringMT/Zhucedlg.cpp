// Zhucedlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Zhucedlg.h"
#include "afxdialogex.h"
#include <regex>
using namespace std;

extern CCateringMTApp theApp;
// CZhucedlg 对话框

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


// CZhucedlg 消息处理程序


BOOL CZhucedlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}


void CZhucedlg::OnBnClickedButtonOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_Name.IsEmpty()){
		AfxMessageBox(CString("用户名不能为空"));
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
			AfxMessageBox(CString("请输入以汉字开头(至少两个汉字)，后面可接长度为1-6的字母、数字下划线组合\n或以字母开头长度在6-18的字母、数字、下划线组合"));
			m_Name = "";
			m_Pwd = "";
			m_Pwd1 = "";
			UpdateData(false);
			return;
		}
	}
	catch (regex_error e){
		AfxMessageBox(CString("错误信息：") + e.what());
		return;
	}
	
	if (m_Pwd.IsEmpty()){
		AfxMessageBox(CString("密码不能为空"));
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
		AfxMessageBox(CString("请输入以字母开头长度在8-18的字母、数字、下划线组合"));		
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		return;
	}
	if (m_Pwd1.IsEmpty()){
		AfxMessageBox(CString("请重复输入密码"));
		return;
	}
	if (m_Pwd != m_Pwd1){
		AfxMessageBox(CString("密码不一致!"));
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
		AfxMessageBox(CString("注册成功!"));
		CDialog::OnOK();
	}
	else{
		AfxMessageBox(CString("用户名已存在!"));
		/*可以考虑清空密码
		m_Pwd = "";
		m_Pwd1 = "";
		*/		
		return;
	}
}


void CZhucedlg::OnBnClickedButtonreset()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Name = "";
	m_Pwd = "";
	m_Pwd1 = "";
	UpdateData(false);
}
