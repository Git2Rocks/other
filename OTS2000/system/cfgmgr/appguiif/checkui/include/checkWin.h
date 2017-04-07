#ifndef CHECKWIN_H
#define CHECKWIN_H
#include <QTreeWidget>
#include <QTableWidget>
#include <QSplitter>
#include <QStandardItemModel>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QTextStream>
 #include <QRegExp>
#include <QTextEdit>

#include "mdiMainWin.h"
#include "calldblib.h"
#include "checkinterlock.h"
#include "checkcalcu.h"
#include "checkdbin.h"
#include "checktemp.h"
#include "checkwater.h"
#include "checkdcom.h"
#include "common.h"
#include "operatexml.h"

#define TABLECOLUMNUM 5 //�������ⲿ����
static QString TABLECOLUMNAME[] = {"TYPE","FILENAME","LINE","POINTNAME","INFO"};
static int TABLECOLUMWIDTH[]={80,340,70,320,150};

enum ColumIndex
{
	TYPE=0,
	FILENAME,
	LINE,
	POINTNAME,
	INFO,	
};


QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTableWidget;
class QSplitter;
class MainWindow;
class QSortFilterProxyModel;
class QCheckBox;
QT_END_NAMESPACE



class CcheckWin :   public QSplitter 
{
	Q_OBJECT
public:
	CcheckWin(MdiMainWindow * parent);
	~CcheckWin();
public:
	
	

	Calldblib *pCalldblib;
	CheckInterlock *pCheckInterlock;
	CheckCalcu *pCheckCalcu;
	CheckDbin *pCheckDbin;
	QList<QString> fileTypeName ;

	CheckTempeigen *pCheckTempeigen;
	CheckWaterRevert *pCheckWaterRevert;
	CheckDcom *pCheckDcom;
	COperateXml *pCOperateXml;

	Dbincfg dbincfg;
	Calcucfg calcucfg;
	Interlockcfg interlockcfg;
	Tempcfg tempcfg;
	Watercfg watercfg;
	Dcomcfg dcomcfg;
	MainWincfg mainWincfg;

private:
	MdiMainWindow * m_parent;
	void createActions();
	void createMainView();
	void createFileTree();
	void CreateTableHead();//������ͷ;
	void DispTableRecord();//��ʾ����
	void DispTable();

	void initClass();
	void initInterlock();
	void initCalcu();
	void initOperateXml();
	void initDbin();
	void initDcom();
	void initTemp();
	void initWater();

	void clearAllSelectFile();//�������ѡ���ļ�
	void getAllSelectFile();//ѡ������ѡ���ļ�

	void creatToolbar();

	QTextStream *m_perrInterLockStream;
	bool saveSourceDefFile();
	bool saveFile(const QString &fileName);

	void getCheckdbincfg();
	void getCheckcalcucfg();
	void getCheckinterlockcfg();
	void getmainWincfg();
	void getcfgmgrcfg();
	void getCheckdcomcfg();
	void getCheckwatercfg();
	void getChecktempcfg();

	void setChecktempcfg();
	void setCheckwatercfg();
	void setCheckdbincfg();
	void setCheckcalcucfg();
	void setCheckinterlockcfg();
	void setmainWincfg();
	void setcfgmgrcfg();
	void setCheckdcomcfg();
	bool textEditmaybeSave();


	QTreeWidget *m_filetree;				//�����ļ��б�
	QGroupBox* leftgroupbox;  //ȷ��ȡ��
	QPushButton *btnCheck;
	QPushButton *btnCancel;


	QTreeWidgetItem *m_toplevelItem;
	QTreeWidgetItem *m_hFileType[FILETYPENUM];

	QTreeWidgetItem *m_calcuItem[2]; //����������ٷ�һ��

	QTableView	*m_paralist1;			//������Ϣ�б�
	QTableView	*m_paralist2;		//ʵʱ���ݼ�¼���б�
	QTextEdit *m_sourceDefEdit;     //��defԴ�ļ�
	QFile *psouceDefFile;
	QString cursourceDefName;

	QHeaderView *paralist1_header; //m_paralist1ˮƽ��ͷ
	QHeaderView *paralist2_header;

	//	FreezeTableWidget *m_paralist1;
	QGroupBox* groupbox;  //����ѡ��
	QLabel * labelOrder;
	QComboBox *m_indexfield1;
	QComboBox *m_indexfield2;

	QLabel * labelCurline;
	QLineEdit *columnName;
	QLineEdit *columnValue;


	QCheckBox *filterCaseSensitivityCheckBox;
	QCheckBox *sortCaseSensitivityCheckBox;
	QCheckBox *ModifyUpdateCheckBox;
	QLabel *filterPatternLabel;
	QLabel *filterSyntaxLabel;
	QLabel *filterColumnLabel;
	QLineEdit *filterPatternLineEdit;
	QComboBox *filterSyntaxComboBox;
	QComboBox *filterColumnComboBox;
	QPushButton *startfilterbtn;


	QStandardItemModel model1;
	QStandardItemModel model2;

	QSortFilterProxyModel *proxyModel;

	QSplitter *splitter1;
	QSplitter *splitter2;

	QToolBar *editToolBar;
	QAction *saveAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
private slots:
	bool Onsave();
	void OnfilterRegExpChanged();
	void OnfilterColumnChanged();
	void OnsortChanged();
	void OnModifyUpdatestateChanged();

	void OntoplevelItemCheckChanged(QTreeWidgetItem * curitem, int colum);
	
	void OnpushCheckbtn();
	void OnpushCancelbtn();
	void Onparalist1doubleClick(const QModelIndex &);
	void OnmousePressEdit();
	void sortByColumn();
	
};
#endif