#ifndef CHECKDCOM_H
#define CHECKDCOM_H
#include <QObject>
#include <QFile>
#include <QTextStream>
#include "common.h"
#include "mdiMainWin.h"
#include "calldblib.h"
//#define DEF_INTERLOCKFILENAME "/home/ems/h9000/cfgmgr/def/InterLockFile.def"
//#define DEF_INTERLOCKERRNAME "/home/ems/h9000/cfgmgr/def/InterLockErr.log"
//#define DEF_INTERLOCKFILEPATH "/home/ems/h9000/cfgmgr/def/"
#define  DCOMERREGEXPSPLIT "\\s"
#define  DCOMERREGEXPKEY "^BEGIN:$|^POINT:$|^INCLUDE$|^END$|^CLOSE$|^OPEN$|^NULL$"	////�ؼ��ֲ����

class  CheckDcom:QObject
{
	Q_OBJECT
public:
	CheckDcom(MdiMainWindow * parent,Dcomcfg dcomcfg);
	~CheckDcom();

	QList<FilePoint> iccpfilelist ;
	QList<FilePoint> iec101filelist ;
	QList<FilePoint> iec104filelist ;
	QStringList getlinelist(QString strin,QRegExp rx);
	
	void checkAllDcomfile(); //������е���ļ�
	int checkOneDcomfile(QString path,Dcomfile dcomfile); //���һ���������ļ�
	int checkPoint(QStringList listline,QString curfilename);  //���һ��list�еĵ� �Ƿ��ڿ��д���
	void getDcomfileInfo(QString filename,Dcomfile*dcomfile);
	void checkdbpoint(Dcomfile dcomfile,QStringList listline,QString curfilename); //����߼��� 
	void checkdbpoint_range(Dcomfile dcomfile,QStringList linelist,QString curfilename);//����߼���&&��������
	void checkintlock(Dcomfile dcomfile,QStringList linelist,QString curfilename);//��������
private:
	MdiMainWindow * m_parent;
	void initClass();
	void getFileNamelist(QString filetype,QString filepath,QList<FilePoint>*filenamelist);
	

	QString strDcomFile;
	QTextStream fileStream;
	QFile *pDcomFile;

	QFile *pDcomErrFile;
	QTextStream *perrFileStream;
	int lineNum;
	Dcomcfg m_dcomcfg;

	Calldblib *m_pCalldblib;
};
#endif