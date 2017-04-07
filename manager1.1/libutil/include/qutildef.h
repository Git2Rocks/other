#ifndef QUTILDEF_H
#define QUTILDEF_H

#include <QString>
#include <QVector>
#include <QDateTime>
#include <QFileInfo>
#include <QIcon>
#include <QMetaType>
#include <QMap>
#include <QPair>

#include "global.h"
#include "qsharedobject.h"

template<class T>
class QRegisterInstances
{
public:
	QRegisterInstances(){};
	~QRegisterInstances(){};

public:
	static QRegisterInstances* instance()
	{
		static QRegisterInstances* g_pInstances=new QRegisterInstances;

		return g_pInstances;
	}

public:
	void addInterface(const T& ptr)
	{
		if (ptr != NULL)
		{
			m_instances.append(ptr);
		}
	}

	const QVector<T>& interfaces() const
	{
		return m_instances;
	}

private:
	QVector<T> m_instances;
};

template<class T, typename PT>
class QRegisterInterface
{
public:
	QRegisterInterface()
	{
		QRegisterInstances<PT>::instance()->addInterface(PT(new T));
	}
}; 

template<typename T, class P>
class QRegisterClassProducer
{
public:
	QRegisterClassProducer(){};
	~QRegisterClassProducer(){};

public:
	static QRegisterClassProducer* instance()
	{
		static QRegisterClassProducer* g_pInstances=new QRegisterClassProducer;

		return g_pInstances;
	}

public:
	void registerProducer(const T& type, const P& ptr)
	{
		if (ptr != NULL)
		{
			m_instances.insert(type, ptr);
		}
	}

	const P producer(const T& type)
	{
		return m_instances[type];
	}

private:
	QMap<T, P> m_instances;
};

template<class T>
class QAbstractClassProducer : public QSharedObject
{
public:
	QAbstractClassProducer(){};
	~QAbstractClassProducer(){};

public:
	virtual T* produce()=0;
};

template<class T, typename QTemplateClassProducer>
class QClassProducer : public QTemplateClassProducer
{
public:
	QClassProducer(){};
	~QClassProducer(){};

public:
	virtual T* produce()
	{
		return new T;
	}
};

enum UtilType
{
	UTIL_TYPE_LOCAL_SERVER,
	UTIL_TYPE_TOPOLOGY,
	UTIL_TYPE_REMOTE_SERVER,
	UTIL_TYPE_PROCESSOR,
	UTIL_TYPE_PERF_PROCESSOR,
	UTIL_TYPE_SYSTEM,
	UTIL_TYPE_COMPUTER_SYSTEM,
	UTIL_TYPE_NETWORK_ADAPTER,
	UTIL_TYPE_PROCESS,
	UTIL_TYPE_PERF_PROC_PROCESS,
	UTIL_TYPE_DISK_DRIVE,
	UTIL_TYPE_CDROM_DRIVE,
	UTIL_TYPE_LOGICAL_DISK,
	UTIL_TYPE_PHYSICAL_MEMORY,
	UTIL_TYPE_SYSTEM_MEMORY,
	UTIL_TYPE_END
};

enum OSType
{
	OS_WINDOWS,
	OS_SOLARIS,
	OS_AIX
};

#define SERVER_HOST_IP_SEPARATOR	"@"
#define FILE_MODIFIED_DATETIME_FORMAT	"yyyy-MM-dd hh:mm:ss"
#define STANDARD_DATETIME_FORMAT	"yyyy-MM-dd hh:mm:ss"

typedef struct _server 
{
	QString		addr;			//������ip��ַ
	quint32		netmask;		//��������
	quint16		port;			//�������˿ں�,ʹ��ͬһ�˿�
}Server;

typedef struct _serverInfo
{
	QString		hostName;
	QString		usrName;

	QString		home;			//������Ŀ¼

	int	count;
	QMap<QString, QVector<Server> > servers;	//������MAC��ַ��Ϊkey
}ServerInfo;

