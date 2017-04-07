/*#define AGC_ON_SERVER*/ /*��JMOPA������*/

//#define	WindowsOS
#define	SUNOS
#define	DEBUG
#define	HOST_NAME	"HOSTNAME"

//#define HuaZhongWangDiao	//��������
#define PBG	//�ٲ���

#define SCHEDULE    96
#define NAME_SIZE   40
#define MAXSEGMENT	3
#define MAX_UNIT_NUMB	20
#define HEAD_NUMBER    50
#define	DATA_ERR	-1
#define	CHANN_FAIL	2
#define VIBRATION_NUMB	2
#define INFI	3000000
/*���»���״̬������������ٲ���*/
#ifdef PBG
#define UNIT_IN_CHKOUT_AGC 0	//����̬
#define	UNIT_IN_STANDBY_AGC	2	//����̬
#define	UNIT_IN_COMP_AGC	3
#define	UNIT_IN_UNSYN_AGC	4
#define UNIT_IN_GEN_AGC	5	//����̬
#else
#define UNIT_IN_CHKOUT 2	//����̬
#define	UNIT_IN_STANDBY_AGC	0	//����̬
#define	UNIT_IN_COMP_AGC	3
#define	UNIT_IN_UNSYN_AGC	4
#define UNIT_IN_GEN_AGC 1	//����̬
#endif

#define HANGUP	1
#define QUIT	2

#define INCREASE	1
#define DECREASE	2

#define KJML		0xc10	
#define TJML		0xc20	
#define TZFML		0xc40	
#define KZZFDML	        0xc50  
#define FDZKZML		0xc90   
#define YGTJML		0xc00	
#define WGTJML		0xc00	

#define TGLTHM	 0 	/* ������ */
#define KJLTHM	 1	/* ������ */
#define TJLTHM	 2	/* ͣ���� */
#define WCZTHM	 3	/* no operation */

#define NOT 0
#define YES 1
#define FHQX_INTERVAL 15

#define AGC_MODE_AP_Setpoint	1
#define AGC_MODE_AP_Curve		2
#define	AGC_MODE_NONE			3

struct tm  *ntime;
DMS_COMMON common_aa;
int UNIT_NUMB=0;
int move_curve=0;
int src_id=0;
int oldday=0;
char   logfilename[50]="";
int AGC_Period=0;
int refre_time=0;
int water_refresh_Period=0;
float MinWaterhead,MaxWaterhead;
float WaterheadPower[MAX_UNIT_NUMB+1][6][HEAD_NUMBER+1];
int	Type_UnitNo[MAX_UNIT_NUMB+1][MAX_UNIT_NUMB+1]={0};
int ItemNumber,TypeNumber;
float factor[MAX_UNIT_NUMB+1];
int AP_Step[MAX_UNIT_NUMB+1];
int AP_Adj_Step[MAX_UNIT_NUMB+1];
int minor_adjust[MAX_UNIT_NUMB+1];	//С���ɵ����Ļ�������˳��������
int minor_adjust_p_tmp[MAX_UNIT_NUMB+1];	//С���ɵ����Ļ�����ʱ������
int	ManSetLmt;
int AGC_P_Set_Dev;
int CurveSetFuc;
int	AGC_Loop;

typedef struct
{
	int	   WHeadChanged;
	float    UpWaterLevel;
	float    DownWaterLevel;
	float	 WaterHead;
	float	 XWaterHead;
}Water_Msg;

