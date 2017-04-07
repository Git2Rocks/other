#ifndef QMULTICASTMSGELECT_H
#define QMULTICASTMSGELECT_H

#include <QObject>
#include <QRunnable>

#include "qmessageextern.h"

/**
*	@Desc ѡ���쵼����Ϣ�����ʽ
*	@Author zlb
*	@Time 2012-8-14
*
*	QueryElectLeader:		QueryElectLeader(����ѡ��leader)
*	AnswerElectLeader:		AnswerElectLeader|Leader��λʱ��|ServerInfo�ṹ
*	QueryVote				QueryVote|���ܲ���
*	AnswerVote				AnswerVote(���Ա�ѡ��Ϊleader)
**/

class MSG_EXPORT QMulticastMsgElect : public QObject, public QIMulticastMsg
{
	Q_OBJECT

public:
	QMulticastMsgElect(QObject *parent=0);
	~QMulticastMsgElect();

	enum {Type=MULTICAST_MSG_ELECT};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, const QByteArray& contents="");
	virtual bool parse(const QString& from, const QByteArray& buffer, QObject* view=0);
};

#endif // QMULTICASTMSGELECT_H
