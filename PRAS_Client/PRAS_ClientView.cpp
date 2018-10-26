// PRAS_ClientView.cpp : CPRAS_ClientView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CPRAS_ClientView 构造/析构

CPRAS_ClientView::CPRAS_ClientView()
{
	// TODO: 在此处添加构造代码

}

CPRAS_ClientView::~CPRAS_ClientView()
{
}

BOOL CPRAS_ClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPRAS_ClientView 绘制

void CPRAS_ClientView::OnDraw(CDC* /*pDC*/)
{
	CPRAS_ClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPRAS_ClientView 打印

BOOL CPRAS_ClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPRAS_ClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPRAS_ClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CPRAS_ClientView 诊断

#ifdef _DEBUG
void CPRAS_ClientView::AssertValid() const
{
	CView::AssertValid();
}

void CPRAS_ClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPRAS_ClientDoc* CPRAS_ClientView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPRAS_ClientDoc)));
	return (CPRAS_ClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CPRAS_ClientView 消息处理程序
