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
}

BEGIN_MESSAGE_MAP(CFormConfigView, CFormView)
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
