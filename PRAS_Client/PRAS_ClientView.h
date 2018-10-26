// PRAS_ClientView.h : CPRAS_ClientView ��Ľӿ�
//


#pragma once


class CPRAS_ClientView : public CView
{
protected: // �������л�����
	CPRAS_ClientView();
	DECLARE_DYNCREATE(CPRAS_ClientView)

// ����
public:
	CPRAS_ClientDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPRAS_ClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PRAS_ClientView.cpp �еĵ��԰汾
inline CPRAS_ClientDoc* CPRAS_ClientView::GetDocument() const
   { return reinterpret_cast<CPRAS_ClientDoc*>(m_pDocument); }
#endif

