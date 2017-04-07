

//#define RECORD
//#define CASCADE

#define	HOST_NAME	"HOSTNAME"

#define UNIT_NUMB    8
#define NAME_SIZE    36
#define	MAXSEGMENT		3
#define DATA_ERROR		-1000
#define DATA_BAD		-1001
#define OVER_HIGH_LMT           -1002
#define MAXDEFPOINTS   25
#define	MAXAGCPOINTS   35  
#define	MAXTYPES 	2


#define VIBRATION_NUMB 5   /*�����������*/


#define OPEN_LOOP		0
#define	HALF_OPEN_LOOP	1
#define	CLOSED_LOOP	2


#define TGML        0
#define KJML		23
#define TJML		26	

#define STAND_BY    2
#define CHECKOUT    0

#define BUF_NUM	100

typedef struct
{
	int		WHeadChanged;
	float	 WaterHead;
	float	 XWaterHead;
}Water_Msg;

typedef	struct  
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
    int		AP_MODE;            /*�й����ط�ʽ  Ͷ��/�˳�*/
    int		Last_AP_MODE;
    int		Control_Right;         /* ����Ȩ  ����/�ݵ�/���� 0Ϊ���ء�1Ϊ�ݵ���2Ϊ����*/
    int		Closed_Loop;    /*����/�뿪��/�ջ�*/
    int		Last_Closed_Loop;
    int		Last_Mode;
    int		Mode;           /*AGC���ڷ�ʽ(�й�����1/��������2/��Ƶ3/Ƶ�ʲ���4/�޹���5)*/
    int		AP_Setting;      /*�й�����*/
    int		AP_Curve;        /*��������*/
    int		FR_Regulation;             /*��Ƶ*/
    int		FR_Compensation;  /*Ƶ�ʲ���ģʽ*/
    int		Sel_Bus;        /*ѡ��ĸ��  ĸ��I/ĸ��II*/
    int		SR_AVAIL_Setting;	/*�й�������ת����Ͷ��*/
    int		SR_AVAIL_Curve;	   /*����������ת����Ͷ��*/
    int		AP_Faulty;			/*�й���������*/
    int		XAGC_Unit_Comp;		/*���鴦���й�������ʽ��*/
    float	State_SetValue;		/*�����й��趨ֵ*/
    float	Cascade_SetValue;	/*�ݵ��й��趨ֵ*/
    float	Operator_SetValue;	/*����Ա�趨�й�ֵ*/
    float	p_sum_no_agc;           /* ���ػ����й�֮�� */
    float	p_sum_agc;                      /* ���ػ������й�      */
    float	Last_p_sum_no_agc;
    float	p_sum;                          /* ȫ�����й�       */
    float	AP_Setpoint;     /*ȫ���й�����ֵ*/
    float	XAP_Setpoint;
    float	YAP_Setpoint;
    int		Num_AP_Avail;       
    int		Last_Num_AP_Avail;
    int		AGC_Generating;         /* glfs, number of units in agc generation      */
    int		Last_AGC_Generating; 
    int		AGC_Standby;            /* glbs, numb of units in agc standby   */
    int		Generating_No_AGC;      /* unglfs, nmb of units in no agc generation    */
    int		Num_Unit_Run;			/*�������л�����*/
    float	UplmtCurrentZone;   /*����Խ��������*/
    float	LowlmtCurrentZone;   /*����Խ��������*/
    float	AP_Deadband;        /*�й���������*/
    float	WaterFlow;		/*��������*/
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
    int         APAnswerYesTime;
    int         SSAnswerYesTime;
    int         SSAnswerNoTime;
    int		FR_CTRL_Alarm;		/*Ƶ�ʿ�����Ч*/
    int		XStrStp_Recalc;		/*��ͣ���ؼ���*/
    int		SSReject_Num;		/*��ͣ���ܾ�����*/
    int		XAP_Comp_Mode;
    int		XAP_Comp_Time;
    int         AP_Fail_Time;
    int         FR_Fail_Time;
    float	SR_SetPoint;    /*��ת�����趨ֵ*/
    float       Last_SR_SetPoint;
    float       SR_MaxValue;
    float       SR_MaxChange;
    float	Real_SRValue;
    float	AP_ChangeMax;	/*�й��趨ֵ�����*/
    float	FR_ChangeMax;	/*Ƶ���趨ֵ�����*/
    float	FR_Setpoint;	/*Ƶ���趨ֵ*/
    float	XFR_Setpoint;
    float	YFR_Setpoint;
    float	FR_Deadband;	/*Ƶ������*/
    float	FR_CompDeadband;	/* Ƶ�ʲ�������*/
    float	FR_PowGenDB;     /*��Ƶ�������ڷ�����ֵ*/
    float	Freq_Power;     /*��Ƶ��������й�����ֵ*/
    float	FR_ActValue;	/*Ƶ��ʵ��ֵ*/  
    float       FR_CompPowBand;   /*max change*/
    float	XAP_FreqCTRL;	/*Ƶ�ʿ����й�����ֵ*/
    float	AP_WorkSP;		/*�й����ʹ����趨ֵ*/
    float	Last_AP_WorkSP;
    float	FR_WorkSP;      /*Ƶ�ʹ����趨ֵ*/
    float	Efficiency;		/*Ч��*/
    float	AGC_P_Set;      /* pagc */
    float	AP_Dev;     /*�й�����ֵ�����ӻ��Ǽ���*/
    float       Start_AP_Dev;
    float       AP_Deviation;
    float	Dev_Frequency;  /*Ƶ��ƫ��*/
    float	AP_Min;		/*ȫ����С���й�*/
    float	AP_Max;     /*ȫ��������й�*/
    float	XAP_Max;
    float       FR_Min;
    float       FR_Max;
    float	SS_Deadband;	/*��ͣ������*/
    float	VZ_Deadband;	/*��Խ��������ֵ*/
    float       EC_Deadband;
    float	XFreq_Output;	/*Ƶ�ʿ���ģʽ�������*/
    float	XFreqDoopAdaptFact; /*Ƶ������Ӧϵ��*/
    float	XFreqMaxDev;	/*Ƶ�����ƫ��*/
    int		XFreqDevDir;	/*Ƶ��ƫ���*/
    int		XStrStp_Delay;  /*��ͣ����ʱ*/
    float	XAP_Comp_Step;	/*�й���������*/
    int		XAP_DistributeDelay;	/*������ʱ*/
    int		Lim_Change;			/*�й���ֵ�����仯*/
    int         AP_Alm_Time;
    int         Offset_Enable;
    float       Curve[288];     /**/
    float       SR_Curve[288];
    float       Offset;
    int         CurvePointNum;  
    int         FirstRun;
    int         APCopyTime;
    int         SRCopyTime;
    int         JR_APCopyTime;
    int         JR_SRCopyTime;
    int		Setp_ErrorTime;
	char	English_Name[20];
	char    Chinese_Name[20];
