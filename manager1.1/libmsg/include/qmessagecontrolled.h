#ifndef QMESSAGCONTROLED_H
#define QMESSAGCONTROLED_H

#include <QObject>
#include <QRunnable>

#include "qmessageextern.h"

/**
*	@Desc ���ƻ�ָ����Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-6-29
*
*	QueryConnectToTarget		QueryConnectToTarget|�û�ID|������Ϣ
*	AnswerConnectToTarget		AnswerConnectToTarget|�û�ID|���ӽ���״̬
*	QueryUploadDirToTarget		QueryUploadDirToTarget|�û�ID|�ļ�����|Դ����Ŀ¼����·��|Ŀ���������Ա����ַ
*	AnswerUploadDirToTarget		AnswerUploadDirToTarget|�û�ID|�ļ��д���״̬(|Դ����Ŀ¼·��|Ŀ�����������ַ|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��)
*	QueryUploadFileToTarget		QueryUploadFileToTarget|�û�ID|�ļ�����|�ļ�����·��|�������·��|�����ʽ
*	AnswerUploadFileToTarget	AnswerUploadFileToTarget|�û�ID|�ϴ�״̬(|�ϴ��ļ����ݳ���)
*	QueryUploadSymlinkToTarget	QueryUploadSymlinkToTarget|�û�ID|�����ļ�����|Դ����Ŀ¼����·��|Ŀ���������Ա����ַ
*	AnswerUploadSymlinkToTarget	AnswerUploadSymlinkToTarget|�û�ID|�����ļ�����״̬
*	QueryInterruptTransferToTarget	QueryInterruptTransferToTarget|�û�ID
*	AnswerInterruptTransferToTarget	AnswerInterruptTransferToTarget|�û�ID|�ж�״̬
*	QueryUploadSlientDirToTarget`	QueryUploadSlientDirToTarget|�û�ID|�ļ�����|Դ����Ŀ¼����·��|Ŀ���������Ա����ַ
*	AnswerUploadSlientDirToTarget	AnswerUploadSlientDirToTarget|�û�ID|�ļ��д���״̬(|Դ����Ŀ¼·��|Ŀ�����������ַ|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��)
*	QueryUploadSlientSymlinkToTarget	QueryUploadSlientSymlinkToTarget|�û�ID|�����ļ�����|Դ����Ŀ¼����·��|Ŀ���������Ա����ַ
*	AnswerUploadSlientSymlinkToTarget	AnswerUploadSlientSymlinkToTarget|�û�ID|�����ļ�����״̬
*	QueryUploadSlientFileToTarget	QueryUploadSlientFileToTarget|�û�ID||�ļ�����|�ļ�����·��|�������·��|�����ʽ
*	AnswerUploadSlientFileToTarget	AnswerUploadSlientFileToTarget|�û�ID|�ϴ�״̬(|�ϴ��ļ����ݳ���)
*	QueryExecSyncCommandToTarget	QueryExecSyncCommandToTarget|�û�ID|��¼���|����Ŀ¼|�ļ���
*	AnswerExecSyncCommandToTarget	AnswerExecSyncCommandToTarget|�û�ID|ִ��״̬|�������
**/

class MSG_EXPORT QMessageControlled : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageControlled(QObject *parent=0);
	~QMessageControlled();

	enum {Type=MSG_CONTROLLED};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);
};

class MSG_EXPORT QMessageControlledRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageControlledRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageControlledRunnable();

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

private:
	QObject*		m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGCONTROLED_H
