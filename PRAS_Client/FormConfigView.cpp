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
	DDX_Control(pDX, IDC_COMBO1, m_ComboBoxCtrl);
}

BEGIN_MESSAGE_MAP(CFormConfigView, CFormView)
	ON_CBN_SELENDOK(IDC_COMBO1, &CFormConfigView::OnCbnSelendokCombo1)
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

void CFormConfigView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_ComboBoxCtrl.InsertString(0,_T("我是第一"));
	m_ComboBoxCtrl.InsertString(0,_T("我是第二"));
	m_ComboBoxCtrl.InsertString(0,_T("我是第三"));
	m_ComboBoxCtrl.InsertString(0,_T("我是第四"));
	m_ComboBoxCtrl.InsertString(2,_T("我是第五"));
}

void CFormConfigView::OnCbnSelendokCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_ComboBoxCtrl.GetCurSel();
	CString selection;
	selection.Format(_T("我选第 %d 个"),i+1);
	MessageBox(selection);
}
