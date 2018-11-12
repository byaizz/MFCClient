#include "StdAfx.h"
#include "MyExcel.h"

MyExcel::MyExcel(void)
{
}

MyExcel::~MyExcel(void)
{
}

void MyExcel::ExcelOperation()
{
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		MessageBox(NULL,_T("创建Excel服务失败."),_T("error"),MB_OK);
		return;
	}
	COleVariant
		covTrue((short)TRUE),
		covFalse((short)FALSE),
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	workbooks.AttachDispatch(app.get_Workbooks());

	LPDISPATCH lpDis = NULL;
	lpDis = workbooks.Add(COleVariant(_T("E:\\test_by.xlsx")));
	if (lpDis != NULL)
	{
		workbook.AttachDispatch(lpDis);
		workbook.ExportAsFixedFormat(0,COleVariant(_T("E:\\test_by.pdf")),covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
	}


	workbook.Close(covFalse,COleVariant(_T("E:\\test_by.xlsx")),covOptional);
	workbooks.Close();

	worksheet.ReleaseDispatch();
	worksheets.ReleaseDispatch();
	range.ReleaseDispatch();
	workbook.ReleaseDispatch();
	workbooks.ReleaseDispatch();
	app.ReleaseDispatch();

	app.Quit();
}
