#include "StdAfx.h"
#include "ExcelManager.h"
#include <fstream>
#include <comdef.h>

ExcelManager::ExcelManager(void)
:covTrue((short)TRUE)
,covFalse((short)FALSE)
,covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR)
{
}

ExcelManager::~ExcelManager(void)
{
	Close();
}

void ExcelManager::Close()
{
	workbooks.Close();
	app.Quit();
 	worksheet.ReleaseDispatch();
 	worksheets.ReleaseDispatch();
 	workbook.ReleaseDispatch();
 	workbooks.ReleaseDispatch();
	app.ReleaseDispatch();
}

CWorksheet * ExcelManager::GetActiveWorksheet()
{
	worksheet.AttachDispatch(workbook.get_ActiveSheet());//获取当前活动sheet
	return &worksheet;
}

CWorkbook * ExcelManager::GetWorkbook()
{
	return &workbook;
}

CWorkbooks * ExcelManager::GetWorkbooks()
{
	return &workbooks;
}

CWorksheet * ExcelManager::GetWorksheet(const CString &sheetName)
{
	try
	{
		worksheet.AttachDispatch(worksheets.get_Item(COleVariant(sheetName)));//获取sheet
	}
	catch (CException* e)
	{
		MessageBox(NULL,_T("获取sheet失败"),_T("警告"),MB_OK);
		return NULL;
	}
	return &worksheet;
}

CWorksheets * ExcelManager::GetWorksheets()
{
	return &worksheets;
}

CRange * ExcelManager::GetRange()
{
	return &range;
}

bool ExcelManager::Init()
{
	if (AfxOleGetMessageFilter() == NULL)//检查是否初始化OLE
	{
		if (!AfxOleInit())//初始化OLE
		{
			MessageBox(NULL,_T("初始化OLE失败."),_T("警告"),MB_OK);
			return false;
		}
	}
	return true;
}

bool ExcelManager::IsFileExist(const CString &fileName)
{
	DWORD dwAttrib = GetFileAttributes(fileName);
	return INVALID_FILE_ATTRIBUTES != dwAttrib;
}

bool ExcelManager::Open(const CString &iFileName, bool autoCreate)
{
	try
	{
		if (!app.CreateDispatch(_T("Excel.Application")))//创建Excel服务
		{
			MessageBox(NULL,_T("创建Excel服务失败."),_T("警告"),MB_OK);
			return false;
		}
		app.put_Visible(FALSE);//默认不显示excel表格

		workbooks.AttachDispatch(app.get_Workbooks());
		if (IsFileExist(iFileName))
		{
			workbook.AttachDispatch(workbooks.Open(iFileName,vtMissing,vtMissing,
				vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,
				vtMissing,vtMissing,vtMissing,vtMissing,vtMissing));//获取workbook
		}
		else if (autoCreate)
		{
			workbook.AttachDispatch(workbooks.Add(COleVariant(covOptional)));//获取workbook
			SaveAs(iFileName);//创建新文件
		}
		else
		{
			MessageBox(NULL,_T("excel文件不存在，打开失败"),_T("警告"),MB_OK);
			return false;
		}
		worksheets.AttachDispatch(workbook.get_Sheets());//获取所有sheet
	}
	catch (CException* e)
	{
		MessageBox(NULL,_T("excel文件打开失败"),_T("警告"),MB_OK);
		return false;
	}
	return true;
}

bool ExcelManager::OpenFromTemplate(const CString &iFileName)
{
	try
	{
		if (!app.CreateDispatch(_T("Excel.Application")))//创建Excel服务
		{
			MessageBox(NULL,_T("创建Excel服务失败."),_T("警告"),MB_OK);
			return false;
		}
		app.put_Visible(FALSE);//默认不显示excel表格

		if (!IsFileExist(iFileName))
		{
			MessageBox(NULL,_T("文件不存在"),_T("警告"),MB_OK);
			return false;
		}
		workbooks.AttachDispatch(app.get_Workbooks());
		//以路径指出的文件为模板创建excel
		workbook.AttachDispatch(workbooks.Add(COleVariant(iFileName)));//获取workbook
		worksheets.AttachDispatch(workbook.get_Sheets());//获取所有sheet
	}
	catch (CException* e)
	{
		MessageBox(NULL,_T("excel文件创建失败"),_T("警告"),MB_OK);
		return false;
	}
	
	return true;
}

void ExcelManager::Save()
{
	workbook.Save();
}

void ExcelManager::SaveAs(const CString &iFileName)
{
	long acessMode = 1;//默认值（不更改访问模式）
	workbook.SaveAs(COleVariant(iFileName),covOptional,covOptional,covOptional,covOptional,covOptional
		,acessMode,covOptional,covOptional,covOptional,covOptional,covOptional);
}

void ExcelManager::SaveAsPDF(const CString &iFileName)
{
	long type = 0;//参数0为.pdf，参数1为.xps
	workbook.ExportAsFixedFormat(type,COleVariant(iFileName),covOptional,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional);
}

void ExcelManager::Test()
{
	range.AttachDispatch(worksheet.get_Range(COleVariant(_T("A1")),COleVariant(_T("C5"))));
	VARIANT result;
	result = range.get_Value2();
	COleSafeArray oleArray(result);
	long row;
	long column;
	oleArray.GetUBound(1,&row);
	oleArray.GetUBound(2,&column);
	std::fstream fs;
	fs.open("E:\\test.txt",std::ios::out);
	if (!fs)
	{
		return;
	}
	long index[2];
	VARIANT val;
	for (int i = 1; i <= row; ++i)
	{
		index[0] = i;
		for (int j = 1; j <= column; ++j)
		{
			index[1] = j;
			oleArray.GetElement(index,&val);
			
			if (val.vt == VT_R8)
			{
				fs<<val.dblVal<<"\t";
			}else if (val.vt == VT_BSTR)
			{
				CString str(val.bstrVal);
				fs<<CStringA(val.bstrVal)<<std::endl;
			}else
			{
				int a = 1;
			}
		}
	}
	
}
