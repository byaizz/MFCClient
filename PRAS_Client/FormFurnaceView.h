#pragma once



// CFormFurnaceView ������ͼ

class CFormFurnaceView : public CFormView
{
	DECLARE_DYNCREATE(CFormFurnaceView)

protected:
	CFormFurnaceView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFormFurnaceView();

public:
	enum { IDD = IDD_FORMFURNACEVIEW };
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


