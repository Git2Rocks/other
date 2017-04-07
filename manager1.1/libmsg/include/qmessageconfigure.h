#ifndef QMESSAGECONFIGURE_H
#define QMESSAGECONFIGURE_H

#include <QObject>
#include <QRunnable>
#include <QVector>

#include "qmessageextern.h"

/**
*	@Desc �����ʽ
*	@Author zlb
*	@Time 2013-04-07
*
*	QuerySyncAssociationConfigure	QuerySyncAssociationConfigure|�û�ID
*	AnswerSyncAssociationConfigure	AnswerSyncAssociationConfigure|�û�ID|�ļ�����������Ϣ
*	QueryWriteSyncAssociateionConfig	QueryWriteSyncAssociateionConfig|�û�ID|�ļ�����������Ϣ
*	AnswerWriteSyncAssociateionConfig	AnswerWriteSyncAssociateionConfig|�û�ID|����״̬
*	QueryExecSyncConfigureCommand	QueryExecSyncConfigureCommand|�û�ID|����Ŀ¼|�ļ���Ϣ
*	AnswerExecSyncConfigureCommand	AnswerExecSyncConfigureCommand|�û�ID|״̬��ԭ��
**/

class MSG_EXPORT QMessageConfigure : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageConfigure(QObject *parent=0);
	~QMessageConfigure();

	enum {Type=MSG_CONFIGURE};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int ackType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer);
};

class MSG_EXPORT QMessageConfigureRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageConfigureRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageConfigureRunnable();

signals:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer=QByteArray());

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

private:
	QObject*		m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGECONFIGURE_H
