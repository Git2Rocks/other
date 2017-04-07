#ifndef QTREEVIEWUPDATEFILE_H
#define QTREEVIEWUPDATEFILE_H

#include <QTreeView>
#include <QPoint>
#include <QRunnable>
#include <QStyledItemDelegate>
#include <QPainter>

#include "qutildef.h"
#include "qtreemodel.h"
#include "qfilecomparefactory.h"
#include "qreadwritexmlfile.h"

class QUpdateFileDelegate;
class QTreeViewUpdateFile : public QTreeView
{
	Q_OBJECT

public:
	QTreeViewUpdateFile(QWidget *parent=0);
	~QTreeViewUpdateFile();

public:
	enum TitleLabel
	{
		NameTitle,
		SizeTitle,
		TypeTitle,
		StatusTitle,
		UpdatedTitle
	};

	enum ItemRoleType
	{
		GroupRole,
		FileRole
	};

	enum UserData
	{
		ItemRole=Qt::UserRole,		//��ɫ����
		CheckedRole,				//ѡ��
		DiffFileRole,				//�����ļ���Ϣ
		LocalFileRole				//�����ļ���Ϣ
	};

public:
	void setWorkspace(const QString& workspace, const QString& hostname, const QString& address);

	QVector<QPair<DiffFile, FileInfo> > selectedItems(const QModelIndex& parent=QModelIndex());
	bool hasSelected() const;

	QModelIndexList manuSelectItems();	//ѡ�񣬲�����check��־��ѡ��
	bool hasManuSelected() const;

	bool fetchItem(int row, QPair<DiffFile, FileInfo>& peer, const QModelIndex& parent=QModelIndex());
	bool fetchItem(const QModelIndex& index, QPair<DiffFile, FileInfo>& peer);

	int rowCount(const QModelIndex& parent=QModelIndex()) const;

	int itemState(int row, const QModelIndex & parent=QModelIndex()) const;
	void setItemState(int row, int state, const QModelIndex & parent=QModelIndex());

	int itemRole(int row, const QModelIndex & parent=QModelIndex()) const;

	virtual void setItemCheckState(int row, int state, const QModelIndex& parent=QModelIndex());
	int itemCheckState(int row, const QModelIndex& parent=QModelIndex()) const;

	void itemModified(const QModelIndex& index);

	bool hasModifiedItem() const;

	QTreeModel*	copy() const;

	void checkItems(int state, const QModelIndex& parent=QModelIndex());

	void setRestrictFilterEnabled(bool enable);
	void setLocalLastModifiedEnabled(bool enable);

public:
	void setCustomModel(QTreeModel* model);

	virtual QModelIndex mapToSourceItem(const QModelIndex& index);
	virtual QModelIndex mapFromSourceItem(const QModelIndex& index);

public:
	virtual QString record() const=0;
	virtual QString commonFolder() const=0;	//Ĭ�Ϲ���Ŀ¼

	virtual void checkModified(const QString& workspace, const QString& hostname, const QString& address)=0;

// public:
// 	void save(const QString& filename);		//path=folder����ֵ
// 	void save();

public:
	static bool isModified(const QTreeModel* model);

public:
	void clear();

Q_SIGNALS:
	void refreshKeyPress();

	void refreshModelFinished();
	void mouseRightButtonPressed(QPoint pos);

	void findModified(QString hostname, QString address);

	void selectedChanged();

private slots:
	void finished(QTreeModel* model);

private:
	void setChildItemCheckState(int row, int state, const QModelIndex & parent=QModelIndex());
	void setParentItemCheckState(const QModelIndex& parent=QModelIndex());

private:
	void setParentItemState(const QModelIndex & parent=QModelIndex());

//	void recordFiles(QVector<DiffFile>& files, const QModelIndex & parent=QModelIndex());

private:
	void copyChildrenItems(const QTreeModel* smodel, const QModelIndex & sparent, QTreeModel* tmodel, const QModelIndex & tparent) const;

protected:
	virtual void check() = 0;

	virtual void setCustomItemDelegate();
	virtual void setTreeModel(QTreeModel* model);

protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);

protected:
	QTreeModel*	m_pModel;
	QUpdateFileDelegate*	m_pDelegate;

	bool		m_bRestrictFilter;	//�Ƿ���������ļ�
	bool		m_bLocalLastModified;	//�Ƿ�ʹ�ñ����ļ��޸�����

	QString		m_strWorkspace;		//��ǰ����Ŀ¼
	QString		m_strHostName;		//ͬ�������û���
	QString		m_strAddress;		//ͬ������IP��ַ
};

