#ifndef EXTERN_H
#define EXTERN_H

enum MsgType
{
	MSG_PROCESSOR=0,
	MSG_FILE_TRANSFER,
	MSG_SYSTEM,
	MSG_COMPUTER_SYSTEM,
	MSG_NETWORK_ADAPTER,
	MSG_SYSTEM_PROCESS,
	MSG_DISK_DRIVE,
	MSG_SYSTEM_MEMORY,
	MSG_PERFORMER
};

enum WmiType
{
	WMI_TYPE_PROCESSOR=0,
	WMI_TYPE_PERF_PROCESSOR,
	WMI_TYPE_SYSTEM,
	WMI_TYPE_COMPUTER_SYSTEM,
	WMI_TYPE_NETWORK_ADAPTER,
	WMI_TYPE_PROCESS,
	WMI_TYPE_PERF_PROC_PROCESS,
	WMI_TYPE_DISK_DRIVE,
	WMI_TYPE_CDROM_DRIVE,
	WMI_TYPE_LOGICAL_DISK,
	WMI_TYPE_PHYSICAL_MEMORY,
	WMI_TYPE_SYSTEM_MEMORY
};

enum OSType
{
	OS_WINDOWS,
	OS_SOLARIS,
	OS_AIX
};

#include <QString>
#include <QVector>
#include <QDateTime>
#include <QFileInfo>
#include <QIcon>
#include <QMetaType>

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

QDataStream& operator<<(QDataStream& out, const ProcessorInfo& processor);
QDataStream& operator>>(QDataStream& in, ProcessorInfo& processor);

typedef struct _perfProcessorCore 
{
	QString name;
	double percentProcessorTime;
}PerfProcessorCore;

typedef struct _perfProcessor
{
	quint32 currentClockSpeed;	//MHz
	qreal	currentVoltage;		//0~6λ��ֵ/10��ʾ��ѹ
	QString status;				//����״̬

	QVector<PerfProcessorCore> core;
}PerfProcessor;

typedef struct _operatingSystem
{
	QString caption;		//ϵͳ����
	QString version;		//ϵͳ�汾
	QString buildNumber;	//�������
	QString CSDVersion;		//service pack��Ϣ
}OperatingSystem;

typedef struct _computerSystem
{
	QString name;			//��������
	QString workgroup;		//������
	QString domain;			//��
}ComputerSystem;

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

QDataStream& operator<<(QDataStream& out, const DiskDrive& disk);
QDataStream& operator>>(QDataStream& in, DiskDrive& disk);

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

QDataStream& operator<<(QDataStream& out, const CDROMDrive& disk);
QDataStream& operator>>(QDataStream& in, CDROMDrive& disk);

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

void registerMessage();
void registerWmi();

FileInfo entryInfo(const QFileInfo& info);
int entryInfoFileType(const QFileInfo& info);
QString fileType(const QFileInfo& info);

QIcon fileIcon(const FileInfo& info);
QIcon fileIcon(int type);
QString fileSize(quint64 size);
QString fileType(const FileInfo& info);

QString configManagerErrorCode(quint32 configManager);

Q_DECLARE_METATYPE(QVector<ProcessorInfo>)
Q_DECLARE_METATYPE(PerfProcessor)
Q_DECLARE_METATYPE(QVector<OperatingSystem>)
Q_DECLARE_METATYPE(QVector<ComputerSystem>)
Q_DECLARE_METATYPE(QVector<NetworkAdapter>)
Q_DECLARE_METATYPE(QVector<SystemProcess>)
Q_DECLARE_METATYPE(QVector<FileInfo>)
Q_DECLARE_METATYPE(QVector<DiskDrive>)
Q_DECLARE_METATYPE(QVector<CDROMDrive>)
Q_DECLARE_METATYPE(QVector<LogicalDisk>)
Q_DECLARE_METATYPE(QVector<PhysicalMemory>)
Q_DECLARE_METATYPE(SystemMemory)

#endif	//EXTERN_H

