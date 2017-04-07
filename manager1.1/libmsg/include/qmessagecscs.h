#ifndef QMESSAGECSCS_H
#define QMESSAGECSCS_H

#include <QObject>
#include <QRunnable>

#include "qmessageextern.h"

/**
*	@Desc H9000�����Ϣ�����ʽ
*	@Author zlb
*	@Time 2012-11-08
*
*	QueryCscsStruct					QueryCscsStruct|�û�ID
*	AnswerCscsStruct				AnswerCscsStruct|�û�ID|ʵʱ���ݿ⳧վ�ṹ
*	QueryCscsStation				QueryCscsStation|�û�ID|��վID
*	AnswerCscsStation				AnswerCscsStation|�û�ID|��վID|״̬(|��վ����ֵ��
*	QueryCscsGroupEigenvalue		QueryCscsGroupEigenvalue|�û�ID|��վID|�豸ID
*	AnswerCscsGroupEigenvalue		AnswerCscsGroupEigenvalue|�û�ID|��վID|״̬(|�豸����ֵ)
*	QueryCscsDataTypeEigenvalue		QueryCscsDataTypeEigenvalue|�û�ID|��վID|�豸ID|��������
*	AnswerCscsDataTypeEigenvalue	AnswerCscsDataTypeEigenvalue|�û�ID|��վID|�豸ID|��������|״̬(|��������ֵ)
**/

class MSG_EXPORT QMessageCscs : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageCscs(QObject *parent=0);
	~QMessageCscs();

	enum {Type=MSG_CSCS};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int msgType, quint32 usrID, QByteArray buffer);
};

class MSG_EXPORT QMessageCscsRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageCscsRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageCscsRunnable();

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

#endif // QMESSAGECSCS_H
