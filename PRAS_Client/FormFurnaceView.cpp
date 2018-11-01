// FormFurnaceView.cpp : 实现文件
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormFurnaceView.h"


// CFormFurnaceView

IMPLEMENT_DYNCREATE(CFormFurnaceView, CFormView)

CFormFurnaceView::CFormFurnaceView()
	: CFormView(CFormFurnaceView::IDD)
{

}

CFormFurnaceView::~CFormFurnaceView()
{
}

void CFormFurnaceView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormFurnaceView, CFormView)
END_MESSAGE_MAP()


// CFormFurnaceView 诊断

#ifdef _DEBUG
void CFormFurnaceView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormFurnaceView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormFurnaceView 消息处理程序
