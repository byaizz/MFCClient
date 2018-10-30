// ChildFrm.cpp : CChildFrame 类的实现
//
#include "stdafx.h"
#include "PRAS_Client.h"

#include "ChildFrm.h"
#include "FormNavigView.h"
#include "FormMonitorView.h"
#include "PRAS_Definition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
}

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	return;
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	AfxGetMainWnd()->SetMenu(NULL);//屏蔽菜单
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_CHILD|WS_VISIBLE|WS_OVERLAPPED|WS_CAPTION|WS_MAXIMIZE|FWS_ADDTOTITLE;
	return TRUE;
}


// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	//启动计时器
	SetTimer(COMP_TIMER_ID,1000,NULL);//设置计时器触发间隔1000ms，响应函数为默认响应

	CRect rcClient;
	GetClientRect(&rcClient);
	ScreenToClient(rcClient);

	if (!m_wndSplitter.CreateStatic(this,1,2))//分割窗口，一行两列
		return FALSE;

	//创建左边视图
	if (!m_wndSplitter.CreateView(0,
									0,
									RUNTIME_CLASS(CFormNavigView),
									CSize(rcClient.Width()*0.4,rcClient.Height()),
									pContext))
	{
		return FALSE;
	}


	//创建右边视图
	if (!m_wndSplitter.CreateView(0,
									1,
									RUNTIME_CLASS(CFormMonitorView),
									CSize(rcClient.Width()*0.6,
									rcClient.Height()),
									pContext))
	{
		return FALSE;
	}

	return TRUE;
}

#endif //_DEBUG


// CChildFrame 消息处理程序

void CChildFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == COMP_TIMER_ID)
	{
		static int sCount = 0;
		TRACE("第 %d 次执行timer\n", sCount++);
	}

	CMDIChildWnd::OnTimer(nIDEvent);
}
