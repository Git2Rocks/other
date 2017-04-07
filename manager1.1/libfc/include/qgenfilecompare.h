#ifndef QGENFILECOMPARE_H
#define QGENFILECOMPARE_H

#include <QObject>
#include <QVector>
#include <QTextStream>

#include "qfcextern.h"

class FC_EXPORT QGenFileCompare : public QObject, public QAbstractFileCompare
{
	Q_OBJECT

public:
	QGenFileCompare(QObject *parent=0);
	~QGenFileCompare();

	enum {Type=COMPARE_GEN_FILE};

	typedef struct
	{
		QString	cabinet_no;
		QString	unit_no;       	
		QString	slot_no;		
		QString	channel_no;	        
		QString	terminal_no;	
	} HARD_ADDR;

	typedef struct
	{
		QString	procType;
		QString	almCba;
		QString	statistic;
		QString	fault;
		QString	fail;
		QString	ctrl;
		QString	soe;
		QString	trendAlm;
		QString	keySignal;
		QString	faultRec;
		QString	audAlm;
		QString	normalClose;
		QString	doublePt;
		QString	sysVirtual;
		QString	lcuVirtual;
		QString	cascade;
		QString	hdbRec;
		QString	hdbCurve;
		QString	onAlm;
		QString	offAlm;
		QString	normalState;
		QString	res;
		QString	hdbPeriod;
	} IOATTR;

	typedef struct
	{
		QString	cmd;
		QString	alm;
	} MSG_SELECTOR;

	typedef	struct		/* Entry descriptor - fixed portion */
	{
		QString		entryName;	/* Entry's name	*/
		QString		entryLongname;	/* Entry's longname	*/
		QString		entryExLongname;
		QString		dsp_filename;
		HARD_ADDR	hard_addr;
		QString		io_group;
		IOATTR		ioattr;
		QString		pairName;
		QString		pairType;
		QString		ctrl_addr;
		MSG_SELECTOR msg_sel;
		QString		id;
	} ENTRY_FIXED;

	typedef struct
	{
		QString	D_BAND;
		QString HDB_BAND;
		QString	ENG_CVT;
		QString	HI_RANGE;		
		QString	LO_RANGE;		
		QString	ZERO;			
		QString	COMPSATE;
		QString	HI_CODE;
		QString	LO_CODE;
		QString HDB_CONDITION;
		QString CONSTRAINT;
		QString CONSTRAINTGROUP_ID;
	} ANA_ENG_PARA;

	typedef struct
	{
		QString	HI_ALARM; 
		QString	HI_WARN;
		QString	HI_RECOVER;
		QString	LO_ALARM;
		QString	LO_WARN;
		QString	LO_RECOVER;
		QString	TR_WARN;
		QString	TR_RECOVER;
	} LMT_PARA;

	typedef struct
	{
		QString        unitName;
		ANA_ENG_PARA    eng_para;
		LMT_PARA    lmt_para;
	} ENTRY_ANLG_VAL;

	typedef struct
	{
		QString	PT;		
		QString	CT;		
		QString	ENG_CVT;
		QString	CONSTANT;
		QString	DAY_RATE;
		QString	YEAR_RATE;
	} IMP_ENG_PARA;

	typedef struct
	{
		IMP_ENG_PARA	eng_para;		
	} ENTRY_IMP_VAL;

	typedef struct
	{
		QString		start_pt_name;
		QString		pt_num;
	} ENTRY_CHARA_VAL;

	typedef struct
	{
		QString		seg_num;
		ANA_ENG_PARA    eng_para;
	} ENTRY_CURVE_VAL;

	typedef struct
	{
		ENTRY_ANLG_VAL	anlg;
		struct
		{
			ENTRY_IMP_VAL	entry;		
		} imp;
		ENTRY_CHARA_VAL	chara;
		ENTRY_ANLG_VAL	calc;
		ENTRY_CURVE_VAL	curve;
	} RD_VAR_UNION;

