#ifndef EXPORTEXCELOBJECT_H
#define EXPORTEXCELOBJECT_H

#include <QtCore/qstring.h>
#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QSqlDatabase>
#include <ActiveQt/QAxFactory>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QAxBase>
#include <QAxObject>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>

#include <QTableWidget>
#include <QTableView>
#include <QTableWidgetItem>
#include <QDebug>

typedef unsigned int UINT;
#define EXCEL_MODE_READ		0
#define EXCEL_MODE_WRITE	1

class EEO_Field
{
public:
    EEO_Field(const int ic, const QString &sf, const QString &st):
            iCol(ic),sFieldName(sf),sFieldType(st){};

    int     iCol;
    QString sFieldName;
    QString sFieldType;
};

class ExcelObjectODBC : public QObject
{
	Q_OBJECT
public:
	ExcelObjectODBC(const QString &filePath,const QString &sheetName = QString("sheet"));
	~ExcelObjectODBC();
	inline void SetFilePath(const QString &filePath){m_sFilePath = filePath;};
	inline void SetSheetName(const QString &sheetName){m_sSheetName = sheetName;};
	inline const QString &GetLastError(){return m_sLastError;}
	bool Open();
	void AddHeader(const int columun, const QString &fieldName, const QString &fieldType);//filedType char(n) datetime int float ...
	void RemoveAllFields(){while (!fieldList.isEmpty()) delete fieldList.takeFirst();};
	int ExportTableViewToExcel(QTableView *tableView);
	bool ReadRow(const QVariantList &rowValues, long row=0);
	bool ReadColumn(const QVariantList &columnValues, const QString &column, bool auto = true);
	bool ReadColumn(const QVariantList &columnValues, int column);
	bool WriteRow(const QVariantList &rowValues);
	QSqlQueryModel *GetExcelSheetModel();
Q_SIGNALS:
	void exportedRowCount(int row);
public Q_SLOTS:
	void cancel() {m_bIsCancel = true;};
private:
	void GetExcelDriver();// Get the name of the Excel-ODBC driver
	QString m_sFilePath;
	QString m_sSheetName;
	QString m_sExcelDriver;
	QString m_sDsn;
	QString m_sLastError;
	bool m_bIsCancel;
	QSqlDatabase m_Database;
	QSqlQueryModel *excelModel;
	QList<EEO_Field *> fieldList;
};

class ExportExcelObject : public QObject
{
    Q_OBJECT
public:
	ExportExcelObject(){};
    ExportExcelObject(const QString &filepath, const QString &sheettitle,
                      QTableView *tableview):excelFilePath(filepath),
					  sheetName(sheettitle), tableView(tableview){};

    ~ExportExcelObject() {QSqlDatabase::removeDatabase("excelexport");excelObject->dynamicCall("Quit()");};

public:
    void setOutputFilePath(const QString &spath) {excelFilePath = spath;};
    void setOutputSheetTitle(const QString &ssheet) {sheetName = ssheet;};
    void setTableView(QTableView *tableview) {tableView = tableview;};

    void addField(const int iCol, const QString &fieldname, const QString &fieldtype)
         {fieldList << new EEO_Field(iCol, fieldname, fieldtype);};

    void removeAllFields()
         {while (!fieldList.isEmpty()) delete fieldList.takeFirst();};

    int export2Excel();
	int readExcelData();
	int initExcelObject();//���Ҫ����excel��ʽ����ִ�д˺���;
	void setColumnWidth(int column,int width);
	void setColumnFormat(int column,const QString &displayFormat = QString::fromLocal8Bit("G/ͨ�ø�ʽ"));
	void setAlignment(int row = 0,int column = 0,Qt::Alignment flag = Qt::AlignCenter);//rowΪ0ʱ��������(column) columnΪ0ʱ��������(row) ȫΪ0ʱ��������
	void save();
signals:
    void exportedRowCount(int row);

private:
	bool isCancel;
    QString excelFilePath;
    QString sheetName;
    QTableView *tableView;
    QList<EEO_Field *> fieldList;
	QAxObject *excelObject;
	QAxObject *workbook;
	QAxObject *worksheet;
public slots:
	void cancel() {isCancel = TRUE;};
	void resizeRowToContents(int row);
	void resizeRowsToContents();
	void resizeColumnToContents(int column);
	void resizeColumnsToContents();
};

class ExcelObjectCOM : protected QObject
{
public:
	ExcelObjectCOM();
	ExcelObjectCOM(QString xlsFile);
	~ExcelObjectCOM();

public:
	bool Open(UINT nSheet = 1, bool visible = false);//��xls�ļ�
	bool Open(QString xlsFile, UINT nSheet = 1, bool visible = false);
	void Save();                //����xls����
	void Close();               //�ر�xls����

	bool SaveDataFrTable(QTableWidget *tableWidget); //�������ݵ�xls
	bool ReadDataToTable(QTableWidget *tableWidget); //��xls��ȡ���ݵ�ui

	QVariant GetCellData(UINT row, UINT column);                //��ȡָ����Ԫ����
	bool     SetCellData(UINT row, UINT column, QVariant data); //�޸�ָ����Ԫ����
	void setColumnWidth(int column,int width);
	void setColumnFormat(int column,const QString &displayFormat = QString::fromLocal8Bit("G/ͨ�ø�ʽ"));
	void setAlignment(int row = 0,int column = 0,Qt::Alignment flag = Qt::AlignCenter);//rowΪ0ʱ��������(column) columnΪ0ʱ��������(row) ȫΪ0ʱ��������
	void resizeRowToContents(int row);
	void resizeRowsToContents();
	void resizeColumnToContents(int column);
	void resizeColumnsToContents();
	inline UINT GetRowCount()const;
	inline UINT GetColumnCount()const;

	inline bool IsOpen();
	inline bool IsValid();

protected:
	bool CreateXlsFile(const QString &xlsFile);
	void Clear();

private:
	QAxObject *pExcel;      //ָ������excelӦ�ó���
	QAxObject *pWorkbooks;  //ָ��������,excel�кܶ๤����
	QAxObject *pWorkbook;   //ָ��sXlsFile��Ӧ�Ĺ�����
	QAxObject *pWorksheet;  //ָ�������е�ĳ��sheet��

	QString   sXlsFile;     //xls�ļ�·��
	UINT      nCurrSheet;   //��ǰ�򿪵ĵڼ���sheet
	bool      bIsVisible;   //excel�Ƿ�ɼ�
	int       nRowCount;    //����
	int       nColumnCount; //����
	int       nStartRow;    //��ʼ�����ݵ����±�ֵ
	int       nStartColumn; //��ʼ�����ݵ����±�ֵ

	bool      bIsOpen;      //�Ƿ��Ѵ�
	bool      bIsValid;     //�Ƿ���Ч

};

#endif // EXPORTEXCELOBJECT_H
