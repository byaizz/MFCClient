// ChildFrm.h : CChildFrame 类的接口
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

// 属性
public:

// 操作
public:

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
private:
	CSplitterWnd m_wndSplitter;//窗口分割器
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnUMClose(WPARAM wParam,LPARAM lParam);//客户端退出
	afx_msg LRESULT OnUMViewChange(WPARAM wParam,LPARAM lParam);//view切换
	BOOL SwitchRightView(WPARAM wParam);//页面切换

	CPRASGuiSerComm m_SerComm;
	bool m_bInit;
};
