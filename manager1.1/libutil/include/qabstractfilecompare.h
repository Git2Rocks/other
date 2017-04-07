#ifndef QABSTRACTFILECOMPARE_H
#define QABSTRACTFILECOMPARE_H

#include <QAbstractItemModel>
#include <QTextStream>
#include <QStack>

#include "qutildef.h"
#include "qsharedobject.h"

enum CompareFileType
{
	COMPARE_UNKNOW_FILE=-1,
	COMPARE_STATION_DEF_FILE,
	COMPARE_GROUP_DEF_FILE,
	COMPARE_RECORD_DEF_FILE,
	COMPARE_MSG_DEF_FILE,
	COMPARE_CMD_MSG_FILE,
	COMPARE_DBIO_DEF_FILE,
	COMPARE_GEN_FILE,
	COMPARE_TEXT_FILE,
	COMPARE_BINARY_FILE
};

#define COMPARE_FILE_WRITE_PROPERTY(stream, key, value)		stream<<"\t\t\t\t\t"<<key<<"\t= "<<value<<"\n"

class QAbstractFileCompare;
typedef QSharedObjectPtr<QAbstractFileCompare> QAbstractFileComparePtr;

class UTIL_EXPORT QAbstractFileCompare : public QSharedObject
{
public:
	QAbstractFileCompare();
	~QAbstractFileCompare();

public:
	enum ErrorCode
	{
		NoError,
		FileNoExistError,
		FileOpenError,
		FileWriteError,

		//�����ļ�У��
		UnknowError,
		FileNameIsEmptyError,
		KeyPropertyIsEmpryError,
		KeyPropertyRepeatError
	};

	enum UserDataRole
	{
		//�����ļ��Ա�
		RowRole=Qt::UserRole,
		ItemRole,

		//����ͬ������
		AssignRowRole,			//�б���ֵ(��ֵΪ��ֵ�еĽ�ɫ)
		AssignItemRole,			//�����Ա���ֵ(true/false)
		VerifyItemRole,			//������У��(true/false)

		//����ѡ�в���
		SelectRowRole,			//ѡ���У����ڽ�����ʾ
		SelectItemRole			//ѡ��ĳһ���ԣ����ڽ�����ʾ
	};

	enum RoleType
	{
		//�����ļ��Ա�
		AppendRowRole,		//������
		DeleteRowRole,		//ɾ����
		ModifyRowRole,		//�޸���
		CommonRowRole,		//��ͬ��
		BlankRowRole,		//�հ���
		AddItemRole,
		DeleteItemRole,
		ModifyItemRole,
		CommonItemRole,

		//����ѡ�в���
		NoSelectRowRole,
		SelectBeginRowRole=(1<<4),	//ѡ����ʼ��
		SelectEndRowRole=(1<<5)		//ѡ�н�����
	};

	typedef struct
	{
		int type;		//�ļ�����
		int errcode;	//�ļ���ȡ�������

		QString filename;

		QVariant data;	//��ȡ���ļ��ṹ������

		QStringList titles;			//�б���
		QAbstractItemModel* model;	//����Դ
	}FileCompareResult;

public:
	virtual int type() const=0;
	virtual bool match(const QString& filename) const=0;

public:
	FileCompareResult parse(const QString& filename);
	void compare(FileCompareResult& source, FileCompareResult& target);

	bool isModified(FileCompareResult& source, FileCompareResult& target);
	bool isHeaderHidden(const FileCompareResult& source, const FileCompareResult& target) const;

	virtual int write(FileCompareResult& source, FileCompareResult& target, QPair<QModelIndex, QModelIndex>& error);	//errorΪ�������ֵ�������ϴδ���
	int write(QIODevice* device, FileCompareResult& result, QPair<QModelIndex, QModelIndex>& error);

	int check(FileCompareResult& result, QPair<QModelIndex, QModelIndex>& error);
	
public:
	void setNextChain(const QAbstractFileComparePtr& ptr, bool replace=false);
	QAbstractFileComparePtr& nextChain();

public:
	static QVector<QString> parseString(const QString& text);
	static void writeProperty(QTextStream& stream, const QString& key, const QString& value);
	static void writeGroup(QTextStream& stream, const QString& group, const QString& key, const QString& value);

protected:
	virtual void parseFile(QFile& file, FileCompareResult& result)=0;
	virtual void compareFile(FileCompareResult& source, FileCompareResult& target)=0;
	virtual int writeData(QIODevice* device, FileCompareResult& result)=0;
	virtual bool checkModified(FileCompareResult& source, FileCompareResult& target)=0;
	virtual int checkValidity(FileCompareResult& result, QPair<QModelIndex, QModelIndex>& error);

	//������UI��ʾ�й�
	virtual bool isHeaderHidden() const;

protected:
	QAbstractFileComparePtr	m_pChildChain;
};

