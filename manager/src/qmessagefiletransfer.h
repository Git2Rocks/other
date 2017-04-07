#ifndef QMESSAGEFILETRANSFER_H
#define QMESSAGEFILETRANSFER_H

#include <QObject>
#include <QRunnable>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QFileInfoList>
#include <QDataStream>

#include "qimessage.h"
#include "extern.h"

/**
*	@Desc �����ʽ
*	@Author zlb
*	@Time 2011-3-31
*
*	QueryRoot:			QueryRoot|�û�ID
*	AnswerRoot:			AnswerRoot|�û�ID|·��
*	QueryPath:			QueryPath|�û�ID|·��|����ʽ
*	AnswerPath:			AnswerPath|�û�ID|·��|��ѯ״̬(|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��)
*	AnswerDir:			ͬAnswerPath
*	QueryFile:			QueryFile|�û�ID|����·���ļ���
*	AnswerFileInfo:		AnswerFileInfo|�û�ID|��ѯ״̬(|�ļ���С)
*	QueryTransferFile	QueryTransferFile|�û�ID|����·���ļ���|�����ʽ
*	QueryRetransmitFile	QueryRetransmitFile|�û�ID|����·���ļ���|�����ʽ|��ʼλ��
*	AnswerTransferFile	AnswerTransferFile|�û�ID|����״̬(|�ļ����ݳ���|�ļ�����)
*	QueryDir			QueryDir|�û�ID|Ŀ¼·��
*	QuerySymLink		QuerySymLink|�û�ID|����·���ļ���
*	AnswerSymLink		AnswerSymLink|�û�ID|��ѯ״̬(|������Ϣ)
*	QueryDrive			QueryDrive|�û�ID
*	AnswerDrive			AnswerDrive|�û�ID|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��
*	QueryUpload			QueryUpload|�û�ID|�ļ�����|�����ַ(|�����ʽ(�������ļ�)|������Ϣ(���������ļ�))
*	AnswerUpload		AnswerUpload|�û�ID|����״̬
*	QueryUploadFile		QueryUploadFile|�û�ID|����״̬|�ļ����ݳ���|�ļ�����
*	AnswerUploadFile	AnswerUploadFile|�û�ID|����״̬
*	QueryRename			QueryRename|�û�ID|Ŀ¼|�к�|ԭ��|����
*	AnswerRename		AnswerRename|�û�ID|�к�|ԭ��|����|����������״̬
*	QueryNewDirectory	QueryNewDirectory|�û�ID|��Ŀ¼
*	AnswerNewDirectory	AnswerNewDirectory|�û�ID|�½�����״̬(|Ŀ¼��Ϣ)
*	QueryDelete			QueryDelete|�û�ID|��Ŀ¼|�ļ�����|�ļ����б�
*	AnswerDelete		AnswerDelete|�û�ID|ɾ������״̬
**/

