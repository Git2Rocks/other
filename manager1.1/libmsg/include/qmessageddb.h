#ifndef QMESSAGEDDB_H
#define QMESSAGEDDB_H

#include <QObject>
#include <QRunnable>

#include "qmessageextern.h"

/**
*	@Desc �ֲ�ʽ���ݿ���Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-4-24
*
*	QueryInformDdbConnection:		QueryInformDdbConnection|�û�ID|�û�UID
*	AnswerInformDdbConnection		AnswerInformDdbConnection|�û�ID
*	QueryUploadPrivilegeData		QueryUploadPrivilegeData|�û�ID|������|�Ƿ���Ҫ��������
*	AnswerUploadPrivilegeData		AnswerUploadPrivilegeData|�û�ID|������
*	QueryCheckPrivilege				QueryCheckPrivilege|�û�ID|�û���|�û�����
*	AnswerCheckPrivilege			AnswerCheckPrivilege|�û�ID|�û���|��ѯ״̬��|�û���Ϣ��
*	QueryPrivileges					QueryPrivileges|�û�ID
*	AnswerPrivileges				AnswerPrivileges|�û�ID|������
*	QueryCreateGroup				QueryCreateGroup|�û�ID|�û�����
*	AnswerCreateGroup				AnswerCreateGroup|�û�ID|����״̬|�û�����|�û�����Ϣ
*	QueryDeleteGroup				QueryDeleteGroup|�û�ID|����
*	AnswerDeleteGroup				AnswerDeleteGroup|�û�ID|����|�û�����Ϣ
*	QueryCreateUser					QueryCreateUser|�û�ID|����|�û���Ϣ
*	AnswerCreateUser				AnswerCreateUser|�û�ID|����״̬|����|�û���|�û�����Ϣ
*	QueryDeleteUser					QueryDeleteUser|�û�ID|�û���
*	AnswerDeleteUser				AnswerDeleteUser|�û�ID|�û���|�û�����Ϣ
*	QueryModifyUserPrivilege		QueryModifyUserPrivilege|�û�ID|�û���Ϣ
*	AnswerModifyUserPrivilege		AnswerModifyUserPrivilege|�û�ID|״̬|����|�û���|�û�����Ϣ
*	QueryModifyUserPassword			QueryModifyUserPassword|�û�ID|�û���|�û���������
*	AnswerModifyUserPassword		AnswerModifyUserPassword|�û�ID|״̬|�û���(|�û���Ϣ)
*	UpdateUserPrivilege				UpdateUserPrivilege|�û�ID(-1)|��־λ(�û���|�û���Ϣ)
**/

class MSG_EXPORT QMessageDdb : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageDdb(QObject *parent=0);
	~QMessageDdb();

	enum {Type=MSG_DDB};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int msgType, quint32 usrID, QByteArray buffer);
};

class MSG_EXPORT QMessageDdbRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageDdbRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageDdbRunnable();

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

#endif // QMESSAGEDDB_H
