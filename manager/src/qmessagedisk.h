#ifndef QMESSAGEDISK_H
#define QMESSAGEDISK_H

#include <QObject>
#include <QRunnable>

#include "qimessage.h"
#include "extern.h"

/**
*	@Desc ������洢�豸��������Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-24
*
*	QueryDiskDrive:			QueryDiskDrive
*	AnswerDiskDrive:		AnswerDiskDrive|����״̬(|�洢�豸��������Ϣ)
*	QueryCDROMDrive:		QueryCDROMDrive
*	AnswerCDROMDrive:		AnswerCDROMDrive|����״̬(|������������Ϣ)
*	QueryLogicalDisk:		QueryLogicalDisk
*	AnswerLogicalDisk:		AnswerLogicalDisk|����״̬(|����������Ϣ)
**/

class QMessageDisk : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageDisk(QObject *parent=0);
	~QMessageDisk();

	enum {Type=MSG_DISK_DRIVE};

	enum MsgType
	{
		QueryDiskDrive=0,
		AnswerDiskDrive,
		QueryCDROMDrive,
		AnswerCDROMDrive,
		QueryLogicalDisk,
		AnswerLogicalDisk
	};

	enum QueryResult
	{
		QueryFailed=0,		//��ȡ���������ϵͳ��Ϣʧ��
		QuerySucceed		//��ȡ���������ϵͳ��Ϣ�ɹ�
	};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QConnection* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QConnection* sender, int msgType, QByteArray buffer);
};

class QMessageDiskRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageDiskRunnable(QConnection* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageDiskRunnable();

public:
	void setArg(QConnection* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

signals:
	void finished(QConnection* sender, int msgType, QByteArray buffer);

private:
	QConnection*	m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGEDISK_H
