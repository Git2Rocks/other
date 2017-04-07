#ifndef _CALCULATION_H
#define _CALCULATION_H

#include <QString>
#include <QStringList>
#include "/home/ems/system/ots/ots_hdb/inc/ots_hdb.h" 
#include "Login.h"
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>

#define SUBJECT_TYPE_ALARM	0   //������Ϣ
#define	SUBJECT_TYPE_CMD	1	//����
#define	SUBJECT_TYPE_OPR	2	//�ֵز���
#define SUBJECT_TYPE_CHECK	3	//�豸���

#define SUBJECT_STATUS_UNJUDGE -1
#define SUBJECT_STATUS_FINISH	0
#define SUBJECT_STATUS_UNFINISH	1
#define SUBJECT_STATUS_UNSATISFIYED	2
#define SUBJECT_STATUS_DISORDER	3
#define SUBJECT_KEYBEFOREUNFINISH_BUTRIGHT	4
#define SUBJECT_KEYBEFOREUNFINISH_ANDWRONG	5

typedef struct
{
	DATA_SUBJECT data_subject;
	int status;// 0����� 1��δ��� 2���ؼ���������δ���� 3���������ǰ��������
}SUBJECT_INFO;

typedef struct _RECORD_INFO
{
	QDateTime	datetime;
	short	type;
	char	station_id;	
	char	dev_id;	
	int		task_id;
	int		send_task_id;
	QString	logicalname;
	short	type_id;
	short 	status;
	float	fvalue;
	int step;
public:
	void operator =(const _RECORD_INFO &RecordInfo)
	{
		datetime = RecordInfo.datetime;
		type = RecordInfo.type;
		station_id = RecordInfo.station_id;
		dev_id = RecordInfo.dev_id;
		task_id = RecordInfo.task_id;
		send_task_id = RecordInfo.send_task_id;
		logicalname = RecordInfo.logicalname;
		type_id = RecordInfo.type_id;
		status = RecordInfo.status;
		fvalue = RecordInfo.fvalue;
		step = RecordInfo.step;
	}
	bool operator ==(const _RECORD_INFO &RecordInfo)
	{
		return (datetime == RecordInfo.datetime &&
				type == RecordInfo.type &&
				station_id == RecordInfo.station_id &&
				dev_id == RecordInfo.dev_id &&
				task_id == RecordInfo.task_id &&
				send_task_id == RecordInfo.send_task_id &&
				logicalname == RecordInfo.logicalname &&
				type_id == RecordInfo.type_id &&
				status == RecordInfo.status &&
				fvalue == RecordInfo.fvalue&&step==RecordInfo.step);
	}
}RECORD_INFO;
Q_DECLARE_METATYPE(SUBJECT_INFO);
Q_DECLARE_METATYPE(RECORD_INFO);
class CTaskCalculation : public QObject
{
	Q_OBJECT
public:
	CTaskCalculation(int task_id = 0,int send_task_id = 0,QSqlDatabase db = db_conn);
	~CTaskCalculation();
	float getTaskScore(){return score;};
	int getStepNum(){return mapSubjectInfo.count();};
	int getStepStatus(int step){return mapSubjectInfo[step].status;};
	DATA_SUBJECT *getStepSubjectInfo(int step){return &mapSubjectInfo[step].data_subject;};
	void setTaskId(int task_id){m_task_id = task_id;};
	void setSendTaskId(int send_task_id){m_send_task_id = send_task_id;};
	void setSqlDatabase(QSqlDatabase db){m_db = db;};
	int getTaskId(){return m_task_id;};
	int getSendTaskId(){return m_send_task_id;};
	//DZY ����MODE���� ����JUDGE���ڲ�����ʾ��MODE = 1�������������ּ��� ��MODE =0��
	bool judgeStepFinished(int step,int mode = 0);
	void judgeStepTimeout(int step);
	QTimer *timer_overtime;
	bool judgeStepPreConditionFinished(int step);//dzy
	int updateTaskRecordToHash();
	int updateTaskSubjectToMap(); 
	int calcTaskScore();
	bool stop_flag;//DZY
	int step_timeout;//DZY
	bool curstep_timeout;
	//dzy record from rtb
	int di_rt_data;
	float ai_rt_data;
	bool flag_keystep_unfinished;
private:
	int m_task_id;
	int m_send_task_id;
	QSqlDatabase m_db;
	float score;
	int curStep;
	RECORD_INFO curKeystep;//dzy ��¼��ǰ����ɵĹؼ�����;
	QMultiHash<int,RECORD_INFO> usedRecordInfo;//
	QMultiHash<QString,RECORD_INFO> hashRecordInfo,usedRecordforPreSubjectInfo;//ѧԺ���в�����¼//dzy ����ǰ��������;
	QMap<int,SUBJECT_INFO> mapSubjectInfo;
	bool isRecordUsed(RECORD_INFO *);
	bool isPointInUsedinfo(QString pointname);
	int math(int n1,int n2,QChar op);
	int precedence(QChar op);
	int judgeCondExp(const QString &cond_exp,int mode = 0);//mode = 0Ĭ���������������ж� mode = 1 ǰ�������ж�
	int getValueByRpn(const QString &rpn,int *value);
	int chgExpToRpn(const QString &exp,QString &rpn);
	void splitSubject(const QString &str_subject,QStringList &list_subject);
	int getAlarmPointResultFromRecord(const QString &pointName,short *type_id,short *status,float *fValue,int mode = 0);//mode = 0Ĭ������ mode = 1 ����������¼
	int getCmdPointResultFromRecord(const QString &pointName,short *type_id,short *status,float *fValue,int mode = 0);//mode = 0Ĭ������ mode = 1 ����������¼
	int getLocalOprFromRecord(const QString &opr_id,int *isExist,int mode = 0);//mode = 0Ĭ������ mode = 1 ����������¼
	int getPtCheckFromRecord(const QString &pointName,short *status,int mode = 0);//mode = 0Ĭ������ mode = 1 ����������¼
	void writeScoreToHdb(int step,float score);
	//dzy added 
	int  getAlamPointfromDMS(const QString &pointName,short *type_id,short *status,float *fValue);
private slots:
	void steptimeout();

};

#endif