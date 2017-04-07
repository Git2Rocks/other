#ifndef QCONNECTION_H
#define QCONNECTION_H

#include "common.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QMutex>

#include "qsharedobject.h"

class NETWORK_EXPORT QConnection : public QObject, public QSharedObject
{
	Q_OBJECT

public:
	QConnection(QTcpSocket* socket, QObject *parent=0);
	~QConnection();

public:
	enum ConnectionStatus
	{
		WaitingForMessage=0,
		ReadingMessage,
		ReadyForUse,
		Quit
	};

public:
	QHostAddress peerAddress();
	quint16 peerPort();

	QTcpSocket*	connectionSocket();

public:
	bool isQuit();

public slots:
	Q_INVOKABLE bool sendMessage(const QByteArray& buffer, int msgType);
	Q_INVOKABLE bool addReceiver(quint32 usrID, int msgType);
	Q_INVOKABLE bool removeReceiver(quint32 usrID, int msgType);

public slots:
	void readyRead();
	Q_INVOKABLE void disconnected();

private:
	QByteArray addHeaderToPacket(const QByteArray& buffer, int msgType);

signals:
	void recvMessage(QConnection* sender, QByteArray buffer);
	void deleteConnection(QConnection* connection);

private:
	QTcpSocket*		m_pSocket;			//�����׽���,��Ҫ�ֶ�ɾ��

	ConnectionStatus	m_eStatus;	//ͨѶ״̬
	QByteArray	m_buffer;			//ͨ����Ϣ������

	int		m_nEncryptType;			//��������
	int		m_nNextBlockSize;		//ͨ����Ϣ���С

	bool	m_bLock;				//���ڴ�����Ϣ����������

	QMutex	m_mutex;
};

typedef QSharedObjectPtr<QConnection>	QConnectionPtr;

#endif // QCONNECTION_H
