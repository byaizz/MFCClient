// ChildFrm.cpp : CChildFrame 类的实现
//
#include "stdafx.h"
#include "PRAS_Client.h"

#include "ChildFrm.h"
#include "FormNavigView.h"
#include "FormMonitorView.h"
#include "FormRollView.h"
#include "FormConfigView.h"
#include "FormUserView.h"
#include "FormFurnaceView.h"
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
	ON_MESSAGE(UM_CLOSE,OnUMClose)
	ON_MESSAGE(UM_VIEW_CHANGE,OnUMViewChange)
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
//	AfxGetMainWnd()->SetMenu(NULL);//屏蔽菜单
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
	SetTimer(ID_TIMER_CHILDFRM,1000,NULL);//设置计时器触发间隔1000ms，响应函数为默认响应

	CRect rcClient;
	GetClientRect(&rcClient);//获取客户区坐标
	ScreenToClient(rcClient);//转换屏幕坐标到客户区坐标，转换后客户区左上角坐标为(0,0)

	if (!m_wndSplitter.CreateStatic(this,1,2))//分割窗口，一行两列
		return FALSE;

	//创建左边视图
	if (!m_wndSplitter.CreateView(0,
									0,
									RUNTIME_CLASS(CFormNavigView),
									CSize(rcClient.Width()*0.2,rcClient.Height()),
									pContext))
	{
		return FALSE;
	}

	//创建右边视图，默认为monitor view
	if (!m_wndSplitter.CreateView(0,
									1,
									RUNTIME_CLASS(CFormMonitorView),
									CSize(rcClient.Width()*0.8,
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
	if (!m_SerComm.IsCommInit())
	{
		if (!m_SerComm.InitComm())
		{
			MessageBox(_T("通信初始化失败"));
			this->GetTopLevelFrame()->PostMessage(WM_CLOSE);
		}
	}
	static int count = 0;
	if (count > 55)
	{
		count = 0;
	}
	static char text[56] = {0};
	text[count] = 'a';
	count += 2;

	m_SerComm.SendData(text,sizeof(text));

	CMDIChildWnd::OnTimer(nIDEvent);
}

LRESULT CChildFrame::OnUMClose(WPARAM wParam,LPARAM lParam)
{
	int iRet = 0;
	//可在资源视图String Table中修改标题，ID:AFX_IDS_APP_TITLE
	iRet = AfxMessageBox(_T("确定退出系统？"),MB_YESNO|MB_ICONQUESTION);

	if (iRet == IDYES)
	{
		this->GetTopLevelFrame()->PostMessage(WM_CLOSE);
	}
	return 0;
}

LRESULT CChildFrame::OnUMViewChange(WPARAM wParam,LPARAM lParam)
{
	SwitchRightView(wParam);
	return 0;
}

BOOL CChildFrame::SwitchRightView(WPARAM wParam)
{
	if (!m_wndSplitter.GetPane(0,1))//判断右侧是否存在视图
	{
		return FALSE;
	}

	m_wndSplitter.DeleteView(0,1);//删除右侧视图

	switch (wParam)
	{
	case IDView::ID_VIEW_MONITOR:
		{
			m_wndSplitter.CreateView(0,
				1,
				RUNTIME_CLASS(CFormMonitorView),
				CSize(0,0),
				NULL);
			break;
		}
	case IDView::ID_VIEW_ROLL:
		{
			m_wndSplitter.CreateView(0,
				1,
				RUNTIME_CLASS(CFormRollView),
				CSize(0,0),
				NULL);
			break;
		}
	case IDView::ID_VIEW_CONFIG:
		{
			m_wndSplitter.CreateView(0,
				1,
				RUNTIME_CLASS(CFormConfigView),
				CSize(0,0),
				NULL);
			break;
		}
	case IDView::ID_VIEW_USER:
		{
			m_wndSplitter.CreateView(0,
				1,
				RUNTIME_CLASS(CFormUserView),
				CSize(0,0),
				NULL);
			break;
		}
	case IDView::ID_VIEW_FURNACE:
		{
			m_wndSplitter.CreateView(0,
				1,
				RUNTIME_CLASS(CFormFurnaceView),
				CSize(0,0),
				NULL);
			break;
		}
	default:
		break;
	}

	m_wndSplitter.RecalcLayout();
 
	return TRUE;
}
