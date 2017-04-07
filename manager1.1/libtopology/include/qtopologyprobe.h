#ifndef QTOPOLOGYPROBE_H
#define QTOPOLOGYPROBE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QTimer>
#include <QRunnable>

#include "global.h"
#include "topocommon.h"
#include "qicmp.h"
#include "qsnmp.h"
#include "qutildef.h"

class TOPOLOGY_EXPORT QTopologyProbe : public QObject
{
	Q_OBJECT

public:
	QTopologyProbe(QObject *parent=0);
	~QTopologyProbe();

public:
	typedef struct _graphTopoTask
	{
		quint64 puid;	//���ڵ�uid
		int ifIndex;	//���ڵ�ӿں�

		QString physAddress;	//���ڵ�ӿںŶ�Ӧ�������ַ
		QVector<quint32>	segments;	//���ڵ�ӿںŶ�Ӧ������
		QHash<quint32, quint64>	nodes;	//���ش�����Ľڵ�,key=uid��hashֵ,quint64=uid
	}GraphTopoTask;

public:
	void probe(const GraphTopoTask& task);

	void addSegments(quint32 address, bool around=false);	//���address����,around=true��Ӹ�������һ
	void addSegment(quint32 address);	//���address����

	void findAlives(quint32 segment);		//���ֻIP

	void querySysName(quint32 segment);		//�����豸����
	void queryOidProperty(quint32 segment, int oidtype, unsigned char dataType, int requestType=QSnmp::SnmpAsynGet, int nodeType=AllNode);		//�����豸OID��Ϣ
	void querySwitchOidProperty(quint32 segment, int oidtype, unsigned char dataType, int requestType=QSnmp::SnmpAsynGet);
	void queryRouterOidProperty(quint32 segment, int oidtype, unsigned char dataType, int requestType=QSnmp::SnmpAsynGet);

	bool contains(quint32 segment, int nodeType);
	quint64 contains(quint32 segment, const QString& addr);

public:
	void assemble(quint32 segment);	//��װ����ͼ,segment:����
	void assembleRouter(GraphTopoNode& parent, quint32 segment, QList<quint64> uids);	//��װ·�����ڵ�,parent=·�����ڵ㣬segment=���������,uids=������SNMP���������
	void assembleRootSwitch(GraphTopoNode& parent, int ifIndex, QList<quint64>& uids, quint32 segment, QList<quint64>& hosts);	//��װ���������ڵ�
	void assembleSwitch(GraphTopoNode& sw, int ifIndex, QList<quint64>& uids, quint32 segment, QList<quint64>& hosts);	//��װ�������ڵ�
	void assembleSwitchPerIfIndex(GraphTopoNode& sw, int ifIndex, QList<quint64>& uids, quint32 segment, QList<quint64>& hosts);	//��װ������ÿ���˿�,����ifIndex��uid=�������˿ڣ�uids=������SNMP���������
	void assembleHub(GraphTopoNode& parent, int ifIndex, QList<quint64>& uids, quint32 segment, QList<quint64>& hosts);	//��װHub

	quint64 addHostToTopo(const QString& physAddr, quint32 segment);
	quint64 addHostToTopo(const QString& physAddr, quint32 segment, GraphNodeInterface& face);

public:
	QString octetStrToString(const QString& str);
	GraphNodeIpNetToMedia ipNetToMediaFromArp(const QString& physAddr);
	const QString macAddrFromIpAddr(const QString& addr) const;
	const QVector<QString> ipAddrFromMacAddr(const QString& mac, quint32 segment=GRAPH_TOPO_INVALID_SEGMENT);

public slots:
	void foundAlives(quint32 segment, QVector<quint32> alives);
	void snmpResponse(int oidType, QVector<QSnmp::SnmpResponse> results);
	void assembled();

public:
	static int ifIndexToPort(const GraphTopoNode& node, int ifIndex);
	static int portToIfIndex(const GraphTopoNode& node, int port);

#ifdef Q_OS_AIX
	void setLocalArpEntry(const ServerInfo& info);
#endif

signals:
	void finished(QTopologyProbe::GraphTopoTask task, GraphTopoNode root, QMap<quint64, GraphTopoNode> nodes);

private:
	void terminateThread();

	void nextAliveTask();
	void foundArpEntry(const QString& mac, const QString& addr);

private:
	GraphTopoTask m_topoTask;

#ifdef Q_OS_AIX
	ServerInfo	m_local;	//����IP��ַ��mac��Ӧ��ϵ��aix��arp�����ޱ�����Ϣ
#endif

	GraphTopoNode m_root;
	int m_nIfIndex;

	QIcmp*	m_pIcmp;		//ICMPЭ��
	QSnmp*	m_pSnmp;		//SNMPЭ��

private:
	QMap<quint32, QVector<quint32> >	m_segments;	//key=����,value=���λIP
	QMap<quint32, QHash<quint32, quint64> >	m_agents;	//ÿ�����εĻ�����quin32=���Σ�Hash<ip��ַhash��ֵ�� �ڵ�Ψһ��ʶ>
	QMap<quint64, GraphTopoNode>	m_nodes;	//�������˽ڵ㣬key=Ψһ��ʶ��value=�ڵ���Ϣ

	QVector<ArpEntry>	m_tableArp;			//����arp��
	QHash<quint32, int>	m_tableArpMacKey;	//����arp��,key=mac��ַhashֵ��value=arp������
	QHash<quint32, int> m_tableArpAddrKey;	//����arp��key=ip��ַhashֵ��value=arp������

	QLinkedList<quint32>	m_tasks;
	QPair<quint32, int>		m_task;		//̽��IP��key=���Σ�value=̽�����
};

class TOPOLOGY_EXPORT QTopologyAssembleRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QTopologyAssembleRunnable(QTopologyProbe* prober, quint32 segment,  QObject* parent=0);
	virtual ~QTopologyAssembleRunnable();

public:
	virtual void run();

signals:
	void finished();

private:
	QTopologyProbe*		m_pProber;
	quint32 m_nSegment;
};

Q_DECLARE_METATYPE(QTopologyProbe::GraphTopoTask)
Q_DECLARE_METATYPE(GraphTopoNode)

#endif // QTOPOLOGYPROBE_H

