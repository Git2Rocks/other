#ifndef QMUTILCASTRECEIVER_H
#define QMUTILCASTRECEIVER_H

#include "global.h"
#include "qabstractmulticast.h"

class NETWORK_EXPORT QMulticastReceiver : public QObject, public QSharedObject
{
	Q_OBJECT

public:
	QMulticastReceiver(const QString& uid, quint16 port, QObject* view, QObject* parent=0);
	~QMulticastReceiver();

public slots:
	void readDatagram();

private:
	QUdpSocket	m_socket;

	QByteArray	m_buffer;			//ͨ����Ϣ������
	QString		m_uid;				//Ψһ��ʶ
	quint16		m_nPort;

	QObject*	m_pView;
};

#endif // QMUTILCASTRECEIVER_H
