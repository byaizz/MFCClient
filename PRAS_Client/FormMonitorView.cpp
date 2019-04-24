// FormMonitorView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormMonitorView.h"
#include "ExcelManager.h"

#define ONE_DECIMAL	1
#define TWO_DECIMAL	2

// CFormMonitorView

IMPLEMENT_DYNCREATE(CFormMonitorView, CFormView)

CFormMonitorView::CFormMonitorView()
	: CFormView(CFormMonitorView::IDD)
	, m_edit1(_T(""))
	, m_edit2(_T(""))
{

}

CFormMonitorView::~CFormMonitorView()
{
}

void CFormMonitorView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_GridControl(pDX, IDC_CUSTOM_GRID_SLAB, m_GridSlabInfo);
    DDX_Control(pDX, IDC_BUTTON1, m_buttonControl);
    DDX_Text(pDX, IDC_EDIT1, m_edit1);
    DDX_Text(pDX, IDC_EDIT2, m_edit2);
    DDX_Control(pDX, IDC_EDIT1, m_editCtrl1);
    DDX_Control(pDX, IDC_EDIT2, m_editCtrl2);
    DDX_Control(pDX, IDC_EDIT3, m_editCtrl3);
    DDX_Control(pDX, IDC_EDIT4, m_editCtrl4);
    DDX_Control(pDX, IDC_EDIT5, m_editCtrl5);
    DDX_Control(pDX, IDC_CUSTOM1, m_testGrid);
}

BEGIN_MESSAGE_MAP(CFormMonitorView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CFormMonitorView::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CFormMonitorView::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CFormMonitorView ���

#ifdef _DEBUG
void CFormMonitorView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormMonitorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormMonitorView ��Ϣ�������

void CFormMonitorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
//     m_testGrid.SetColumnCount(3);
//     m_testGrid.SetRowCount(2);

	//���ñ������
 	m_GridSlabInfo.SetListMode(TRUE);//�����Ƿ�Ϊ����ģʽ
	m_GridSlabInfo.SetGridColor(RGB(255,255,255));//������������ɫ
	m_GridSlabInfo.SetTextBkColor(RGB(128,255,255));//���ñ�񱳾���ɫ
	m_GridSlabInfo.SetTextColor(RGB(238,44,44));//����������ɫ
	m_GridSlabInfo.SetModified(FALSE);//�����Ƿ���޸�
	m_GridSlabInfo.EnableSelection(FALSE);//�����Ƿ��ѡ��
	m_GridSlabInfo.SetBkColor(RGB(255,255,255));//���ñ�����ɫ(���֮�����ɫ)

	//���ñ��������
	int rowCount = 6;
	int colCount = 6;
	m_GridSlabInfo.SetRowCount(rowCount);//��������
 	m_GridSlabInfo.SetColumnCount(colCount);//��������
	m_GridSlabInfo.SetFixedRowCount(1);//���ù̶�����
	m_GridSlabInfo.SetFixedColumnCount(1);//���ù̶�����
	m_GridSlabInfo.SetEditable(FALSE);//�����Ƿ�ɱ༭
	m_GridSlabInfo.ShowScrollBar(SB_BOTH, FALSE);//�����Ƿ���ʾ������
	m_GridSlabInfo.SetRowBkColour(2,RGB(0,255,0));//����������ɫ

	for (int i = 0; i < rowCount; ++i)
	{
		GV_ITEM item;
		item.mask = GVIF_TEXT | GVIF_FORMAT;
		item.row = i;
		item.nFormat = DT_LEFT | DT_SINGLELINE | DT_END_ELLIPSIS;
		for (int j = 0; j < colCount; ++j)
		{
			item.col = j;
			item.szText.Format(_T("%d��%d��"), i+1, j+1);
			m_GridSlabInfo.SetItem(&item);
			m_GridSlabInfo.SetRowHeight(item.row,25);
			m_GridSlabInfo.SetColumnWidth(item.col,75);
		}	
	}

	m_GridSlabInfo.AutoSize();
	int width = m_GridSlabInfo.GetColumnCount()*m_GridSlabInfo.GetColumnWidth(0);
	int height = m_GridSlabInfo.GetRowCount()*m_GridSlabInfo.GetRowHeight(0);
	m_GridSlabInfo.MoveWindow(100,100,width,height);

	m_editCtrl1.SetWindowText(_T("12345"));
	m_editCtrl2.SetWindowText(_T("12345"));
	m_editCtrl3.SetWindowText(_T("12345"));
	m_editCtrl4.SetWindowText(_T("12345"));
	m_editCtrl5.SetWindowText(_T("12345"));

}

void CFormMonitorView::OnBnClickedButton1()
{
	m_buttonControl.EnableWindow(FALSE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExcelManager excel;
	if (excel.OpenFromTemplate(_T("E:\\test_by.xlsx")))
	{
		excel.Test1();
		excel.SaveAsPDF(_T("E:\\test_by.pdf"));
	}
	excel.Close();
// 	if (excel.Open(_T("E:\\test.xlsx")))
// 	{
// 		excel.Test();
// 	}
	m_buttonControl.EnableWindow(TRUE);
}

void CFormMonitorView::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// 	UpdateData(TRUE);
// 	m_edit2 = m_edit1;
// 	UpdateData(FALSE);
	
}

BOOL CFormMonitorView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_LBUTTONUP == pMsg->message)
	{
		const int nSize(5);
		int nNumber[nSize] = {IDC_EDIT1,
		IDC_EDIT2,
		IDC_EDIT3,
		IDC_EDIT4,
		IDC_EDIT5};

		for (int i = 0; i < nSize; i++)
		{
			if (pMsg->hwnd == ((CEdit*)GetDlgItem(nNumber[i]))->m_hWnd)
			{
				((CEdit*)GetDlgItem(nNumber[i]))->SetSel(0, -1);
			}
		}	
	}
#if 1
	if (   (WM_KEYFIRST <= pMsg->message)
		&& (WM_KEYLAST  >= pMsg->message))
	{  
		if(   (VK_RETURN == pMsg->wParam)
			&& (WM_KEYUP == pMsg->message))
		{
			if (GetFocus() == GetDlgItem(IDC_EDIT1) ||
				GetFocus() == GetDlgItem(IDC_EDIT2) ||
				GetFocus() == GetDlgItem(IDC_EDIT3) ||
				GetFocus() == GetDlgItem(IDC_EDIT4))
			{
				bool bFlag(true);
				if (GetFocus() == GetDlgItem(IDC_EDIT1)
					&& bFlag)
				{
					bFlag = false;
					m_editCtrl2.SetFocus();
					m_editCtrl2.SetSel(0, -1);
				}
				if (GetFocus() == GetDlgItem(IDC_EDIT2)
					&& bFlag)
				{
					bFlag = false;
					m_editCtrl3.SetFocus();
					m_editCtrl3.SetSel(0, -1);
				}
				if (GetFocus() == GetDlgItem(IDC_EDIT3)
					&& bFlag)
				{
					bFlag = false;
					m_editCtrl4.SetFocus();
					m_editCtrl4.SetSel(0, -1);
				}
				if (GetFocus() == GetDlgItem(IDC_EDIT4)
					&& bFlag)
				{
					bFlag = false;
					m_editCtrl5.SetFocus();
					m_editCtrl5.SetSel(0, -1);
				}
			}

		}
	}
#endif
	return CFormView::PreTranslateMessage(pMsg);
}
