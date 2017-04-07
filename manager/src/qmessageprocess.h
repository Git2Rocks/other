#ifndef QMESSAGEPROCESS_H
#define QMESSAGEPROCESS_H

#include <QObject>
#include <QRunnable>

#include "qimessage.h"
#include "extern.h"

/**
*	@Desc �����ϵͳ������Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-15
*
*	QueryProcess			QueryProcess
*	AnswerProcess			QueryProcess|����״̬(|�����ϵͳ������Ϣ)
*	QueryCreateProcess		QueryCreateProcess|������
*	AnswerCreateProcess		AnswerCreateProccess|������|ִ�н��
*	QueryTerminateProcess	QueryTerminateProcess|����ID
*	AnswerTerminateProcess	AnswerTerminateProcess|����ID|��ֹ״̬
*	QueryUnrefProcess		QueryUnrefProcess
**/

class QMessageProcess : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageProcess(QObject *parent=0);
	~QMessageProcess();

	enum {Type=MSG_SYSTEM_PROCESS};

	enum MsgType
	{
		QueryProcess=0,
		AnswerProcess,
		QueryCreateProcess,
		AnswerCreateProcess,
		QueryTerminateProcess,
		AnswerTerminateProcess,
		QueryUnrefProcess			//������Ҫ������Ϣ
	};

	enum QueryResult
	{
		QueryFailed=0,		//��ȡ�����ϵͳ������Ϣʧ��
		QuerySucceed		//��ȡ�����ϵͳ������Ϣ�ɹ�
	};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QConnection* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QConnection* sender, int msgType, QByteArray buffer);
};

class QMessageProcessRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageProcessRunnable(QConnection* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageProcessRunnable();

public:
	void setArg(QConnection* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QConnection* sender, int msgType, QByteArray buffer=QByteArray());

private:
	QConnection*	m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGEPROCESS_H
