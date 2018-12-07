#pragma once

#include "CApplication.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include "CWorkbook.h"
#include "CWorksheet.h"
#include "CRange.h"


class ExcelManager
{
public:
	ExcelManager(void);
	~ExcelManager(void);
	
	//************************************************************************
	// Method:		Close
	// Returns:		void
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	void Close();
	
	//************************************************************************
	// Method:		Init
	// Returns:		bool
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool Init();
	
	//************************************************************************
	// Method:		IsFileExist		判断文件或文件夹是否存在
	// Returns:		bool
	// Parameter:	const CString & fileName	文件路径名
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool IsFileExist(const CString &fileName);
	
	//************************************************************************
	// Method:		IsRegionEqual	判断单元格区域是否与二维数组区域大小相同
	// Returns:		bool
	// Parameter:	CRange & iRange		单元格区域
	// Parameter:	COleSafeArray & iTwoDimArray	二维数组
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool IsRegionEqual(CRange &iRange,COleSafeArray &iTwoDimArray);
	
	//************************************************************************
	// Method:		Open	打开文件
	// Returns:		bool
	// Parameter:	const CString & iFileName	文件路径名
	// Parameter:	bool autoCreate		打开模式，默认文件不存在不自动创建
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool Open(const CString &iFileName, bool autoCreate = false);
	
	//************************************************************************
	// Method:		OpenFromTemplate	根据模板创建新文件
	// Returns:		bool
	// Parameter:	const CString & iFileName	模板文件路径名	
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool OpenFromTemplate(const CString &iFileName);
	
	//************************************************************************
	// Method:		Save	保存文件，OpenFromTemplate创建的文件不能使用该方法保存
	// Returns:		void
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool Save();
	
	//************************************************************************
	// Method:		SaveAs	另存为
	// Returns:		bool
	// Parameter:	const CString & iFileName	文件路径名
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SaveAs(const CString &iFileName);
	
	//************************************************************************
	// Method:		SaveAsPDF	另存为PDF文件
	// Returns:		bool
	// Parameter:	const CString & iFileName	文件路径名
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SaveAsPDF(const CString &iFileName);
	
	//************************************************************************
	// Method:		SetCellsValue	批量写入多个单元格数据
	// Returns:		bool
	// Parameter:	COleVariant startCell	起始单元格(左上角单元格),例如:"B5"
	// Parameter:	COleVariant endCell		起始单元格(左上角单元格),例如:"C7"
	// Parameter:	COleSafeArray & iTwoDimArray	二维数组(要写入的数据)
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SetCellsValue(COleVariant startCell,COleVariant endCell,
		COleSafeArray &iTwoDimArray);
	
	//************************************************************************
	// Method:		SetCellValue	写入单个单元格数据
	// Returns:		bool
	// Parameter:	COleVariant rowIndex		单元格行号,例如:"8"
	// Parameter:	COleVariant columnIndex		单元格列号,例如:"C"
	// Parameter:	COleVariant data			要写入的数据
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SetCellValue(COleVariant rowIndex, COleVariant columnIndex,COleVariant data);
	
	//************************************************************************
	// Method:		SwitchWorksheet		切换sheet
	// Returns:		bool
	// Parameter:	const CString & sheetName	sheet名称
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SwitchWorksheet(const CString &sheetName);

	void Test();
	void Test1();
public://not use
	//此处暂时不用，若需要的功能该类未封装，可使用以下函数获取book、sheet自定义操作

	CRange *GetRange();
	CWorkbook *GetWorkbook();
	CWorkbooks *GetWorkbooks();
	CWorksheet *GetWorksheet();
	CWorksheets *GetWorksheets();

private:
	CApplication	m_app;
	CRange			m_range;
	CWorkbook		m_workbook;
	CWorkbooks		m_workbooks;
	CWorksheet		m_worksheet;
	CWorksheets		m_worksheets;

	COleVariant		covTrue;
	COleVariant		covFalse;
	COleVariant		covOptional;
};
