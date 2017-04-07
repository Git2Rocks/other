#ifndef QMESSAGEMEMORY_H
#define QMESSAGEMEMORY_H

#include <QObject>
#include <QRunnable>

#include "qimessage.h"
#include "qmessageextern.h"

/**
*	@Desc ������ڴ���Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-26
*
*	QueryPhysicalMemory		QueryPhysicalMemory|�û�ID
*	AnswerPhysicalMemory	AnswerPhysicalMemory|�û�ID|����״̬(|�����ϵͳ�ڴ���Ϣ)
*	QueryRefSystemMemory	QueryRefSystemMemory|�û�ID
*	QueryUnrefSystemMemory	QueryUnrefSystemMemory|�û�ID
*	QuerySystemMemory		QuerySystemMemory|�û�ID
*	AnswerSystemMemory		AnswerSystemMemory||�û�ID����״̬(|�����ϵͳ�ڴ�ʹ����Ϣ)
**/

class MSG_EXPORT QMessageMemory : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageMemory(QObject *parent=0);
	~QMessageMemory();

	enum {Type=MSG_SYSTEM_MEMORY};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int msgType, quint32 usrID, QByteArray buffer);
};

class MSG_EXPORT QMessageMemoryRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageMemoryRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageMemoryRunnable();

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QObject* sender, int msgType, quint32 usrID, QByteArray buffer=QByteArray());

private:
	QObject*	m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGEMEMORY_H
