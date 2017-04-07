#ifndef QCLIENT_H
#define QCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>

#include "qsharedobject.h"
#include "qconnection.h"
#include "qutildef.h"

#define MAX_RECONNECT_COUNT	2

class NETWORK_EXPORT QClient : public QTcpSocket, public QSharedObject
{
	Q_OBJECT

public:
	QClient(const QHostAddress& serverAddr, quint16 port, QObject *parent=0);
	QClient(const ServerInfo& serverInfo, QObject *parent=0);
	~QClient();

public:
	void connectToHost();
	void closeSocket();

	bool sendMessage(const QByteArray& buffer, int msgType);

public:
	const QHostAddress& serverAddr() const;
	quint16 port() const;

	void setServerAddr(const QString& addr);
	void setPort(quint16 port);

	QConnection* connection();

signals:
	void recvMessage(QConnection* sender, QByteArray buffer);
	void quit();
	void clientStateChanged(QAbstractSocket::SocketState socketState);

public slots:
	void socketStateChanged(QAbstractSocket::SocketState socketState);

private slots:
	void deleteConnection(QConnection* connection);

private:
	QHostAddress	m_serverAddr;		//�����ӵķ�����ip��ַ
	quint16			m_nPort;			//�����ӵķ������˿ں�

	int				m_nIndex;			//��ǰʹ�õķ�����IP����
	QVector<Server>	m_vecAddrs;			//�����ӵ�IP��ַ
	ServerInfo		m_server;			//��������IP��Ϣ

	QConnection*	m_pConnection;
	bool			m_bClosed;			//ͨ�����ر�

private:
	static QMap<QString, Server>	m_sMapFirstServer;	//��������ѡ���ӵ�ַ
};

typedef QSharedObjectPtr<QClient>	QSharedClientPtr;

#endif // QCLIENT_H
