#pragma once
#include "afxwin.h"



// CFormNavigView 窗体视图

class CFormNavigView : public CFormView
{
	DECLARE_DYNCREATE(CFormNavigView)

protected:
	CFormNavigView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFormNavigView();

public:
	enum { IDD = IDD_FORMNAVIGVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// 过程监控按钮
	CButton m_btnMonitor;
	// 轧辊信息按钮
	CButton m_btnRoll;
	// 用户管理按钮
	CButton m_btnUser;
	// 轧机操作按钮
	CButton m_btnConfig;
	// 加热炉按钮
	CButton m_btnFurnace;
	// 系统退出按钮
	CButton m_btnQuit;
	virtual void OnInitialUpdate();
	void UpdataCurrentTime();
	void SetButtonStatus(int iViewID, BOOL status);
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonMonitor();
	afx_msg void OnBnClickedButtonRoll();
	afx_msg void OnBnClickedButtonUser();
	afx_msg void OnBnClickedButtonConfig();
	afx_msg void OnBnClickedButtonFurnace();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 用于显示当前时间
	CStatic m_staticCurrentTime;
	int m_lastViewID;
};