#ifdef CASCADE
	float	yggd_pyl;
#endif
	int		AllocationToUnit;
	int		Last_AllocationToUnit;
} T_PLANT;   

typedef struct
{
    int		Status;            /*����״̬ */
    int		XStatus;
    int         Maint_Status;
    int		Last_Status;		/*�ϴλ���״̬*/
    int         AP_Sel;
    int         AP_Permit;
    int		AP_Avail;           /*�����Ƿ����ؿɵ�*/
    int		Last_AP_Avail;		/*�ϴλ����Ƿ����ؿɵ�*/
    float	AP_RtValue;				/*ʵ���й�*/
    float	Last_AP_RtValue;
    float       InputPower;
    int		AP_Faulty;			/*�й�������������*/
    float	Standby_Time;         /*��������ʱ�䣬��λ����*/
    float	Generating_Time;         /*��������ʱ�䣬��λ����*/
    int		Start;			/*����*/
    int		Stop;			/*ͣ��*/
    int		XStop;			/*ж�ظ�����δ��ͣ����*/
    int		Start_Req;      /*��������*/
    int		Stop_Req;       /*ͣ������*/
    int		XAnswerNo;		/*�ܾ�*/
    int		segment;          /*���������糧*/
    float	AP_Min;          /*������������*/
    float	AP_Max;          /*������������*/
    float       Last_AP_Min;
    float       Last_AP_Max;
    float	CurrentUplmt;                 /*��ǰ����Խ��������*/
    float	CurrentLowlmt;                /*��ǰ����Խ��������*/
    float       Privilege;     /*��ͣ�����ȼ�*/
    int		Type;			/*��������*/
    float	XAP_Setp;		/*���������й�ֵ*/
    float	AP_Setp;		/*���������й�ֵ*/
    float	YAP_Setp;
    float	ZAP_Setp;
    int		StartCmdTime;		/*��������ʱ��*/
    int		StopCmdTime;		/*ͣ��ж��ʱ��*/
    int		StopTime;			/*����ͣ������ʱ�䣨����ͣ��ʧ�ܱ�����*/
    int		StopAction;			/*���Ϊͣ������*/
    int		StartAction;		/*��ע����Ϊ��������*/
    int         StartProcess;
    int		Starting;			/*���ڿ������飬��PLC��״̬*/
    int		Stopping;			/*����ͣ�����飬��PLC��״̬*/
    int         ReduceLoad;
    int		StartFlag;
    int		StopFlag;
    int		StartTime;         /*���鿪������ʱ�䣨��������ʧ�ܱ�����*/
    int		XAPCompMode;		/*�й���������*/
    int		XPowerUp;
    int		Zone;				/*��������������*/
    int		Vib_Zone;			/*0/1��ʾ����/������*/
    int		AllocationInVib;    /*�����й�������*/
    int		XVibDelay;			/*ͳ�ƻ���������ʱ��*/
    int		XAP_Setp_Calc;		/*�������µ��趨ֵ*/
    int		XStartUpTime;		/*���鲢�����ʱ*/
    int		AP_Fail;			/*�й�����ʧ��*/
    int		XStartBlockTime;	/*��������ʱ��*/
    int		CommandTime;		/*������ͣ�������ʱ��10��*/
    int		APCompTime;			/*�й�����ʱ��*/
    int		StartBlockTime;     /*��������ʱ��*/
    int		StopBlockTime;     /*ͣ������ʱ��*/
    int         AP_FailTime;
    int         ReduceLoadFailTime;
    float	Flow;				/*����*/
    float       Efficiency;
    T_CTRL_Fail     XAP_Err_Detect;     /*����й�����*/
} T_UNIT;     /*���鹤��*/



