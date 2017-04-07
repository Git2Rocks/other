#ifndef QIMESSAGE_H
#define QIMESSAGE_H

#include <QDataStream>

#include "global.h"
#include "qsharedobject.h"

enum MsgType
{
	MSG_LOCAL_SERVER,
	MSG_REMOTE_SERVER,
	MSG_TOPOLOGY,
	MSG_PROCESSOR,
	MSG_SYSTEM,
	MSG_COMPUTER_SYSTEM,
	MSG_NETWORK_ADAPTER,
	MSG_SYSTEM_PROCESS,
	MSG_DISK_DRIVE,
	MSG_SYSTEM_MEMORY,
	MSG_FILE_TRANSFER,
	MSG_CONTROLLED,
	MSG_STATUS_CHANGED,
	MSG_DDB,
	MSG_CSCS,			//H9000�����Ϣ
	MSG_CONFIGURE
};

enum ConfigureAckType
{
	QuerySyncAssociationConfigure,		//����ͬ����������
	AnswerSyncAssociationConfigure,		//Ӧ��ͬ����������
	QueryWriteSyncAssociateionConfig,	//������Ĺ�������
	AnswerWriteSyncAssociateionConfig,
	QueryExecSyncConfigureCommand,		//����ִ���ļ�ͬ������
	AnswerExecSyncConfigureCommand
};

enum ConfigureAckResultType
{
	QueryWriteConfigureFail,		//д�����ļ�ʧ��
	QueryWriteConfigureSuccess,
	QueryCommandFoundProcessesFail,	//δ��ȡmib�н�����Ϣ
	QueryCommandKillProcessFail,	//��ֹ����ʧ��
	QueryCommandCreateProcessFail,	//��������ʧ��
	QueryCommandFoundCommandFail,	//�����ҵ�ִ�к���������������
	QueryCommandExecCommand,
	QueryCommandFinish
};

enum CscsAckType
{
	QueryCscsStruct,	//����H9000��վ�ṹ
	AnswerCscsStruct,
	QueryCscsStationEigenvalue,
	AnswerCscsStationEigenvalue,
	QueryCscsGroupEigenvalue,
	AnswerCscsGroupEigenvalue,
	QueryCscsDataTypeEigenvalue,
	AnswerCscsDataTypeEigenvalue
};

enum CscsAckResultType
{
	CscsDataSourceLost,			//H9000δ������ʵʱ������Դ
	CscsDataSourceFound,		//�ɹ���ȡ����Դ
	CscsDataSourceNoExisted,	//���ҵ����ݲ�����
	CscsCommandNoExisted,
	CscsCommandParamError,
	CscsCommandFailed,			//ִ��ʧ��
	CscsCommandSuccess
};

enum CscsEigenvalueType
{
	CscsDbHead,
	CscsStationEntry,
	CscsGroupEntry,
	CscsRecordEntry
};

enum DdbAckType
{
	QueryInformDdbConnection,		//ddb���ӣ���������������
	AnswerInformDdbConnection,
	QueryUploadPrivilegeData,		//�ϴ�Ȩ������
	AnswerUploadPrivilegeData,
	QueryCheckPrivilege,			//����û�������Ϣ
	AnswerCheckPrivilege,
	QueryPrivileges,				//���������û�����Ϣ
	AnswerPrivileges,
	QueryCreateGroup,				//���󴴽���
	AnswerCreateGroup,
	QueryDeleteGroup,				//����ɾ����
	AnswerDeleteGroup,
	QueryCreateUser,				//���󴴽��û�
	AnswerCreateUser,
	QueryDeleteUser,				//����ɾ���û�
	AnswerDeleteUser,
	QueryModifyUserPrivilege,		//�����޸��û�Ȩ��
	AnswerModifyUserPrivilege,
	QueryModifyUserPassword,		//�����޸��û�����
	AnswerModifyUserPassword,
	UpdateUserPrivilege				//�����û�Ȩ��
};

enum DdbAckResultType
{
	PrivilegeDataModified,
	PrivilegeDataUnmodified,
	PrivilegeUncheckable,		//Ȩ�޲�������������
	PrivilegeUserNoExisted,		//�û���������
	PrivilegePasswdError,		//�������
	PrivilegeCheckPass,			//����ͨ��

	CreateGroupSuccess,			//������ɹ�
	CreateGroupExisted,			//���Ѵ���

	CreateUserSuccess,			//�����û��ɹ�
	CreateUserExisted,			//�û�����
	CreateUserGroupNonexistent,	//�����û��鲻����

