// Logindlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Logindlg.h"
#include "afxdialogex.h"
#include "CateringMTDlg.h"

extern CCateringMTApp theApp;
// CLogindlg �Ի���

IMPLEMENT_DYNAMIC(CLogindlg, CDialogEx)

CLogindlg::CLogindlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogindlg::IDD, pParent)
	, m_Uname(_T(""))
	, m_Upasswd(_T(""))
{

}

CLogindlg::~CLogindlg()
{
}

void CLogindlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_uname, m_Uname);	
	DDX_Text(pDX, IDC_EDIT_upasswd, m_Upasswd);
}


BEGIN_MESSAGE_MAP(CLogindlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogindlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLogindlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLogindlg ��Ϣ�������


void CLogindlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (!m_Uname.IsEmpty() && !m_Upasswd.IsEmpty()){
		CString sql = CString("select * from Login where Uname='") + m_Uname + "' and Upasswd='" + m_Upasswd + "'";
		//CString str = CString("select Upasswd from Login");
		//m_pRs = theApp.m_pCon->Execute(_bstr_t(str), NULL, adCmdText);
		//CString str_pwd;
		//str_pwd = m_pRs->GetCollect("Upasswd");
		try{					
				//m_pRs.CreateInstance("ADODB.Recordset");
				//m_pRs->Open((_variant_t)sql, theApp.m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);

			if (m_pRs->adoEOF){				
				m_Uname = "";
				m_Upasswd = "";
				UpdateData(false);
				++i;
				if (i >= 3){
					AfxMessageBox(CString("�������̫�࣡"));
					OnBnClickedCancel();	
					return;
				}
				AfxMessageBox(CString("�û������������"));
				return;
			}
			else{
				theApp.name = m_Uname;
				theApp.pwd = m_Upasswd;
				CDialogEx::OnOK();
				return;
			}										
					
		}
		catch(_com_error e){
			CString temp;
			temp.Format(CString("�������ݿ����:%s"), e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
	}
	else{
		AfxMessageBox(CString("�û������벻��Ϊ��"));
		m_Upasswd = "";
		UpdateData(false);
	}	
}

BOOL CLogindlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_login)), TRUE);
	return TRUE;
}

void CLogindlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
