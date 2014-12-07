
// CateringMTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CateringMT.h"
#include "CateringMTDlg.h"
#include "afxdialogex.h"
#include "Copydlg.h"
#include "Diancaidlg.h"
#include "Jiacaidlg.h"
#include "Jiezhangdlg.h"
#include "Kaitaidlg.h"
#include "Logindlg.h"
#include "Returndlg.h"
#include "SLdlg.h"
#include "Zhucedlg.h"
#include "CPdlg.h"
#include "Jinhuodlg.h"
#include "SPdlg.h"
#include "Rsrcxdlg.h"
#include "Ysrcxdlg.h"
#include "Jinhuocxdlg.h"
#include "Changepwddlg.h"
#include "Quanxiandlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CCateringMTApp theApp;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	return TRUE;
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCateringMTDlg 对话框



CCateringMTDlg::CCateringMTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCateringMTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCateringMTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCateringMTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDB_login,&CCateringMTDlg::OnMenuLogin)
	ON_COMMAND(IDB_kaitai,&CCateringMTDlg::OnMenukaitai)
	ON_COMMAND(IDB_addcai,&CCateringMTDlg::OnMenuaddcai)
	ON_COMMAND(IDB_jiezhang,&CCateringMTDlg::OnMenujiezhang)
	ON_COMMAND(IDB_jiesuan,&CCateringMTDlg::OnMenujiesuan)
	ON_COMMAND(IDB_yuangong,&CCateringMTDlg::OnMenuyuangong)
	ON_COMMAND(IDB_logout,&CCateringMTDlg::OnLogout)
	ON_COMMAND(IDB_exitsys,&CCateringMTDlg::OnCancel)
	ON_COMMAND(ID_Menu_Login, &CCateringMTDlg::OnMenuLogin)
	ON_COMMAND(ID_MENU_kaitai, &CCateringMTDlg::OnMenukaitai)
	ON_COMMAND(ID_MENU_addcai, &CCateringMTDlg::OnMenuaddcai)
	ON_COMMAND(ID_MENU_jiezhang, &CCateringMTDlg::OnMenujiezhang)
	ON_COMMAND(ID_MENU_jiesuan, &CCateringMTDlg::OnMenujiesuan)
	ON_COMMAND(ID_MENU_yuangong, &CCateringMTDlg::OnMenuyuangong)
	ON_COMMAND(ID_MENU_jinhuo, &CCateringMTDlg::OnMenujinhuo)
	ON_COMMAND(ID_MENU_SPInfo, &CCateringMTDlg::OnMenuSpinfo)
	ON_COMMAND(ID_MENU_CP, &CCateringMTDlg::OnMenuCp)
	ON_COMMAND(ID_MENU_rishourucx, &CCateringMTDlg::OnMenurishourucx)
	ON_COMMAND(ID_MENU_yueshourucx, &CCateringMTDlg::OnMenuyueshourucx)
	ON_COMMAND(ID_MENU_jinhuoselect, &CCateringMTDlg::OnMenujinhuoselect)
	ON_COMMAND(ID_MENU_sqlcopy, &CCateringMTDlg::OnMenusqlcopy)
	ON_COMMAND(ID_MENU_sqlreturn, &CCateringMTDlg::OnMenusqlreturn)
	ON_COMMAND(ID_MENU_sqlnew, &CCateringMTDlg::OnMenusqlnew)
	ON_COMMAND(ID_MENU_quanxian, &CCateringMTDlg::OnMenuquanxian)
	ON_COMMAND(ID_MENU_about, &CCateringMTDlg::OnMenuabout)
	ON_COMMAND(ID_MENU_pwd, &CCateringMTDlg::OnMenupwd)
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnToolTipNotify)
END_MESSAGE_MAP()





// CCateringMTDlg 消息处理程序

