// PRAS_ClientView.h : CPRAS_ClientView 类的接口
//


#pragma once


class CPRAS_ClientView : public CView
{
protected: // 仅从序列化创建
	CPRAS_ClientView();
	DECLARE_DYNCREATE(CPRAS_ClientView)

// 属性
public:
	CPRAS_ClientDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPRAS_ClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PRAS_ClientView.cpp 中的调试版本
inline CPRAS_ClientDoc* CPRAS_ClientView::GetDocument() const
   { return reinterpret_cast<CPRAS_ClientDoc*>(m_pDocument); }
#endif