	ModifyPrivilegeUserNonexistent,	//�޸�Ȩ�ޣ��û�������
	ModifyPrivilegeSuccess,		//�޸�Ȩ�޳ɹ�

	ModifyPasswordUserNonexistent,	//�޸����룬�û�������
	ModifyPasswordSuccess,			//�޸�����ɹ�

	UserDeleted,				//�û���ɾ��
	UserPasswordChanged,		//�û����뱻�޸�
	UserPrivilegesChanged		//�û�Ȩ�ޱ��޸�
};

enum LocalServerMsgAckType
{
	QueryLocalServer,		//�����ȡ���ط�������Ϣ
	AnswerLocalServer,
	InformStatusChanged
};

enum RemoteServerMsgAckType
{
	QueryRemoteServerList,	//�����ȡԶ�˷������б�
	AnswerRemoteServerList
};

enum TopologyMsgAckType
{
	QueryTopology,
	AnswerTopology
};

enum SystemProcessMsgAckType
{
	QueryRefProcess,		//�����������ͽ�����Ϣ
	QueryUnrefProcess,		//������Ҫ������Ϣ
	QueryProcess,			//���������Ϣ�����Σ�
	AnswerProcess,
	QueryCreateProcess,
	AnswerCreateProcess,
	QueryTerminateProcess,
	AnswerTerminateProcess
};

enum SystemMsgAckType
{
	QueryOperatingSystem,	//�������ϵͳ��Ϣ
	AnswerOperatingSystem
};

enum ComputerSystemMsgAckType
{
	QueryComputerSystem,
	AnswerComputerSystem	//����ϵͳ��Ϣ
};

enum NetworkAdapterMsgAckType
{
	QueryNetworkAdapter,	//����������������Ϣ
	AnswerNetworkAdapter
};

enum ProcessorMsgAckType
{
	QueryProcessor,			//��������������Ϣ
	AnswerProcessor,
	QueryRefRuntimeProcessor,	//�����������ʹ�����ʹ����Ϣ
	QueryUnrefRuntimeProcessor,	//������ֹ���ʹ�����ʹ����Ϣ
	QueryRuntimeProcessor,		//��������ʹ����Ϣ�����Σ�
	AnswerRuntimeProcessor
};

enum MemoryMsgAckType
{
	QueryPhysicalMemory,		//���������ڴ�������Ϣ
	AnswerPhysicalMemory,
	QueryRefSystemMemory,		//������������ϵͳ�ڴ�ʹ����Ϣ
	QueryUnrefSystemMemory,
	QuerySystemMemory,			//������һ��ϵͳ�ڴ�ʹ����Ϣ
	AnswerSystemMemory
};

enum DiskDriveMsgAckType
{
	QueryDiskDrive,
	AnswerDiskDrive,
	QueryCDROMDrive,
	AnswerCDROMDrive,
	QueryLogicalDisk,
	AnswerLogicalDisk
};

enum CommandType
{
	CommandCreateProcess,		//��������,����Ϊ�����У���ǰĿ¼
	CommandTerminateProcess		//��ֹ����,����Ϊ���̾��
};

enum CommandResultType
{
	ExecMethodComInvalid=-2,	//COM��ʼ��ʧ��
	ExecMethodInvalid=-1,		//��Ч����
	ExecMethodFailed=0,
	ExecMethodSucceed,
	ExecMethodAccessDenied,
	ExecMethodPathNotFound,
	ExecMethodInvalidParameter
};

enum FileTransferMsgAckType
{
	QueryRoot,				//�����Ŀ¼,��Ŀ¼Ϊ��ǰ����ĸ�Ŀ¼
	AnswerRoot,				//���ظ�Ŀ¼
	QueryPath,				//����·��
	AnswerPath,				//����·����������Ŀ¼�Լ��ļ���Ϣ(�򲻴��ڸ�Ŀ¼)
	QueryDrive,				//���������������Ϣ
	AnswerDrive,
	QuerySymLink,			//���������ļ�Ŀ���ַ
	AnswerSymLink,

	QueryDownloadDir,		//���������ļ���
	AnswerDownloadDir,		
	QueryFileInfo,			//�����ļ���Ϣ
	AnswerFileInfo,			//�����ļ���Ϣ
	QueryDownloadFile,		//���������ļ�
	AnswerDownloadFileInfo,	//���س�ʼ���������ļ���Ϣ
	QueryTransferFile,		//�ļ�������ɣ���ʼ�����ļ�
	AnswerTransferFile,		//�����ļ�����
	QueryDownloadSymLink,	//�������ط��������ļ�
	AnswerDownloadSymLink,
	QueryResumeDownloadFile,	//���������ļ�
	AnswerResumeDownloadFile,
	QueryDownloadFlowControl,	//������������
	AnswerDownloadFlowControl,

