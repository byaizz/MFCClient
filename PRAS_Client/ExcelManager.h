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
	// Method:		IsFileExist		�ж��ļ����ļ����Ƿ����
	// Returns:		bool
	// Parameter:	const CString & fileName	�ļ�·����
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool IsFileExist(const CString &fileName);
	
	//************************************************************************
	// Method:		IsRegionEqual	�жϵ�Ԫ�������Ƿ����ά���������С��ͬ
	// Returns:		bool
	// Parameter:	CRange & iRange		��Ԫ������
	// Parameter:	COleSafeArray & iTwoDimArray	��ά����
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool IsRegionEqual(CRange &iRange,COleSafeArray &iTwoDimArray);
	
	//************************************************************************
	// Method:		Open	���ļ�
	// Returns:		bool
	// Parameter:	const CString & iFileName	�ļ�·����
	// Parameter:	bool autoCreate		��ģʽ��Ĭ���ļ������ڲ��Զ�����
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool Open(const CString &iFileName, bool autoCreate = false);
	
	//************************************************************************
	// Method:		OpenFromTemplate	����ģ�崴�����ļ�
	// Returns:		bool
	// Parameter:	const CString & iFileName	ģ���ļ�·����	
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool OpenFromTemplate(const CString &iFileName);
	
	//************************************************************************
	// Method:		Save	�����ļ���OpenFromTemplate�������ļ�����ʹ�ø÷�������
	// Returns:		void
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool Save();
	
	//************************************************************************
	// Method:		SaveAs	���Ϊ
	// Returns:		bool
	// Parameter:	const CString & iFileName	�ļ�·����
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SaveAs(const CString &iFileName);
	
	//************************************************************************
	// Method:		SaveAsPDF	���ΪPDF�ļ�
	// Returns:		bool
	// Parameter:	const CString & iFileName	�ļ�·����
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SaveAsPDF(const CString &iFileName);
	
	//************************************************************************
	// Method:		SetCellsValue	����д������Ԫ������
	// Returns:		bool
	// Parameter:	COleVariant startCell	��ʼ��Ԫ��(���Ͻǵ�Ԫ��),����:"B5"
	// Parameter:	COleVariant endCell		��ʼ��Ԫ��(���Ͻǵ�Ԫ��),����:"C7"
	// Parameter:	COleSafeArray & iTwoDimArray	��ά����(Ҫд�������)
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SetCellsValue(COleVariant startCell,COleVariant endCell,
		COleSafeArray &iTwoDimArray);
	
	//************************************************************************
	// Method:		SetCellValue	д�뵥����Ԫ������
	// Returns:		bool
	// Parameter:	COleVariant rowIndex		��Ԫ���к�,����:"8"
	// Parameter:	COleVariant columnIndex		��Ԫ���к�,����:"C"
	// Parameter:	COleVariant data			Ҫд�������
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SetCellValue(COleVariant rowIndex, COleVariant columnIndex,COleVariant data);
	
	//************************************************************************
	// Method:		SwitchWorksheet		�л�sheet
	// Returns:		bool
	// Parameter:	const CString & sheetName	sheet����
	// Author:		byshi
	// Date:		2018-12-7	
	//************************************************************************
	bool SwitchWorksheet(const CString &sheetName);

	void Test();
	void Test1();
public://not use
	//�˴���ʱ���ã�����Ҫ�Ĺ��ܸ���δ��װ����ʹ�����º�����ȡbook��sheet�Զ������

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
