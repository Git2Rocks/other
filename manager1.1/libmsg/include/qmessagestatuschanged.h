#ifndef QMESSAGESYSTEM_H
#define QMESSAGESYSTEM_H

#include <QObject>
#include <QRunnable>

#include "qmessageextern.h"

/**
*	@Desc ���������״̬�ı�ͨ�洫���ʽ
*	@Author zlb
*	@Time 2012-2-16
*
*	InformStatusChanged:			InformStatusChanged|�����״̬�ı����루uint64��
**/

class MSG_EXPORT QMessageStatusChanged : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageStatusChanged(QObject *parent=0);
	~QMessageStatusChanged();

	enum {Type=MSG_STATUS_CHANGED};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);
};

class MSG_EXPORT QMessageStatusChangedRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageStatusChangedRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageStatusChangedRunnable();

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QObject* sender, int msgType, QByteArray buffer);

private:
	QObject*	m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGESYSTEM_H
