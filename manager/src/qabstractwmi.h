#ifndef QABSTRACTWMI_H
#define QABSTRACTWMI_H

#include <qglobal.h>
#include <QMutex>
#include <QStringList>
#include <QVector>
#include <QVariant>

#ifdef Q_OS_WIN

#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

#endif	//Q_OS_WIN

class QAbstractWmi
{
public:
	QAbstractWmi();
	virtual ~QAbstractWmi();

	enum ExecMethodResult
	{
		ExecMethodComInvalid=-2,	//COM��ʼ��ʧ��
		ExecMethodInvalid=-1,		//��Ч����
		ExecMethodFailed=0,
		ExecMethodSucceed,
		ExecMethodAccessDenied,
		ExecMethodInsufficientPrivilege,
		ExecMethodPathNotFound,
		ExecMethodInvalidParameter
	};

public:
	virtual int type()=0;
	virtual QVariant result()=0;

public:
	virtual void clear();
	virtual QVariant exec(IWbemServices* service);
	virtual int execMethod(IWbemServices* service, int method, const QStringList& arguments);

protected:
	virtual void beferQuery();	//ִ�в�ѯ������ǰ��Ҫ��ɵĹ���
	virtual QStringList query()=0;		//�����ѯ��Ϣ�б�
	virtual void record(IWbemClassObject* object, IWbemServices* service, int index)=0;	//���һ����¼����¼�ü�¼
	virtual void afterQuery();	//��ѯ��Ϻ���Ҫִ�еĲ���

protected:
	quint16 findUInt16(IWbemClassObject* object, LPCWSTR wszName);
	quint32 findUInt32(IWbemClassObject* object, LPCWSTR wszName);
	quint64 findUInt64(IWbemClassObject* object, LPCWSTR wszName);
	QString findString(IWbemClassObject* object, LPCWSTR wszName);
	bool findBoolean(IWbemClassObject* object, LPCWSTR wszName);
	QVector<QString> findStringArray(IWbemClassObject* object, LPCWSTR wszName);
	QVector<quint16> findUInt16Array(IWbemClassObject* object, LPCWSTR wszName);
	qreal findReal(IWbemClassObject* object, LPCWSTR wszName);

private:
	virtual void indicate(IEnumWbemClassObject* enumerator, IWbemServices* service, int index);

protected:
	QMutex m_mutex;
};

#endif // QABSTRACTWMI_H