	QueryUploadDir,			//�����ϴ��ļ���
	AnswerUploadDir,
	QueryUploadFile,		//�����ϴ��ļ�
	AnswerUploadFile,
	QueryUploadFileContent,	//�����ϴ��ļ�����
	AnswerUploadFileContent,
	QueryUploadSymlink,		//�����ϴ����������ļ�
	AnswerUploadSymlink,
	QueryResumeUploadFile,	//���������ļ�
	AnswerResumeUploadFile,
	QueryUploadFlowControl,	//�ϴ���������
	AnswerUploadFlowControl,

	QueryUploadSlientDir,		//�����ϴ��ļ��ж����ط����κ���Ϣ
	QueryUploadSlientSymlink,	//�����ϴ����������ļ������ط����κ���Ϣ
	QueryUploadSlientFile,		//�����ϴ��ļ������ط����κ���Ϣ
	QueryUploadSlientFileContent,	//�����ϴ��ļ����ݣ������ط����κ���Ϣ
	AnswerUploadSlientFileContent,

	QueryRename,			//�������
	AnswerRename,
	QueryNewDirectory,		//���󴴽���Ŀ¼
	AnswerNewDirectory,
	QueryDelete,			//����ɾ���ļ����ļ���
	AnswerDelete,

	QueryInterruptTransfer,	//�����жϴ���
	AnswerInterruptTransfer,

	QueryBackup,			//���󱸷��ļ����ļ���
	AnswerBackup
};

enum ControlledMsgAckType
{
	QueryConnectToTarget,		//��������Ŀ������֮�������
	AnswerConnectToTarget,
	QueryUploadDirToTarget,		//����Դ�����ϴ�Ŀ¼��Ŀ������
	AnswerUploadDirToTarget,
	QueryUploadFileToTarget,	//����ԭ�����ϴ��ļ���Ŀ������
	AnswerUploadFileToTarget,
	QueryUploadSymlinkToTarget,	//�����ϴ����������ļ���Ŀ������
	AnswerUploadSymlinkToTarget,
	QueryInterruptTransferToTarget,	//�����ж���Ŀ������֮����ļ�����
	AnswerInterruptTransferToTarget,
	QueryUploadSlientDirToTarget,	//����Դ�����ϴ�Ŀ¼��Ŀ������,Ŀ����������Ҫ�����κ���Ϣ
	AnswerUploadSlientDirToTarget,
	QueryUploadSlientFileToTarget,	//����ԭ�����ϴ��ļ���Ŀ������,Ŀ����������Ҫ�����κ���Ϣ
	AnswerUploadSlientFileToTarget,
	QueryUploadSlientSymlinkToTarget,	//�����ϴ����������ļ���Ŀ������,Ŀ����������Ҫ�����κ���Ϣ
	AnswerUploadSlientSymlinkToTarget,
	QueryExecSyncCommandToTarget,			//�����ϴ�ִ��ͬ������
	AnswerExecSyncCommandToTarget
};

enum MsgAckResultType
{
	QueryExecuted=-2,		//��Ϣ��ִ�У������ļ�����
	QueryUnknow=-1,
	QueryFailed=0,
	QuerySucceed,

	QueryPathNoExist,		//·��������
	QueryPathValid,			//·����Ч

	QueryDirNoExist,		//�ļ���·��������
	QueryDirValid,			//�ļ���·����Ч
	QueryDirMakePathFailed,	//�����ļ���·��ʧ��

	QueryFileNoExist,		//�ļ�������
	QueryFileUnreadable,	//�ļ����ɶ�
	QueryFileUnwritable,	//�ļ�����д
	QueryFileModified,		//�ļ����޸�
	QueryFileValid,			//�ļ���Ч

	QueryFileNoSymLink,		//���Ƿ��������ļ�

	QueryFileOpenFail,		//���ļ�ʧ��
	QueryFileOpenSuccess,	//���ļ��ɹ�

	QueryFileCreateFail,	//�����ļ�ʧ��
	QueryFileCreateSuccess,	//�����ļ��ɹ�

	QueryFileWriteLost,		//�ļ��Ѿ��رգ�д��ʧ��
	QueryFileWriteFail,		//д���ļ�ʧ��
	QueryFileWriteSuccess,	//д���ļ��ɹ�
	QueryFileWriteFinish,	//д���ļ����

	QueryFileReadLost,		//�ļ��Ѿ��رգ�����ʧ��
	QueryFileReadFail,		//��ȡ�ļ�ʧ��
	QueryFileReadSuccess,	//��ȡ�ļ��ɹ�
	QueryFileReadFinish,	//��ȡ�ļ����

