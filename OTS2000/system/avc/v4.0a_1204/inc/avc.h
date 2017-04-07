//#define SUN_OS
#define WINDOWS
#define	HOST_NAME	"HOSTNAME"

#define SCHEDULE    24
#define NAME_SIZE   40
#define MAX_UNIT_NUMB	20
#define	DATA_ERR	-1
#define	CHANN_FAIL	2
#define SIGN_MASK	0x80
#define NOT 0
#define YES 1
#define MAX_ITEM_NUMB	30

#define WGTJML		0xc00
#define TGLTHM	 0 	/* ������ */

#define DEBUG
#define PBG

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

struct tm  *ntime;
DMS_COMMON common_aa;
int UNIT_NUMB=0;
char   logfilename[50]="";
int move_curve=0;
int src_id=0;
int oldday=0;
int PQ_Enable=0;
int AVC_Loop=0;
int Voltage_Min,Voltage_Max;
float AP_RtValue[MAX_UNIT_NUMB+1];
int RP_Step[MAX_UNIT_NUMB]={0};
float DB_RP_WorkSP;
float MaxAdj_V;

int TypeNumber=0;
int Type_UnitNo[MAX_UNIT_NUMB+1][MAX_UNIT_NUMB+1]={0};
int ItemNum=0;
float AP_Power[MAX_UNIT_NUMB]={0};
float PQCurve[MAX_UNIT_NUMB+1][MAX_ITEM_NUMB][4];
char TypeKeyword[MAX_UNIT_NUMB+1][50];

typedef struct
{
        POINTER ptr;
        ANLG_DATA value;
        char   sec;
	    char   min;
}       COMMON_DEF;     /* ͨѶ���ݰ� */

typedef struct
{
    int			Type;		/*������������*/
	int			RP_Sel;		/*ѡ���޹�����*/
	int			RP_Permit;    /*�޹���������*/
	int			RP_Avail;	    /*�����޹����ؿɵ�*/
	int			Last_RP_Avail;  /*�ϴλ����޹�����״̬*/
	int			RP_Faulty;  /*�����޹�����ֵ����*/
	int			AP_Faulty;  /*�����й�����ֵ����*/
	int			Status;		/*����״̬*/
    int			Maint_Status;    
	int			Privilege;	/*����������ȼ�*/
	int			RPCompMode;		/*���鲹��ģʽ*/
    int         RPCompTime;
    int                 Lock_increase;    /*��ѹ��������Խ�޲������޹�*/
    int                 Lock_decrease;   /*��ѹ�Ͳ��ɼ��޹�*/
	float       RP_RtValue;	/*ʵ���޹�����*/
	float       AP_RtValue;	/*�й�ʵ��ֵ*/
	float       RP_Min;		/*������С�޹�����*/
	float       RP_Max;		/*��������޹�����*/
    float       Last_RP_Min;
    float       Last_RP_Max;
	float       RP_Setp;		/*�޹������趨ֵ*/
	float       XRP_Setp;	
    float       YRP_Setp;
    float       ZRP_Setp;
    int         RP_Setp_Calc;
    float       RP_MaxChange;
    int         RP_Fail;
    float				I_max;		/*���ӵ�������*/
    float				LC_I_max;	/*ת�ӵ�������*/
    float				U_max;		/*���˵�ѹ��������*/
    float				U_min;		/*���˵�ѹ��������*/
	int			Increase_Prohibit;
	int			Decrease_Prohibit;
}T_UNIT;

typedef struct 
{
	int     RP_MODE;        /*AVC�����ܿ���*/
    int     FirstRun;
    int		Mode;		/*AVC���ڷ�ʽ(�޹�����1/��ѹ����2/��ѹ����3/��ѹ����4/�޹���5)*/
	int		Control_Right;
    int		Last_Mode;
	int		AVC_Period;
    int     VO_Curve;               /*voltage curve mode*/
	int		RP_Setting;
    int     VO_Setting;
	int		VO_Regulation;		/*��ѹ����ģʽ*/
	int     VO_Compensation;	/*��ѹ����ģʽ*/
    int     Close_Loop;	/*0Ϊ������1Ϊ�ջ�*/
	int		RP_Faulty;	/*�޹�����ֵ����*/
	int     AP_Faulty;  /*�й�����ֵ����*/
	int     VO_Faulty;	/*��ѹ����ֵ����*/
	int     Num_RP_Avail;        /*�޹����ؿɵ�����̨��*/
    int     Last_Num_Avail;
    int     GenNumb;
	int		XRP_Recalc;			/*ѭ����������*/
    int     Lim_Change;
    int     ALG_AVG;	/*�޹�ƽ�����䷽ʽ*/
    int     ALG_EQUCOS;	/*�ȹ����������䷽ʽ*/
    int                 Lock_RP_increase;    /*��ѹ��������Խ�޲������޹�*/
    int                 Lock_RP_decrease;   /*��ѹ�Ͳ��ɼ��޹�*/
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
    float   XVolt_Output;
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
	int		dqv;
}T_PLANT;


char DB_NAME_Curve_Low[SCHEDULE+1][NAME_SIZE];
char DB_NAME_Curve_High[SCHEDULE+1][NAME_SIZE];
//char DB_NAME_Tomorrow_Curve[SCHEDULE+1][NAME_SIZE];
char DB_NAME_Rt_Status[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_QC_AVC[NAME_SIZE];
char DB_NAME_AVC_KBH[NAME_SIZE];
char DB_NAME_Run_State[NAME_SIZE];
char DB_NAME_DY_GD[NAME_SIZE];
char DB_NAME_DYQX_GD[NAME_SIZE];
char DB_NAME_WGGD[NAME_SIZE];
char DB_NAME_AVC_AVGALG[NAME_SIZE];
char DB_NAME_AVC_EQUCOSALG[NAME_SIZE];
char DB_NAME_Control_Right[NAME_SIZE];
char DB_NAME_SD_Right_ON[NAME_SIZE];
char DB_NAME_SD_Right_OFF[NAME_SIZE];
char DB_NAME_ON_SD_CTRL[NAME_SIZE];
char DB_NAME_VO_Setpoint[NAME_SIZE];
char DB_NAME_VO_Remote_Setpoint[NAME_SIZE];
char DB_NAME_VO_DeadBand[NAME_SIZE];
char DB_NAME_DQV[NAME_SIZE];
char DB_NAME_V_MAX_CHANGE[NAME_SIZE];
char DB_NAME_VO_RtValue[7][NAME_SIZE];
char DB_NAME_AP_RtValue[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_RtValue[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_OptiValue[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_SetValue[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_Setpoint[NAME_SIZE];
char DB_NAME_RP_Remote_Set[NAME_SIZE];
char DB_NAME_RP_CZ[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_CZKT[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_LMT[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_RP_LLMT[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AVC_Period[NAME_SIZE];
char DB_NAME_WG_UP_LOCK[NAME_SIZE];
char DB_NAME_WG_DN_LOCK[NAME_SIZE];
char DB_NAME_AVC_UMAX[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AVC_UMIN[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AVC_IMAX[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_LC_I_MAX[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AVC_UAB[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AVC_I[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_AVC_LCI[MAX_UNIT_NUMB+1][NAME_SIZE];
char DB_NAME_Prvilege[MAX_UNIT_NUMB+1][NAME_SIZE];

T_UNIT  UNIT[MAX_UNIT_NUMB];
T_PLANT PLANT;
char    hostname[20];
float Curve_time_begin[SCHEDULE+1],Curve_time_end[SCHEDULE+1];