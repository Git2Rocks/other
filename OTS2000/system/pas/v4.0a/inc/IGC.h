#ifndef	_IGC_MODULE_DEF_H
#define	_IGC_MODULE_DEF_H


#define DEBUG

#ifdef		_WIN32
#define		WINDOWS_OS
#else
#define     SUN_OS
#endif


#ifdef SUN_OS
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include <time.h>
#include <string.h>
#else
#include<fcntl.h>
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h> 
//#include <shellapi.h>
#endif

#define   SYS_DEFINE_PATH_UNIX		"/home/ems/h9000/def/"
#define   SYS_DEFINE_PATH_WIN		"\\home\\ems\\h9000\\def\\"

#define	IGC_CSOURTHPATH_UNIX 	"/home/ems/system/pas/v4.0a/src/"
#define	IGC_CSOURTHPATH_WIN     "\\home\\ems\\system\\pas\\v4.0a\\src\\"
#define	IGC_DEBUGPATH_WIN     "\\home\\ems\\system\\pas\\v4.0a\\src\\Debug\\"
#define	IGC_DEBUGPATH_UNIX 	"/home/ems/system/pas/v4.0a/src/"
#define IGC_CSOURTHFINENAME     "igc.c"
#define	IGC_DEF_FILE           "IGC_DEF_FILE.def" 

#ifdef		WINDOWS_OS
#define     IGC_CSOURTHPATH IGC_CSOURTHPATH_WIN
#define     SYS_DEFINE_PATH SYS_DEFINE_PATH_WIN
#define     IGC_DEBUGPATH IGC_DEBUGPATH_WIN 
#else       /*UNIX*/
#define     IGC_CSOURTHPATH IGC_CSOURTHPATH_UNIX
#define     SYS_DEFINE_PATH SYS_DEFINE_PATH_UNIX
#define     IGC_DEBUGPATH IGC_DEBUGPATH_UNIX
#endif 

/*#ifdef	    WINDOWS_OS
#define		Msleep(ms)				Sleep(ms)
#else
#define		Msleep(ms)				usleep(ms*1000)
#endif*/


#ifdef	    WINDOWS_OS
#define		igc_access   			_access
#else
#define		igc_access			access
#endif


#define	TAB		9
#define CR		0xd
#define LF		0xa

#define	IGC_LINE_BUF_CHAR	512
#define	IGC_DATA_NAME_LONG	32

#define	Ifloat 	  10000
#define	Idouble	  10000
#define	Iint      10000
#define	Iuint	  10000
#define	Ilong	  10000
#define	Iulong	  10000
#define	Ibool	  10000
#define	Ishort	  10000
#define	Iushort	  10000
#define	Ichar	  10000
#define	Iuchar	  10000
#define	Ibyte	  10000
#define	Idatetime 10000
#define	IH9000_IGC_data 10000

#define	IH9000_IGC_CHARA_data 10000
#define	IH9000_IGC_IND_data   10000
#define	IH9000_IGC_ANA_data   10000

#define	Itimer 10000
#define	Itimer_sysuse 2010
#define	Ialarms 200

#define	loop_sleep_minisec 50 


unsigned long run_count;
unsigned long all_run_millisecond;
unsigned int  last_run_millisecond;
unsigned int  avg_run_millisecond;
unsigned int  max_run_millisecond;
unsigned int  min_run_millisecond;
unsigned long run_count_for_avg;
//DWORD h9000_igc_starttype_cmd_fuc_pam;
int  igc_CLK_TCK;

typedef struct
{	
	int second;     /* seconds after the minute - [0,59] */
	int minute;     /* minutes after the hour - [0,59] */
	int hour;    /* hours since midnight - [0,23] */
	int day;    /* day of the month - [1,31] */
	int month;     /* months since January - [1,12] */
	int year;    
	
}IGC_datetime; 

typedef struct
{
	float value;
	int   int_value;
	int   chan_fail;
	int   ok_flag;
	IGC_datetime update_time;
	IGC_datetime change_time;
}H9000_IGC_data;

typedef struct
{
	int   value;
	int   chan_fail;
	int   ok_flag;
	IGC_datetime update_time;
	IGC_datetime change_time;
}H9000_IGC_IND_data;

typedef struct
{
	float value;
	float D_BAND;    //����ֵ
	float HH_LMT;    //������
	float H_LMT;     //����		
	float L_LMT;     //����
	float LL_LMT;    //������
	float HR_LMT;    //�ϸ���
	float LR_LMT;    //�¸���
	float ENG_CVT;	 //����ת��ϵͳ	
	float HI_RANGE;  //������
	float LO_RANGE;	 //������
	float ZERO;      //0ֵ
	float COMPENSATE;//����ֵ
	float TR_LIM;    //������ֵ
	float RT_LIM;    //���Ƹ�������ֵ
	int   int_value;
	int   chan_fail;
	int   ok_flag;
	
	IGC_datetime update_time;
	IGC_datetime change_time;
}H9000_IGC_ANA_data;

typedef struct
{
	int		max_no;      //���ֵ���
	int		min_no;      //��Сֵ���
	int		max_rate_no; //���仯ֵ���
	int		min_rate_no; //��С�仯ֵ���
	float	max_value;   //���ֵ
	float	min_value;   //��Сֵ
	float	avg_value;   //ƽ��ֵ
	float	std_value;   //����ֵ
	float   max_rate;    //���仯��
	float   min_rate;    //��С�仯��
	
	int   chan_fail;
	int   ok_flag;
	
	IGC_datetime update_time;
	
}H9000_IGC_CHARA_data;