BOOL CCateringMTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
	CTime time;
	time = CTime::GetCurrentTime();
	CString Str = time.Format("%Y-%m-%d");
	m_Imagelist.Create(32, 32, ILC_COLOR24 | ILC_MASK, 1, 1);
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_login));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_open));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_add));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_pay));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_rishouru));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_reg));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_logout));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_cancel));	
	UINT Array[8];
	for (int i = 0; i < 8;i++)
	{
		Array[i] = 9000 + i;
	}


	m_Toolbar.Create(this);
	m_Toolbar.SetButtons(Array, 8);
	
	m_Toolbar.SetButtonText(0, CString("系统登录"));
	m_Toolbar.SetButtonText(1, CString("开台"));
	m_Toolbar.SetButtonText(2, CString("加减菜"));
	m_Toolbar.SetButtonText(3, CString("顾客买单"));
	m_Toolbar.SetButtonText(4, CString("本日收入"));
	m_Toolbar.SetButtonText(5, CString("员工注册"));
	m_Toolbar.SetButtonText(6, CString("退出登录"));
	m_Toolbar.SetButtonText(7, CString("退出系统"));
	
	m_Toolbar.GetToolBarCtrl().SetButtonWidth(60, 120);
	m_Toolbar.GetToolBarCtrl().SetImageList(&m_Imagelist); 
	m_Toolbar.SetSizes(CSize(70, 65), CSize(33, 40));
	//m_Toolbar.ModifyStyle(0, BTNS_SHOWTEXT | TBSTYLE_EX_MIXEDBUTTONS | TBSTYLE_LIST);
	m_Toolbar.EnableToolTips(TRUE);
	for (int i = 0; i < 4; i++){
		Array[i] = 10000 + i;
	}
	m_Statusbar.Create(this);
	m_Statusbar.SetIndicators(Array, 4);
	//for (int i = 0; i < 3; i++){
		//m_Statusbar.SetPaneInfo(i, Array[i], 0, 80);
	//}
	m_Statusbar.SetPaneInfo(0, Array[0], 0, 80);
	m_Statusbar.SetPaneInfo(1, Array[1], 0, 200);
	m_Statusbar.SetPaneInfo(2, Array[2], 0, 800);
	m_Statusbar.SetPaneText(0, CString("餐饮管理系统"));
	m_Statusbar.SetPaneText(2,CString("当前时间") + Str);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);
	/*
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	*/
	// TODO:  在此添加额外的初始化代码
	
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_kaitai, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_addcai, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiezhang, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiesuan, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_yuangong, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_logout, false);
	CMenu *pMenu = GetMenu();
	pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(2, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);;
	pMenu->GetSubMenu(4)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCateringMTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCateringMTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCateringMTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCateringMTDlg::OnMenuLogin()
{
	// TODO:  在此添加命令处理程序代码
	CLogindlg dlg;
	if (dlg.DoModal() == IDOK){
		CString sql = CString("select * from Login where Uname='") + theApp.name + "'";
		m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str_power = m_pRs->GetCollect("Power");
		int power = atoi((char *)(_bstr_t)str_power);
		if (power == 2){
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_addcai, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_kaitai, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiezhang, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiesuan, true);	
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_yuangong, false);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_logout, true);
			CMenu *pMenu = GetMenu();
			pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(2)->EnableMenuItem(2, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(4)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
		}
		if (power == 1){
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_addcai, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_kaitai, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiezhang, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiesuan, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_yuangong, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_logout, true);
			CMenu *pMenu = GetMenu();
			pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(2, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(1)->GetSubMenu(1)->EnableMenuItem(2, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(1)->GetSubMenu(1)->EnableMenuItem(3, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(4)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
		}
		if (power == 0 || power == 9){
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_addcai, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_kaitai, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiezhang, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiesuan, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_yuangong, true);
			m_Toolbar.GetToolBarCtrl().EnableButton(IDB_logout, true);
			CMenu *pMenu = GetMenu();
			pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(2, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(4)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			UpdateData(false);
		}
		m_Statusbar.SetPaneText(1, CString("当前用户: ") + theApp.name);
		SetWindowText(CString("餐饮管理系统      当前登录用户: ") + theApp.name);
	}

}


