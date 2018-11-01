// FormNavigView.cpp : 实现文件
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormNavigView.h"
#include "PRAS_Definition.h"


// CFormNavigView

IMPLEMENT_DYNCREATE(CFormNavigView, CFormView)

CFormNavigView::CFormNavigView()
	: CFormView(CFormNavigView::IDD)
	, m_lastViewID(0)
{

}

CFormNavigView::~CFormNavigView()
{
}

void CFormNavigView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MONITOR, m_btnMonitor);
	DDX_Control(pDX, IDC_BUTTON_ROLL, m_btnRoll);
	DDX_Control(pDX, IDC_BUTTON_USER, m_btnUser);
	DDX_Control(pDX, IDC_BUTTON_CONFIG, m_btnConfig);
	DDX_Control(pDX, IDC_BUTTON_FURNACE, m_btnFurnace);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_btnQuit);
	DDX_Control(pDX, IDC_STATIC_TIME, m_staticCurrentTime);
}

BEGIN_MESSAGE_MAP(CFormNavigView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CFormNavigView::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_MONITOR, &CFormNavigView::OnBnClickedButtonMonitor)
	ON_BN_CLICKED(IDC_BUTTON_ROLL, &CFormNavigView::OnBnClickedButtonRoll)
	ON_BN_CLICKED(IDC_BUTTON_USER, &CFormNavigView::OnBnClickedButtonUser)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CFormNavigView::OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_FURNACE, &CFormNavigView::OnBnClickedButtonFurnace)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFormNavigView 诊断

#ifdef _DEBUG
void CFormNavigView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormNavigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormNavigView 消息处理程序

void CFormNavigView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	CRect clientRect;
	GetClientRect(&clientRect);//获取客户区坐标
	ScreenToClient(&clientRect);//转换屏幕坐标到客户区坐标

	//设置按钮位置
	m_btnMonitor.MoveWindow(30,90,124,36);
	m_btnRoll.MoveWindow(30,140,124,36);
	m_btnUser.MoveWindow(30,190,124,36);
	m_btnConfig.MoveWindow(30,240,124,36);
	m_btnFurnace.MoveWindow(30,290,124,36);
	m_btnQuit.MoveWindow(30,340,124,36);

	//设置初始默认状态
	SetButtonStatus(ID_VIEW_MONITOR,FALSE);
	m_lastViewID = ID_VIEW_MONITOR;
	UpdataCurrentTime();

	SetTimer(ID_TIMER_CURRENTTIME,TIMER_CURRENT_TIME,NULL);
}

void CFormNavigView::UpdataCurrentTime()
{
	if (m_staticCurrentTime.m_hWnd == NULL)
	{
		return;
	}
	CString sTime;
	CTime time = CTime::GetCurrentTime();
	sTime = time.Format("%A\n%H:%M:%S\t%Y/%m/%d");
	m_staticCurrentTime.SetWindowText(sTime);
}

void CFormNavigView::SetButtonStatus(int iViewID, BOOL status)
{
	//设置按钮状态
	switch (iViewID)
	{
	case ID_VIEW_MONITOR:
		{
			m_btnMonitor.EnableWindow(status);
			break;
		}
	case ID_VIEW_ROLL:
		{
			m_btnRoll.EnableWindow(status);
			break;
		}
	case ID_VIEW_CONFIG:
		{
			m_btnConfig.EnableWindow(status);
			break;
		}
	case ID_VIEW_USER:
		{
			m_btnUser.EnableWindow(status);
			break;
		}
	case ID_VIEW_FURNACE:
		{
			m_btnFurnace.EnableWindow(status);
			break;
		}
	default:
		break;
	}
	return;
}

void CFormNavigView::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	this->GetParentFrame()->SendMessage(UM_CLOSE);
}

void CFormNavigView::OnBnClickedButtonMonitor()
{
	// TODO: 在此添加控件通知处理程序代码
	SetButtonStatus(m_lastViewID,TRUE);//前一view按钮释放
	SetButtonStatus(ID_VIEW_MONITOR,FALSE);//当前view按钮锁定
	m_lastViewID = ID_VIEW_MONITOR;//保存当前viewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_MONITOR);//发送view change消息
}

void CFormNavigView::OnBnClickedButtonRoll()
{
	// TODO: 在此添加控件通知处理程序代码
	SetButtonStatus(m_lastViewID,TRUE);//前一view按钮释放
	SetButtonStatus(ID_VIEW_ROLL,FALSE);//当前view按钮锁定
	m_lastViewID = ID_VIEW_ROLL;//保存当前viewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_ROLL);//发送view change消息
}

void CFormNavigView::OnBnClickedButtonUser()
{
	// TODO: 在此添加控件通知处理程序代码
	SetButtonStatus(m_lastViewID,TRUE);//前一view按钮释放
	SetButtonStatus(ID_VIEW_USER,FALSE);//当前view按钮锁定
	m_lastViewID = ID_VIEW_USER;//保存当前viewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_USER);//发送view change消息
}

void CFormNavigView::OnBnClickedButtonConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	SetButtonStatus(m_lastViewID,TRUE);//前一view按钮释放
	SetButtonStatus(ID_VIEW_CONFIG,FALSE);//当前view按钮锁定
	m_lastViewID = ID_VIEW_CONFIG;//保存当前viewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_CONFIG);//发送view change消息
}

void CFormNavigView::OnBnClickedButtonFurnace()
{
	// TODO: 在此添加控件通知处理程序代码
	SetButtonStatus(m_lastViewID,TRUE);//前一view按钮释放
	SetButtonStatus(ID_VIEW_FURNACE,FALSE);//当前view按钮锁定
	m_lastViewID = ID_VIEW_FURNACE;//保存当前viewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_FURNACE);//发送view change消息
}

void CFormNavigView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdataCurrentTime();

	CFormView::OnTimer(nIDEvent);
}
