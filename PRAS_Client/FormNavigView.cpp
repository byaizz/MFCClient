// FormNavigView.cpp : ʵ���ļ�
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


// CFormNavigView ���

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


// CFormNavigView ��Ϣ�������

void CFormNavigView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	CRect clientRect;
	GetClientRect(&clientRect);//��ȡ�ͻ�������
	ScreenToClient(&clientRect);//ת����Ļ���굽�ͻ�������

	//���ð�ťλ��
	m_btnMonitor.MoveWindow(30,90,124,36);
	m_btnRoll.MoveWindow(30,140,124,36);
	m_btnUser.MoveWindow(30,190,124,36);
	m_btnConfig.MoveWindow(30,240,124,36);
	m_btnFurnace.MoveWindow(30,290,124,36);
	m_btnQuit.MoveWindow(30,340,124,36);

	//���ó�ʼĬ��״̬
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
	//���ð�ť״̬
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetParentFrame()->SendMessage(UM_CLOSE);
}

void CFormNavigView::OnBnClickedButtonMonitor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetButtonStatus(m_lastViewID,TRUE);//ǰһview��ť�ͷ�
	SetButtonStatus(ID_VIEW_MONITOR,FALSE);//��ǰview��ť����
	m_lastViewID = ID_VIEW_MONITOR;//���浱ǰviewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_MONITOR);//����view change��Ϣ
}

void CFormNavigView::OnBnClickedButtonRoll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetButtonStatus(m_lastViewID,TRUE);//ǰһview��ť�ͷ�
	SetButtonStatus(ID_VIEW_ROLL,FALSE);//��ǰview��ť����
	m_lastViewID = ID_VIEW_ROLL;//���浱ǰviewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_ROLL);//����view change��Ϣ
}

void CFormNavigView::OnBnClickedButtonUser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetButtonStatus(m_lastViewID,TRUE);//ǰһview��ť�ͷ�
	SetButtonStatus(ID_VIEW_USER,FALSE);//��ǰview��ť����
	m_lastViewID = ID_VIEW_USER;//���浱ǰviewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_USER);//����view change��Ϣ
}

void CFormNavigView::OnBnClickedButtonConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetButtonStatus(m_lastViewID,TRUE);//ǰһview��ť�ͷ�
	SetButtonStatus(ID_VIEW_CONFIG,FALSE);//��ǰview��ť����
	m_lastViewID = ID_VIEW_CONFIG;//���浱ǰviewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_CONFIG);//����view change��Ϣ
}

void CFormNavigView::OnBnClickedButtonFurnace()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetButtonStatus(m_lastViewID,TRUE);//ǰһview��ť�ͷ�
	SetButtonStatus(ID_VIEW_FURNACE,FALSE);//��ǰview��ť����
	m_lastViewID = ID_VIEW_FURNACE;//���浱ǰviewID
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_FURNACE);//����view change��Ϣ
}

void CFormNavigView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdataCurrentTime();

	CFormView::OnTimer(nIDEvent);
}
