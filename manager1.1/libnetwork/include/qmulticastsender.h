#ifndef QMUTILCASTSENDER_H
#define QMUTILCASTSENDER_H

#include <QUdpSocket>
#include <QByteArray>

#include "global.h"
#include "qabstractmulticast.h"

class NETWORK_EXPORT QMulticastSender : public QObject, public QSharedObject
{
	Q_OBJECT

public:
	QMulticastSender(const QString& uid, quint16 port, QObject* parent=0);
	~QMulticastSender();

public:
	const QString& uid() const
	{
		return m_uid;
	}

	void sendDatagram(int msgType, const QString& uid="", const QByteArray& datagram="");	//uid="" �����������г�Ա

private:
	QString		m_uid;		//����Ψһ��ʶ
	quint16		m_nPort;	//�˿ں�

	QUdpSocket	m_socket;
};

typedef QSharedObjectPtr<QMulticastSender>	QMulticastSenderPtr;

#endif // QMUTILCASTSENDER_H
