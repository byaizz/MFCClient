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
	if (AfxOleGetMessageFilter() == NULL)//����Ƿ��ʼ��OLE
	{
		if (!AfxOleInit())//��ʼ��OLE
		{
			MessageBox(NULL,_T("��ʼ��OLEʧ��."),_T("tip"),MB_OK);
			return false;
		}
	}

	if (!app.CreateDispatch(_T("Excel.Application")))//����Excel����
	{
		MessageBox(NULL,_T("����Excel����ʧ��."),_T("tip"),MB_OK);
		return false;
	}

	app.put_Visible(FALSE);//Ĭ�ϲ���ʾexcel���
}

bool MyExcel::SaveAsPDF(const CString &iFileName)
{
	long type = 0;//����0Ϊ.pdf������1Ϊ.xps
	workbook.ExportAsFixedFormat(type,COleVariant(_T("E:\\test_by.pdf")),covOptional,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional);
	return true;
}
