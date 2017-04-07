#ifndef QCONTROLLEDVIEW_H
#define QCONTROLLEDVIEW_H

#include <QObject>

#include "qabstractreceiver.h"
#include "qclient.h"
#include "qclientmanager.h"

class QTempPerformer;
class QPerformerFileTransfer;

class NETWORK_EXPORT QControlledView : public QObject
{
	Q_OBJECT

public:
	QControlledView(QObject *parent=0);
	~QControlledView();

public:
	Q_INVOKABLE void queryConnectToTarget(QObject* sender, quint32 usrID, ServerInfo info);
	Q_INVOKABLE void queryUploadDirToTarget(QObject* sender, quint32 usrID, int fileType, QString sourcePath, QString targetPath, bool slient=false);
	Q_INVOKABLE void queryUploadSymlinkToTarget(QObject* sender, quint32 usrID, int fileType, QString sourcePath, QString targetPath, bool slient=false);
	Q_INVOKABLE void queryUploadFileToTarget(QObject* sender, quint32 usrID, int fileType, QString sourcePath, QString targetPath, int format, bool slient=false);
	Q_INVOKABLE void queryInterruptTransferToTarget(QObject* sender, quint32 usrID);
	Q_INVOKABLE void queryExecSyncCommandToTarget(QObject* sender, quint32 usrID, QString workspace, QVector<FileInfo> files);

private:
	QMap<QObject*, QTempPerformer*>		m_mapPerformer;
};

class NETWORK_EXPORT QTempPerformer : public QObject
{
	Q_OBJECT

public:
	QTempPerformer(QObject* sender, QObject* parent=0);
	virtual ~QTempPerformer();

public:
	void queryConnectToTarget(quint32 usrID, const ServerInfo& info);
	void queryUploadDirToTarget(quint32 usrID, int fileType, const QString& sourcePath, const QString& targetPath, bool slient);
	void queryUploadSymlinkToTarget(quint32 usrID, int fileType, const QString& sourcePath, const QString& targetPath, bool slient);
	void queryUploadFileToTarget(quint32 usrID, int fileType, QString sourcePath, QString targetPath, int format, bool slient);
	void queryInterruptTransferToTarget(quint32 usrID);
	void queryExecSyncCommandToTarget(quint32 usrID, const QString& workspace, const QVector<FileInfo>& files);

private slots:
	void connected(QClient* client);
	void connectFailed(QClient* client);
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
	QObject*	m_pSender;	//��������Դ��������socket

	QClientManager*		m_pClientManager;		//���ڿ���Դ������Ŀ������ͨѶ

	QMap<quint32, ClientInfo>	m_mapClient;	//keyΪ���ƶ�UsrID
};

class NETWORK_EXPORT QPerformerFileTransfer : public QObject, public QAbstractReceiver
{
	Q_OBJECT

public:
	QPerformerFileTransfer(QObject* parent=0);
	~QPerformerFileTransfer();

public:
	typedef struct  _task
	{
		quint32 uid;		//���ڿ��ƻ���Դ����֮��ͨѶ

		quint32	usrID;		//Դ����UsrID��������Ŀ������ͨѶ
		
		int fileType;
		
		QString sourcePath;
		QString targetPath;

		int format;
	}Task;

public:
	void addTask(QPerformerFileTransfer::Task& task);
	const QPerformerFileTransfer::Task& task() const;

signals:
	void transferStatus(int status, QByteArray buffer="");

protected:
	virtual void recvUploadDirAndSymlink(int flag);
	virtual void recvUploadFile(int queryFlag, int flag, quint64 size);
	virtual void recvUploadSlientFile(int flag, quint64 size);
	
	virtual void recvCommandKillProcessFail(QString processName, quint32 processId, QString path);
	virtual void recvCommandCreateProcessFail(QString processName);
	virtual void recvCommandFoundProcessesFail();
	virtual void recvCommandFoundCommandFail();
	virtual void recvCommandExecCommand(int flag, QString command);
	virtual void recvCommandFinish();

private:
	void transferFile();

private:
	Task m_task;
};

#endif // QCONTROLLEDVIEW_H