UTIL_EXPORT bool operator==(const Server& source, const Server& target);
UTIL_EXPORT bool operator==(const ServerInfo& source, const ServerInfo& target);
UTIL_EXPORT bool operator!=(const ServerInfo& source, const ServerInfo& target);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const ServerInfo& info);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, ServerInfo& info);

typedef struct _mibRemoteServer
{
	ServerInfo	info;

	bool coming;
}MibRemoteServer;

typedef struct _processorInfo			//��������Ϣ
{
	int os;

	//windows
	quint32 configManager;		//���ù���״̬

	//aix
	QString status;

	//all
	int core;					//������
	quint16	addressWidth;		//��ַ�ֳ�
	quint16	dataWidth;			//���������ݿ��

	QString description;
	QString deviceID;			//��������Ψһ��ʶ
	quint32 externalClock;		//�ⲿʱ��Ƶ��MHz
	quint32 L2CacheSize;
	quint32 L2CacheSpeed;		//MHz
	QString manufacturer;
	quint32 maxClockSpeed;		//MHz
	QString name;				//����������
}ProcessorInfo ;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const ProcessorInfo& processor);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, ProcessorInfo& processor);

typedef struct _perfProcessorCore 
{
	QString name;
	double percentProcessorTime;
}PerfProcessorCore;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const PerfProcessorCore& core);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, PerfProcessorCore& core);

typedef struct _perfProcessor
{
	quint32 currentClockSpeed;	//MHz
	qreal	currentVoltage;		//0~6λ��ֵ/10��ʾ��ѹ
	QString status;				//����״̬

	QVector<PerfProcessorCore> core;
}PerfProcessor;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const PerfProcessor& perf);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, PerfProcessor& perf);

typedef struct _operatingSystem
{
	QString caption;		//ϵͳ����
	QString version;		//ϵͳ�汾
	QString buildNumber;	//�������
	QString CSDVersion;		//service pack��Ϣ
	QString OSArchitecture;	//ϵͳ����
}OperatingSystem;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const OperatingSystem& system);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, OperatingSystem& system);

typedef struct _computerSystem
{
	quint32 numberOfProcessors;
	quint64 totalPhysicalMemory;

	QString name;			//��������
	QString workgroup;		//������
	QString domain;			//��

	QString processor;		//������
}ComputerSystem;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const ComputerSystem& system);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, ComputerSystem& system);

typedef struct _networkAdapter
{
	QString description;
	QVector<QString> defaultIPGateway;
	QVector<QString> DNSServer;
	QVector<quint16> gatewayCostMetric;
	QVector<QString> IPAddress;
	QVector<QString> IPSubnet;
	QString MACAddress;
}NetworkAdapter;

UTIL_EXPORT bool operator!=(const NetworkAdapter& source, const NetworkAdapter& target);
UTIL_EXPORT bool operator==(const NetworkAdapter& source, const NetworkAdapter& target);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const NetworkAdapter& adapter);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, NetworkAdapter& adapter);

#if defined(Q_OS_AIX) || defined(Q_OS_SOLARIS)
UTIL_EXPORT QVector<NetworkAdapter> findNetworkAdapter();
#endif

typedef struct _systemProcess
{
	QString usrName;
	QString	executablePath;
	QString name;
	quint32 processId;
	quint32 sessionId;
	quint64 workingSetSize;
	quint64 processorTime;	//ռ��cpuʱ��
	qreal	percentProcessorTime;
}SystemProcess;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const SystemProcess& process);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, SystemProcess& process);

typedef struct _fileInfo 
{
	int type;
	QString name;
	quint64 size;
	bool isReadable;
	bool isWritable;
	bool isExecutable;
	QDateTime lastModified;
}FileInfo;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const FileInfo& info);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, FileInfo& info);
UTIL_EXPORT bool operator==(const FileInfo& source, const FileInfo& target);
UTIL_EXPORT bool operator!=(const FileInfo& source, const FileInfo& target);

