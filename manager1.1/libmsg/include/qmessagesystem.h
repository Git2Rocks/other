#ifndef QMESSAGESYSTEM_H
#define QMESSAGESYSTEM_H

#include <QObject>
#include <QRunnable>

#include "qmessageextern.h"

/**
*	@Desc ���������ϵͳ��Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-12
*
*	QueryOperatingSystem:			QueryOperatingSystem|�û�ID
*	AnswerComputerSystem:			AnswerComputerSystem|�û�ID|����״̬(|���������ϵͳ��Ϣ)
**/

class MSG_EXPORT QMessageSystem : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageSystem(QObject *parent=0);
	~QMessageSystem();

	enum {Type=MSG_SYSTEM};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int ackType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer);
};

class MSG_EXPORT QMessageSystemRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageSystemRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageSystemRunnable();

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer);

private:
	QObject*		m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGESYSTEM_H
