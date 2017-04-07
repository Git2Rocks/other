#ifndef QMESSAGEPROCESSOR_H
#define QMESSAGEPROCESSOR_H

#include <QRunnable>

#include "common.h"
#include "qmessageextern.h"
#include "qimessage.h"

/**
*	@Desc �����ϵͳ��������Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-22
*
*	QueryProcessor			QueryProcessor|�û�ID
*	AnswerProcessor			AnswerProcessor|�û�ID|����״̬(|�����ϵͳ��������Ϣ)
*	QueryRuntimeProcessor	QueryRuntimeProcessor|�û�ID
*	AnswerRuntimeProcessor	AnswerRuntimeProcessor|�û�ID|����״̬(|�����ϵͳ����������״̬��Ϣ)
**/

class MSG_EXPORT QMessageProcessor : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageProcessor(QObject* parent=0);
	virtual ~QMessageProcessor();

	enum {Type=MSG_PROCESSOR};

public:
	virtual int type() const	{return Type;}

	virtual QByteArray query(int ackType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer);
};

class MSG_EXPORT QMessageProcessorRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageProcessorRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageProcessorRunnable();

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer=QByteArray());

private:
	QObject*		m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGEPROCESSOR_H
