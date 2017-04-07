#ifndef QABSTRACTMONITOR_H
#define QABSTRACTMONITOR_H

#include <QObject>
#include <QMutex>
#include <QMap>

#include "qutildef.h"

class QAbstractMonitor : public QObject
{
	Q_OBJECT

public:
	QAbstractMonitor(const QString& filename, QObject* watched, QObject *parent=0);
	~QAbstractMonitor();

public:
	void load();

protected:
	virtual bool eventFilter(QObject* watched, QEvent* event);

	virtual bool loadFile()=0;

protected:
	QMutex	m_mutex;

	QString		m_strFileName;	//�ļ�����
	FileInfo	m_file;			//�ļ���Ϣ

	bool		m_bFirst;		//�Ƿ��״μ���

	QObject*	m_pWatched;		//������
};


#endif // QABSTRACTMONITOR_H
