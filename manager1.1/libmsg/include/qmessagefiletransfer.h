#ifndef QMESSAGEFILETRANSFER_H
#define QMESSAGEFILETRANSFER_H

#include <QObject>
#include <QRunnable>
#include <QMap>
#include <QTimer>
#include <QVector>
#include <QFileInfoList>
#include <QDataStream>
#include <QMutex>

#include "qmessageextern.h"
#include "qfileex.h"

/**
*	@Desc �����ʽ
*	@Author zlb
*	@Time 2011-3-31
*	@Modify	2012-2-28
*
*	QueryRoot:			QueryRoot|�û�ID
*	AnswerRoot:			AnswerRoot|�û�ID|·��
*	QueryPath:			QueryPath|�û�ID|·��|����ʽ|nameFilter|Filter
*	AnswerPath:			AnswerPath|�û�ID|·��|��ѯ״̬(|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��)
*	QueryDrive			QueryDrive|�û�ID
*	AnswerDrive			AnswerDrive|�û�ID|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��
*	QuerySymLink		QuerySymLink|�û�ID|�ļ�����·��
*	AnswerSymLink		AnswerSymLink|�û�ID|��ѯ״̬(|���ӵ�ַ)
*	QueryDownloadDir:	QueryDownloadDir|�û�ID|Ŀ¼·��|Ŀ¼����·��
*	AnswerDownloadDir:	AnswerPath|�û�ID|Ŀ¼·��|��ѯ״̬(|Ŀ¼����·��|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��)
*	QueryFileInfo		QueryFileInfo|�û�ID|����·���ļ���
*	AnswerFileInfo		AnswerFileInfo|�û�ID|����·���ļ���|��ѯ״̬(|(������)�ļ���Ϣ|����·��·��+�ļ���[���]��)
*	QueryDownloadFile:	QueryDownloadFile|�û�ID|����·���ļ���|�����ʽ|�ļ��������·���ļ���
*	AnswerDownloadFileInfo:		AnswerDownloadFileInfo|�û�ID|����·���ļ���|��ѯ״̬(|�ļ��������·���ļ���|�����ʽ|�ļ���С)
*	QueryTransferFile	QueryTransferFile|�û�ID|����״̬
*	AnswerTransferFile	AnswerTransferFile|�û�ID|����״̬((�ļ����|�ļ����ݳ���|�ļ�����)|(�ļ�Ȩ����Ϣ))
*	QueryResumeDownloadFile	QueryResumeDownloadFile|�û�ID|����·���ļ���|�����ʽ|�ļ���ʼƫ����|����޸�����|�ļ��������·���ļ���
*	AnswerResumeDownloadFile	AnswerResumeDownloadFile|�û�ID|����·���ļ���|��ѯ״̬��|�ļ��������·���ļ���|�����ʽ|�ļ���С|�ļ���ʼƫ������
*	QueryDownloadFlowControl	QueryDownloadFlowControl|�û�ID
*	AnswerDownloadFlowControl	AnswerDownloadFlowControl|�û�ID
*	QueryDownloadSymLink		QueryDownloadSymLink|�û�ID|�ļ�����·��|�ļ��������·��
*	AnswerDownloadSymLink		AnswerDownloadSymLink|�û�ID|��ѯ״̬(�ļ��������·��|������Ϣ|�ļ�Ȩ��)
*	QueryUploadDir		QueryUploadDir|�û�ID|�ļ�������|�ļ��д�������·��
*	AnswerUploadDir		AnswerUploadDir|�û�ID|�ļ��д���״̬
*	QueryUploadFile		QueryUploadFile|�û�ID|�������·��|�ļ�����·��|�����ʽ
*	AnswerUploadFile	AnswerUploadFile|�û�ID|�ļ�����״̬|�ļ�����·��|�����ʽ
*	QueryUploadFileContent	QueryUploadFileContent|�û�ID|״̬(�ļ����|(�ļ�����|�ļ�����)|(�ļ�Ȩ����Ϣ))
*	AnswerUploadFileContent	AnswerUploadFileContent|�û�ID|����״̬
*	QueryUploadSymlink	QueryUploadSymlink|�û�ID|�����ļ�����|�ļ���������·��|�ļ����ӵ�ַ
*	AnswerUploadSymlink	AnswerUploadSymlink|�û�ID|�����ļ�����״̬
*	QueryUploadFlowControl	QueryUploadFlowControl|�û�ID
*	AnswerUploadFlowControl	AnswerUploadFlowControl|�û�ID
*	QueryResumeUploadFile	QueryResumeUploadFile|�û�ID|�������·��|�ļ�����·��|�����ʽ|��ʼλ��
*	AnswerResumeUploadFile	AnswerResumeUploadFile|�û�ID|�����ļ�����״̬(|�ļ�����·��|�����ʽ|��ʼλ��)
*	QueryUploadSlientDir	QueryUploadSlientDir|�û�ID|�ļ�������|�ļ��д�������·��
*	QueryUploadSlientSymlink	QueryUploadSlientSymlink|�û�ID|�����ļ�����|�ļ���������·��|�ļ����ӵ�ַ
*	QueryUploadSlientFile	QueryUploadSlientFile|�û�ID|�������·��|�ļ�����·��|�����ʽ
*	QueryUploadSlientFileContent	QueryUploadSlientFileContent|�û�ID|�������·��|�����ʽ
*	AnswerUploadSlientFileContent	AnswerUploadSlientFileContent|�û�ID|�������·��|�����ʽ|״̬(�ļ����|(�ļ�����|�ļ�����)|(�ļ�Ȩ����Ϣ))
*	QueryRename			QueryRename|�û�ID|Ŀ¼|ԭ��|����
*	AnswerRename		AnswerRename|�û�ID|����������״̬|Ŀ¼|ԭ��|����
*	QueryNewDirectory	QueryNewDirectory|�û�ID|��Ŀ¼
*	AnswerNewDirectory	AnswerNewDirectory|�û�ID|�½�����״̬(|Ŀ¼��Ϣ)
*	QueryDelete			QueryDelete|�û�ID|��Ŀ¼|�ļ�����|�ļ����б�
*	AnswerDelete		AnswerDelete|�û�ID|ɾ������״̬(��Ŀ¼|�ļ��������ļ����б�)
*	QueryInterruptTransfer	QueryInterruptTransfer|�û�ID
*	AnswerInterruptTransfer	AnswerInterruptTransfer|�û�ID|�ж�״̬
*	QueryBackup			QueryBackup|�û�ID|����ԴĿ¼|����Ŀ��Ŀ¼|�ļ�����|�ļ���Ϣ
*	AnswerBackup		AnswerBackup|�û�ID|����״̬|�ѱ����ļ�����|���ݳɹ��ļ�����
**/