typedef struct
{
    int		AP_MODE;            /*�й����ط�ʽ  Ͷ��/�˳�*/
    int		Control_Right;         /* ����Ȩ  ����/�ݵ�/���� 0Ϊ���ء�1Ϊ�ݵ���2Ϊ����*/
    int		Closed_Loop;    /*����/�ջ�*/
    int		Mode;           /*AGC���ڷ�ʽ(�й�����/��������/��Ƶ/Ƶ�ʲ���/�޹���)*/
    int		AP_Setting;      /*�й�����*/
    int		AP_Curve;        /*��������*/
    int		FR_Regulation;             /*��Ƶ*/
	int		Auto_StartStop;     /*�Զ���ͣ����ʽ*/
    int		FR_Compensation;  /*Ƶ�ʲ���ģʽ*/
    int		Sel_Bus;        /*ѡ��ĸ��  ĸ��I/ĸ��II*/
    int		SR_AVAIL_Setting;	/*�й�������ת����Ͷ��*/
    int		SR_AVAIL_Curve;	   /*����������ת����Ͷ��*/
    int		AP_Faulty;			/*�й���������*/
    int		XAGC_Unit_Comp;		/*���鴦���й�������ʽ��*/
    float	    State_SetValue;		/*�����й��趨ֵ*/
    float	    Cascade_SetValue;	/*�ݵ��й��趨ֵ*/
    float	    Operator_SetValue;	/*����Ա�趨�й�ֵ*/
    float	    p_sum_no_agc;           /* ���ػ����й�֮�� */
    float	    p_sum_agc;                      /* ���ػ������й�      */
    float	    p_sum;                          /* ȫ�����й�       */
	float	ace;	/*����ֵ��ʵ��ֵ�����*/
	float	last_ace;	/*�ϴμ���ĸ���ֵ��ʵ��ֵ�����*/
    float	    AP_Setpoint;     /*ȫ���й�����ֵ*/
    float	    XAP_Setpoint;
    float	    YAP_Setpoint;
	float		MinorAdjP;  /*С�����仯����������ֵ*/
	int		P_adj;	/*��ǰ����ֵ����һ�θ����Ĳ�ֵ*/
    int		Num_AP_Avail;       
    int		Last_Num_AP_Avail;
    int		AGC_Generating;         /* glfs, number of units in agc generation      */
    int		Last_AGC_Generating; 
    int		AGC_Standby;            /* glbs, numb of units in agc standby   */
    int		Generating_No_AGC;      /* unglfs, nmb of units in no agc generation    */
    int		Num_Unit_Run;			/*�������л�����*/
    int	    UplmtCurrentZone;   /*����Խ��������*/
    int	    LowlmtCurrentZone;   /*����Խ��������*/
    int	    AP_Deadband;        /*�й���������*/
    int	    WaterFlow;		/*��������*/
    int		AP_CTRL_Alarm;  /*�й����Ʊ���*/
    int		FR_Set_change; /*Ƶ���趨ֵ�仯*/
    int		FR_Set_Error;   /*Ƶ���趨ֵ����*/
    int		FR_Faulty;     /*Ƶ�ʲ���ֵ����*/
    int		Start_Req;		/*��������*/
    int		Stop_Req;		/*��������*/
    int		XUnitStrStp;	/*���鿪ͣ��*/
    int		Unit_Start;     /*��һ̨��������*/
    int		Unit_Stop;      /*��һ̨ͣ�˻���*/
    int		SSAnswerYes;		/*��ͣ��ȷ��*/
    int		SSAnswerNo;			/*��ͣ���ܾ�*/
    int		APAnswerYes;		/*�й�����ȷ��*/
    int     APAnswerYesTime;
    int     SSAnswerYesTime;
    int     SSAnswerNoTime;
    int		FR_CTRL_Alarm;		/*Ƶ�ʿ�����Ч*/
    int		XStrStp_Recalc;		/*��ͣ���ؼ���*/
    int		SSReject_Num;		/*��ͣ���ܾ�����*/
    int		XAP_Comp_Mode;
    int		XAP_Comp_Time;
    int     AP_Fail_Time;
    int     FR_Fail_Time;
    int		SR_SetPoint;    /*��ת�����趨ֵ*/
    int     Last_SR_SetPoint;
    int     SR_MaxValue;
    int     SR_MaxChange;
    float		AP_ChangeMax;	/*�й��趨ֵ�����*/
    int		FR_ChangeMax;	/*Ƶ���趨ֵ�����*/
    float		FR_Setpoint;	/*Ƶ���趨ֵ*/
    float		XFR_Setpoint;
    float		YFR_Setpoint;
    float		FR_Deadband;	/*Ƶ������*/
    float		FR_CompDeadband;	/* Ƶ�ʲ�������*/
    float		FR_PowGenDB;     /*��Ƶ�������ڷ�����ֵ*/
    float		FR_ActValue;	/*Ƶ��ʵ��ֵ*/  
    float     FR_CompPowBand;   /*max change*/
    float		XAP_FreqCTRL;	/*Ƶ�ʿ����й�����ֵ*/
    float		AP_WorkSP;		/*ȫ���й������趨��¼ֵ*/
    int		FR_WorkSP;      /*Ƶ�ʹ����趨ֵ*/
    int		Efficiency;		/*Ч��*/
    int		AGC_P_Set;      /* ����������й����ʵ�ǰ����ֵ */
	int		Last_AGC_P_Set; /* ����������й������ϴθ���ֵ */
    int		AP_Dev;     /*�й�����ֵ�����ӻ��Ǽ���*/
    int     AP_Deviation;
    int		Dev_Frequency;  /*Ƶ��ƫ��*/
    int		AP_Min;		/*ȫ����С���й�*/
    int		AP_Max;     /*ȫ��������й�*/
    int     FR_Min;
    int     FR_Max;
    float		SS_Deadband;	/*��ͣ������*/
    int		VZ_Deadband;	/*��Խ��������ֵ*/
    float     EC_Deadband;
    int		XFreq_Output;	/*Ƶ�ʿ���ģʽ�������*/
    int		XFreqDoopAdaptFact; /*Ƶ������Ӧϵ��*/
    int		XFreqMaxDev;	/*Ƶ�����ƫ��*/
    int		XFreqDevDir;	/*Ƶ��ƫ���*/
    int		XStrStp_Delay;  /*��ͣ����ʱ*/
    int		XAP_Comp_Step;	/*�й���������*/
    int		XAP_DistributeDelay;	/*������ʱ*/
    int		ACE_over_adj;			/*���鸺�ɲ������й�ACE�����仯��Ҫ΢��*/
    int     AP_Alm_Time;
    int     Offset_Enable;
    int     Curve[SCHEDULE];     /**/
    int     SR_Curve[SCHEDULE];
    int     Offset;
    int     ZeroCurveValue;
    int     CurvePointNum;  
    int     FirstRun;
    int		Remote_SingleUnit_Control;
	int		Manual_Set;
} T_PLANT;   

