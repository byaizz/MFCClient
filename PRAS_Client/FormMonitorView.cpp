// FormMonitorView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormMonitorView.h"


// CFormMonitorView

IMPLEMENT_DYNCREATE(CFormMonitorView, CFormView)

CFormMonitorView::CFormMonitorView()
	: CFormView(CFormMonitorView::IDD)
{

}

CFormMonitorView::~CFormMonitorView()
{
}

void CFormMonitorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormMonitorView, CFormView)
END_MESSAGE_MAP()


// CFormMonitorView ���

#ifdef _DEBUG
void CFormMonitorView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormMonitorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormMonitorView ��Ϣ�������

void CFormMonitorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
//	AfxMessageBox(_T("init"));
}
