// FormMonitorView.cpp : ʵ���ļ�
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
		item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
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

	//����toolTips
	EnableToolTips(TRUE);//enable
	m_toolTips.Create(this);
	m_toolTips.Activate(TRUE);
	m_toolTips.SetTipTextColor(RGB(0,255,0));//font color
	m_toolTips.SetDelayTime(100);//delay time
	m_toolTips.SetDelayTime(TTDT_AUTOPOP,20000);//set duration
	//����һΪ���������ʾ�Ŀؼ�IDC(����Ӷ��)��������Ϊ����ӵ���ʾ���
	m_toolTips.AddTool(GetDlgItem(IDC_CUSTOM_GRID_SLAB),_T("��ʾ��Ϣ"));

}

BOOL CFormMonitorView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: �ڴ����ר�ô����/����û���
	NM_GRIDVIEW		*pGridInfo;		//�����Ϣ
	if (IDC_CUSTOM_GRID_SLAB == wParam)
	{
		pGridInfo = (NM_GRIDVIEW *)lParam;
		if (NM_DBLCLK == pGridInfo->hdr.code
			|| WM_RBUTTONDOWN == pGridInfo->hdr.code)
		{
			//MessageBox(_T("���˵���"));
			CPoint	point;
			CMenu	MenuRight;	//�Ҽ��˵�
			CMenu	*pMenuPop;	//�����˵�
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
	// TODO: �ڴ���������������
	CTest test;
	test.DoModal();
}

BOOL CFormMonitorView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_toolTips.RelayEvent(pMsg);

		CCellID idCurrentCell;
		idCurrentCell.row = -1;
		idCurrentCell.col = -1;
		m_GridSlabInfo.GetCellPoint(idCurrentCell);
		//������ƶ�����һ����Ԫ��ʱ
		if (idLastCell.row != idCurrentCell.row
			|| idLastCell.col != idCurrentCell.col)
		{
			idLastCell.row = idCurrentCell.row;
			idLastCell.col = idCurrentCell.col;
			if (idCurrentCell.row >= 0 && idCurrentCell.col >= 0
				&&idCurrentCell.row < m_GridSlabInfo.GetRowCount()
				&&idCurrentCell.col < m_GridSlabInfo.GetColumnCount())
			{
				//����tips����
				CString str;
				str.Format(_T("%d ��,%d ��"),idCurrentCell.row,idCurrentCell.col);
				m_toolTips.Activate(TRUE);
				m_toolTips.UpdateTipText(str,GetDlgItem(IDC_CUSTOM_GRID_SLAB));
			}
			else
			{
				m_toolTips.Activate(FALSE);//���֮�ⲻ��ʾtips
			}
		}
	}

	return CFormView::PreTranslateMessage(pMsg);
}