typedef struct
{
    int		Status;            /*����״̬ */
    int     Maint_Status;
    int		Last_Status;		/*�ϴλ���״̬*/
    int     AP_Sel;
    int     AP_Permit;
    int		AP_Avail;           /*�����Ƿ����ؿɵ�*/
    int		Last_AP_Avail;		/*�ϴλ����Ƿ����ؿɵ�*/
    float	AP_RtValue;			/*ʵ���й�*/
	float	Last_APValue;		/*�ϴ�ʵ���й�*/
    int     InputPower;
    int		AP_Faulty;			/*�й�������������*/
    int		Standby_Time;         /*��������ʱ�䣬��λ����*/
    int		Generating_Time;         /*��������ʱ�䣬��λ����*/
    int		Start;			/*����*/
    int		Stop;			/*ͣ��*/
    int		XStop;			/*ж�ظ�����δ��ͣ����*/
    int		Start_Req;      /*��������*/
    int		Stop_Req;       /*ͣ������*/
    int		XAnswerNo;		/*�ܾ�*/
	int		VibrationNum;
    float		Low_Vibration[VIBRATION_NUMB+1];
	float		Up_Vibration[VIBRATION_NUMB+1];
    float		AP_Min;          /*������������*/
    float		AP_Max;          /*������������*/
    float       Last_AP_Min;
    float       Last_AP_Max;
    float       AP_Chang_Max;
    int		CurrentUplmt;                 /*��ǰ����Խ��������*/
    int		CurrentLowlmt;                /*��ǰ����Խ��������*/
    int     Privilege;     /*��ͣ�����ȼ�*/
    int		Type;			/*��������*/
    int		XAP_Setp;		/*���������й�ֵ*/
    int		AP_Setp;		/*���������й�ֵ*/
    int		StartCmdTime;		/*��������ʱ��*/
    int		StopCmdTime;		/*ͣ��ж��ʱ��*/
    int		StopTime;			/*����ͣ������ʱ�䣨����ͣ��ʧ�ܱ�����*/
    int		StopAction;			/*���Ϊͣ������*/
    int		StartAction;		/*��ע����Ϊ��������*/
    int		StartProcess;
    int		Starting;			/*���ڿ������飬��PLC��״̬*/
    int		Stopping;			/*����ͣ�����飬��PLC��״̬*/
    int		ReduceLoad;
    int		StartFlag;
    int		StopFlag;
    int		StartTime;         /*���鿪������ʱ�䣨��������ʧ�ܱ�����*/
    int		XAPCompMode;		/*�й���������*/
    int		XPowerUp;
    int		Zone;				/*��������������*/
    int		Vib_Zone;			/*0/1��ʾ����/������*/
    int		XVibDelay;			/*ͳ�ƻ���������ʱ��*/
    int		XAP_Setp_Calc;		/*�������µ��趨ֵ*/
    int		XStartUpTime;		/*���鲢�����ʱ*/
    int		AP_Fail;			/*�й�����ʧ��*/
    int		XStartBlockTime;	/*��������ʱ��*/
    int		CommandTime;		/*������ͣ�������ʱ��10��*/
    int		APCompTime;			/*�й�����ʱ��*/
    int     AP_FailTime;
    int     RduceLoadFailTime;
    int		Flow;				/*����*/
    int		Efficiency;
    int		RemoteControlable;	/*�����Ƿ�Զ���ɿ�*/
} T_UNIT;     /*���鹤��*/

