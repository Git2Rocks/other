#ifndef QTREEVIEWINSPECT_H
#define QTREEVIEWINSPECT_H

#include <QTreeView>
#include <QRunnable>

#include "qutildef.h"
#include "qtreemodel.h"
#include "qtreeviewinspectsetting.h"
#include "qinspectdelegate.h"
#include "qclientmanager.h"
#include "qreceiverinspect.h"

class QTreeViewInspect : public QTreeView
{
	Q_OBJECT

public:
	QTreeViewInspect(QWidget *parent=0);
	~QTreeViewInspect();

public:
	enum TitleLabel
	{
		NameTitle,
		StatusTitle,
		TitleLabelEnd
	};

	enum ItemRoleType
	{
		PeerItem,
		GroupItem,
		ChildItem
	};

	enum ItemStatusType
	{
		Initialized,
		Connecting,
		Unconnected,
		Connected,
		Reconnecting,
		Collecting,		//�����ռ�...
		Verifying,		//������֤...
		Skip,			//����
		Completed,		//�ռ��ο�Դ�������
		Failed,			//�ռ�����Դʧ��
		Match,
		Mismatch
	};

	enum ItemCauseType
	{
		H9000NotRunning,		//H9000δ����
		DataSourceNoExisted,	//����Դ������
		NoReferenceSource,		//�޲ο�Դ
		ServiceQuit				//�������˳�
	};

	enum UserDataRole
	{
		ItemRole=Qt::UserRole,
		PeerInfoRole,
		ComparedRole,
		MsgParamRole,	//��������ͨ�Ų�ѯ
		DataRole,		//�û�����
		StatusRole,		//Ѳ��״̬
		CauseRole		//����ԭ��
	};

public:
	void setInspectItems(const ServerInfo& info, const QTreeViewInspectSetting::InspectItem& items);

	void inspect(bool init=false);

	void pause(bool state);
	void cancel();

signals:
	void sendMessage(QString tip);
	void finished(int normal, int skip, int total);
	void progress(int value, int min, int max);
	void addItemsFinished();

protected:
	virtual void resizeEvent(QResizeEvent* event);

private slots:
	void addInspectItemsFinished(QTreeModel* model, int count);

	void connected(QClient* client);
	void unconnected(QClient* client);
	void disconnected(QClient* client);

	void cscsDataSourceLost();
	void cscsDataSourceNoExisted();
	void recvCscsStationEigenvalue(int stn, QByteArray buffer);
	void recvCscsGroupEigenvalue(int stn, int group, QByteArray buffer);
	void recvCscsRecordEigenvalue(int stn, int group, int datatype, QByteArray buffer);
	void recvCscsEigenvalue(QByteArray buffer);

private:
	void nextTask();
	void setData(const QModelIndex& index, const QVariant& value, int role);

	void restore(const QModelIndex& pindex=QModelIndex());
	int childrenCount(const QModelIndex& index);

private:
	QTreeModel*			m_pModel;
	QInspectDelegate*	m_pDelegate;

	QClientManager*		m_pClientManager;
	QReceiverInspect*	m_pReceiver;

	QModelIndex			m_index;
	QClient*			m_pClient;
	bool				m_bInpecting;
	bool				m_bReconnecting;

	int		m_nMsg;		//Ѳ������Ϣ����ID
	int		m_nAck;		//Ѳ������ϢӦ��ID

	bool	m_bReference;	//�ο�Դ
	QMap<QByteArray, QByteArray>	m_data;	//Ѳ��ο�Դ����

	int		m_nNumItems;	//����Ѳ�������
	int		m_nCurItem;		//��ǰѲ�����
	int		m_nNumNormal;	//Ѳ����������
	int		m_nNumSkip;		//��������

	bool	m_bPause;
};

class QTreeViewInspectRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QTreeViewInspectRunnable(const ServerInfo& info, const QTreeViewInspectSetting::InspectItem& items, QObject* parent=0);
	virtual ~QTreeViewInspectRunnable();

signals:
	void finished(QTreeModel* model, int count);

public:
	virtual void run();

private:
	void addInspectGroup(const ServerInfo& info, const QTreeViewInspectSetting::InspectItem& items, bool compared=false);
	void addInspectItem(const QTreeViewInspectSetting::InspectItem& item, const QModelIndex& parent, bool isGroup, const QByteArray& buffer="");

private:
	ServerInfo	m_info;		//�ο�����Դ������Ϣ
	QTreeViewInspectSetting::InspectItem	m_items;	//Ѳ����

	QTreeModel*	m_pModel;
	int			m_nNumItems;	//Ѳ��������
};

#endif // QTREEVIEWINSPECT_H
