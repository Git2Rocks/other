#ifndef QMESSAGEMEMORY_H
#define QMESSAGEMEMORY_H

#include <QObject>
#include <QRunnable>

#include "qimessage.h"
#include "extern.h"

/**
*	@Desc ������ڴ���Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-26
*
*	QueryPhysicalMemory		QueryPhysicalMemory
*	AnswerPhysicalMemory	AnswerPhysicalMemory|����״̬(|�����ϵͳ�ڴ���Ϣ)
*	QuerySystemMemory		QuerySystemMemory
*	AnswerSystemMemory		AnswerSystemMemory|����״̬(|�����ϵͳ�ڴ�ʹ����Ϣ)
*	QueryUnrefSystemMemory	QueryUnrefSystemMemory
**/

class QMessageMemory : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageMemory(QObject *parent=0);
	~QMessageMemory();

	enum {Type=MSG_SYSTEM_MEMORY};

	enum MsgType
	{
		QueryPhysicalMemory=0,
		AnswerPhysicalMemory,
		QuerySystemMemory,
		AnswerSystemMemory,
		QueryUnrefSystemMemory
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

class QMessageMemoryRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageMemoryRunnable(QConnection* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageMemoryRunnable();

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

#endif // QMESSAGEMEMORY_H
