// PRAS_Client.h : PRAS_Client Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPRAS_ClientApp:
// �йش����ʵ�֣������ PRAS_Client.cpp
//

class CPRAS_ClientApp : public CWinApp
{
public:
	CPRAS_ClientApp();
	~CPRAS_ClientApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPRAS_ClientApp theApp;