typedef struct
{		
	int     range_p_dn;
	int		range_p_up;
}	P_RANGE;

typedef struct
{
	int     unit_id;
	int		range_id;
	P_RANGE p_range;
}       P_SPACE_1U;        /*1̨�����й�����Ľ�ռ�*/

typedef struct
{
	int  spa1_id;
	int	 spa2_id;
	P_RANGE p_range;
}       P_SPACE_2U;        /*2̨�����й�����Ľ�ռ�*/

typedef struct
{	
	int	 spaU2_id;
	int  spaU1_id;
	P_RANGE p_range;
}       P_SPACE_3U;        /*3̨�����й�����Ľ�ռ�*/

typedef struct
{
	int  spaU3_id;
	int	 spaU1_id;
	P_RANGE p_range;
}       P_SPACE_4U;        /*4̨�����й�����Ľ�ռ�*/

typedef struct
{
	int  unit_id;
	int  unit_P;
}       P_SPA_Unit_RESULT;        /*�ý�ռ�ķ����ó��Ļ����й�����Ľ�*/

typedef struct
{
	P_SPA_Unit_RESULT Unit_Result[5]; //���������̨����Ľ�
	int	 dx;		//�����ķ���
}       P_SPACE_RESULT;        /*�ý�ռ�ķ����ó��Ļ����й�����Ľ⣬Ŀǰ�����̨����*/

typedef struct
{
        POINTER ptr;
        ANLG_DATA value;
        char   sec;
	    char   min;
}       COMMON_DEF;     /* ͨѶ���ݰ� */


Water_Msg Watermsg;
T_PLANT PLANT;
T_UNIT  UNIT[MAX_UNIT_NUMB+1];
P_SPACE_1U result_space1[20];
P_SPACE_2U result_space2[100];
P_SPACE_3U result_space3[100];
P_SPACE_4U result_space4[300];
P_SPACE_RESULT p_space_result,tmp_space_result;
int spnum_1U;
int spnum_2U;
int spnum_3U;
int spnum_4U;

