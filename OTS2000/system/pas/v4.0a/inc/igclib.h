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
#else
#include<fcntl.h>
#include<stdio.h>
#include <time.h>
#endif

#include	"../../../dms/v4.0a/inc/syslog.h"
#include	"../../../dms/v4.0a/inc/dms_com.h"
#include	"../../../pas/v4.0a/inc/pdc_def.h"
#include	"../../../dps/v4.0a/inc/ipc_common.h"
#include	"../../../dps/v4.0a/inc/dps_rec_def.h"
#include	"../../../dps/v4.0a/inc/dps_type_def.h"
#include	"../../../lan/v4.0a/inc/lan_common.h"
#include	"../../../sms/v4.0a/inc/user_privilege_def.h"
#include	"../../../dps/v4.0a/inc/fault_table_def.h" 
#include	"../../../oix/v4.0a/inc/alarm_str.h"
#include	"../../../dps/v4.0a/inc/dps_functions_def.h"

#define  IGC_CMDTYPE_C_UNIT 49//��������
#define  IGC_CMDTYPE_OPER_C_UNIT_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_UNIT_stop_NUM 44
char *IGC_CMDTYPE_OPER_C_UNIT[]= {	
	"NULL",         //0
	"Start",        //1.   ����
	"Stop",         //2.   ͣ��
	"Reset",        //3.   �����ֶ�������
	"Step",         //4.   ����������
	"Jump",         //5.   ��ת��
	"NoVoltRun",    //6.   ��ת
	"NoLoadRun",    //7.   ����
	"BlackStart",   //8.   ���������
	"CmpStart",     //9.   ���������
	"EmergStop",    //10.  ����ͣ��
	"Open",         //11.  ����
	"ReadyStart",   //12.  ����׼��
	"TransNoLoad",  //13.  �������(�����ٲ�����)
	"ZeroVRun",     //14.  ������ѹ
	"TranZVRun",    //15.  ������������ѹ
	"ZeroVStop",    //16.  ������ѹת����
	"NULL",         //17.  
	"NULL",         //18.  
	"NULL",         //19.  
	"StartToCool",  //20.  ��������ȴˮ��
	"StartToSpin",  //21.  ��������ת��
	"StartToNLoad", //22.  ������������
	"StartToOnLin", //23.  ������������
	"StopToNLoad",  //24.  ͣ����������
	"StopToSpin",   //25.  ͣ������ת��
	"StopToCool",   //26.  ͣ������ȴˮ��
	"StopToStand",  //27.  ͣ����ȫͣ��
	"StartStep",    //28.  ������������������
	"StopStep",     //29.  ����ͣ������������
	"EmergStep",    //30.  ��������ͣ������������
	"FastStopStep", //31.  ��������ͣ������������
	"PumpStart",    //32.  ����
	"PumpStop",     //33.  ͣ��
	"DragStart",    //34.  ���Ϸ���
	"SFCHSStart",   //35.  ��Ƶ������ת�ٳ�ˮ
	"SFCLSStart",   //36.  ��Ƶ������ת�ٳ�ˮ
	"SFCHSCmp",     //37.  ��Ƶ������ת��ˮ�õ���
	"SFCLSCmp",     //38.  ��Ƶ������ת��ˮ�õ���
	"DragHSStart",  //39.  ����������ת�ٳ�ˮ
	"DragLSStart",  //40.  ����������ת�ٳ�ˮ
	"DragHSCmp",    //41.  ����������ת��ˮ�õ���
	"DragLSCmp",    //42.  ����������ת��ˮ�õ���
	"PumpToGe",     //43.  ��ˮת����
	"GenToPump"    //44.  ����ת��ˮ
};


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
char *IGC_CMDTYPE_OPER_C_BREAKER[]= {	
	"Reset",          //0. ���ϸ���
	"Open",           //1. ��բ
	"Close",          //2. ��բ
	"IM_Line",        //3. Iĸ����·����
	"IIM_Line",       //4. IIĸ����·����
	"Line_IM",        //5. ��·��Iĸ����
	"Line_IIM",       //6. ��·��IIĸ����
	"Tran_IM",        //7. ��ѹ����Iĸ����
	"Tran_IIM",       //8. ��ѹ����IIĸ����
	"IM_Tran",        //9. Iĸ�Ա�ѹ������
	"IIM_Tran",       //10.IIĸ�Ա�ѹ������
	"TestClose",      //11.�����
	"CancelSyn",      //12.ͬ���˳�
	"LoopClose",      //13.������
	"ChgVltCls",      //14.����
	"ZroVltCls"       //15.��ѹ��
};

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
char *IGC_CMDTYPE_OPER_C_SWITCH[]= {	
	    "Reset",        //0. ���ϸ���
		"Open",         //1.  ��բ
		"Close",        //2.  ��բ
		"TestOpen",     //3.  �����բ
		"TestClose"     //4.  �����բ
};

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
char *IGC_CMDTYPE_OPER_C_APOWER[]= {	
	"Power",      //0.  ���ʵ���
	"Openning",   //1.  ���ȵ���
	"Flux"        //2.  ��������
};

