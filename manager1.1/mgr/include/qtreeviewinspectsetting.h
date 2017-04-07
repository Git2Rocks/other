#ifndef QTREEVIEWINSPECTSETTING_H
#define QTREEVIEWINSPECTSETTING_H

#include <QTreeView>

#include "qutildef.h"
#include "qtreemodel.h"
#include "qabstractreadwritexmlfile.h"
#include "qinspectsettingdelegate.h"
#include "qclientmanager.h"
#include "qreceiverinspect.h"

class QReadInspectRecordFormXmlFile : public QAbstractReadXmlFile
{
public:
	QReadInspectRecordFormXmlFile(const QString& filename);
	~QReadInspectRecordFormXmlFile();

public:
	typedef struct _inspectItem 
	{
		int id;
		bool checked;

		QMap<int, _inspectItem> children;
	}InspectItem;

public:
	InspectItem result()
	{
		return m_record;
	}

protected:
	virtual void readNode(QXmlStreamReader& reader);

private:
	void readInspectionNode(QXmlStreamReader& reader);
	void readInspectNode(QXmlStreamReader& reader);
	void readItemNode(QXmlStreamReader& reader, QMap<int, InspectItem>& items);

private:
	InspectItem	m_record;
};

class QWriteInspectRecordToXmlFile : public QAbstractWriteXmlFile
{
public:
	QWriteInspectRecordToXmlFile(const QString& filename, const QReadInspectRecordFormXmlFile::InspectItem& records);
	~QWriteInspectRecordToXmlFile();

protected:
	virtual QString parentNodeName() const
	{
		return "Inspection";
	}

	virtual void save(QDomDocument& doc, QDomElement& parent);

private:
	void saveRecords(QDomDocument& doc, QDomElement& node, const QReadInspectRecordFormXmlFile::InspectItem& items);

private:
	QReadInspectRecordFormXmlFile::InspectItem		m_records;
};

class QTreeViewInspectSetting : public QTreeView
{
	Q_OBJECT

public:
	QTreeViewInspectSetting(QWidget *parent=0);
	~QTreeViewInspectSetting();

public:
	enum TitleLabel
	{
		NameTitle,
		TitleLabelEnd
	};

	enum ItemRoleType
	{
		TitleItem,
		ChildItem
	};

	enum StatusRoleType
	{
		Connecting,		//����������
		Unconnected,	//����ʧ��
		DataLoading,	//���ݼ�����
		DataLoaded,		//���ݼ������
		H9000NotRunning	//H9000δ����
	};

	enum UserDataRole
	{
		ItemRole=Qt::UserRole,
		StatusRole,		//TitleItem ��״̬����
		CheckedRole,	//��ѡ���ʶ
		MsgParamRole,	//��������ͨ�Ų�ѯ
		DataRole,		//�û�����
		InspectRole		//�Ƿ����Ѳ��
	};

	typedef struct _inspectItem 
	{
		int id;
		int msgParam;
		QString desc;

		QVector<_inspectItem> children;
	}InspectItem;

public:
	void setClient(const ServerInfo& info);

public:
	void setItemCheckState(int row, int state, const QModelIndex& parent);
	InspectItem writeConfigure();

protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);

signals:
	void refreshKeyPress();
	void enableInspect(bool enable);

private slots:
	void connected(QClient* client);
	void unconnected(QClient* client);
	void disconnected(QClient* client);

	void cscsDataSourceLost();
	void recvCscsDatabase(CscsDatabase db);

private:
	void init();

	void setTitleItemStatus(int paramRole, StatusRoleType statusRole);

private:
	int refreshItemCheckedState(const QReadInspectRecordFormXmlFile::InspectItem& item, const QModelIndex & index=QModelIndex());

	void setChildItemCheckState(int row, int state, const QModelIndex & parent=QModelIndex());
	void setParentItemCheckState(const QModelIndex& parent=QModelIndex());

	void writeItemCheckedState(InspectItem& item, QReadInspectRecordFormXmlFile::InspectItem& record, const QModelIndex & parent=QModelIndex());

private:
	QClient*			m_pClient;
	QClientManager*		m_pClientManager;

	QReceiverInspect*	m_pReceiver;

	QTreeModel*					m_pModel;
	QInspectSettingDelegate*	m_pDelegate;

	QReadInspectRecordFormXmlFile::InspectItem	m_record;
};

Q_DECLARE_METATYPE(QVector<QTreeViewInspectSetting::InspectItem>)

#endif // QTREEVIEWINSPECTSETTING_H
