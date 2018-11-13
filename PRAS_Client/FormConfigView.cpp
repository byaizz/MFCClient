// FormConfigView.cpp : ʵ���ļ�
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


// CFormConfigView ���

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


// CFormConfigView ��Ϣ�������

void CFormConfigView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//ComboBox�ؼ���ʼ��
	m_ComboBoxCtrl.InsertString(0,_T("���ǵ�һ"));
	m_ComboBoxCtrl.InsertString(0,_T("���ǵڶ�"));
	m_ComboBoxCtrl.InsertString(0,_T("���ǵ���"));
	m_ComboBoxCtrl.InsertString(0,_T("���ǵ���"));
	m_ComboBoxCtrl.InsertString(2,_T("���ǵ���"));

	//����toolTips
	EnableToolTips(TRUE);//enable
	m_toolTips.Create(this);
	m_toolTips.Activate(TRUE);
	m_toolTips.SetTipTextColor(RGB(0,255,0));//font color
	m_toolTips.SetDelayTime(100);//delay time
	m_toolTips.SetDelayTime(TTDT_AUTOPOP,25000);//set duration
	//IDC_TESTΪ���������ʾ�Ŀؼ�IDC(����Ӷ��)��"helloΪ����ӵ���ʾ���"
	m_toolTips.AddTool(GetDlgItem(IDC_COMBO1),_T("��ʾ��Ϣ"));
	m_toolTips.AddTool(GetDlgItem(IDC_BUTTON1),_T("���ǰ�ť"));

	//CStatic�ؼ���Ĭ�ϲ������κ������Ϣ�ģ���Ҫ����SS_NOTIFY������ʾtips
	CStatic	*staticText = (CStatic *)GetDlgItem(IDC_STATIC_TEST2);
	LONG style = GetWindowLong(staticText->GetSafeHwnd(), GWL_STYLE);
	SetWindowLong(staticText->GetSafeHwnd(),GWL_STYLE,style|SS_NOTIFY);
	m_toolTips.AddTool(GetDlgItem(IDC_STATIC_TEST2),_T("�����ı���"));
}

void CFormConfigView::OnCbnSelendokCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = m_ComboBoxCtrl.GetCurSel();
	CString selection;
	selection.Format(_T("��ѡ�� %d ��"),i+1);
	MessageBox(selection);
}

BOOL CFormConfigView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_toolTips.RelayEvent(pMsg);//��Ϣת��	
	}

	return CFormView::PreTranslateMessage(pMsg);
}
