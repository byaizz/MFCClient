// ChildFrm.cpp : CChildFrame ���ʵ��
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


// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	return;
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	AfxGetMainWnd()->SetMenu(NULL);//���β˵�
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_CHILD|WS_VISIBLE|WS_OVERLAPPED|WS_CAPTION|WS_MAXIMIZE|FWS_ADDTOTITLE;
	return TRUE;
}


// CChildFrame ���

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
	//������ʱ��
	SetTimer(COMP_TIMER_ID,1000,NULL);//���ü�ʱ���������1000ms����Ӧ����ΪĬ����Ӧ

	CRect rcClient;
	GetClientRect(&rcClient);
	ScreenToClient(rcClient);

	if (!m_wndSplitter.CreateStatic(this,1,2))//�ָ�ڣ�һ������
		return FALSE;

	//���������ͼ
	if (!m_wndSplitter.CreateView(0,
									0,
									RUNTIME_CLASS(CFormNavigView),
									CSize(rcClient.Width()*0.4,rcClient.Height()),
									pContext))
	{
		return FALSE;
	}


	//�����ұ���ͼ
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


// CChildFrame ��Ϣ�������

void CChildFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == COMP_TIMER_ID)
	{
		static int sCount = 0;
		TRACE("�� %d ��ִ��timer\n", sCount++);
	}

	CMDIChildWnd::OnTimer(nIDEvent);
}
