#pragma once

#include "GridCtrl.h"
#include "afxwin.h"
#include "d:\vsprojects\pras_client\gridctrlhead\gridctrl.h"

// CFormMonitorView ������ͼ

class CFormMonitorView : public CFormView
{
	DECLARE_DYNCREATE(CFormMonitorView)

protected:
	CFormMonitorView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFormMonitorView();

public:
	enum { IDD = IDD_FORMMONITORVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
private:
	// �������
	CGridCtrl m_GridSlabInfo;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	CButton m_buttonControl;
	afx_msg void OnEnChangeEdit1();
	CString m_edit1;
	CString m_edit2;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_editCtrl1;
	CEdit m_editCtrl2;
	CEdit m_editCtrl3;
	CEdit m_editCtrl4;
	CEdit m_editCtrl5;
    CGridCtrl m_testGrid;
};