char DB_NAME_Today_Curve[SCHEDULE+1][NAME_SIZE];
char DB_NAME_Tomorrow_Curve[SCHEDULE+1][NAME_SIZE];
char DB_NAME_AP_RtValue[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Optimization_Value[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Control_Command[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RT_P_Curve[NAME_SIZE];
char DB_NAME_AGC_Period[NAME_SIZE];
char DB_NAME_Control_Right[NAME_SIZE];
char DB_NAME_AGC_CLOSED_LOOP[NAME_SIZE];
char DB_NAME_QC_AGC[NAME_SIZE];
char DB_NAME_AP_Setting[NAME_SIZE];
char DB_NAME_AP_Curve[NAME_SIZE];
char DB_NAME_AP_ChangeMax[NAME_SIZE];
char DB_NAME_Rt_Status[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_Group[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_CZKT[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_RtValue[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_SetValue[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_BREAKER_Status[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AGC_STATE[NAME_SIZE];
char DB_NAME_Prvilege[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_Setpoint[NAME_SIZE];
char DB_NAME_Upstream_Level[NAME_SIZE];
char DB_NAME_Downstream_Level[NAME_SIZE];
char DB_NAME_Water_Head[NAME_SIZE];
char DB_NAME_Manual_Set[NAME_SIZE];
char DB_NAME_Remote_Setpoint[NAME_SIZE];
char DB_NAME_Low_Vibration[MAX_UNIT_NUMB+1][VIBRATION_NUMB+1][NAME_SIZE];
char DB_NAME_Up_Vibration[MAX_UNIT_NUMB+1][VIBRATION_NUMB+1][NAME_SIZE];
char DB_NAME_AP_Min[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_Max[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_StartStopDeadband[NAME_SIZE];
char DB_NAME_DB_AP_WorkSP[NAME_SIZE];
char DB_NAME_P_UPLMT[NAME_SIZE];
char DB_NAME_P_DOWNLMT[NAME_SIZE];
char DB_NAME_RemoteAGCOnLine[NAME_SIZE];
char DB_NAME_SD_YK[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_SD_PSet[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AGCYG_STEP[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Remote_OverPLmtALM[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Remote_OverBCLmtALM[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_QCUNRUN_UPLMT1[NAME_SIZE];    /*ȫ����һ�й����������ޣ�added by �ٲ��� for FT 2010-918*/
char DB_NAME_QCUNRUN_DNLMT1[NAME_SIZE];
char DB_NAME_QCUNRUN_UPLMT2[NAME_SIZE];    /*ȫ���ڶ��й����������ޣ�added by �ٲ��� for FT 2010-918*/
char DB_NAME_QCUNRUN_DNLMT2[NAME_SIZE];
char DB_NAME_ALM_Plant_UN_RUN[NAME_SIZE];	/*ȫ���й�������ȫ���������ڱ���*/
char DB_NAME_ALM_ChangeMax[NAME_SIZE];	/*ȫ���й�������������������������*/
char DB_NAME_ALM_StatusErr[NAME_SIZE];	/*ȫ���й�������������������������*/
char DB_NAME_ALM_YFKErr[NAME_SIZE];	/*ȫ��AGC��Զ�����������㱨��*/
char DB_NAME_AGC_FRUPLMT[NAME_SIZE]; /*���й�����Ƶ������ֵ*/
char DB_NAME_AGC_FRDOWNLMT[NAME_SIZE]; /*���й�����Ƶ������ֵ*/
char DB_NAME_AGC_FRLOW_ERR[NAME_SIZE]; /*AGCƵ�ʵͼ����ɱ���*/
char DB_NAME_AGC_FRHIGH_ERR[NAME_SIZE]; /*AGCƵ�ʸ������ɱ���*/
char DB_NAME_AGC_RTFR[NAME_SIZE]; /*��ǰĸ��Ƶ��ֵ*/
char DB_NAME_AGC_FRLOW_ERR[NAME_SIZE];	/*AGCƵ�ʵͼ����ɱ���*/
char DB_NAME_AGC_FRHIGH_ERR[NAME_SIZE];	/*AGCƵ�ʸ������ɱ���*/
char DB_NAME_DD104_DOWN[NAME_SIZE];	/*������104ͨѶ�ж�*/
char DB_NAME_WATERINFO_ERR[NAME_SIZE]; /*AGCˮ�����ݴ��󱨾�*/
char DB_NAME_AGC_PLOW_ERR[NAME_SIZE];	/*������104ͨѶ�ж�*/
char DB_NAME_AGC_POVER_ERR[NAME_SIZE]; /*AGCˮ�����ݴ��󱨾�*/
char DB_NAME_AGC_LMT_DB_ALM[NAME_SIZE]; /*AGC���Խ���������������ֵ����ʱ������*/
char DB_NAME_AGC_COMP_DERECT[NAME_SIZE];	/*AGC���Խ���������������ֵ����ʱ�����������ɵķ���1Ϊ����2Ϊ��*/
char DB_NAME_AGC_LMT_DB_ADVICE[NAME_SIZE]; /*AGC���Խ���������������ֵ����ʱ�����ֶ������ĸ���ֵ*/
char DB_NAME_ALM_P_GETERR[NAME_SIZE]; /*AGCȫ���й��ɼ�ֵͻ�䱨��*/
char DB_NAME_WATER_REFR_TIME[NAME_SIZE]; /*�˹�����ˮλˢ��ʱ��*/
char DB_NAME_MINOR_ADJ_P[NAME_SIZE]; /*С�����仯����������ֵ*/

//float min_jz_uplmt,sum_jz_downlmt;	/*�������������С�����޺ͷ�������������ֵ֮��(�ɵ�ȫ�������㷨)*/

/*for Schedule.o*/
/*
#define BUF_NUM	100
typedef struct{
  int		  RowNum;
  int         Position;    //Position of row
  int         Hour;        //Hour of time
  int         Minute;      //Minute of time
  double       APower;      //Active power
  double       Voltage;     //Voltage
  double       Spinn;       //Spinning reserve
  double        Error;       //Error in line detected
}T_Schedule;

int LIMITS_MAX_ACTIVE_POWER;
int LIMITS_MIN_ACTIVE_POWER;
int LIMITS_MAX_SPINN_RESERVE;
int LIMITS_MIN_SPINN_RESERVE;
int LIMITS_MAX_VOLTAGE;
int LIMITS_MIN_VOLTAGE;
char DB_NAME_TD_JRFHQX_SD[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_JRFHQX_XZ[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_MRFHQX_SD[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_MRFHQX_XZ[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_JRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_MRDYQX[MAXSEGMENT][NAME_SIZE];
*/
