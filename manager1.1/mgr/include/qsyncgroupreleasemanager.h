#ifndef QSYNCGROUPRELEASEMANAGER_H
#define QSYNCGROUPRELEASEMANAGER_H

#include <QFrame>
#include <QHBoxLayout>

#include "ui_syncgroupreleasefile.h"
#include "qbuttonlist.h"
#include "qutildef.h"
#include "qframesyncgroupreleasefile.h"
#include "qframefilereceiver.h"
#include "qtreeviewgrouptransferqueue.h"
#include "qlistviewprompt.h"
#include "qtransferinstructor.h"

class QSyncGroupReleaseManager : public QFrame
{
	Q_OBJECT

public:
	QSyncGroupReleaseManager(QWidget *parent=0);
	~QSyncGroupReleaseManager();

	enum ButtonId
	{
		ButtonConfigFiles,
		ButtonPictures,
		ButtonDBDefine,
		ButtonDatFiles,
		ButtonRtdbFile,
		ButtonIEC104Files,
		ButtonSoundFiles,
		ButtonEnd
	};

public:
	void setServerList(const QList<QPair<ServerInfo, int> >& servers);

public:
	void setTitleText(const QString& title);
	void setDefaultDescText(const QString& desc);

	void setThemePixmap(const QPixmap& pixmap);
	void showTipsPixmap(bool show);

private slots:
	void prompt(int flag, const QString& tip);

	void buttonClicked(int id);
	void buttonChecked(int id, bool checked);

	void selectedChanged();

	void onClickedBtnCancel();
	void onClickedBtnRelease();

	void loaded(bool state);

	void mouseRightButtonPressed(QPoint pos);
	void actionTriggered(int index);

private slots:
	void synchronize();
	void recvMessage(QTransferInstructor::MessageType type, const QString& message);
	void addSubTask(const QGroupTransferQueue::TransferQueueItem& task, QVector<FileInfo> files);
	void transferedFileContents(const QGroupTransferQueue::TransferQueueItem& task, quint64 size);

private:
	void fetchTask();
	void transfer(const QModelIndex& index, int role, const QVariant& item);

	void finished();

private:
	void setupUi(int id);

	void setMenuState(bool refresh);

	bool checkLoaded() const;

private:
	Ui::FrameSyncGroupReleaseFile*	m_ui;

	QString		m_strDefaultDesc;		//Ĭ����ʾ��Ϣ����

	QButtonList*		m_pButtonList;

	QFrameSyncGroupReleaseFile*		m_pFrameFiles[ButtonEnd];

	QFrameFileReceiver*				m_pFrameReceiver[ButtonEnd];	//���ն��б�
	QTreeViewGroupTransferQueue*	m_pTreeViewQueue;
	QListViewPrompt*				m_pListViewPrompt;

	QModelIndex	m_index;		//��ǰͬ���ļ�λ��ͬ�����б�����
	QGroupTransferQueue::TransferQueueItem m_task;

	QTransferInstructor*	m_pTransferInstructor;

private:
	bool	m_bSync;			//�Ƿ�����ͬ��
	int		m_nRow;				//��ǰͬ����

private:
	enum ActionType
	{
		ActionCancel,
		ActionRetransmit,
		ActionDeleteAll,
		ActionEnd
	};

	QMenu*		m_pMenuQueue;		//������в˵�
	QAction*	m_pActions[ActionEnd];

	QSignalMapper*	m_pSignalMapper;
};

#endif // QSYNCGROUPRELEASEMANAGER_H
