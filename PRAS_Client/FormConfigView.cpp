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
	m_ComboBoxCtrl.InsertString(0,_T("���ǵ�һ"));
	m_ComboBoxCtrl.InsertString(0,_T("���ǵڶ�"));
	m_ComboBoxCtrl.InsertString(0,_T("���ǵ���"));
	m_ComboBoxCtrl.InsertString(0,_T("���ǵ���"));
	m_ComboBoxCtrl.InsertString(2,_T("���ǵ���"));
}

void CFormConfigView::OnCbnSelendokCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = m_ComboBoxCtrl.GetCurSel();
	CString selection;
	selection.Format(_T("��ѡ�� %d ��"),i+1);
	MessageBox(selection);
}