typedef struct _diskDrive
{
	int os;					//ϵͳ����

	//windows
	quint32 configManager;		//����״̬
	quint32 partitions;			//������
	quint32 numberOfMediaSupported;
	quint32 SCSIBus;
	quint16 SCSILogicalUnit;
	quint16 SCSITargetId;
	quint16 SCSIPort;
	QString mediaType;

	//aix
	QString status;
	QString serialNumber;
	QString position;

	//all
	QString description;
	QString deviceID;
	QString interfaceType;
	QString manufacturer;

	quint64 size;				//�ֽ�
	QString model;
}DiskDrive;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const DiskDrive& disk);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, DiskDrive& disk);

typedef struct _CDROMDrive 
{
	int os;

	//windows
	quint32 configManager;		//����״̬
	QString drive;				//�̷�
	quint32 numberOfMediaSupported;
	quint32 SCSIBus;
	quint16 SCSILogicalUnit;
	quint16 SCSITargetId;
	quint16 SCSIPort;
	quint64 size;
	QString mediaType;

	//aix
	QString status;
	QString position;

	//all
	QString description;
	QString deviceID;
	QString manufacturer;

	qreal	transferRate;		//��λKB/s
	QString volumeName;
	QString volumeSerialNumber;
	QString name;
}CDROMDrive;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const CDROMDrive& disk);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, CDROMDrive& disk);

typedef struct _logicalDisk
{
	QString description;
	QString deviceID;
	quint32 driveType;
	QString driveTypeDesc;
	QString fileSystem;
	quint64 freeSpace;
	quint64 size;
}LogicalDisk;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const LogicalDisk& disk);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, LogicalDisk& disk);

typedef struct _physicalMemory
{
	quint64 capacity;
	quint16 dataWidth;
	QString description;
	QString manufacturer;
	QString memoryType;
	QString name;
	QString serialNumber;
	quint32 speed;
	QString tag;
	QString version;
}PhysicalMemory;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const PhysicalMemory& memory);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, PhysicalMemory& memory);

typedef struct _systemMemory 
{
	QDateTime datetime;		//��ȡ�ڴ���Ϣʱ��

	//��λKB
	quint64 freePhysicalMemory;
	quint64 freeVirtualMemory;

	quint64 totalVisibleMemorySize;
	quint64 totalVirtualMemorySize;

	quint64 freeSpaceInPagingFiles;
	quint64 sizeStoredInPagingFiles;
	quint64 sizeUsageInPagingFiles;
	quint64 sizeUsageInPagingFilesPeak;

	quint64 systemCache;

	quint64 poolNonpaged;
	quint64 poolPaged;
}SystemMemory;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const SystemMemory& memory);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, SystemMemory& memory);

enum NodeType
{
	HoldNode=1,	//ռλ��
	RouterNode=(1<<1),
	SwitchL3Node=(1<<2),
	SwitchNode=(1<<3),
	FirewallNode=(1<<4),
	HubNode=(1<<5),
	HostNode=(1<<6),
	LeafNode=(FirewallNode|HostNode),
	LogicalNode=(HubNode),
	AllNode=0xff
};

typedef struct _graphNodeIpEntAddr 
{
	QString address;	//IP��ַ
	int ifIndex;		//�ӿ�������
	QString netmask;	//��������
}GraphNodeIpEntAddr;

typedef struct _graphNodeIpRoute 
{
	QString dest;
	int ifIndex;
	QString nextHop;
	int routeType;		//3=direct ֱ������,4=indirect ������һ��·����
	QString routeMask;
}GraphNodeIpRoute;

typedef struct _graphNodeIpNetToMedia 
{
	int ifIndex;
	QString physAddress;
	QString netAddress;
}GraphNodeIpNetToMedia;

typedef struct _graphNodeInterface
{
	int ifIndex;	//�ӿ�����
	QString	desc;	//�ӿ�������Ϣ
	int type;		//�ӿ����ͣ�6=ethernetCsmacd��53=propVirtual��1=other
	quint32	speed;	//�ӿ��ٶ�
	QString physAddress;	//�ӿ�MAC��ַ
	int operStatus;		//1=up, 2=down

	QVector<QString>	addresses;	//�ӿڰ󶨵�IP��ַ
}GraphNodeInterface;

