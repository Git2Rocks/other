#ifndef CHECKWATER_H
#define CHECKWATER_H
#include <QObject>
#include <QFile>
#include <QTextStream>
#include "common.h"
#include "mdiMainWin.h"
#include "calldblib.h"

//#define DEF_WATERFILENAME "water_revert.def"
//#define DEF_WATERERRNAME "/home/ems/h9000/cfgmgr/def/WaterErr.log"
//#define DEF_WATERFILEPATH "/home/ems/h9000/cfgmgr/def/"

#define  WATERERREGEXPSPLIT "\\s\|^BEGIN:$|^POINT:$|^INCLUDE$|^END$|^CLOSE$|^OPEN$|[=-\?\+\&()/</>]" //�ָ��ַ���
#define  WATERERREGEXPKEY "^BEGIN:$|^POINT:$|^INCLUDE$|^END$|^CLOSE$|^OPEN$|^[0-9]+$|^#*$"	////�ؼ��ֲ����

class  CheckWaterRevert:QObject
{
	Q_OBJECT
public:
	CheckWaterRevert(MdiMainWindow * parent,Watercfg watercfg);
	~CheckWaterRevert();

	QList<FilePoint> filenamelist ;
	QStringList getlinelist(QString strin,QRegExp rx);
	
	void checkAllWaterfile(); //�������water�ļ�
	int checkOneWaterfile(QString filename); //���һ������water�ļ�
	int checkPoint(QStringList listline,QString curfilename,bool pointflag=false);  //���һ��list�еĵ� �Ƿ��ڿ��д���
//	QTextStream getErrFileSteam(){return perrFileStream;}
	//QTextStream *perrFileStream;
private:
	MdiMainWindow * m_parent;
	void initClass();
	int loadTempFile(QString filepath,QList<FilePoint>*filenamelist);
	QString strWaterFile;
	QTextStream fileStream;
	QFile *pWaterFile;

	QFile *pWaterErrFile;
	QTextStream *perrFileStream;
	int lineNum;
	Watercfg m_watercfg;

	Calldblib *m_pCalldblib;
};
#endif