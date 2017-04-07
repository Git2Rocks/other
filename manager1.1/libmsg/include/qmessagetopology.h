#ifndef QMESSAGETOPOLOGY_H
#define QMESSAGETOPOLOGY_H

#include <QObject>
#include <QRunnable>

#include "qmessageextern.h"

/**
*	@Desc ���������������Ϣ�����ʽ
*	@Author zlb
*	@Time 2012-3-27
*
*	QueryTopology:			QueryTopology|�û�ID
*	AnswerTopology:			AnswerTopology|�û�ID|����״̬(|�������������Ϣ)
**/

class MSG_EXPORT QMessageTopology : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageTopology(QObject *parent=0);
	~QMessageTopology();

	enum {Type=MSG_TOPOLOGY};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int ackType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer);
};

class MSG_EXPORT QMessageTopologyRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageTopologyRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageTopologyRunnable();

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QObject* sender, int msgType, quint32 usrID, QByteArray buffer);

private:
	QObject*		m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGETOPOLOGY_H