IGC_datetime  lacal_datetime_now;//20110905
enum time_unit  {unit_second,unit_minute,unit_hour,unit_day};
enum yes_no  {no,yes};
typedef struct
{
	enum yes_no enable;
	enum yes_no autorestart;
	enum time_unit unit;
	unsigned int full_count;
	unsigned int real_count;
	unsigned int reached_times;
	IGC_datetime lastdotime;
	int inited;
}H9000_timer;

typedef struct
{
	int     ok_flag;
	char	sn_str[12];
	char	time_str[64];
	char	repeatAlm[12];
	char	logicname[52];
	char	longname[112];
	char	state_str[128];

	char	hostname[10];
	char	usrname[8];
	char	message[256];
	IGC_datetime igc_datetime;
} H9000_IGC_alarm_record;
 
float          I_floats[Ifloat];
double         I_doubles[Idouble];
int            I_ints[Iint];
unsigned int   I_uints[Iuint];
long           I_longs[Ilong];
unsigned long  I_ulongs[Iulong];
int            I_bools[Ibool];
short          I_shorts[Ishort];
unsigned short I_ushorts[Iushort];
char           I_chars[Ichar];
unsigned char  I_uchars[Iuchar];
IGC_datetime   I_datetimes[Idatetime];
H9000_IGC_data I_H9000_IGC_datas[IH9000_IGC_data];

H9000_IGC_CHARA_data I_H9000_IGC_CHARA_datas[IH9000_IGC_CHARA_data];
H9000_IGC_IND_data   I_H9000_IGC_IND_datas[IH9000_IGC_IND_data];
H9000_IGC_ANA_data   I_H9000_IGC_ANA_datas[IH9000_IGC_ANA_data];

H9000_timer    I_H9000_timers[Itimer];
H9000_IGC_alarm_record I_H9000_alarms[Ialarms];

H9000_timer    h9000_igc_timeer_sysuse[Itimer_sysuse];
char           h9000_igc_char_sysuse[Itimer_sysuse];
int            h9000_igc_cmd_num_sysuse[Itimer_sysuse];

enum IGC_ENUM_IND_ALM_STATUS  {	
	IND_ALM_STATUS_0 =0,     //0.   ���������� ֵ0
    IND_ALM_STATUS_1 ,       //1.   ���������� ֵ1
	IND_ALM_STATUS_2,        //2.   ���������� ֵ2
	IND_ALM_STATUS_3,        //3.   ���������� ֵ3
	IND_ALM_STATUS_4,        //4.   ���������� ֵ4
	IND_ALM_STATUS_5,        //5.   ���������� ֵ5
	IND_ALM_STATUS_6,        //6.   ���������� ֵ6
	IND_ALM_STATUS_7,        //7.   ���������� ֵ7
	IND_ALM_STATUS_8,        //8.   ���������� ֵ8
	IND_ALM_STATUS_9,        //9.   ���������� ֵ9
	IND_ALM_STATUS_10,       //10.  ���������� ֵ10
	IND_ALM_STATUS_11,       //11.  ���������� ֵ11
	IND_ALM_STATUS_12,       //12.  ���������� ֵ12
	IND_ALM_STATUS_13,       //13.  ���������� ֵ13
	IND_ALM_STATUS_14,       //14.  ���������� ֵ14
	IND_ALM_STATUS_15,       //15.  ���������� ֵ15
};


enum IGC_ENUM_ANA_ALM_STATUS  {	
	ANA_ALM_STATUS_NORM_SCAN =0,     //0.   ����״̬
	ANA_ALM_STATUS_OVER_HH_LMT ,     //1.   Խ������
	ANA_ALM_STATUS_OVER_H_LMT,       //2.   Խ����
	ANA_ALM_STATUS_OVER_L_LMT,       //3.   Խ����
	ANA_ALM_STATUS_OVER_LL_LMT,      //4.   Խ������
	ANA_ALM_STATUS_BACK_H_LMT,       //5.   ������
	ANA_ALM_STATUS_BACK_L_LMT,       //6.   ������
	ANA_ALM_STATUS_BACK_HH_LMT,      //7.   ��������
	ANA_ALM_STATUS_BACK_LL_LMT       //8.   ��������
};


enum IGC_ENUM_TREND_ALM_STATUS  {	
	TREND_ALM_STATUS_NORM_SCAN =0,     //0.   ����״̬
	TREND_ALM_STATUS_OVER_TR_LMT ,     //1.   ����Խ��
	TREND_ALM_STATUS_BACK_TR_LMT ,     //2.   ���Ƹ���
};


enum IGC_ENUM_IGC_ALM_TYPE  {	
	IGC_ALM_TYPE_LMT_ALM =1,       //1.   ����Խ���ޱ���
	IGC_ALM_TYPE_TREND_ALM ,       //2.   ����Խ���ޱ���	
	IGC_ALM_TYPE_CHAN_FAIL_ALM ,   //3.   ͨ������
	IGC_ALM_TYPE_CTRL_BLOCK_ALM ,  //4.   �˳�����
	IGC_ALM_TYPE_OVERFLOW_ALM      //5.   �������
};

