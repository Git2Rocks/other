#include "excelobject.h"
#include "qt_windows.h"
#include <odbcinst.h>

int ExportExcelObject::export2Excel()
{
	isCancel = FALSE;
    if(fieldList.size() <= 0)
    {
        qDebug() << "ExportExcelObject::export2Excel failed: No fields defined.";
        return -1;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "excelexport");
    if(!db.isValid())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: QODBC not supported.";
        return -2;
    }
    // set the dsn string
    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").
                  arg(excelFilePath).arg(excelFilePath);
    db.setDatabaseName(dsn);
    if(!db.open())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: Create Excel file failed by DRIVER={Microsoft Excel Driver (*.xls)}.";
        //QSqlDatabase::removeDatabase("excelexport");
        return -3;
    }
	
    QSqlQuery query(db);

    //drop the table if it's already exists
    QString s, sSql = QString("DROP TABLE [%1] (").arg(sheetName);
    query.exec(sSql);

    //create the table (sheet in Excel file)
    sSql = QString("CREATE TABLE [%1] (").arg(sheetName);
    for (int i = 0; i < fieldList.size(); i++)
    {
        s = QString("[%1] %2").arg(fieldList.at(i)->sFieldName).arg(fieldList.at(i)->sFieldType);
        sSql += s;
        if(i < fieldList.size() - 1)
            sSql += " , ";
    }

    sSql += ")";
    query.prepare(sSql);

    if(!query.exec())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: Create Excel sheet failed.";
        //db.close();
        //QSqlDatabase::removeDatabase("excelexport");
        return -4;
    }

    //add all rows
    sSql = QString("INSERT INTO [%1] (").arg(sheetName);
    for (int i = 0; i < fieldList.size(); i++)
    {
        sSql += fieldList.at(i)->sFieldName;
        if(i < fieldList.size() - 1)
            sSql += " , ";
    }
    sSql += ") VALUES (";
    for (int i = 0; i < fieldList.size(); i++)
    {
        sSql += QString(":data%1").arg(i);
        if(i < fieldList.size() - 1)
            sSql += " , ";
    }
    sSql += ")";

    qDebug() << sSql;

    int r, iRet = 0;
    for(r = 0 ; r < tableView->model()->rowCount() ; r++)
    {
        query.prepare(sSql);
        for (int c = 0; c < fieldList.size(); c++)
        {
			query.bindValue(QString(":data%1").arg(c),tableView->model()->data(tableView->model()->index(r, fieldList.at(c)->iCol)));
        }

        if(query.exec())
            iRet++;

        if(r % 10 == 0)
            emit exportedRowCount(r);

		if(isCancel)
			break;
    }

    emit exportedRowCount(r);
    return iRet;
}
int ExportExcelObject::readExcelData()
{
// 	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "excel");
// 	if(!db.isValid())
// 	{
// 		qDebug() << "ExportExcelObject::export2Excel failed: QODBC not supported.";
// 		return -2;
// 	}
// 	// set the dsn string
// 	QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=TRUE;DBQ=%2").
// 		arg(excelFilePath).arg(excelFilePath);
// 	db.setDatabaseName(dsn);
// 	if(!db.open())
// 	{
// 		qDebug() << "ExportExcelObject::export2Excel failed: Create Excel file failed by DRIVER={Microsoft Excel Driver (*.xls)}.";
// 		//QSqlDatabase::removeDatabase("excelexport");
// 		return -3;
// 	}
// 
// 	QSqlQuery query(db);
// 
// 	QString sql_str = QString::fromLocal8Bit("select * from %1").arg(QString::fromLocal8Bit(sheetName));
// 
// 	if(!query.exec(sql_str))
// 	{
// 		qDebug() << "ExportExcelObject::export2Excel failed: Create Excel sheet failed.";
// 		//db.close();
// 		//QSqlDatabase::removeDatabase("excelexport");
// 		return -4;
// 	}
// 	int col = query.record().count();
	return TRUE;
}
int ExportExcelObject::initExcelObject()
{
	QSqlDatabase::removeDatabase("excelexport");
	excelObject = new QAxObject( "Excel.Application", this );
	if (!excelObject)
	{
		qDebug() << "��ʼ��Excel���󣬿���û�а�װoffice���!";
		return -1;
	}
	QAxObject *workbooks = excelObject->querySubObject( "Workbooks" ); //�õ�Workbooks���ϵ�ָ�� 
	if (!workbooks)
	{
		qDebug() << "��ʼ��Excel���󣬿���û�а�װoffice���!";
		return -2;
	}
	workbook = workbooks->querySubObject( "Open(const QString&)", excelFilePath); //��Ӳ���ϵ�һ��Excel�ĵ� 
	if (!workbook)
	{
		qDebug() << "Excel�ļ��򿪴���!";
		return -3;
	}
	QAxObject *worksheets = workbook->querySubObject("worksheets");
	worksheet = workbook->querySubObject("worksheets(const QString&)",sheetName);
	return TRUE;
}
void ExportExcelObject::setColumnWidth(int column,int width)
{
	QAxObject *columnObject = worksheet->querySubObject("columns(int)",column);
	columnObject->setProperty("ColumnWidth",QVariant(width));//���õ�һ���п�Ϊ5
}
void ExportExcelObject::setColumnFormat(int column,const QString &displayFormat)
{
	QAxObject *columnObject = worksheet->querySubObject("columns(int)",column);
	columnObject->setProperty("NumberFormatLocal",QVariant(displayFormat));
}
void ExportExcelObject::setAlignment(int row,int column,Qt::Alignment flag)
{
	if (row < 0 || column < 0)
		return;
	QAxObject* rangeObject;
	if (row == 0 && column != 0)
	{
		rangeObject = worksheet->querySubObject("columns(int)",column);
	}
	else if (row != 0 && column == 0)
	{
		rangeObject = worksheet->querySubObject("rows(int)",row);
	}
	else if (row == 0 && column == 0)
	{
		rangeObject = worksheet->querySubObject("Cells()");
	}
	else
	{
		rangeObject = worksheet->querySubObject("Cells( int, int )",row,column);
	}
	switch(flag)
	{
		case Qt::AlignLeft:
			rangeObject->setProperty("HorizontalAlignment",QVariant(-4131));
			break;
		case Qt::AlignRight:
			rangeObject->setProperty("HorizontalAlignment",QVariant(-4152));
			break;
		case Qt::AlignHCenter:
			rangeObject->setProperty("HorizontalAlignment",QVariant(-4108));
			break;
		case Qt::AlignTop:
			rangeObject->setProperty("VerticalAlignment",QVariant(-4160));
			break;
		case Qt::AlignBottom:
			rangeObject->setProperty("VerticalAlignment",QVariant(-4107));
			break;
		case Qt::AlignVCenter:
			rangeObject->setProperty("VerticalAlignment",QVariant(-4108));
			break;
		case Qt::AlignCenter:
			rangeObject->setProperty("HorizontalAlignment",QVariant(-4108));
			rangeObject->setProperty("VerticalAlignment",QVariant(-4108));
			break;
		default:
			break;
	}
}
void ExportExcelObject::resizeRowToContents(int row)
{
	QAxObject *rowObject = worksheet->querySubObject("rows(int)",row);
	rowObject->dynamicCall("AutoFit()");
}
void ExportExcelObject::resizeRowsToContents()
{
	QAxObject *rowsObject = worksheet->querySubObject("rows()");
	rowsObject->dynamicCall("AutoFit()");
}
void ExportExcelObject::resizeColumnToContents(int column)
{
	QAxObject *columnObject = worksheet->querySubObject("columns(int)",column);
	columnObject->dynamicCall("AutoFit()");
}
void ExportExcelObject::resizeColumnsToContents()
{
	QAxObject *columnsObject = worksheet->querySubObject("columns()");
	columnsObject->dynamicCall("AutoFit()");
}
void ExportExcelObject::save()
{
	workbook->querySubObject("Save()");
	excelObject->dynamicCall("Quit()");
}

