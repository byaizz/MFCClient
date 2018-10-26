// PRAS_ClientView.cpp : CPRAS_ClientView ���ʵ��
//

#include "stdafx.h"
#include "PRAS_Client.h"

#include "PRAS_ClientDoc.h"
#include "PRAS_ClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPRAS_ClientView

IMPLEMENT_DYNCREATE(CPRAS_ClientView, CView)

BEGIN_MESSAGE_MAP(CPRAS_ClientView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CPRAS_ClientView ����/����

CPRAS_ClientView::CPRAS_ClientView()
{
	// TODO: �ڴ˴���ӹ������

}

CPRAS_ClientView::~CPRAS_ClientView()
{
}

BOOL CPRAS_ClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPRAS_ClientView ����

void CPRAS_ClientView::OnDraw(CDC* /*pDC*/)
{
	CPRAS_ClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPRAS_ClientView ��ӡ

BOOL CPRAS_ClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPRAS_ClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPRAS_ClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPRAS_ClientView ���

#ifdef _DEBUG
void CPRAS_ClientView::AssertValid() const
{
	CView::AssertValid();
}

void CPRAS_ClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPRAS_ClientDoc* CPRAS_ClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPRAS_ClientDoc)));
	return (CPRAS_ClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CPRAS_ClientView ��Ϣ�������
