#ifndef QMESSAGECOMPUTERSYSTEM_H
#define QMESSAGECOMPUTERSYSTEM_H

#include <QObject>
#include <QRunnable>

#include "qimessage.h"
#include "extern.h"

/**
*	@Desc �����ϵͳ��Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-13
*
*	QueryComputerSystem:			QueryComputerSystem
*	AnswerComputerSystem:			AnswerComputerSystem|����״̬(|�����ϵͳ��Ϣ)
**/

class QMessageComputerSystem : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageComputerSystem(QObject *parent=0);
	~QMessageComputerSystem();

	enum {Type=MSG_COMPUTER_SYSTEM};

	enum MsgType
	{
		QueryComputerSystem=0,
		AnswerComputerSystem
	};

	enum QueryResult
	{
		QueryFailed=0,		//��ȡ�����ϵͳ��Ϣʧ��
		QuerySucceed		//��ȡ�����ϵͳ��Ϣ�ɹ�
	};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QConnection* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QConnection* sender, int msgType, QByteArray buffer);
};

class QMessageComputerSystemRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageComputerSystemRunnable(QConnection* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageComputerSystemRunnable();

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

#endif // QMESSAGECOMPUTERSYSTEM_H
