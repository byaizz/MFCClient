// FormUserView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormUserView.h"


// CFormUserView

IMPLEMENT_DYNCREATE(CFormUserView, CFormView)

CFormUserView::CFormUserView()
	: CFormView(CFormUserView::IDD)
{

}

CFormUserView::~CFormUserView()
{
}

void CFormUserView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormUserView, CFormView)
END_MESSAGE_MAP()


// CFormUserView ���

#ifdef _DEBUG
void CFormUserView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormUserView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormUserView ��Ϣ�������
