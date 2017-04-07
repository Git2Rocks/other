#ifndef QABSTRACTSTAT_H
#define QABSTRACTSTAT_H

#include "global.h"

#include <QMutex>
#include <QStringList>
#include <QVariant>

#include "qsharedobject.h"

class UTIL_EXPORT QAbstractStat : public QSharedObject
{
public:
	QAbstractStat();
	virtual ~QAbstractStat();

	enum ExecMethodResult
	{
		ExecMethodInvalid=-1,		//��Ч����
		ExecMethodFailed=0,
		ExecMethodSucceed,
		ExecMethodAccessDenied,
		ExecMethodInsufficientPrivilege,
		ExecMethodPathNotFound,
		ExecMethodInvalidParameter,
		ExecMethodUnfinished
	};

public:
	virtual int type()=0;
	virtual QVariant result()=0;

public:
	virtual void init();
	virtual void clear();

	virtual QVariant exec();
	virtual int execMethod(int method, const QStringList& arguments);

protected:
	virtual void beferQuery();	//ִ�в�ѯ������ǰ��Ҫ��ɵĹ���
	virtual void afterQuery();	//��ѯ��Ϻ���Ҫִ�еĲ���

	virtual void query()=0;

protected:
	QMutex	m_mutex;
};

typedef QSharedObjectPtr<QAbstractStat> QAbstractStatPtr;

typedef void (*CreateStatInstanceFunc)(QVector<QAbstractStatPtr>& instances);		//windows mib�ද̬������ṩ�Ľӿ�

#endif // QABSTRACTSTAT_H
