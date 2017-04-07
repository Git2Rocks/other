#include    "/home/ems/system/dms/v4.0a/inc/dms_structure_def.h"
#include    "/home/ems/system/dms/v4.0a/inc/dms_data_def.h"
#include    "/home/ems/system/dms/v4.0a/inc/dms_functions.h"

#include <time.h>

DMS_COMMON 	common_aa, common_bb, *common_aaa;

#define	CHANN_FAIL	2
#define DATA_GOOD	0
#define	DATA_ERR	-1
#define DATA_OVER_LMT	-5
#define FLT_E		0.05

#define NAME_SIZE   40
#define MAX_IRRIGATION_GROUP_NUMB	8//ÿ�����ϵͳ������ֹ�����8
#define MAX_FIELD_NUMB 5 //������������ϵͳ��327��
#define MAX_IRRIGATION_TURN 4//����ȴ��� 30
#define MAX_VALVE_NUM_IN_GROUP 10
#define MAX_FIELD_VALVE_NUM	350

/*#define KJML		1	
#define TJML		2*/
#define OPEN		1
#define CLOSE		0

#define WCZTHM	 0	/* no operation */
#define KJLTHM	 1	/* ��ʼ�ֹ��� */
#define TJLTHM	 2	/* ֹͣ����� */


#define IN_STANDBY 0
#define IN_PUMPING 1
#define IN_PUMPED	2

//#define DEBUG

struct tm  *ntime;
DMS_COMMON common_aa;
int IRRIGATION_GROUP_NUMB=0,IRRIGATION_TURN_NUMB=0;
int FIELD_NUM=0;
//int move_curve=0;
//int src_id=0;
int oldmonth=0,oldday=0,oldhour=0,oldmin=0;
char   logfilename[50]="";
int AIC_Period=0;
int	AIC_Loop;



typedef struct
{
    int		Status[MAX_IRRIGATION_TURN+1];            /*�ֹ���ʵʱ״̬ */
    int		AP_Avail;           /*�����Ƿ�����ֹ�*/
    int		Pumping_Time[MAX_IRRIGATION_TURN+1];         /*��Ҫ���ʱ�䣬��λ��Сʱ*/
	int		Pumped_time[MAX_IRRIGATION_TURN+1];		/*�Ѿ����ʱ��*/
	time_t start_time[MAX_IRRIGATION_TURN+1];		/*��ʼ���ʱ��*/
	time_t end_time[MAX_IRRIGATION_TURN+1];		/*�رչ��ʱ��*/
    int		Start;			/*��ʼ���*/
    int		Stop;			/*ֹͣ���*/
	int		cur_turn;
	char db_name_valve[MAX_VALVE_NUM_IN_GROUP+1][NAME_SIZE];
} T_IRRIGATION_GROUP;     /*�ֹ��鹤��*/  

typedef struct
{
    int		Status[MAX_IRRIGATION_TURN+1];            /*����ʵʱ״̬ */
    int		AP_Avail;           /*�÷����Ƿ�����ֹ�*/
    int		Pumping_Time[MAX_IRRIGATION_TURN+1];         /*������Ҫ���ʱ�䣬��λ��Сʱ*/
	int		Pumped_time[MAX_IRRIGATION_TURN+1];		/*�����Ѿ����ʱ��*/
	time_t start_time[MAX_IRRIGATION_TURN+1];		/*��ʼ���ʱ��*/
	time_t end_time[MAX_IRRIGATION_TURN+1];		/*�رչ��ʱ��*/
    int		Start;			/*���ι�ȿ�ʼ*/
    int		Stop;			/*���ι��ֹͣ*/	
	int cur_turn;
	char db_name_valve[NAME_SIZE];
} T_IRRIGATION_FIELD_GATE;     /*�ֹ෧�Ź���*/

typedef struct
{
    int		Status;            /*���ϵͳʵʱ״̬ */
    int		AP_Avail;           /*�����ϵͳ�Ƿ�����ֹ�*/
    int		Pumping_Time[MAX_IRRIGATION_TURN+1];         /*������Ҫ���ʱ�䣬��λ��Сʱ*/
	int		Pumped_time[MAX_IRRIGATION_TURN+1];		/*�����Ѿ����ʱ��*/
	time_t start_time[MAX_IRRIGATION_TURN+1];		/*��ʼ���ʱ��*/
	time_t end_time[MAX_IRRIGATION_TURN+1];		/*�رչ��ʱ��*/
    int		Start;			/*���ι�ȿ�ʼ*/
    int		Stop;			/*���ι��ֹͣ*/
	T_IRRIGATION_GROUP Irrigation_Group[MAX_IRRIGATION_GROUP_NUMB+1];//���ϵͳ���ֹ���
	int group_num;
	int Cur_Turn;
} T_IRRIGATION_FIELD;     /*���ϵͳ����*/