/**************************************************************************************************************************************************/
ExcelObjectCOM::ExcelObjectCOM()
{
    pExcel     = NULL;
    pWorkbooks = NULL;
    pWorkbook  = NULL;
    pWorksheet = NULL;

    sXlsFile     = "";
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;

    bIsOpen  = false;
    bIsValid = false;

    HRESULT r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
        qDebug("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
    }
}

ExcelObjectCOM::ExcelObjectCOM(QString xlsFile)
{
    pExcel     = NULL;
    pWorkbooks = NULL;
    pWorkbook  = NULL;
    pWorksheet = NULL;

    sXlsFile     = xlsFile;
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;

    bIsOpen  = false;
    bIsValid = false;

    HRESULT r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
        qDebug("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
    }
}

ExcelObjectCOM::~ExcelObjectCOM()
{
    if ( bIsOpen )
    {
        //����ǰ���ȱ������ݣ�Ȼ��ر�workbook
        Close();
    }
    OleUninitialize();
}

/**
  *@brief ��sXlsFileָ����excel����
  *@return true : �򿪳ɹ�
  *        false: ��ʧ��
  */
bool ExcelObjectCOM::Open(UINT nSheet, bool visible)
{

    if ( bIsOpen )
    {
        //return bIsOpen;
        Close();
    }

    if ( NULL == pExcel )
    {
        pExcel = new QAxObject("Excel.Application");
        if ( pExcel )
        {
            bIsValid = true;
        }
        else
        {
            bIsValid = false;
            bIsOpen  = false;
            return bIsOpen;
        }
		bIsVisible = visible;
        pExcel->dynamicCall("SetVisible(bool)", bIsVisible);
    }

    if ( !bIsValid )
    {
        bIsOpen  = false;
        return bIsOpen;
    }

    if ( sXlsFile.isEmpty() )
    {
        bIsOpen  = false;
        return bIsOpen;
    }


    bool ok = CreateXlsFile(sXlsFile);
    if ( !ok )
    {
        bIsOpen  = false;
        return bIsOpen;
    }

    nCurrSheet = nSheet;

    pWorkbooks = pExcel->querySubObject("WorkBooks"); //��ȡ������
    pWorkbook = pWorkbooks->querySubObject("Open(QString, QVariant)",sXlsFile,QVariant(0)); //��xls��Ӧ�Ĺ�����
    pWorksheet = pWorkbook->querySubObject("WorkSheets(int)", nCurrSheet);//�򿪵�һ��sheet

    //�����Ѵ򿪣���ʼ��ȡ��Ӧ����
    QAxObject *usedrange = pWorksheet->querySubObject("UsedRange");//��ȡ��sheet��ʹ�÷�Χ����
    QAxObject *rows = usedrange->querySubObject("Rows");
    QAxObject *columns = usedrange->querySubObject("Columns");

    //��Ϊexcel���Դ��������������ݶ���һ���Ǵ�0,0��ʼ�����Ҫ��ȡ�������±�
    nStartRow    = usedrange->property("Row").toInt();    //��һ�е���ʼλ��
    nStartColumn = usedrange->property("Column").toInt(); //��һ�е���ʼλ��

    nRowCount    = rows->property("Count").toInt();       //��ȡ����
    nColumnCount = columns->property("Count").toInt();    //��ȡ����

    bIsOpen  = true;
    return bIsOpen;
}

