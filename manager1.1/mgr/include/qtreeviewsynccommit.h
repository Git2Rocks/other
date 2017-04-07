#ifndef QTREEVIEWSYNCCOMMIT_H
#define QTREEVIEWSYNCCOMMIT_H

#include <QTreeView>
#include <QPoint>
#include <QRunnable>

#include "qutildef.h"
#include "qtreemodel.h"
#include "qdelegatesynccommit.h"
#include "qfilecomparefactory.h"
#include "qreadwritexmlfile.h"

class QTreeViewSyncCommit : public QTreeView
{
	Q_OBJECT

public:
	QTreeViewSyncCommit(QWidget *parent=0);
	~QTreeViewSyncCommit();

public:
	enum TitleLabel
	{
		NameTitle,
		SizeTitle,
		TypeTitle,
		StatusTitle,
		ModifiedTitle,
		TitleLabelEnd
	};

	enum ItemRoleType
	{
		GroupRole,
		FileRole
	};

	enum DiffFileUserData
	{
		ItemRole=Qt::UserRole,	//item��ɫ
		CheckableRole,			//�Ƿ��ѡ��
		CheckedRole,			//ѡ��
		StatusRole,				//item״̬����
		UserDataRole			//�ļ���Ϣ
	};

public:
	virtual QString record() const=0;	//��¼�ϴ��ύ���ļ���Ϣ
	virtual QString commonFolder() const=0;	//Ĭ�Ϲ���Ŀ¼

public:
	/**
	*	@Desc	������
	*
	*	@Param	workspace ����Ŀ¼��������ԴĿ¼
	*	@Param	history	��ʷ��¼Ŀ¼�����ں͹���Ŀ¼���бȽϣ��ó�����
	**/
	void check(const QString& workspace, const QString& histroy);

public:
	QVector<QPair<FileInfo, int> > selectedItems(const QModelIndex& parent=QModelIndex());

	bool fetchItem(const QModelIndex& index, QPair<FileInfo, int>& file);

	int rowCount(const QModelIndex& parent=QModelIndex()) const;

	void setItemsCheckable(bool checkable);
	int itemCheckState(int row, const QModelIndex& parent=QModelIndex()) const;

	virtual void setItemCheckState(int row, int state, const QModelIndex& parent=QModelIndex());

	QModelIndexList selectedRows();

	bool hasSelected() const;

	void setRestrictFilterEnabled(bool enable);

public:
	void save();	//�����¼

public:
	void clear();

Q_SIGNALS:
	void refreshKeyPress();

	void refreshModelFinished();
	void mouseRightButtonPressed(QPoint pos);

	void selectedChanged();

private slots:
	void finished(QTreeModel* model);

private:
	void setChildItemCheckState(int row, int state, const QModelIndex & parent=QModelIndex());
	void setParentItemCheckState(const QModelIndex& parent=QModelIndex());

	void setChildItemCheckable(int row, bool checkable, const QModelIndex & parent=QModelIndex());

private:
	void saveRecords(QVector<DiffFile>& files, const QModelIndex & parent=QModelIndex());

protected:
	virtual void checkDiff() = 0;	//����ʵ�ֲ�����

	virtual void setCustomItemDelegate();
	virtual void setTreeModel(QTreeModel* model);

	virtual QModelIndex mapToSourceItem(const QModelIndex& index);

	virtual void mousePressEvent(QMouseEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);

protected:
	QTreeModel*	m_pModel;
	QDelegateSyncCommit*	m_pDelegate;

	bool		m_bRestrictFilter;	//�Ƿ���������ļ�

	QString		m_strWorkspace;		//����Ŀ¼
	QString		m_strHistory;		//��ʷ����Ŀ¼

	bool m_bCheckable;
};

class QTreeViewSyncCommitRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QTreeViewSyncCommitRunnable(const QString& workspace, const QString& history, const QString& record, bool checkable, bool enableRestrict, QObject* parent=0);
	virtual ~QTreeViewSyncCommitRunnable();

signals:
	void finished(QTreeModel* model);

public:
	virtual void run();

protected:
	virtual void check()=0;

	bool traceSubDir(const QString& folder, const QString& suffix="", const QModelIndex& pindex=QModelIndex());		//����Ŀ¼

	bool checkDir(const QString& folder, const QModelIndex& pindex=QModelIndex());		//����ļ���
	bool checkFile(const QString& name, const QModelIndex& pindex=QModelIndex());	//����ļ�

private:
	void checkBackupFiles();

protected:
	QString m_strWorkspace;	//�޸�Ŀ¼
	QString m_strHistory;	//��ʷĿ¼
	QString	m_strRecord;	//�ϴ��޸ļ�¼�ļ�

	bool m_bCheckable;
	bool m_bRestrictFilter;	//�Ƿ���������ļ� 

	QTreeModel*	m_pModel;

protected:
	QMap<QString, DiffFile>	m_files;		//�ϴ��޸ļ�¼�ļ�
	QMap<QString, DiffFile>	m_filesBackup;	//��ʷ�����ļ�
};

typedef QAbstractClassProducer<QTreeViewSyncCommit> QTreeViewSyncCommitProducer;
typedef QSharedObjectPtr<QTreeViewSyncCommitProducer> QTreeViewSyncCommitProducerPtr;
typedef QRegisterClassProducer<QString, QTreeViewSyncCommitProducerPtr> QTreeViewSyncCommitRegister;

template<typename T, class C>
class QRegisterTreeViewSyncCommit
{
public:
	QRegisterTreeViewSyncCommit(T t)
	{
		QTreeViewSyncCommitRegister::instance()->registerProducer(t, QTreeViewSyncCommitProducerPtr(new C));
	}
};

#define REGISTER_TREE_VIEW_SYNC_COMMIT_CLASS(name)	\
	static QRegisterTreeViewSyncCommit<QString, QClassProducer<name, QTreeViewSyncCommitProducer> > static##name##Instance(#name);

#define treeViewSyncCommitDynamicClass(key) \
	QTreeViewSyncCommitRegister::instance()->producer(key)==NULL? NULL:QTreeViewSyncCommitRegister::instance()->producer(key)->produce();

#endif // QTREEVIEWSYNCCOMMIT_H
