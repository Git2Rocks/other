#ifndef QABSTRACTALARM_H
#define QABSTRACTALARM_H

#include <QVector>
#include <QMutex>
#include <QVariant>
#include <QDateTime>

#include "global.h"
#include "qsharedobject.h"

enum Alarm
{
	H9000AlarmEvent=0
};

class UTIL_EXPORT QAbstractAlarm : public QSharedObject
{
public:
	QAbstractAlarm();
	virtual ~QAbstractAlarm();

	enum AlarmUpdateIntervalFlags
	{
		AlarmUpdateIntervalL1=1,
		AlarmUpdateIntervalL2=(1<<1)
	};

public:
	void open();
	void close();

public:
	virtual int type() const=0;

	virtual void initialize();
	bool initialized();

	virtual void destroy();

public:
	void alarm(const QVariant& var);

protected:
	virtual int trigger(const QVariant& var, bool L1, bool L2)=0;

protected:
	QMutex	m_mutex;
	bool	m_bInit;

	int		m_nIntervalL1;	//���ؾ��沥�����
	int		m_nIntervalL2;	//��ͨ���沥�����

	QDateTime	m_lastDateTimeL1;		//��һ�����ز�����ʱ��
	QDateTime	m_lastDateTimeL2;		//��һ����ͨ������ʱ��

private:
	bool	m_bOpened;
};

typedef QSharedObjectPtr<QAbstractAlarm> QAbstractAlarmPtr;

typedef void (*CreateAlarmInstanceFunc)(QVector<QAbstractAlarmPtr>&);		//Ԥ��ϵͳ��̬������ṩ�Ľӿ�

#endif // QABSTRACTALARM_H