/**
  *@brief Open()�����غ���
  */
bool ExcelObjectCOM::Open(QString xlsFile, UINT nSheet, bool visible)
{
    sXlsFile = xlsFile;
    nCurrSheet = nSheet;
    bIsVisible = visible;

    return Open(nCurrSheet,bIsVisible);
}

/**
  *@brief ���������ݣ�������д���ļ�
  */
void ExcelObjectCOM::Save()
{
    if ( pWorkbook )
    {
        pWorkbook->dynamicCall("Save()");
    }
}

/**
  *@brief �ر�ǰ�ȱ������ݣ�Ȼ��رյ�ǰExcel COM���󣬲��ͷ��ڴ�
  */
void ExcelObjectCOM::Close()
{
    //�ر�ǰ�ȱ�������
    Save();
    if ( pExcel && pWorkbook )
    {
        pWorkbook->dynamicCall("Close(bool)", true);
        pExcel->dynamicCall("Quit()");

        delete pExcel;
        pExcel = NULL;

        bIsOpen = false;
        bIsValid = false;
    }
}

/**
  *@brief ��tableWidget�е����ݱ��浽excel��
  *@param tableWidget : ָ��GUI�е�tablewidgetָ��
  *@return ����ɹ���� true : �ɹ�
  *                  false: ʧ��
  */