#define RECORD_DEF_FILE "DATABASE.GEN"
#define CMD_MSG_FILE "CMD_MSG.DEF"
#define IOGROUP_DEF_FILE "DBIOGROUP.DEF"
#define GROUP_DEF_FILE "DATABASE.DEF"
#define MSG_DEF_FILE "MSG_DEF.DEF"
#define STATION_DEF_FILE "DBSTATION.DEF"

typedef struct
{
	QString grpName;
	QVector<QString> records;
}RECORD_GROUP_ENTRY;

typedef struct  
{
	QString stnName;

	QVector<RECORD_GROUP_ENTRY> groups;
}RECORD_STATION_ENTRY;

UTIL_EXPORT QVector<RECORD_STATION_ENTRY> parseRecordDefFile(QTextStream& stream);

typedef struct                                  /* station structure */
{
	QString	stnName;
	QString	stnLongname;
	QString	stnComment;
	QString	stnExLongname;
	QString	stnExComment;
	uchar   stnId;
	uint	grp_num;                        /* Number of groups in the station	*/
} STATION_ENTRY;

UTIL_EXPORT QVector<STATION_ENTRY> parseStationDefFile(QTextStream& stream);

typedef	struct					/* group structure */
{
	QString	grpName;	
	QString	grpLongname; 
	QString	grpComment;
	QString	grpTypeName;
	QString	grpExLongname;
	QString	grpExComment;
	uchar	grpId;
	QString grpConditionDev;
	QString	grpConditionType;
	QString	grpConditionID;
} GROUP_ENTRY;

typedef struct
{
	QString stnName;
	QVector<GROUP_ENTRY> entries;
}GROUP_ENTRY_EX;

UTIL_EXPORT QVector<GROUP_ENTRY_EX> parseGroupDefFile(QTextStream& stream);

/**
*	@Desc ��������㷨Ϊ������㷨��ʱ�临�Ӷ�ΪO(n*m),�ռ临�Ӷ�ΪO(n*m)���ʲ��ʺϱȽϴ�����ݱȽ�
**/
template<class T>
class UTIL_EXPORT QLongestCommonSubsequence
{
public:
	QLongestCommonSubsequence() {};
	~QLongestCommonSubsequence() {};

public:
	QVector<QPair<int, int> > parse(const QVector<T>& t1, const QVector<T>& t2)	//�Ƚ�t1,t2���õ�����������У����ع������ж�
	{
		m_results.clear();

		int m=t1.size()+1;
		int n=t2.size()+1;

		int** score=new int*[m];
		int** trace=new int*[m];
		for (int i=0; i<m; i++)
		{
			score[i]=new int[n];
			trace[i]=new int[n];
		}

		for (int i = 0; i < m; i++)  
		{
			score[i][0] = 0;  
		}

		for (int i = 0; i < n; i++)  
		{
			score[0][i] = 0;  
		}

		for (int i = 1; i < m; i++)
		{  
			for (int j = 1; j < n; j++)
			{  
				if (t1[i - 1] == t2[j - 1])
				{  
					score[i][j] = score[(i - 1)][j - 1] + 1;  
					trace[i][j] = 1; 
				}
				else if (score[i - 1][j] >= score[i][j - 1])
				{  
					score[i][j] = score[i - 1][j];  
					trace[i][j] = 0;
				}
				else
				{  
					score[i][j] = score[i][j - 1];  
					trace[i][j] = -1;
				}  
			}  
		}

		goback(trace, m-1, n-1);

		for (int i=0; i<m; i++)
		{
			SAFE_DELETE_ARRAY(score[i]);
			SAFE_DELETE_ARRAY(trace[i]);
		}

		SAFE_DELETE_ARRAY(score);
		SAFE_DELETE_ARRAY(trace);

		return m_results.toVector();
	}

private:
	void goback(int** trace, int i, int j)
	{
		while (i!=0 && j!=0)
		{
			if(trace[i][j] == 1)
			{
				m_results.push_front(QPair<int, int>(--i, --j));
			}
			else if(trace[i][j] == 0)
			{  
				i--;
			}
			else
			{  
				j--;
			}  
		}
	}

private:
	QList<QPair<int, int> > m_results;
};