class MSG_EXPORT QMessageFileTransfer : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageFileTransfer(QObject *parent=0);
	~QMessageFileTransfer();

	enum {Type=MSG_FILE_TRANSFER};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int ackType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QObject* sender, QByteArray buffer, QObject* view=0);

private slots:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer=QByteArray());
	void download(QObject* sender, quint32 usrID, QObject* view);
	void upload(QObject* sender, quint32 usrID, QObject* view);
	void slientUpload(QObject* sender, quint32 usrID, QString save, int format, QObject* view);
};

class MSG_EXPORT QMessageFileTransferRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageFileTransferRunnable(QObject* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageFileTransferRunnable();

signals:
	void finished(QObject* sender, int ackType, quint32 usrID, QByteArray buffer=QByteArray());
	void download(QObject* sender, quint32 usrID, QObject* view);
	void upload(QObject* sender, quint32 usrID, QObject* view);
	void slientUpload(QObject* sender, quint32 usrID, QString save, int format, QObject* view);

public:
	void setArg(QObject* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

private:
	QObject*		m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

class QSharedFile;
typedef QSharedObjectPtr<QSharedFile>	QSharedFilePtr;

#define SHARED_FILE_FIRST_BLOCK		1
class MSG_EXPORT QSharedFile : public QFileEx, public QSharedObject
{
public:
	QSharedFile(const QString & name);
	QSharedFile(QObject* parent);
	QSharedFile(const QString& name, QObject* parent);
	~QSharedFile();

public:
	static QSharedFilePtr createFile(const QString& filename, int format, QObject* client, quint32 usrID);

public:
	qint64 write(int number, const QByteArray& byteArray);

	void setPermissions(int number, Permissions permissionSpec);
	int setPermissions();
	int permissionsSerial();

	int nextBlock();
	bool isCurrentBlock(int number) const;

private:
	void init();

private:
	static QMutex	g_mutex;

private:
	QMutex	m_mutex;

	int		m_nNextBlock;

private:
	QMap<int, QByteArray>	m_contents;
	QPair<int, QFile::Permissions>	m_permissions;
};

class MSG_EXPORT QMessageFileTransferManager : public QObject, public QSharedObject
{
	Q_OBJECT

public:
	QMessageFileTransferManager(QObject* parent=0);
	~QMessageFileTransferManager();

public:
	static QMessageFileTransferManager* instance();

public:
	bool addTransferFile(QObject* client, quint32 usrID, const QSharedFilePtr& file);
	void removeTransferFile(QObject* client, quint32 usrID);

	QSharedFilePtr transferFile(QObject* client, quint32 usrID);
	int flowControl(QObject* client, quint32 usrID);

public:
	void check();

private slots:
	void timeout();

private:
	typedef struct _fileHandle
	{
		QSharedFilePtr	file;
		int tick;
		int flowCtl;	//�������
	}FileHandle;

	QMap<QObject*, QMap<quint32, FileHandle> >	m_mapFiles;

	QTimer		m_timer;

private:
	static QMutex		g_mutex;
};

#endif // QMESSAGEFILETRANSFER_H
