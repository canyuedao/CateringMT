
// CateringMT.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCateringMTApp: 
// �йش����ʵ�֣������ CateringMT.cpp
//

class CCateringMTApp : public CWinApp
{
public:
	CCateringMTApp();
	CString pwd;
	CString name;
	_ConnectionPtr m_pCon;
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