typedef struct _graphNodeBridgeBasePort 
{
	int port;			//�˿ں�
	int ifIndex;	//�˿ںŶ�Ӧ�Ľӿ�����
}GraphNodeBridgeBasePort;

typedef struct _graphNodeBridgeBase 
{
	QString address;	//MAC��ַ����������СMAC��ַ
	int numPorts;		//�������˿�����
	int type;			//

	QMap<int, GraphNodeBridgeBasePort>	portTable;
}GraphNodeBridgeBase;

typedef struct _graphNodeFdb 
{
	QString address;	//MAC��ַ
	int port;			//�˿ں�
	int status;		//1=other,2=invalid,3=learned,4=self,5=mgmt
}GraphNodeFdb;

#define GRAPH_TOPO_INVALID_NODE	(quint64)-1		//��Ч�ڵ��ʶ
#define GRAPH_TOPO_INVALID_SEGMENT	(quint32)-1	//��Ч����
#define GRAPH_TOPO_INVALID_IP_ADDRESS	(quint32)-1
#define GRAPH_TOPO_ROOT_HOLD_NODE	0			//����ͼ���ڵ�

typedef struct _graphTopoNode GraphTopoNode;
struct _graphTopoNode
{
	quint64 uid;	//Ψһ��ʶ,����mac��ַ����Ϊ����СMAC��ַ�������48λΪ�������豸����СMAC��ַ����16λΪ�����ӵ��豸����

	int type;		//�ڵ�����
	QString	name;	//�豸����
	QString oid;	//�豸����ID
	QString desc;	//�豸����
	quint32 services;	//�豸�ṩ���߲�����ʶ

	quint32	ifNumber;	//�豸�ӿ�����
	quint32 ipForwarding;	//1:forwarding ������ǰת�����ݰ��Ĺ��ܣ��ж���·���������㽻�����ı�Ҫ������	2:notForwarding

	QMap<QString, GraphNodeIpEntAddr>	ipEntAddrs;		//IP��ַ��Ӧ���ɻ�ȡ������Ϣ
	QMap<int, GraphNodeIpRoute>		ipRoutes;		//·����Ϣ,key:ifIndex,value:·����Ϣ
	QMap<QString, GraphNodeIpNetToMedia>	ipMedia;	//arp��Ϣ

	QMap<int, GraphNodeInterface>	interfaces;		//��������·�����Ľӿ���Ϣ,key:ifIndex,vale:�ӿ���Ϣ

	GraphNodeBridgeBase	bridgeBase;	//�������˿���ӿڶ�Ӧ��Ϣ
	QMap<int, GraphNodeFdb>	fdb;	//������AFT����Ϣ��key:�˿ںţ�value:�ڽ���Ϣ��

	QMap<int, QPair<quint64, int> >	peers;	//key=�ӿں�,value=<Ψһ��ʶ,�ӿں�>
};

typedef struct _graphTopo
{
	GraphTopoNode root;		//�������˳�ʼռλ�ڵ㣬�Ӵ˽ڵ������������ͼ
	QMap<quint64, QPair<GraphTopoNode, int> >	nodes;	//��������ͼΪ����ͼ�ṹ,quint64=uid, int=ticks����������<>0ʱ��ʾ�ڵ�����
}GraphTopo;

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const GraphNodeInterface& face);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, GraphNodeInterface& face);

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const GraphTopoNode& node);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, GraphTopoNode& node);

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const GraphTopo& graph);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, GraphTopo& graph);

UTIL_EXPORT FileInfo entryInfo(const QFileInfo& info, bool isDrive);
UTIL_EXPORT int entryInfoFileType(const QFileInfo& info);
UTIL_EXPORT QString fileType(const QFileInfo& info);

UTIL_EXPORT void entryInfoList(const QFileInfoList& list, QVector<FileInfo>& files, bool isDrive);
UTIL_EXPORT bool deleteDir(const QString& path);
UTIL_EXPORT int readContents(QFile* file, QByteArray& buffer, bool highRate=false);

