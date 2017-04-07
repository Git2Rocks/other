#ifndef QLISTVIEWFILERECEIVER_H
#define QLISTVIEWFILERECEIVER_H

#include <QListView>
#include <QStandardItemModel>

#include "qutildef.h"
#include "qserverdelegate.h"
#include "qreadwritexmlfile.h"
#include "qabstractmonitor.h"

class QMonitorFileReceiver;
class QListViewFileReceiver : public QListView
{
	Q_OBJECT

public:
	QListViewFileReceiver(const QString& xmlfile, const QString& record, const QString& subPath, QWidget *parent=0);
	~QListViewFileReceiver();

	enum UserRole
	{
		ItemTypeRole=Qt::UserRole,
		ItemUserDataRole,
		ServerOnlineRole,
		ServerSelectRole,
		ServerSaveRole,		//�ļ�����Ŀ¼
		RoleEnd
	};

	enum ItemType
	{
		OriginItem,
		AddedItem
	};

	typedef struct _fileReceiver 
	{
		QString	name;		//���ն˱�ʶ
		QString workspace;	//���ն˱���Ŀ¼
		bool select;		//���ն��Ƿ�ѡ��
	}FileReceiver;

public:
	void clear();

	void addReceiver(const QPair<ServerInfo, int>& info);
	bool addReceiver(const Server& server);

	QList<Server> removeSelectedReceiver();

	bool hasSelected() const;
	int nextSelected(int row, ServerInfo& info) const;

	bool isAddedItem(int row) const;
	QString savePath(int row) const;

public slots:
	void clicked(const QModelIndex& index);

	void selectAll();
	void selectNone();

signals:
	void selectChanged(bool removable);
	void selectedChanged();

protected:
	virtual void paintEvent(QPaintEvent* event);

private slots:
	void changed(const QMap<QString, QListViewFileReceiver::FileReceiver>& receivers);

	virtual void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
	QListViewFileReceiver::FileReceiver& findReceiver(const ServerInfo& info);
	bool contains(const ServerInfo& info);

private:
	void setToolTip(const QModelIndex& index, const ServerInfo& info, const QString& savePath);
	void setToolTip(const QModelIndex& index, const Server& server, const QString& savePath);

private:
	QMonitorFileReceiver*	m_pMonitor;

	QStandardItemModel* m_pModel;
	QServerDelegate* m_pDelegate;

private:
	QString	m_strSubPath;	//Ĭ����Ŀ¼

	QMap<QString, QListViewFileReceiver::FileReceiver>	m_receivers;
};

bool operator==(const QListViewFileReceiver::FileReceiver& source, const QListViewFileReceiver::FileReceiver& target);

class QMonitorFileReceiver : public QAbstractMonitor
{
	Q_OBJECT

public:
	QMonitorFileReceiver(const QString& filename, const QString& type, QObject* watched, QObject* parent=0);
	~QMonitorFileReceiver();

public:
	virtual bool loadFile();
	void save(const QMap<QString, QListViewFileReceiver::FileReceiver>& receivers);

signals:
	void changed(const QMap<QString, QListViewFileReceiver::FileReceiver>& receivers);

private:
	QString		m_strRecord;	//��¼���ն˱����ļ���Ŀ¼����

	QMap<QString, QListViewFileReceiver::FileReceiver>	m_receivers;
};

class QReadFileRecevierFromXmlFile : public QAbstractReadXmlFile
{
public:
	QReadFileRecevierFromXmlFile(const QString& filename, const QString& type);
	~QReadFileRecevierFromXmlFile();

public:
	QMap<QString, QListViewFileReceiver::FileReceiver>	result()
	{
		return m_results;
	}

protected:
	virtual void readNode(QXmlStreamReader& reader);

private:
	void readTransferNode(QXmlStreamReader& reader);
	void readTypeNode(QXmlStreamReader& reader);
	void readReceiversNode(QXmlStreamReader& reader);
	void readReceiverNode(QXmlStreamReader& reader);

private:
	QString		m_strType;

	QMap<QString, QListViewFileReceiver::FileReceiver>	m_results;
};

class QWriteFileRecevierToXmlFile : public QAbstractWriteXmlFile
{
public:
	QWriteFileRecevierToXmlFile(const QString& filename, const QString& type, const QVector<QListViewFileReceiver::FileReceiver>& receivers);
	~QWriteFileRecevierToXmlFile();

protected:
	virtual QString parentNodeName() const
	{
		return "transfer";
	}

	virtual void save(QDomDocument& doc, QDomElement& parent);

private:
	QDomElement findChildElement(QDomDocument& doc, QDomElement& parent, const QString& tag);

private:
	QString				m_strType;
	QVector<QListViewFileReceiver::FileReceiver>	m_receivers;
};

#endif // QLISTVIEWFILERECEIVER_H