enum IGC_ENUM_CMDTYPE_C_APOWER  {	
	    CMDTYPE_C_APOWER_Power,     //0.  ���ʵ���
		CMDTYPE_C_APOWER_Openning,  //1.  ���ȵ���
		CMDTYPE_C_APOWER_Flux       //2.  ��������
};



#define  IGC_CMDTYPE_C_RPOWER 53//�޹�����
#define  IGC_CMDTYPE_OPER_C_RPOWER_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_RPOWER_stop_NUM 2
char *IGC_CMDTYPE_OPER_C_RPOWER[]= {	
	"Power",      //0.  ���ʵ���
	"Volt",       //1.  ��ѹ����
	"Cos"         //2.  ������������
};

enum IGC_ENUM_CMDTYPE_C_RPOWER  {	
	    CMDTYPE_C_RPOWER_Power,      //0.  ���ʵ���
		CMDTYPE_C_RPOWER_Volt,       //1.  ��ѹ����
		CMDTYPE_C_RPOWER_Cos         //2.  ������������	
};


#define  IGC_CMDTYPE_C_DEVICE 54//һ���豸
#define  IGC_CMDTYPE_OPER_C_DEVICE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_DEVICE_stop_NUM 2
char *IGC_CMDTYPE_OPER_C_DEVICE[]= {	
	"Reset",       //0. ���ϸ���
	"Off",         //1. �豸�˳�
	"On"           //2. �豸Ͷ��
};

enum IGC_ENUM_CMDTYPE_C_DEVICE  {	
    	CMDTYPE_C_DEVICE_Reset,       //0. ���ϸ���
		CMDTYPE_C_DEVICE_Off,         //1. �豸�˳�
		CMDTYPE_C_DEVICE_On           //2. �豸Ͷ��		
};

#define  IGC_CMDTYPE_C_GATE 55//բ��
#define  IGC_CMDTYPE_OPER_C_GATE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_GATE_stop_NUM 16
char *IGC_CMDTYPE_OPER_C_GATE[]= {	
	"Reset",       //0. ���ϸ���
	"Open",        //1. ��բ��
	"Close",       //2. ��բ��
	"Stop",        //3. ֹͣ����
	"Up",          //4. ����(�߶�)
	"Down",        //5. �½�(�߶�)
	"FastOpen",    //6. ���ٿ�բ��
	"FastClose",   //7. ���ٹ�բ��
	"StepUp",      //8. ��������(�̶��߶�)
	"StepDown",    //9. �����½�(�̶��߶�)
	"Forward",     //10.ǰ��
	"Backward",    //11.��
	"SetZero",     //12.���Ƶ����趨
	"SetFlux",     //13.�����趨
	"SmoothPress", //14.�ֶ�ƽѹ
	"SetOpening",  //15.��������
	"SetPos"       //16.�߶�����
};

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
char *IGC_CMDTYPE_OPER_C_TRANS[]= {	
	"Reset",      //0. ���ϸ���
	"Raise",      //1. ����
	"Down",       //2. �½�
	"Stop",       //3. ֹͣ����
	"RaiseTo",    //4. ������(��ͷλ��)
	"DownTo",     //5. �½���(��ͷλ��)
};

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
char *IGC_CMDTYPE_OPER_C_VOLT_STEP[]= {	
	"NULL",      //0. 
	"Decrease",  //1. ������ѹ
	"Increase",  //2. ������ѹ
};
enum IGC_ENUM_CMDTYPE_C_VOLT_STEP  {		
    	CMDTYPE_C_VOLT_STEP_Decrease=1,  //1. ������ѹ
		CMDTYPE_C_VOLT_STEP_Increase     //2. ������ѹ
};

