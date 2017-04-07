#ifndef QLOGICALTOPO_H
#define QLOGICALTOPO_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QTimer>

#include "global.h"
#include "qtraceroute.h"
#include "qrouteprobe.h"
#include "qicmp.h"

#define INVALID_IP_ADDRESS	-1

class TOPOLOGY_EXPORT QLogicalTopo : public QObject
{
	Q_OBJECT

public:
	QLogicalTopo(QObject *parent=0);
	~QLogicalTopo();

public:
	void probe();
	void reprobe();

	void addSegments(quint32 address, bool around);	//���address����,around=true��Ӹ�������һ
	void addSegment(quint32 address);	//���address����

	void findRoutePath();				//����·��·��
	void findGateways(quint32 segment, QVector<quint32> alives);
	void findAlive(quint32 segment);		//���ֻIP

public slots:
	void foundRoutes(QVector<QPair<quint32, int> > routes);
	void foundAlives(quint32 segment, QVector<quint32> alives);
	void foundGateways(QPair<quint32, quint32> gateway);

signals:
	void routesProbed(QVector<QPair<quint32, int> > routes);
	void alivesProbed(quint32 route, quint32 gateway, QVector<quint32> alives);

	void checkAlives();
	void disconnected();

private:
	void init();
	void probeTopo();

	void terminateThread();

	void nextTask();
	void nextAliveTask();

	quint32 firstRoute(quint32 segment);	//��ȡ���ε�ֱ��·������ -1��ʾ��λ����ѡ·������
	bool isFirstRoute(quint32 address);		//��������ѡ·������

private:
	QVector<QPair<quint32, int> > m_routes[2];	//��ѡ·��·��������·��·��

	QMap<quint32, QPair<quint32, quint32> >		m_gateways;		//̽������·��ʱ�����ڱ���������ֱ��·������
	quint32 m_segment;							//̽������·��·��ʱ����������

	QMap<quint32, QVector<quint32> >	m_segments;	//keyΪ����

	QLinkedList<quint32>	m_tasks;
	QPair<quint32, int>		m_task;

	QTraceRoute*	m_pTraceRoute;
	QRouteProbe*	m_pRouteProbe;
	QIcmp*			m_pIcmp;

	bool			m_bReprobe;		//�Ƿ�����̽��

private:
	enum ProbeFlag
	{
		ProbeFlagInvalid=-1,
		ProbeFirstRoutes,		//̽����ѡ·��
		ProbeRoutes,			//̽������·��
		ProbeAlives,
		ProbeStop				//̽��ֹͣ
	};
	int				m_nProbeFlag;	//̽���־
};

#endif // QLOGICALTOPO_H

