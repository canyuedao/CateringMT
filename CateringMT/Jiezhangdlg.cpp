// Jiezhangdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CateringMT.h"
#include "Jiezhangdlg.h"
#include "afxdialogex.h"

extern CCateringMTApp theApp;
// CJiezhangdlg �Ի���

IMPLEMENT_DYNAMIC(CJiezhangdlg, CDialogEx)

CJiezhangdlg::CJiezhangdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJiezhangdlg::IDD, pParent)	
{

}

CJiezhangdlg::~CJiezhangdlg()
{
}

void CJiezhangdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_zhuohao, m_ZhuoHaoCombo);
	DDX_Control(pDX, IDC_EDIT_yingshou, m_YingShou);
	DDX_Control(pDX, IDC_EDIT_shishou, m_ShiShou);
	DDX_Control(pDX, IDC_EDIT_zhaoling, m_ZhaoLing);
	DDX_Control(pDX, IDC_LIST_mingxi, m_MingXi);
}


BEGIN_MESSAGE_MAP(CJiezhangdlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_zhuohao, &CJiezhangdlg::OnCbnSelchangeCombozhuohao)
	ON_CBN_EDITCHANGE(IDC_COMBO_zhuohao, &CJiezhangdlg::OnCbnEditchangeCombozhuohao)
	ON_EN_CHANGE(IDC_EDIT_shishou, &CJiezhangdlg::OnEnChangeEditshishou)
	ON_BN_CLICKED(IDC_BUTTON_jiezhang, &CJiezhangdlg::OnBnClickedButtonjiezhang)
	ON_BN_CLICKED(IDC_BUTTON_return, &CJiezhangdlg::OnBnClickedButtonreturn)
END_MESSAGE_MAP()


// CJiezhangdlg ��Ϣ�������
BOOL CJiezhangdlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_pay)), TRUE); 
	CString sql = CString("select distinct ���� from paybill");
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str;
	while (!m_pRs->adoEOF){
		str = CString(m_pRs->GetCollect("����"));
		m_ZhuoHaoCombo.AddString(str);
		m_pRs->MoveNext();
	}
	m_MingXi.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_MingXi.InsertColumn(0, CString("����"), LVCFMT_LEFT, 150, 0);
	m_MingXi.InsertColumn(1, CString("����"), LVCFMT_LEFT, 80, 1);
	m_MingXi.InsertColumn(2, CString("���ѣ�Ԫ��"), LVCFMT_LEFT, 80, 1);
	
	return TRUE;
}

void CJiezhangdlg::OnCbnSelchangeCombozhuohao()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString str;
	m_ZhuoHaoCombo.GetLBText(m_ZhuoHaoCombo.GetCurSel(), str);
	CString sql = CString("select * from paybill where ����=") + str;
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str_name,str_num,str_value;
	double total = 0;
	m_MingXi.DeleteAllItems();
	while (!m_pRs->adoEOF){		
		str_name = m_pRs->GetCollect("����");
		str_num = m_pRs->GetCollect("����");
		str_value = m_pRs->GetCollect("����");
		total += atof((char *)(_bstr_t)str_value);
		m_MingXi.InsertItem(0, CString(""));
		m_MingXi.SetItemText(0, 0, str_name);
		m_MingXi.SetItemText(0, 1, str_num);
		m_MingXi.SetItemText(0, 2, str_value);
		m_pRs->MoveNext();
	}
	CString str_total = (CString)(char *)(_bstr_t)(total);
	m_YingShou.SetWindowText(str_total);
	
	UpdateData(false);

}


void CJiezhangdlg::OnCbnEditchangeCombozhuohao()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_MingXi.DeleteAllItems();
	m_YingShou.SetWindowText(CString(""));
	CString str;
	m_ZhuoHaoCombo.GetWindowText(str);		
	if (str.GetLength() == 4){
		UpdateData();
		CString sql = CString("select * from paybill where ����=") + str;
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str_name, str_num, str_value;
		double total = 0;
		if (m_pRs->adoEOF){
			m_YingShou.SetWindowText(CString("0"));
			return;
		}
		while (!m_pRs->adoEOF){
			str_name = m_pRs->GetCollect("����");
			str_num = m_pRs->GetCollect("����");
			str_value = m_pRs->GetCollect("����");
			total += atof((char *)(_bstr_t)(str_value));
			m_MingXi.InsertItem(0, CString(""));
			m_MingXi.SetItemText(0, 0, str_name);
			m_MingXi.SetItemText(0, 1, str_num);
			m_MingXi.SetItemText(0, 2, str_value);
			m_pRs->MoveNext();
		}
		CString str_total = (CString)(char *)(_bstr_t)(total);
		m_YingShou.SetWindowText(str_total);
		
		UpdateData(false);
	}
}


