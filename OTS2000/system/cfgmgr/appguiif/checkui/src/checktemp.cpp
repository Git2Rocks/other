#include "checktemp.h"
#include <QDebug>
#include <QMessageBox>
CheckTempeigen::CheckTempeigen(MdiMainWindow * parent,Tempcfg tempcfg)
{
	m_parent=parent;
	m_tempcfg=tempcfg;
	initClass();
}
CheckTempeigen::~CheckTempeigen()
{

}
void CheckTempeigen::initClass()
{
	lineNum=0;
	filenamelist.clear();
	m_pCalldblib=new Calldblib(DBPATH);
	if(-1==m_pCalldblib->MountDB())
	{
		qDebug()<<"Fail to MountDB!";
		QMessageBox::information(m_parent, tr("MountDB"),
			tr("Fail to MountDB!.\nplease check DATABASE.OUT and restart!"));
		exit(-1);
	} 


	loadTempFile(m_tempcfg.tempfile,&filenamelist);


}
int CheckTempeigen::loadTempFile(QString filepath,QList<FilePoint>*filenamelist)
{
	FilePoint tmpfile;
	tmpfile.filename=filepath;
	tmpfile.selectflag=0;
	tmpfile.validflag=1;
	
	filenamelist->append(tmpfile);

	return 1;

}
void CheckTempeigen::checkAllTempfile() //������б����ļ�
{
	if (QFile::exists(m_tempcfg.errfile))
	{
		QFile(m_tempcfg.errfile).remove();
	}

	pTempErrFile=new QFile(m_tempcfg.errfile);

	if (!pTempErrFile->open(QFile::WriteOnly | QFile::Text))
	{
		qDebug()<<"open "<<m_tempcfg.errfile<<" error";
		pTempErrFile->close();
		return;
	}
	perrFileStream=new QTextStream(pTempErrFile);
	
	QString filename;
	for(int i=0;i<filenamelist.count();i++)
	{
		if (filenamelist.at(i).selectflag)
		{
			filename=filenamelist.at(i).filename;
			checkOneTempfile(filename);
		}

	}

	pTempErrFile->close();
	
}
int CheckTempeigen::checkOneTempfile(QString filename) //���һ����������ļ�
{
	filename=m_tempcfg.filepath+"/"+filename;
	pTempFile=new QFile(filename);
	if (!pTempFile->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug()<<"open "<<filename<<" error";
		pTempFile->close();
		return(-1);
	}

	bool interlockPoint=false; //��ǰ���Ƿ��� POINT����
	QTextStream streamIn(pTempFile);
	lineNum=0;
	while (!streamIn.atEnd()) {

		QString line = streamIn.readLine();

		if (line.contains("POINT:"))
		{
			interlockPoint=true;
		}
		else
		{
			interlockPoint=false;
		}
		QStringList linelist=getlinelist(line,QRegExp(TEMPERREGEXPSPLIT));
		lineNum++;
		checkPoint(linelist, filename,interlockPoint);

	}
	
	pTempFile->close();
	return 1;
}

QStringList CheckTempeigen::getlinelist(QString strin,QRegExp rx)
{

	QStringList tmplist=strin.split( rx,QString::SkipEmptyParts);	
	return	tmplist;

}

int CheckTempeigen::checkPoint(QStringList listline,QString curfilename,bool pointflag)   //���һ��list�еĵ� �Ƿ��ڿ��д���
{
	int check_pt_err=0;
	QString namestr;
	POINTER	point;
	int enorcn=0;
	for (int i=0;i<listline.count();i++)
	{
		namestr=listline.at(i);

		if (namestr.contains(QRegExp(TEMPERREGEXPKEY))) //�ؼ��ֲ����
		{
			continue;
		}

		enorcn=0;
		foreach(QChar charitem,namestr)
		{
			if (charitem.unicode()>0x7F)
			{
				enorcn=1;
				break;
			}
		}

		if (enorcn) //���ֲ����
		{
			continue;
		}

		if(-1==m_pCalldblib->qGetPtIdByNameStr(namestr.toLocal8Bit().data(), &point))
		{
			check_pt_err= 1;
			QString errstr=QString("TEMP\t%1\t%2\t%3\tnot in db \n").arg(curfilename).arg(lineNum).arg(namestr);
			//qDebug()<<errstr;
			*perrFileStream<<errstr;
		}
	}

	return check_pt_err;
}