bool ExcelObjectCOM::SaveDataFrTable(QTableWidget *tableWidget)
{
    if ( NULL == tableWidget )
    {
        return false;
    }
    if ( !bIsOpen )
    {
        return false;
    }

    int tableR = tableWidget->rowCount();
    int tableC = tableWidget->columnCount();

    //��ȡ��ͷд����һ��
    for (int i=0; i<tableC; i++)
    {
        if ( tableWidget->horizontalHeaderItem(i) != NULL )
        {
            this->SetCellData(1,i+1,tableWidget->horizontalHeaderItem(i)->text());
        }
    }

    //д����
    for (int i=0; i<tableR; i++)
    {
        for (int j=0; j<tableC; j++)
        {
            if ( tableWidget->item(i,j) != NULL )
            {
                this->SetCellData(i+2,j+1,tableWidget->item(i,j)->text());
            }
        }
    }

    //����
    Save();

    return true;
}

/**
  *@brief ��ָ����xls�ļ��а����ݵ��뵽tableWidget��
  *@param tableWidget : ִ��Ҫ���뵽��tablewidgetָ��
  *@return ����ɹ���� true : �ɹ�
  *                   false: ʧ��
  */
bool ExcelObjectCOM::ReadDataToTable(QTableWidget *tableWidget)
{
    if ( NULL == tableWidget )
    {
        return false;
    }

    //�Ȱ�table���������
    int tableColumn = tableWidget->columnCount();
    tableWidget->clear();
    for (int n=0; n<tableColumn; n++)
    {
        tableWidget->removeColumn(0);
    }

    int rowcnt    = nStartRow + nRowCount;
    int columncnt = nStartColumn + nColumnCount;

    //��ȡexcel�еĵ�һ��������Ϊ��ͷ
    QStringList headerList;
    for (int n = nStartColumn; n<columncnt; n++ )
    {
        QAxObject * cell = pWorksheet->querySubObject("Cells(int,int)",nStartRow, n);
        if ( cell )
        {
            headerList<<cell->dynamicCall("Value2()").toString();
        }
    }

    //���´�����ͷ
    tableWidget->setColumnCount(nColumnCount);
    tableWidget->setHorizontalHeaderLabels(headerList);


    //����������
    for (int i = nStartRow+1, r = 0; i < rowcnt; i++, r++ )  //��
    {
        tableWidget->insertRow(r); //��������
        for (int j = nStartColumn, c = 0; j < columncnt; j++, c++ )  //��
        {
            QAxObject * cell = pWorksheet->querySubObject("Cells(int,int)", i, j );//��ȡ��Ԫ��

            //��r�����������������
            if ( cell )
            {
                tableWidget->setItem(r,c,new QTableWidgetItem(cell->dynamicCall("Value2()").toString()));
            }
        }
    }

    return true;
}

/**
  *@brief ��ȡָ����Ԫ�������
  *@param row : ��Ԫ����к�
  *@param column : ��Ԫ����к�
  *@return [row,column]��Ԫ���Ӧ������
  */
QVariant ExcelObjectCOM::GetCellData(UINT row, UINT column)
{
    QVariant data;

    QAxObject *cell = pWorksheet->querySubObject("Cells(int,int)",row,column);//��ȡ��Ԫ�����
    if ( cell )
    {
        data = cell->dynamicCall("Value2()");
    }

    return data;
}

/**
  *@brief �޸�ָ����Ԫ�������
  *@param row : ��Ԫ����к�
  *@param column : ��Ԫ��ָ�����к�
  *@param data : ��Ԫ��Ҫ�޸�Ϊ��������
  *@return �޸��Ƿ�ɹ� true : �ɹ�
  *                   false: ʧ��
  */
bool ExcelObjectCOM::SetCellData(UINT row, UINT column, QVariant data)
{
    bool op = false;

    QAxObject *cell = pWorksheet->querySubObject("Cells(int,int)",row,column);//��ȡ��Ԫ�����
    if ( cell )
    {
        QString strData = data.toString(); //excel ��Ȼֻ�ܲ����ַ��������ͣ��������޷�����
        cell->dynamicCall("SetValue(const QVariant&)",strData); //�޸ĵ�Ԫ�������
        op = true;
    }
    else
    {
        op = false;
    }

    return op;
}

