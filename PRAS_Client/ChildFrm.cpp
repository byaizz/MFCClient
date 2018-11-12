// ChildFrm.cpp : CChildFrame ���ʵ��
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
//	AfxGetMainWnd()->SetMenu(NULL);//���β˵�
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
	SetTimer(ID_TIMER_CHILDFRM,1000,NULL);//���ü�ʱ���������1000ms����Ӧ����ΪĬ����Ӧ

	CRect rcClient;
	GetClientRect(&rcClient);//��ȡ�ͻ�������
	ScreenToClient(rcClient);//ת����Ļ���굽�ͻ������꣬ת����ͻ������Ͻ�����Ϊ(0,0)

	if (!m_wndSplitter.CreateStatic(this,1,2))//�ָ�ڣ�һ������
		return FALSE;

	//���������ͼ
	if (!m_wndSplitter.CreateView(0,
									0,
									RUNTIME_CLASS(CFormNavigView),
									CSize(rcClient.Width()*0.2,rcClient.Height()),
									pContext))
	{
		return FALSE;
	}

	//�����ұ���ͼ��Ĭ��Ϊmonitor view
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


// CChildFrame ��Ϣ�������

void CChildFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_SerComm.IsCommInit())
	{
		if (!m_SerComm.InitComm())
		{
			MessageBox(_T("ͨ�ų�ʼ��ʧ��"));
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
	//������Դ��ͼString Table���޸ı��⣬ID:AFX_IDS_APP_TITLE
	iRet = AfxMessageBox(_T("ȷ���˳�ϵͳ��"),MB_YESNO|MB_ICONQUESTION);

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
	if (!m_wndSplitter.GetPane(0,1))//�ж��Ҳ��Ƿ������ͼ
	{
		return FALSE;
	}

	m_wndSplitter.DeleteView(0,1);//ɾ���Ҳ���ͼ

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