typedef QAbstractClassProducer<QTreeViewUpdateFile> QTreeViewUpdateFileProducer;
typedef QSharedObjectPtr<QTreeViewUpdateFileProducer> QTreeViewUpdateFileProducerPtr;
typedef QRegisterClassProducer<QString, QTreeViewUpdateFileProducerPtr> QTreeViewUpdateFileRegister;

template<typename T, class C>
class QRegisterTreeViewUpdateFile
{
public:
	QRegisterTreeViewUpdateFile(T t)
	{
		QTreeViewUpdateFileRegister::instance()->registerProducer(t, QTreeViewUpdateFileProducerPtr(new C));
	}
};

#define REGISTER_TREE_VIEW_UPDATE_FILE_CLASS(name)	\
	static QRegisterTreeViewUpdateFile<QString, QClassProducer<name, QTreeViewUpdateFileProducer> > static##name##Instance(#name);

#define treeViewUpdateFileDynamicClass(key) \
	QTreeViewUpdateFileRegister::instance()->producer(key)==NULL? NULL:QTreeViewUpdateFileRegister::instance()->producer(key)->produce();

class QUpdateFileRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QUpdateFileRunnable(const QString& workspace, const QString& catagory, 
		const QString& hostname, const QString& address, bool restrictFilter, bool localLastModified, bool immediate=false, QObject* parent=0);
	virtual ~QUpdateFileRunnable();

signals:
	void finished(QTreeModel* model);
	void modified(QString hostname, QString address);

public:
	virtual void run();

	bool check(bool immediate=true);	//����Ƿ����޸ģ�immediate=true�������أ����ڼ��ʱ�����޸�

protected:
	virtual bool readFiles(bool immediate) = 0;

	bool traceSubDir(const QString& folder, const QString& suffix="", bool immidate=true, const QModelIndex& pindex=QModelIndex());		//����Ŀ¼

protected:
	bool readDir(const QString& folder, bool immediate=true, const QModelIndex& pindex=QModelIndex());		//����ļ���
	bool readFile(const QString& name, bool immediate=true, const QModelIndex & pindex=QModelIndex());

	void findRequestFiles();

protected:
	QString m_strWorkspace;	//��ǰ����Ŀ¼
	QString m_strCatagory;	//����
	QString m_strHostName;	//ͬ�������û���
	QString	m_strAddress;	//ͬ������IP��ַ

	bool m_bImmediate;
	bool m_bRestrictFilter;
	bool m_bLocalLastModified;

	QTreeModel*	m_pModel;

	QMap<QString, DiffFile>	m_files;			//���ظ���ʱ�Ѹ��µ��ļ���Ϣ
	QMap<QString, DiffFile>	m_filesRequest;		//������µ��ļ���Ϣ
};

class QReadUpdateRecordsFromXmlFile : public QAbstractReadXmlFile
{
public:
	QReadUpdateRecordsFromXmlFile(const QString& filename, const QString& path, const QString& hostname, const QString& address);
	~QReadUpdateRecordsFromXmlFile();

public:
	QMap<QString, DiffFile>	result()
	{
		return m_files;
	}

protected:
	virtual void readNode(QXmlStreamReader& reader);

private:
	void readWorkspaceNode(QXmlStreamReader& reader);
	void readFolder(QXmlStreamReader& reader);
	void readFile(QXmlStreamReader& reader);

private:
	QMap<QString, DiffFile>	m_files;			//���ؼ�¼���ļ�

	QString		m_strPath;
	QString		m_strHostName;
	QString		m_strAddress;
};

class QWriteUpdateRecordsToXmlFile : public QAbstractWriteXmlFile
{
public:
	QWriteUpdateRecordsToXmlFile(const QString& filename, const QString& path, 
		const QString& hostname, const QString& address, const QVector<DiffFile>& files);
	~QWriteUpdateRecordsToXmlFile();

protected:
	virtual QString parentNodeName() const
	{
		return "workspace";
	}

	virtual bool check(const QDomElement& node) const;
	virtual void save(QDomDocument& doc, QDomElement& parent);

private:
	QString		m_strPath;
	QString		m_strHostName;
	QString		m_strAddress;

	QVector<DiffFile>	m_files;
};

class QUpdateFileDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QUpdateFileDelegate(QObject* parent=0);
	~QUpdateFileDelegate();

public:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

protected:
	void drawItem(QPainter* painter, const QStyleOptionViewItem& option, const QAbstractItemModel* model, const QModelIndex& index) const;
};

#endif // QTREEVIEWUPDATEFILE_H