#define IGC_ALM_DAYAFLOW_FLAG_YES 1       //���ݱ���ʱ���
#define IGC_ALM_DAYAFLOW_FLAG_NO  0       //���ݱ���ʱδ���

#define IGC_DATA_QUALITY_NOCHG -1       //��������������
#define IGC_DATA_QUALITY_OK   0         //������������
#define IGC_DATA_QUALITY_FAIL 1         //������������

#define  IGC_DATA_MAN_SET_NOCHG  -1     //�������ֶ���������״̬
#define  IGC_DATA_MAN_SET_FORCE   1     //�����ֶ���������
#define  IGC_DATA_MAN_SET_NOFORCE 0     //ȡ���ֶ���������

#define  IGC_DATA_CHAN_FAIL_NOCHG  -1     //������ͨ������״̬
#define  IGC_DATA_CHAN_FAIL_SET     1     //����ͨ������
#define  IGC_DATA_CHAN_FAIL_CANCEL  0     //����ͨ������

#define  IGC_DATA_CHAN_FAIL_YES     1     //����ͨ������
#define  IGC_DATA_CHAN_FAIL_NO      0     //������ͨ������

#define  IGC_IND_ALMTYPE_CHANGE     1     //��������λ����
#define  IGC_IND_ALMTYPE_MAN_SET    2     //�������ֶ����ñ���
#define  IGC_IND_ALMTYPE_CHAN_FAIL  3     //������ͨ�����ϱ���
 

extern int IGC_GetCurentHostCtrlPrvg(int Itype);

extern int IGC_SEND_H9000_SMG(char * smg);
extern int igc_InitStrTextDefine();

extern H9000_IGC_alarm_record igc_search_one_record_by_logicalname(char * logicalname,int Forward_num,int Forward_index);
extern H9000_IGC_alarm_record igc_usetime_search_one_record_by_logicalname(char * logicalname,int Forward_num,int Forward_index,IGC_datetime start_time);
extern H9000_IGC_alarm_record igc_search_one_alarm_by_logicalname(char * logicalname,int Forward_num);

void   h9000_igc_cmd_opfuc_do(int cmdnum) ;
void   h9000_igc_cmd_op_fuc(); 
extern int igc_InterLockFileLoad();
extern int igc_InterLockFree();

extern int IGC_Init_RECORD_IPC();
extern int igc_userlogin(char * user,char * pass);
extern int igc_userunlogin();
extern int igc_SendCmd(int cmdtype,int operate_type,int sim_cmd,char * logicalname,float setvalue,char * interlockname_user);
extern int set_igc_cmd_control_point(int cmd_type,char * logicalname);
extern int clear_igc_cmd_control_point(int cmd_type);
extern int igc_UnMountDB();
 
extern int get_CLK_TCK();
extern int strncmp();
//extern int strlen();
extern int igc_MountDB();
extern int igc_WSAStartup();
extern int igc_lan_out_init();

//extern void igc_SetModuleName(char *module);
extern int	igc_SetErrLogMode(int argc, char *argv[]);
//extern void igc_CreateLockFile(char *filename );
extern void igc_Err_log( char *info_buf );

extern void sleep_second_igclib(int second);
extern void sleep_millisecond_igclib(int millisecond);
extern IGC_datetime get_lacal_datetime_now();
extern long total_time_seconds(IGC_datetime start_time,IGC_datetime end_time);
extern int  get_iogroup_by_pointid(unsigned short stnid,unsigned short devid,unsigned short datatype_id,unsigned short ptid);
extern int  set_iogroup_by_pointid(unsigned short stnid,unsigned short devid,unsigned short datatype_id,unsigned short ptid,unsigned short io_group_id);
extern int  if_point_is_Doublept_By_pointid(unsigned short stnid,unsigned short devid,unsigned short datatype_id,unsigned short ptid);
extern int set_pt_to_doublePt_by_pointid(unsigned short stnid,unsigned short devid,unsigned short datatype_id,unsigned short ptid,unsigned short stnid_P,unsigned short devid_P,unsigned short datatype_id_P,unsigned short ptid_P,int isdoublept);

extern H9000_IGC_data get_data_value_by_logicalname(char * logicalname);
extern H9000_IGC_data get_data_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int POINT_ID);
 
extern H9000_IGC_IND_data get_ind_data_value_by_logicalname(char * logicalname);
extern H9000_IGC_IND_data get_ind_data_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int POINT_ID);

extern H9000_IGC_ANA_data get_ana_data_value_by_logicalname(char * logicalname);
extern H9000_IGC_ANA_data get_ana_data_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int POINT_ID);

extern int ind_alm_by_logicalname(char * logicalname,int alm_status,int stand_by,int MAN_SET,int CHAN_FAIL,int alarm_type,int sendsms_falg);
extern int ana_alm_by_logicalname(char * logicalname,float set_value,int alm_status,int trend_alarm_status,int data_overflow,int CHAN_FAIL,int alarm_type,int sendsms_falg);//status (0.���� 1.Խ������ 2.Խ���� 3.Խ���� 4.Խ������ 5.������ 6.������ 7.�������� 8.��������....)
extern int ind_alm_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,
					   int alm_status,int stand_by,int MAN_SET,int CHAN_FAIL,int alarm_type,unsigned int START_POINT_ID,unsigned int END_POINT_ID,int sendsms_falg);