void CCateringMTDlg::OnMenukaitai()
{
	// TODO:  在此添加命令处理程序代码
	CKaitaidlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenuaddcai()
{
	// TODO:  在此添加命令处理程序代码
	CJiacaidlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenujiezhang()
{
	// TODO:  在此添加命令处理程序代码
	CJiezhangdlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenujiesuan()
{
	// TODO:  在此添加命令处理程序代码
	CTime time = CTime::GetCurrentTime();
	CString str_time = time.Format("%Y-%m-%d");
	
	CString sql = CString("select 日收入 from shouru where 时间='") + str_time + "'";
	m_pRs = theApp.m_pCon->Execute(_bstr_t(sql), NULL, adCmdText);
	if (!m_pRs->adoEOF){
		CString str = m_pRs->GetCollect("日收入");
		AfxMessageBox(CString("今日收入：") + str);
	}
}


void CCateringMTDlg::OnMenuyuangong()
{
	// TODO:  在此添加命令处理程序代码
	CZhucedlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenujinhuo()
{
	// TODO:  在此添加命令处理程序代码
	CJinhuodlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenuSpinfo()
{
	// TODO:  在此添加命令处理程序代码
	CSPdlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenuCp()
{
	// TODO:  在此添加命令处理程序代码
	CCPdlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenurishourucx()
{
	// TODO:  在此添加命令处理程序代码
	CRsrcxdlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenuyueshourucx()
{
	// TODO:  在此添加命令处理程序代码
	CYsrcxdlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenujinhuoselect()
{
	// TODO:  在此添加命令处理程序代码
	CJinhuocxdlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenusqlcopy()
{
	// TODO:  在此添加命令处理程序代码
	CCopydlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenusqlreturn()
{
	// TODO:  在此添加命令处理程序代码
	CReturndlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenusqlnew()
{
	// TODO:  在此添加命令处理程序代码
	if (MessageBox(CString("确定要初始化数据库吗？"), CString("提示"), MB_YESNO) == IDYES){
		try{
			CString sql1 = CString("delete from caishiinfo");
			CString sql2 = CString("delete from jinhuoinfo");
			CString sql3 = CString("delete from shangpininfo");
			CString sql4 = CString("delete from shouru");
			CString sql5 = CString("delete from paybill");
			theApp.m_pCon->Execute(_bstr_t(sql1), NULL, adCmdText);
			theApp.m_pCon->Execute(_bstr_t(sql2), NULL, adCmdText);
			theApp.m_pCon->Execute(_bstr_t(sql3), NULL, adCmdText);
			theApp.m_pCon->Execute(_bstr_t(sql4), NULL, adCmdText);
			theApp.m_pCon->Execute(_bstr_t(sql5), NULL, adCmdText);
			AfxMessageBox(CString("初始化成功"));
			return;
		}
		catch (_com_error e){
			MessageBox(CString("初始化失败！\n错误信息: ") + e.ErrorMessage(), CString("系统提示"), MB_OK|MB_ICONEXCLAMATION);
			return;
		}
		
	}
	else
		return;
}


void CCateringMTDlg::OnMenuquanxian()
{
	// TODO:  在此添加命令处理程序代码
	CQuanxiandlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenupwd()
{
	// TODO:  在此添加命令处理程序代码
	CChangepwddlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnMenuabout()
{
	// TODO:  在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}


void CCateringMTDlg::OnLogout(){
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_kaitai, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_addcai, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiezhang, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiesuan, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_yuangong, false);
	m_Toolbar.GetToolBarCtrl().EnableButton(IDB_logout, false);
	CMenu *pMenu = GetMenu();
	pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(2, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
}


void CCateringMTDlg::OnCancel(){
	CDialogEx::OnCancel();
}


BOOL CCateringMTDlg::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult){
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT*)pNMHDR;
	UINT nID = pNMHDR->idFrom;
	if (nID){
		nID = m_Toolbar.CommandToIndex(nID);
		if (nID != -1){
			m_Toolbar.GetButtonText(nID, str);
			pTTT->lpszText = (_bstr_t)str;
			pTTT->hinst = AfxGetResourceHandle();
			return(TRUE);
		}
	}
	return(FALSE);
}