/*Ч������һ��*/
typedef struct {
  float         OutPow;        /*�������*/
  float         Eff;           /*Ч��efficiency*/
  float         Flow;          /*����Water Flow*/
  unsigned char VibZone;       /*������ϢVibration zone */
                               
}T_EffRec;

/*ĳһˮͷЧ�����߽ṹ*/
typedef struct {
  float    WaterHead;                 /*ˮͷ*/
  float    MinPower;                  /*��ˮͷ����С����*/
  float    MaxPower;                  /*��ˮͷ��������*/
  T_EffRec EffCurve[MAXDEFPOINTS+1];  /*25��Ч������ֵ*/
}T_EffCurve;

//Definition of one type of unit
typedef struct  {
  int       used;
  T_EffCurve WaterHead[MAXDEFPOINTS+1];
}T_EffSet;

//Calculated efficiency record for actual water head
typedef struct  {
  float         OutPow;        /*�������*/
  float         Eff;           /*Ч��Efficency*/
  float         Flow;          /*����Water Flow*/
  float         InpPow;        /*���빦�� Input Power*/
  float         dInp_dOut;     /*Slope of Input Power devided by Output Power*/
  unsigned char VibZone;       /*������ϢVibration zone */
                               
}T_AGCRec;

//Calculated efficiency curve for actual water head
typedef struct  {
  float    WaterHead;                 /*ˮͷ*/
  float    MinPower;                  /*��ˮͷ����С����*/
  float    MaxPower;                  /*��ˮͷ��������*/
  T_AGCRec EffCurve[MAXAGCPOINTS+1];  /*35��Ч������ֵ*/
}T_AGCCurve;

//Set for one vibration zone
typedef struct {
  int     Used;
  float    AP_Begin;                  //Active power at begin of zone
  float    AP_End;                    //Active power at end of zone
  float    AP_Size;                   //Size of zone
}T_VibSet ;

//Vibration zone for actual water head
typedef struct {
  int     Used;
  T_VibSet Vibration[VIBRATION_NUMB+1];
} T_AGCVibration;


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



