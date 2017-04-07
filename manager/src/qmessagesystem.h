#ifndef QMESSAGESYSTEM_H
#define QMESSAGESYSTEM_H

#include <QObject>
#include <QRunnable>

#include "qimessage.h"
#include "extern.h"

/**
*	@Desc ���������ϵͳ��Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-12
*
*	QueryOperatingSystem:			QueryOperatingSystem
*	AnswerComputerSystem:			AnswerComputerSystem|����״̬(|���������ϵͳ��Ϣ)
**/

class QMessageSystem : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageSystem(QObject *parent=0);
	~QMessageSystem();

	enum {Type=MSG_SYSTEM};

	enum MsgType
	{
		QueryOperatingSystem=0,
		AnswerOperatingSystem
	};

	enum QueryResult
	{
		QueryFailed=0,		//��ȡ���������ϵͳ��Ϣʧ��
		QuerySucceed		//��ȡ���������ϵͳ��Ϣ�ɹ�
	};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QConnection* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QConnection* sender, int msgType, QByteArray buffer);
};

class QMessageSystemRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageSystemRunnable(QConnection* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageSystemRunnable();

public:
	void setArg(QConnection* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QConnection* sender, int msgType, QByteArray buffer);

private:
	QConnection*	m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGESYSTEM_H