	typedef struct 
	{
		ENTRY_FIXED fixed;
		RD_VAR_UNION var;
	}RECORD_ENTRY;

	typedef struct
	{
		QString recName;

		QVector<RECORD_ENTRY> entries;
	}RECORD_DEF_ENTRY;

public:
	virtual int type() const	{return Type;}
	virtual bool match(const QString& filename) const;

protected:
	virtual void parseFile(QFile& file, FileCompareResult& result);
	virtual void compareFile(FileCompareResult& source, FileCompareResult& target);
	virtual int writeData(QIODevice* device, FileCompareResult& result);
	virtual bool checkModified(FileCompareResult& source, FileCompareResult& target);
	virtual int checkValidity(FileCompareResult& result, QPair<QModelIndex, QModelIndex>& error);

private:
	void diff(int recordType, QAbstractItemModel* source, QAbstractItemModel* target, int& curIntexTarget,int endIndexTarget,
		const QVector<QGenFileCompare::RECORD_ENTRY>& data, bool append=true);

	void fill(int num, QAbstractItemModel* model);

	int setData(int recordType, QAbstractItemModel* model, const QGenFileCompare::RECORD_ENTRY& data, int rowRole);
	void setItemData(QAbstractItemModel* model, int row, int column, const QVariant& var, int itemRole);

	bool compareDiff(QAbstractItemModel* source, int srow, QAbstractItemModel* target, int trow, int recordType, const QVector<int>& ignored);

	QVector<int> ignoredColumns(const QString& filename) const;

private:
	enum CommonTitleType
	{
		LogicalNameTitle,		//�߼���
		LongNameTitle,			//������
		CommonTitleEnd
	};

	enum AnaTitleType
	{
		HHLimitTitle=CommonTitleEnd,			//������ֵ
		HLimitTitle,			//����ֵ
		HRLimitTitle,			//���޸�����
		LRLimitTitle,			//���޸�����
		LLimitTitle,			//����ֵ
		LLLimitTitle,			//������ֵ
		DBandTitle,				//����ֵ
		HDBBandTitle,			//��ʷ��������ֵ
		ENGConvertTitle,		//ת��ϵ��
		HighRangeTitle,			//������
		LowRangeTitle,			//������
		HighCodeTitle,			//ԭ��������
		LowCodeTitle,			//ԭ��������
		TrendLimitTitle,		//����Խ��ֵ
		RTLimitTitle,			//���Ƹ�������
		DSPFileTitle,			//���ݿ��ļ�
		FaultPointTitle,		//�¹ʵ�
		FailPointTitle,			//���ϵ�
		AudioAlarmTitle,		//����������
		TrendAlarmTitle,		//���Ʊ�����
		CascadePointTitle,		//���ݵ���
		ControlPointTitle,		//���Ƶ�
		ControlAddrTitle,		//���Ƶ�ַ
		ZeroTitle,				//���ֵ
		CompensateTitle,		//����ֵ
		AlarmCBATitle,			//����������
		VirtualPointTitle,		//ϵͳ�����
		LCUVirtualTitle,		//LCU�����
		CMDMsgTitle,			//�����ַ�����
		UnitTitle,				//��λ
		PairTypeTitle,			//�������
		PairPointTitle,			//��Ե��߼���
		HDBRecordTitle,			//д��ʷ��
		HDBPeriodTitle,			//��ʱ���ݲ�������
		HDBCurveTitle,			//�����뼶����
		IOGroupTitle,			//�����
		TerminalNoTitle,		//���Ӻ�
		CabinetNoTitle,			//�����
		UnitNoTitle,			//�����
		SlotNoTitle,			//��ۺ�
		ChannelNoTitle,			//ͨ����
		HDBConditionTitle,		//����д��
		ConstraintTitle,		//Լ������
		ConstraintGroupIDTitle,	//Լ��������ID
		IDTitle,					//ID��
		AnaTitleEnd
	};