void CJiezhangdlg::OnEnChangeEditshishou()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString Str_ShiShou,Str_YingShou;
	m_ShiShou.GetWindowText(Str_ShiShou);
	m_YingShou.GetWindowText(Str_YingShou);
	double Value_ShiShou, Value_YingShou, Value_ZhaoLing;
	Value_ShiShou = atof((char *)(_bstr_t)(Str_ShiShou));
	Value_YingShou = atof((char *)(_bstr_t)(Str_YingShou));
	Value_ZhaoLing = Value_ShiShou - Value_YingShou;
	CString Str_ZhaoLing;
	Str_ZhaoLing.Format(CString("%0.2f"), Value_ZhaoLing);	
	m_ZhaoLing.SetWindowText(Str_ZhaoLing);
	
}


void CJiezhangdlg::OnBnClickedButtonjiezhang()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString str;
	m_ZhuoHaoCombo.GetWindowText(str);
	int i_len = str.GetLength();
	if (i_len != 4){
		AfxMessageBox(CString("��������ȷ������"));
		return;
	}
	else{
		CString sql = CString("select * from TableUSE where ����=") + str;
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		if (m_pRs->adoEOF){
			AfxMessageBox(CString("û�����Ų�̨"));
			return;
		}
		CString sql_1 = CString("select * from paybill where ����=") + str;
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql_1), NULL, adCmdText);
		if (m_pRs->adoEOF){
			AfxMessageBox(CString("��������Ҫ����"));
			return;
		}		
		else{
			CString Str_ShiShou;
			m_ShiShou.GetWindowText(Str_ShiShou);
			if (Str_ShiShou.IsEmpty()){
				AfxMessageBox(CString("������˿͸���"));
				return;
			}
			CString Str_ZhaoLing;
			m_ZhaoLing.GetWindowText(Str_ZhaoLing);			
			//double Value_YingShou = atof((char*)(_bstr_t)Str_YingShou);
			//double Value_ShiShou = atof((char*)(_bstr_t)Str_ShiShou);
			//double Value_ZhaoLing = Value_ShiShou - Value_YingShou;
			double Value_ZhaoLing = atof((char*)(_bstr_t)Str_ZhaoLing);
			if (Value_ZhaoLing < 0){
				AfxMessageBox(CString("����"));
				return;
			}
			else{
				//�������������
				CTime time = CTime::GetCurrentTime();
				CString str_time = time.Format("%Y-%m-%d");
				CString sql = CString("select * from shouru where ʱ��='") + str_time + "'";
				m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
				double value_rishouru=0;
				CString str_yingshou;
				m_YingShou.GetWindowText(str_yingshou);
				double value_yingshou = atof((char*)(_bstr_t)str_yingshou);
				CString str_rishouru;				
				str_rishouru.Format(CString("%0.2f"), value_yingshou);
				//double value_yingshou;
				if(!m_pRs->adoEOF){
					CString sql_shouru = CString("update shouru set ������=������+") + str_rishouru + " where ʱ��='" + str_time + "'";
					theApp.m_pCon->Execute(_bstr_t(sql_shouru), NULL, adCmdText);
					//CString str = m_pRs->GetCollect("������");
					//value_rishouru = atof((char*)(_bstr_t)str);
					//value_yingshou = atof((char*)(_bstr_t)str_yingshou);
				}
				else{
					CString sql_shouru = CString("insert into shouru(������,ʱ��) values(") + str_rishouru + ",'" + str_time + "')";
					theApp.m_pCon->Execute(_bstr_t(sql_shouru), NULL, adCmdText);
				}
				
				//double value_yingshou = atof((char*)(_bstr_t)str_yingshou);
				//value_rishouru += value_yingshou;
				
				
				
				
				//��������״̬��ɾ���˵�����Ӧ����
				CString sql_1, sql_2;
				sql_1 = CString("update TableUSE set TableUSEID=0 where ����=") + str;
				sql_2 = CString("delete from paybill where ����=") + str;
				theApp.m_pCon->Execute(_bstr_t(sql_1), NULL, adCmdText);
				theApp.m_pCon->Execute(_bstr_t(sql_2), NULL, adCmdText);
				//ɾ���ؼ�״̬
				m_YingShou.SetWindowText(CString(""));
				m_ShiShou.SetWindowText(CString(""));
				m_ZhaoLing.SetWindowText(CString(""));
				m_ZhuoHaoCombo.SetWindowText(CString(""));
				m_ZhuoHaoCombo.DeleteString(m_ZhuoHaoCombo.GetCurSel());
				m_MingXi.DeleteAllItems();
				UpdateData(false);
				AfxMessageBox(CString("��ӭ����"));
			}


		}
		
	}
}


void CJiezhangdlg::OnBnClickedButtonreturn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