#define  IGC_CMDTYPE_C_SPEED_STEP 61//������Ƶ
#define  IGC_CMDTYPE_OPER_C_SPEED_STEP_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_SPEED_STEP_stop_NUM 2
char *IGC_CMDTYPE_OPER_C_SPEED_STEP[]= {	
	"NULL",      //0. 
	"Decrease",  //1. ������Ƶ
	"Increase"   //2. ������Ƶ
};

enum IGC_ENUM_CMDTYPE_C_SPEED_STEP  {		
	    CMDTYPE_C_SPEED_STEP_Decrease=1,  //1. ������Ƶ
		CMDTYPE_C_SPEED_STEP_Increase     //2. ������Ƶ
};

#define  IGC_CMDTYPE_C_ONOFF_FORCE 62//������ǿ��
#define  IGC_CMDTYPE_OPER_C_ONOFF_FORCE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_ONOFF_FORCE_stop_NUM 2
char *IGC_CMDTYPE_OPER_C_ONOFF_FORCE[]= {	
    "UnForce",     //0.���ǿ�� 
	"ForceOff",    //1.ǿ�÷�
	"ForceOn"      //2.ǿ�ú�
};

enum IGC_ENUM_CMDTYPE_C_ONOFF_FORCE  {		    
	CMDTYPE_C_ONOFF_FORCE_UnForce,     //0.���ǿ�� 
	CMDTYPE_C_ONOFF_FORCE_ForceOff,    //1.ǿ�÷�
	CMDTYPE_C_ONOFF_FORCE_ForceOn      //2.ǿ�ú�
};



#define  IGC_CMDTYPE_C_ANA_FORCE 63//ģ����ǿ��
#define  IGC_CMDTYPE_OPER_C_ANA_FORCE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_ANA_FORCE_stop_NUM 1
char *IGC_CMDTYPE_OPER_C_ANA_FORCE[]= {	
    "UnForce",     //0.���ǿ�� 
	"Force"        //1.ǿ��ģ��ֵ
};

enum IGC_ENUM_CMDTYPE_C_ANA_FORCE  {		    
	CMDTYPE_C_ANA_FORCE_UnForce,     //0.���ǿ�� 
	CMDTYPE_C_ANA_FORCE_Force        //1.ǿ��ģ��ֵ
}; 

#define  IGC_CMDTYPE_C_IO_CTRL_BLOCK 64//IO�����˳������ʽ
#define  IGC_CMDTYPE_OPER_C_IO_CTRL_BLOCK_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_IO_CTRL_BLOCK_stop_NUM 1
char *IGC_CMDTYPE_OPER_C_IO_CTRL_BLOCK[]= {	
    "Ctrl_UnBlock",     //0. IO���ƻָ� 
	"Ctrl_Block"        //1. IO�����˳�
};

enum IGC_ENUM_CMDTYPE_C_IO_CTRL_BLOCK  {		    
	CMDTYPE_C_IO_CTRL_BLOCK_Ctrl_UnBlock,     //0. IO���ƻָ� 
	CMDTYPE_C_IO_CTRL_BLOCK_Ctrl_Block        //1. IO�����˳�
};


