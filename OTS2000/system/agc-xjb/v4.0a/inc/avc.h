
#define CASCADE

#define	UNIT_NUMB		8
#define DATA_ERROR		-1000
#define DATA_BAD		-1001
#define OVER_HIGH_LMT           -1002

#define	MAXPQPOINTS	21
#define MAXTYPES	2
#define MAXSEGMENT      2
#define NAME_SIZE        36

#define OPEN_LOOP   0
#define CLOSE_LOOP  1

//Detection of unit power control failure
typedef struct  
{
    float       HL_Value;
    float       LL_Value;
    float       LastValue;
    int         MoveTime;
    int        INC_Dir;
    int        Moving;
    int        Enabled;
}T_CTRL_Fail;

typedef struct
{
	int		Type;		/*������������*/
	int		RP_Sel;		/*ѡ���޹�����*/
	int		RP_Permit;    /*�޹���������*/
	int		RP_Avail;	    /*�����޹����ؿɵ�*/
	int		Last_RP_Avail;  /*�ϴλ����޹�����״̬*/
	int		RP_Faulty;  /*�����޹�����ֵ����*/
	int		AP_Faulty;  /*�����й�����ֵ����*/
	int		segment;        /*����������*/
	int		Status;		/*����״̬*/
	int		Last_Status;
	int		XStatus;
	int             Maint_Status;
	int		RPCompMode;		/*���鲹��ģʽ*/
	int             RPCompTime;
	float           RP_RtValue;	/*ʵ���޹�����*/
	float           AP_RtValue;	/*�й�ʵ��ֵ*/
	float           RP_Min;		/*������С�޹�����*/
	float           RP_Max;		/*��������޹�����*/
	float           Last_RP_Min;
	float           Last_RP_Max;
	float           RP_Setp;		/*�޹������趨ֵ*/
	float           XRP_Setp;	
	float           YRP_Setp;
	float           ZRP_Setp;
	int             RP_Setp_Calc;
	float           RP_MaxChange;
	int             RP_Fail;
	int             ReduceLoad;
	int             Last_ReduceLoad;
	int             RP_FailTime;
	T_CTRL_Fail     XRP_Err_Detect;
}T_UNIT;

typedef struct 
{
	int     RP_MODE;        /*AVC�����ܿ���*/
	int	Last_RP_MODE;
	int     FirstRun;
	int	Mode;		/*AVC���ڷ�ʽ(�޹�����1/��ѹ����2/��ѹ����3/��ѹ����4/�޹���5)*/
	int	Last_Mode;
	int	VO_Regulation;		/*��ѹ����ģʽ*/
	int     VO_Curve;               /*voltage curve mode*/
	int     RP_Setting;
	int     VO_Compensation;	/*��ѹ����ģʽ*/
	int	Sel_Bus;	/*ѡ��I��IIĸΪ��ĸ�ߣ�0ΪIĸ��1ΪIIĸ*/
	int     Close_Loop;	/*0Ϊ������1Ϊ�ջ�*/
	int	Last_Close_Loop;
	int	RP_Faulty;	/*�޹�����ֵ����*/
	int     AP_Faulty;  /*�й�����ֵ����*/
	int     VO_Faulty;	/*��ѹ����ֵ����*/
	int     Num_RP_Avail;        /*�޹����ؿɵ�����̨��*/
	int     Last_Num_Avail;
	int     GenNumb;
	int	VO_CTRL_Alarm;      /*��ѹ���Ʊ���*/
	int	XAVC_Unit_Comp;		/*���鴦�ڹ��ʲ���ģʽ*/
	int     XRP_Comp_Time;
	int	XVoltDevDir;		/*��ѹƫ���*/
	int	XRP_Recalc;			/*ѭ����������*/
	int     RPAnswerYes;
	int     RPAnswerYesTime;
	int     Lim_Change;
	int     CompLimPos;
	float   RP_WorkSP;
	float	RP_Setpoint;	/*��ǰ�޹��趨ֵ*/
	float	XRP_Setpoint;
	float	YRP_Setpoint;
	float	RP_Deadband;		/*�޹���������*/
	float	XRP_Min;				/*�޹���С����ֵ*/
	float   XRP_Max;				/*�޹������ֵ*/
	float	Volt_Power;       /*��ѹ�������ѹ���߷�ʽ���������������޹�ֵ*/
	float	VO_Deadband;	/*��ѹ����ֵ*/
	float   Comp_Deadband;    
	float	VO_Work;		/*��ѹ�����趨ֵ*/
	float   VO_Deviation;		/*��ѹƫ��*/
	float	VO_RtValue;		/*��ѹʵʱֵ*/
	float	VO_Min;				/*��ѹ��Сֵ*/
	float   VO_Max;				/*��ѹ���ֵ*/
	float	RP_Min;				/*�޹���Сֵ����������*/
	float   RP_Max;				/*�޹����ֵ����������*/
	float	VO_Setpoint;		/*��ѹ�趨ֵ*/
	float   XVO_Setpoint;
	float   YVO_Setpoint;
	float	VO_PowGenDB;		/*��ѹ�������޹����ڷ�����ֵ*/
	float	XRP_VoltCTRL;		/*�ϴ��޹�����ֵ*/
	float   XVoltMaxDev;
	float	XVoltDoopAdaptFact;	/*��ѹ��������Ӧϵ��*/
	float   XVolt_Output;
	float   Last_XVolt_Output;
	float   VO_MaxChange;
	float   RP_MaxChange;
	float   RP_Dev;
	float   RP_Deviation;
	float   P_Sum;
	float   P_Sum_AVC;
	float   RP_Sum;
	float   RP_Sum_AVC;
	float   RP_Sum_NotAVC;
	float   Last_RP_Sum_NotAVC;
	int     RP_Alarm_Time;
	int     RP_Fail_Time;
	int     VO_Fail_Time;
	int     RPCopyTime;
	int     JR_RPCopyTime;
	float   Curve[288];
	int     CurvePointNum;
	char    English_Name[20];
	char    Chinese_Name[20];
	int		Control_Right;         /* ����Ȩ  ����/�ݵ� 0Ϊ���ء�1Ϊ�ݵ�*/
	int		AllocationToUnit;
	int		Last_AllocationToUnit;
}T_PLANT;