typedef struct
{
    int		AIC_state;            /*AIC  Ͷ��/�˳�*/
   // int		Control_Right;         /* ����Ȩ  ����/�ݵ�/���� 0Ϊ���ء�1Ϊ�ݵ���2Ϊ����*/
    int		Closed_Loop;    /*����/�ջ�*/
	int		Field_num;
	T_IRRIGATION_FIELD_GATE Field_Gate[MAX_FIELD_NUMB+1];
	T_IRRIGATION_FIELD Field_Sys[MAX_FIELD_NUMB+1];
} T_PUMP; 

typedef struct
{
    int		Start[MAX_IRRIGATION_TURN+1];     /*��һ�ֹ���*/
    int		Stop[MAX_IRRIGATION_TURN+1];      /*��һͣ����*/
    int     CurvePointNum;  
	int	IrrigationGroup;//��ǰ���ȵ��ֹ����
} GROUP_PUMP;   



typedef struct
{
        int     ctrl_type;
        int     p;
}       CMD_DEF;        /*���Ƶ�������*/

typedef struct
{
        POINTER ptr;
        ANLG_DATA value;
        char   sec;
	    char   min;
}       COMMON_DEF;     /* ͨѶ���ݰ� */

T_PUMP PUMP;


char DB_NAME_AIC_Period[NAME_SIZE];
char DB_NAME_Control_Right[NAME_SIZE];
char DB_NAME_AIC_CLOSED_LOOP[NAME_SIZE];
char DB_NAME_QC_AIC[NAME_SIZE];


char DB_NAME_AP_Group_Field[MAX_FIELD_NUMB+1][NAME_SIZE];//���ϵͳ�����ֹ�
char DB_NAME_AP_Group_Group[MAX_FIELD_NUMB+1][MAX_IRRIGATION_GROUP_NUMB+1][NAME_SIZE];//�ֹ�������ֹ�


char DB_NAME_FIELD_AP_CZKT[MAX_FIELD_NUMB+1][NAME_SIZE];//���ϵͳ����ɿ�
char DB_NAME_GROUP_AP_CZKT[MAX_FIELD_NUMB+1][MAX_IRRIGATION_GROUP_NUMB+1][NAME_SIZE];//�ֹ������ɿ�

char DB_NAME_AIC_STATE[NAME_SIZE];//AICִ��/����״̬


char DB_NAME_Group_StartTime[MAX_FIELD_NUMB+1][MAX_IRRIGATION_GROUP_NUMB+1][MAX_IRRIGATION_TURN+1][NAME_SIZE];
char DB_NAME_Group_EndTime[MAX_FIELD_NUMB+1][MAX_IRRIGATION_GROUP_NUMB+1][MAX_IRRIGATION_TURN+1][NAME_SIZE];
char DB_NAME_Group_PumpTime[MAX_FIELD_NUMB+1][MAX_IRRIGATION_GROUP_NUMB+1][MAX_IRRIGATION_TURN+1][NAME_SIZE];


char DB_NAME_Field_StartTime[MAX_FIELD_NUMB+1][MAX_IRRIGATION_TURN+1][NAME_SIZE];
char DB_NAME_Field_EndTime[MAX_FIELD_NUMB+1][MAX_IRRIGATION_TURN+1][NAME_SIZE];
char DB_NAME_Field_PumpTime[MAX_FIELD_NUMB+1][MAX_IRRIGATION_TURN+1][NAME_SIZE];

char DB_NAME_Field_Control_Command[MAX_FIELD_NUMB+1][NAME_SIZE];
char DB_NAME_IrrigationGroup_Control_Command[MAX_FIELD_NUMB+1][MAX_IRRIGATION_GROUP_NUMB+1][NAME_SIZE];

char DB_NAME_Field_Status[MAX_FIELD_NUMB+1][NAME_SIZE];
char DB_NAME_Group_Status[MAX_FIELD_NUMB+1][MAX_IRRIGATION_GROUP_NUMB+1][NAME_SIZE];