#define  IGC_CMDTYPE_C_DEV_MODE 57//IO�����˳������ʽ
#define  IGC_CMDTYPE_OPER_C_DEV_MODE_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_DEV_MODE_stop_NUM 3
char *IGC_CMDTYPE_OPER_C_DEV_MODE[]= {	
    "Off",       //0. �˳� 
	"On",        //1. Ͷ��
	"On2",       //2. Ͷ�����з�ʽ2
	"On3"        //3. Ͷ�����з�ʽ3
};
enum IGC_ENUM_CMDTYPE_C_DEV_MODE  {		    
	CMDTYPE_C_DEV_MODE_Off,     //0. �˳� 
	CMDTYPE_C_DEV_MODE_On,      //1. Ͷ��
	CMDTYPE_C_DEV_MODE_On2,     //2. Ͷ�����з�ʽ2
	CMDTYPE_C_DEV_MODE_On3      //3. Ͷ�����з�ʽ3
};

#define  IGC_CMDTYPE_C_SIGNAL_RESET 83//�źŸ��������ʽ
#define  IGC_CMDTYPE_OPER_C_SIGNAL_RESET_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_SIGNAL_RESET_stop_NUM 2
char *IGC_CMDTYPE_OPER_C_SIGNAL_RESET[]= {	
	"NULL",            //0. 
    "FaultReset",      //1. �¹��źŸ��� 
	"FailReset"        //2. �����źŸ���
};

enum IGC_ENUM_CMDTYPE_C_SIGNAL_RESET  {		    
	CMDTYPE_C_SIGNAL_RESET_FaultReset=1,      //1. �¹��źŸ��� 
	CMDTYPE_C_SIGNAL_RESET_FailReset        //2. �����źŸ���
};


#define  IGC_CMDTYPE_C_LCU_ONOFF 48//LCU����/��������
#define  IGC_CMDTYPE_OPER_C_LCU_ONOFF_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_LCU_ONOFF_stop_NUM 2
char *IGC_CMDTYPE_OPER_C_LCU_ONOFF[]= {	
	"NULL",         //0. 
    "Offline",      //1. �豸���� 
	"Online"        //2. �豸����
};

enum IGC_ENUM_CMDTYPE_C_LCU_ONOFF  {		    
	CMDTYPE_C_LCU_ONOFF_Offline=1,      //1. �豸���� 
	CMDTYPE_C_LCU_ONOFF_Online,         //2. �豸����
};

#define  IGC_CMDTYPE_TIME_SYNC 47//LCUʱ��ͬ��
#define  IGC_CMDTYPE_OPER_TIME_SYNC_start_NUM 0
#define  IGC_CMDTYPE_OPER_TIME_SYNC_stop_NUM 0
char *IGC_CMDTYPE_OPER_TIME_SYNC[]= {	
    "TimeSync"      //0. ͬ�� 
};

enum IGC_ENUM_CMDTYPE_TIME_SYNC  {		    
	CMDTYPE_TIME_SYNC_TimeSync
};



#define  IGC_CMDTYPE_C_HOST_SYS 69//LCU����/��������
#define  IGC_CMDTYPE_OPER_C_HOST_SYS_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_HOST_SYS_stop_NUM 2
char *IGC_CMDTYPE_OPER_C_HOST_SYS[]= {	
 	"NULL",          //0. 
	"MainHost",      //1. ������ϵͳ 
	"ViceHost"       //2. ������ϵͳ
};
enum IGC_ENUM_CMDTYPE_C_HOST_SYS  {		    
	CMDTYPE_C_HOST_SYS_MainHost=1,      //1. ������ϵͳ 
	CMDTYPE_C_HOST_SYS_ViceHost         //2. ������ϵͳ
};


