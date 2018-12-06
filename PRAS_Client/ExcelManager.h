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
	bool Open(const CString &iFileName, bool autoCreate = false);//���ļ�,Ĭ���ļ������ڲ��Զ�����
	bool OpenFromTemplate(const CString &iFileName);//����ģ���½��ļ�
	void Save();//OpenFromTemplate�������ļ�����ʹ�ø÷�������
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
