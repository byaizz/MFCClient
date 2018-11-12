// ChildFrm.h : CChildFrame ��Ľӿ�
//


#pragma once

#include "PRASGuiSerComm.h"

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);

// ����
public:

// ����
public:

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
private:
	CSplitterWnd m_wndSplitter;//���ڷָ���
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnUMClose(WPARAM wParam,LPARAM lParam);//�ͻ����˳�
	afx_msg LRESULT OnUMViewChange(WPARAM wParam,LPARAM lParam);//view�л�
	BOOL SwitchRightView(WPARAM wParam);//ҳ���л�

	CPRASGuiSerComm m_SerComm;
	bool m_bInit;
};
