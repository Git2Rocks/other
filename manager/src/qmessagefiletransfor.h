#ifndef QMESSAGEFILETRANSFOR_H
#define QMESSAGEFILETRANSFOR_H

#include <QObject>
#include <QRunnable>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QFileInfoList>

#include "qimessage.h"
#include "extern.h"

/**
*	@Desc �����ʽ
*	@Author zlb
*	@Time 2011-3-31
*
*	QueryRoot:			QueryRoot|�û�ID
*	AnswerRoot:			AnswerRoot|�û�ID|·��
*	QueryPath:			QueryPath|�û�ID|·��|����ʽ
*	AnswerPath:			AnswerPath|�û�ID|��ѯ״̬(|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��)
*	QueryFile:			QueryFile|�û�ID|����·���ļ���
*	AnswerFile:			AnswerFile|�û�ID|��ѯ״̬(|�ļ���С)
*	QueryTransforFile	QueryTransforFile|�û�ID|�����ʽ
*	QueryRetransforFile	QueryRetransforFile|�û�ID|�����ʽ|��ʼλ��
*	AnswerTransforFile	AnswerTransforFile|�û�ID|�ļ����ݳ���|�ļ�����
*	QueryDir			QueryDir|�û�ID|Ŀ¼·��
*	QuerySymLink		QuerySymLink|�û�ID|����·���ļ���
*	AnswerSymLink		AnswerSymLink|�û�ID||��ѯ״̬(|������Ϣ)
*	QueryDrive			QueryDrive|�û�ID
*	AnswerDrive			AnswerDrive|�û�ID|�ļ�����|�ļ�����|����|�ֽڴ�С|�ɶ�|��д|��ִ��|����޸�ʱ��
**/

class QMessageFileTransfor : public QObject, public QIMessage
{
	Q_OBJECT

public:
	QMessageFileTransfor(QObject *parent=0);
	~QMessageFileTransfor();

	enum {Type=MSG_FILE_TRANSFER};

	enum MsgType
	{
		QueryRoot=0,			//�����Ŀ¼
		AnswerRoot,				//���ظ�Ŀ¼
		QueryPath,				//����·��
		AnswerPath,				//����·����������Ŀ¼�Լ��ļ���Ϣ(�򲻴��ڸ�Ŀ¼)
		QueryFile,				//�������ļ������ô����ʽ���ı��������ƣ�
		AnswerFileInfo,			//�����ļ���Ϣ(��С)�����ļ�������
		QueryTransforFile,		//�ļ�������ɣ����Դ����ļ�
		QueryRetransforFile,	//��ָ�����ȿ�ʼ�ش��ļ�
		AnswerTransforFile,		//�����ļ�����
		QueryDir,				//�������ļ���
		AnswerDir,				//�����ļ�����Ϣ
		QuerySymLink,			//��������������ļ�
		AnswerSymLink,
		QueryDrive,				//�������������
		AnswerDrive
	};

	enum QueryResult
	{
		QueryPathNoExist=0,		//�����ļ�·��������
		QueryPathValid,			//�����ļ�·����Ч
		QueryFileNoExist,		//�����ļ�������
		QueryFileUnreadable,	//�����ļ����ɶ�
		QueryFileValid,			//�����ļ���Ч
		QuerySymLinkNoLink		//�����ļ����Ƿ��������ļ�
	};

	enum SortFlags
	{
		SortName=0,				//����������
		SortTime,				//��ʱ������
		SortSize,				//����С����
		SortType,				//����������
		SortReversed=0x10		//��������������ʽ���ʹ��
	};

	enum FileType
	{
		Dir=0,
		File,
		SymLink,
		Drive,
		HideDir,
		HideFile,
		HideSymLink
	};

	enum FileTransforFormat
	{
		TextFormat=0,		//�ı���ʽ
		DataFormat			//�����Ƹ�ʽ
	};

public:
	virtual int type() const	{return Type;}

public:
	virtual QByteArray query(int msgType, quint32 usrID=-1, const QByteArray& contents="");
	virtual bool parse(QConnection* sender, QByteArray buffer, QObject* view=0);

public:
	bool addTransforFile(int usrID, QFile* file);
	void removeTransforFile(int usrID);

	QFile* transforFile(int usrID);

private slots:
	void finished(QConnection* sender, int msgType, quint32 usrID, QByteArray buffer);

	void timeout();

private:
	typedef struct _fileHandle
	{
		QFile*	file;
		int tick;
	}FileHandle;

	QMap<int, FileHandle>	m_mapFiles;

	QTimer		m_timer;
};

class QMessageFileTransforRunnable : public QObject, public QRunnable
{
	Q_OBJECT

public:
	QMessageFileTransforRunnable(QConnection* sender, const QByteArray& buffer, QObject* view, QObject* parent=0);
	virtual ~QMessageFileTransforRunnable();

signals:
	void finished(QConnection* sender, int msgType, quint32 usrID, QByteArray buffer);

public:
	void setArg(QConnection* sender, const QByteArray& buffer, QObject* view);
	virtual void run();

private:
	void entryInfoList(QFileInfoList& list, QVector<FileInfo>& files);
	void readContents(QFile* file, int format, QByteArray& buffer);

private:
	QConnection*	m_pSender;
	QByteArray		m_buffer;
	QObject*		m_pView;
};

#endif // QMESSAGEFILETRANSFOR_H