extern int ana_alm_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,
					   float set_value,int alm_status,int trend_alarm_status,int data_overflow,int CHAN_FAIL,int alarm_type,unsigned int START_POINT_ID,unsigned int END_POINT_ID,int sendsms_falg);

extern int set_ind_value_by_logicalname(char * logicalname,int set_value,int stand_by,int MAN_SET,int CHAN_FAIL,int sendsms_falg);
extern int set_ana_value_by_logicalname(char * logicalname,float set_value,int stand_by,int MAN_SET,int CHAN_FAIL,int data_overflow,int sendsms_falg);
extern int set_int_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int START_POINT_ID,unsigned int END_POINT_ID,
							 int set_value,int stand_by,int MAN_SET,int CHAN_FAIL,int sendsms_falg);
extern int set_ana_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int START_POINT_ID,unsigned int END_POINT_ID,
							 float set_value,int stand_by,int MAN_SET,int CHAN_FAIL,int data_overflow,int sendsms_falg);



#define  IGC_CMDTYPE_C_UNIT 49//��������
#define  IGC_CMDTYPE_OPER_C_UNIT_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_UNIT_stop_NUM 44

enum IGC_ENUM_CMDTYPE_C_UNIT  {	
		CMDTYPE_C_UNIT_Start =1,     //1.   ����
		CMDTYPE_C_UNIT_Stop,         //2.   ͣ��
		CMDTYPE_C_UNIT_Reset,        //3.   �����ֶ�������
		CMDTYPE_C_UNIT_Step,         //4.   ����������
		CMDTYPE_C_UNIT_Jump,         //5.   ��ת��
		CMDTYPE_C_UNIT_NoVoltRun,    //6.   ��ת
		CMDTYPE_C_UNIT_NoLoadRun,    //7.   ����
		CMDTYPE_C_UNIT_BlackStart,   //8.   ���������
		CMDTYPE_C_UNIT_CmpStart,     //9.   ���������
		CMDTYPE_C_UNIT_EmergStop,    //10.  ����ͣ��
		CMDTYPE_C_UNIT_Open,         //11.  ����
		CMDTYPE_C_UNIT_ReadyStart,   //12.  ����׼��
		CMDTYPE_C_UNIT_TransNoLoad,  //13.  �������(�����ٲ�����)
		CMDTYPE_C_UNIT_ZeroVRun,     //14.  ������ѹ
		CMDTYPE_C_UNIT_TranZVRun,    //15.  ������������ѹ
		CMDTYPE_C_UNIT_ZeroVStop,    //16.  ������ѹת����
		CMDTYPE_C_UNIT_StartToCool=20,  //20.  ��������ȴˮ��
		CMDTYPE_C_UNIT_StartToSpin,  //21.  ��������ת��
		CMDTYPE_C_UNIT_StartToNLoad, //22.  ������������
		CMDTYPE_C_UNIT_StartToOnLin, //23.  ������������
		CMDTYPE_C_UNIT_StopToNLoad,  //24.  ͣ����������
		CMDTYPE_C_UNIT_StopToSpin,   //25.  ͣ������ת��
		CMDTYPE_C_UNIT_StopToCool,   //26.  ͣ������ȴˮ��
		CMDTYPE_C_UNIT_StopToStand,  //27.  ͣ����ȫͣ��
		CMDTYPE_C_UNIT_StartStep,    //28.  ������������������
		CMDTYPE_C_UNIT_StopStep,     //29.  ����ͣ������������
		CMDTYPE_C_UNIT_EmergStep,    //30.  ��������ͣ������������
		CMDTYPE_C_UNIT_FastStopStep, //31.  ��������ͣ������������
		CMDTYPE_C_UNIT_PumpStart,    //32.  ����
		CMDTYPE_C_UNIT_PumpStop,     //33.  ͣ��
		CMDTYPE_C_UNIT_DragStart,    //34.  ���Ϸ���
		CMDTYPE_C_UNIT_SFCHSStart,   //35.  ��Ƶ������ת�ٳ�ˮ
		CMDTYPE_C_UNIT_SFCLSStart,   //36.  ��Ƶ������ת�ٳ�ˮ
		CMDTYPE_C_UNIT_SFCHSCmp,     //37.  ��Ƶ������ת��ˮ�õ���
		CMDTYPE_C_UNIT_SFCLSCmp,     //38.  ��Ƶ������ת��ˮ�õ���
		CMDTYPE_C_UNIT_DragHSStart,  //39.  ����������ת�ٳ�ˮ
		CMDTYPE_C_UNIT_DragLSStart,  //40.  ����������ת�ٳ�ˮ
		CMDTYPE_C_UNIT_DragHSCmp,    //41.  ����������ת��ˮ�õ���
		CMDTYPE_C_UNIT_DragLSCmp,    //42.  ����������ת��ˮ�õ���
		CMDTYPE_C_UNIT_PumpToGe,     //43.  ��ˮת����
		CMDTYPE_C_UNIT_GenToPump     //44.  ����ת��ˮ
};

#define  IGC_CMDTYPE_C_BREAKER 50//��·��
#define  IGC_CMDTYPE_OPER_C_BREAKER_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_BREAKER_stop_NUM 15
 

