#ifndef QFRAMESYNCFILE_H
#define QFRAMESYNCFILE_H

#include <QFile>
#include <QTimer>
#include <QList>

#include "qabstractsync.h"
#include "extern.h"
#include "qclient.h"
#include "qabstractfiletransfer.h"

class QFrameSyncFile : public QAbstractSync, public QAbstractFileTransfer
{
	Q_OBJECT

public:
	QFrameSyncFile(QClient* client, const QString& subPath, QWidget *parent=0);
	~QFrameSyncFile();

public:
	void queryRoot();
	void queryDrives();
	void queryPath(const QString& path);
	void queryFile(const QString& file);
	void queryDir(const QString& path);
	void querySymLink(const QString& symLink);
	void queryTransferFile(const QString& file, int format);
	void queryUpload();
	void queryUploadFile();

	virtual void queryRename(const QString& location, int row, const QString& old, const QString& now);
	virtual void queryNewDirectory(const QString& location);
	virtual void queryDelete(const QString& location, const QStringList& files);

public:
	void remoteDeepRefresh();

protected:
	virtual void recvRoot(const QString& root);
	virtual void recvDrive(const QVector<FileInfo>& drives);
	virtual void recvPath(const QString& path, int flag, const QVector<FileInfo>& files);
	virtual void recvFileInfo(int flag, quint64 size);
	virtual void recvFileData(int flag, const QByteArray& buffer);
	virtual void recvDir(const QString& path, int flag, const QVector<FileInfo>& files);
	virtual void recvSymLink(int flag, FileInfo info, const QString& symLink);
	virtual void recvUpload(int flag);
	virtual void recvUploadFile(int flag);
	virtual void recvRename(int row, QString old, QString now, int flag);
	virtual void recvNewDirectory(int flag, const FileInfo& file);
	virtual void recvDelete(int flag);

protected:
	virtual void transfer(int row, const QTreeViewTransferQueue::TransferQueueItem& task);

	void transferFile(int row, const QTreeViewTransferQueue::TransferQueueItem& task);
	void downloads();
	void uploads();

	virtual void cancel();
	virtual void finished();

	virtual void gotoRemoteHome();
	virtual void gotoRemoteLocation(const QString& location);

private slots:
	void timeout();

private:
	void fetchTask();

protected:
	QClient*	m_pClient;
	quint32		m_nUsrID;		//�û�ID�����ڲ�ѯĿ¼��Ϣ
	quint32		m_nDynamicID;	//�û�ID�������ļ�����

	int			m_nIndex;		//��ǰͬ���ļ��������
	QList<FileInfo>	m_listFileInfo;

	QFile*		m_pFile;		//��ǰ��Ҫ�����ļ�
	int			m_nFormat;		//��ǰͬ���ļ������ʽ
	quint64		m_nSize;		//��ǰͬ���ļ���С

	QString		m_strRoot;		//�������и�Ŀ¼
	QString		m_strSubPath;	//����ڸ�Ŀ¼��·��

private:
	bool		m_bQueryComputer;	//�����ȡ�������������Ϣ

	int			m_nRow;			//��ǰͬ���ļ�λ��ͬ���б��к�
	QTreeViewTransferQueue::TransferQueueItem	m_task;		//����
	bool		m_bStatus;		//�ļ�����״̬,trueΪ��ɣ�falseΪʧ��

private:
	QTimer		m_timer;		//���ߴ��䳬ʱ
	int			m_nTick;
};

#endif // QFRAMESYNCFILE_H