/**
  *@brief ����һ��xls�����ļ�
  *@param xlsFile : �����ļ���
  *@return true : �����ɹ�
  *        false: ����ʧ��
  */
bool ExcelObjectCOM::CreateXlsFile(const QString &xlsFile)
{

    bool cr = false;
    QFile f(xlsFile);
    if ( !f.exists())
    {
        /**
          *@note �����޷��ҵ�workbook����һ���������Ľӿڣ�ֻ�������ֿ����ļ��ķ���
          *���ߣ�ֱ�Ӵ���һ��.xlsΪ��׺�Ŀհ��ĵ�
          */
        QFile copyFile(tr("./template/template.xls"));
        if ( copyFile.exists() )
        {
            //ֱ�ӿ���һ��ģ��
            QFile::copy(tr("./template/template.xls"),xlsFile);
        }
        else
        {
            //������xlsΪ��׺�Ŀհ��ĵ�
            f.open(QIODevice::WriteOnly);
            f.close();
        }

        //�ж��Ƿ񴴽��ɹ�
        cr = f.open(QIODevice::ReadWrite);
        f.close();

    }
    else
    {
        cr = true;
    }

    return cr;
}
void ExcelObjectCOM::setColumnWidth(int column,int width)
{
	QAxObject *columnObject = pWorksheet->querySubObject("columns(int)",column);
	columnObject->setProperty("ColumnWidth",QVariant(width));//���õ�һ���п�Ϊ5
}
void ExcelObjectCOM::setColumnFormat(int column,const QString &displayFormat)
{
	QAxObject *columnObject = pWorksheet->querySubObject("columns(int)",column);
	columnObject->setProperty("NumberFormatLocal",QVariant(displayFormat));
}
void ExcelObjectCOM::setAlignment(int row,int column,Qt::Alignment flag)
{
	if (row < 0 || column < 0)
		return;
	QAxObject* rangeObject;
	if (row == 0 && column != 0)
	{
		rangeObject = pWorksheet->querySubObject("columns(int)",column);
	}
	else if (row != 0 && column == 0)
	{
		rangeObject = pWorksheet->querySubObject("rows(int)",row);
	}
	else if (row == 0 && column == 0)
	{
		rangeObject = pWorksheet->querySubObject("Cells()");
	}
	else
	{
		rangeObject = pWorksheet->querySubObject("Cells( int, int )",row,column);
	}
	switch(flag)
	{
		case Qt::AlignLeft:
			rangeObject->setProperty("HorizontalAlignment",QVariant(-4131));
			break;
		case Qt::AlignRight:
			rangeObject->setProperty("HorizontalAlignment",QVariant(-4152));
			break;
		case Qt::AlignHCenter:
			rangeObject->setProperty("HorizontalAlignment",QVariant(-4108));
			break;
		case Qt::AlignTop:
			rangeObject->setProperty("VerticalAlignment",QVariant(-4160));
			break;
		case Qt::AlignBottom:
			rangeObject->setProperty("VerticalAlignment",QVariant(-4107));
			break;
		case Qt::AlignVCenter:
			rangeObject->setProperty("VerticalAlignment",QVariant(-4108));
			break;
		case Qt::AlignCenter:
			rangeObject->setProperty("HorizontalAlignment",QVariant(-4108));
			rangeObject->setProperty("VerticalAlignment",QVariant(-4108));
			break;
		default:
			break;
	}
}
void ExcelObjectCOM::resizeRowToContents(int row)
{
	QAxObject *rowObject = pWorksheet->querySubObject("rows(int)",row);
	rowObject->dynamicCall("AutoFit()");
}
void ExcelObjectCOM::resizeRowsToContents()
{
	QAxObject *rowsObject = pWorksheet->querySubObject("rows()");
	rowsObject->dynamicCall("AutoFit()");
}
void ExcelObjectCOM::resizeColumnToContents(int column)
{
	QAxObject *columnObject = pWorksheet->querySubObject("columns(int)",column);
	columnObject->dynamicCall("AutoFit()");
}
void ExcelObjectCOM::resizeColumnsToContents()
{
	QAxObject *columnsObject = pWorksheet->querySubObject("columns()");
	columnsObject->dynamicCall("AutoFit()");
}
/**
  *@brief ��ճ�����֮�������
  */
