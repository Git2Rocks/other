#ifndef QFILECOMPAREFACTORY_H
#define QFILECOMPAREFACTORY_H

#include <QMutex>
#include <QMap>

#include "qabstractfilecompare.h"
#include "qutildef.h"

enum FileModifiedStatus
{
	Modified,		//���޸ĵ�
	Added,			//��ӵ�
	Deleted,		//ɾ����
	Unmodified,		//δ�޸ĵ�
	NonVersioned,	//�Ѵ��ڣ��������Ե�
	ModifiedStatusEnd
};

enum FileUpdateFlag
{
	Modify=Modified,	//�޸�
	Add=Added,			//���
	Latest=ModifiedStatusEnd,			//�ļ��������µ�
	Delete,				//ɾ��
	UpdateFlagEnd
};

typedef struct _diffFile 
{
	QString path;	//�ļ����·����
	quint64 size;	//�ļ���С
	int type;		//�ļ�����
	QDateTime modified;		//�޸�����
	int status;		//�ļ��޸ı�ʶ
	int version;	//�ļ��޸İ汾
}DiffFile;

class UTIL_EXPORT QFileCompareFactory : public QObject
{
	Q_OBJECT

public:
	virtual ~QFileCompareFactory();

	typedef struct _fileCompareResult
	{
		QAbstractFileCompare::FileCompareResult source;
		QAbstractFileCompare::FileCompareResult target;
	}FileCompareResult;

protected:
	QFileCompareFactory();

public:
	static QFileCompareFactory* instance();

public:
	FileCompareResult compare(const QString& source, const QString& target);
	QAbstractFileCompare::ErrorCode write(QAbstractFileCompare::FileCompareResult& source, QAbstractFileCompare::FileCompareResult& target, 
		QPair<QModelIndex, QModelIndex>& error);

	bool isModified(const QString& source, const QString& target);
	bool isHeaderHidden(const FileCompareResult& result) const;

public:
	bool loadLibrary(const QString& filename, const char* symbol);

public:
	void registerProduct(const QAbstractFileComparePtr& ptr);

private:
	QAbstractFileComparePtr	m_pChains;

	QMutex	m_mutex;
};

Q_DECLARE_METATYPE(QFileCompareFactory::FileCompareResult)
Q_DECLARE_METATYPE(DiffFile)

#endif // QFILECOMPAREFACTORY_H