/**
*	@Desc ������л����㷨�ĸĽ��㷨�������˿ռ临�Ӷȱ������ӣ�����ΪO(n*m)
**/
template<class T>
class UTIL_EXPORT QLongestCommonSubsequenceV1
{
public:
	QLongestCommonSubsequenceV1() {};
	~QLongestCommonSubsequenceV1() {};

public:
	QVector<QPair<int, int> > parse(const QVector<T>& t1, const QVector<T>& t2)	//�Ƚ�t1,t2���õ�����������У����ع������ж�
	{
		m_results.clear();

		int m=t1.size()+1;
		int n=t2.size()+1;

		int** score=new int*[m];
		for (int i=0; i<m; i++)
		{
			score[i]=new int[n];
		}

		for (int i = 0; i < m; i++)  
		{
			score[i][0] = 0;  
		}

		for (int i = 0; i < n; i++)  
		{
			score[0][i] = 0;  
		}

		for (int i = 1; i < m; i++)
		{  
			for (int j = 1; j < n; j++)
			{  
				if (t1[i - 1] == t2[j - 1])
				{  
					score[i][j] = score[(i - 1)][j - 1] + 1;  
				}
				else
				{  
					score[i][j] = (score[i - 1][j] >= score[i][j - 1]? score[i - 1][j]:score[i][j - 1]);
				}
			}  
		}

		goback(score, m-1, n-1);

		for (int i=0; i<m; i++)
		{
			SAFE_DELETE_ARRAY(score[i]);
		}

		SAFE_DELETE_ARRAY(score);

		return m_results.toVector();
	}

private:
	void goback(int** score, int i, int j)
	{
		while (i!=0 && j!=0)
		{
			if(score[i][j] > score[i-1][j] && score[i][j] > score[i][j-1])
			{
				m_results.push_front(QPair<int, int>(--i, --j));
			}
			else
			{
				score[i][j-1] > score[i-1][j]? j--:i--;
			}
		}
	}

private:
	QList<QPair<int, int> > m_results;
};

/**
*	@Desc �������Nakatsu�㷨���ռ临�Ӷ�O(n)
**/
static const int MAX_VALUE=0x7fffffff;
template<class T>
class UTIL_EXPORT QLongestCommonSubsequenceV2
{
public:
	QLongestCommonSubsequenceV2() {};

	~QLongestCommonSubsequenceV2() {};

public:
	QVector<QPair<int, int> > parse(const QVector<T>& t1, const QVector<T>& t2)	//�Ƚ�t1,t2���õ�����������У����ع������ж�
	{
		QVector<QPair<int, int> > results;

		if (t1.isEmpty() || t2.isEmpty())
		{
			return results;
		}

		int nLen=t1.size()+1;
		int* L=new int[nLen];

		if (L == NULL)
		{
			return results;
		}

		QMap<int, QVector<QPair<int, int> > > matches;		//QMap<k, QVector<QPair<i, j> > >
		L[0]=0;

		for (int i=1; i<nLen; i++)
		{
			L[i]=MAX_VALUE;
		}

		int nValue;
		int nLenMatch=0;
		for (int i=0; i<nLen; i++)
		{
			for (int k=1; k<nLen-i; k++)
			{
				nValue=find(i+k-1, L[k-1], L[k], t1, t2);
				if (nValue < L[k])
				{
					L[k]=nValue;
					matches[k].append(QPair<int, int>(i+k-1, nValue-1));
				}
				else if (L[k] == MAX_VALUE)
				{
					break;
				}
			}

			if (L[nLen-i-1] < MAX_VALUE)
			{
				nLenMatch=nLen-i-1;

				break;
			}
		}

		SAFE_DELETE_ARRAY(L);

		if (nLenMatch > 0)
		{
			results.resize(nLenMatch);

			QPair<int, int> peer=matches[nLenMatch].last();
			results[nLenMatch-1]=peer;
			for (int nIndex=nLenMatch-1; nIndex > 0; nIndex--)
			{
				const QVector<QPair<int, int> >& candidates=matches[nIndex];
				for (int m=candidates.size()-1; m>=0 ; m--)
				{
					if (candidates[m].first < peer.first)
					{
						peer=candidates[m];
						results[nIndex-1]=peer;
						break;
					}
				}
			}
		}

		return results;
	}

private:
	int find(int index, int start, int end, const QVector<T>& t1, const QVector<T>& t2)
	{
		if (end == MAX_VALUE)
		{
			end=t2.size()+1;
		}

		for (int i=start+1; i<end; i++)
		{
			if (t1[index] == t2[i-1])
			{
				return i;
			}
		}

		return MAX_VALUE;
	}
};

typedef void (*CreateFileCompareInstanceFunc)(QVector<QAbstractFileComparePtr>& instances);		//�Ƚ��ද̬������ṩ�Ľӿ�

#define SYNC_H9000_FILE_COMMON_CONF_FILE "ini/data/sync.xml"
#define SYNC_H9000_FILE_LOCAL_PATH	"ini/data/localhost/"
#define SYNC_H9000_FILE_REQUEST_RECORD_PATH "ini/data/"
#define SYNC_H9000_DATABASE_FILE_LOCAL_RECORD_FILE "/ini/data/localhost/database.xml"

#endif // QABSTRACTFILECOMPARE_H
