// Copydlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Copydlg.h"
#include "afxdialogex.h"

extern CCateringMTApp theApp;
// CCopydlg �Ի���

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


// CCopydlg ��Ϣ�������
BOOL CCopydlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}

void CCopydlg::OnBnClickedButtonview()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString ReturnPath;
	TCHAR szPath[_MAX_PATH];
	BROWSEINFO bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.lpszTitle = _T("��ѡ�񱸷��ļ���");
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString str;
	m_Edit.GetWindowText(str);
	if (str.IsEmpty()){
		AfxMessageBox(CString("��ѡ���ļ�����·��!"));
		return;
	}
	if (m_Name.IsEmpty()){
		AfxMessageBox(CString("������һ���ļ���!"));
		return;
	}
	
	CString strPath = str + "\\" + m_Name + ".accdb";;
	WCHAR temp[256];	
	//��ȡ�ļ�·��
	//GetModuleFileName(NULL, temp, 256);
	//PathRemoveFileSpec(temp);
	/*����Bug,���������ٻ�ԭ�޷��ɹ�ִ��
	::GetCurrentDirectory(256, temp);
	*/
	::GetCurrentDirectory(256, temp);
	CString buf = temp + CString("\\canyin.accdb");	
	try{
		CopyFile(buf, strPath, false);
	}
	catch (...){
		AfxMessageBox(CString("����ʧ�ܣ�"));
		return;
	}
	
	MessageBox(CString("�������!"), CString("ϵͳ��ʾ"), MB_OK | MB_ICONEXCLAMATION);
	CDialogEx::OnOK();
}


void CCopydlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
