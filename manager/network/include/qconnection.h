#ifndef QCONNECTION_H
#define QCONNECTION_H

#include "common.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QMutex>

class NETWORK_EXPORT QConnection : public QObject
{
	Q_OBJECT

	enum ConnectionStatus
	{
		WaitingForMessage=0,
		ReadingMessage,
		ReadyForUse,
		Quit
	};

public:
	QConnection(QTcpSocket* socket, QObject *parent=0);
	~QConnection();

public:
	QHostAddress peerAddress();
	quint16 peerPort();

public:
	void ref();
	void unref();

	bool isQuit();

public slots:
	bool sendMessage(const QByteArray& buffer, int msgType);

private slots:
	void readyRead();
	void disconnected();

signals:
	void recvMessage(QConnection* sender, QByteArray buffer);
	void deleteConnection(QTcpSocket* socket, QHostAddress addr, quint16 port);

private:
	QTcpSocket*		m_pSocket;			//�����׽���

	ConnectionStatus	m_eStatus;	//ͨѶ״̬
	QByteArray	m_buffer;			//ͨ����Ϣ������

	int		m_nNextBlockSize;		//ͨ����Ϣ���С

	QMutex	m_mutex;
	int		m_nRef;			//�������ô���
};

#endif // QCONNECTION_H