typedef struct _transferFileItem 
{
	QString name;
	quint64 size;
	int type;
	QString typeDesc;
}TransferFileItem;

UTIL_EXPORT bool operator==(const TransferFileItem& source, const TransferFileItem& target);
UTIL_EXPORT bool operator!=(const TransferFileItem& source, const TransferFileItem& target);

#ifdef Q_WS_WIN
#ifndef Q_OS_WINCE
UTIL_EXPORT QPixmap convertHIconToPixmap( const HICON icon);
#else
UTIL_EXPORT QPixmap convertHIconToPixmap( const HICON icon, bool large = false);
#endif
#endif

UTIL_EXPORT QIcon fileIcon(const FileInfo& info);
UTIL_EXPORT QIcon fileIcon(int type);
UTIL_EXPORT QIcon fileIcon(const QString& filename, int type);
UTIL_EXPORT quint64 fileSizeForNumber(const FileInfo& info);
UTIL_EXPORT QString fileSize(const FileInfo& info);
UTIL_EXPORT QString fileSize(quint64 size);
UTIL_EXPORT QString fileType(const FileInfo& info);
UTIL_EXPORT bool isFile(int type);
UTIL_EXPORT bool isDir(int type);

UTIL_EXPORT QString configManagerErrorCode(quint32 configManager);

#define HMAN_PRIVILEGE_FILE	"/ini/authority"
#define HMAN_PRIVILEGE_FILE_HEADER	"PRIVILEGE"
#define HMAN_PRIVALEGE_DEFAULT_GROUP_NAME	"Administrator"
#define HMAN_PRIVALEGE_DEFAULT_USER_NAME	"root"
#define HMAN_PRIVALEGE_DEFAULT_USER_PASSWD	"root"

//�û�Ȩ��
typedef struct _privilegeUser
{
	QString	datetime;	//ʱ��
	QString name;		//�û���
	QString passwd;		//����

	QMap<int, quint32> privileges;	//Ȩ��
}PrivilegeUser;

enum EAuthorityType
{
	PrivilegeRole,
	ProcessPrivilege,
	FileTransferPrivilege,
	FileSynchronizationPrivilege
};

enum EAuthorityFlag
{
	AdministratorRole=1,
	GuestRole=1<<1,

	CreateProcessPrivilege=1,
	TerminateProcessPrivilege=1<<1,

	UploadFileAndFolderPrivilege=1,
	DownloadFileAndFolderPrivilege=1<<1,

	CommitFilePrivilege=1,
	UpdateFilePrivilege=1<<1
};

UTIL_EXPORT bool checkPrivileges(const QMap<int, quint32>& privileges, int type, int flag);

typedef struct _privilegeGroup
{
	QString	datetime;	//ʱ��
	QString name;		//����

	QMap<QString, PrivilegeUser>	usrs;	//������������û�,key=�û���
}PrivilegeGroup;

enum EPrivilegeOperation
{
	PrivilegeDeleteGroup,
	PrivilegeDeleteUser
};

typedef struct _privilegeOperation 
{
	QString uid;		//�ֲ�ʹ��,/�ָ���
	QString datetime;	//����ʱ��

	int operation;		//��������
}PrivilegeOperation;

typedef struct _privilegeGroups 
{
	QMap<QString, PrivilegeGroup>		groups;		//������,key=����
	QList<PrivilegeOperation>			operations;	//����
}PrivilegeGroups;

UTIL_EXPORT QDataStream& operator>>(QDataStream& in, PrivilegeUser& user);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const PrivilegeUser& user);

UTIL_EXPORT QDataStream& operator>>(QDataStream& in, PrivilegeGroup& group);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const PrivilegeGroup& group);

UTIL_EXPORT bool operator==(const PrivilegeGroup& source, const PrivilegeGroup& target);
UTIL_EXPORT bool operator!=(const PrivilegeGroup& source, const PrivilegeGroup& target);

UTIL_EXPORT QDataStream& operator>>(QDataStream& in, PrivilegeOperation& operation);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const PrivilegeOperation& operation);

UTIL_EXPORT QDataStream& operator>>(QDataStream& in, PrivilegeGroups& groups);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const PrivilegeGroups& groups);

