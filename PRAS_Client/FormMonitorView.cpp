// FormMonitorView.cpp : 实现文件
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


// CFormMonitorView 诊断

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


// CFormMonitorView 消息处理程序

void CFormMonitorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//设置表格属性
 	m_GridSlabInfo.SetListMode(TRUE);//设置是否为排序模式
	m_GridSlabInfo.SetGridColor(RGB(255,255,255));//设置网格线颜色
	m_GridSlabInfo.SetTextBkColor(RGB(128,255,255));//设置表格背景颜色
	m_GridSlabInfo.SetTextColor(RGB(238,44,44));//设置文字颜色
	m_GridSlabInfo.SetModified(FALSE);//设置是否可修改
	m_GridSlabInfo.EnableSelection(FALSE);//设置是否可选择
	m_GridSlabInfo.SetBkColor(RGB(255,255,255));//设置背景颜色(表格之外的颜色)

	//设置表格行列数
	int rowCount = 6;
	int colCount = 6;
	m_GridSlabInfo.SetRowCount(rowCount);//设置行数
 	m_GridSlabInfo.SetColumnCount(colCount);//设置列数
	m_GridSlabInfo.SetFixedRowCount(1);//设置固定行数
	m_GridSlabInfo.SetFixedColumnCount(1);//设置固定列数
	m_GridSlabInfo.SetEditable(FALSE);//设置是否可编辑
	m_GridSlabInfo.ShowScrollBar(SB_BOTH, FALSE);//设置是否显示滚动条
	m_GridSlabInfo.SetRowBkColour(2,RGB(0,255,0));//设置整行颜色

	for (int i = 0; i < rowCount; ++i)
	{
		GV_ITEM item;
		item.mask = GVIF_TEXT | GVIF_FORMAT;
		item.row = i;
		item.nFormat = DT_LEFT | DT_SINGLELINE | DT_END_ELLIPSIS;
		for (int j = 0; j < colCount; ++j)
		{
			item.col = j;
			item.szText.Format(_T("%d行%d列"), i+1, j+1);
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
	// TODO: 在此添加控件通知处理程序代码
	ExcelManager excel;
	if (!excel.Init())
	{
		MessageBox(_T("初始化excel失败"));
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
