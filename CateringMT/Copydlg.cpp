// Copydlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Copydlg.h"
#include "afxdialogex.h"

extern CCateringMTApp theApp;
// CCopydlg 对话框

IMPLEMENT_DYNAMIC(CCopydlg, CDialogEx)

CCopydlg::CCopydlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCopydlg::IDD, pParent)
	, m_Name(_T(""))
{

}

CCopydlg::~CCopydlg()
{
}

void CCopydlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
}


BEGIN_MESSAGE_MAP(CCopydlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_view, &CCopydlg::OnBnClickedButtonview)
	ON_BN_CLICKED(IDOK, &CCopydlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCopydlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCopydlg 消息处理程序
BOOL CCopydlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}

void CCopydlg::OnBnClickedButtonview()
{
	// TODO:  在此添加控件通知处理程序代码
	CString ReturnPath;
	TCHAR szPath[_MAX_PATH];
	BROWSEINFO bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.lpszTitle = _T("请选择备份文件夹");
	bi.pszDisplayName = szPath;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	LPITEMIDLIST pItemIDList = SHBrowseForFolder(&bi);
	if (pItemIDList){
		if (SHGetPathFromIDList(pItemIDList, szPath))
			ReturnPath = szPath;
	}
	else
		ReturnPath = "";	
	m_Edit.SetWindowText(ReturnPath); 
}


void CCopydlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CString str;
	m_Edit.GetWindowText(str);
	if (str.IsEmpty()){
		AfxMessageBox(CString("请选择文件保存路径!"));
		return;
	}
	if (m_Name.IsEmpty()){
		AfxMessageBox(CString("请输入一个文件名!"));
		return;
	}
	
	CString strPath = str + "\\" + m_Name + ".accdb";;
	WCHAR temp[256];	
	//获取文件路径
	//GetModuleFileName(NULL, temp, 256);
	//PathRemoveFileSpec(temp);
	/*存在Bug,当备份了再还原无法成功执行
	::GetCurrentDirectory(256, temp);
	*/
	::GetCurrentDirectory(256, temp);
	CString buf = temp + CString("\\canyin.accdb");	
	try{
		CopyFile(buf, strPath, false);
	}
	catch (...){
		AfxMessageBox(CString("备份失败！"));
		return;
	}
	
	MessageBox(CString("备份完成!"), CString("系统提示"), MB_OK | MB_ICONEXCLAMATION);
	CDialogEx::OnOK();
}


void CCopydlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
