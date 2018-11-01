// FormConfigView.cpp : 实现文件
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormConfigView.h"


// CFormConfigView

IMPLEMENT_DYNCREATE(CFormConfigView, CFormView)

CFormConfigView::CFormConfigView()
	: CFormView(CFormConfigView::IDD)
{

}

CFormConfigView::~CFormConfigView()
{
}

void CFormConfigView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormConfigView, CFormView)
END_MESSAGE_MAP()


// CFormConfigView 诊断

#ifdef _DEBUG
void CFormConfigView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormConfigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormConfigView 消息处理程序
