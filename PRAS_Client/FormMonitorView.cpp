// FormMonitorView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormMonitorView.h"
#include "ExcelManager.h"


// CFormMonitorView

IMPLEMENT_DYNCREATE(CFormMonitorView, CFormView)

CFormMonitorView::CFormMonitorView()
	: CFormView(CFormMonitorView::IDD)
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
}

BEGIN_MESSAGE_MAP(CFormMonitorView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CFormMonitorView::OnBnClickedButton1)
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

}

void CFormMonitorView::OnBnClickedButton1()
{
	m_buttonControl.EnableWindow(FALSE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExcelManager excel;
	if (!excel.Init())
	{
		MessageBox(_T("��ʼ��excelʧ��"));
		return;
	}
	if (excel.Open(_T("E:\\test_by.xlsx")))
	{
		excel.SaveAsPDF(_T("E:\\test_by.pdf"));
	}
	excel.Close();
// 	if (excel.Open(_T("E:\\test.xlsx")))
// 	{
// 		excel.Test();
// 	}
	m_buttonControl.EnableWindow(TRUE);
}
