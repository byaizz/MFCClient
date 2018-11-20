#pragma once

#include "CApplication.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include "CWorkbook.h"
#include "CWorksheet.h"
#include "CRange.h"


class MyExcel
{
public:
	MyExcel(void);
public:
	~MyExcel(void);
	bool Open(const CString &iFileName);
	void Close();
	bool Init();
	bool SaveAsPDF(const CString &iFileName);
private:
	CApplication	app;
	CWorkbooks		workbooks;
	CWorkbook		workbook;
	CWorksheets		worksheets;
	CWorksheet		worksheet;

	COleVariant		covTrue;
	COleVariant		covFalse;
	COleVariant		covOptional;
};
