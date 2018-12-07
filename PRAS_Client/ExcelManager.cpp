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
	m_workbook.Close(covFalse,covOptional,covOptional);//默认不保存更改
	m_workbooks.Close();
	m_range.ReleaseDispatch();
 	m_worksheet.ReleaseDispatch();
 	m_worksheets.ReleaseDispatch();
 	m_workbook.ReleaseDispatch();
 	m_workbooks.ReleaseDispatch();
	m_app.Quit();
	m_app.ReleaseDispatch();
}

bool ExcelManager::Init()
{
	if (AfxOleGetMessageFilter() == NULL)//检查是否初始化OLE
	{
		if (!AfxOleInit())//初始化OLE
		{
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

bool ExcelManager::IsRegionEqual(CRange &iRange,COleSafeArray &iTwoDimArray)
{
	if ( iTwoDimArray.GetDim() != 2)//数组维数判断
	{
		return false;//数组非二维数组
	}

	//获取二维数组行数和列数
	long firstLBound = 0;//第一维左边界
	long fristUBound = 0;//第一维右边界
	long secondLBound = 0;//第二维左边界
	long secondUBound = 0;//第二维右边界
	long row1 = 0;//行数
	long column1 = 0;//列数
	iTwoDimArray.GetLBound(1,&firstLBound);
	iTwoDimArray.GetUBound(1,&fristUBound);
	iTwoDimArray.GetLBound(2,&secondLBound);
	iTwoDimArray.GetUBound(2,&secondUBound);
	row1 = fristUBound - firstLBound + 1;
	column1 = secondUBound - secondLBound + 1;

	//获取表格区域行数和列数
	CRange range;
	range.AttachDispatch(iRange.get_Rows());
	long row2 = range.get_Count();//获取行数
	range.AttachDispatch(iRange.get_Columns());
	long column2 = range.get_Count();//获取列数
	if (row1 != row2 || column1 != column2)
	{
		return false;//区域大小不一致
	}
	return true;
}

bool ExcelManager::Open(const CString &iFileName, bool autoCreate)
{
	try
	{
		if (!m_app.CreateDispatch(_T("Excel.Application")))//创建Excel服务
		{
			MessageBox(NULL,_T("创建Excel服务失败."),_T("警告"),MB_OK);
			return false;
		}
		m_app.put_Visible(FALSE);//默认不显示excel表格

		m_workbooks.AttachDispatch(m_app.get_Workbooks());
		if (IsFileExist(iFileName))
		{
			m_workbook.AttachDispatch(m_workbooks.Open(iFileName,vtMissing,vtMissing,
				vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,
				vtMissing,vtMissing,vtMissing,vtMissing,vtMissing));//获取workbook
		}
		else if (autoCreate)
		{
			m_workbook.AttachDispatch(m_workbooks.Add(COleVariant(covOptional)));//获取workbook
			SaveAs(iFileName);//创建新文件
		}
		else
		{
			MessageBox(NULL,_T("excel文件不存在"),_T("警告"),MB_OK);
			return false;
		}
		m_worksheets.AttachDispatch(m_workbook.get_Sheets());//获取所有sheet
		m_worksheet.AttachDispatch(m_workbook.get_ActiveSheet());//获取当前活动sheet
	}
	catch (CException* e)
	{
		MessageBox(NULL,_T("excel文件打开异常"),_T("警告"),MB_OK);
		return false;
	}
	return true;
}

bool ExcelManager::OpenFromTemplate(const CString &iFileName)
{
	try
	{
		if (!m_app.CreateDispatch(_T("Excel.Application")))//创建Excel服务
		{
			MessageBox(NULL,_T("创建Excel服务失败."),_T("警告"),MB_OK);
			return false;
		}
		m_app.put_Visible(FALSE);//默认不显示excel表格

		if (!IsFileExist(iFileName))
		{
			MessageBox(NULL,_T("excel文件不存在"),_T("警告"),MB_OK);
			return false;
		}
		m_workbooks.AttachDispatch(m_app.get_Workbooks());
		//以路径指出的文件为模板创建excel
		m_workbook.AttachDispatch(m_workbooks.Add(COleVariant(iFileName)));//获取workbook
		m_worksheets.AttachDispatch(m_workbook.get_Sheets());//获取所有sheet
		m_worksheet.AttachDispatch(m_workbook.get_ActiveSheet());//获取当前活动sheet
	}
	catch (CException* e)
	{
		MessageBox(NULL,_T("excel文件打开异常"),_T("警告"),MB_OK);
		return false;
	}
	
	return true;
}

bool ExcelManager::Save()
{
	try
	{
		m_workbook.Save();
	}
	catch (CException* e)
	{
		return false;
	}
	return true;
}

bool ExcelManager::SaveAs(const CString &iFileName)
{
	try
	{
		long acessMode = 1;//默认值（不更改访问模式）
		m_workbook.SaveAs(COleVariant(iFileName),covOptional,covOptional,covOptional,covOptional,covOptional
			,acessMode,covOptional,covOptional,covOptional,covOptional,covOptional);
	}
	catch (CException* e)
	{
		return false ;
	}
	return true;
}

bool ExcelManager::SaveAsPDF(const CString &iFileName)
{
	try
	{
		long type = 0;//参数0为.pdf，参数1为.xps
		m_workbook.ExportAsFixedFormat(type,COleVariant(iFileName),covOptional,covOptional,
			covOptional,covOptional,covOptional,covOptional,covOptional);
	}
	catch (CException* e)
	{
		return false;
	}
	return true;
}

bool ExcelManager::SetCellsValue(COleVariant startCell,COleVariant endCell,COleSafeArray &iTwoDimArray)
{
	try
	{
		m_range.AttachDispatch(m_worksheet.get_Range(COleVariant(startCell),COleVariant(endCell)));
		if (!IsRegionEqual(m_range,iTwoDimArray))
		{
			return false;
		}
		m_range.put_Value2(iTwoDimArray);
	}
	catch (CException* e)
	{
		return false;
	}
	return true;
}

bool ExcelManager::SetCellValue(COleVariant rowIndex, COleVariant columnIndex,COleVariant data)
{
	try
	{
		m_range.AttachDispatch(m_worksheet.get_Cells());
		m_range.put_Item(rowIndex,columnIndex,data);
	}
	catch (CException* e)
	{
		return false;
	}
	return true;
}

bool ExcelManager::SwitchWorksheet(const CString &sheetName)
{
	try
	{
		m_worksheet.AttachDispatch(m_worksheets.get_Item(COleVariant(sheetName)));//获取sheet
	}
	catch (CException* e)
	{
		return NULL;
	}
	return &m_worksheet;
}

void ExcelManager::Test()
{
	m_range.AttachDispatch(m_worksheet.get_Range(COleVariant(_T("A1")),COleVariant(_T("C5"))));
	VARIANT result;
	result = m_range.get_Value2();
	COleSafeArray oleArray(result);
	long row;
	long column;
	oleArray.GetLBound(1,&row);
	oleArray.GetLBound(2,&column);
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
	Save();
}


void ExcelManager::Test1()
{
	COleSafeArray safeArray;
	DWORD numElements[2] = {5, 10};

	safeArray.Create(VT_BSTR, 2, numElements);
	long firstLBound = 0;
	safeArray.GetLBound(1,&firstLBound);
	long firstUBound = 0;
	safeArray.GetUBound(1,&firstUBound);
	long secondLBound = 0;
	safeArray.GetLBound(2,&secondLBound);
	long secondUBound = 0;
	safeArray.GetUBound(2,&secondUBound);

	long index[2] = {0,0};
	for (long i = firstLBound; i <= firstUBound; ++i)
	{
		index[0] = i;
		for (long j = secondLBound; j <= secondUBound; ++j)
		{
			index[1] = j;
			CString str;
			str.Format(_T("%d行%d列"),i,j);
			VARIANT var = COleVariant(str);
			safeArray.PutElement(index,var.bstrVal);
			// 			long lElement= (i+1) * (j+1); 
			// 			safeArray.PutElement(index, &lElement);
		}
	}

	//SetCellsValue(_T("D5"),_T("M9"),safeArray);
	SetCellValue(_T("1"),_T("A"),100.02121123131131313131313133666);

	Save();
}


CRange * ExcelManager::GetRange()
{
	return &m_range;
}

CWorkbook * ExcelManager::GetWorkbook()
{
	return &m_workbook;
}

CWorkbooks * ExcelManager::GetWorkbooks()
{
	return &m_workbooks;
}

CWorksheet * ExcelManager::GetWorksheet()
{
	return &m_worksheet;
}

CWorksheets * ExcelManager::GetWorksheets()
{
	return &m_worksheets;
}
