// PRAS_ClientDoc.cpp : CPRAS_ClientDoc ���ʵ��
//

#include "stdafx.h"
#include "PRAS_Client.h"

#include "PRAS_ClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPRAS_ClientDoc

IMPLEMENT_DYNCREATE(CPRAS_ClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CPRAS_ClientDoc, CDocument)
END_MESSAGE_MAP()


// CPRAS_ClientDoc ����/����

CPRAS_ClientDoc::CPRAS_ClientDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPRAS_ClientDoc::~CPRAS_ClientDoc()
{
}

BOOL CPRAS_ClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPRAS_ClientDoc ���л�

void CPRAS_ClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CPRAS_ClientDoc ���

#ifdef _DEBUG
void CPRAS_ClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPRAS_ClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPRAS_ClientDoc ����
