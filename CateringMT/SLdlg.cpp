// SLdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "SLdlg.h"
#include "afxdialogex.h"


// CSLdlg �Ի���

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


// CSLdlg ��Ϣ�������


void CSLdlg::OnBnClickedButtonOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_ShuLiang == "0" || m_ShuLiang.IsEmpty()){
		AfxMessageBox(CString("��������Ϊ1"));
		return;
	}
	CDialogEx::OnOK();
}


void CSLdlg::OnBnClickedButtonreturn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

BOOL CSLdlg::OnInitDialog(){
	CDialog::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_sl)), TRUE);
	return TRUE;
}