#define  IGC_CMDTYPE_C_PLC_SWITCH 73//PLC˫CPU�л������ʽ
#define  IGC_CMDTYPE_OPER_C_PLC_SWITCH_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_PLC_SWITCH_stop_NUM 2
char *IGC_CMDTYPE_OPER_C_PLC_SWITCH[]= {	
	"NULL",           //0. 
    "MainCPU",        //1. ������ϵͳ 
	"ViceCPU"         //2. ������ϵͳ
};
enum IGC_ENUM_CMDTYPE_C_PLC_SWITCH  {		    	
	CMDTYPE_C_PLC_SWITCH_MainCPU=1,       //1. ������ϵͳ 
	CMDTYPE_C_PLC_SWITCH_ViceCPU         //2. ������ϵͳ
};


#define  IGC_CMDTYPE_C_NET_SWITCH 70//�����л������ʽ
#define  IGC_CMDTYPE_OPER_C_NET_SWITCH_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_NET_SWITCH_stop_NUM 4
char *IGC_CMDTYPE_OPER_C_NET_SWITCH[]= {	
	"NULL",        //0. 
	"NetA",        //1. ����A#�� 
	"NetB",        //2. ����B#��
	"NetC",        //2. ����C#��
	"NetD"         //3. ����C#��
};
enum IGC_ENUM_CMDTYPE_C_NET_SWITCH  {		    
	
	CMDTYPE_C_NET_SWITCH_NetA=1,       //1. ����A#�� 
	CMDTYPE_C_NET_SWITCH_NetB,         //2. ����B#��
	CMDTYPE_C_NET_SWITCH_NetC,         //2. ����C#��
	CMDTYPE_C_NET_SWITCH_NetD          //3. ����C#��
};


#define  IGC_CMDTYPE_C_OP_VALUE_SET 85//���в������������ʽ
#define  IGC_CMDTYPE_OPER_C_OP_VALUE_SET_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_OP_VALUE_SET_stop_NUM 0
char *IGC_CMDTYPE_OPER_C_OP_VALUE_SET[]= {	
	"Real_Value"           //0.ʵʱֵ 
};
enum IGC_ENUM_CMDTYPE_C_OP_VALUE_SET  {		    
	CMDTYPE_C_OP_VALUE_SET_Real_Value          //0.ʵʱֵ 
};


#define  IGC_CMDTYPE_C_SYS_MODE_SET 86//ϵͳ���з�ʽ
#define  IGC_CMDTYPE_OPER_C_SYS_MODE_SET_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_SYS_MODE_SET_stop_NUM 3
char *IGC_CMDTYPE_OPER_C_SYS_MODE_SET[]= {	
	"Off",       //0.�˳� 
	"On",        //1.Ͷ��
	"On2",       //2.Ͷ�뷽ʽ2
	"On3"        //2.Ͷ�뷽ʽ3
};
enum IGC_ENUM_CMDTYPE_C_SYS_MODE_SET  {		    
	CMDTYPE_C_SYS_MODE_SET_Off,       //0.�˳� 
	CMDTYPE_C_SYS_MODE_SET_On,        //1.Ͷ��
	CMDTYPE_C_SYS_MODE_SET_On2,       //2.Ͷ�뷽ʽ2
	CMDTYPE_C_SYS_MODE_SET_On3        //2.Ͷ�뷽ʽ3
};

#define  IGC_CMDTYPE_C_LCU_PARAM 72//PLC��ֵ��������
#define  IGC_CMDTYPE_OPER_C_LCU_PARAM_start_NUM 1
#define  IGC_CMDTYPE_OPER_C_LCU_PARAM_stop_NUM 1
char *IGC_CMDTYPE_OPER_C_LCU_PARAM[]= {	
	"NULL",       //0.�˳� 
	"ParamDnLoad",//1.�´�LCU����
};
enum IGC_ENUM_CMDTYPE_C_LCU_PARAM  {		    
	CMDTYPE_C_LCU_PARAM_ParamDnLoad=1 //1.�´�LCU����
};