void ExcelObjectCOM::Clear()
{
    sXlsFile     = "";
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;
}

/**
  *@brief �ж�excel�Ƿ��ѱ���
  *@return true : �Ѵ�
  *        false: δ��
  */
bool ExcelObjectCOM::IsOpen()
{
    return bIsOpen;
}

/**
  *@brief �ж�excel COM�����Ƿ���óɹ���excel�Ƿ����
  *@return true : ����
  *        false: ������
  */
bool ExcelObjectCOM::IsValid()
{
    return bIsValid;
}

/**
  *@brief ��ȡexcel������
  */
UINT ExcelObjectCOM::GetRowCount()const
{
    return nRowCount;
}

/**
  *@brief ��ȡexcel������
  */
UINT ExcelObjectCOM::GetColumnCount()const
{
    return nColumnCount;
}
/*******************************************************************************************************************************************************/
ExcelObjectODBC::ExcelObjectODBC(const QString &filePath,const QString &sheetName)
{
	m_sFilePath = filePath;
	m_sSheetName = sheetName;
	excelModel = new QSqlQueryModel;
	m_Database = QSqlDatabase::addDatabase("QODBC", "excel");
	GetExcelDriver();
	//set the dsn string
 	m_sDsn = QString("DRIVER={%1};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%2\";DBQ=%3").
 		arg(m_sExcelDriver).arg(m_sFilePath).arg(m_sFilePath);
}
ExcelObjectODBC::~ExcelObjectODBC()
{
	QSqlDatabase::removeDatabase("excel");
}
void ExcelObjectODBC::AddHeader(const int columun, const QString &fieldName, const QString &fieldType)
{
	fieldList << new EEO_Field(columun, fieldName, fieldType);
}
int ExcelObjectODBC::ExportTableViewToExcel(QTableView *tableView)
{
	m_bIsCancel = false;
	if(fieldList.size() <= 0)
	{
		m_sLastError = QString("ExcelObjectODBC::ExportTableViewToExcel() No fields defined.");
		return FALSE;
	}
	QSqlQuery query(m_Database);

	//drop the table if it's already exists
	QString s, sSql = QString("DROP TABLE [%1] (").arg(m_sSheetName);
	query.exec(sSql);

	//create the table (sheet in Excel file)
	sSql = QString("CREATE TABLE [%1] (").arg(m_sSheetName);
	for (int i = 0; i < fieldList.size(); i++)
	{
		s = QString("[%1] %2").arg(fieldList.at(i)->sFieldName).arg(fieldList.at(i)->sFieldType);
		sSql += s;
		if(i < fieldList.size() - 1)
			sSql += " , ";
	}

	sSql += ")";
	query.prepare(sSql);

	if(!query.exec())
	{
		m_sLastError = QString("ExcelObjectODBC::ExportTableViewToExcel() Create Excel sheet failed.");
		return FALSE;
	}

	//add all rows
	sSql = QString("INSERT INTO [%1] (").arg(m_sSheetName);
	for (int i = 0; i < fieldList.size(); i++)
	{
		sSql += fieldList.at(i)->sFieldName;
		if(i < fieldList.size() - 1)
			sSql += " , ";
	}
	sSql += ") VALUES (";
	for (int i = 0; i < fieldList.size(); i++)
	{
		sSql += QString(":data%1").arg(i);
		if(i < fieldList.size() - 1)
			sSql += " , ";
	}
	sSql += ")";

	qDebug() << sSql;

	int r, iRet = 0;
	for(r = 0 ; r < tableView->model()->rowCount() ; r++)
	{
		query.prepare(sSql);
		for (int c = 0; c < fieldList.size(); c++)
		{
			query.bindValue(QString(":data%1").arg(c),tableView->model()->data(tableView->model()->index(r, fieldList.at(c)->iCol)));
		}

		if(query.exec())
			iRet++;

		if(r % 10 == 0)
			emit exportedRowCount(r);

		if(m_bIsCancel)
			break;
	}

	emit exportedRowCount(r);
	return iRet;
}
bool ExcelObjectODBC::ReadRow(const QVariantList &rowValues, long row)
{
	return true;
}
bool ExcelObjectODBC::ReadColumn(const QVariantList &columnValues, const QString &column, bool auto)
{
	return true;
}
bool ExcelObjectODBC::ReadColumn(const QVariantList &columnValues, int column)
{
	return true;
}
bool ExcelObjectODBC::WriteRow(const QVariantList &rowValues)
{
	if (rowValues.size() != fieldList.size())
	{
		m_sLastError = QString("ExcelObjectODBC::input field num error!");
		return false;
	}
	QSqlQuery query(m_Database);
	QString sSql;
	sSql = QString("INSERT INTO [%1] (").arg(m_sSheetName);
	for (int i = 0; i < fieldList.size(); i++)
	{
		sSql += fieldList.at(i)->sFieldName;
		if(i < fieldList.size() - 1)
			sSql += " , ";
	}
	sSql += ") VALUES (";
	for (int i = 0; i < fieldList.size(); i++)
	{
		sSql += QString("\'%1\'").arg(rowValues.at(fieldList.at(i)->iCol).toString());
		if(i < fieldList.size() - 1)
			sSql += " , ";
	}
	sSql += ")";

	qDebug() << sSql;
	if (!query.exec(sSql))
	{
		m_sLastError = query.lastError().text();
		return false;
	}
	return true;
}
void ExcelObjectODBC::GetExcelDriver()
{
	wchar_t szBuf[2001];
	wchar_t excl[] = L"Excel";
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	wchar_t *pszBuf = szBuf;
	// ��ȡ�Ѱ�װ����������(������odbcinst.h��)
	if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
	{
		m_sExcelDriver = "";
		m_sLastError = QString("ExcelObjectODBC::Get the names of the installed drivers error");

		return;
	}
	// �����Ѱ�װ�������Ƿ���Excel...
	do
	{
		if(wcsstr(pszBuf, excl) != 0)
		{
			//���� !
			m_sExcelDriver = QString::fromWCharArray(pszBuf);
			break;
		}
		wchar_t ze = {'\0'};
		pszBuf = wcschr(pszBuf, ze) + 1;
	}
	while (pszBuf[1] != '\0');
}
bool ExcelObjectODBC::Open()
{
	if(!m_Database.isValid())
	{
		qDebug() << "ExcelObjectODBC::open failed: QODBC not supported.";
		m_sLastError = QString("ExcelObjectODBC::open failed: QODBC not supported.");
		return false;
	}
	m_Database.setDatabaseName(m_sDsn);
	if(!m_Database.open())
	{
		qDebug() << "ExcelObjectODBC::open failed: Create Excel file failed by DRIVER={Microsoft Excel Driver (*.xls)}.";
		m_sLastError = QString("ExcelObjectODBC::open failed: Create Excel file failed by DRIVER={Microsoft Excel Driver (*.xls)}.");
		return false;
	}
	if (fieldList.size()!=0)
	{
		QSqlQuery query(m_Database);

		//drop the table if it's already exists
		QString s, sSql = QString("DROP TABLE [%1] (").arg(m_sSheetName);
		query.exec(sSql);

		//create the table (sheet in Excel file)
		sSql = QString("CREATE TABLE [%1] (").arg(m_sSheetName);
		for (int i = 0; i < fieldList.size(); i++)
		{
			s = QString("[%1] %2").arg(fieldList.at(i)->sFieldName).arg(fieldList.at(i)->sFieldType);
			sSql += s;
			if(i < fieldList.size() - 1)
				sSql += " , ";
		}

		sSql += ")";
		query.prepare(sSql);

		if(!query.exec())
		{
			qDebug() << "ExcelObjectODBC::Create Excel sheet failed.";
			m_sLastError = QString("ExcelObjectODBC::Create Excel sheet failed.");
			return false;
		}
	}
	return true;
}
QSqlQueryModel *ExcelObjectODBC::GetExcelSheetModel()
{
	excelModel->clear();
	excelModel->setQuery(QString("SELECT * from [%1$A1:IV65536]").arg(m_sSheetName),m_Database);
	return excelModel;
}