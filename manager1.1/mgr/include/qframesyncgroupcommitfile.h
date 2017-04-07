#ifndef QFRAMESYNCGROUPCOMMITFILE_H
#define QFRAMESYNCGROUPCOMMITFILE_H

#include <QFile>
#include <QTimer>
#include <QList>
#include <QRunnable>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QMenu>
#include <QAction>
#include <QSignalMapper>

#include "ui_syncgroupcommitfile.h"
#include "qabstractreceiver.h"
#include "qtreeviewsynccommit.h"
#include "qlistviewsyncfileserver.h"
#include "qlistviewsyncfilerequestserver.h"
#include "qtransferinstructor.h"
#include "qtreeviewgrouptransferqueue.h"
#include "qlinkbutton.h"

class QFrameSyncGroupCommitFile : public QFrame, public Ui::FrameSyncGroupCommitFile
{
	Q_OBJECT

public:
	QFrameSyncGroupCommitFile(const QString& treeview, bool enableRestrict, QWidget *parent=0);
	~QFrameSyncGroupCommitFile();

public:
	void setTitleText(const QString& title);
	void setDefaultDescText(const QString& desc);

	void setThemePixmap(const QPixmap& pixmap);
	void showTipsPixmap(bool show);

public:
	void refreshFileSystem();
	void refreshServerList(const QList<QPair<ServerInfo, int> >& servers);

	void setRestrictFilterEnabled(bool enable);

public slots:
	void appendTip(int flag, const QString& tip);

protected:
	void transferFile(const QModelIndex& index, int role, const QVariant& item);

	virtual void cancel();
	virtual void finished();

protected:
	virtual bool eventFilter(QObject* watched, QEvent* event);

private slots:
	void readCommonFolder();
	void currentTextChanged();
	void refreshModelFinished();

	void actionTriggered(int index);

	void onClickedBtnOk();
	void onClickedBtnCancel();
	void onClickedBtnSelectAll();
	void onClickedBtnSelectNone();
	void onClickedBtnRefresh();
	void onClickedBtnWorkspace();
	void onClickedBtnShowLog();

	void doubleClicked(const QModelIndex& index);

	void mouseRightButtonPressed(QPoint pos);

	void selectedChanged();

	void recvMessage(QTransferInstructor::MessageType type, const QString& message);
	void addSubTask(const QGroupTransferQueue::TransferQueueItem& task, QVector<FileInfo> files);
	void transferedFileContents(const QGroupTransferQueue::TransferQueueItem& task, quint64 size);
	void backupProcess(int finished, int success);

	void closing();		//�Աȴ��ڹر�

private:
	void fetchTask();
	int findFileFormat(const QString& name, int format) const;

	void syncFinished();

private:
	void appendTransferTip(int flag, const QString& tip);

	void setItemsCheckState(int state);

private:
	void saveBackupRecord(const QString& filename, QVector<QPair<FileInfo, int> >& files);

	bool writeConfigure();

	void logplus(int flag, const QString& tip);
	
private:
	QString		m_strDefaultDesc;		//Ĭ����ʾ��Ϣ����

	QPair<int, QString>	m_transferTip;	//������Ϣ

	QListViewSyncFileServer*	m_pListViewServers;		//ͬ�����շ��б�
	bool		m_bSync;		//�Ƿ����ͬ���ļ�

	QLinkButton*	m_pButtonWorkspace;	//ͬ�����ͷ�����Ŀ¼
	QMap<QString, QString>	m_configure;	//���Ͷ�������Ϣ

	QLinkButton*	m_pButtonRefresh;

	QTreeViewSyncCommit*	m_pTreeView;	//ͬ�����ͷ��ļ��б�

	QTreeViewGroupTransferQueue*	m_pTreeViewQueue;

	QString		m_strPath;		//�����ϴ�Ŀ¼
	QString		m_strSavePath;	//Զ�˱���Ŀ¼

	QModelIndex	m_index;		//��ǰͬ���ļ�λ��ͬ�����б�����

	QGroupTransferQueue::TransferQueueItem m_task;

	QTransferInstructor*	m_pTransferInstructor;

private:
	QMap<QModelIndex, QObject*>		m_mapWnd;	//�������뵱ǰ

private:
	enum ActionType
	{
		ActionSync,
		ActionCancel,
		ActionDiff,
		ActionSelectAll,
		ActionSelectNone,
		ActionShowLog,
		ActionRefresh,
		ActionDeleteAll,
		ActionRetransmit,
		ActionEnd
	};

	QMenu*		m_pMenu;
	QMenu*		m_pMenuQueue;		//������в˵�
	QAction*	m_pActions[ActionEnd];

	QSignalMapper*	m_pSignalMapper;
};

class QWriteBackupToXmlFile : public QAbstractWriteXmlFile
{
public:
	QWriteBackupToXmlFile(const QString& filename, const QString& path, const QVector<QPair<FileInfo, int> >& files);
	~QWriteBackupToXmlFile();

protected:
	virtual QString parentNodeName() const
	{
		return "folder";
	}

	virtual void save(QDomDocument& doc, QDomElement& parent);

private:
	QString		m_strPath;
	 QVector<QPair<FileInfo, int> > m_files;
};

#endif // QFRAMESYNCGROUPCOMMITFILE_H
