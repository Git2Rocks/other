#ifndef QMESSAGEPROCESS_H
#define QMESSAGEPROCESS_H

#include <QObject>
#include <QRunnable>

#include "qimessage.h"
#include "qmessageextern.h"

/**
*	@Desc �����ϵͳ������Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-15
*	@modify	2012-2-24
*
*	QueryRefProcess			QueryRefProcess|�û�ID
*	QueryUnrefProcess		QueryUnrefProcess|�û�ID
*	QueryProcess			QueryProcess|�û�ID
*	AnswerProcess			QueryProcess|�û�ID|����״̬(|�����ϵͳ������Ϣ|�����ڴ��С)
*	QueryCreateProcess		QueryCreateProcess|�û�ID|������
*	AnswerCreateProcess		AnswerCreateProccess|�û�ID|������|ִ�н��
*	QueryTerminateProcess	QueryTerminateProcess|�û�ID|����ID
*	AnswerTerminateProcess	AnswerTerminateProcess|�û�ID|����ID|��ֹ״̬
**/

class MSG_EXPORT QMessageProcess : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageProcess(QObject *parent=0);
	~QMessageProcess();

	enum {Type=MSG_SYSTEM_PROCESS};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int ackType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer);
};

class MSG_EXPORT QMessageProcessRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageProcessRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageProcessRunnable();

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

#endif // QMESSAGEPROCESS_H
