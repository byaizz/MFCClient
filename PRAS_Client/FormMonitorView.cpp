// FormMonitorView.cpp : 实现文件
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "FormMonitorView.h"

#include "Test.h"


// CFormMonitorView

IMPLEMENT_DYNCREATE(CFormMonitorView, CFormView)

CFormMonitorView::CFormMonitorView()
	: CFormView(CFormMonitorView::IDD)
{
	idLastCell.row = -1;
	idLastCell.col = -1;
}

CFormMonitorView::~CFormMonitorView()
{
}

void CFormMonitorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_CUSTOM_GRID_SLAB, m_GridSlabInfo);
}

BEGIN_MESSAGE_MAP(CFormMonitorView, CFormView)
	ON_COMMAND(ID_EXCEL_EXCEL2, &CFormMonitorView::OnExcelExcel2)
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
		item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
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

	//创建toolTips
	EnableToolTips(TRUE);//enable
	m_toolTips.Create(this);
	m_toolTips.Activate(TRUE);
	m_toolTips.SetTipTextColor(RGB(0,255,0));//font color
	m_toolTips.SetDelayTime(100);//delay time
	m_toolTips.SetDelayTime(TTDT_AUTOPOP,20000);//set duration
	//参数一为你想添加提示的控件IDC(可添加多个)，参数二为想添加的提示语句
	m_toolTips.AddTool(GetDlgItem(IDC_CUSTOM_GRID_SLAB),_T("提示信息"));

}

BOOL CFormMonitorView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类
	NM_GRIDVIEW		*pGridInfo;		//表格信息
	if (IDC_CUSTOM_GRID_SLAB == wParam)
	{
		pGridInfo = (NM_GRIDVIEW *)lParam;
		if (NM_DBLCLK == pGridInfo->hdr.code
			|| WM_RBUTTONDOWN == pGridInfo->hdr.code)
		{
			//MessageBox(_T("有人点我"));
			CPoint	point;
			CMenu	MenuRight;	//右键菜单
			CMenu	*pMenuPop;	//弹出菜单
			if (MenuRight.LoadMenu(IDR_MENU_GRID_CTRL))
			{
 				pMenuPop = MenuRight.GetSubMenu(0);
 				//int iCount = pMenuPop->GetMenuItemCount();
 				//pMenuPop->EnableMenuItem(IDR_MENU_GRID_CTRL,MF_BYCOMMAND|MF_ENABLED);
 				GetCursorPos(&point);
 				pMenuPop->TrackPopupMenu(TPM_LEFTALIGN/*|TPM_RIGHTBUTTON*/,point.x,point.y,this);
			}
		}
	}
	
	return CFormView::OnNotify(wParam, lParam, pResult);
}

void CFormMonitorView::OnExcelExcel2()
{
	// TODO: 在此添加命令处理程序代码
	CTest test;
	test.DoModal();
}

BOOL CFormMonitorView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_toolTips.RelayEvent(pMsg);

		CCellID idCurrentCell;
		idCurrentCell.row = -1;
		idCurrentCell.col = -1;
		m_GridSlabInfo.GetCellPoint(idCurrentCell);
		//当鼠标移动到另一个单元格时
		if (idLastCell.row != idCurrentCell.row
			|| idLastCell.col != idCurrentCell.col)
		{
			idLastCell.row = idCurrentCell.row;
			idLastCell.col = idCurrentCell.col;
			if (idCurrentCell.row >= 0 && idCurrentCell.col >= 0
				&&idCurrentCell.row < m_GridSlabInfo.GetRowCount()
				&&idCurrentCell.col < m_GridSlabInfo.GetColumnCount())
			{
				//设置tips内容
				CString str;
				str.Format(_T("%d 行,%d 列"),idCurrentCell.row,idCurrentCell.col);
				m_toolTips.Activate(TRUE);
				m_toolTips.UpdateTipText(str,GetDlgItem(IDC_CUSTOM_GRID_SLAB));
			}
			else
			{
				m_toolTips.Activate(FALSE);//表格之外不显示tips
			}
		}
	}

	return CFormView::PreTranslateMessage(pMsg);
}