	enum ImpTitleType
	{
		IMP_ProcTypeTitle=CommonTitleEnd,	//�ӵ�����
		IMP_ConvertTitle,			//ת��ϵ��
		IMP_PTTitle,				//PT
		IMP_CTTitle,				//CT
		IMP_DayRateTitle,			//�ձ���
		IMP_YearRateTitle,			//�걶��
		IMP_ConstantTitle,			//��ת����
		IMP_DspFileTitle,			//�����ļ�
		IMP_CascadePointTitle,		//���ݵ���
		IMP_HDBRecordTitle,			//д��ʷ��
		IMP_HDBPeriodTitle,			//��ʱ���ݲ�������
		IMP_IOGroupTitle,			//�����
		IMP_TerminalNoTitle,		//���Ӻ�
		IMP_CabinetNoTitle,			//�����
		IMP_UnitNoTitle,			//�����
		IMP_SlotNoTitle,			//��ۺ�
		IMP_ChannelNoTitle,			//ͨ����
		IMP_IDTitle,				//ID��
		IMPTitleEnd
	};

	enum IntTitleType
	{
		INT_ProcTypeTitle=CommonTitleEnd,	//�ӵ�����
		INT_MSGDefTitle,			//�¼��ַ�����
		INT_CMDMsgTitle,			//�����ַ�����
		INT_AudioAlarmTitle,		//����������
		INT_StatisticsTitle,		//ͳ�Ƶ�
		INT_FailRecordTitle,		//�¹�׷���
		INT_FaultPointTitle,		//�¹ʵ�
		INT_FailPointTitle,			//���ϵ�
		INT_KeySignalTitle,			//��Ҫ��
		INT_DspFileTitle,			//�����ļ�
		INT_ControlPointTitle,		//���Ƶ�
		INT_ControlAddrTitle,		//���Ƶ�ַ
		INT_SOE,					//�¼�˳���¼��
		INT_AlarmCBATitle,			//����������
		INT_NormalStateTitle,		//�ӵ㳣̬
		INT_ONAlarm,				//0->1�����¼�
		INT_OFFAlarm,				//1->0�����¼�
		INT_VirtualPointTitle,		//ϵͳ�����
		INT_LCUVirtualTitle,		//LCU�����
		INT_CascadePointTitle,		//���ݵ���
		INT_TriplePointTitle,		//��̬��
		INT_NormalCloseTitle,		//��̬��رսӵ�
		INT_PairTypeTitle,			//��̬���������
		INT_PairPointTitle,			//��̬����Ե��߼���
		INT_HDBRecordTitle,			//д��ʷ��
		INT_IOGroupTitle,			//�����
		INT_TerminalNoTitle,		//���Ӻ�
		INT_CabinetNoTitle,			//�����
		INT_UnitNoTitle,			//�����
		INT_SlotNoTitle,			//��ۺ�
		INT_ChannelNoTitle,			//ͨ����
		INT_IDTitle,				//ID��
		INTTitleEnd
	};

	enum CurveTitleType
	{
		CUR_NumPoints=CommonTitleEnd,	//���ݸ���
		CUR_ENGConvertTitle,		//ת��ϵ��
		CUR_HighRangeTitle,			//������
		CUR_LowRangeTitle,			//������
		CUR_HDBRecordTitle,			//д��ʷ��
		CUR_IDTitle,				//ID��
		CURTitleEnd
	};

	int recordTypeFromName(const QString& name) const;
	RECORD_DEF_ENTRY parseEntryFile(QTextStream& stream);
};

FC_EXPORT bool operator==(const QGenFileCompare::RECORD_ENTRY& source, const QGenFileCompare::RECORD_ENTRY& target);
FC_EXPORT bool operator==(const QGenFileCompare::HARD_ADDR& source, const QGenFileCompare::HARD_ADDR& target);

Q_DECLARE_METATYPE(QGenFileCompare::RECORD_DEF_ENTRY)

#endif // QGENFILECOMPARE_H
