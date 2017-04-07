#ifndef QMESSAGEPROCESSOR_H
#define QMESSAGEPROCESSOR_H

#include <QRunnable>

#include "common.h"
#include "extern.h"
#include "qimessage.h"

/**
*	@Desc �����ϵͳ��������Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-22
*
*	QueryProcessor			QueryProcessor
*	AnswerProcessor			QueryProcessor|����״̬(|�����ϵͳ��������Ϣ)
*	QueryRuntimeProcessor	QueryRuntimeProcessor
*	AnswerRuntimeProcessor	AnswerRuntimeProcessor|����״̬(|�����ϵͳ����������״̬��Ϣ)
**/

class QMessageProcessor : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageProcessor(QObject* parent=0);
	virtual ~QMessageProcessor();

	enum {Type=MSG_PROCESSOR};

	enum MsgType
	{
		QueryProcessor=0,
		AnswerProcessor,
		QueryRuntimeProcessor,
		AnswerRuntimeProcessor,
		QueryUnrefRuntimeProcessor
	};

	enum QueryResult
	{
		QueryFailed=0,		//��ȡ�����ϵͳ��������Ϣʧ��
		QuerySucceed		//��ȡ�����ϵͳ��������Ϣ�ɹ�
	};

public:
	virtual int type() const	{return Type;}

	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QConnection* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QConnection* sender, int msgType, QByteArray buffer);
};

class QMessageProcessorRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageProcessorRunnable(QConnection* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageProcessorRunnable();

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

#endif // QMESSAGEPROCESSOR_H
