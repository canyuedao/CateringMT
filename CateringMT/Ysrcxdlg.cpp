// Ysrcxdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Ysrcxdlg.h"
#include "afxdialogex.h"


extern CCateringMTApp theApp;
// CYsrcxdlg 对话框

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


// CYsrcxdlg 消息处理程序
BOOL CYsrcxdlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}


void CYsrcxdlg::OnBnClickedButtoncheck()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_Year.IsEmpty() | m_Month.IsEmpty()){
		AfxMessageBox(CString("请输入一个时间"));
		return;
	}
		
	
	
	CString sql = CString("select * from shouru where Year(时间)=") + m_Year + " and Month(时间)=" + m_Month;
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_temp;
	double value_total = 0;
	if (m_pRs->adoEOF){
		MessageBox(m_Year + "年" + m_Month + "月的收入为：0", CString("月收入查询"));
		return;
	}
	while (!m_pRs->adoEOF){
		str_temp = m_pRs->GetCollect("日收入");
		value_total += atof((char*)(_bstr_t)str_temp);
		m_pRs->MoveNext();
		
	}
	CString str_total = (CString)(char*)(_bstr_t)(value_total);
	MessageBox(m_Year + "年" + m_Month + "月的收入为：" + str_total, CString("月收入查询"));
	
		
	
}


void CYsrcxdlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CYsrcxdlg::OnEnChangeEdityear()
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


void CYsrcxdlg::OnEnChangeEditmonth()
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