enum IGC_ENUM_CMDTYPE_C_BREAKER  {	
	CMDTYPE_C_BREAKER_Reset=0,        //0. ���ϸ���
	CMDTYPE_C_BREAKER_Open,           //1. ��բ
	CMDTYPE_C_BREAKER_Close,          //2. ��բ
	CMDTYPE_C_BREAKER_IM_Line,        //3. Iĸ����·����
	CMDTYPE_C_BREAKER_IIM_Line,       //4. IIĸ����·����
	CMDTYPE_C_BREAKER_Line_IM,        //5. ��·��Iĸ����
	CMDTYPE_C_BREAKER_Line_IIM,       //6. ��·��IIĸ����
	CMDTYPE_C_BREAKER_Tran_IM,        //7. ��ѹ����Iĸ����
	CMDTYPE_C_BREAKER_Tran_IIM,       //8. ��ѹ����IIĸ����
	CMDTYPE_C_BREAKER_IM_Tran,        //9. Iĸ�Ա�ѹ������
	CMDTYPE_C_BREAKER_IIM_Tran,       //10.IIĸ�Ա�ѹ������
	CMDTYPE_C_BREAKER_TestClose,      //11.�����
	CMDTYPE_C_BREAKER_CancelSyn,      //12.ͬ���˳�
	CMDTYPE_C_BREAKER_LoopClose,      //13.������
	CMDTYPE_C_BREAKER_ChgVltCls,      //14.����
	CMDTYPE_C_BREAKER_ZroVltCls       //15.��ѹ��
};

#define  IGC_CMDTYPE_C_SWITCH 51//���뿪��
#define  IGC_CMDTYPE_OPER_C_SWITCH_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_SWITCH_stop_NUM 4
 

enum IGC_ENUM_CMDTYPE_C_SWITCH  {	
		CMDTYPE_C_SWITCH_Reset,        //0. ���ϸ���
		CMDTYPE_C_SWITCH_Open,         //1.  ��բ
		CMDTYPE_C_SWITCH_Close,        //2.  ��բ
		CMDTYPE_C_SWITCH_TestOpen,     //3.  �����բ
		CMDTYPE_C_SWITCH_TestClose     //4.  �����բ
};



#define  IGC_CMDTYPE_C_APOWER 52//�й�����
#define  IGC_CMDTYPE_OPER_C_APOWER_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_APOWER_stop_NUM 2
 

enum IGC_ENUM_CMDTYPE_C_APOWER  {	
	    CMDTYPE_C_APOWER_Power,     //0.  ���ʵ���
		CMDTYPE_C_APOWER_Openning,  //1.  ���ȵ���
		CMDTYPE_C_APOWER_Flux       //2.  ��������
};



#define  IGC_CMDTYPE_C_RPOWER 53//�޹�����
#define  IGC_CMDTYPE_OPER_C_RPOWER_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_RPOWER_stop_NUM 2
 

enum IGC_ENUM_CMDTYPE_C_RPOWER  {	
	    CMDTYPE_C_RPOWER_Power,      //0.  ���ʵ���
		CMDTYPE_C_RPOWER_Volt,       //1.  ��ѹ����
		CMDTYPE_C_RPOWER_Cos         //2.  ������������	
};


#define  IGC_CMDTYPE_C_DEVICE 54//һ���豸
#define  IGC_CMDTYPE_OPER_C_DEVICE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_DEVICE_stop_NUM 2
 

enum IGC_ENUM_CMDTYPE_C_DEVICE  {	
    	CMDTYPE_C_DEVICE_Reset,       //0. ���ϸ���
		CMDTYPE_C_DEVICE_Off,         //1. �豸�˳�
		CMDTYPE_C_DEVICE_On           //2. �豸Ͷ��		
};

#define  IGC_CMDTYPE_C_GATE 55//բ��
#define  IGC_CMDTYPE_OPER_C_GATE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_GATE_stop_NUM 16
 
enum IGC_ENUM_CMDTYPE_C_GATE  {		
    	CMDTYPE_C_GATE_Reset,       //0. ���ϸ���
		CMDTYPE_C_GATE_Open,        //1. ��բ��
		CMDTYPE_C_GATE_Close,       //2. ��բ��
		CMDTYPE_C_GATE_Stop,        //3. ֹͣ����
		CMDTYPE_C_GATE_Up,          //4. ����(�߶�)
		CMDTYPE_C_GATE_Down,        //5. �½�(�߶�)
		CMDTYPE_C_GATE_FastOpen,    //6. ���ٿ�բ��
		CMDTYPE_C_GATE_FastClose,   //7. ���ٹ�բ��
		CMDTYPE_C_GATE_StepUp,      //8. ��������(�̶��߶�)
		CMDTYPE_C_GATE_StepDown,    //9. �����½�(�̶��߶�)
		CMDTYPE_C_GATE_Forward,     //10.ǰ��
		CMDTYPE_C_GATE_Backward,    //11.��
		CMDTYPE_C_GATE_SetZero,     //12.���Ƶ����趨
		CMDTYPE_C_GATE_SetFlux,     //13.�����趨
		CMDTYPE_C_GATE_SmoothPress, //14.�ֶ�ƽѹ
		CMDTYPE_C_GATE_SetOpening,  //15.��������
		CMDTYPE_C_GATE_SetPos       //16.�߶�����
};