//P/Q Curve for one voltage
typedef struct {
	float    AP[MAXPQPOINTS+1];  //�й��ٷֱ�
	float    RP_OE[MAXPQPOINTS+1];  //��������޹����ʵİٷֱ�
	float    RP_UE[MAXPQPOINTS+1];  //Ƿ��������޹����ʵİٷֱ�
}T_P_Q_Curve;

typedef struct {
	float    S_Total;    //���ڹ���
	T_P_Q_Curve Voltage;
} T_P_Q_Set;

char DB_NAME_QC_AVC[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_RTVALUE[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_WG_GD[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_RTVALUE[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_UNIT_STATUS[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_CLOSED_LOOP[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SEL_BUS[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_REGULATION[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_COMPENSATION[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_CURVE[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_SETTING[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_RTVALUE[4][NAME_SIZE];
char DB_NAME_RP_CZKT[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_DEADBAND[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_DEADBAND[MAXSEGMENT][NAME_SIZE];
char DB_NAME_COMP_DEADBAND[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_MIN[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_MAX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_XMIN[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_XMAX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_MIN[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_MAX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_PowGenDB[MAXSEGMENT][NAME_SIZE];
char DB_NAME_UNIT_AVCSEL[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_AVAIL[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_CZKT[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_VO_SETPOINT[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_SETPOINT[MAXSEGMENT][NAME_SIZE];
char DB_NAME_UNIT_SETPOINT[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_ANSWERYES[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_MAXCHANGE[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_MAXCHANGE[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_RCTSETPOINT[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_RCTSETPOINT[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_FAIL[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_FAIL[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RP_Sum[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Maint_Status[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_ReduceLoad[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Unit_RP_Fail[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_Dev_Alm[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Copy_JRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Copy_MRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_MLKG[NAME_SIZE];
char DB_NAME_ONLINE_STA[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_STOP_STA[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_OELimit[MAXSEGMENT][NAME_SIZE];
char DB_NAME_UELimit[MAXSEGMENT][NAME_SIZE];
char DB_NAME_JRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_MRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_JRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_MRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VO_REACT_VALUE[MAXSEGMENT][NAME_SIZE];
char DB_NAME_WG_GD_CAS[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_CTRL_PRI[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_GD_VO_SETPOINT[MAXSEGMENT][NAME_SIZE];

char DB_NAME_AllocationToUnit[MAXSEGMENT][NAME_SIZE];

#ifdef CASCADE
char DB_NAME_CasToPlantValue[MAXSEGMENT][NAME_SIZE];
#endif