#define  IGC_CMDTYPE_C_DATA_POLLING 71//�����ٻ�����
#define  IGC_CMDTYPE_OPER_C_DATA_POLLING_start_NUM 0
#define  IGC_CMDTYPE_OPER_C_DATA_POLLING_stop_NUM 0
char *IGC_CMDTYPE_OPER_C_DATA_POLLING[]= {	
	"DataPolling"      //0.�ٻ� 
};
enum IGC_ENUM_CMDTYPE_C_DATA_POLLING  {		    
	CMDTYPE_C_DATA_POLLING_DataPolling      //0.�ٻ� 
};


#define  IGC_CMDTYPE_ANA_PARAM_SET 42//ģ����/����ֵ�������������ʽ
#define  IGC_CMDTYPE_OPER_ANA_PARAM_SET_start_NUM 0
#define  IGC_CMDTYPE_OPER_ANA_PARAM_SET_stop_NUM 15
char *IGC_CMDTYPE_OPER_ANA_PARAM_SET[]= {	
	    "D_BAND",  //	0	����ֵ			
		"HH_LMT",  //	1	������ֵ	
		"H_LMT",   //	2	����ֵ			
		"L_LMT",   //	3	����ֵ			
		"LL_LMT",  //	4	������ֵ		
		"HR_LMT",  //	5	�ϸ�������ֵ		
		"LR_LMT",  //	6	�¸�������ֵ		
		"ENG_CVT", //	7	������ת��ϵ��	
		"H_RANG",  //	8	������			
		"L_RANG",  //	9	������			
		"ZERO",    //  10	���ֵ(��ֵ)		
		"COMPENS", //  11	����ֵ			
		"TR_LMT",  //  12	����Խ��ֵ			
		"RT_LMT",  //  13	���Ƹ�������ֵ		
		"H_CODE",  //  14	ԭ��������			
		"L_CODE"   //  15	ԭ��������			
};
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
char *IGC_CMDTYPE_OPER_IMP_PARAM_SET[]= {	
    	"IMP_ACCUM",       //(������)	    0	�����ۼ�ֵ    		
		"D_ACCUM",         //(������)		1	��ȱ����			
		"D_DAY_PEAK",      //(������)		2	�շ�ֵ			
		"D_MONTH_PEAK",    //(������)		3	�·�ֵ			
		"D_YEAR_PEAK",     //(������)		4	���ֵ			
		"D_DAY_VALLY",     //(������)		5	�չ�ֵ			
		"D_MONTH_VALLY",   //(������)		6	�¹�ֵ			
		"D_YEAR_VALLY",    //(������)		7	���ֵ			
		"D_DAY_AVE",       //(������)		8	��ƽֵ			
		"D_MONTH_AVE",     //(������)		9	��ƽֵ			
		"D_YEAR_AVE",      //(������)		10	��ƽֵ			
		"D_DAY_SUM",       //(������)		11	����ֵ			
		"D_MONTH_SUM",     //(������)		12	����ֵ			
		"D_YEAR_SUM",      //(������)		13	����ֵ			
		"D_DAY_PPEAK",     //(������)	    (V3.0)		14	�ռ��ֵ			
		"D_MONTH_PPEAK",   //(������)   	(V3.0)		15	�¼��ֵ			
		"D_YEAR_PPEAK",    //(������)	    (V3.0)		16	����ֵ			
		"D_DAY_SUM_INI",   //(������)	    (V4.0)		17	���ܳ�ֵ			
		"D_MONTH_SUM_INI", //(������)   	(V4.0)		18	���ܳ�ֵ			
		"D_YEAR_SUM_INI",  //(������)	    (V4.0)		19	���ܳ�ֵ			
		"IMP_ENG_CVT",     //(������)		20	������ת��ϵ��		
		"PT_CVT",          //(������)		(V4.0)		21	PT���ϵ��			
		"CT_CVT",          //(������)		(V4.0)		22	CT���ϵ��			
		"CONSTANT",        //(������)		(V4.0)		23	����������㷭תֵ	
		"IMP_BASE"         //(������)		(V4.0)		24	�����ֵ			
};
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
char *IGC_CMDTYPE_OPER_C_ONOFF_SET[]= {	
    	"NULL"
		"NORMAL_OPEN", //	    1	������բ����		
		"NORMAL CLOSE",//	    2	������բ����				
		"FAULT OPEN",  //		3	�¹ʷ�բ����		
		"FAULT CLOSE", // 		4	�¹ʺ�բ����				
};
enum IGC_ENUM_CMDTYPE_C_ONOFF_SET  {		    
		CMDTYPE_C_ONOFF_SETNORMAL_OPEN=1, //	1	������բ����		
		CMDTYPE_C_ONOFF_SETNORMAL_CLOSE, //	    2	������բ����				
		CMDTYPE_C_ONOFF_SETFAULT_OPEN,   //		3	�¹ʷ�բ����		
		CMDTYPE_C_ONOFF_SETFAULT_CLOSE   //     4	�¹ʺ�բ����	
};


