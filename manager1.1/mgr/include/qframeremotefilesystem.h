#ifndef QFRAMEREMOTEFILESYSTEM_H
#define QFRAMEREMOTEFILESYSTEM_H

#include <QDir>

#include "qservermanager.h"
#include "qclientmanager.h"
#include "qabstractreceiver.h"
#include "qframefilesystem.h"
#include "qframeremotefilesystem.h"

class QFrameRemoteFileSystem : public QFrameFileSystem, public QAbstractReceiver
{
	Q_OBJECT

public:
	QFrameRemoteFileSystem(const QString& initPath, const QString& subPath, QWidget *parent=0);
	~QFrameRemoteFileSystem();

public:
	enum TipType
	{
		Information,
		Warning,
		Error,
		TipEnd
	};

public:
	void setClient(const ServerInfo& info);

	QVector<TransferFileItem> selectedFileItems();
	QVector<FileInfo> selectedItems();

	void setFilters(const QStringList& nameFilters, QDir::Filters filters = QDir::NoFilter);

	QString locationText();
	QString currentLocationText();

	bool canUpload();
	bool canDelete();
	bool canOpen();
	bool canRename();
	bool canNewDir();

	void deepRefresh();

	void doubleClickedLocation();

	void gotoHome();
	void gotoLocation(const QString& location);

public:
	void queryRoot();
	void queryDrives();
	void queryPath(const QString& path);

	void queryRename(const QString& location, const QString& old, const QString& now);
	void queryNewDirectory(const QString& location);
	void queryDelete(const QString& location, const QVector<QString>& files);

public slots:
	void refresh();

	void editTextChangedLocation(const QString& location);

	void newDirectory();
	void delDirectory();
	void rename();

signals:
	void unconnected();		//Ϊ��������
	void serverQuit();		//�������˳�
	void dirNoExist(const QString& dir);	//����Ŀ¼������
	void rootDirDeleted();	//��������Ŀ¼������

	void enterInvalidChar(bool invalid, const QChar& ch);
	void focusStatusChanged(bool has);
	void mouseRightButtonPress(QPoint pos);

	void tip(int type, const QString& tip);

protected:
	virtual void recvRoot(const QString& root);
	virtual void recvDrives(const QVector<FileInfo>& drives);
	virtual void recvPath(const QString& path, int flag, const QVector<FileInfo>& files);
	virtual void recvNewDirectory(int flag, const FileInfo& file);
	virtual void recvDelete(int flag, const QVector<QString>& files);
	virtual void recvRename(int flag, const QString& dir, const QString& old, const QString& now);

private slots:
	void enterPressed(QString location);
	void clickedToolButton(int type);

	void locationCurrentIndexChanged(QString location);
	void doubleClickedLocation(const QModelIndex& index);
	void dataChanged(QModelIndex index, QString old, QString now);

	void mouseRightButtonPressed(QPoint pos);

	void connected(QClient* client);

private:
	QClient*			m_pClient;
	QClientManager*		m_pClientManager;

	quint32		m_nUsrID;		//�û�ID�����ڲ�ѯĿ¼��Ϣ

	QString		m_strRoot;		//�������и�Ŀ¼
	QString		m_strSubPath;	//����ڸ�Ŀ¼��·��

	QString		m_strInitPath;	//��ʼ·��

	bool		m_bQueryComputer;	//�����ȡ�������������Ϣ

private:
	QStringList		m_nameFilters;
	QDir::Filters	m_filters;
};

#endif // QFRAMEREMOTEFILESYSTEM_H
