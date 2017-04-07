#ifndef QTREEVIEWGROUPTRANSFERQUEUE_H
#define QTREEVIEWGROUPTRANSFERQUEUE_H

#include <QTreeView>
#include <QIcon>

#include "qservermanager.h"
#include "qframeremotefilesystem.h"
#include "qtreemodel.h"
#include "qgrouptransferqueue.h"

class QTreeViewGroupTransferQueue : public QTreeView
{
	Q_OBJECT

public:
	QTreeViewGroupTransferQueue(QWidget *parent);
	~QTreeViewGroupTransferQueue();

public:
	enum TitleLabel
	{
		NameTitle,
		TypeTitle,
		StatusTitle,
		ProcessTitle,
		TargetTitle
	};

	enum TransferStatus
	{
		InvalidStatus=-1,
		Waiting=0,
		Transfering,
		BackingUp,
		Failed,
		Skip,
		Finished,
		Connecting,
		Connected,
		Unconneced,
		StatusEnd
	};

	enum TransferRoleType
	{
		ServerRole,
		FileRole,
		BackUpRole,		//����
		CommandRole		//ִ������
	};

	enum UserDataRole
	{
		TransferRole=Qt::UserRole,
		TransferDataRole,
		TransferStatusRole,
		TransferProcessRole
	};

	typedef struct _transferQueuePeerItem
	{
		bool isSlient;		//true: ���Ͷ˲����տͻ��˻�Ӧ

		ServerInfo source;	//���Ͷ�
		ServerInfo target;	//���ն�
	}TransferQueuePeerItem;

	typedef struct _transferQueueFileItem
	{
		bool isTop;
		int format;

		QString source;

		TransferFileItem	file;			//���ڴ��䵥���ļ�

		QString target;
	}TransferQueueFileItem;

	typedef struct _transferQueueBackupItem 
	{
		QString source;
		QString target;

		QVector<FileInfo>	files;	//���ڱ���
	}TransferQueueBackupItem;

	typedef struct _transferQueueCommandItem 
	{
		QString name;	//��������
		QString workspace;

		QVector<FileInfo>	files;		//�ύ���ļ�
	}TransferQueueCommandItem;

public:
	void clear();

	QModelIndex appendPeerItem(const TransferQueuePeerItem& peer);
	QModelIndex appendBackupItem(const TransferQueueBackupItem& item);

	void appendItem(const QTreeViewGroupTransferQueue::TransferQueueFileItem& item, int status, const QModelIndex& parent);
	void insertItem(int row, const QTreeViewGroupTransferQueue::TransferQueueFileItem& item, int status, const QModelIndex& parent);
	void removeItem(int row, const QModelIndex& parent);

	void appendCommandItem(const QTreeViewGroupTransferQueue::TransferQueueCommandItem& item, const QModelIndex& parent);
	void insertCommandItem(int row, const QTreeViewGroupTransferQueue::TransferQueueCommandItem& item, const QModelIndex& parent);

	void setItemTransferStatus(int row, QTreeViewGroupTransferQueue::TransferStatus status, const QModelIndex& parent=QModelIndex());
	int itemTransferStatus(int row, const QModelIndex& parent=QModelIndex());
	void addItemProcess(int row, quint64 size, const QModelIndex& parent);
	void setItemProcess(int row, quint64 size, const QModelIndex& parent);

	QModelIndex fetchTask(int& role, QVariant& var, int& status);	//��Ч��ʾ������

	QModelIndexList selectedRows();
	int taskCount(const QModelIndex& parent=QModelIndex());

	QModelIndex index(int row, const QModelIndex& parent=QModelIndex());

public:
	void showAbsolutePath(bool show);

Q_SIGNALS:
	void synchronize();
	void mouseRightButtonPressed(QPoint pos);

protected:
	virtual void mousePressEvent(QMouseEvent* event);

private:
	QTreeModel*		m_pModel;

	bool	m_bShowAbsolutePath;
};

Q_DECLARE_METATYPE(QTreeViewGroupTransferQueue::TransferQueuePeerItem)
Q_DECLARE_METATYPE(QTreeViewGroupTransferQueue::TransferQueueFileItem)
Q_DECLARE_METATYPE(QTreeViewGroupTransferQueue::TransferQueueBackupItem)
Q_DECLARE_METATYPE(QTreeViewGroupTransferQueue::TransferQueueCommandItem)

#endif // QTREEVIEWGROUPTRANSFERQUEUE_H