typedef struct
{	
	int second;     /* seconds after the minute - [0,59] */
	int minute;     /* minutes after the hour - [0,59] */
	int hour;       /* hours since midnight - [0,23] */
	int day;        /* day of the month - [1,31] */
	int month;      /* months since January - [1,12] */
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


typedef struct
{
	int     ok_flag;
	char	sn_str[12];
	char	time_str[64];
	char	repeatAlm[12];
	char	logicname[52];
	char	longname[112];
	char	state_str[128];
//	char	cmd_src[64];
//	char	cmd_result[64];
	char	hostname[10];
	char	usrname[8];
	char	message[256];
	IGC_datetime igc_datetime;
} H9000_IGC_alarm_record;

extern PRIVILEGE_DB		privilege_db;
extern int LoadUserPrivilegeDatabase( );
char igc_cmd_control_point[128][POINT_NAME_SIZE+12];
 
char igc_user_login_name[20];
SHM_RECORD	 *shm_rec_addr;
FAULT_RECORD_TABLE *shm_fault_addr;
int  if_point_is_Doublept_By_pointid(unsigned short stnid,unsigned short devid,unsigned short datatype_id,unsigned short ptid);
int set_pt_to_doublePt_by_pointid(unsigned short stnid,unsigned short devid,unsigned short datatype_id,unsigned short ptid,unsigned short stnid_P,unsigned short devid_P,unsigned short datatype_id_P,unsigned short ptid_P,int isdoublept);
int  get_iogroup_by_pointid(unsigned short stnid,unsigned short devid,unsigned short datatype_id,unsigned short ptid);


int IGC_SEND_H9000_SMG(char * smg);

int  igc_InitStrTextDefine();

H9000_IGC_alarm_record igc_search_one_record_by_logicalname(char * logicalname,int Forward_num,int Forward_index);
H9000_IGC_alarm_record igc_usetime_search_one_record_by_logicalname(char * logicalname,int Forward_num,int Forward_index,IGC_datetime start_time);
H9000_IGC_alarm_record igc_search_one_alarm_by_logicalname(char * logicalname,int Forward_num);

 

int IGC_GetCurentHostCtrlPrvg(int Itype);
int igc_GetPointIdFromRec(REC_ENTRY_UNION *rec, POINTER *pt, int *alm_type);
int trans_cmdtype_to_priv(int cmdtype);

int IGC_Init_RECORD_IPC();
int igc_userlogin(char * user,char * pass);
int igc_userunlogin();
int  set_igc_cmd_control_point(int cmd_type,char * logicalname);
int  clear_igc_cmd_control_point(int cmd_type);
int igc_SendCmd(int cmdtype,int operate_type,int sim_cmd,char * logicalname,float setvalue,char * interlockname_user);

int   igc_WSAStartup();
int   igc_lan_out_init();
//void  igc_SetModuleName(char *module);
int   igc_SetErrLogMode(int argc, char *argv[]);
//void  igc_CreateLockFile(char *filename );
void  igc_Err_log( char *info_buf );

int  igc_Judge_interlock();
int  igc_MountDB();
int  igc_UnMountDB();
int  igc_InterLockFileLoad();
void igc_InterLockFree();
int  get_CLK_TCK();
void sleep_second_igclib(int second);
void sleep_minisecond_igclib(int minisecond);
IGC_datetime get_lacal_datetime_now();
IGC_datetime get_datetime_by_time_t(time_t ltime);

long total_time_seconds(IGC_datetime start_time,IGC_datetime end_time);

H9000_IGC_data get_data_value_by_logicalname(char * logicalname);
H9000_IGC_data get_data_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int POINT_ID);
void get_data_value_by_pointid_IN(POINTER point,H9000_IGC_data * R_data);

