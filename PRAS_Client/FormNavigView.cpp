// FormNavigView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormNavigView.h"


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
}

BEGIN_MESSAGE_MAP(CFormNavigView, CFormView)
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
