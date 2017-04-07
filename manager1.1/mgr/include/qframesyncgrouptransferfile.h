#ifndef QFRAMESYNCGROUPTRANSFERFILE_H
#define QFRAMESYNCGROUPTRANSFERFILE_H

#include <QFrame>
#include <QMenu>
#include <QAction>

#include "ui_syncgrouptransferfile.h"
#include "qlinkbutton.h"
#include "qlistviewfilereceiver.h"
#include "qtransferinstructor.h"
#include "qtreeviewgrouptransferqueue.h"
#include "qtreeviewupdatefile.h"
#include "qlistviewprompt.h"

class QFrameSyncGroupTransferFile : public QFrame, public Ui::FrameSyncGroupTransferFile
{
	Q_OBJECT

public:
	QFrameSyncGroupTransferFile(const QString& record, const QString& subPath, const QString& treeview, QWidget *parent=0);
	~QFrameSyncGroupTransferFile();

public:
	void setTitleText(const QString& title);
	void setDefaultDescText(const QString& desc);

	void setThemePixmap(const QPixmap& pixmap);
	void showTipsPixmap(bool show);

public:
	void setServerList(const QList<QPair<ServerInfo, int> >& servers);
	void setTreeModel(QTreeModel* model);
	void setWorkspace(const QString& workspace);

signals:
	void goBack();
	void command(const QString& workspace);

protected:
	virtual bool eventFilter(QObject* watched, QEvent* event);

private slots:
	void prompt(int flag, const QString& tip);

	void mouseRightButtonPressed(QPoint pos);

	void actionTriggered(int index);

	void onClickedBtnCommit();
	void onClickedBtnCommand();
	void onClickedBtnSelect();
	void onClickedBtnSelectAll();
	void onClickedBtnSelectNone();

	void selectedChanged();

	void synchronize();
	void recvMessage(QTransferInstructor::MessageType type, const QString& message);
	void addSubTask(const QGroupTransferQueue::TransferQueueItem& task, QVector<FileInfo> files);
	void transferedFileContents(const QGroupTransferQueue::TransferQueueItem& task, quint64 size);

private:
	void fetchTask();
	void transfer(const QModelIndex& index, int role, const QVariant& item);

	void finished();

	void setFileItemsCheckState(int state);

private:
	QString		m_strDefaultDesc;		//Ĭ����ʾ��Ϣ����

	QString		m_strRecord;			//��¼��ʶ

	QLinkButton*			m_pButtonWorkspace;			//ͬ�����ͷ�����Ŀ¼
	QTreeViewUpdateFile*	m_pTreeViewFiles;			//ͬ�����ͷ��ļ��б�

	QLinkButton*	m_pButtonUpload;
	QLinkButton*	m_pButtonCommand;

	QListViewFileReceiver*			m_pListViewReveiver;	//���ն��б�
	QTreeViewGroupTransferQueue*	m_pTreeViewQueue;
	QListViewPrompt*				m_pListViewPrompt;

	QModelIndex	m_index;		//��ǰͬ���ļ�λ��ͬ�����б�����
	QGroupTransferQueue::TransferQueueItem m_task;

	QTransferInstructor*	m_pTransferInstructor;

private:
	enum ActionType
	{
		ActionUpload,
		ActionSelectAll,
		ActionSelectNone,
		ActionRetransmit,
		ActionDeleteTask,
		ActionDeleteAllTask,
		ActionEnd
	};

	QMenu*		m_pMenu;
	QMenu*		m_pMenuTask;

	QAction*	m_pActions[ActionEnd];

	QSignalMapper*	m_pSignalMapper;

private:
	bool	m_bSync;			//�Ƿ�����ͬ��
	int		m_nRow;				//��ǰͬ����
};

#endif // QFRAMESYNCGROUPTRANSFERFILE_H
