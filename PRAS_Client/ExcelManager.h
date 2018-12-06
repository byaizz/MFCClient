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
	void Close();
	CWorksheet *GetActiveWorksheet();
	CWorkbook *GetWorkbook();
	CWorkbooks *GetWorkbooks();
	CWorksheet *GetWorksheet(const CString &sheetName);
	CWorksheets *GetWorksheets();
	CRange *GetRange();

	bool Init();
	bool IsFileExist(const CString &fileName);
	bool Open(const CString &iFileName, bool autoCreate = false);//打开文件,默认文件不存在不自动创建
	bool OpenFromTemplate(const CString &iFileName);//打开以模板新建文件
	void Save();//OpenFromTemplate创建的文件不能使用该方法保存
	bool SaveAs(const CString &iFileName);
	bool SaveAsPDF(const CString &iFileName);
	void Test();
private:
	CApplication	app;
	CWorkbooks		workbooks;
	CWorkbook		workbook;
	CWorksheets		worksheets;
	CWorksheet		worksheet;
	CRange			range;

	COleVariant		covTrue;
	COleVariant		covFalse;
	COleVariant		covOptional;
};
