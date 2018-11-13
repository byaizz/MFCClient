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
	//ComboBox控件初始化
	m_ComboBoxCtrl.InsertString(0,_T("我是第一"));
	m_ComboBoxCtrl.InsertString(0,_T("我是第二"));
	m_ComboBoxCtrl.InsertString(0,_T("我是第三"));
	m_ComboBoxCtrl.InsertString(0,_T("我是第四"));
	m_ComboBoxCtrl.InsertString(2,_T("我是第五"));

	//创建toolTips
	EnableToolTips(TRUE);//enable
	m_toolTips.Create(this);
	m_toolTips.Activate(TRUE);
	m_toolTips.SetTipTextColor(RGB(0,255,0));//font color
	m_toolTips.SetDelayTime(100);//delay time
	m_toolTips.SetDelayTime(TTDT_AUTOPOP,25000);//set duration
	//IDC_TEST为你想添加提示的控件IDC(可添加多个)，"hello为想添加的提示语句"
	m_toolTips.AddTool(GetDlgItem(IDC_COMBO1),_T("提示信息"));
	m_toolTips.AddTool(GetDlgItem(IDC_BUTTON1),_T("我是按钮"));

	//CStatic控件是默认不接受任何鼠标信息的，需要设置SS_NOTIFY才能显示tips
	CStatic	*staticText = (CStatic *)GetDlgItem(IDC_STATIC_TEST2);
	LONG style = GetWindowLong(staticText->GetSafeHwnd(), GWL_STYLE);
	SetWindowLong(staticText->GetSafeHwnd(),GWL_STYLE,style|SS_NOTIFY);
	m_toolTips.AddTool(GetDlgItem(IDC_STATIC_TEST2),_T("我是文本框"));
}

void CFormConfigView::OnCbnSelendokCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_ComboBoxCtrl.GetCurSel();
	CString selection;
	selection.Format(_T("我选第 %d 个"),i+1);
	MessageBox(selection);
}

BOOL CFormConfigView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_toolTips.RelayEvent(pMsg);//消息转发	
	}

	return CFormView::PreTranslateMessage(pMsg);
}
