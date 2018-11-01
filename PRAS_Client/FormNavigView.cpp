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
	DDX_Control(pDX, IDC_BUTTON_OPERATION, m_btnOperation);
	DDX_Control(pDX, IDC_BUTTON_FURNACE, m_btnFurnace);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_btnQuit);
	DDX_Control(pDX, IDC_STATIC_TIME, m_staticCurrentTime);
}

BEGIN_MESSAGE_MAP(CFormNavigView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CFormNavigView::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_MONITOR, &CFormNavigView::OnBnClickedButtonMonitor)
	ON_BN_CLICKED(IDC_BUTTON_ROLL, &CFormNavigView::OnBnClickedButtonRoll)
	ON_BN_CLICKED(IDC_BUTTON_USER, &CFormNavigView::OnBnClickedButtonUser)
	ON_BN_CLICKED(IDC_BUTTON_OPERATION, &CFormNavigView::OnBnClickedButtonOperation)
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
	m_btnOperation.MoveWindow(30,240,124,36);
	m_btnFurnace.MoveWindow(30,290,124,36);
	m_btnQuit.MoveWindow(30,340,124,36);

	SetTimer(ID_TIMER_CURRENTTIME,100,NULL);
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

void CFormNavigView::OnBnClickedButtonQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetParentFrame()->SendMessage(UM_CLOSE);
}

void CFormNavigView::OnBnClickedButtonMonitor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_MONITOR);
}

void CFormNavigView::OnBnClickedButtonRoll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_ROLL);
}

void CFormNavigView::OnBnClickedButtonUser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_USER);
}

void CFormNavigView::OnBnClickedButtonOperation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_OPERATION);
}

void CFormNavigView::OnBnClickedButtonFurnace()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetParentFrame()->SendMessage(UM_VIEW_CHANGE,ID_VIEW_FURNACE);
}

void CFormNavigView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdataCurrentTime();

	CFormView::OnTimer(nIDEvent);
}
