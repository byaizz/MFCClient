#pragma once



// CFormNavigView ������ͼ

class CFormNavigView : public CFormView
{
	DECLARE_DYNCREATE(CFormNavigView)

protected:
	CFormNavigView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


