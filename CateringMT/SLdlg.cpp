// SLdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "SLdlg.h"
#include "afxdialogex.h"


// CSLdlg 对话框

IMPLEMENT_DYNAMIC(CSLdlg, CDialogEx)

CSLdlg::CSLdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSLdlg::IDD, pParent)
	, m_ShuLiang(_T(""))
{

}

CSLdlg::~CSLdlg()
{
}

void CSLdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_shuliang, m_ShuLiang);
}


BEGIN_MESSAGE_MAP(CSLdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CSLdlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_return, &CSLdlg::OnBnClickedButtonreturn)
END_MESSAGE_MAP()


// CSLdlg 消息处理程序


void CSLdlg::OnBnClickedButtonOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_ShuLiang == "0" || m_ShuLiang.IsEmpty()){
		AfxMessageBox(CString("数量至少为1"));
		return;
	}
	CDialogEx::OnOK();
}


void CSLdlg::OnBnClickedButtonreturn()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

BOOL CSLdlg::OnInitDialog(){
	CDialog::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_sl)), TRUE);
	return TRUE;
}
