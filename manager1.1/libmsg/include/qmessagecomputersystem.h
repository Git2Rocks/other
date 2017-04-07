#ifndef QMESSAGECOMPUTERSYSTEM_H
#define QMESSAGECOMPUTERSYSTEM_H

#include <QObject>
#include <QRunnable>

#include "qmessageextern.h"

/**
*	@Desc �����ϵͳ��Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-13
*
*	QueryComputerSystem:			QueryComputerSystem|�û�ID
*	AnswerComputerSystem:			AnswerComputerSystem|�û�ID|����״̬(|�����ϵͳ��Ϣ)
**/

class MSG_EXPORT QMessageComputerSystem : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageComputerSystem(QObject *parent=0);
	~QMessageComputerSystem();

	enum {Type=MSG_COMPUTER_SYSTEM};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int ackType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=NULL);

private slots:
	void finished(QObject* sender, int ackType, quint32 nUsrID, QByteArray buffer);
};

class MSG_EXPORT QMessageComputerSystemRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageComputerSystemRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageComputerSystemRunnable();

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QObject* sender, int ackType, quint32 nUsrID, QByteArray buffer);

private:
	QObject*		m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGECOMPUTERSYSTEM_H
