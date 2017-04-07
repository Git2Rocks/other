#if defined(Q_WS_WIN)
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include <QtGlobal>
#include <QApplication>
#include <QtGui>
#include <QTranslator>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include "SimuTrainee.h"
class  QSystemSemaphore;
class QSharedMemory;
QSystemSemaphore sema("OTS_SIMUTRAINEE",1,QSystemSemaphore::Open); 
QSharedMemory mem("SimuTrainee");// ȫ�ֶ����� 
int InitHDB()
{	
	// ȷ��ֻ����һ�� 	
	if (!mem.create(1))// ���ȫ�ֶ����Դ������˳� 
	{ 
		QMessageBox().information(NULL,QString::fromLocal8Bit("��ʾ!"),QString::fromLocal8Bit("����������"),QMessageBox::Ok);		
		sema.release();// ����� Unix ϵͳ�����Զ��ͷš� 
		return FALSE;
	} 
	if(MountDB(DB_NAME) == -1)
	{
		QMessageBox().information(NULL,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("call MountDB(DATABASE_NAME) error!"),QMessageBox::Ok);		
		return FALSE;
	}
	if(lan_init_all() == (int)FALSE)
	{
		QMessageBox().information(NULL,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("call Lan_init_all() error!"),QMessageBox::Ok);		
		return FALSE;
	}
	if(get_ots_shm()==(int)FALSE||get_hdb_shm()==(int)FALSE)
	{
		QMessageBox().information(NULL,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ȡ����������ʧ��!"),QMessageBox::Ok);		
		return FALSE;
	}
	else
	{
		shm_hdb_addr->data_revert.speed = 8;//�Ժ�Ҫ�İ�...0728????????
	}
	ReadOtsDefFile();
	db_conn.setDatabaseName("SimuTrainee");
	if(ConnectHDB(db_conn)==(int)FALSE)
	{
		QMessageBox().information(NULL,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("������ʷ���ݿ�ʧ��!"),QMessageBox::Ok);		
		return FALSE;
	}	

	if( InitOTSHdb()!=(int)TRUE )
	{
		QMessageBox().information(NULL,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("InitOTSHdbʧ��!"),QMessageBox::Ok);		
		return FALSE;
	} 
	return TRUE;
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(SimuTrainee);

	QApplication app(argc, argv);
	QString translatorFileName = QLatin1String("qt_");
	translatorFileName += QLocale::system().name();
	QTranslator *translator;
	translator= new QTranslator(&app);
	//if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
	if (translator->load(translatorFileName,"./plugins"))
		app.installTranslator(translator);

	sema.acquire();// ���ٽ������������ڴ�   SharedMemory
	//������ʷ���ݿ�
	int nRet=InitHDB();
	sema.release();// �ٽ���
	if (!nRet)
	{ 	 
		QMessageBox::information( NULL,QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("SIMUTRAINEE����ʧ��,��������,ȷ��H9000ϵͳ������"),
			QMessageBox::Ok);
		exit(0);
	}
 	SimuTrainee window;	
	//window.setAttribute(Qt::WA_QuitOnClose,true);
	//window.setAttribute(Qt::WA_DeleteOnClose,true);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
	QApplication::addLibraryPath("./plugins");
	window.show();
	return app.exec();
	UnMountDB ();
}