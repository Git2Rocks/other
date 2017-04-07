#ifndef QWMIPROCESS_H
#define QWMIPROCESS_H

/**
*	@Desc	��ȡ������Ϣ
*	@Author zlb
*	@Time	2011-4-14
**/

#include <QObject>
#include <QVector>
#include <QMap>

#include "qabstractwmi.h"
#include "extern.h"
#include "define.h"

class QWmiProcess : public QObject, public QAbstractWmi
{
	Q_OBJECT

public:
	QWmiProcess(QObject *parent=0);
	~QWmiProcess();

	enum {Type=WMI_TYPE_PROCESS};

	enum MethodType
	{
		MethodCreate=0,		//��������,����Ϊ�����У���ǰĿ¼
		MethodTerminate		//��ֹ����,����Ϊ���̾��
	};

public:
	virtual int type(){ return Type; }
	virtual QVariant result() CONVERT_TO_VARIANT(m_vecProcess)
	virtual int execMethod(IWbemServices* service, int method, const QStringList& arguments);

public:
	virtual void clear();

protected:
	virtual void beferQuery();
	virtual QStringList query();
	virtual void record(IWbemClassObject* object, IWbemServices* service, int index);
	virtual void afterQuery();

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

#endif // QWMIPROCESS_H