#define  IGC_CMDTYPE_C_TRANS 56//�����ͷ
#define  IGC_CMDTYPE_OPER_C_TRANS_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_TRANS_stop_NUM 5
 

enum IGC_ENUM_CMDTYPE_C_TRANS  {		
	    CMDTYPE_C_TRANS_Reset,      //0. ���ϸ���
		CMDTYPE_C_TRANS_Raise,      //1. ����
		CMDTYPE_C_TRANS_Down,       //2. �½�
		CMDTYPE_C_TRANS_Stop,       //3. ֹͣ����
		CMDTYPE_C_TRANS_RaiseTo,    //4. ������(��ͷλ��)
		CMDTYPE_C_TRANS_DownTo,     //5. �½���(��ͷλ��)	
};


#define  IGC_CMDTYPE_C_VOLT_STEP 60//������ѹ
#define  IGC_CMDTYPE_OPER_C_VOLT_STEP_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_VOLT_STEP_stop_NUM 2
 
enum IGC_ENUM_CMDTYPE_C_VOLT_STEP  {		
    	CMDTYPE_C_VOLT_STEP_Decrease=1,  //1. ������ѹ
		CMDTYPE_C_VOLT_STEP_Increase     //2. ������ѹ
};

#define  IGC_CMDTYPE_C_SPEED_STEP 61//������Ƶ
#define  IGC_CMDTYPE_OPER_C_SPEED_STEP_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_SPEED_STEP_stop_NUM 2
 
enum IGC_ENUM_CMDTYPE_C_SPEED_STEP  {		
	    CMDTYPE_C_SPEED_STEP_Decrease=1,  //1. ������Ƶ
		CMDTYPE_C_SPEED_STEP_Increase     //2. ������Ƶ
};

#define  IGC_CMDTYPE_C_ONOFF_FORCE 62//������ǿ��
#define  IGC_CMDTYPE_OPER_C_ONOFF_FORCE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_ONOFF_FORCE_stop_NUM 2
 

enum IGC_ENUM_CMDTYPE_C_ONOFF_FORCE  {		    
	CMDTYPE_C_ONOFF_FORCE_UnForce,     //0.���ǿ�� 
	CMDTYPE_C_ONOFF_FORCE_ForceOff,    //1.ǿ�÷�
	CMDTYPE_C_ONOFF_FORCE_ForceOn      //2.ǿ�ú�
};



#define  IGC_CMDTYPE_C_ANA_FORCE 63//ģ����ǿ��
#define  IGC_CMDTYPE_OPER_C_ANA_FORCE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_ANA_FORCE_stop_NUM 1
 

enum IGC_ENUM_CMDTYPE_C_ANA_FORCE  {		    
	CMDTYPE_C_ANA_FORCE_UnForce,     //0.���ǿ�� 
	CMDTYPE_C_ANA_FORCE_Force        //1.ǿ��ģ��ֵ
}; 

#define  IGC_CMDTYPE_C_IO_CTRL_BLOCK 64//IO�����˳������ʽ
#define  IGC_CMDTYPE_OPER_C_IO_CTRL_BLOCK_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_IO_CTRL_BLOCK_stop_NUM 1
 

enum IGC_ENUM_CMDTYPE_C_IO_CTRL_BLOCK  {		    
	CMDTYPE_C_IO_CTRL_BLOCK_Ctrl_UnBlock,     //0. IO���ƻָ� 
	CMDTYPE_C_IO_CTRL_BLOCK_Ctrl_Block        //1. IO�����˳�
};


#define  IGC_CMDTYPE_C_DEV_MODE 57//IO�����˳������ʽ
#define  IGC_CMDTYPE_OPER_C_DEV_MODE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_DEV_MODE_stop_NUM 3
 
enum IGC_ENUM_CMDTYPE_C_DEV_MODE  {		    
	CMDTYPE_C_DEV_MODE_Off,     //0. �˳� 
	CMDTYPE_C_DEV_MODE_On,      //1. Ͷ��
	CMDTYPE_C_DEV_MODE_On2,     //2. Ͷ�����з�ʽ2
	CMDTYPE_C_DEV_MODE_On3      //3. Ͷ�����з�ʽ3
};

#define  IGC_CMDTYPE_C_SIGNAL_RESET 83//�źŸ��������ʽ
#define  IGC_CMDTYPE_OPER_C_SIGNAL_RESET_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_SIGNAL_RESET_stop_NUM 2
 

enum IGC_ENUM_CMDTYPE_C_SIGNAL_RESET  {		    
	CMDTYPE_C_SIGNAL_RESET_FaultReset=1,      //1. �¹��źŸ��� 
	CMDTYPE_C_SIGNAL_RESET_FailReset        //2. �����źŸ���
};


#define  IGC_CMDTYPE_C_LCU_ONOFF 48//LCU����/��������
#define  IGC_CMDTYPE_OPER_C_LCU_ONOFF_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_LCU_ONOFF_stop_NUM 2
 

enum IGC_ENUM_CMDTYPE_C_LCU_ONOFF  {		    
	CMDTYPE_C_LCU_ONOFF_Offline=1,      //1. �豸���� 
	CMDTYPE_C_LCU_ONOFF_Online,         //2. �豸����
};