	QueryFileSeekFail,		//�����ļ���ǰλ��ʧ��

	QueryFileRenameFail,	//�������ļ�ʧ��
	QueryFileChangePermissionFail,	//�����ļ�Ȩ��ʧ��

	QueryFileTransferFinish,	//�����ļ����

	QueryFileRemoveFail,	//ɾ���ļ�ʧ��
	QueryFileRemoveSuccess,
	QueryFileRemoved,

	QueryFileSendFlowControl,	//�����������ư�

	QuerySymLinkNoLink,		//�����ļ����Ƿ��������ļ�
	QueryCreateSymLinkFail,	//�������������ļ�ʧ��
	QueryCreateSymLinkSuccess,

	QueryMakePathSuccess,	//���󴴽��ļ��гɹ�
	QueryMakePathFail,		//���󴴽��ļ���ʧ��

	QueryRenameFail,
	QueryRenameSuccess,
	QueryRenamePathLost,	//δ����ԭʼ·��

	QueryNewFail,
	QueryNewSuccess,

	QueryDelFail,
	QueryDelSuccess,

	QueryConnectToTargetFailed,	//Դ������Ŀ��������������ʧ��
	QueryConnectToTargetSuccess,//�������ӳɹ�
	TargetDisconnected,			//Դ������Ŀ�������Ͽ�����
	QueryUploadToTargetSourceDirLost,		//Դ�����ļ��в�����
	
	QuerySourceFileOpenFail,	//Դ�ļ���ʧ��
	QuerySourceFileReadLost,	//Դ����δ�ҵ��ļ�
	QuerySourceFileReadFail,	//Դ�������ļ�ʧ��
	QuerySourceTransferFile,	//Դ���������ļ���
	QuerySourceTransferFileFinish,	//Դ������ɴ����ļ�
	QuerySourceSendFlowControl,		//Դ����������������
	QueryTargetFileCreateFail,	//Ŀ�����������ļ�ʧ��
	QueryTargetFileWriteFail,	//Ŀ������д�ļ�ʧ��
	QueryTargetFileWriteSuccess,	//Ŀ������д�ļ��ɹ�
	QueryTargetFileWriteLost,	//Ŀ������д�ļ�����������Ѿ��ر�
	QueryTargetFileWriteFinish,	//Ŀ������д���ļ����
	QueryTargetFileChangePermissionFail,	//Ŀ���ļ��ı��ļ�Ȩ��ʧ��

	QueryTargetUploadFileFail,		//Ŀ����������ʱ�ļ�����Ϊ�����ļ�ʧ��
	QueryTargetUploadSymLinkSuccess,	//�����ϴ������ļ������ɹ�
	QueryTargetUploadSymLinkFail,		//�����ϴ������ļ�����ʧ��

	QueryBackingUp,					//���ڱ����ļ�
	QueryBackUpFinish				//�������
};

enum SortFlags
{
	SortName,				//����������
	SortTime,				//��ʱ������
	SortSize,				//����С����
	SortType,				//����������
	SortReversed=0x10		//��������������ʽ���ʹ��
};

enum FileType
{
	Drive=1,
	CDDVDDrive=(1<<1),
	Dir=(1<<2),
	HideDir=(1<<3),
	File=(1<<4),
	HideFile=(1<<5),
	SymLink=(1<<6),
	HideSymLink=(1<<7),
	SymLinkDir=SymLink|Dir,
	SymLinkHideDir=SymLink|HideDir,
	SymLinkFile=SymLink|File,
	SymLinkHideFile=SymLink|HideFile,
	FileTypeMask=0x3f
};

enum FileTransferFormat
{
	TextFormat=0,		//�ı���ʽ
	BinaryFormat,		//�����Ƹ�ʽ
	AutoFormat,
	FormatEnd
};

#define UNIVERSAL_MAC_ADDRESS	"FF:FF:FF:FF:FF:FF"

class UTIL_EXPORT QIMessage : public QSharedObject
{
public:
	QIMessage(){};
	virtual ~QIMessage(){};

public:
	virtual int type() const=0;

	virtual QByteArray query(int ackType, quint32 usrID=-1, const QByteArray& contents="")=0;		//��������
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=NULL)=0;
};

typedef QSharedObjectPtr<QIMessage> QIMessagePtr;

typedef void (*CreateMessageInstanceFunc)(QVector<QIMessagePtr>&);		//��Ϣ�ද̬������ṩ�Ľӿ�

#endif // QIMESSAGE_H
