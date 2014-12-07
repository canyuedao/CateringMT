// Returndlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Returndlg.h"
#include "afxdialogex.h"


// CReturndlg �Ի���

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


// CReturndlg ��Ϣ�������
BOOL CReturndlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}


void CReturndlg::OnBnClickedButtonview()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, (CString)("accdb"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(CString)("Access�ļ�(*.accdb)|*.accdb|Access�ļ�(*.mdb)|*.mdb||"), NULL);

	if (dlg.DoModal() == IDOK){
		CString str = dlg.GetPathName();
		m_Edit.SetWindowText(str);

	}
}


void CReturndlg::OnBnClickedButtonreturn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString str;
	m_Edit.GetWindowText(str);
	if (str.IsEmpty()){
		AfxMessageBox(CString("��ѡ��ԭ�ļ�!"));
		return;
	}
	WCHAR buf[256];
	//��ȡ�ļ�·��
	//GetModuleFileName(NULL, buf, 256);
	//PathRemoveFileSpec(buf);
	/*����Bug,���������ٻ�ԭ�޷��ɹ�ִ��
	::GetCurrentDirectory(256, temp);
	*/
	::GetCurrentDirectory(256, buf);
	CString temp = buf + CString("\\canyin.accdb");
	try{
		CopyFile(str, temp, false);
	}
	catch (...){
		AfxMessageBox(CString("��ԭʧ�ܣ�"));
		return;
	}
	MessageBox(CString("��ԭ���!"), CString("ϵͳ��ʾ"), MB_OK | MB_ICONEXCLAMATION);
	CDialogEx::OnOK();
}


void CReturndlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();	
}
