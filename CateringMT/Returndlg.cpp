// Returndlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Returndlg.h"
#include "afxdialogex.h"


// CReturndlg 对话框

IMPLEMENT_DYNAMIC(CReturndlg, CDialogEx)

CReturndlg::CReturndlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReturndlg::IDD, pParent)
{

}

CReturndlg::~CReturndlg()
{
}

void CReturndlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(CReturndlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_view, &CReturndlg::OnBnClickedButtonview)
	ON_BN_CLICKED(IDC_BUTTON_return, &CReturndlg::OnBnClickedButtonreturn)
	ON_BN_CLICKED(IDCANCEL, &CReturndlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CReturndlg 消息处理程序
BOOL CReturndlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}


void CReturndlg::OnBnClickedButtonview()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, (CString)("accdb"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(CString)("Access文件(*.accdb)|*.accdb|Access文件(*.mdb)|*.mdb||"), NULL);

	if (dlg.DoModal() == IDOK){
		CString str = dlg.GetPathName();
		m_Edit.SetWindowText(str);

	}
}


void CReturndlg::OnBnClickedButtonreturn()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CString str;
	m_Edit.GetWindowText(str);
	if (str.IsEmpty()){
		AfxMessageBox(CString("请选择还原文件!"));
		return;
	}
	WCHAR buf[256];
	//获取文件路径
	//GetModuleFileName(NULL, buf, 256);
	//PathRemoveFileSpec(buf);
	/*存在Bug,当备份了再还原无法成功执行
	::GetCurrentDirectory(256, temp);
	*/
	::GetCurrentDirectory(256, buf);
	CString temp = buf + CString("\\canyin.accdb");
	try{
		CopyFile(str, temp, false);
	}
	catch (...){
		AfxMessageBox(CString("还原失败！"));
		return;
	}
	MessageBox(CString("还原完成!"), CString("系统提示"), MB_OK | MB_ICONEXCLAMATION);
	CDialogEx::OnOK();
}


void CReturndlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();	
}
