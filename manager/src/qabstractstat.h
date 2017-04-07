#ifndef QABSTRACTSTAT_H
#define QABSTRACTSTAT_H

#include <qglobal.h>
#include <QMutex>
#include <QStringList>
#include <QVariant>

#include "define.h"

class QAbstractStat
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

#endif // QABSTRACTSTAT_H