class QMessageFileTransfer : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageFileTransfer(QObject *parent=0);
	~QMessageFileTransfer();

	enum {Type=MSG_FILE_TRANSFER};

	enum MsgType
	{
		QueryRoot=0,			//�����Ŀ¼
		AnswerRoot,				//���ظ�Ŀ¼
		QueryPath,				//����·��
		AnswerPath,				//����·����������Ŀ¼�Լ��ļ���Ϣ(�򲻴��ڸ�Ŀ¼)
		QueryFile,				//�������ļ������ô����ʽ���ı��������ƣ�
		AnswerFileInfo,			//�����ļ���Ϣ(��С)�����ļ�������
		QueryTransferFile,		//�ļ�������ɣ����Դ����ļ�
		QueryRetransmitFile,	//��ָ�����ȿ�ʼ�ش��ļ�
		AnswerTransferFile,		//�����ļ�����
		QueryDir,				//�������ļ���
		AnswerDir,				//�����ļ�����Ϣ
		QuerySymLink,			//��������������ļ�
		AnswerSymLink,
		QueryDrive,				//���������������Ϣ
		AnswerDrive,
		QueryUpload,			//�����ϴ��ļ���Ŀ¼����������λ��(,�ļ������ʽ)
		AnswerUpload,
		QueryUploadFile,		//�ϴ��ļ�����
		AnswerUploadFile,
		QueryRename,			//�������
		AnswerRename,
		QueryNewDirectory,		//���󴴽���Ŀ¼
		AnswerNewDirectory,
		QueryDelete,			//����ɾ���ļ����ļ���
		AnswerDelete
	};

	enum QueryResult
	{
		QueryUnknow=-1,
		QueryPathNoExist=0,		//�����ļ�·��������
		QueryPathValid,			//�����ļ�·����Ч
		QueryFileNoExist,		//�����ļ�������
		QueryFileUnreadable,	//�����ļ����ɶ�
		QueryFileValid,			//�����ļ���Ч
		QuerySymLinkNoLink,		//�����ļ����Ƿ��������ļ�
		QueryMakePathSuccess,	//���󴴽��ļ��гɹ�
		QueryMakePathFail,		//���󴴽��ļ���ʧ��
		QueryCreateFileSuccess,	//�����ϴ��ļ���������ʱ�ļ��ɹ�
		QueryCreateFileFail,	//�����ϴ��ļ���������ʱ�ļ�ʧ��
		QueryUploadFileWriteLost,	//�����ϴ��ļ���д�ļ�����������Ѿ��ر�
		QueryUploadFileWriteFail,	//�����ϴ��ļ���д����ʱ�ļ�ʧ��
		QueryUploadFileWriteSuccess,//�����ϴ��ļ���д����ʱ�ļ��ɹ�
		QueryUploadFileSuccess,	//�����ϴ��ļ��ɹ�������ʱ�ļ�����Ϊ�����ļ�
		QueryUploadFileFail,	//�����ϴ��ļ�ʧ��
		QueryUploadSymLinkSuccess,	//�����ϴ������ļ������ɹ�
		QueryUploadSymLinkFail	//�����ϴ������ļ�����ʧ��
	};

	enum SortFlags
	{
		SortName=0,				//����������
		SortTime,				//��ʱ������
		SortSize,				//����С����
		SortType,				//����������
		SortReversed=0x10		//��������������ʽ���ʹ��
	};

	enum FileType
	{
		Drive=1,
		Dir=(1<<1),
		HideDir=(1<<2),
		File=(1<<3),
		HideFile=(1<<4),
		SymLink=(1<<5),
		HideSymLink=(1<<6),
		CDDVDDrive=(1<<7),
		SymLinkDir=SymLink|Dir,
		SymLinkHideDir=SymLink|HideDir,
		SymLinkFile=SymLink|File,
		SymLinkHideFile=SymLink|HideFile
	};

	enum FileTransferFormat
	{
		TextFormat=0,		//�ı���ʽ
		BinaryFormat		//�����Ƹ�ʽ
	};

	enum TransferStatus
	{
		TransferNormal=0,
		TransferReadError,
		TransferFinish
	};

	enum RenameStatus
	{
		RenameFail=0,
		RenameSuccess,
		RenamePathLost		//δ����ԭʼ·��
	};

	enum NewDirectoryStatus
	{
		NewFail=0,
		NewSuccess
	};

	enum DelStatus
	{
		DelFail=0,
		DelSuccess
	};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QConnection* sender, QByteArray buffer, QObject* view=0);

public:
	Q_INVOKABLE bool addTransferFile(QObject* client, quint32 usrID, QFile* file);
	Q_INVOKABLE void removeTransferFile(QObject* client, quint32 usrID);

	QFile* transferFile(QObject* client, quint32 usrID);

private slots:
	void finished(QConnection* sender, int msgType, quint32 usrID, QByteArray buffer=QByteArray(), int status=-1);

	void timeout();

private:
	typedef struct _fileHandle
	{
		QFile*	file;
		int tick;
	}FileHandle;

	QMap<QObject*, QMap<quint32, FileHandle> >	m_mapFiles;

	QTimer		m_timer;
};

class QMessageFileTransferRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageFileTransferRunnable(QConnection* sender, const QByteArray& buffer, QObject* view, 
		QMessageFileTransfer* message, QObject* parent=0);
	virtual ~QMessageFileTransferRunnable();

signals:
	void finished(QConnection* sender, int msgType, quint32 usrID, QByteArray buffer=QByteArray(), int status=-1);

public:
	void setArg(QConnection* sender, const QByteArray& buffer, QObject* view, QMessageFileTransfer* message);
	virtual void run();

public:
	static int readContents(QFile* file, QByteArray& buffer);
	static void entryInfoList(QFileInfoList& list, QVector<FileInfo>& files);
	static bool deleteDir(const QString& path);

private:
	QConnection*	m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;

	QMessageFileTransfer*	m_pMessage;
};

QDataStream& operator<<(QDataStream& out, const FileInfo& info);
QDataStream& operator>>(QDataStream& in, FileInfo& info);

#endif // QMESSAGEFILETRANSFER_H
