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
	void ExcelOperation();
private:
	CApplication	app;
	CWorkbooks		workbooks;
	CWorkbook		workbook;
	CWorksheets		worksheets;
	CWorksheet		worksheet;
	CRange			range;

};