#define  IGC_CMDTYPE_TIME_SYNC 47//LCUʱ��ͬ��
#define  IGC_CMDTYPE_OPER_TIME_SYNC_start_NUM 0
#define  IGC_CMDTYPE_OPER_TIME_SYNC_stop_NUM 0
 

enum IGC_ENUM_CMDTYPE_TIME_SYNC  {		    
	CMDTYPE_TIME_SYNC_TimeSync
};



#define  IGC_CMDTYPE_C_HOST_SYS 69//LCU����/��������
#define  IGC_CMDTYPE_OPER_C_HOST_SYS_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_HOST_SYS_stop_NUM 2
 
enum IGC_ENUM_CMDTYPE_C_HOST_SYS  {		    
	CMDTYPE_C_HOST_SYS_MainHost=1,      //1. ������ϵͳ 
	CMDTYPE_C_HOST_SYS_ViceHost         //2. ������ϵͳ
};


#define  IGC_CMDTYPE_C_PLC_SWITCH 73//PLC˫CPU�л������ʽ
#define  IGC_CMDTYPE_OPER_C_PLC_SWITCH_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_PLC_SWITCH_stop_NUM 2
 
enum IGC_ENUM_CMDTYPE_C_PLC_SWITCH  {		    	
	CMDTYPE_C_PLC_SWITCH_MainCPU=1,       //1. ������ϵͳ 
	CMDTYPE_C_PLC_SWITCH_ViceCPU         //2. ������ϵͳ
};


#define  IGC_CMDTYPE_C_NET_SWITCH 70//�����л������ʽ
#define  IGC_CMDTYPE_OPER_C_NET_SWITCH_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_NET_SWITCH_stop_NUM 4
 
enum IGC_ENUM_CMDTYPE_C_NET_SWITCH  {		    
	
	CMDTYPE_C_NET_SWITCH_NetA=1,       //1. ����A#�� 
	CMDTYPE_C_NET_SWITCH_NetB,         //2. ����B#��
	CMDTYPE_C_NET_SWITCH_NetC,         //2. ����C#��
	CMDTYPE_C_NET_SWITCH_NetD          //3. ����C#��
};


#define  IGC_CMDTYPE_C_OP_VALUE_SET 85//���в������������ʽ
#define  IGC_CMDTYPE_OPER_C_OP_VALUE_SET_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_OP_VALUE_SET_stop_NUM 0
 
enum IGC_ENUM_CMDTYPE_C_OP_VALUE_SET  {		    
	CMDTYPE_C_OP_VALUE_SET_Real_Value          //0.ʵʱֵ 
};


#define  IGC_CMDTYPE_C_SYS_MODE_SET 86//ϵͳ���з�ʽ
#define  IGC_CMDTYPE_OPER_C_SYS_MODE_SET_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_SYS_MODE_SET_stop_NUM 3

enum IGC_ENUM_CMDTYPE_C_SYS_MODE_SET  {		    
	CMDTYPE_C_SYS_MODE_SET_Off,       //0.�˳� 
	CMDTYPE_C_SYS_MODE_SET_On,        //1.Ͷ��
	CMDTYPE_C_SYS_MODE_SET_On2,       //2.Ͷ�뷽ʽ2
	CMDTYPE_C_SYS_MODE_SET_On3        //2.Ͷ�뷽ʽ3
};

#define  IGC_CMDTYPE_C_LCU_PARAM 72//PLC��ֵ��������
#define  IGC_CMDTYPE_OPER_C_LCU_PARAM_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_LCU_PARAM_stop_NUM 1
 
enum IGC_ENUM_CMDTYPE_C_LCU_PARAM  {		    
	CMDTYPE_C_LCU_PARAM_ParamDnLoad=1 //1.�´�LCU����
};


#define  IGC_CMDTYPE_C_DATA_POLLING 71//�����ٻ�����
#define  IGC_CMDTYPE_OPER_C_DATA_POLLING_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_DATA_POLLING_stop_NUM 0
 
enum IGC_ENUM_CMDTYPE_C_DATA_POLLING  {		    
	CMDTYPE_C_DATA_POLLING_DataPolling      //0.�ٻ� 
};


#define  IGC_CMDTYPE_ANA_PARAM_SET 42//ģ����/����ֵ�������������ʽ
#define  IGC_CMDTYPE_OPER_ANA_PARAM_SET_start_NUM 0
#define  IGC_CMDTYPE_OPER_ANA_PARAM_SET_stop_NUM 15
 
