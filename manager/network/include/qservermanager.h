#ifndef QSERVERMANAGER_H
#define QSERVERMANAGER_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QMutex>
#include <QTimer>
#include <QMultiHash>
#include <QMetaType>

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

	typedef struct _server 
	{
		QString		addr;			//������ip��ַ
		quint32		netmask;		//��������
		quint16		port;			//�������˿ں�,ʹ��ͬһ�˿�
	}Server;

	typedef struct _serverInfo
	{
		QString		hostName;
		QMap<QString, QVector<Server> > servers;	//�������ַ��Ϊkey

		int	heartbeat;		//������ʱ����������ʱ��������ʮ�κ󣬱�ʾ����������˳�
		
		int	count;
	}ServerInfo;

protected:
	QServerManager(QObject *parent=0);

public:
	static QServerManager*	instance();
	static void destroy();

	static bool checkConnect(const QServerManager::ServerInfo& source, const QServerManager::ServerInfo& target,
		QString& sourceAddr, QString& targetAddr);

	static QString findFirstAddress(const QServerManager::ServerInfo& info, bool hasPort=false);

public:
	QServerManager::RegisterStatus registerServer(const QString& hardwareAddr, const Server& server);
	void unregisterServer(const QString& hardwareAddr, const Server& server);

	void unregisterAll();

	void addRemoteServer(const QServerManager::ServerInfo& serverInfo);

	bool canConnected(const Server& server);

public:
	const ServerInfo& localServer() const;
	const ServerInfo& localAddr() const;

	const QMultiHash<QString, QServerManager::ServerInfo>& remoteServer() const;

	void checkLocalAddress();	//��Ȿ������
	
signals:
	void remoteServerComing(const QServerManager::ServerInfo& server);
	void remoteServerQuit(const QServerManager::ServerInfo& server);

private slots:
	void timeout();

private:
	static QMutex				m_mutex;
	static QServerManager*		m_pServerManager;

	ServerInfo		m_localAddr;		//����������Ϣ

	ServerInfo		m_server;
	QList<QServer*>	m_listServer;		//���ط������б�

	QTimer				m_timer;		//��ʱ��ʱ��
	QMultiHash<QString, ServerInfo>	m_multiHashRemoteServer;	//Զ�̿��÷������б�
};

NETWORK_EXPORT bool operator==(const QServerManager::ServerInfo& source, const QServerManager::ServerInfo& target);
NETWORK_EXPORT QDataStream& operator<<(QDataStream& out, const QServerManager::ServerInfo& info);
NETWORK_EXPORT QDataStream& operator>>(QDataStream& in, QServerManager::ServerInfo& info);

Q_DECLARE_METATYPE(QServerManager::Server)
Q_DECLARE_METATYPE(QServerManager::ServerInfo)

#endif // QSERVERMANAGER_H
