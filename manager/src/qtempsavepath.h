#ifndef QTEMPSAVEPATH_H
#define QTEMPSAVEPATH_H

#include <QAbstractItemModel>

#include "extern.h"
#include "qservermanager.h"
#include "qclientmanager.h"
#include "qabstractfiletransfer.h"
#include "qframefilesystem.h"

class QTempSavePath : public QObject, public QAbstractFileTransfer
{
	Q_OBJECT

public:
	QTempSavePath(QAbstractItemModel* model, const QModelIndex& index, int kind, 
		const QString& subPath, QObject *parent=0);
	~QTempSavePath();

public:
	void setClient(const QServerManager::ServerInfo& info);

public:
	void queryRoot();
	void queryPath(const QString& path);

protected:
	virtual void recvRoot(const QString& root);
	virtual void recvPath(const QString& path, int flag, const QVector<FileInfo>& files);

private slots:
	void connected(QClient* client);
	void disconnected(QClient* client);

private:
	QAbstractItemModel*	m_pModel;
	QModelIndex			m_index;

	QClient*			m_pClient;
	QClientManager*		m_pClientManager;

	quint32		m_nUsrID;		//�û�ID�����ڲ�ѯĿ¼��Ϣ

	int			m_nKind;		//·������
	QString		m_strDefault;	//Ĭ��·��

	QString		m_strRoot;		//�������и�Ŀ¼
	QString		m_strSubPath;	//����ڸ�Ŀ¼��·��
};

#endif // QTEMPSAVEPATH_H
