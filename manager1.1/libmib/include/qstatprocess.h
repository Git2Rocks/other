#ifndef QSTATPROCESS_H
#define QSTATPROCESS_H

/**
*	@Desc	��ȡ������Ϣ
*	@Author zlb
*	@Time	2011-5-31
**/

#include <QMap>

#include "qmibextern.h"

class MIB_EXPORT QStatProcess : public QObject, public QAbstractStat
{
	Q_OBJECT

public:
	QStatProcess(QObject *parent=0);
	~QStatProcess();

	enum {Type=UTIL_TYPE_PROCESS};

	enum MethodType
	{
		MethodCreate=0,		//��������,����Ϊ�����У���ǰĿ¼
		MethodTerminate		//��ֹ����,����Ϊ���̾��
	};

public:
	virtual int type(){ return Type; }
	virtual QVariant result() CONVERT_TO_VARIANT(m_vecProcess)
	virtual int execMethod(int method, const QStringList& arguments);

public:
	virtual void clear();

protected:
	virtual void beferQuery();
	virtual void afterQuery();
	virtual void query();

private:
	QVector<SystemProcess>	m_vecProcess;

private:
	typedef struct _processUserName
	{
		quint32 nBeatCount;
		QString processName;
	}ProccessUserName;

	QMap<quint32, ProccessUserName>	m_mapUserName;
};

#endif // QSTATPROCESS_H
