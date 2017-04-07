#ifndef QFRAMETRANSFERFILE_H
#define QFRAMETRANSFERFILE_H

#include <QFile>
#include <QTimer>
#include <QList>

#include "qclient.h"
#include "qabstractfiletransfer.h"
#include "qreceivertransferfile.h"

class QFrameTransferFile : public QAbstractFileTransfer
{
	Q_OBJECT

public:
	QFrameTransferFile(QClient* client, const QString& subPath, QWidget *parent=0);
	~QFrameTransferFile();

public:
	void queryPath(const QString& path);

	virtual void queryRename(const QString& location, const QString& old, const QString& now);
	virtual void queryNewDirectory(const QString& location);
	virtual void queryDelete(const QString& location, const QVector<QString>& files);

public:
	void remoteDeepRefresh();

protected:
	virtual void transfer(int row, const QReceiverTransferFile::TransferQueueItem& task);

	void transferFile(int row, const QReceiverTransferFile::TransferQueueItem& task);

	virtual void cancel();
	virtual void finished();

	virtual void gotoRemoteHome();
	virtual void gotoRemoteLocation(const QString& location);

private slots:
	void timeout();
	void sendMessageFailed();

	void recvDrives(const QVector<FileInfo> drives);
	void recvRoot(const QString root);

	void folderCatalog(const QString path, const QVector<FileInfo> files);
	void folderCatalogFailed(const QString path);

	void rename(const QString dir, const QString old, const QString now);
	void newDirSuccess(const FileInfo file);

	void deleteFiles();

	void downloadDirSuccess(const QString path, const QString savePath, const QVector<FileInfo> files, int direction, int format);
	void downloadDirFailed();

	void downloadFileRenamed(const QString file);

	void downloadFileCreateSuccess(quint64 size);
	void downloadFileFailed();
	void downloadFileSuccess();

	void downloadFileWriteSuccess(int size);

	void uploadFailed();
	void uploadSuccess();
	void uploadDirSuccess(QReceiverTransferFile::TransferQueueItem task, const QVector<FileInfo> files);

	void uploadFileRenamed(const QString file);
	void uploadFileReadSuccess(quint64 size);

	void interruptTransfer();

private:
	void fetchTask();

protected:
	QClient*	m_pClient;

	QString		m_strRoot;		//�������и�Ŀ¼
	QString		m_strSubPath;	//����ڸ�Ŀ¼��·��

	QReceiverTransferFile*	m_pReceiver;	//�ļ�����

private:
	bool		m_bQueryComputer;	//�����ȡ�������������Ϣ
	bool		m_bQueryHomePath;	//������Ŀ¼

	int			m_nRow;			//��ǰͬ���ļ�λ��ͬ���б��к�
	bool		m_bStatusTransfer;	//����״̬�� true������ɣ�false����ʧ��
};

#endif // QFRAMETRANSFERFILE_H
