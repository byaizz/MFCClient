#pragma once



// CFormUserView ������ͼ

class CFormUserView : public CFormView
{
	DECLARE_DYNCREATE(CFormUserView)

protected:
	CFormUserView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFormUserView();

public:
	enum { IDD = IDD_FORMUSERVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