enum IGC_ENUM_CMDTYPE_ANA_PARAM_SET  {		    
		CMDTYPE_ANA_PARAM_SET_D_BAND,   //	0	����ֵ			
		CMDTYPE_ANA_PARAM_SET_HH_LMT,   //	1	������ֵ	
		CMDTYPE_ANA_PARAM_SET_H_LMT,    //	2	����ֵ			
		CMDTYPE_ANA_PARAM_SET_L_LMT,    //	3	����ֵ			
		CMDTYPE_ANA_PARAM_SET_LL_LMT,   //	4	������ֵ		
		CMDTYPE_ANA_PARAM_SET_HR_LMT,   //	5	�ϸ�������ֵ		
		CMDTYPE_ANA_PARAM_SET_LR_LMT,   //	6	�¸�������ֵ		
		CMDTYPE_ANA_PARAM_SET_ENG_CVT,  //	7	������ת��ϵ��	
		CMDTYPE_ANA_PARAM_SET_H_RANG,   //	8	������			
		CMDTYPE_ANA_PARAM_SET_L_RANG,   //	9	������			
		CMDTYPE_ANA_PARAM_SET_ZERO,     //	10	���ֵ(��ֵ)		
		CMDTYPE_ANA_PARAM_SET_COMPENS,  //	11	����ֵ			
		CMDTYPE_ANA_PARAM_SET_TR_LMT,   //	12	����Խ��ֵ			
		CMDTYPE_ANA_PARAM_SET_RT_LMT,   //	13	���Ƹ�������ֵ		
		CMDTYPE_ANA_PARAM_SET_H_CODE,   //  14	ԭ��������			
		CMDTYPE_ANA_PARAM_SET_L_CODE,   //	15	ԭ��������	
};


#define  IGC_CMDTYPE_IMP_PARAM_SET 43//������������������
#define  IGC_CMDTYPE_OPER_IMP_PARAM_SET_start_NUM 0
#define  IGC_CMDTYPE_OPER_IMP_PARAM_SET_stop_NUM 24
 
enum IGC_ENUM_CMDTYPE_IMP_PARAM_SET  {		    
		CMDTYPE_IMP_PARAM_SET_IMP_ACCUM,       //(������)	    0	�����ۼ�ֵ    		
		CMDTYPE_IMP_PARAM_SET_D_ACCUM,         //(������)		1	��ȱ����			
		CMDTYPE_IMP_PARAM_SET_D_DAY_PEAK,      //(������)		2	�շ�ֵ			
		CMDTYPE_IMP_PARAM_SET_D_MONTH_PEAK,    //(������)		3	�·�ֵ			
		CMDTYPE_IMP_PARAM_SET_D_YEAR_PEAK,     //(������)		4	���ֵ			
		CMDTYPE_IMP_PARAM_SET_D_DAY_VALLY,     //(������)		5	�չ�ֵ			
		CMDTYPE_IMP_PARAM_SET_D_MONTH_VALLY,   //(������)		6	�¹�ֵ			
		CMDTYPE_IMP_PARAM_SET_D_YEAR_VALLY,    //(������)		7	���ֵ			
		CMDTYPE_IMP_PARAM_SET_D_DAY_AVE,       //(������)		8	��ƽֵ			
		CMDTYPE_IMP_PARAM_SET_D_MONTH_AVE,     //(������)		9	��ƽֵ			
		CMDTYPE_IMP_PARAM_SET_D_YEAR_AVE,      //(������)		10	��ƽֵ			
		CMDTYPE_IMP_PARAM_SET_D_DAY_SUM,       //(������)		11	����ֵ			
		CMDTYPE_IMP_PARAM_SET_D_MONTH_SUM,     //(������)		12	����ֵ			
		CMDTYPE_IMP_PARAM_SET_D_YEAR_SUM,      //(������)		13	����ֵ			
		CMDTYPE_IMP_PARAM_SET_D_DAY_PPEAK,     //(������)	    (V3.0)		14	�ռ��ֵ			
		CMDTYPE_IMP_PARAM_SET_D_MONTH_PPEAK,   //(������)   	(V3.0)		15	�¼��ֵ			
		CMDTYPE_IMP_PARAM_SET_D_YEAR_PPEAK,    //(������)	    (V3.0)		16	����ֵ			
		CMDTYPE_IMP_PARAM_SET_D_DAY_SUM_INI,   //(������)	    (V4.0)		17	���ܳ�ֵ			
		CMDTYPE_IMP_PARAM_SET_D_MONTH_SUM_INI, //(������)   	(V4.0)		18	���ܳ�ֵ			
		CMDTYPE_IMP_PARAM_SET_D_YEAR_SUM_INI,  //(������)	    (V4.0)		19	���ܳ�ֵ			
		CMDTYPE_IMP_PARAM_SET_IMP_ENG_CVT,     //(������)		20	������ת��ϵ��		
		CMDTYPE_IMP_PARAM_SET_PT_CVT,          //(������)		(V4.0)		21	PT���ϵ��			
		CMDTYPE_IMP_PARAM_SET_CT_CVT,          //(������)		(V4.0)		22	CT���ϵ��			
		CMDTYPE_IMP_PARAM_SET_CONSTANT,        //(������)		(V4.0)		23	����������㷭תֵ	
		CMDTYPE_IMP_PARAM_SET_IMP_BASE         //(������)		(V4.0)		24	�����ֵ
};

#define  IGC_CMDTYPE_C_ONOFF_SET 44//��������������ͳ����
#define  IGC_CMDTYPE_OPER_C_ONOFF_SET_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_ONOFF_SET_stop_NUM 4
 
enum IGC_ENUM_CMDTYPE_C_ONOFF_SET  {		    
		CMDTYPE_C_ONOFF_SETNORMAL_OPEN=1, //	1	������բ����		
		CMDTYPE_C_ONOFF_SETNORMAL_CLOSE, //	    2	������բ����				
		CMDTYPE_C_ONOFF_SETFAULT_OPEN,   //		3	�¹ʷ�բ����		
		CMDTYPE_C_ONOFF_SETFAULT_CLOSE   //     4	�¹ʺ�բ����	
};
#endif