//��H9000Ѳ���й�
typedef struct _cscsDataType 
{
	uchar dataType;
	QString longname;
}CscsDataType;

typedef struct _cscsGroup
{
	uchar grpId;
	QString longname;

	QVector<CscsDataType> types;
}CscsGroup;

typedef struct _cscsStation 
{
	uchar stnId;
	QString longname;

	QVector<CscsGroup> groups;
}CscsStation;

typedef struct _cscsDatabase
{
	QVector<CscsStation> stations;
}CscsDatabase;

UTIL_EXPORT QDataStream& operator>>(QDataStream& in, CscsDatabase& data);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const CscsDatabase& data);

UTIL_EXPORT QDataStream& operator>>(QDataStream& in, CscsStation& data);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const CscsStation& data);

UTIL_EXPORT QDataStream& operator>>(QDataStream& in, CscsGroup& data);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const CscsGroup& data);

UTIL_EXPORT QDataStream& operator>>(QDataStream& in, CscsDataType& data);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const CscsDataType& data);

typedef struct _syncMonitorFile
{
	QString path;
	FileInfo file;

	bool enabled;
}SyncMonitorFile;

typedef struct _syncProgram
{
	QString	path;
	FileInfo program;
	bool enabled;
	bool running;
	bool terminal;

	QVector<SyncMonitorFile> files;
}SyncProgram;

typedef struct _syncCommand 
{
	QString command;
	QVector<QString> params;
	bool enabled;

	QVector<SyncMonitorFile> files;
}SyncCommand;

typedef struct _syncCommands
{
	QMap<int, SyncProgram> programs;
	QMap<int, SyncCommand> commands;
}SyncCommands;

#define SYNC_COMMANDS_PROGRAM_KIND	"program"
#define SYNC_COMMANDS_COMMAND_KIND	"command"

UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const SyncMonitorFile& info);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, SyncMonitorFile& info);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const SyncProgram& info);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, SyncProgram& info);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const SyncCommand& info);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, SyncCommand& info);
UTIL_EXPORT QDataStream& operator<<(QDataStream& out, const SyncCommands& info);
UTIL_EXPORT QDataStream& operator>>(QDataStream& in, SyncCommands& info);

Q_DECLARE_METATYPE(SyncMonitorFile)
Q_DECLARE_METATYPE(QVector<SyncMonitorFile>)
Q_DECLARE_METATYPE(SyncProgram)
Q_DECLARE_METATYPE(SyncCommand)

Q_DECLARE_METATYPE(Server)
Q_DECLARE_METATYPE(ServerInfo)
Q_DECLARE_METATYPE(MibRemoteServer)
Q_DECLARE_METATYPE(QList<ServerInfo>)
Q_DECLARE_METATYPE(QVector<ProcessorInfo>)
Q_DECLARE_METATYPE(PerfProcessor)
Q_DECLARE_METATYPE(QVector<OperatingSystem>)
Q_DECLARE_METATYPE(OperatingSystem)
Q_DECLARE_METATYPE(ComputerSystem)
Q_DECLARE_METATYPE(QVector<NetworkAdapter>)
Q_DECLARE_METATYPE(QVector<SystemProcess>)
Q_DECLARE_METATYPE(QVector<FileInfo>)
Q_DECLARE_METATYPE(FileInfo)
Q_DECLARE_METATYPE(QVector<DiskDrive>)
Q_DECLARE_METATYPE(QVector<CDROMDrive>)
Q_DECLARE_METATYPE(QVector<LogicalDisk>)
Q_DECLARE_METATYPE(LogicalDisk)
Q_DECLARE_METATYPE(QVector<PhysicalMemory>)
Q_DECLARE_METATYPE(SystemMemory)
Q_DECLARE_METATYPE(GraphTopo)
Q_DECLARE_METATYPE(PrivilegeGroups)
Q_DECLARE_METATYPE(PrivilegeUser)
Q_DECLARE_METATYPE(CscsDatabase)

#endif // QUTILDEF_H