char DB_NAME_QC_AGC[MAXSEGMENT][NAME_SIZE];
char DB_NAME_CLOSED_LOOP[MAXSEGMENT][NAME_SIZE];
char DB_NAME_CONTROL_RIGHT[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SEL_BUS[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_Setting[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_Curve[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_Regulation[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_COMPENSATION[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_RTVALUE[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_YG_GD[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_UNIT_STATUS[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_LXBYSJ[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_LXYXSJ[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_PRVILEGE[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_STATE_SETVALUE[MAXSEGMENT][NAME_SIZE];
char DB_NAME_CASECADE_SETVALUE[MAXSEGMENT][NAME_SIZE];
char DB_NAME_OPERATOR_SETVALUE[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_ACTVALUE[4][NAME_SIZE];
char DB_NAME_FR_SETPOINT[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SR_SETPOINT[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_MIN[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_MAX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_XMIN[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_XMAX[MAXSEGMENT][NAME_SIZE]; //act value
char DB_NAME_FR_DEADBAND[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_CompDeadband[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SS_DEADBAND[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_VZ_DEADBAND[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_ChangeMax[MAXSEGMENT][NAME_SIZE];
char DB_NAME_WATERHEAD[NAME_SIZE];
char DB_NAME_STARTING[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_STOPPING[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_SR_AVAIL_SETTING[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SR_AVAIL_CURVE[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Maint_Status[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_UNIT_AGCSEL[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_UNIT_Permit[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_CZKT[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_UNIT_SETPOINT[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_ANSWERYES[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Start_Req[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Stop_Req[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Start_Cmd[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Stop_Cmd[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_ReduceLoad[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Efficiency[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Flow[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Real_APSetpoint[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Real_FrSetpoint[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Unit_Efficiency[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AP_RtSum[MAXSEGMENT][NAME_SIZE];
char DB_NAME_RunInVibration[MAXSEGMENT][NAME_SIZE];
char DB_NAME_PlantStrStp_Req[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SSAnswerYes[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SSAnswerNo[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_Deadband[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_Fail[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_Fail[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_PowGenDB[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Offset_Enable[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Offset[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_Min[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_Max[MAXSEGMENT][NAME_SIZE];
char DB_NAME_EC_DEADBAND[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_ChangeMax[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Real_SRValue[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Unit_AP_Fail[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Curve_Too_Small[MAXSEGMENT][NAME_SIZE];
char DB_NAME_APSetpoint_Err[MAXSEGMENT][NAME_SIZE];
char DB_NAME_AP_Dev_Alm[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SR_MaxChange[MAXSEGMENT][NAME_SIZE];
char DB_NAME_SR_MaxValue[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Copy_AP_SD[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Copy_AP_XZ[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Copy_JR_AP_SD[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Copy_JR_AP_XZ[MAXSEGMENT][NAME_SIZE];
char DB_NAME_VIBRATION1_MIN[VIBRATION_NUMB+1][NAME_SIZE];
char DB_NAME_VIBRATION1_MAX[VIBRATION_NUMB+1][NAME_SIZE];
char DB_NAME_VIBRATION2_MIN[VIBRATION_NUMB+1][NAME_SIZE];
char DB_NAME_VIBRATION2_MAX[VIBRATION_NUMB+1][NAME_SIZE];
char DB_NAME_VIBRATION3_MIN[VIBRATION_NUMB+1][NAME_SIZE];
char DB_NAME_VIBRATION3_MAX[VIBRATION_NUMB+1][NAME_SIZE];
char DB_NAME_MIN[MAXTYPES+1][NAME_SIZE];
char DB_NAME_MAX[MAXTYPES+1][NAME_SIZE];
char DB_NAME_MLKG[NAME_SIZE];
char DB_NAME_ONLINE_STA[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_STOP_STA[UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AGC_Whead[NAME_SIZE];
char DB_NAME_Water_Level1[2][NAME_SIZE];
char DB_NAME_Water_Level2[2][NAME_SIZE];
char DB_NAME_JRFHQX_SD[MAXSEGMENT][NAME_SIZE];
char DB_NAME_MRFHQX_SD[MAXSEGMENT][NAME_SIZE];
char DB_NAME_JRFHQX_XZ[MAXSEGMENT][NAME_SIZE];
char DB_NAME_MRFHQX_XZ[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_JRFHQX_SD[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_JRFHQX_XZ[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_MRFHQX_SD[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_MRFHQX_XZ[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_JRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_TD_MRDYQX[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FailToSetp[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Gap[MAXSEGMENT][NAME_SIZE];
char DB_NAME_Setp_Error[MAXSEGMENT][NAME_SIZE];
char DB_NAME_FR_REACT_VALUE[MAXSEGMENT][NAME_SIZE];

char DB_NAME_AllocationToUnit[MAXSEGMENT][NAME_SIZE];
#ifdef CASCADE
char DB_NAME_CasToPlantValue[MAXSEGMENT][NAME_SIZE];
char DB_NAME_YGGD_PYL[MAXSEGMENT][NAME_SIZE];
#endif

static float factor[]={0,1,1,1,1,1,1,1,1}; 


