#include "StdAfx.h"
#include "MyExcel.h"

MyExcel::MyExcel(void)
:covTrue((short)TRUE)
,covFalse((short)FALSE)
,covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR)
{
}

MyExcel::~MyExcel(void)
{
}

bool MyExcel::Open(const CString &iFileName)
{
	workbooks.AttachDispatch(app.get_Workbooks());
	workbook.AttachDispatch(workbooks.Add(COleVariant(iFileName)));//_T("E:\\test_by.xlsx")
	worksheets.AttachDispatch(workbook.get_Sheets());
	worksheet.AttachDispatch(workbook.get_ActiveSheet());

	return true;
}

void MyExcel::Close()
{
	workbooks.Close();
	app.Quit();
}

bool MyExcel::Init()
{
	if (AfxOleGetMessageFilter() == NULL)//检查是否初始化OLE
	{
		if (!AfxOleInit())//初始化OLE
		{
			MessageBox(NULL,_T("初始化OLE失败."),_T("tip"),MB_OK);
			return false;
		}
	}

	if (!app.CreateDispatch(_T("Excel.Application")))//创建Excel服务
	{
		MessageBox(NULL,_T("创建Excel服务失败."),_T("tip"),MB_OK);
		return false;
	}

	app.put_Visible(FALSE);//默认不显示excel表格
}

bool MyExcel::SaveAsPDF(const CString &iFileName)
{
	long type = 0;//参数0为.pdf，参数1为.xps
	workbook.ExportAsFixedFormat(type,COleVariant(_T("E:\\test_by.pdf")),covOptional,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional);
	return true;
}
