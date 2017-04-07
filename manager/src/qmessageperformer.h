#ifndef QMESSAGEPERFORMER_H
#define QMESSAGEPERFORMER_H

#include <QObject>
#include <QFile>

#include "qimessage.h"
#include "extern.h"
#include "qclientmanager.h"
#include "qabstractfiletransfer.h"

/**
*	@Desc ���ƻ�ָ����Ϣ�����ʽ
*	@Author zlb
*	@Time 2011-6-29
*
*	QueryConnectToTarget	QueryConnectToTarget|�û�ID|������Ϣ
*	AnswerConnectToTarget	AnswerConnectToTarget|�û�ID|���ӽ���״̬
*	QueryUpload				QueryUpload|�û�ID|�ļ�����|Դ����·����ַ|Ŀ�����������ַ|�����ʽ(�������ļ�)
*	AnswerUpload			AnswerUpload|�û�ID|����״̬|���ݳ���|����((�������ļ���)�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��)
**/

class QTempPerformer;
class QPerformerFileTransfer;
class QMessagePerformer : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessagePerformer(QObject *parent=0);
	~QMessagePerformer();

	enum {Type=MSG_PERFORMER};

	enum MsgType
	{
		QueryConnectToTarget,		//��������Ŀ������֮�������
		AnswerConnectToTarget,
		QueryUpload,				//����Դ�����ϴ��ļ���Ŀ¼��Ŀ������
		AnswerUpload
	};

	enum QueryResult
	{
		QueryConnectToTargetFailed,	//Դ������Ŀ��������������ʧ��
		QueryConnectToTargetSuccess,//�������ӳɹ�
		TargetDisconnected,			//Դ������Ŀ�������Ͽ�����
		QueryUploadDirSuccess,		//�����ϴ��ļ��гɹ�
		QuerySourceDirLost,			//Դ�����ļ��в�����
		QueryTargetMakeDirFail,		//Ŀ�����������ļ���ʧ��
		QuerySourceFileReadLost,	//Դ����δ�ҵ��ļ�
		QuerySourceFileReadFail,	//Դ�������ļ�ʧ��
		QueryTargetCreateFileFail,	//Ŀ�����������ļ�ʧ��
		QuerySourceTransferFileBengin,	//Դ������ʼ�����ļ�
		QuerySourceTransferFileFinish,	//Դ������ɴ����ļ�
		QuerySourceTransferFile,	//Դ���������ļ���
		QueryTargetFileWriteLost,	//Ŀ������д�ļ�����������Ѿ��ر�
		QueryTargetFileWriteFail,	//Ŀ������д����ʱ�ļ�ʧ��
		QueryTargetFileWriteSuccess,//Ŀ������д����ʱ�ļ��ɹ�
		QueryUploadFileSuccess,		//Ŀ����������ʱ�ļ�����Ϊ�����ļ��ɹ�
		QueryUploadFileFail,		//Ŀ����������ʱ�ļ�����Ϊ�����ļ�ʧ��
		QueryUploadSymLinkSuccess,	//�����ϴ������ļ������ɹ�
		QueryUploadSymLinkFail		//�����ϴ������ļ�����ʧ��
	};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QConnection* sender, QByteArray buffer, QObject* view=0);

private:
	QMap<QConnection*, QTempPerformer*>		m_mapPerformer;
};

class QTempPerformer : public QObject, public QAbstractFileTransfer
{
	Q_OBJECT

public:
	QTempPerformer(QConnection* sender, QObject* view, QObject* parent=0);
	virtual ~QTempPerformer();

public:
	void parse(const QByteArray& buffer);

private slots:
	void connected(QClient* client);
	void disconnected(QClient* client);

	void transferStatus(int status, QByteArray buffer);

private:
	void sendMessageToController(quint32 userID, int msgType, int status, const QByteArray& buffer="");	//������Ϣ�����ƶ�

private:
	typedef struct _clientInfo 
	{
		QClient*	client;		//Դ������Ŀ����������socket
		QPerformerFileTransfer*	transferInterface;

		bool	queryConnect;	//�Ƿ�����Դ������Ŀ��������������
	}ClientInfo;

private:
	QConnection*	m_pSender;	//��������Դ��������socket
	QObject*		m_pView;

	QClientManager*		m_pClientManager;		//���ڿ���Դ������Ŀ������ͨѶ

	QMap<quint32, ClientInfo>	m_mapClient;	//keyΪ���ƶ�UsrID
};

class QPerformerFileTransfer : public QObject, public QAbstractFileTransfer
{
	Q_OBJECT

public:
	QPerformerFileTransfer(QObject* parent=0);
	~QPerformerFileTransfer();

public:
	void setSourceDir(const QString& dir);
	void setSourceFile(QFile* file);
	quint32 user();

signals:
	void transferStatus(int status, QByteArray buffer="");

protected:
	virtual void recvUpload(int flag);
	virtual void recvUploadFile(int flag);

private:
	void transferFile();

private:
	quint32		m_nUsrID;		//Դ����UsrID��������Ŀ������ͨѶ

	QFile*		m_pFile;		//�����ļ�����
	QString		m_strDir;		//Դ������ǰ�ϴ�Ŀ¼
};

#endif // QMESSAGEPERFORMER_H
