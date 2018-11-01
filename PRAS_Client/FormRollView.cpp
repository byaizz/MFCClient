// FormRollView.cpp : 实现文件
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormRollView.h"


// CFormRollView

IMPLEMENT_DYNCREATE(CFormRollView, CFormView)

CFormRollView::CFormRollView()
	: CFormView(CFormRollView::IDD)
{

}

CFormRollView::~CFormRollView()
{
}

void CFormRollView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormRollView, CFormView)
END_MESSAGE_MAP()


// CFormRollView 诊断

#ifdef _DEBUG
void CFormRollView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormRollView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormRollView 消息处理程序