H9000_IGC_CHARA_data  get_chara_data_value_by_logicalname(char * logicalname);
H9000_IGC_CHARA_data get_chara_data_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int POINT_ID);
void get_chara_data_value_by_pointid_IN(POINTER point,H9000_IGC_CHARA_data * R_data);

 
H9000_IGC_IND_data get_ind_data_value_by_logicalname(char * logicalname);
H9000_IGC_IND_data get_ind_data_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int POINT_ID);
void get_ind_data_value_by_pointid_IN(POINTER point,H9000_IGC_IND_data * R_data);

 
H9000_IGC_ANA_data get_ana_data_value_by_logicalname(char * logicalname);
H9000_IGC_ANA_data get_ana_data_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int POINT_ID);
void get_ana_data_value_by_pointid_IN(POINTER point,H9000_IGC_ANA_data * R_data);

 
void MultiPointPack_set_ind(unsigned char type_id,unsigned char stn,unsigned char dev,unsigned char type,unsigned short first,unsigned short end,unsigned short status,int data,int smsfalg);

void MultiPointPack_ALM(unsigned char typeid,unsigned char stn,unsigned char dev,unsigned char type,unsigned short first,unsigned short end,unsigned short status,int data,int almfag,int smsfalg);
int ind_alm_by_logicalname(char * logicalname,int alm_status,int stand_by,int MAN_SET,int CHAN_FAIL,int alarm_type,int sendsms_falg);
int ana_alm_by_logicalname(char * logicalname,float set_value,int alm_status,int trend_alarm_status,int data_overflow,int CHAN_FAIL,int alarm_type,int sendsms_falg);//status (0.���� 1.Խ������ 2.Խ���� 3.Խ���� 4.Խ������ 5.������ 6.������ 7.�������� 8.��������....)
int ind_alm_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,
					   int alm_status,int stand_by,int MAN_SET,int CHAN_FAIL,int alarm_type,unsigned int START_POINT_ID,unsigned int END_POINT_ID,int sendsms_falg);
int ana_alm_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,
					   float set_value,int alm_status,int trend_alarm_status,int data_overflow,int CHAN_FAIL,int alarm_type,unsigned int START_POINT_ID,unsigned int END_POINT_ID,int sendsms_falg);

int set_ind_value_by_logicalname(char * logicalname,int set_value,int stand_by,int MAN_SET,int CHAN_FAIL,int sendsms_falg);
int set_ana_value_by_logicalname(char * logicalname,float set_value,int stand_by,int MAN_SET,int CHAN_FAIL,int data_overflow,int sendsms_falg);
int set_int_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int START_POINT_ID,unsigned int END_POINT_ID,
							 int set_value,int stand_by,int MAN_SET,int CHAN_FAIL,int sendsms_falg);
int set_ana_value_by_pointid(unsigned int station_ID,unsigned int  DEVICE_ID,unsigned int  TTPE_ID,unsigned int START_POINT_ID,unsigned int END_POINT_ID,
							 float set_value,int stand_by,int MAN_SET,int CHAN_FAIL,int data_overflow,int sendsms_falg);


