#ifndef QHEARTBEAT_H
#define QHEARTBEAT_H

#include "global.h"
#include "qsharedobject.h"

#include <QByteArray>
#include <QList>
#include <QMultiHash>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>

class NETWORK_EXPORT QHeartBeat : public QObject, public QSharedObject
{
	Q_OBJECT

public:
	QHeartBeat(quint16 beatPort);
	virtual ~QHeartBeat();

public:
	void setPort(quint16 nPort);

	void run();
	void pause();

signals:
	void localNetStatusChanged(bool status);

private slots:
	void sendBeatDatagram();
	void readBeatDatagram();

private:
	QList<QHostAddress> m_listBroadcastAddr;	//�㲥��ַ�б�

	QUdpSocket	m_socketBeat;
	QTimer		m_timerBeat;

	quint16		m_nPort;		//�����㲥��ַ�˿�

	bool		m_bConnecting;	//�����Ƿ����ӵ�����
};

typedef QSharedObjectPtr<QHeartBeat>	QHeartBeatPtr;
#endif
