#ifndef QSERVERMANAGER_H
#define QSERVERMANAGER_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QMutex>
#include <QTimer>
#include <QMultiHash>
#include <QMetaType>

#include "qutildef.h"
#include "qserver.h"

class NETWORK_EXPORT QServerManager : public QObject
{
	Q_OBJECT

public:
	~QServerManager();

	enum RegisterStatus
	{
		RegisterSuccess=0,
		RegisterFail,
		ServerExisting
	};

	typedef struct _localServer
	{
		ServerInfo	info;	//����������Ϣ
		quint16		port;	//���ض˿ں�

		ServerInfo	server;	//���ط�������Ϣ
		QList<QServerPtr>	servers;		//���ط������б�
	}LocalServer;

	typedef struct _remoteServer 
	{
		ServerInfo	server;

		int	heartbeat;		//������ʱ����������ʱ���������趨�����󣬱�ʾ����������˳�
	}RemoteServer;

protected:
	QServerManager(QObject *parent=0);

public:
	static QServerManager*	instance();
	static void destroy();

	static bool checkConnect(const ServerInfo& source, const ServerInfo& target, Server* sourceServer, Server* targetServer);
	static bool findFirstServer(const ServerInfo& info, Server* server);
	static bool canConnected(const ServerInfo& info, const Server& server);

public:
	QServerManager::RegisterStatus registerServer(const QString& hardwareAddr, const Server& server);
	QServerManager::RegisterStatus registerLocalServer();	//���ڽ��̼�ͨ��
	void unregisterServer(const QString& hardwareAddr, const Server& server);

	void unregisterAll();

	void addRemoteServer(const ServerInfo& serverInfo);

public:
	const ServerInfo localServer() const;
	const ServerInfo& localAddr() const;
	const QList<QServerPtr>& localServerList() const;

	const QMultiHash<QString, RemoteServer>& remoteServer() const;

	void checkLocalAddress();	//��Ȿ������
	void setPort(quint16 port);

public:
	void informStatusChanged(quint64 sign);
	
signals:
	void remoteServerComing(const ServerInfo& server);
	void remoteServerQuit(const ServerInfo& server);

private slots:
	void timeout();

private:
	LocalServer		m_localServer;
	
	QServerPtr		m_pLocalServer;			//�ػ���ַ������,���ڽ��̼�ͨѶ

	QTimer			m_timer;		//��ʱ��ʱ��
	QMultiHash<QString, RemoteServer>	m_multiHashRemoteServer;	//Զ�̿��÷������б�

private:
	QMutex	m_mutex;

private:
	static QMutex				m_smutex;
	static QServerManager*		m_pServerManager;
};

#endif // QSERVERMANAGER_H
