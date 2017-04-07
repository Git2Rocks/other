#ifdef WindowsOS
	include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <math.h>
	#include <time.h>
	#include <signal.h>
	#include <sys/types.h>
	#include <fcntl.h>
#endif
#ifdef SUNOS
	#include	<unistd.h>
	#include	<sys/mman.h>
	#include	<fcntl.h>
	#include	<stdio.h>
	#include	<errno.h>
	#include	<signal.h>
	#include	<sys/types.h>
	#include	<sys/ipc.h>
	#include	<sys/shm.h>
	#include	<sys/time.h>
	#include  <math.h>
#endif

#include	"../../../dms/v4.0a/inc/dms_com.h"
#include	"../../../dps/v4.0a/inc/dps_type_def.h"
#include	"../../../dps/v4.0a/inc/dps_rec_def.h"
#include	"../../../lan/v4.0a/inc/lan_common.h"
#include    "../../../agc/v4.0a/inc/agc.h"
#include    "../../../cmd/v4.0a/inc/cmd_def.h"
#include    "../../../dms/v4.0a/inc/dms_std.h"
#include    "../../../dms/v4.0a/inc/dms_structure_def.h"
#include    "../../../dms/v4.0a/inc/os_type_def.h"


int Number_ANA=0;
ANA_MSG	ml_buf_ANA[64];
LAN_HEAD	lanhd_ANA,lanhd_IND;
int Number_IND=0;
SYS_MSG	ml_buf_IND[64];
char    hostname[20];
char	yf_flag,set_p_flag,iec_flag,NoAGCUnit_flag,unit_status_flag[MAX_UNIT_NUMB+1];
float	old_waterlevel;

extern void CreateLockFile(char *);
extern int LocateKeyword( FILE *, char *);
extern int BdSms(char* sms);
extern int BroadCastSms(char* message, BOOL IsAlm);
/*added from v3.0*/
void UnMount_handle ()
{
    UnMountDB();
    printf ("AGC exit!(Ctrl_c or kill -2 pid)\n");
    lan_finish(0);
    exit (0);
}

void SIGINT_handler (int signal_handler)
{
#ifdef DEBUG
	 printf ( "\nSIGVAL=%d", signal_handler);
#endif
	 UnMountDB();
    lan_finish(0);
    exit (0);
}

void ReadTime ()/*��ʵʱʱ��*/
{
	time_t          shjian;	
	time ( &shjian );
	ntime = localtime ( &shjian );
}

void    WriteLogFile (char logtxt[])
{
	FILE *fp;
	
    fp = fopen(logfilename, "a");
    if ( fp != NULL)
    {
        fwrite( logtxt, strlen( logtxt ),1,fp);
        fclose(fp);
     }
	fclose(fp);
}


/*����Ϊh9000 v4.0 ��д�����*/
int GetControlState()
{
	USHORT state;
	GetHostState(hostname,&state);
	return state;
}

int Compare_SYS_MSG(SYS_MSG Ind1,SYS_MSG Ind2)
{
    if((Ind1.type_id==Ind2.type_id)&&(Ind1.stn_id==Ind2.stn_id)
        &&(Ind1.dev_id==Ind2.dev_id)&&(Ind1.data_type==Ind2.data_type)
        &&(Ind1.number==Ind2.number)&&(Ind1.point_id==Ind2.point_id)
        &&(Ind1.status==Ind2.status)&&(Ind1.host_id==Ind2.host_id))
    	  return 0;
     else
     	  return 1;
}

float ReadDB_ANA(char *PointName)
{
	float ReturnValue;
	char err_str[80]="";
	DMS_COMMON common_aa;
	if(ReadEntryByNameStr(PointName,&common_aa)==-1)
	{
		sprintf(err_str,"No this point %s\n",PointName);
		Err_log(err_str);
		return(DATA_ERR);
	}
	/*if(common_aa.var.anlg.value.status.chan_fail==1)
	return(DATA_BAD);
    stat= common_aa.var.anlg.value.status.lmt_state;
    if (stat==ANA_ALM_HI_ALARM||stat==ANA_ALM_HI_WARN)
      return(OVER_HIGH_LMT);*/

	ReturnValue=common_aa.var.anlg.fValue;
	return(ReturnValue);
}

int ReadDB_Chan(char *PointName)
{
	DMS_COMMON common_aa;
	int ReturnValue,EntryType;
	char err_str[80]="";
	if(ReadEntryByNameStr(PointName,&common_aa)==-1)
	{
		sprintf(err_str,"No this point %s\n",PointName);
		Err_log(err_str);
		return(DATA_ERR);
	}
	EntryType=common_aa.point.data_type;
	if(EntryType==ANA_TYPE)
		ReturnValue=common_aa.var.anlg.value.status.chan_fail;
	else if((EntryType==SOE_TYPE)||(EntryType==POL_TYPE))
		ReturnValue=common_aa.var.ind.status.chan_fail;
	return(ReturnValue);
}

int ReadDB_IND(char *PointName)
{
	int ReturnValue;
	char err_str[80]="";
	DMS_COMMON common_aa;
	if(ReadEntryByNameStr(PointName,&common_aa)==-1)
	{
		sprintf(err_str,"No this point %s\n",PointName);
		Err_log(err_str);
		return(DATA_ERR);
	}
	ReturnValue=common_aa.var.ind.status.state;
	return(ReturnValue);
}

int AGC_UpdateRTDB_ANA (char *PointName,float data)
{
	 DMS_COMMON common_aa;
	 char err_str[80]="";
	time_t  tim;
	struct tm   tmpt;
	int value;
	float OldValue=0;
	if(GetControlState()!=1) return(0);	//����վ���㲥��added by fengxun,2009-05-07
	value=(int)(data*1000);
	if (ReadEntryByNameStr(PointName,&common_aa)==-1)
	{
	  sprintf(err_str,"No this point %s\n",PointName);
	  Err_log(err_str);
		  return(-1);
	 }
	
	OldValue=common_aa.var.anlg.fValue; 	
	if(fabs(OldValue-data)<0.001)
		return 0;	
	
	ml_buf_ANA[Number_ANA].type_id =DPS_ANALOG;
	ml_buf_ANA[Number_ANA].stn_id =common_aa.point.stn_id;
	ml_buf_ANA[Number_ANA].dev_id =common_aa.point.dev_id;
	ml_buf_ANA[Number_ANA].data_type=common_aa.point.data_type;
	ml_buf_ANA[Number_ANA].number=1;
	ml_buf_ANA[Number_ANA].point_id = common_aa.point.pt_id;

	ml_buf_ANA[Number_ANA].status=0;
	memcpy(ml_buf_ANA[Number_ANA].data,&value,4);
	GetLocalHostId(&ml_buf_ANA[Number_ANA].host_id);

	tim=time (NULL);
	tmpt=*localtime (&tim);
	ml_buf_ANA[Number_ANA].sec=tmpt.tm_sec;
	ml_buf_ANA[Number_ANA].min=tmpt.tm_min;
	ml_buf_ANA[Number_ANA].hour=tmpt.tm_hour;
	ml_buf_ANA[Number_ANA].day=tmpt.tm_mday;
	ml_buf_ANA[Number_ANA].month=tmpt.tm_mon+1;
	ml_buf_ANA[Number_ANA].year=tmpt.tm_year+1900;
	
   
#ifdef SUNOS
	Swap2Byte(&ml_buf_ANA[Number_ANA].point_id);
	Swap2Byte(&ml_buf_ANA[Number_ANA].status);
	Swap2Byte(&ml_buf_ANA[Number_ANA].number);
	Swap4Byte(&ml_buf_ANA[Number_ANA].data);
	Swap2Byte(&ml_buf_ANA[Number_ANA].year);
#endif

	Number_ANA+=1;
	lanhd_ANA.length=ANAMSG_SIZE*Number_ANA;
#ifdef SUNOS
	Swap2Byte(&lanhd_ANA.length);
#endif
	
	lanhd_ANA.dp_type=BJ_DB_TIME;
	lanhd_ANA.dest_id =0;
	GetLocalHostId(&lanhd_ANA.src_id);
	lanhd_ANA.dest_stn =ml_buf_ANA[0].stn_id;
	lanhd_ANA.packet_num =0; 
	if(Number_ANA>=4)
	{
		if(GetControlState()==1)
		   lan_out ((char *)&ml_buf_ANA,lanhd_ANA,(unsigned char)0); 
		Number_ANA=0; 
	}
	return 0;
}

int AGC_UpdateRTDB_IND (char *PointName,short data)
{
	DMS_COMMON common_aa; 
	char err_str[80]="";
	time_t  tim;
	struct tm   tmpt;
	int OldValue,i,Two_Identical;
	Two_Identical=0;
	if(GetControlState()!=1) return(0);	//����վ���㲥��added by fengxun,2009-05-07
	if (ReadEntryByNameStr(PointName,&common_aa)==-1)
	{
		sprintf(err_str,"No this point %s\n",PointName);
		Err_log(err_str);
		return(-1);
	}
	
	OldValue=common_aa.var.ind.status.state;  
	if(OldValue==data)
		return  0;

	ml_buf_IND[Number_IND].type_id =DPS_IND_ALM;
	ml_buf_IND[Number_IND].stn_id =common_aa.point.stn_id;
	ml_buf_IND[Number_IND].dev_id =common_aa.point.dev_id;
	ml_buf_IND[Number_IND].data_type=common_aa.point.data_type;
	ml_buf_IND[Number_IND].number=1;
	ml_buf_IND[Number_IND].point_id = common_aa.point.pt_id;

	ml_buf_IND[Number_IND].status=data+256;

	GetLocalHostId(&ml_buf_IND[Number_IND].host_id);
	tim=time (NULL);
	tmpt=*localtime (&tim);
	ml_buf_IND[Number_IND].sec=tmpt.tm_sec; 
	ml_buf_IND[Number_IND].min=tmpt.tm_min;
	ml_buf_IND[Number_IND].hour=tmpt.tm_hour;
	ml_buf_IND[Number_IND].day=tmpt.tm_mday;
	ml_buf_IND[Number_IND].month=tmpt.tm_mon+1;
	ml_buf_IND[Number_IND].year=tmpt.tm_year+1900;
	lanhd_IND.length=SYSMSG_SIZE*(Number_IND+1);

#ifdef SUNOS
	Swap2Byte(&ml_buf_IND[Number_IND].point_id);
	Swap2Byte(&ml_buf_IND[Number_IND].number);
	Swap2Byte(&ml_buf_IND[Number_IND].status);
	Swap2Byte(&ml_buf_IND[Number_IND].year);
	Swap2Byte(&lanhd_IND.length);
#endif

	lanhd_IND.dp_type=BJ_DB_TIME;
	lanhd_IND.dest_id =0;
	GetLocalHostId(&lanhd_IND.src_id);
	lanhd_IND.dest_stn =ml_buf_IND[0].stn_id;
	lanhd_IND.packet_num =0;
    
	for(i=0;i<Number_IND;i++)
	{
		if(Compare_SYS_MSG(ml_buf_IND[Number_IND],ml_buf_IND[i])==0)
		{
			Two_Identical=1;
			break;
		}		
	}
	if(Two_Identical==1)
	{
		lanhd_IND.length=SYSMSG_SIZE*(Number_IND);
#ifdef SUNOS
		Swap2Byte(&lanhd_IND.length);
#endif
	}
	else
	{
		Number_IND+=1;
	} 
    
	if(Number_IND>=4)
	{
		if(GetControlState()==1)
		lan_out ((char *)&ml_buf_IND,lanhd_IND,(unsigned char)0);
		Number_IND=0;
	}
	return 0;
}

float ReadDB_HighLmt(char *PointName)
{
    DMS_COMMON common_aa;
    ReadEntryByNameStr(PointName,&common_aa);
    return(common_aa.var.anlg.lmt_para.HI_WARN);
}

float ReadDB_LowLmt(char *PointName)
{
    DMS_COMMON common_aa;
    ReadEntryByNameStr(PointName,&common_aa);
    return(common_aa.var.anlg.lmt_para.LO_WARN);
}

int SendCommandToPLC (char *PointName,int Type_id,float data,short Status)
{
	DMS_COMMON common_aa;
	COMMAND_MSG	ml_buf;
	char err_str[80]="";
	time_t  tim;
	struct tm   tmpt;
	LAN_HEAD	lanhd;
	if(GetControlState()!=1) return(0);	//����վ���㲥��added by fengxun,2009-05-07
	if (ReadEntryByNameStr(PointName,&common_aa)==-1)
	{
		sprintf(err_str,"No this point %s\n",PointName);
		Err_log(err_str);
		return(-1);
	}

    ml_buf.type_id =Type_id;
    ml_buf.stn_id =common_aa.point.stn_id;
    ml_buf.dev_id =common_aa.point.dev_id;
    ml_buf.data_type=common_aa.point.data_type;
    ml_buf.point_id = common_aa.point.pt_id;

    ml_buf.status.opr= Status;
    ml_buf.status.state=0;
    ml_buf.status.src=1;

    ml_buf.data.iValue=(int)(data*1000);
    ml_buf.ctrl_addr=common_aa.fixed.ctrl_addr;
    GetLocalHostId(&ml_buf.host_id);
    ml_buf.usr_id=0;

    tim=time (NULL);
    tmpt=*localtime (&tim);
    ml_buf.second=tmpt.tm_sec;
    ml_buf.minute=tmpt.tm_min;
    ml_buf.hour=tmpt.tm_hour;
    ml_buf.day=tmpt.tm_mday;
    ml_buf.month=tmpt.tm_mon+1;
    ml_buf.year=tmpt.tm_year+1900;
    strcpy(ml_buf.usr_login_name,"AGC");
    lanhd.length=sizeof(COMMAND_MSG);

#ifdef SUNOS
    Swap2Byte(&ml_buf.point_id);
    Swap2Byte(&ml_buf.status);
    Swap4Byte(&ml_buf.data.iValue);
    Swap2Byte(&ml_buf.ctrl_addr);
    Swap2Byte(&ml_buf.year);
    Swap2Byte(&lanhd.length);
#endif

    lanhd.dp_type=COMM_TIME;
    lanhd.dest_id =ml_buf.dev_id;
    lanhd.src_id =ml_buf.host_id;
    lanhd.dest_stn =ml_buf.stn_id;
    lanhd.packet_num =0;
    
    if(GetControlState()==1)
        lan_out ((char *)&ml_buf,lanhd,(unsigned char)0);
//		printf("��������%s�´�Ϊ%f",PointName,data);
    return 0;
}

void FillCommandBuf()
{
	int i,flag;
	char	logtxt[100];
	flag=0;
	for (i=1;i<=UNIT_NUMB;i++) 
	{   
		if(UNIT[i].AP_Avail==0)continue;
/*        if((UNIT[i].Start==1)&&(UNIT[i].Status==UNIT_IN_STANDBY_AGC)&&(PLANT.Closed_Loop==1)&&(UNIT[i].StartAction==0))
        {
            UNIT[i].Start=0;
			UNIT[i].StartAction=1;
			SendAGC_CommandPeerToPeer(DB_NAME_Rt_Status[i], C_UNIT,UNIT[i].AP_Setp,KJML);
            printf("No:%d Unit Start!\n",i);
			rt_status = 0;  
			rt_status = SetCharBits ( rt_status, KJLTHM, BitS_CMD_TYPE, BitN_CMD_TYPE );	
			rt_status = SetCharBits ( rt_status, AGCML, BitS_AGC_TYPE, BitN_AGC_TYPE );
			CheckAndUpdateRTDB_Entry ( DB_NAME_Control_Command[i], MSG_SET, 0, rt_status );
			
			flag=1;
	        sprintf(logtxt, "%d��%02d��  %02d:%02d:%02d \n",ntime->tm_mon+1,ntime->tm_mday, ntime->tm_hour, ntime->tm_min, ntime->tm_sec );
	        WriteLogFile(logtxt);
			sprintf(logtxt,"No.Unit %d Start Command send out\n",i);
			WriteLogFile(logtxt);
        }
        if((UNIT[i].Stop==1)&&(UNIT[i].Status==UNIT_IN_GEN_AGC)&&(PLANT.Closed_Loop==1)&&(UNIT[i].StopAction==0))
        {
            UNIT[i].Stop=0;
			UNIT[i].StopAction=1;
			SendAGC_CommandPeerToPeer(DB_NAME_Rt_Status[i], C_UNIT,UNIT[i].AP_Setp,TJML);
            printf("No:%d Unit Stop!\n",i);
			rt_status = 0;  
			rt_status = SetCharBits ( rt_status, TJLTHM, BitS_CMD_TYPE, BitN_CMD_TYPE );	
			rt_status = SetCharBits ( rt_status, AGCML, BitS_AGC_TYPE, BitN_AGC_TYPE );
			CheckAndUpdateRTDB_Entry ( DB_NAME_Control_Command[i], MSG_SET, 0, rt_status );

			flag=1;
			sprintf(logtxt, "%d��%02d��  %02d:%02d:%02d \n",ntime->tm_mon+1,ntime->tm_mday, ntime->tm_hour, ntime->tm_min, ntime->tm_sec );
	        WriteLogFile(logtxt);
			sprintf(logtxt,"No.Unit %d Stop Command send out\n",i);
			WriteLogFile(logtxt);
        } 
*/		
		sprintf(logtxt, "%d��%02d��  %02d:%02d:%02d \n",ntime->tm_mon+1,ntime->tm_mday, ntime->tm_hour, ntime->tm_min, ntime->tm_sec );
		WriteLogFile(logtxt);
		sprintf(logtxt,"%d�Ż���ԭ�Ż�ֵ%d����ǰ�Ż�ֵ%d��ʵ��ֵ%6.2f\n",i,UNIT[i].AP_Setp,UNIT[i].XAP_Setp,UNIT[i].AP_RtValue);
		WriteLogFile(logtxt);
		AGC_UpdateRTDB_ANA (DB_NAME_Optimization_Value[i],UNIT[i].XAP_Setp);
		if(((abs(UNIT[i].AP_Setp-UNIT[i].XAP_Setp)>=1)&&(UNIT[i].Status==UNIT_IN_GEN_AGC)&&(PLANT.ACE_over_adj!=YES))||((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(PLANT.ACE_over_adj==YES)))
		{ 
//			UNIT[i].AP_Setp=UNIT[i].XAP_Setp;	
			if(PLANT.Closed_Loop==1)
			{
				UNIT[i].AP_Setp=UNIT[i].XAP_Setp;	//�˾�Ҳ���Է���PLANT.Closed_Loop�ж���
				SendCommandToPLC(DB_NAME_AP_SetValue[i],C_APOWER,UNIT[i].AP_Setp,0); 
				UNIT[i].CommandSendSbo = YES;	//ÿ�μ�������������־λ
				AGC_UpdateRTDB_IND (DB_NAME_Control_Command[i] , TGLTHM);
				flag=1;				
				sprintf(logtxt,"%d�Ż��� �й�����ֵ=%d �´�!\n",i,UNIT[i].AP_Setp);
				WriteLogFile(logtxt);
			}
		} 
/*		if((UNIT[i].AP_Setp==UNIT[i].XAP_Setp)&&(fabs(UNIT[i].AP_Setp-UNIT[i].AP_RtValue)>5)     //�����й�ƫ�ƴ���5MW���������ע��˹�����С���ɵ������ڹ��ܲ���ͬʱʹ��
			&&(UNIT[i].Status==UNIT_IN_GEN_AGC)&&(PLANT.Closed_Loop==1))
		{
			SendCommandToPLC(DB_NAME_AP_SetValue[i],C_APOWER,UNIT[i].AP_Setp,0); 
			AGC_UpdateRTDB_IND (DB_NAME_Control_Command[i] , TGLTHM);
		}*/
	}
	if(flag==1)
	{
		for(i=1;i<=UNIT_NUMB;i++)
		{
			sprintf(logtxt,"Unit No.%d Status=%d,AP_Avail=%d,Active Power=%f,AP_Min=%f,AP_Max=%f,AP_Setp=%f\n",
				i,UNIT[i].Status,UNIT[i].AP_Avail,UNIT[i].AP_RtValue,UNIT[i].AP_Min,UNIT[i].AP_Max,UNIT[i].AP_Setp);
			WriteLogFile(logtxt);
		}
		sprintf(logtxt,"PLANT.Mode=%d,WaterHead=%f,APSetpoint=%7.1f,PLANT.Control_Right=%d\n\n\n",PLANT.Mode,Watermsg.WaterHead,PLANT.AP_Setpoint,PLANT.Control_Right);
		WriteLogFile(logtxt);
	}
}

/*����Ϊh9000 v4.0 ��д�����*/

void InitData()
{
	int i;
	float Sum=0;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		UNIT[i].AP_RtValue=UNIT[i].Last_APValue=ReadDB_ANA(DB_NAME_AP_RtValue[i]);
		Sum+=UNIT[i].AP_RtValue;
		UNIT[i].AP_Setp=UNIT[i].XAP_Setp=(int)(UNIT[i].AP_RtValue+0.5);
		UNIT[i].StartAction=0;
		UNIT[i].StopAction=0;
		UNIT[i].Privilege=(int)ReadDB_ANA(DB_NAME_Prvilege[i]);
		UNIT[i].AP_Yggd = ReadDB_ANA(DB_NAME_AP_SetValue[i]);
	}
	PLANT.AP_Setpoint=Sum;
	PLANT.AP_WorkSP=Sum;
	PLANT.Mode=AGC_MODE_NONE;	
//	printf("ȫ�����й�=%d\n",(int)Sum);
	AGC_UpdateRTDB_ANA ( DB_NAME_AP_Setpoint, (int)Sum );
	AGC_UpdateRTDB_IND ( DB_NAME_QC_AGC, NOT);
	AGC_UpdateRTDB_IND ( DB_NAME_AGC_CLOSED_LOOP,  NOT );
	AGC_UpdateRTDB_IND ( DB_NAME_Control_Right,  NOT );  
	old_waterlevel=ReadDB_ANA (DB_NAME_Water_Head );
}

void ReadCurveDefFile()
{
	FILE	*fp;
	char filename[100]="/home/ems/h9000/def/Curve.DEF";
	char keyword[30]="";
	char StrTemp[50]="";
	int i,tmp;

	if( (fp=fopen(filename, "r"))==NULL )
	{
         printf("Fail to open %s\n", filename);
         UnMount_handle();
	}

	strcpy(keyword,"TodayCurve");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<SCHEDULE+1;i++)			//SCHEDULEΪ���ߵ����
	{
		fscanf(fp,"%s\n",DB_NAME_Today_Curve[i]);
		printf("%d\t%s\n",i,DB_NAME_Today_Curve[i]);
		
		tmp = ReadDB_Chan ( DB_NAME_Today_Curve[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_Today_Curve[i]);
			UnMount_handle();
		}
	}

	strcpy(keyword,"TomorrowCurve");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<SCHEDULE+1;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_Tomorrow_Curve[i]);
		printf("%d\t%s\n",i,DB_NAME_Tomorrow_Curve[i]);
		tmp = ReadDB_Chan ( DB_NAME_Tomorrow_Curve[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_Tomorrow_Curve[i]);
			UnMount_handle();
		}
	}
	fclose(fp);	
}

void ReadWaterHeadPowerDefFile()
{
	FILE	*fp;
	char filename[100]="/home/ems/h9000/def/WaterHeadPower.DEF";
	char keyword[30]="";
	char StrTemp[50]="",StrTemp1[50]="",StrTemp2[50]="",StrTemp3[50]="",StrTemp4[50]="",StrTemp5[50]="";
	char TypeKeyword[MAX_UNIT_NUMB+1][50];
	int i,j;

	if( (fp=fopen(filename, "r"))==NULL )
	{
         printf("Fail to open %s\n", filename);
         UnMount_handle();
	}
/*
	strcpy(keyword,"UnitMinPower");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
	   fscanf(fp,"%s\n",StrTemp);
	   UNIT[i].AP_Min=atoi(StrTemp);
#ifdef DEBUG
	printf("Unit No.%d AP_Min=%d\n",i,UNIT[i].AP_Min);
#endif
	}
*/			/*����������޲����ļ����*/
	strcpy(keyword,"ItemNumber");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",StrTemp);
    ItemNumber=atoi(StrTemp);
#ifdef DEBUG
	printf("ItemNumber=%d\n",ItemNumber);
#endif

	strcpy(keyword,"TypeNumber");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",StrTemp);
    TypeNumber=atoi(StrTemp);
	if((TypeNumber<=0)||(TypeNumber>UNIT_NUMB))
	{
		printf("�������͸�������ȷ\n");
		UnMount_handle();
	}
#ifdef DEBUG
	printf("TypeNumber=%d\n",TypeNumber);
#endif

	strcpy(keyword,"TypeKeyword");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=TypeNumber;i++)
	{
	   fscanf(fp,"%s\n",TypeKeyword[i]);
#ifdef DEBUG
	printf("TypeKeyword=%s\n",TypeKeyword[i]);
#endif
	}

	strcpy(keyword,"Type_UnitNo");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=TypeNumber;i++)
	{
		fscanf(fp,"%s",StrTemp);
		Type_UnitNo[i][0]=atoi(StrTemp);
		for(j=1;j<=Type_UnitNo[i][0];j++)
		{
		   fscanf(fp,"%s",StrTemp);
		   Type_UnitNo[i][j]=atoi(StrTemp);
#ifdef DEBUG
	printf("Type No%d: Unit %d\n",i,Type_UnitNo[i][j]);
#endif
		}
	}

	for(i=1;i<=TypeNumber;i++)
	{
		strcpy(keyword,TypeKeyword[i]);
		if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
		for(j=1;j<=ItemNumber;j++)
		{
			fscanf(fp,"%s	%s	%s	%s	%s	%s\n",StrTemp,StrTemp1,StrTemp2,StrTemp3,StrTemp4,StrTemp5);
			WaterheadPower[i][0][j]=(float)atof(StrTemp);
			WaterheadPower[i][1][j]=(float)atof(StrTemp1);	
			WaterheadPower[i][2][j]=(float)atof(StrTemp2);
			WaterheadPower[i][3][j]=(float)atof(StrTemp3);
			WaterheadPower[i][4][j]=(float)atof(StrTemp4);
			WaterheadPower[i][5][j]=(float)atof(StrTemp5);
#ifdef DEBUG
			printf("Type No%d:Waterhead=%f,MaxPower=%f,UnRunlow1=%f,UnRunhigh1=%f,UnRunlow2=%f,UnRunhigh2=%f\n",i,
			WaterheadPower[i][0][j],WaterheadPower[i][1][j],WaterheadPower[i][2][j],WaterheadPower[i][3][j],
			WaterheadPower[i][4][j],WaterheadPower[i][5][j]);
#endif
		}
	}
	fclose(fp);	
}

void GetCurrentUnitMaxMinPower()
{
	int i,j,Pos,k,tmpid;
	float MaxPower,UnRunlow1,UnRunhigh1,UnRunlow2,UnRunhigh2;
	k=1;
#ifdef PBG
	Watermsg.WaterHead=Watermsg.UpWaterLevel;  //���������ٲ�����������ˮλ����ֵ�ĵ糧��
#endif
	for(i=1;i<=TypeNumber;i++)
	{
		Pos=0;
		for(j=1;j<ItemNumber;j++)
		{
			if((Watermsg.WaterHead>=WaterheadPower[i][0][j])&&(Watermsg.WaterHead<WaterheadPower[i][0][j+1]))
			{
				Pos=j;
				break;
			}
		}
		if(Watermsg.WaterHead>=WaterheadPower[i][0][ItemNumber])
		{	
			Pos=ItemNumber;  //printf("Pos=%d,ItemNumber=%d,WaterheadPower[%d][1][%d]=%f,Type_UnitNo[%d][0]=%d\n",Pos,ItemNumber,i,ItemNumber,WaterheadPower[i][1][ItemNumber],i,Type_UnitNo[i][0]);
		}
		if(Pos==0)
		{
			MaxPower=WaterheadPower[i][1][1];
			UnRunlow1=WaterheadPower[i][2][1];
			UnRunhigh1=WaterheadPower[i][3][1];
			UnRunlow2=WaterheadPower[i][4][1];
			UnRunhigh2=WaterheadPower[i][5][1];
		}
		else if(Pos==ItemNumber)
		{
			MaxPower=WaterheadPower[i][1][ItemNumber];
			UnRunlow1=WaterheadPower[i][2][ItemNumber];
			UnRunhigh1=WaterheadPower[i][3][ItemNumber];
			UnRunlow2=WaterheadPower[i][4][ItemNumber];
			UnRunhigh2=WaterheadPower[i][5][ItemNumber];
		}
		else
		{
//������������ò�ֵ������
			MaxPower=(Watermsg.WaterHead-WaterheadPower[i][0][Pos])/(WaterheadPower[i][0][Pos+1]-WaterheadPower[i][0][Pos])*(WaterheadPower[i][1][Pos+1]-WaterheadPower[i][1][Pos])+WaterheadPower[i][1][Pos];
//���㷨�ǲ�ֵȡ������Χֵ
/*			UnRunlow1=(Watermsg.WaterHead-WaterheadPower[i][0][Pos])/(WaterheadPower[i][0][Pos+1]-WaterheadPower[i][0][Pos])*(WaterheadPower[i][2][Pos+1]-WaterheadPower[i][2][Pos])+WaterheadPower[i][2][Pos];
			UnRunhigh1=(Watermsg.WaterHead-WaterheadPower[i][0][Pos])/(WaterheadPower[i][0][Pos+1]-WaterheadPower[i][0][Pos])*(WaterheadPower[i][3][Pos+1]-WaterheadPower[i][3][Pos])+WaterheadPower[i][3][Pos];
			UnRunlow2=(Watermsg.WaterHead-WaterheadPower[i][0][Pos])/(WaterheadPower[i][0][Pos+1]-WaterheadPower[i][0][Pos])*(WaterheadPower[i][4][Pos+1]-WaterheadPower[i][4][Pos])+WaterheadPower[i][4][Pos];
			UnRunhigh2=(Watermsg.WaterHead-WaterheadPower[i][0][Pos])/(WaterheadPower[i][0][Pos+1]-WaterheadPower[i][0][Pos])*(WaterheadPower[i][5][Pos+1]-WaterheadPower[i][5][Pos])+WaterheadPower[i][5][Pos];
*/

//���㷨��ȡ�Ͽ��������Χֵ
			if(WaterheadPower[i][2][Pos]>WaterheadPower[i][2][Pos+1])  
				UnRunlow1=WaterheadPower[i][2][Pos+1];
			else 
				UnRunlow1=WaterheadPower[i][2][Pos];
			
			if(WaterheadPower[i][3][Pos]<WaterheadPower[i][3][Pos+1])
				UnRunhigh1=WaterheadPower[i][3][Pos+1];
			else 
				UnRunhigh1=WaterheadPower[i][3][Pos];

			if(WaterheadPower[i][4][Pos]>WaterheadPower[i][4][Pos+1])
				UnRunlow2=WaterheadPower[i][4][Pos+1];
			else 
				UnRunlow2=WaterheadPower[i][4][Pos];

			if(WaterheadPower[i][5][Pos]<WaterheadPower[i][5][Pos+1])
				UnRunhigh2=WaterheadPower[i][5][Pos+1];
			else 
				UnRunhigh2=WaterheadPower[i][5][Pos];			
		}
		for(j=1;j<=Type_UnitNo[i][0];j++)
		{
			tmpid=Type_UnitNo[i][j];
			if (UNIT[tmpid].Status!=UNIT_IN_GEN_AGC) //ʡ��Ҫ�󣬲��ڷ���̬�Ļ��������Χ��Ϊ0~600MW
			{    
				AGC_UpdateRTDB_ANA ( DB_NAME_AP_Min[tmpid], 0 );   	
				AGC_UpdateRTDB_ANA ( DB_NAME_AP_Max[tmpid], 600.0 );   	
			}
			else
			{
				UNIT[tmpid].AP_Max=MaxPower;	              /*UNIT[i].AP_Max��ReadWaterHeadPowerDefFile��GetWaterLevel�������*/				
				if(PLANT.Manual_Set==YES)	//�ֶ�ˮλ����
				{	
					UNIT[tmpid].AP_Min=ReadDB_ANA(DB_NAME_AP_Min[tmpid]);
					if(UNIT[tmpid].AP_Min<15)
					{
						UNIT[tmpid].AP_Min=15;
					}
				}
				else	//�Զ�ˮλ
				{
					UNIT[tmpid].AP_Min=15;
				}
				
//		        printf("��ǰˮͷ%6.2f�ף�No%d.%d�Ż��ɷ�����й�ֵΪ%6.2f\n",Watermsg.WaterHead,k,Type_UnitNo[i][j],UNIT[k].AP_Max);
//				printf("����1����%6.2f������1����%6.2f������2����%6.2f������2����%6.2f\n",UnRunlow1,UnRunhigh1,UnRunlow2,UnRunhigh2);
				UNIT[tmpid].Low_Vibration[1]=UnRunlow1;
				UNIT[tmpid].Up_Vibration[1]=UnRunhigh1;
				UNIT[tmpid].Low_Vibration[2]=UnRunlow2;
				UNIT[tmpid].Up_Vibration[2]=UnRunhigh2;

				if(UNIT[tmpid].Low_Vibration[1]<=UNIT[tmpid].AP_Min && UNIT[tmpid].Up_Vibration[1]>=UNIT[tmpid].AP_Min)
				{
					UNIT[tmpid].AP_Min=UNIT[tmpid].Up_Vibration[1];
				}
				AGC_UpdateRTDB_ANA ( DB_NAME_AP_Min[tmpid], UNIT[tmpid].AP_Min );

				if((UNIT[tmpid].Low_Vibration[1]==UNIT[tmpid].Up_Vibration[1]) /*ֻ��һ������������������������Ϊ�������޼�1�������˵��ʵʱֵ��Ϊ0*/
					||(UNIT[tmpid].Low_Vibration[1]<=UNIT[tmpid].AP_Min && UNIT[tmpid].Up_Vibration[1]<=UNIT[tmpid].AP_Min))
				{
					UNIT[tmpid].Low_Vibration[1]=UNIT[tmpid].AP_Min+1;
					UNIT[tmpid].Up_Vibration[1]=UNIT[tmpid].AP_Min+1;
					AGC_UpdateRTDB_ANA ( DB_NAME_Low_Vibration[tmpid][1], 0 );
					AGC_UpdateRTDB_ANA ( DB_NAME_Up_Vibration[tmpid][1], 0 );
				}
				else if(UNIT[tmpid].Low_Vibration[1]<=UNIT[tmpid].AP_Min && UNIT[tmpid].Up_Vibration[1]>UNIT[tmpid].AP_Min) //�����й������������ڣ���Ϊ��������Ч
				{
					UNIT[tmpid].Low_Vibration[1]=UNIT[tmpid].AP_Min+1;
					AGC_UpdateRTDB_ANA ( DB_NAME_Low_Vibration[tmpid][1], UNIT[tmpid].Low_Vibration[1] );
					AGC_UpdateRTDB_ANA ( DB_NAME_Up_Vibration[tmpid][1], UNIT[tmpid].Up_Vibration[1] );
				}
				else	/*��������*/
				{
					AGC_UpdateRTDB_ANA ( DB_NAME_Low_Vibration[tmpid][1], UNIT[tmpid].Low_Vibration[1] );
					AGC_UpdateRTDB_ANA ( DB_NAME_Up_Vibration[tmpid][1], UNIT[tmpid].Up_Vibration[1] );
				}

				AGC_UpdateRTDB_ANA ( DB_NAME_AP_Max[tmpid], UNIT[tmpid].AP_Max );
				AGC_UpdateRTDB_ANA ( DB_NAME_Low_Vibration[tmpid][2], UNIT[tmpid].Low_Vibration[2] );
				AGC_UpdateRTDB_ANA ( DB_NAME_Up_Vibration[tmpid][2], UNIT[tmpid].Up_Vibration[2] );	
				k++;
			}
		}
	}
}

void Check_AKQJ()
{	
	FILE	*fp;
	char filename[100]="/home/ems/h9000/def/AGC.DEF";
	char keyword[30]="";
	int i,j,agc_akqj_unitnum;
	float akqj_rl,AGC_AKQJRL_all,AGC_AKQJRL_limit,noagc_akqj_limit,akqj_blrl[MAX_UNIT_NUMB+1]; //�����л�����,Ͷ�밲���л��Ļ����������,AGC���ɿصİ����л���������
	char unit_akqj_sta[MAX_UNIT_NUMB+1];
    char DB_NAME_AKQJRL[NAME_SIZE],DB_NAME_AKQJRL_LACK[NAME_SIZE],DB_NAME_AKQJJZCL[NAME_SIZE];
    char DB_NAME_AKQJ_Sta[MAX_UNIT_NUMB+1][NAME_SIZE],DB_NAME_AKQJ_BLRL[MAX_UNIT_NUMB+1][NAME_SIZE];
	float tmp,tmp1;
	
	if( (fp=fopen(filename, "r"))==NULL )
	{
		printf("Fail to open %s\n", filename);
		UnMount_handle();
	}
	
	strcpy(keyword,"AGC_AKQJRL");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AKQJRL);
	akqj_rl = ReadDB_ANA( DB_NAME_AKQJRL );
#ifdef DEBUG
//	printf("�����л�����=%6.2f\n",akqj_rl);
#endif

	strcpy(keyword,"AGC_AKQJRL_LACK");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AKQJRL_LACK);
#ifdef DEBUG
//	printf("�����л��������㱨�����Ƶ���=%s\n",DB_NAME_AKQJRL_LACK);
#endif

	strcpy(keyword,"AGC_AKQJJZCL");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AKQJJZCL);
#ifdef DEBUG
//	printf("�����л�����������޲����㱨�����Ƶ�=%s\n",DB_NAME_AKQJJZCL);
#endif

	strcpy(keyword,"AKQJ_JYBLRL");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AKQJ_BLRL[i]);
		#ifdef DEBUG
//		printf("�����л����鱣���������Ƶ�%s\n",DB_NAME_AKQJ_BLRL[i]);
		#endif
	}
	
	strcpy(keyword,"Unit_AKQJ_Sta");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AKQJ_Sta[i]);
		unit_akqj_sta[i] = ReadDB_IND( DB_NAME_AKQJ_Sta[i] );		
        #ifdef DEBUG
//	    printf("�����л�״̬[%d]=%d\n",i,unit_akqj_sta[i]);
        #endif
	}  
	fclose(fp);
	AGC_AKQJRL_all=0;
	agc_akqj_unitnum=0;
	AGC_AKQJRL_limit=0;
	noagc_akqj_limit=0;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(unit_akqj_sta[i]==1)
		{
			AGC_AKQJRL_all+=UNIT[i].AP_RtValue;
			AGC_AKQJRL_limit+=UNIT[i].AP_Min;
			if(UNIT[i].AP_Avail!=1) 
				noagc_akqj_limit+=UNIT[i].AP_RtValue;
			else			
				agc_akqj_unitnum++;
		}
		else
		{
			AGC_UpdateRTDB_ANA ( DB_NAME_AKQJ_BLRL[i], 0 );
		}
	}

	if(AGC_AKQJRL_all<=akqj_rl)
		AGC_UpdateRTDB_IND ( DB_NAME_AKQJRL_LACK, YES );
	else
		AGC_UpdateRTDB_IND ( DB_NAME_AKQJRL_LACK, NOT );

	if(AGC_AKQJRL_limit<akqj_rl)
	{			
		tmp=akqj_rl-noagc_akqj_limit;
		if(agc_akqj_unitnum==0) 
		{
			AGC_UpdateRTDB_IND ( DB_NAME_AKQJJZCL, YES );
			return;
		}
		for(i=1;i<=UNIT_NUMB;i++)
		{
			if((UNIT[i].AP_Avail==1) && (unit_akqj_sta[i]==1))
			{	
				tmp1=tmp/agc_akqj_unitnum;
				if(tmp1>0)
				{	
					if(tmp1>UNIT[i].AP_Max)					
					{
						akqj_blrl[i]=UNIT[i].AP_Max-10;
						AGC_UpdateRTDB_IND ( DB_NAME_AKQJJZCL, YES );
					}
					else
					{
						akqj_blrl[i]=	tmp1;
						AGC_UpdateRTDB_IND ( DB_NAME_AKQJJZCL, NOT );
					}
				}
				else 
					akqj_blrl[i]=0;
				for(j=1;j<=UNIT[i].VibrationNum;j++)
				{
					if((akqj_blrl[i]>=UNIT[i].Low_Vibration[j])&&(akqj_blrl[i]<UNIT[i].Up_Vibration[j]))
						akqj_blrl[i]=UNIT[i].Up_Vibration[j];
				}				
			}
			else if(unit_akqj_sta[i]!=1) akqj_blrl[i]=0;	//�ǰ����л����齨��ֵΪ0
			else if(UNIT[i].AP_Avail==1) akqj_blrl[i]=UNIT[i].AP_RtValue;  //�ǳ��鰲���л����齨��ֵΪ�������ʵʱֵ
			AGC_UpdateRTDB_ANA ( DB_NAME_AKQJ_BLRL[i], akqj_blrl[i] );
		}
	}	
}

void InitialAGC_Data_On_Screen ()
{
	int	i, tmp;
	float Sum;
	Sum=0;
	for ( i= 1; i<= UNIT_NUMB; i++ )  
	{
		UNIT[i].AP_RtValue=UNIT[i].Last_APValue=ReadDB_ANA(DB_NAME_AP_RtValue[i]);
		if(UNIT[i].Status==UNIT_IN_GEN_AGC) Sum+=UNIT[i].AP_RtValue;
		UNIT[i].AP_Setp=UNIT[i].XAP_Setp=(int)(UNIT[i].AP_RtValue+0.5);
		UNIT[i].StartAction=0;
		UNIT[i].StopAction=0;
		UNIT[i].CommandSendSbo = NOT;
		UNIT[i].Privilege=(int)ReadDB_ANA(DB_NAME_Prvilege[i]);
		AGC_UpdateRTDB_ANA (DB_NAME_Optimization_Value[i], UNIT[i].AP_RtValue);
		AGC_UpdateRTDB_IND ( DB_NAME_Control_Command[i], WCZTHM );
	}
	PLANT.AP_Setpoint=Sum;
	PLANT.AP_WorkSP=Sum;
	PLANT.Mode=AGC_MODE_NONE;
	if((PLANT.Control_Right==1)&&(PLANT.AP_Setting==1)&&(set_p_flag==1))
        {AGC_UpdateRTDB_ANA ( DB_NAME_AP_Setpoint, PLANT.AP_Setpoint );}
#ifndef HuaZhongWangDiao
	else if(PLANT.AP_Setting==1)
		//yyp	
		AGC_UpdateRTDB_ANA ( DB_NAME_Remote_Setpoint,PLANT.AP_Setpoint );
#endif
	else if(PLANT.AP_Curve==1)
	{
		AGC_UpdateRTDB_ANA ( DB_NAME_AP_Setpoint, PLANT.AP_Setpoint );
		//yyp
		AGC_UpdateRTDB_ANA ( DB_NAME_Remote_Setpoint, PLANT.AP_Setpoint );
	}
}

void ReadAGCDefFile()
{
	FILE	*fp;
	char filename[100]="/home/ems/h9000/def/AGC.DEF";
	char keyword[30]="";
	char StrTemp[50]="",StrTemp1[50]="";
	int i,j;
	int tmp;

	if( (fp=fopen(filename, "r"))==NULL )
	{
		printf("Fail to open %s\n", filename);
		UnMount_handle();
	}
    strcpy(keyword,"UnitNumber");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",StrTemp);
    UNIT_NUMB=atoi(StrTemp);
	if((UNIT_NUMB>MAX_UNIT_NUMB)||(UNIT_NUMB<=0))
	{
		printf("����̨���������!\n");
		UnMount_handle();
	}
#ifdef DEBUG
	printf("UNIT_NUMB=%d\n",UNIT_NUMB);
#endif   

	strcpy(keyword,"StartStopFunction");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",StrTemp);
    PLANT.Auto_StartStop=atoi(StrTemp);
	if((PLANT.Auto_StartStop!=0)&&(PLANT.Auto_StartStop!=1))
	{
		printf("�����Զ���ͣ����ʽ�������!ֻ��Ϊ0��1!\n");
		UnMount_handle();
	}
#ifdef DEBUG
	printf("Auto_StartStop=%d\n",PLANT.Auto_StartStop);
#endif 

	strcpy(keyword,"VZ_Deadband");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",StrTemp);
    PLANT.VZ_Deadband=atoi(StrTemp);
#ifdef DEBUG
	printf("VZ_Deadband=%d\n",PLANT.VZ_Deadband);
#endif

	strcpy(keyword,"Factor");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
	    fscanf(fp,"%s\n",StrTemp);
        factor[i]=(float)atof(StrTemp);
#ifdef DEBUG
	printf("factor[%d]=%f\n",i,factor[i]);
#endif
	}

	strcpy(keyword,"AP_Step");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
	    fscanf(fp,"%s\n",StrTemp);
        AP_Step[i]=atoi(StrTemp);
#ifdef DEBUG
	printf("AP_Step[%d]=%d\n",i,AP_Step[i]);
#endif
	}

	strcpy(keyword,"AP_Adj_Step");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_ADJ_STEP[i]);
		tmp = ReadDB_Chan ( DB_NAME_ADJ_STEP[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_ADJ_STEP[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_ADJ_STEP[%d]=%s\n",i,DB_NAME_ADJ_STEP[i]);
#endif
	}
	
	strcpy(keyword,"ManSetLmt");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",StrTemp);
    ManSetLmt=atoi(StrTemp);
#ifdef DEBUG
	printf("ManSetLmt=%d\n",ManSetLmt);
#endif

	strcpy(keyword,"CurveSetFuc");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",StrTemp);
    CurveSetFuc=atoi(StrTemp);
#ifdef DEBUG
	printf("CurveSetFuc=%d\n",CurveSetFuc);
#endif

	strcpy(keyword,"AP_ChangeMax");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AP_ChangeMax);
#ifdef DEBUG
	printf("AP_ChangeMax=%s\n",DB_NAME_AP_ChangeMax);
#endif

	strcpy(keyword,"ALM_P_GETERR");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_ALM_P_GETERR);
#ifdef DEBUG
	printf("ALM_P_GETERR=%s\n",DB_NAME_ALM_P_GETERR);
#endif

	strcpy(keyword,"ALM_ChangeMax");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_ALM_ChangeMax);
#ifdef DEBUG
	printf("ALM_ChangeMax=%s\n",DB_NAME_ALM_ChangeMax);
#endif

	if(PLANT.Auto_StartStop==1)
	{
	    strcpy(keyword,"StartStopDeadband");
	    if(-1==LocateKeyword(fp,keyword))
		   UnMount_handle();
	    fscanf(fp,"%s\n",DB_NAME_StartStopDeadband);
#ifdef DEBUG
	printf("DB_NAME_StartStopDeadband=%s\n",DB_NAME_StartStopDeadband);
#endif 
	}

	strcpy(keyword,"DB_AP_WorkSP");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_DB_AP_WorkSP);
#ifdef DEBUG
	printf("DB_NAME_DB_AP_WorkSP=%s\n",DB_NAME_DB_AP_WorkSP);
#endif  

	strcpy(keyword,"Vibration");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
	    fscanf(fp,"%s\n",StrTemp);
        UNIT[i].VibrationNum=atoi(StrTemp);
	    if((UNIT[i].VibrationNum>VIBRATION_NUMB)||(UNIT[i].VibrationNum<0))
		{
		   printf("�������������������!\n");
		   UnMount_handle();
		}
#ifdef DEBUG
	printf("No.%d VibrationNum=%d\n",i,UNIT[i].VibrationNum);
#endif
	     for(j=1;j<=UNIT[i].VibrationNum;j++)
		 {
			 fscanf(fp,"%s	%s\n",DB_NAME_Low_Vibration[i][j],DB_NAME_Up_Vibration[i][j]);			 
			 tmp = ReadDB_Chan ( DB_NAME_Low_Vibration[i][j] );
	         if ( tmp == DATA_ERR )
			 {
		        printf ( "AGC: %s is not found in Database!\n", DB_NAME_Low_Vibration[i][j]);
		        UnMount_handle();
			 }
			 tmp = ReadDB_Chan ( DB_NAME_Low_Vibration[i][j] );
	         if ( tmp == DATA_ERR )
			 {
		        printf ( "AGC: %s is not found in Database!\n", DB_NAME_Up_Vibration[i][j]);
		        UnMount_handle();
			 }
#ifdef DEBUG
	printf("UNIT.No.%d %s	%s\n",i,DB_NAME_Low_Vibration[i][j],DB_NAME_Up_Vibration[i][j]);
#endif
		 }
	}

	if(ManSetLmt==0)
	{
	    strcpy(keyword,"VibrationValue");
	    if(-1==LocateKeyword(fp,keyword))
		    UnMount_handle();
	    for(i=1;i<=UNIT_NUMB;i++)
		{
	        for(j=1;j<=UNIT[i].VibrationNum;j++)
			{ 
			    fscanf(fp,"%s	%s\n",StrTemp,StrTemp1);
			    UNIT[i].Low_Vibration[j]=(float)atoi(StrTemp);
			    UNIT[i].Up_Vibration[j]=(float)atoi(StrTemp1);
#ifdef DEBUG
	        printf("Unit No.%d Low_Vibration[%d]=%d,Up_Vibration[%d]=%d\n",
				  i,j,UNIT[i].Low_Vibration[j],j,UNIT[i].Up_Vibration[j]);
#endif
			    if(UNIT[i].Low_Vibration[j]>=UNIT[i].Up_Vibration[j])
				{
				   printf("Unit No.%d ��%d������������˳����!!!\n",i,j);
				   UnMount_handle();
				}
			    if((j>1)&&(UNIT[i].Low_Vibration[j]<=UNIT[i].Up_Vibration[j-1]))
				{
				   printf("����Ӧ��С����˳������!\n");
				   UnMount_handle();
				}
			}
		}
	}


	strcpy(keyword,"WaterHead_Range");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s %s\n",StrTemp,StrTemp1);
    MinWaterhead=(float)atof(StrTemp);
	MaxWaterhead=(float)atof(StrTemp1);
#ifdef DEBUG
	printf("MinWaterhead=%f,MaxWaterhead=%f\n",MinWaterhead,MaxWaterhead);
#endif

	strcpy(keyword,"Upstream_Level");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_Upstream_Level);
	tmp = ReadDB_Chan ( DB_NAME_Upstream_Level );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_Upstream_Level);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_Upstream_Level=%s\n",DB_NAME_Upstream_Level);
#endif

	strcpy(keyword,"Downstream_Level");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_Downstream_Level);
	tmp = ReadDB_Chan ( DB_NAME_Downstream_Level );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_Downstream_Level);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_Downstream_Level=%s\n",DB_NAME_Downstream_Level);
#endif

	strcpy(keyword,"Water_Head");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_Water_Head);
	tmp = ReadDB_Chan ( DB_NAME_Water_Head );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_Water_Head);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_Water_Head=%s\n",DB_NAME_Water_Head);
#endif

	strcpy(keyword,"Manual_Set");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_Manual_Set);
	tmp = ReadDB_Chan ( DB_NAME_Manual_Set );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_Manual_Set);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_Manual_Set=%s\n",DB_NAME_Manual_Set);
#endif

	strcpy(keyword,"AGC_Period");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_Period);
	tmp = ReadDB_Chan ( DB_NAME_AGC_Period );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_Period);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_Period=%s\n",DB_NAME_AGC_Period);
#endif

	strcpy(keyword,"WATER_REFR_TIME");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_WATER_REFR_TIME);
	tmp = ReadDB_Chan ( DB_NAME_WATER_REFR_TIME );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_WATER_REFR_TIME);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("WATER_REFR_TIME=%s\n",DB_NAME_WATER_REFR_TIME);
#endif

	strcpy(keyword,"AP_RtValue");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AP_RtValue[i]);
		tmp = ReadDB_Chan ( DB_NAME_AP_RtValue[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_RtValue[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_AP_RtValue[%d]=%s\n",i,DB_NAME_AP_RtValue[i]);
#endif
	}
	
	strcpy(keyword,"AP_SETValue");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AP_SetValue[i]);
		tmp = ReadDB_Chan ( DB_NAME_AP_SetValue[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_SetValue[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_AP_SetValue[%d]=%s\n",i,DB_NAME_AP_SetValue[i]);
#endif
	}
	
	strcpy(keyword,"Optimization_Value");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_Optimization_Value[i]);		
		tmp = ReadDB_Chan ( DB_NAME_Optimization_Value[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_Optimization_Value[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_Optimization_Value[%d]=%s\n",i,DB_NAME_Optimization_Value[i]);
#endif
	}

	strcpy(keyword,"Control_Command");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_Control_Command[i]);
		tmp = ReadDB_Chan ( DB_NAME_Control_Command[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_Control_Command[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_Control_Command[%d]=%s\n",i,DB_NAME_Control_Command[i]);
#endif
	}

	strcpy(keyword,"RT_P_Curve");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_RT_P_Curve);
	tmp = ReadDB_Chan ( DB_NAME_RT_P_Curve );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_RT_P_Curve);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_RT_P_Curve=%s\n",DB_NAME_RT_P_Curve);
#endif

	strcpy(keyword,"Control_Right");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_Control_Right);
	tmp = ReadDB_Chan ( DB_NAME_Control_Right );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_Control_Right);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_Control_Right=%s\n",DB_NAME_Control_Right);
#endif

	strcpy(keyword,"AGC_CLOSED_LOOP");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_CLOSED_LOOP);
	tmp = ReadDB_Chan ( DB_NAME_AGC_CLOSED_LOOP );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_CLOSED_LOOP);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_CLOSED_LOOP=%s\n",DB_NAME_AGC_CLOSED_LOOP);
#endif

	strcpy(keyword,"QC_AGC");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_QC_AGC);
	tmp = ReadDB_Chan ( DB_NAME_QC_AGC );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_QC_AGC);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_QC_AGC=%s\n",DB_NAME_QC_AGC);
#endif 

	strcpy(keyword,"AP_Setting");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AP_Setting);
	tmp = ReadDB_Chan ( DB_NAME_AP_Setting );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_Setting);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AP_Setting=%s\n",DB_NAME_AP_Setting);
#endif

	strcpy(keyword,"AP_Curve");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AP_Curve);
	tmp = ReadDB_Chan ( DB_NAME_AP_Curve );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_Curve);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AP_Curve=%s\n",DB_NAME_AP_Curve);
#endif

	strcpy(keyword,"Rt_Status");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_Rt_Status[i]);
		tmp = ReadDB_Chan ( DB_NAME_Rt_Status[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_Rt_Status[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_Rt_Status[%d]=%s\n",i,DB_NAME_Rt_Status[i]);
#endif
	}   

	strcpy(keyword,"AP_Group");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AP_Group[i]);
		tmp = ReadDB_Chan ( DB_NAME_AP_Group[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_Group[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_AP_Group[%d]=%s\n",i,DB_NAME_AP_Group[i]);
#endif
	} 

	strcpy(keyword,"AP_CZKT");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AP_CZKT[i]);
		tmp = ReadDB_Chan ( DB_NAME_AP_CZKT[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_CZKT[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_AP_CZKT[%d]=%s\n",i,DB_NAME_AP_CZKT[i]);
#endif
	} 

	strcpy(keyword,"AGC_JZJX");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AGC_JZJX[i]);
		tmp = ReadDB_Chan ( DB_NAME_AGC_JZJX[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_JZJX[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_AGC_JZJX[%d]=%s\n",i,DB_NAME_AGC_JZJX[i]);
#endif
	} 

	strcpy(keyword,"Though_Vibration");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_VIBRATING[i]);
#ifdef DEBUG
		printf("DB_NAME_VIBRATING[%d]=%s\n",i,DB_NAME_VIBRATING[i]);
#endif
	}

	strcpy(keyword,"Unit_OverTime");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_UNIT_OVERTIME[i]);
#ifdef DEBUG
		printf("DB_NAME_UNIT_OVERTIME[%d]=%s\n",i,DB_NAME_UNIT_OVERTIME[i]);
#endif
	}

	strcpy(keyword,"Unit_P_Rebalance");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_UNITP_BALANCE[i]);
#ifdef DEBUG
		printf("DB_NAME_UNITP_BALANCE[%d]=%s\n",i,DB_NAME_UNITP_BALANCE[i]);
#endif
	}

	strcpy(keyword,"AGC_STATE");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_STATE);
	tmp = ReadDB_Chan ( DB_NAME_AGC_STATE );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_STATE);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_STATE=%s\n",DB_NAME_AGC_STATE);
#endif

	strcpy(keyword,"Prvilege");
	if(-1==LocateKeyword(fp,keyword))
	UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_Prvilege[i]);
		tmp = ReadDB_Chan ( DB_NAME_Prvilege[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_Prvilege[i]);
			UnMount_handle();
		}
#ifdef DEBUG
		printf("DB_NAME_Prvilege[%d]=%s\n",i,DB_NAME_Prvilege[i]);
#endif
	}   

	
	strcpy(keyword,"AP_Setpoint");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AP_Setpoint);
	tmp = ReadDB_Chan ( DB_NAME_AP_Setpoint );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_Setpoint);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AP_Setpoint=%s\n",DB_NAME_AP_Setpoint);
#endif 
    
	strcpy(keyword,"Remote_Setpoint");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_Remote_Setpoint);
	tmp = ReadDB_Chan ( DB_NAME_Remote_Setpoint );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_Remote_Setpoint);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_Remote_Setpoint=%s\n",DB_NAME_Remote_Setpoint);
#endif 

	strcpy(keyword,"AP_Min");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AP_Min[i]);
		tmp = ReadDB_Chan ( DB_NAME_AP_Min[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_Min[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_AP_Min[%d]=%s\n",i,DB_NAME_AP_Min[i]);
#endif
	}   

	strcpy(keyword,"AP_Max");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AP_Max[i]);
		tmp = ReadDB_Chan ( DB_NAME_AP_Max[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_AP_Max[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_AP_Max[%d]=%s\n",i,DB_NAME_AP_Max[i]);
#endif
	}  
		
	strcpy(keyword,"Control_Lmt");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s %s\n",DB_NAME_P_UPLMT,DB_NAME_P_DOWNLMT);
	tmp = ReadDB_Chan ( DB_NAME_P_UPLMT );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n",DB_NAME_P_UPLMT);
		UnMount_handle();
	}
	tmp = ReadDB_Chan ( DB_NAME_P_DOWNLMT );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n",DB_NAME_P_DOWNLMT);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_P_UPLMT=%s,DB_NAME_P_DOWNLMT=%s\n",DB_NAME_P_UPLMT,DB_NAME_P_DOWNLMT);
#endif
        
	strcpy(keyword,"Plant_UN_RUN");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=3;i++)
	{
		fscanf(fp,"%s %s\n",DB_NAME_QCUNRUN_UPLMT[i],DB_NAME_QCUNRUN_DNLMT[i]);
		tmp = ReadDB_Chan ( DB_NAME_QCUNRUN_UPLMT[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_QCUNRUN_UPLMT[i]);
			UnMount_handle();
		}
		tmp = ReadDB_Chan ( DB_NAME_QCUNRUN_DNLMT[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_QCUNRUN_DNLMT[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_QCUNRUN_UPLMT[%d]=%s,DB_NAME_QCUNRUN_DNLMT[%d]=%s\n",i,DB_NAME_QCUNRUN_UPLMT[i],i,DB_NAME_QCUNRUN_DNLMT[i]);
#endif
	}

	strcpy(keyword,"ALM_Plant_UN_RUN");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_ALM_Plant_UN_RUN);
	tmp = ReadDB_Chan ( DB_NAME_ALM_Plant_UN_RUN );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_ALM_Plant_UN_RUN);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_ALM_Plant_UN_RUN=%s\n",DB_NAME_ALM_Plant_UN_RUN);
#endif 

	strcpy(keyword,"ALM_StatusErr");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_ALM_StatusErr);
	tmp = ReadDB_Chan ( DB_NAME_ALM_StatusErr );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_ALM_StatusErr);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_ALM_StatusErr=%s\n",DB_NAME_ALM_StatusErr);
#endif 

	strcpy(keyword,"Rt_Breaker_sta");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<=UNIT_NUMB;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_BREAKER_Status[i]);
		tmp = ReadDB_Chan ( DB_NAME_BREAKER_Status[i] );
		if ( tmp == DATA_ERR )
		{
			printf ( "AGC: %s is not found in Database!\n", DB_NAME_BREAKER_Status[i]);
			UnMount_handle();
		}
#ifdef DEBUG
	printf("DB_NAME_BREAKER_Status[%d]=%s\n",i,DB_NAME_BREAKER_Status[i]);
#endif
	}   

	strcpy(keyword,"ALM_YFKErr");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_ALM_YFKErr);
	tmp = ReadDB_Chan ( DB_NAME_ALM_YFKErr );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_ALM_YFKErr);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_ALM_YFKErr=%s\n",DB_NAME_ALM_YFKErr);
#endif

	strcpy(keyword,"AGC_FRUPLMT");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_FRUPLMT);
	tmp = ReadDB_Chan ( DB_NAME_AGC_FRUPLMT );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_FRUPLMT);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_FRUPLMT=%s\n",DB_NAME_AGC_FRUPLMT);
#endif 

	strcpy(keyword,"AGC_FRDOWNLMT");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_FRDOWNLMT);
	tmp = ReadDB_Chan ( DB_NAME_AGC_FRDOWNLMT );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_FRDOWNLMT);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_FRDOWNLMT=%s\n",DB_NAME_AGC_FRDOWNLMT);
#endif 

	strcpy(keyword,"AGC_REALFR");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	for(i=1;i<FREQUENCY_NUM+1;i++)
	{
		fscanf(fp,"%s\n",DB_NAME_AGC_RTFR[i]);
		tmp = ReadDB_Chan ( DB_NAME_AGC_RTFR[i] );
		if ( tmp == DATA_ERR )
		{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_RTFR[i]);
		UnMount_handle();
		}
#ifdef DEBUG
		printf("DB_NAME_AGC_RTFR[%d]=%s\n",i,DB_NAME_AGC_RTFR[i]);
#endif 
	}
	
	
	strcpy(keyword,"AGC_FRLOW_ERR");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_FRLOW_ERR);
	tmp = ReadDB_Chan ( DB_NAME_AGC_FRLOW_ERR );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_FRLOW_ERR);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_FRLOW_ERR=%s\n",DB_NAME_AGC_FRLOW_ERR);
#endif

	strcpy(keyword,"AGC_FRHIGH_ERR");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_FRHIGH_ERR);
	tmp = ReadDB_Chan ( DB_NAME_AGC_FRHIGH_ERR );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_FRHIGH_ERR);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_FRHIGH_ERR=%s\n",DB_NAME_AGC_FRHIGH_ERR);
#endif

	strcpy(keyword,"AGC_PLOW_ERR");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_PLOW_ERR);
	tmp = ReadDB_Chan ( DB_NAME_AGC_PLOW_ERR );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_PLOW_ERR);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_PLOW_ERR=%s\n",DB_NAME_AGC_PLOW_ERR);
#endif

	strcpy(keyword,"AGC_POVER_ERR");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_POVER_ERR);
	tmp = ReadDB_Chan ( DB_NAME_AGC_POVER_ERR );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_POVER_ERR);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_AGC_POVER_ERR=%s\n",DB_NAME_AGC_POVER_ERR);
#endif

	strcpy(keyword,"DD104_DOWN");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_DD104_DOWN);
	tmp = ReadDB_Chan ( DB_NAME_DD104_DOWN );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_DD104_DOWN);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_DD104_DOWN=%s\n",DB_NAME_DD104_DOWN);
#endif

	strcpy(keyword,"WATERINFO_ERR");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_WATERINFO_ERR);
	tmp = ReadDB_Chan ( DB_NAME_WATERINFO_ERR );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n", DB_NAME_WATERINFO_ERR);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_WATERINFO_ERR=%s\n",DB_NAME_WATERINFO_ERR);
#endif
	
	strcpy(keyword,"AGC_LMT_DB_ALM");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_LMT_DB_ALM);
	tmp = ReadDB_Chan ( DB_NAME_AGC_LMT_DB_ALM);
  	if ( tmp == DATA_ERR )
  	{
  		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_LMT_DB_ALM);
  		UnMount_handle();
  	}
#ifdef DEBUG
//	printf("AGC���Խ���������������ֵ����ʱ������=%s\n",DB_NAME_AGC_LMT_DB_ALM);
#endif

	strcpy(keyword,"AGC_COMP_DERECT");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_COMP_DERECT);
	tmp = ReadDB_Chan ( DB_NAME_AGC_COMP_DERECT);
  	if ( tmp == DATA_ERR )
  	{
  		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_COMP_DERECT);
  		UnMount_handle();
  	}
#ifdef DEBUG
//	printf("AGC���Խ���������������ֵ����ʱ�����������ɵķ���1Ϊ����2Ϊ��=%s\n",DB_NAME_AGC_COMP_DERECT);
#endif

	strcpy(keyword,"AGC_LMT_DB_ADVICE");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_AGC_LMT_DB_ADVICE);
	tmp = ReadDB_Chan ( DB_NAME_AGC_LMT_DB_ADVICE);
  	if ( tmp == DATA_ERR )
  	{
  		printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGC_LMT_DB_ADVICE);
  		UnMount_handle();
  	}
#ifdef DEBUG
//	printf("AGC���Խ���������������ֵ����ʱ�����ֶ������ĸ���ֵ=%s\n",DB_NAME_AGC_LMT_DB_ADVICE);
#endif

	strcpy(keyword,"AGC_MINOR_ADJ_P");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_MINOR_ADJ_P);
	tmp = ReadDB_Chan ( DB_NAME_MINOR_ADJ_P);
  	if ( tmp == DATA_ERR )
  	{
  		printf ( "AGC: %s is not found in Database!\n", DB_NAME_MINOR_ADJ_P);
  		UnMount_handle();
  	}
#ifdef DEBUG
//	printf("С�����仯������ֵ=%s\n",DB_NAME_MINOR_ADJ_P);
#endif

	strcpy(keyword,"SingleUnit_RemoteControl");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",StrTemp);
    PLANT.Remote_SingleUnit_Control=atoi(StrTemp);
	if((PLANT.Remote_SingleUnit_Control!=0)&&(PLANT.Remote_SingleUnit_Control!=1))
	{
		printf("ʡ���������ƹ��ܶ������!ֻ��Ϊ0��1!\n");
		UnMount_handle();
	}
#ifdef DEBUG
	printf("Remote_SingleUnit_Control=%d\n",PLANT.Remote_SingleUnit_Control);
#endif 
	if(PLANT.Remote_SingleUnit_Control==1)
  {
  	strcpy(keyword,"RemoteAGCOnLine");
	if(-1==LocateKeyword(fp,keyword))
		UnMount_handle();
	fscanf(fp,"%s\n",DB_NAME_RemoteAGCOnLine);
	tmp = ReadDB_Chan ( DB_NAME_RemoteAGCOnLine );
	if ( tmp == DATA_ERR )
	{
		printf ( "AGC: %s is not found in Database!\n",DB_NAME_RemoteAGCOnLine);
		UnMount_handle();
	}
#ifdef DEBUG
	printf("DB_NAME_RemoteAGCOnLine=%s\n",DB_NAME_RemoteAGCOnLine);
#endif

  	strcpy(keyword,"AP_RemoteControl");  	
  	if(-1==LocateKeyword(fp,keyword))
  		UnMount_handle();
  	for(i=1;i<=UNIT_NUMB;i++)
  	{
  		fscanf(fp,"%s\n",DB_NAME_SD_YK[i]);
  		tmp = ReadDB_Chan ( DB_NAME_SD_YK[i] );
  		if ( tmp == DATA_ERR )
  		{
  			printf ( "AGC: %s is not found in Database!\n", DB_NAME_SD_YK[i]);
  			UnMount_handle();
  		}
  #ifdef DEBUG
  	printf("DB_NAME_SD_YK[%d]=%s\n",i,DB_NAME_SD_YK[i]);
  #endif
  	} 
  	
  	strcpy(keyword,"Remote_SetUnitP");
  	if(-1==LocateKeyword(fp,keyword))
  		UnMount_handle();
  	for(i=1;i<=UNIT_NUMB;i++)
  	{
  		fscanf(fp,"%s\n",DB_NAME_SD_PSet[i]);
  		tmp = ReadDB_Chan ( DB_NAME_SD_PSet[i] );
  		if ( tmp == DATA_ERR )
  		{
  			printf ( "AGC: %s is not found in Database!\n", DB_NAME_SD_PSet[i]);
  			UnMount_handle();
  		}
  #ifdef DEBUG
  	printf("DB_NAME_SD_PSet[%d]=%s\n",i,DB_NAME_SD_PSet[i]);
  #endif
  	}
  	
  	strcpy(keyword,"Remote_SetUnitPLmt");
  	if(-1==LocateKeyword(fp,keyword))
  		UnMount_handle();
  	for(i=1;i<=UNIT_NUMB;i++)
  	{
  		fscanf(fp,"%s\n",DB_NAME_AGCYG_STEP[i]);
  		tmp = ReadDB_Chan ( DB_NAME_AGCYG_STEP[i] );
  		if ( tmp == DATA_ERR )
  		{
  			printf ( "AGC: %s is not found in Database!\n", DB_NAME_AGCYG_STEP[i]);
  			UnMount_handle();
  		}
  #ifdef DEBUG
  	printf("DB_NAME_AGCYG_STEP[%d]=%s\n",i,DB_NAME_AGCYG_STEP[i]);
  #endif
  	}
  	
  	strcpy(keyword,"Remote_OverPLmtALM");
  	if(-1==LocateKeyword(fp,keyword))
  		UnMount_handle();
  	for(i=1;i<=UNIT_NUMB;i++)
  	{
  		fscanf(fp,"%s\n",DB_NAME_Remote_OverPLmtALM[i]);
  		tmp = ReadDB_Chan ( DB_NAME_Remote_OverPLmtALM[i] );
  		if ( tmp == DATA_ERR )
  		{
  			printf ( "AGC: %s is not found in Database!\n", DB_NAME_Remote_OverPLmtALM[i]);
  			UnMount_handle();
  		}
  #ifdef DEBUG
  	printf("DB_NAME_Remote_OverPLmtALM[%d]=%s\n",i,DB_NAME_Remote_OverPLmtALM[i]);
  #endif
  	}
  	
  	strcpy(keyword,"Remote_OverBCLmtALM");
  	if(-1==LocateKeyword(fp,keyword))
  		UnMount_handle();
  	for(i=1;i<=UNIT_NUMB;i++)
  	{
  		fscanf(fp,"%s\n",DB_NAME_Remote_OverBCLmtALM[i]);
  		tmp = ReadDB_Chan ( DB_NAME_Remote_OverBCLmtALM[i] );
  		if ( tmp == DATA_ERR )
  		{
  			printf ( "AGC: %s is not found in Database!\n", DB_NAME_Remote_OverBCLmtALM[i]);
  			UnMount_handle();
  		}
  #ifdef DEBUG
  	printf("DB_NAME_Remote_OverBCLmtALM[%d]=%s\n",i,DB_NAME_Remote_OverBCLmtALM[i]);
  #endif
  	}
	}
	fclose(fp);
}

void   LogFileChangeDayAndWriteTime()
{
//	char   logfilename[50];
	FILE *fp;

	if( oldday != ntime->tm_mday )
	{
		oldday = ntime->tm_mday;
#ifdef SUNOS
    sprintf(logfilename, "/home/ems/h9000/his/agc/AGCcmd.%02d",ntime->tm_mday);
#else
	sprintf(logfilename, "/home/ems/h9000/his/agc/AGCcmd.%02d",ntime->tm_mday);
#endif
	    fp=fopen(logfilename, "w");
	    fclose(fp);
	}
}

void MoveP_Curve_At_Zero ()
{
	int     i, hour, host_assist;
	float   p_tomorrow;

	ReadTime ();
	hour = ntime->tm_hour;
	if( hour > 0 ) move_curve = NOT;

	host_assist = GetControlState();

	if(( hour == 0 )&&( move_curve == NOT )&&( host_assist==1))
	{
		move_curve = YES;
		for(i=1;i<=SCHEDULE;i++)
		{
			p_tomorrow = ReadDB_ANA (DB_NAME_Tomorrow_Curve[i]);
			
			AGC_UpdateRTDB_ANA ( DB_NAME_Today_Curve[i], p_tomorrow );
		}
	}
}

int GetLoadCurveTimeIndex()
{
	int	hour, minute;
	ReadTime ();
	hour = ntime->tm_hour*60/FHQX_INTERVAL;
	minute = ntime->tm_min/FHQX_INTERVAL;
	return(hour + minute);
}

void MoveRTP_Curve ()	
{
	int  index;
	float rt_curve;

	index=GetLoadCurveTimeIndex();  
	rt_curve = ReadDB_ANA (DB_NAME_Today_Curve[index] );
	
	AGC_UpdateRTDB_ANA ( DB_NAME_RT_P_Curve,  rt_curve );
	
}

void GetWaterLevel()
{
	short rt_status=0;

	Watermsg.UpWaterLevel=ReadDB_ANA(DB_NAME_Upstream_Level);

	Watermsg.DownWaterLevel=ReadDB_ANA(DB_NAME_Downstream_Level);

	PLANT.Manual_Set=ReadDB_IND(DB_NAME_Manual_Set);
//	PLANT.Manual_Set=1;		//��������ʵʱˮͷ��������

	if(!PLANT.Manual_Set)
	{
		Watermsg.WaterHead=Watermsg.UpWaterLevel-Watermsg.DownWaterLevel;
//		AGC_UpdateRTDB_ANA(DB_NAME_Water_Head, Watermsg.WaterHead );
	}
	else
	{
#ifdef PBG
		Watermsg.UpWaterLevel=ReadDB_ANA (DB_NAME_Water_Head );	//changed by fengxun for PBG,2010-09-22,�ٲ���������ˮλ��ֵ
#else
		Watermsg.WaterHead=ReadDB_ANA (DB_NAME_Water_Head );
#endif
	}

/*	if((Watermsg.WaterHead<MinWaterhead)||(Watermsg.WaterHead>MaxWaterhead))
		printf("%f  %f  %f ˮͷ���ݴ���!\n",Watermsg.WaterHead,MinWaterhead,MaxWaterhead);*/
	if((Watermsg.UpWaterLevel<MinWaterhead)||(Watermsg.UpWaterLevel>MaxWaterhead))
		printf("%f  %f  %f ˮλ���ݴ���!\n",Watermsg.WaterHead,MinWaterhead,MaxWaterhead);
}

void GetControlable_P_lmt() 
{
	float p_up_controlable,p_down_controlable;
	int i;

	p_up_controlable =0;
	p_down_controlable =0;


	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(PLANT.Auto_StartStop==1)
		{
			if(UNIT[i].AP_Avail==1)
			{
				p_up_controlable+=UNIT[i].AP_Max;
				p_down_controlable+=UNIT[i].AP_Min;
			}
			else if(UNIT[i].Status==UNIT_IN_GEN_AGC)
			{
				p_up_controlable+=UNIT[i].AP_RtValue;
				p_down_controlable+=UNIT[i].AP_RtValue;
			}
		}
		else
		{
			if(UNIT[i].Status==UNIT_IN_GEN_AGC)
			{
				if(UNIT[i].AP_Avail==1)
				{
					p_up_controlable+=UNIT[i].AP_Max;
					p_down_controlable+=UNIT[i].AP_Min;
				}
				else
				{
					p_up_controlable+=UNIT[i].AP_RtValue;
					p_down_controlable+=UNIT[i].AP_RtValue;
				}
			}
		}
	}
	
	AGC_UpdateRTDB_ANA ( DB_NAME_P_DOWNLMT ,p_down_controlable );
	AGC_UpdateRTDB_ANA ( DB_NAME_P_UPLMT ,p_up_controlable );
}

void Refresh_Manwatermsg()
{
	refre_time+=1;
	if(PLANT.Manual_Set!=1)
	{
		if(fabs(Watermsg.WaterHead-old_waterlevel)>2)	//�ֶ�����ˮλ��ʵ��ˮλ������2�ף�������Ϊ�ֶ�ˮͷ
		{
			AGC_UpdateRTDB_IND ( DB_NAME_Manual_Set ,YES );
			PLANT.Manual_Set=1;
			Watermsg.WaterHead=old_waterlevel;
		}
		else if(refre_time>=water_refresh_Period)	//ˢ���˹�����ˮλ������Ϊwater_refresh_Period
		{
			AGC_UpdateRTDB_ANA ( DB_NAME_Water_Head ,Watermsg.WaterHead );
			old_waterlevel=Watermsg.WaterHead;
			refre_time=0;
		}
	}
	old_waterlevel= Watermsg.WaterHead;
}

void Statistics_Unit()	/*����鹤����ע�⣺ʡ����������ʱ���鲻�ܳ��飡����*/
{
	int 	i,Num_AP_Avail,AGC_Generating,AGC_Standby;
	int		sbo_flag,unit_timeout,unit_jx;
	float	p_sum,p_sum_agc,p_sum_no_agc;
	float	gd_tmp;

	p_sum=0;
	p_sum_agc=0;
	p_sum_no_agc=0;
	Num_AP_Avail=0;
	AGC_Generating=0;
	AGC_Standby=0;
	PLANT.P_Balance=NOT;
/*	for(i=1;i<=UNIT_NUMB;i++)//�ж�ʡ���ܷ񵥻�����
	{
		UNIT[i].RemoteControlable=0;
		sbo_flag = ReadDB_IND(DB_NAME_SD_YK[i]);
		if(sbo_flag==1) UNIT[i].RemoteControlable=1; 

	}
        */
	for (i=1; i<=UNIT_NUMB;i++)
	{
		sbo_flag = ReadDB_IND ( DB_NAME_AP_CZKT[ i ] );
		UNIT[i].P_balance = ReadDB_IND ( DB_NAME_UNITP_BALANCE[ i ] );
		unit_timeout = ReadDB_IND ( DB_NAME_UNIT_OVERTIME[ i ] );
		unit_jx = ReadDB_IND ( DB_NAME_AGC_JZJX[ i ] );
		if((unit_timeout==1)||(unit_jx==1))
		{
			AGC_UpdateRTDB_IND  ( DB_NAME_AP_Group[i], NOT );
			sbo_flag=0;
		}
		if((UNIT[i].Status!=UNIT_IN_CHKOUT_AGC)&&(sbo_flag == 1 ))
		{
			if ( UNIT[i].Status == UNIT_IN_STANDBY_AGC )
			AGC_Standby++;
			else if (UNIT[i].Status == UNIT_IN_GEN_AGC )
			{
				AGC_Generating++;
				p_sum_agc+=UNIT[i].AP_RtValue;
			}
			UNIT[i].AP_Yggd=ReadDB_ANA(DB_NAME_AP_SetValue[i]);        //added by fengxun,2012-04-09
			UNIT[i].AP_Avail = 1;    
			Num_AP_Avail++;
		}
		else    
		{
			UNIT[i].AP_Avail = 0; 
			if (UNIT[i].Status == UNIT_IN_GEN_AGC )
			{
				gd_tmp = ReadDB_ANA(DB_NAME_AP_SetValue[i]);        //added by fengxun,2012-04-09
				if(UNIT[i].P_balance==YES) 					
				{
					PLANT.P_Balance=YES;					
					if((fabs(gd_tmp-UNIT[i].AP_Yggd)>PLANT.AP_Deadband)&&(NoAGCUnit_flag!=1))	//�й�����ֵ�����仯
					{
						PLANT.P_Yggd_ChangeValue+=UNIT[i].AP_Yggd-gd_tmp;												
						NoAGCUnit_flag=1;
					}
					UNIT[i].AP_Yggd=gd_tmp;
					UNIT[i].AP_Setp=UNIT[i].AP_Yggd;
					p_sum_no_agc+=UNIT[i].AP_Yggd;
				}
				else
				{
					p_sum_no_agc+=UNIT[i].AP_RtValue;
					UNIT[i].AP_Setp=UNIT[i].AP_RtValue;
				}				
			}
			else
			UNIT[i].AP_Setp=0;
			if(UNIT[i].RemoteControlable!=1)    /*���鲻��Զ��ң��*/
			{
				AGC_UpdateRTDB_ANA (DB_NAME_Optimization_Value[i], UNIT[i].AP_RtValue );
			}
		}

/*		if(UNIT[i].AP_Avail!=1)
		{
			UNIT[i].AP_Avail=0;
			printf("******************UNIT[%d].AP_Avail=%d\n",i,UNIT[i].AP_Avail);
			AGC_UpdateRTDB_IND  ( DB_NAME_AP_Group[i], NOT );
		}
		AGC_UpdateRTDB_IND  ( DB_NAME_AP_CZKT[i], UNIT[i].AP_Avail );*///removed by fengxun,2008-12-27
	}

	p_sum=p_sum_agc+p_sum_no_agc;
	PLANT.p_sum=p_sum;
	PLANT.AGC_Standby=AGC_Standby;
	PLANT.AGC_Generating=AGC_Generating;
	PLANT.p_sum_agc=p_sum_agc;
	PLANT.Num_AP_Avail=Num_AP_Avail;
	PLANT.p_sum_no_agc=p_sum_no_agc;  
	if(Num_AP_Avail == 0)
	{
		AGC_UpdateRTDB_ANA ( DB_NAME_AP_Setpoint, PLANT.p_sum);
#ifndef HuaZhongWangDiao
		//yyp
		AGC_UpdateRTDB_ANA ( DB_NAME_Remote_Setpoint, PLANT.p_sum);
#endif
	}
}

void GetPlantSetpointValue()
{
	int RemoteAGCOnLine;
	PLANT.AP_Setpoint=PLANT.p_sum;
	PLANT.Mode=AGC_MODE_NONE;

	if(PLANT.Control_Right==1)
	{
		/*RemoteAGCOnLine=ReadDB_IND(DB_NAME_RemoteAGCOnLine);*//*ʡ���Բ���ʡ�������ź��͸��糧ʱ*/
		RemoteAGCOnLine=1;      /*ʡ���Բ���ʡ�������ź��͸��糧ʱ*/
		printf("AGC����Զ������ģʽ�� \n",RemoteAGCOnLine);
		if((RemoteAGCOnLine==1)&&(PLANT.AP_Setting==1))		/*������Ȩ��Զ����ȫ������Ͷ��ʱ*/
		{
			PLANT.AP_Setpoint=ReadDB_ANA(DB_NAME_Remote_Setpoint);
			printf("Զ������ȫ���й�=%6.2f\n",PLANT.AP_Setpoint);
			PLANT.Mode=AGC_MODE_AP_Setpoint;
		}
		else
			PLANT.Mode=AGC_MODE_NONE;
	}
	else 
	{
		  
		if(PLANT.AP_Setting==1)
		{
			PLANT.AP_Setpoint=ReadDB_ANA(DB_NAME_AP_Setpoint);			
			PLANT.Mode=AGC_MODE_AP_Setpoint;
		}
		else if(PLANT.AP_Curve==1)
		{
			PLANT.AP_Setpoint=ReadDB_ANA(DB_NAME_RT_P_Curve);
			PLANT.Mode=AGC_MODE_AP_Curve;
		}
		else
			PLANT.AP_Setpoint=PLANT.p_sum;
	}
	/*������������ں���CheckFault()��Ҳ�ٴν������ж�*/
/*	if(PLANT.AP_Setpoint>PLANT.AP_Max+1)	//1MWΪ����
	{
		PLANT.AP_Setpoint=PLANT.p_sum;
//		AGC_UpdateRTDB_IND ( DB_NAME_AGC_POVER_ERR, YES);
	}
	if(PLANT.AP_Setpoint<PLANT.AP_Min-1)	//1MWΪ����
	{
		PLANT.AP_Setpoint=PLANT.p_sum;
//		AGC_UpdateRTDB_IND ( DB_NAME_AGC_PLOW_ERR, YES);
	}
  if(fabs(PLANT.AP_Setpoint-PLANT.p_sum)>PLANT.AP_ChangeMax)
	{
		PLANT.AP_Setpoint=PLANT.p_sum;
//		AGC_UpdateRTDB_IND ( DB_NAME_ALM_ChangeMax, YES);
	}
*/
	
	if((PLANT.Control_Right==1)&&(PLANT.AP_Setting==1))
	{
		AGC_UpdateRTDB_ANA ( DB_NAME_AP_Setpoint, PLANT.AP_Setpoint );}
#ifndef HuaZhongWangDiao
	else if(PLANT.AP_Setting==1)
		//yyp
		AGC_UpdateRTDB_ANA ( DB_NAME_Remote_Setpoint,PLANT.AP_Setpoint ); //removed by fengxun,2010-6-9
#endif
	else if(PLANT.AP_Curve==1)
	{
		AGC_UpdateRTDB_ANA ( DB_NAME_AP_Setpoint, PLANT.AP_Setpoint );
		//yyp
		AGC_UpdateRTDB_ANA ( DB_NAME_Remote_Setpoint, PLANT.AP_Setpoint );
	}
}

float GetRTSumPower()			/*added by fengxun,for JM,2007-12-17*/
{
	int i;
	float Sum=0;
	for(i=1;i<=UNIT_NUMB;i++)
	{		
		if(ReadDB_IND(DB_NAME_Rt_Status[i])==UNIT_IN_GEN_AGC)
		{
			UNIT[i].AP_RtValue=ReadDB_ANA(DB_NAME_AP_RtValue[i]);
			Sum+=UNIT[i].AP_RtValue;
		}
	}
	return(Sum);
}

void GetUnitRunArea()
{
	int i,j,tmp,Find;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		for(j=1;j<=UNIT[i].VibrationNum;j++)
		{
			if((UNIT[i].AP_Min>=UNIT[i].Low_Vibration[j])&&(UNIT[i].AP_Min<UNIT[i].Up_Vibration[j]))
				UNIT[i].AP_Min=UNIT[i].Up_Vibration[j];
			if((UNIT[i].AP_Max<=UNIT[i].Up_Vibration[j])&&(UNIT[i].AP_Max>UNIT[i].Low_Vibration[j]))
				UNIT[i].AP_Max=UNIT[i].Low_Vibration[j];
#ifndef PBG
			if(ManSetLmt==1)	//removed by fengxun for PBG,2010-09-19
			{
				AGC_UpdateRTDB_ANA ( DB_NAME_Low_Vibration[i][j], UNIT[i].Low_Vibration[j] );
				AGC_UpdateRTDB_ANA ( DB_NAME_Up_Vibration[i][j], UNIT[i].Up_Vibration[j] );
			}
#endif
		}
	}
	for(i=1;i<=UNIT_NUMB;i++)
	{
		Find=0;
		if(UNIT[i].VibrationNum==0)
		{
			UNIT[i].CurrentUplmt=UNIT[i].AP_Max;
			UNIT[i].CurrentLowlmt=UNIT[i].AP_Min;
			Find=1;
			break;
		}
		for(j=1;j<=UNIT[i].VibrationNum;j++)
		{
			if(UNIT[i].Low_Vibration[j]==UNIT[i].Up_Vibration[j])
			continue;
			tmp=(UNIT[i].Low_Vibration[j]+UNIT[i].Up_Vibration[j])/2;
//			printf("UNIT[%d].AP_Setp=%d,UNIT[%d].AP_RtValue=%f,tmp=%d\n",i,UNIT[i].AP_Setp,i,UNIT[i].AP_RtValue,tmp);
			if(UNIT[i].AP_Setp<tmp) 
//			if(UNIT[i].AP_RtValue<=tmp) //changed by fengxun,2010-09-23
			{
				if(j==1)
				{
					UNIT[i].CurrentUplmt=UNIT[i].Low_Vibration[j];
					UNIT[i].CurrentLowlmt=UNIT[i].AP_Min;
				}
				else 
				{
					UNIT[i].CurrentUplmt=UNIT[i].Low_Vibration[j];
					UNIT[i].CurrentLowlmt=UNIT[i].Up_Vibration[j-1];
				}
				Find=1;
				break;
			}
		}
		if(Find==0)
		{
			UNIT[i].CurrentUplmt=UNIT[i].AP_Max;
			UNIT[i].CurrentLowlmt=UNIT[i].Up_Vibration[UNIT[i].VibrationNum];
		}
	}
}

void GetResultSpace_1Unit()
{
	int i,k;
	k=1;
	for(i=1;i<=UNIT_NUMB;i++)	
	{
		if(UNIT[i].AP_Avail==1)	//�������Ŀ���������
		{	
			if(UNIT[i].VibrationNum==0)
			{
				result_space1[k].unit_id=i;
				result_space1[k].range_id=1;
				result_space1[k].p_range.range_p_dn=UNIT[i].AP_Min;
				result_space1[k].p_range.range_p_up=UNIT[i].AP_Max;
				k++;
			}
			else if(UNIT[i].VibrationNum==1)
			{
				result_space1[k].unit_id=i;
				result_space1[k].range_id=1;
				result_space1[k].p_range.range_p_dn=UNIT[i].AP_Min;
				result_space1[k].p_range.range_p_up=UNIT[i].Low_Vibration[1];
				k++;
				result_space1[k].unit_id=i;
				result_space1[k].range_id=2;
				result_space1[k].p_range.range_p_dn=UNIT[i].Up_Vibration[1];
				result_space1[k].p_range.range_p_up=UNIT[i].AP_Max;
				k++;
			}
			else if(UNIT[i].VibrationNum==2)
			{
				result_space1[k].unit_id=i;
				result_space1[k].range_id=1;
				result_space1[k].p_range.range_p_dn=UNIT[i].AP_Min;
				result_space1[k].p_range.range_p_up=UNIT[i].Low_Vibration[1];
				k++;
				result_space1[k].unit_id=i;
				result_space1[k].range_id=2;
				result_space1[k].p_range.range_p_dn=UNIT[i].Up_Vibration[1];
				result_space1[k].p_range.range_p_up=UNIT[i].Low_Vibration[2];
				k++;
				result_space1[k].unit_id=i;
				result_space1[k].range_id=3;
				result_space1[k].p_range.range_p_dn=UNIT[i].Up_Vibration[2];
				result_space1[k].p_range.range_p_up=UNIT[i].AP_Max;
				k++;				
			}
		}
	}
	spnum_1U=k-1;
}

void GetResultSpace_2Unit()	//����̨����Ľ�ռ�
{
	int i,j,k;
	k=1;
	for(i=1;i<=spnum_1U;i++)
	{
		for(j=i+1;j<=spnum_1U;j++)
		{
			if(result_space1[i].unit_id<result_space1[j].unit_id)	//��������������
			{
				result_space2[k].spa1_id=i;	//����1������ռ���
				result_space2[k].spa2_id=j;	//��һ̨����2�ĵ�����ռ���
				result_space2[k].p_range.range_p_dn=result_space1[i].p_range.range_p_dn+result_space1[j].p_range.range_p_dn;
				result_space2[k].p_range.range_p_up=result_space1[i].p_range.range_p_up+result_space1[j].p_range.range_p_up;
				k++;
			}
			else
				continue;
		}	
	}
	spnum_2U=k-1;
}

void GetResultSpace_3Unit()	//����̨����Ľ�ռ�
{
	int i,j,k;
	int id1_2U,id2_2U,id_1U;
	k=1;
	for(i=1;i<=spnum_2U;i++)
	{
		id1_2U=result_space1[result_space2[i].spa1_id].unit_id;
		id2_2U=result_space1[result_space2[i].spa2_id].unit_id;
		for(j=1;j<=spnum_1U;j++)
		{
			id_1U=result_space1[j].unit_id;
			if(id_1U>id2_2U)	//��>����Ϊ�˱����ظ����㣬�γ��ظ��Ľ�ռ䣬��(result_space2[1],result_space1[7])��(result_space2[7],result_space1[4])�����ظ���,��Ϊ(����1��һ��������+����2��һ��������+����3��һ��������)
			{
				result_space3[k].spaU2_id=i;	//��̨������ɵĽ�ռ�ı��
				result_space3[k].spaU1_id=j;	//��һ̨����2�ĵ�����ռ���
				result_space3[k].p_range.range_p_dn=result_space2[i].p_range.range_p_dn+result_space1[j].p_range.range_p_dn;
				result_space3[k].p_range.range_p_up=result_space2[i].p_range.range_p_up+result_space1[j].p_range.range_p_up;
				k++;
			}
			else
				continue;
		}
	}
	spnum_3U=k-1;
}

void GetResultSpace_4Unit()	//����̨����Ľ�ռ�
{
	int i,j,k;
	int id1_3U,id2_3U,id3_3U,id_1U;
	int tmpid;
	k=1;
	for(i=1;i<=spnum_3U;i++)
	{
		tmpid=result_space3[i].spaU2_id;
		id1_3U=result_space1[result_space2[tmpid].spa1_id].unit_id;
		id2_3U=result_space1[result_space2[tmpid].spa2_id].unit_id;
		id3_3U=result_space1[result_space3[i].spaU1_id].unit_id;
		for(j=1;j<=spnum_1U;j++)
		{
			id_1U=result_space1[j].unit_id;
			if(id_1U>id3_3U)
			{
				result_space4[k].spaU3_id=i;	//����1������ռ���
				result_space4[k].spaU1_id=j;	//��һ̨����2�ĵ�����ռ���
				result_space4[k].p_range.range_p_dn=result_space3[i].p_range.range_p_dn+result_space1[j].p_range.range_p_dn;
				result_space4[k].p_range.range_p_up=result_space3[i].p_range.range_p_up+result_space1[j].p_range.range_p_up;
				k++;
			}
			else
				continue;
		}
	}
	spnum_4U=k-1;
}

int AdjustInRange(int num_unit,int adjust_p )  //��Check_PreAllocat()�������ƣ��������������Ļ������С��������
{
	int i;
	int unit_rl_up[MAX_UNIT_NUMB+1],unit_rl_dn[MAX_UNIT_NUMB+1]; //�����ڲ���Խ���������µ�����������
	int tmp,tmp1,sum_p,prv_id;

	for(i=1;i<=UNIT_NUMB;i++)
	{
		unit_rl_up[i]=UNIT[i].CurrentUplmt-UNIT[i].AP_Setp;
		unit_rl_dn[i]=UNIT[i].AP_Setp-UNIT[i].CurrentLowlmt;
		minor_adjust_p_tmp[i]=UNIT[i].AP_Setp;
	}

	tmp=abs(adjust_p);

	if(adjust_p>0)  //����������ȼ����з��䣨��������Ŀ��ֵС�ڵ�ǰ����Խ�����ɵ��������ޣ�
	{
		for(i=1;i<=num_unit;i++)
		{
			prv_id=minor_adjust[i];
			if((unit_rl_up[prv_id]<AP_Adj_Step[prv_id])&&(unit_rl_up[prv_id]<tmp))
			{
				minor_adjust_p_tmp[prv_id]=UNIT[prv_id].CurrentUplmt;
				tmp-=unit_rl_up[prv_id];
				unit_rl_up[prv_id]=0;
			}
			else if((unit_rl_up[prv_id]>=AP_Adj_Step[prv_id])&&(tmp>=AP_Adj_Step[prv_id]))
			{
				minor_adjust_p_tmp[prv_id]+=AP_Adj_Step[prv_id];
				tmp-=AP_Adj_Step[prv_id];
				unit_rl_up[prv_id]-=AP_Adj_Step[prv_id];
			}
			else
			{
				minor_adjust_p_tmp[prv_id]+=tmp;
				tmp=0;
			}
			if((i==PLANT.Num_AP_Avail)&&(tmp>=1))
			{	
				i=0;
				if(tmp==tmp1) return(YES);
				tmp1=tmp;
			}
		}
	}
	else if(adjust_p<0)  //����������ȼ����з��䣨��������Ŀ��ֵ���ڵ�ǰ����Խ�����ɵ��������ޣ�
	{
		for(i=1;i<=num_unit;i++)
		{
			prv_id=minor_adjust[i];
			if((unit_rl_dn[prv_id]<AP_Adj_Step[prv_id])&&(unit_rl_dn[prv_id]<tmp))
			{
				minor_adjust_p_tmp[prv_id]=UNIT[prv_id].CurrentLowlmt;
				tmp-=unit_rl_dn[prv_id];
				unit_rl_dn[prv_id]=0;
			}
			else if((unit_rl_dn[prv_id]>=AP_Adj_Step[prv_id])&&(tmp>=AP_Adj_Step[prv_id]))
			{
				minor_adjust_p_tmp[prv_id]-=AP_Adj_Step[prv_id];
				tmp-=AP_Adj_Step[prv_id];
				unit_rl_dn[prv_id]-=AP_Adj_Step[prv_id];
			}
			else
			{
				minor_adjust_p_tmp[prv_id]-=tmp;
				tmp=0;
			}
			if((i==PLANT.Num_AP_Avail)&&(tmp>=1))
			{	
				i=0;
				if(tmp==tmp1) return(YES);
				tmp1=tmp;
			}
		}
	}
	return(YES);
}

void Check_P_Space2U(int id1,int id2,int Pset)
{
	int i,unit_id1,unit_id2;
	int du1_dn,du1_up,du2_dn,du2_up;
	int du2_u1dn,du2_u1up,du1_u2dn,du1_u2up;
	int p_U1,p_U2;
	int dx[5],tmp; /*���н⵽��ǰֵ�ķ�����Թ��ƽ�ĺû�*/
	int	Uplmt,Lowlmt,Sum_P,adjust_p;
	P_SPA_Unit_RESULT unit_tmp1[5],unit_tmp2[5];
		
	unit_id1=result_space1[id1].unit_id;
	unit_id2=result_space1[id2].unit_id;
	p_U1=UNIT[unit_id1].AP_Setp;
	p_U2=UNIT[unit_id2].AP_Setp;
	Sum_P=p_U1+p_U2;     //�������п�Խ��������̨���鰴���ȼ�������㣬����������
	Uplmt=UNIT[unit_id1].CurrentUplmt+UNIT[unit_id2].CurrentUplmt;
	Lowlmt=UNIT[unit_id1].CurrentLowlmt+UNIT[unit_id2].CurrentLowlmt;
	if(Pset<=Uplmt && Pset>=Lowlmt)
	{		
		if(UNIT[unit_id1].Privilege<UNIT[unit_id2].Privilege)
		{
			minor_adjust[1]=unit_id1;
			minor_adjust[2]=unit_id2;
		}
		else
		{
			minor_adjust[1]=unit_id2;
			minor_adjust[2]=unit_id1;
		}
		adjust_p=Pset-Sum_P;
		if(AdjustInRange(2,adjust_p)==YES)
		{
			tmp_space_result.Unit_Result[1].unit_id=unit_id1;
			tmp_space_result.Unit_Result[1].unit_P=minor_adjust_p_tmp[unit_id1];
			tmp_space_result.Unit_Result[2].unit_id=unit_id2;
			tmp_space_result.Unit_Result[2].unit_P=minor_adjust_p_tmp[unit_id2];
			tmp_space_result.dx=pow((p_U1-tmp_space_result.Unit_Result[1].unit_P),2)*UNIT[unit_id1].Privilege
				               +pow((p_U2-tmp_space_result.Unit_Result[2].unit_P),2)*UNIT[unit_id2].Privilege;
			if(tmp_space_result.Unit_Result[1].unit_P+tmp_space_result.Unit_Result[2].unit_P==Pset) return;
		}
	}

	for(i=1;i<5;i++) dx[i]=INFI;
	/*ע�⣬����ⶼ����ȷ��һ�����������޻����޵Ľ⣬Ȼ��ó���һ���������������ͬ�Ļ���*/
	/*��һ��⣬Unit1�Ľ�Ϊdu1_dn��Unit2�Ľ�Ϊdu2_u1dn*/
	du1_dn=result_space1[id1].p_range.range_p_dn;	//
	du2_u1dn=Pset-du1_dn;

	/*�ڶ���⣬Unit1�Ľ�Ϊdu1_up��Unit2�Ľ�Ϊdu2_u1up*/
	du1_up=result_space1[id1].p_range.range_p_up;
	du2_u1up=Pset-du1_up;

	/*������⣬Unit1�Ľ�Ϊdu2_dn��Unit2�Ľ�Ϊdu1_u2dn*/
	du2_dn=result_space1[id2].p_range.range_p_dn;
	du1_u2dn=Pset-du2_dn;

	/*������⣬Unit1�Ľ�Ϊdu2_up��Unit2�Ľ�Ϊdu1_u2up*/
	du2_up=result_space1[id2].p_range.range_p_up;
	du1_u2up=Pset-du2_up;

	/*�ֱ���������м��*/
	if(((p_U1<du1_dn)||(p_U1>=du1_dn && p_U1<=du1_up))&&(du2_u1dn<du2_up))	
	{
		unit_tmp1[1].unit_id=unit_id1;
		unit_tmp1[1].unit_P=du1_dn;
		unit_tmp2[1].unit_id=unit_id2;
		unit_tmp2[1].unit_P=du2_u1dn;
//		dx[1]=pow((p_U1-du1_dn),2)+pow((p_U2-du2_u1dn),2);  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[1]=pow((p_U1-du1_dn),2)*UNIT[unit_id1].Privilege+pow((p_U2-du2_u1dn),2)*UNIT[unit_id2].Privilege;
	}

	if(((p_U1>du1_up)||(p_U1>=du1_dn && p_U1<=du1_up))&&(du2_u1up>du2_dn))	
	{
		unit_tmp1[2].unit_id=unit_id1;
		unit_tmp1[2].unit_P=du1_up;
		unit_tmp2[2].unit_id=unit_id2;
		unit_tmp2[2].unit_P=du2_u1up;
//		dx[2]=pow((p_U1-du1_up),2)+pow((p_U2-du2_u1up),2);  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[2]=pow((p_U1-du1_up),2)*UNIT[unit_id1].Privilege+pow((p_U2-du2_u1up),2)*UNIT[unit_id2].Privilege;  
	}

	if(((p_U2<du2_dn)||(p_U2>=du2_dn && p_U2<=du2_up))&&(du1_u2dn<du1_up))	
	{
		unit_tmp1[3].unit_id=unit_id1;
		unit_tmp1[3].unit_P=du1_u2dn;
		unit_tmp2[3].unit_id=unit_id2;
		unit_tmp2[3].unit_P=du2_dn;
//		dx[3]=pow((p_U2-du2_dn),2)+pow((p_U1-du1_u2dn),2);  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[3]=pow((p_U2-du2_dn),2)*UNIT[unit_id2].Privilege+pow((p_U1-du1_u2dn),2)*UNIT[unit_id1].Privilege;
	}

	if(((p_U2>du2_up)||(p_U2>=du2_dn && p_U2<=du2_up))&&(du1_u2up>du1_dn))	
	{
		unit_tmp1[4].unit_id=unit_id1;
		unit_tmp1[4].unit_P=du1_u2up;
		unit_tmp2[4].unit_id=unit_id2;
		unit_tmp2[4].unit_P=du2_up;
//		dx[4]=pow((p_U2-du2_up),2)+pow((p_U1-du1_u2up),2);  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[4]=pow((p_U2-du2_up),2)*UNIT[unit_id2].Privilege+pow((p_U1-du1_u2up),2)*UNIT[unit_id1].Privilege;
	}
	tmp=dx[1];
	for(i=1;i<5;i++)
	{
		if((tmp>=dx[i])&&(dx[i]!=INFI))
		{
			tmp_space_result.Unit_Result[1].unit_id=unit_tmp1[i].unit_id;
			tmp_space_result.Unit_Result[1].unit_P=unit_tmp1[i].unit_P;
			tmp_space_result.Unit_Result[2].unit_id=unit_tmp2[i].unit_id;
			tmp_space_result.Unit_Result[2].unit_P=unit_tmp2[i].unit_P;
			tmp_space_result.dx=dx[i];
			tmp=dx[i];
		}
	}
}

void Check_P_Space3U(int id2U,int id1U,int Pset)	//id2UΪ��̨����Ľ�ռ��ţ�id1UΪ��һ̨����Ľ�ռ���
{
	int i,unit_id1,unit_id2,unit_id3;
	int spa1_2U,spa2_2U;
	float p_2U,p_1U;
	int du1_dn,du1_up,du2_dn,du2_up;
	int du2_u1dn,du2_u1up,du1_u2dn,du1_u2up;
	int dx[10];
	int tmp; /*���н⵽��ǰֵ�ķ�����Թ��ƽ�ĺû�*/
	P_SPA_Unit_RESULT unit_tmp1[5],unit_tmp2[5],unit_tmp3[5];
	
	spa1_2U=result_space2[id2U].spa1_id;	//��̨����Ľ�ռ��зֱ�̨����Ľ�ռ���
	spa2_2U=result_space2[id2U].spa2_id;
	unit_id1=result_space1[spa1_2U].unit_id;  //��̨����Ľ�ռ��е�̨����ֱ��Ӧ�Ļ����
	unit_id2=result_space1[spa2_2U].unit_id;
	unit_id3=result_space1[id1U].unit_id;	
	p_2U=UNIT[unit_id1].AP_Setp+UNIT[unit_id2].AP_Setp;	
	p_1U=UNIT[unit_id3].AP_Setp;
	for(i=1;i<10;i++) dx[i]=INFI;
	/*ע�⣬����ⶼ����ȷ��һ�����������޻����޵Ľ⣬Ȼ��ó���һ����������һ������̨����ģ�һ����һ̨�����*/
	/*��һ��⣬Unit1�Ľ�Ϊdu1_dn��Unit2�Ľ�Ϊdu2_u1dn*/
	du1_dn=result_space2[id2U].p_range.range_p_dn;
	du2_u1dn=Pset-du1_dn;

	/*�ڶ���⣬Unit1�Ľ�Ϊdu1_up��Unit2�Ľ�Ϊdu2_u1up*/
	du1_up=result_space2[id2U].p_range.range_p_up;
	du2_u1up=Pset-du1_up;

	/*������⣬Unit1�Ľ�Ϊdu2_dn��Unit2�Ľ�Ϊdu1_u2dn*/
	du2_dn=result_space1[id1U].p_range.range_p_dn;
	du1_u2dn=Pset-du2_dn;

	/*������⣬Unit1�Ľ�Ϊdu2_up��Unit2�Ľ�Ϊdu1_u2up*/
	du2_up=result_space1[id1U].p_range.range_p_up;
	du1_u2up=Pset-du2_up;

	/*�ֱ���������м��*/
	if(((p_2U<du1_dn)||(p_2U>=du1_dn && p_2U<=du1_up))&&(du2_u1dn<du2_up))
	{		
		unit_tmp1[1].unit_id=unit_id1;
		unit_tmp1[1].unit_P=result_space1[spa1_2U].p_range.range_p_dn;
		unit_tmp2[1].unit_id=unit_id2;
		unit_tmp2[1].unit_P=result_space1[spa2_2U].p_range.range_p_dn;
		unit_tmp3[1].unit_id=unit_id3;
		unit_tmp3[1].unit_P=du2_u1dn;
/*		dx[1]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[1].unit_P),2)
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[1].unit_P),2)
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[1].unit_P),2);*/  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[1]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[1].unit_P),2)*UNIT[unit_id1].Privilege
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[1].unit_P),2)*UNIT[unit_id2].Privilege
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[1].unit_P),2)*UNIT[unit_id3].Privilege;
	}

	if(((p_2U>du1_up)||(p_2U>=du1_dn && p_2U<=du1_up))&&(du2_u1up>du2_dn))
	{
		unit_tmp1[2].unit_id=unit_id1;
		unit_tmp1[2].unit_P=result_space1[spa1_2U].p_range.range_p_up;
		unit_tmp2[2].unit_id=unit_id2;
		unit_tmp2[2].unit_P=result_space1[spa2_2U].p_range.range_p_up;
		unit_tmp3[2].unit_id=unit_id3;
		unit_tmp3[2].unit_P=du2_u1up;
/*		dx[2]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[2].unit_P),2)
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[2].unit_P),2)
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[2].unit_P),2); */  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[2]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[2].unit_P),2)*UNIT[unit_id1].Privilege
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[2].unit_P),2)*UNIT[unit_id2].Privilege
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[2].unit_P),2)*UNIT[unit_id3].Privilege;
	}

	if(((p_1U<du2_dn)||(p_1U>=du2_dn && p_1U<=du2_up))&&(du1_u2dn<du1_up))	
	{
		Check_P_Space2U(spa1_2U,spa2_2U,du1_u2dn);
		unit_tmp1[3].unit_id=tmp_space_result.Unit_Result[1].unit_id;
		unit_tmp1[3].unit_P=tmp_space_result.Unit_Result[1].unit_P;
		unit_tmp2[3].unit_id=tmp_space_result.Unit_Result[2].unit_id;
		unit_tmp2[3].unit_P=tmp_space_result.Unit_Result[2].unit_P;
		unit_tmp3[3].unit_id=unit_id3;
		unit_tmp3[3].unit_P=du2_dn;
/*		dx[3]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[3].unit_P),2)
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[3].unit_P),2)
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[3].unit_P),2); */  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[3]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[3].unit_P),2)*UNIT[unit_id1].Privilege
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[3].unit_P),2)*UNIT[unit_id2].Privilege
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[3].unit_P),2)*UNIT[unit_id3].Privilege;
	}

	if(((p_1U>du2_up)||(p_1U>=du2_dn && p_1U<=du2_up))&&(du1_u2up>du1_dn))	
	{
		Check_P_Space2U(spa1_2U,spa2_2U,du1_u2up);
		unit_tmp1[4].unit_id=tmp_space_result.Unit_Result[1].unit_id;
		unit_tmp1[4].unit_P=tmp_space_result.Unit_Result[1].unit_P;
		unit_tmp2[4].unit_id=tmp_space_result.Unit_Result[2].unit_id;
		unit_tmp2[4].unit_P=tmp_space_result.Unit_Result[2].unit_P;
		unit_tmp3[4].unit_id=unit_id3;
		unit_tmp3[4].unit_P=du2_up;
/*		dx[4]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[4].unit_P),2)
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[4].unit_P),2)
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[4].unit_P),2); */  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[4]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[4].unit_P),2)*UNIT[unit_id1].Privilege
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[4].unit_P),2)*UNIT[unit_id2].Privilege
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[4].unit_P),2)*UNIT[unit_id3].Privilege;
	}
	tmp=INFI;
	for(i=1;i<5;i++)
	{
		if((tmp>=dx[i])&&(dx[i]!=INFI))
		{
			tmp_space_result.Unit_Result[1].unit_id=unit_tmp1[i].unit_id;
			tmp_space_result.Unit_Result[1].unit_P=unit_tmp1[i].unit_P;
			tmp_space_result.Unit_Result[2].unit_id=unit_tmp2[i].unit_id;
			tmp_space_result.Unit_Result[2].unit_P=unit_tmp2[i].unit_P;
			tmp_space_result.Unit_Result[3].unit_id=unit_tmp3[i].unit_id;
			tmp_space_result.Unit_Result[3].unit_P=unit_tmp3[i].unit_P;
			tmp_space_result.dx=dx[i];
			tmp=dx[i];
		}
	}
}

void Check_P_Space4U(int id3U,int id1U,int Pset)	//id3UΪ��̨����Ľ�ռ��ţ�id1UΪ��һ̨����Ľ�ռ���
{
	int i,unit_id1,unit_id2,unit_id3,unit_id4;
	int spa1_3U,spa2_3U,spa3_3U;
	int spa1_2U,spa2_2U;
	float p_3U,p_1U;
	int du1_dn,du1_up,du2_dn,du2_up;
	int du2_u1dn,du2_u1up,du1_u2dn,du1_u2up;
	int dx[10];
	int tmp; /*���н⵽��ǰֵ�ķ�����Թ��ƽ�ĺû�*/
	P_SPA_Unit_RESULT unit_tmp1[5],unit_tmp2[5],unit_tmp3[5],unit_tmp4[5];
	
	spa1_3U=result_space3[id3U].spaU2_id;	//��̨����Ľ�ռ��зֱ�̨����Ľ�ռ���
	spa2_3U=result_space3[id3U].spaU1_id;
	spa1_2U=result_space2[spa1_3U].spa1_id;
	spa2_2U=result_space2[spa1_3U].spa2_id;
	unit_id1=result_space1[spa1_2U].unit_id;  //��̨����Ľ�ռ��е�̨����ֱ��Ӧ�Ļ����
	unit_id2=result_space1[spa2_2U].unit_id;
	unit_id3=result_space1[spa2_3U].unit_id;
	unit_id4=result_space1[id1U].unit_id;
	
	p_3U=UNIT[unit_id1].AP_Setp+UNIT[unit_id2].AP_Setp+UNIT[unit_id3].AP_Setp;	
	p_1U=UNIT[unit_id4].AP_Setp;
	for(i=1;i<10;i++) dx[i]=INFI;
	/*ע�⣬����ⶼ����ȷ��һ�����������޻����޵Ľ⣬Ȼ��ó���һ����������һ������̨����ģ�һ����һ̨�����*/
	/*��һ��⣬Unit1�Ľ�Ϊdu1_dn��Unit2�Ľ�Ϊdu2_u1dn*/
	du1_dn=result_space3[id3U].p_range.range_p_dn;
	du2_u1dn=Pset-du1_dn;

	/*�ڶ���⣬Unit1�Ľ�Ϊdu1_up��Unit2�Ľ�Ϊdu2_u1up*/
	du1_up=result_space3[id3U].p_range.range_p_up;
	du2_u1up=Pset-du1_up;

	/*������⣬Unit1�Ľ�Ϊdu2_dn��Unit2�Ľ�Ϊdu1_u2dn*/
	du2_dn=result_space1[id1U].p_range.range_p_dn;
	du1_u2dn=Pset-du2_dn;

	/*������⣬Unit1�Ľ�Ϊdu2_up��Unit2�Ľ�Ϊdu1_u2up*/
	du2_up=result_space1[id1U].p_range.range_p_up;
	du1_u2up=Pset-du2_up;

	/*�ֱ���������м��*/
	if(((p_3U<du1_dn)||(p_3U>=du1_dn && p_3U<=du1_up))&&(du2_u1dn<du2_up))
	{		
		unit_tmp1[1].unit_id=unit_id1;
		unit_tmp1[1].unit_P=result_space1[spa1_2U].p_range.range_p_dn;
		unit_tmp2[1].unit_id=unit_id2;
		unit_tmp2[1].unit_P=result_space1[spa2_2U].p_range.range_p_dn;
		unit_tmp2[1].unit_id=unit_id3;
		unit_tmp2[1].unit_P=result_space1[spa2_3U].p_range.range_p_dn;
		unit_tmp4[1].unit_id=unit_id4;
		unit_tmp4[1].unit_P=du2_u1dn;
/*		dx[1]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[1].unit_P),2)
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[1].unit_P),2)
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[1].unit_P),2)
			+pow((UNIT[unit_id4].AP_Setp-unit_tmp4[1].unit_P),2); */ //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[1]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[1].unit_P),2)*UNIT[unit_id1].Privilege
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[1].unit_P),2)*UNIT[unit_id2].Privilege
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[1].unit_P),2)*UNIT[unit_id3].Privilege
			+pow((UNIT[unit_id4].AP_Setp-unit_tmp4[1].unit_P),2)*UNIT[unit_id4].Privilege;
	}

	if(((p_3U>du1_up)||(p_3U>=du1_dn && p_3U<=du1_up))&&(du2_u1up>du2_dn))
	{
		unit_tmp1[2].unit_id=unit_id1;
		unit_tmp1[2].unit_P=result_space1[spa1_2U].p_range.range_p_up;
		unit_tmp2[2].unit_id=unit_id2;
		unit_tmp2[2].unit_P=result_space1[spa2_2U].p_range.range_p_up;
		unit_tmp3[2].unit_id=unit_id3;
		unit_tmp3[2].unit_P=result_space1[spa2_3U].p_range.range_p_up;
		unit_tmp4[2].unit_id=unit_id4;
		unit_tmp4[2].unit_P=du2_u1up;
/*		dx[2]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[2].unit_P),2)
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[2].unit_P),2)
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[2].unit_P),2)
			+pow((UNIT[unit_id4].AP_Setp-unit_tmp4[2].unit_P),2); */  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[2]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[2].unit_P),2)*UNIT[unit_id1].Privilege
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[2].unit_P),2)*UNIT[unit_id2].Privilege
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[2].unit_P),2)*UNIT[unit_id3].Privilege
			+pow((UNIT[unit_id4].AP_Setp-unit_tmp4[2].unit_P),2)*UNIT[unit_id4].Privilege;
	}

	if(((p_1U<du2_dn)||(p_1U>=du2_dn && p_1U<=du2_up))&&(du1_u2dn<du1_up))	
	{
		Check_P_Space3U(spa1_3U,spa2_3U,du1_u2dn);
		unit_tmp1[3].unit_id=tmp_space_result.Unit_Result[1].unit_id;
		unit_tmp1[3].unit_P=tmp_space_result.Unit_Result[1].unit_P;
		unit_tmp2[3].unit_id=tmp_space_result.Unit_Result[2].unit_id;
		unit_tmp2[3].unit_P=tmp_space_result.Unit_Result[2].unit_P;
		unit_tmp3[3].unit_id=tmp_space_result.Unit_Result[3].unit_id;
		unit_tmp3[3].unit_P=tmp_space_result.Unit_Result[3].unit_P;
		unit_tmp4[3].unit_id=unit_id4;
		unit_tmp4[3].unit_P=du2_dn;
/*		dx[3]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[3].unit_P),2)
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[3].unit_P),2)
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[3].unit_P),2)
			+pow((UNIT[unit_id4].AP_Setp-unit_tmp4[3].unit_P),2); */  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[3]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[3].unit_P),2)*UNIT[unit_id1].Privilege
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[3].unit_P),2)*UNIT[unit_id2].Privilege
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[3].unit_P),2)*UNIT[unit_id3].Privilege
			+pow((UNIT[unit_id4].AP_Setp-unit_tmp4[3].unit_P),2)*UNIT[unit_id4].Privilege;
	}

	if(((p_1U>du2_up)||(p_1U>=du2_dn && p_1U<=du2_up))&&(du1_u2up>du1_dn))	
	{
		Check_P_Space3U(spa1_3U,spa2_3U,du1_u2up);
		unit_tmp1[4].unit_id=tmp_space_result.Unit_Result[1].unit_id;
		unit_tmp1[4].unit_P=tmp_space_result.Unit_Result[1].unit_P;
		unit_tmp2[4].unit_id=tmp_space_result.Unit_Result[2].unit_id;
		unit_tmp2[4].unit_P=tmp_space_result.Unit_Result[2].unit_P;
		unit_tmp3[4].unit_id=tmp_space_result.Unit_Result[3].unit_id;
		unit_tmp3[4].unit_P=tmp_space_result.Unit_Result[3].unit_P;
		unit_tmp4[4].unit_id=unit_id4;
		unit_tmp4[4].unit_P=du2_up;
/*		dx[4]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[4].unit_P),2)
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[4].unit_P),2)
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[4].unit_P),2)
			+pow((UNIT[unit_id4].AP_Setp-unit_tmp4[14].unit_P),2); */  //�����ǻ���������ȼ�����ֵ����
		//����Ϊ�����˻����������Ȩ����ֵ����
		dx[4]=pow((UNIT[unit_id1].AP_Setp-unit_tmp1[4].unit_P),2)*UNIT[unit_id1].Privilege
			+pow((UNIT[unit_id2].AP_Setp-unit_tmp2[4].unit_P),2)*UNIT[unit_id2].Privilege
			+pow((UNIT[unit_id3].AP_Setp-unit_tmp3[4].unit_P),2)*UNIT[unit_id3].Privilege
			+pow((UNIT[unit_id4].AP_Setp-unit_tmp4[14].unit_P),2)*UNIT[unit_id4].Privilege;
	}
	tmp=INFI;
	for(i=1;i<5;i++)
	{
		if((tmp>=dx[i])&&(dx[i]!=INFI))
		{
			tmp_space_result.Unit_Result[1].unit_id=unit_tmp1[i].unit_id;
			tmp_space_result.Unit_Result[1].unit_P=unit_tmp1[i].unit_P;
			tmp_space_result.Unit_Result[2].unit_id=unit_tmp2[i].unit_id;
			tmp_space_result.Unit_Result[2].unit_P=unit_tmp2[i].unit_P;
			tmp_space_result.Unit_Result[3].unit_id=unit_tmp3[i].unit_id;
			tmp_space_result.Unit_Result[3].unit_P=unit_tmp3[i].unit_P;
			tmp_space_result.Unit_Result[4].unit_id=unit_tmp4[i].unit_id;
			tmp_space_result.Unit_Result[4].unit_P=unit_tmp4[i].unit_P;
			tmp_space_result.dx=dx[i];
			tmp=dx[i];
		}
	}
}

void GetResultBy_P_Space()
{
	int i;
	int id1,id2,id3;
	int tmp_dx=INFI;
	
	if(PLANT.Num_AP_Avail==2)  /*��̨�������ɵ��ý�ռ����*/
	{
		GetResultSpace_1Unit();
		GetResultSpace_2Unit();
		for(i=1;i<=spnum_2U;i++)
		{
			if((result_space2[i].p_range.range_p_dn<=PLANT.AGC_P_Set)&&(result_space2[i].p_range.range_p_up>=PLANT.AGC_P_Set))
			{
				id1=result_space2[i].spa1_id;
				id2=result_space2[i].spa2_id;
				Check_P_Space2U(id1,id2,PLANT.AGC_P_Set);	
				if(tmp_dx>=tmp_space_result.dx)
				{
					p_space_result=tmp_space_result;
					tmp_dx=tmp_space_result.dx;
				}
			}
		}
	}
	else if(PLANT.Num_AP_Avail==3)	/*��̨��������޷���������*/
	{
		GetResultSpace_1Unit();
		GetResultSpace_2Unit();
		GetResultSpace_3Unit();
		for(i=1;i<=spnum_3U;i++)
		{
			if((result_space3[i].p_range.range_p_dn<=PLANT.AGC_P_Set)&&(result_space3[i].p_range.range_p_up>=PLANT.AGC_P_Set))
			{
				id1=result_space3[i].spaU2_id;
				id2=result_space3[i].spaU1_id;
				Check_P_Space3U(id1,id2,PLANT.AGC_P_Set);	
				if(tmp_dx>tmp_space_result.dx)
				{
					p_space_result=tmp_space_result;
					tmp_dx=tmp_space_result.dx;
				}
			}
		}
	}
	else if(PLANT.Num_AP_Avail==4)	/*��̨��������޷���������*/
	{
		GetResultSpace_1Unit();
		GetResultSpace_2Unit();
		GetResultSpace_3Unit();
		GetResultSpace_4Unit();
		for(i=1;i<=spnum_4U;i++)
		{
			if((result_space4[i].p_range.range_p_dn<=PLANT.AGC_P_Set)&&(result_space4[i].p_range.range_p_up>=PLANT.AGC_P_Set))
			{
				id1=result_space4[i].spaU3_id;
				id2=result_space4[i].spaU1_id;
				Check_P_Space4U(id1,id2,PLANT.AGC_P_Set);	
				if(tmp_dx>tmp_space_result.dx)
				{
					p_space_result=tmp_space_result;
					tmp_dx=tmp_space_result.dx;
				}
			}
		}
	}
}

void GetPlantRunLmt()
{
	int i,j,num,first_avail;
	int k,m;
//	int avl_num[UNIT_NUMB+1];
	float tmp_run_down[5],tmp_run_up[5],unit_run_dn[MAX_UNIT_NUMB+1][VIBRATION_NUMB+1],unit_run_up[MAX_UNIT_NUMB+1][VIBRATION_NUMB+1];
	float plant_agc_dnlmt[4],plant_agc_uplmt[4],plant_all_dnlmt[4],plant_all_uplmt[4],Sum_P_no_agc;
	float tmp_dn[15],tmp_up[15];
	float down_tmp,up_tmp;

	Sum_P_no_agc=0;
        for(i=0;i<4;i++)
        {
            plant_agc_uplmt[i]=0;
            plant_agc_dnlmt[i]=0;
            plant_all_dnlmt[i]=0;
            plant_all_uplmt[i]=0;
        }
	
	first_avail=0;
	for(i=1;i<=UNIT_NUMB;i++)	
	{
		if(UNIT[i].AP_Avail==1)	//�������Ŀ���������
		{
			if(first_avail==0) first_avail=i;	//first_availΪ��һ̨����ɿصĻ���ı��
//			k++;
//			avl_num[k]=i;
			if((UNIT[i].Low_Vibration[2]>UNIT[i].AP_Max)&&(UNIT[i].Up_Vibration[2]>UNIT[i].AP_Max)) 	//added for jiangya by fengxun,2010-01-18
			{
				UNIT[i].Low_Vibration[2]=UNIT[i].AP_Max;
				UNIT[i].Up_Vibration[2]=UNIT[i].AP_Max;
			}
			if((UNIT[i].Low_Vibration[1]<UNIT[i].AP_Min)&&(UNIT[i].Up_Vibration[1]<UNIT[i].AP_Min)) 	//added for jiangya by fengxun,2010-01-18
			{
				UNIT[i].Low_Vibration[1]=UNIT[i].AP_Min;
				UNIT[i].Up_Vibration[1]=UNIT[i].AP_Min;
			}
			if(UNIT[i].VibrationNum==0)
			{
				unit_run_dn[i][0]=UNIT[i].AP_Min;
				unit_run_up[i][0]=UNIT[i].AP_Max;
				if(first_avail==i)
				{
					tmp_run_down[0]=unit_run_dn[first_avail][0];
					tmp_run_up[0]=unit_run_up[first_avail][0];
				}
			}
			else if(UNIT[i].VibrationNum==1)
			{
				unit_run_dn[i][0]=UNIT[i].AP_Min;
				unit_run_up[i][0]=UNIT[i].Low_Vibration[1];
				unit_run_dn[i][1]=UNIT[i].Up_Vibration[1];
				unit_run_up[i][1]=UNIT[i].AP_Max;
				if(first_avail==i)
				{
					tmp_run_down[0]=unit_run_dn[first_avail][0];
					tmp_run_up[0]=unit_run_up[first_avail][0];
					tmp_run_down[1]=unit_run_dn[first_avail][1];
					tmp_run_up[1]=unit_run_up[first_avail][1];
				}
			}
			else if(UNIT[i].VibrationNum==2)
			{
				unit_run_dn[i][0]=UNIT[i].AP_Min;
				unit_run_up[i][0]=UNIT[i].Low_Vibration[1];
				unit_run_dn[i][1]=UNIT[i].Up_Vibration[1];
				unit_run_up[i][1]=UNIT[i].Low_Vibration[2];
				unit_run_dn[i][2]=UNIT[i].Up_Vibration[2];
				unit_run_up[i][2]=UNIT[i].AP_Max;
				if(first_avail==i)
				{
					tmp_run_down[0]=unit_run_dn[first_avail][0];
					tmp_run_up[0]=unit_run_up[first_avail][0];
					tmp_run_down[1]=unit_run_dn[first_avail][1];
					tmp_run_up[1]=unit_run_up[first_avail][1];
					tmp_run_down[2]=unit_run_dn[first_avail][2];
					tmp_run_up[2]=unit_run_up[first_avail][2];
				}
			}
		}
		else if(UNIT[i].Status == UNIT_IN_GEN_AGC)
			Sum_P_no_agc+=UNIT[i].AP_RtValue;
	}
	
	for(num=1;num<=UNIT_NUMB;num++)	//�������������������1
	{
		k=0;
		m=0;

		if((num==first_avail)&&(PLANT.Num_AP_Avail==1))	//����һ̨�������
		{
			m=UNIT[num].VibrationNum;
			for(i=0;i<m;i++)
			{
				plant_agc_dnlmt[i] = UNIT[num].Low_Vibration[i+1];
				plant_agc_uplmt[i] = UNIT[num].Up_Vibration[i+1];
			}
			break;
		}

		if((UNIT[num].AP_Avail==1)&&(num!=first_avail))	//����һ̨�������
		{
			for(i=0;i<VIBRATION_NUMB+1;i++)
			{
				for(j=0;j<VIBRATION_NUMB+1;j++)
				{
					tmp_dn[k]=tmp_run_down[i]+unit_run_dn[num][j];
					tmp_up[k]=tmp_run_up[i]+unit_run_up[num][j];
					k++;
				}
			}
		}
		else
			continue;
		for(i=0;i<k;i++)
		{
			for(j=i+1;j<k;j++)
			{
				if((tmp_dn[i]>tmp_dn[j])
					||((tmp_dn[i]==tmp_dn[j])&&(tmp_up[i]>tmp_up[j])))
				{
					down_tmp=tmp_dn[j];
					up_tmp=tmp_up[j];
					tmp_dn[j]=tmp_dn[i];
					tmp_up[j]=tmp_up[i];
					tmp_dn[i]=down_tmp;
					tmp_up[i]=up_tmp;
				}
			}
		}
		tmp_run_down[0]=tmp_dn[0];
		tmp_run_up[0]=tmp_up[0];
		for(i=0;i<4;i++)
		{
			plant_agc_dnlmt[i] =0;
			plant_agc_uplmt[i] =0;
		}
		for(i=0;i<k-1;i++)
		{

			if(tmp_run_up[m]<tmp_dn[i+1]) 
			{
//				plant_agc_dnlmt[m] = tmp_up[i];
				plant_agc_dnlmt[m] = tmp_run_up[m];
				plant_agc_uplmt[m] = tmp_dn[i+1];
/*				if(tmp_run_down[m]>tmp_dn[i]) 
					tmp_run_down[m]=tmp_dn[i];
				if(tmp_run_up[m]<tmp_up[i])
					tmp_run_up[m]=tmp_up[i];*/
				tmp_run_down[m+1]=tmp_dn[i+1];
				tmp_run_up[m+1]=tmp_up[i+1];
				m++;
			}
			else if(tmp_up[i+1]>tmp_run_up[m])
			{
				tmp_run_up[m]=tmp_up[i+1];
			}
			if(m==4)	//ֻȡ4������
			{
				tmp_run_up[m]=tmp_up[k-1];
				break;
			}
		}
		
		if(m<4)
		{
			for(i=m+1;i<4;i++)
			{
				tmp_run_down[i]=tmp_run_down[0];
				tmp_run_up[i]=tmp_run_up[0];
			}
		}
	}

	//for(i=0;i<m;i++) printf("**%f %f\n",plant_agc_dnlmt[i]+Sum_P_no_agc,plant_agc_uplmt[i]+Sum_P_no_agc);
	//printf("\n");
	k=0;
	for(i=0;i<4;i++) 
	{
		if(plant_agc_uplmt[i]==plant_agc_dnlmt[i])
		{
//			plant_all_dnlmt[i]=0;
//			plant_all_uplmt[i]=0;
		}
		else
		{
			/*if((PLANT.p_sum>plant_agc_uplmt[i]+Sum_P_no_agc+PLANT.AP_ChangeMax)
				||(PLANT.p_sum<plant_agc_dnlmt[i]+Sum_P_no_agc-PLANT.AP_ChangeMax))
				continue;*/
			plant_all_dnlmt[k]=plant_agc_dnlmt[i]+Sum_P_no_agc-1;	//�Ĵ�ʡ��Ҫ�����ͽ����������޸�����1MW
			plant_all_uplmt[k]=plant_agc_uplmt[i]+Sum_P_no_agc+1;
			k++;
		}
	}
	
	/*added for PBG,2011-05-13*/
	if((plant_all_uplmt[0]==plant_all_dnlmt[0]))
	{
		plant_all_dnlmt[0]=1;
		plant_all_uplmt[0]=2;
	}
	if((plant_all_uplmt[1]==plant_all_dnlmt[1]))
	{
		plant_all_dnlmt[1]=plant_all_uplmt[0]+1;
		plant_all_uplmt[1]=plant_all_uplmt[0]+2;		
	}
	if((plant_all_uplmt[2]==plant_all_dnlmt[2]))
	{
		plant_all_dnlmt[2]=plant_all_uplmt[1]+1;
		plant_all_uplmt[2]=plant_all_uplmt[1]+2;
	}
	
	for(i=0;i<3;i++) 
	{
		AGC_UpdateRTDB_ANA(DB_NAME_QCUNRUN_UPLMT[i+1],plant_all_uplmt[i]);
		AGC_UpdateRTDB_ANA(DB_NAME_QCUNRUN_DNLMT[i+1],plant_all_dnlmt[i]);
	}
}

void CheckWDCtrl()
{
	float remote_p_set;	
	
	if(PLANT.Control_Right == 1)
	{
		remote_p_set = ReadDB_ANA(DB_NAME_Remote_Setpoint);	
		if((fabs( remote_p_set - PLANT.AP_WorkSP)>10.0)&&(yf_flag==0))
		{
			PLANT.Control_Right =0;
			AGC_UpdateRTDB_IND  ( DB_NAME_Control_Right,  NOT );
			AGC_UpdateRTDB_IND  ( DB_NAME_ALM_YFKErr,  YES );
		}
		else if	(yf_flag==0)
		{
			yf_flag=1;
		}
	}
	else
	{
		AGC_UpdateRTDB_IND  ( DB_NAME_ALM_YFKErr,  NOT );
		yf_flag=0;
	}
}

int Check_Cmd_ReSend()
{
	int yggd,i;
	char err_str[80];
	
	if(GetControlState()!=1) //����վ���㲥��added by fengxun,2011-11-23
	{		
		for ( i= 1; i<= UNIT_NUMB; i++ ) 
			UNIT[i].CommandSendSbo = NOT;
		return(0);	
	}
	for ( i= 1; i<= UNIT_NUMB; i++ ) 
	{
		yggd=(int)ReadDB_ANA(DB_NAME_AP_SetValue[i]);
		if(UNIT[i].AP_Avail==0)	
		{
			UNIT[i].CommandSendSbo = NOT;
			UNIT[i].AP_Setp=yggd;
			continue;		
		}
		if((UNIT[i].CommandSendSbo == YES)&&(fabs(UNIT[i].AP_Setp-yggd)>2))	//���ڸո�ͨ��FillCommandBuf()����Ļ��飬��������ֵ�Ƿ���ղŵ��·�ֵ���
		{	
			sprintf(err_str,"%dF:AGC�й����������·�",i);
			BroadCastSms(err_str, TRUE);		
			SendCommandToPLC(DB_NAME_AP_SetValue[i],C_APOWER,UNIT[i].AP_Setp,0); 				
		}
		UNIT[i].CommandSendSbo = NOT;
	}
	return(1);
}

int Check_Unit_P_Status(int i)
{
	int tmp,tmp1,jzjx;
	char err_str[80];
	tmp = ReadDB_Chan ( DB_NAME_AP_RtValue[i] );		//�л����й�����ͨ���Ƿ����
	tmp1 = ReadDB_Chan ( DB_NAME_BREAKER_Status[i] );		//�л����·���ֺ��Ƿ����
	jzjx = ReadDB_IND(DB_NAME_AGC_JZJX[i]);
	if((UNIT[i].AP_RtValue<0)&&(UNIT[i].Status!=UNIT_IN_GEN_AGC))	//�Ƿ���̬�����й�Ϊ0
		UNIT[i].AP_RtValue=0;
	else if(((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(jzjx==0)&&((tmp==1)||(tmp1==1)))||     //���鷢��̬���й�����ͨ�����ϣ��˳�AGC
		((UNIT[i].Status!=UNIT_IN_GEN_AGC)&&(jzjx==0)&&(UNIT[i].AP_RtValue>20.0)) )	//���鲻�ڷ���̬���й����ʴ���20MW�������˳�AGC
	{
		if((GetControlState()==1)&&(ReadDB_IND( DB_NAME_QC_AGC )==1))
		{
			if(unit_status_flag[i]==1)
			{
				unit_status_flag[i]=0;
				if(tmp==1) 
					sprintf(err_str,"%dF:�����й�ͨ����������",i);
				else if(tmp1==1) 
					sprintf(err_str,"%dF:�����·��ͨ����������",i);
				else
					sprintf(err_str,"%dF:����Ƿ���̬�й�%dMW",i,(int)(UNIT[i].AP_RtValue+0.5));
				BroadCastSms(err_str, TRUE);
				AGC_UpdateRTDB_IND  ( DB_NAME_ALM_StatusErr,  YES );
				return(QUIT);
			}
			else
				unit_status_flag[i]=1;
		}		
	}		
	/*�ж���һ���ɼ������ڣ������й��ɼ�ֵͻ�䣨����120MW����AGC�����˳�*/
/*	else if(fabs(UNIT[i].AP_RtValue-UNIT[i].Last_APValue)>120)
	{
		printf("����%d�й��ɼ�����ͻ�䣡��AGC�˳���\n",i,UNIT[i].AP_RtValue,UNIT[i].Last_APValue);
		AGC_UpdateRTDB_IND ( DB_NAME_ALM_P_GETERR, YES);
		UNIT[i].Last_APValue=UNIT[i].AP_RtValue;
		return(QUIT);
	}*/
	else
	{
		unit_status_flag[i]=0;
		AGC_UpdateRTDB_IND  ( DB_NAME_ALM_StatusErr,  NOT );
	}
//	UNIT[i].Last_APValue=UNIT[i].AP_RtValue;
	return(0);
}

void Check_CmdTime()
{
	int yy,mm,dd,hh,Mi,ss;
	DMS_COMMON common_aa;
	if(ReadEntryByNameStr(DB_NAME_Remote_Setpoint,&common_aa)==-1)
	{
		printf("No this point %s\n",DB_NAME_Remote_Setpoint);
	}

	yy=common_aa.var.anlg.update_time.year;
	mm=common_aa.var.anlg.update_time.month;
	dd=common_aa.var.anlg.update_time.day;
	hh=common_aa.var.anlg.update_time.hour;
	Mi=common_aa.var.anlg.update_time.minute;
	ss=common_aa.var.anlg.update_time.second;
	AGC_UpdateRTDB_ANA ( "PBG.SYS.ANA.SD_P_SET_YEAR", yy );
	AGC_UpdateRTDB_ANA ( "PBG.SYS.ANA.SD_P_SET_MONTH", mm );
	AGC_UpdateRTDB_ANA ( "PBG.SYS.ANA.SD_P_SET_DATE", dd );
	AGC_UpdateRTDB_ANA ( "PBG.SYS.ANA.SD_P_SET_HOUR", hh );
	AGC_UpdateRTDB_ANA ( "PBG.SYS.ANA.SD_P_SET_MINUTE", Mi );
	AGC_UpdateRTDB_ANA ( "PBG.SYS.ANA.SD_P_SET_SEC", ss );

}

void Check_Vibrating()
{
	int i;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(CheckPowerVibZone(i, (int)UNIT[i].AP_RtValue,20)!=0)
			AGC_UpdateRTDB_IND(DB_NAME_VIBRATING[i] , YES);
		else
			AGC_UpdateRTDB_IND(DB_NAME_VIBRATING[i] , NOT);
	}
}

void ReadAGC_DataFromRTDB()
{
	int i,j,tmp;
	int P_deadband;
	char err_str[80];
//	MoveP_Curve_At_Zero();	//�޸������߷�ʽ
//	MoveRTP_Curve(); 
	AGC_Period=(int)ReadDB_ANA(DB_NAME_AGC_Period);
	if(AGC_Period<2)
	{
		AGC_Period=2;
		AGC_UpdateRTDB_ANA ( DB_NAME_AGC_Period,  AGC_Period );
	}
	
	P_deadband=(int)ReadDB_ANA(DB_NAME_DB_AP_WorkSP);
	if(P_deadband<2)
	{
		P_deadband=2;
		AGC_UpdateRTDB_ANA ( DB_NAME_DB_AP_WorkSP,  P_deadband );
	}

	water_refresh_Period=(int)ReadDB_ANA(DB_NAME_WATER_REFR_TIME);
	if(water_refresh_Period<5) water_refresh_Period=5;
	PLANT.AP_Deadband=P_deadband;
	PLANT.AP_ChangeMax=ReadDB_ANA(DB_NAME_AP_ChangeMax);
//	PLANT.MinorAdjP = ReadDB_ANA(DB_NAME_MINOR_ADJ_P);	//added by fengxun for PBG,2010-11-18
	PLANT.Control_Right = ReadDB_IND (DB_NAME_Control_Right);
	PLANT.Closed_Loop = ReadDB_IND ( DB_NAME_AGC_CLOSED_LOOP );
	PLANT.AP_Setting = ReadDB_IND ( DB_NAME_AP_Setting );
	PLANT.AP_Curve = 0; /*  for FT*/

	for(i=1;i<=UNIT_NUMB;i++)
	{
		UNIT[i].Status=ReadDB_IND(DB_NAME_Rt_Status[i]);		
		tmp=(int)ReadDB_ANA(DB_NAME_Prvilege[i]);		
		UNIT[i].Privilege=tmp;
		AP_Adj_Step[i]=ReadDB_ANA(DB_NAME_ADJ_STEP[i]);
		UNIT[i].AP_RtValue=ReadDB_ANA(DB_NAME_AP_RtValue[i]);
		/*�ж���һ���ɼ������ڣ������й��ɼ�ֵͻ�䣨����100MW����AGC�����˳�*/
		if(fabs(UNIT[i].AP_RtValue-UNIT[i].Last_APValue)>100)
		{
			printf("����%d�й��ɼ�����ͻ�䣡��AGC�˳���\n",i,UNIT[i].AP_RtValue,UNIT[i].Last_APValue);
			AGC_UpdateRTDB_IND ( DB_NAME_ALM_P_GETERR, YES);
			sprintf(err_str,"%dF:�й��ɼ�����ͻ��%dMW",i,(int)(UNIT[i].AP_RtValue+0.5));
				BroadCastSms(err_str, TRUE);
			AGC_UpdateRTDB_IND  ( DB_NAME_QC_AGC,  NOT );
		}
		else
			AGC_UpdateRTDB_IND ( DB_NAME_ALM_P_GETERR, NOT);
		UNIT[i].Last_APValue=UNIT[i].AP_RtValue;
/*		tmp=Check_Unit_P_Status(i);  //removed by fengxun,2011-12-25
		if(tmp==QUIT)
		{
			AGC_UpdateRTDB_IND  ( DB_NAME_QC_AGC,  NOT );
		}*/
	}
	
	tmp = ReadDB_IND ( DB_NAME_QC_AGC );
	if(tmp==0)
	{
		PLANT.Closed_Loop=0;
		PLANT.AP_Setting=0;
		PLANT.AP_Curve=0;
		PLANT.Control_Right=0;
		AGC_UpdateRTDB_IND  ( DB_NAME_AGC_CLOSED_LOOP,  NOT );
		AGC_UpdateRTDB_IND  ( DB_NAME_AP_Setting,  NOT );
		AGC_UpdateRTDB_IND  ( DB_NAME_AP_Curve,  NOT );
		AGC_UpdateRTDB_IND  ( DB_NAME_Control_Right,  NOT );
//		AGC_UpdateRTDB_IND  ( DB_NAME_RemoteAGCOnLine,  NOT );
		for(i=1;i<=UNIT_NUMB;i++)
		{
#ifdef SUNOS
		usleep(100000);
#else
		 Sleep(100);
#endif	
			AGC_UpdateRTDB_IND  ( DB_NAME_AP_Group[i], NOT );
			AGC_UpdateRTDB_IND  ( DB_NAME_AP_CZKT[i], NOT );
		}
	}
	
	PLANT.AP_Max=0;
	PLANT.AP_Min=0;
	Statistics_Unit();
	GetWaterLevel();
	GetCurrentUnitMaxMinPower();
	Refresh_Manwatermsg();	//��ʱˢ���ֶ����õ�ˮͷ����
#ifdef PBG
	Check_AKQJ();	/*added by Lixiaojuan 2010-09-16,�����л�*/
	Check_CmdTime();	/*ʡ������ʱ��*/
	Check_Vibrating();  /*�����Ƿ�������*/
#endif
	GetUnitRunArea();
	GetPlantRunLmt();   /*added by fengxun 2007-10-31*/
	if(ManSetLmt==1)
	{
		for(i=1;i<=UNIT_NUMB;i++)
		{
			if(UNIT[i].VibrationNum==0)continue;
			for(j=1;j<=UNIT[i].VibrationNum;j++)
			{
				/*printf("Unit No.%d Low_Vibration[%d]=%d,Up_Vibration[%d]=%d\n",
				  i,j,UNIT[i].Low_Vibration[j],j,UNIT[i].Up_Vibration[j]);*/
				if(UNIT[i].Low_Vibration[j]>UNIT[i].Up_Vibration[j])
				{
					printf("Unit No.%d ��%d�����������޲���ȷ!!!\n",i,j);
					UnMount_handle();
				}
			}
		} 
	}
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(UNIT[i].AP_Avail==0)
		{	
			AGC_UpdateRTDB_IND ( DB_NAME_Control_Command[i], WCZTHM );
			if(UNIT[i].Status==UNIT_IN_GEN_AGC)
			{
				PLANT.AP_Max+=UNIT[i].AP_RtValue;
				PLANT.AP_Min+=UNIT[i].AP_RtValue;
			}
		}
		else if(UNIT[i].AP_Avail==1)
		{
			PLANT.AP_Max+=UNIT[i].AP_Max;
			PLANT.AP_Min+=UNIT[i].AP_Min;
		}
	}
#ifdef HuaZhongWangDiao
	CheckWDCtrl();
#endif
	GetPlantSetpointValue();
	if (( PLANT.AP_Setting ==1 )&&( PLANT.AP_Curve == 1 ))
	{
		PLANT.AP_Setting=PLANT.AP_Curve=0;

		AGC_UpdateRTDB_IND ( DB_NAME_AP_Setting, NOT);   
		AGC_UpdateRTDB_IND ( DB_NAME_AP_Curve, NOT);
	}
	GetControlable_P_lmt();
}

void MinorAdjustPrv()
{
	int tmp,i,j,k=0;
	int tmp_prv[MAX_UNIT_NUMB+1];

	for(i=1;i<=UNIT_NUMB;i++)
		tmp_prv[i]=UNIT[i].Privilege;
	
	for(i=1;i<=UNIT_NUMB;i++)
	{
		tmp=1000;
		for(j=1;j<=UNIT_NUMB;j++)
		{
			if((UNIT[j].Status!=UNIT_IN_GEN_AGC)||(UNIT[j].AP_Avail==0))
				continue;
			if(tmp_prv[j]<tmp)
			{
				tmp=tmp_prv[j];
				k=j;
			}
		}
		minor_adjust[i]=k;
		tmp_prv[k]=2000;
	}
}

void StartStopCalculation()
{
	int Ready_Start,Ready_Stop,Max,i,First_Start,First_Stop,tmp1,tmp2;
	Ready_Start=0;
	Ready_Stop=0;
	Max=0;
	First_Start=0;
	First_Stop=0;
	tmp1=1000;
	tmp2=-1;
	PLANT.Start_Req=0;
	PLANT.Stop_Req=0;
	PLANT.Unit_Start=0;
	PLANT.Unit_Stop=0;
	PLANT.SS_Deadband=ReadDB_ANA(DB_NAME_StartStopDeadband);
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(UNIT[i].AP_Avail==0)
			continue;
		if((UNIT[i].Status==UNIT_IN_STANDBY_AGC)&&(UNIT[i].Privilege<tmp1))
		{
			tmp1=UNIT[i].Privilege;
			First_Start=i;
		}
		if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].Privilege>tmp2))
		{
			tmp2=UNIT[i].Privilege;
			First_Stop=i;
		}
		if(UNIT[i].Status==UNIT_IN_GEN_AGC)
			Max+=UNIT[i].AP_Max;
	}
	if((PLANT.AP_WorkSP-Max>PLANT.SS_Deadband)&&(PLANT.AP_WorkSP>PLANT.AP_Min))
		Ready_Start=1;
	if(Max-UNIT[First_Stop].AP_Max-PLANT.AP_WorkSP>PLANT.SS_Deadband)
		Ready_Stop=1;
	if((Ready_Start==1)&&(First_Start>0))
	{
		UNIT[First_Start].Start_Req=1;
		PLANT.Start_Req=1;
		PLANT.Unit_Start=First_Start;
	}
	if((Ready_Stop==1)&&(First_Stop>0))
	{
		UNIT[First_Stop].Stop_Req=1;
		PLANT.Stop_Req=1;
		PLANT.Unit_Stop=First_Stop;
	}
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(i!=PLANT.Unit_Start)
			UNIT[i].Start_Req=0;
		if(i!=PLANT.Unit_Stop)
			UNIT[i].Stop_Req=0;
	}
}

void StartStopModule()
{
	int Unit_Start,Unit_Stop;
	Unit_Start=0;
	Unit_Stop=0;
	if((PLANT.Start_Req==1)&&(PLANT.Unit_Start>0))
	{
		Unit_Start=PLANT.Unit_Start;
		UNIT[Unit_Start].Start_Req=0;
		UNIT[Unit_Start].Start=1;
		PLANT.XStrStp_Recalc=0;
	}
	if((PLANT.Stop_Req==1)&&(PLANT.Unit_Stop>0))
	{
		Unit_Stop=PLANT.Unit_Stop;
		UNIT[Unit_Stop].Stop_Req=0;
		UNIT[Unit_Stop].Stop=1;
		PLANT.XStrStp_Recalc=0;
	}
}

void CalculatePowerZone() /*������鱣�ֵ�ǰ����״̬����Խ�������й���Χ*/
{
	int i;
	PLANT.UplmtCurrentZone=PLANT.LowlmtCurrentZone=0;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].AP_Avail==1))
		{
			PLANT.UplmtCurrentZone+=UNIT[i].CurrentUplmt;
			PLANT.LowlmtCurrentZone+=UNIT[i].CurrentLowlmt;
		}
	}
}

int CheckPowerVibZone(int UnitPos,int UnitPower,int Deadband)
{
	int i,ReturnValue;
	ReturnValue=0;
	if(UNIT[UnitPos].VibrationNum==0)
		return 0;
	for(i=1;i<=UNIT[UnitPos].VibrationNum;i++)
	{
		if((UnitPower>UNIT[UnitPos].Low_Vibration[i]+Deadband)&&(UnitPower<UNIT[UnitPos].Up_Vibration[i]-Deadband))
		{
			ReturnValue=i;
			break;
		}
	}
	return(ReturnValue);
}

int Jump_Vibration(int UnitPos,int UnitPower,int derection)
{
	int i,ReturnValue;
	int vib;
	ReturnValue=0;
	if(UNIT[UnitPos].VibrationNum==0)
		return(0);
	for(i=1;i<=UNIT[UnitPos].VibrationNum;i++)
	{
		if((UnitPower<=UNIT[UnitPos].Low_Vibration[i])&&(UnitPower>UNIT[UnitPos].AP_Min+1)
			&&(derection==INCREASE)&&(UNIT[UnitPos].Low_Vibration[i]<UNIT[UnitPos].Up_Vibration[i]))
		{
			return((int)UNIT[UnitPos].Up_Vibration[i]);
		}
		else if((UnitPower>=UNIT[UnitPos].Up_Vibration[i])&&(UnitPower<UNIT[UnitPos].AP_Max-1)
			&&(derection==DECREASE)&&(UNIT[UnitPos].Low_Vibration[i]<UNIT[UnitPos].Up_Vibration[i]))
		{
			if((i<UNIT[UnitPos].VibrationNum)&&(UnitPower>UNIT[UnitPos].Low_Vibration[i+1]))
				continue;
			return((int)UNIT[UnitPos].Low_Vibration[i]);
		}
	}	
	return(0);
}

float GetUnitCurrentMin(int UnitPos,int UnitPower)
{
	int ReturnValue,i,tmp;
	ReturnValue=0;
	if((UnitPower<=UNIT[UnitPos].AP_Min)||(UNIT[UnitPos].VibrationNum==0))
		return(UNIT[UnitPos].AP_Min);
	for(i=1;i<=UNIT[UnitPos].VibrationNum;i++)
	{
		tmp=(UNIT[UnitPos].Low_Vibration[i]+UNIT[UnitPos].Up_Vibration[i])/2;
		if(UnitPower<=tmp)
		{
			if(i==1)
			{
				return(UNIT[UnitPos].AP_Min);
			}
			else
			{
				return(UNIT[UnitPos].Up_Vibration[i-1]);
			}
		}
	}
	return(UNIT[UnitPos].Up_Vibration[UNIT[UnitPos].VibrationNum]);
}

int GetUnitCurrentMax(int UnitPos,int UnitPower)
{
	int ReturnValue,i,tmp;
	ReturnValue=0;
	if((UnitPower>=UNIT[UnitPos].AP_Max)||(UNIT[UnitPos].VibrationNum==0))
		return((int)UNIT[UnitPos].AP_Max);
	for(i=1;i<=UNIT[UnitPos].VibrationNum;i++)
	{
		tmp=(UNIT[UnitPos].Low_Vibration[i]+UNIT[UnitPos].Up_Vibration[i])/2;
		if(UnitPower<=tmp)
		{
			return((int)UNIT[UnitPos].Low_Vibration[i]);
		}
	}
	return((int)UNIT[UnitPos].AP_Max);
}

int CalcUnitZone(int UnitPos, int Power)
{
	int i,tmp;
	int ReturnValue;
	ReturnValue=0;
	if(UNIT[UnitPos].VibrationNum==0)
		return 1;
	for(i=1;i<=UNIT[UnitPos].VibrationNum;i++)
	{
		tmp=(UNIT[UnitPos].Low_Vibration[i]+UNIT[UnitPos].Up_Vibration[i])/2;
		if(Power<=tmp)
		{
			ReturnValue=i;
			break;
		}
		else
		{
			ReturnValue=i+1;
		}
	}
	return(ReturnValue);
}

int Check_PreAllocate()
{
	int i,j;
	int unit_rl_up[MAX_UNIT_NUMB+1],unit_rl_dn[MAX_UNIT_NUMB+1]; //�����ڲ���Խ���������µ�����������
	int tmp,tmp1,aim_p,prv_id,updown_flag;
	int sum_rl_up=0,sum_rl_dn=0;
	int unit_stable_adj;	//�����ϴε����Ѿ��ﵽ�ȶ�̬����ʱ���л����й��仯
	
	if(PLANT.ACE_over_adj==YES)  //���ɲ���Խ��
		aim_p=(int)(PLANT.p_sum_agc+PLANT.ace);
	else if(NoAGCUnit_flag==YES)
		aim_p=PLANT.AGC_P_Set;
	else
		aim_p=PLANT.AGC_P_Set;
	updown_flag=0;

//���������ڵ�ǰ����Խ�����ɵ��������޻�С�ڵ�ǰ����Խ�����ɵ��������ޣ�������Ƿ��ܰ����ȼ���һ̨����ֱ�ӿ�Խ����
	if((aim_p>PLANT.UplmtCurrentZone)||(aim_p<PLANT.LowlmtCurrentZone)) 
	{
		//�����Ƿ��ܰ����ȼ���һ̨����ֱ�ӿ�Խ������һ�������е�ֵ
		for(i=1;i<=PLANT.Num_AP_Avail;i++)
		{
			if(NoAGCUnit_flag==YES)		//added by fengxun 2012-07-17
				tmp=UNIT[minor_adjust[i]].AP_Setp+PLANT.P_Yggd_ChangeValue;
			else
				tmp=UNIT[minor_adjust[i]].AP_Setp+PLANT.P_adj;

			if(tmp>=UNIT[minor_adjust[i]].AP_Min && tmp<=UNIT[minor_adjust[i]].AP_Max)
			{
				if(CheckPowerVibZone(minor_adjust[i], tmp,0)==0)
				{
					for(j=1;j<=UNIT_NUMB;j++)
					{
						minor_adjust_p_tmp[j]=UNIT[j].AP_Setp;
					}
					minor_adjust_p_tmp[minor_adjust[i]]=tmp;
					return(YES);
				}
			}
		}
		//�����淽�����ɹ��������Ƿ��ܰ����ȼ���һ̨����ֱ�ӿ�Խ�����������߽磬�������鲹�䲻�������
		for(i=1;i<=UNIT_NUMB;i++)
		{
			unit_rl_up[i]=UNIT[i].CurrentUplmt-UNIT[i].AP_Setp;
			unit_rl_dn[i]=UNIT[i].AP_Setp-UNIT[i].CurrentLowlmt;
			minor_adjust_p_tmp[i]=UNIT[i].AP_Setp;
			if(UNIT[i].AP_Avail==1) 
			{
				sum_rl_up+=unit_rl_up[i];
				sum_rl_dn+=unit_rl_dn[i];
			}
		}
		for(i=1;i<=PLANT.Num_AP_Avail;i++)
		{
			if(NoAGCUnit_flag==YES) 	//added by fengxun 2012-07-17
				tmp=UNIT[minor_adjust[i]].AP_Setp+PLANT.P_Yggd_ChangeValue;
			else
				tmp=UNIT[minor_adjust[i]].AP_Setp+PLANT.P_adj;
			if((PLANT.P_adj>0)&&(UNIT[minor_adjust[i]].CurrentUplmt<UNIT[minor_adjust[i]].AP_Max))
			{
				tmp=Jump_Vibration(minor_adjust[i],UNIT[minor_adjust[i]].AP_Setp,INCREASE);
//				sum_rl_up-=unit_rl_up[minor_adjust[i]];
			}
			else if((PLANT.P_adj<0)&&(UNIT[minor_adjust[i]].CurrentLowlmt>UNIT[minor_adjust[i]].AP_Min))
			{
				tmp=Jump_Vibration(minor_adjust[i],UNIT[minor_adjust[i]].AP_Setp,DECREASE);
//				sum_rl_dn-=unit_rl_dn[minor_adjust[i]];
			}
			else
				continue;
			if(tmp==0) 
				continue;
			else
			{
				tmp1=PLANT.P_adj-(tmp-UNIT[minor_adjust[i]].AP_Setp);
				if((tmp1>0 && tmp1>(sum_rl_up-unit_rl_up[minor_adjust[i]]))||(tmp1<0 && abs(tmp1)>(sum_rl_dn-unit_rl_dn[minor_adjust[i]])))
					continue;
				else
				{
					sum_rl_up-=unit_rl_up[minor_adjust[i]];
					sum_rl_dn-=unit_rl_dn[minor_adjust[i]];
				}
			}			
			
			for(j=1;j<=PLANT.Num_AP_Avail;j++)	//�ȼ���ʣ��Ŀɷ���һ̨���鲹���꣬�����Ļ��鲻һ�������ȼ��ߵĻ���
			{
				if(i==j) continue;
				if(((tmp1>0)&&(unit_rl_up[minor_adjust[j]]>=tmp1))||((tmp1<0)&&(unit_rl_dn[minor_adjust[j]]>=abs(tmp1))))
				{
					minor_adjust_p_tmp[minor_adjust[i]]=tmp;
					minor_adjust_p_tmp[minor_adjust[j]]=tmp1+UNIT[minor_adjust[j]].AP_Setp;
					return(YES);
				}
			}
			for(j=1;j<=PLANT.Num_AP_Avail;j++)	//���һ̨���鲹�䲻�������ȼ���̨���鲹�䵽��ǰ��������Ե
			{
				if(i==j) continue;
				if((tmp1>0)&&(tmp1<=sum_rl_up))
				{
					if(tmp1<=unit_rl_up[minor_adjust[j]])
					{
						minor_adjust_p_tmp[minor_adjust[j]]=tmp1+UNIT[minor_adjust[j]].AP_Setp;
						sum_rl_up-=tmp1;
						tmp1=0;
						minor_adjust_p_tmp[minor_adjust[i]]=tmp;
						return(YES);
					}
					else
					{
						tmp1-=unit_rl_up[minor_adjust[j]];
						sum_rl_up-=unit_rl_up[minor_adjust[j]];
						minor_adjust_p_tmp[minor_adjust[j]]=UNIT[minor_adjust[j]].CurrentUplmt;
					}
				}
				else if((tmp1<0)&&(abs(tmp1)<=sum_rl_dn))
				{
					if(abs(tmp1)<=unit_rl_dn[minor_adjust[j]])
					{
						minor_adjust_p_tmp[minor_adjust[j]]=tmp1+UNIT[minor_adjust[j]].AP_Setp;
						sum_rl_dn-=abs(tmp1);
						tmp1=0;
						minor_adjust_p_tmp[minor_adjust[i]]=tmp;
						return(YES);
					}
					else
					{
						tmp1+=unit_rl_dn[minor_adjust[j]];
						sum_rl_dn-=unit_rl_dn[minor_adjust[j]];
						minor_adjust_p_tmp[minor_adjust[j]]=UNIT[minor_adjust[j]].CurrentLowlmt;
					}					
				}
				else if(tmp1==0)
				{
					minor_adjust_p_tmp[minor_adjust[i]]=tmp;
					return(YES);
				}
			}
		}
		return(NOT);
	}
/*����Ϊ����Ҫ��Խ�������*/
	if(PLANT.ACE_over_adj==YES)		//���鸺�ɲ�����ɵ�΢��
	{
		unit_stable_adj=1;
		for ( i= 1; i<= UNIT_NUMB; i++ )	//���г���Ļ��鶼�ѵ��ڵ�λ����Ҫ����΢��;����δ����Ļ�������˸��ɣ�Ӧ���¼���
		{
			if((UNIT[i].AP_Avail==1)&&(UNIT[i].Status==UNIT_IN_GEN_AGC)&&(fabs(UNIT[i].AP_RtValue-UNIT[i].AP_Setp)>5))	//�л����Զ�ƫ�ƹ��󣬴���5MW				
				unit_stable_adj=0;
		}
		if((AGC_P_Set_Dev<=PLANT.AP_Deadband)&&(unit_stable_adj==0))	//����Ļ����й��ܸ���δ�����仯�����г������ƫ�ƴ���5MW����ԭֵ�����·�
		{
			for(i=1;i<=UNIT_NUMB;i++)
			{
				minor_adjust_p_tmp[i]=UNIT[i].AP_Setp;
			}
			return(YES);
		}
		for(i=1;i<=UNIT_NUMB;i++)
		{
			unit_rl_up[i]=UNIT[i].CurrentUplmt-UNIT[i].AP_RtValue;
			unit_rl_dn[i]=UNIT[i].AP_RtValue-UNIT[i].CurrentLowlmt;
			minor_adjust_p_tmp[i]=UNIT[i].AP_RtValue;
		}
		if(PLANT.ace>0) updown_flag=1;
		if(PLANT.ace<0) updown_flag=-1;
		tmp=(int)fabs(PLANT.ace);
		printf("ʵ���й��������ޣ�С���ɵ�����΢��ֵ=%d\n",tmp);	
	}
	else	//�й�����ֵС���ɵ�����ɵ�΢��
	{
		for(i=1;i<=UNIT_NUMB;i++)
		{
			unit_rl_up[i]=UNIT[i].CurrentUplmt-UNIT[i].AP_Setp;
			unit_rl_dn[i]=UNIT[i].AP_Setp-UNIT[i].CurrentLowlmt;
			minor_adjust_p_tmp[i]=UNIT[i].AP_Setp;
		}
		
		if(NoAGCUnit_flag==YES)
		{
			if(PLANT.P_Yggd_ChangeValue>0) updown_flag=1;
			if(PLANT.P_Yggd_ChangeValue<0) updown_flag=-1;
			tmp=abs((int)PLANT.P_Yggd_ChangeValue);
		}
		else
		{
			if(PLANT.P_adj>0) updown_flag=1;
			if(PLANT.P_adj<0) updown_flag=-1;
			tmp=abs(PLANT.P_adj);
		}
		printf("�й�����ֵС���ɵ�����΢��ֵ=%d\n",tmp);
	}

	if((aim_p<=PLANT.UplmtCurrentZone)&&(updown_flag==1))  //����������ȼ����з��䣨��������Ŀ��ֵС�ڵ�ǰ����Խ�����ɵ��������ޣ�
	{
		for(i=1;i<=PLANT.Num_AP_Avail;i++)
		{
			prv_id=minor_adjust[i];
			printf("����΢��%d���з��䣬΢��ֵ=%d\n",prv_id,tmp);
			if((unit_rl_up[prv_id]<AP_Adj_Step[prv_id])&&(unit_rl_up[prv_id]<tmp))
			{
				minor_adjust_p_tmp[prv_id]=UNIT[prv_id].CurrentUplmt;
				tmp-=unit_rl_up[prv_id];
				unit_rl_up[prv_id]=0;
			}
			else if((unit_rl_up[prv_id]>=AP_Adj_Step[prv_id])&&(tmp>=AP_Adj_Step[prv_id]))
			{
				minor_adjust_p_tmp[prv_id]+=AP_Adj_Step[prv_id];
				tmp-=AP_Adj_Step[prv_id];
				unit_rl_up[prv_id]-=AP_Adj_Step[prv_id];
			}
			else
			{
				minor_adjust_p_tmp[prv_id]+=tmp;
				tmp=0;
			}
			if((i==PLANT.Num_AP_Avail)&&(tmp>=1))
			{	
				i=0;
				if(tmp==tmp1) return(YES);
				tmp1=tmp;
			}
		}
	}
	else if((aim_p>=PLANT.LowlmtCurrentZone)&&(updown_flag==-1))  //����������ȼ����з��䣨��������Ŀ��ֵ���ڵ�ǰ����Խ�����ɵ��������ޣ�
	{
		for(i=1;i<=PLANT.Num_AP_Avail;i++)
		{
			prv_id=minor_adjust[i];
			printf("����΢��%d���з��䣬΢��ֵ=%d,",prv_id,tmp);
			if((unit_rl_dn[prv_id]<AP_Adj_Step[prv_id])&&(unit_rl_dn[prv_id]<tmp))
			{
				minor_adjust_p_tmp[prv_id]=UNIT[prv_id].CurrentLowlmt;
				tmp-=unit_rl_dn[prv_id];
				unit_rl_dn[prv_id]=0;
			}
			else if((unit_rl_dn[prv_id]>=AP_Adj_Step[prv_id])&&(tmp>=AP_Adj_Step[prv_id]))
			{
				minor_adjust_p_tmp[prv_id]-=AP_Adj_Step[prv_id];
				tmp-=AP_Adj_Step[prv_id];
				unit_rl_dn[prv_id]-=AP_Adj_Step[prv_id];
			}
			else
			{
				minor_adjust_p_tmp[prv_id]-=tmp;
				tmp=0;
			}
			if((i==PLANT.Num_AP_Avail)&&(tmp>=1))
			{	
				i=0;
				if(tmp==tmp1) return(YES);
				tmp1=tmp;
			}
			printf("��ʱ����ֵ=%d\n",minor_adjust_p_tmp[prv_id]);
		}
	}
	return(YES);
}

void AllocationCalculation() /*����ֻ�ڷ���̬����ɵ���������*/
{
	int i,i1,i2,i3,UnitUpVib[MAX_UNIT_NUMB+1]={0},UnitLowVib[MAX_UNIT_NUMB+1]={0},UpVibNum=0,UnitNumber=0,
       temp=0,LowVibNum=0,Compute_Num=0,Compute_Num1,num[MAX_UNIT_NUMB+1],flag[MAX_UNIT_NUMB+1],Result=0;
	int jzmp[MAX_UNIT_NUMB+1]={0},Current_Min=0,Current_Max=0,jzmp1[MAX_UNIT_NUMB+1]={0},
      mp[MAX_UNIT_NUMB+1]={0},Min,Max,p[MAX_UNIT_NUMB+1]={0};
	int Min1[4]={0},Min2[4]={0},Max1[4]={0},Max2[4]={0},Gap[4]={0},Allocation[4][MAX_UNIT_NUMB+1]={0},
         Efficiency[4]={0};
	int Direction=0,Zone1=0,Zone2=0,NotInVib=0;
	float sum_factor=0,sum_comp,sum_comp1;
	int min_adj_flag=0,aim_p;

	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(UNIT[i].StopAction==1)continue;
		if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].AP_Avail==1))
		{
			UNIT[i].XAP_Setp=UNIT[i].AP_Setp;  /*���ϴη�������Ϊ���η����ʼֵ*/
			sum_factor+=factor[i];  /*���������ϵ�����*/
			UnitNumber+=1;  /*����ɵ��ҷ���̬����̨��֮��*/
		}
	}
	min_adj_flag=Check_PreAllocate();

	i1=i2=0;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(UNIT[i].StopAction==1)continue;
		if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].AP_Avail==1))
		{
#ifdef PBG
			if(min_adj_flag==YES)
				mp[i]=jzmp[i]=minor_adjust_p_tmp[i];	/*������С���ɵ��ڽ������*/
			else
				mp[i]=jzmp[i]=(int)(PLANT.AGC_P_Set*factor[i]/sum_factor); /*����������������*/
#else
			mp[i]=jzmp[i]=(int)(PLANT.AGC_P_Set*factor[i]/sum_factor); /*����������������*/
#endif
			/*������������������ұ���Ŀ��ֵ���ϴη���ֵ���ڸ����鲽����ͳ�ƻ�����*/
			i3=CheckPowerVibZone(i, mp[i],0);
//			if((i3==0)&&(abs(mp[i]-UNIT[i].AP_Setp)>AP_Step[i]))	//changed by fengxun,2010-09-24
			if(i3==0)	NotInVib+=1;
			/*�������Ŀ��ֵ���ڻ��鵱ǰ�����������ޣ���������ΪĿ��ֵ����ͳ�ƿ��Ͽ�����������;
			�������Ŀ��ֵС�ڻ��鵱ǰ�����������ޣ���������ΪĿ��ֵ����ͳ�ƿ��¿�����������*/
			if(jzmp[i]>UNIT[i].CurrentUplmt)
			{
				jzmp[i]=UNIT[i].CurrentUplmt;
				if((jzmp[i]!=UNIT[i].AP_Max)&&(UNIT[i].VibrationNum!=0))
				{
					UnitLowVib[++i1]=i;
					LowVibNum+=1;
//					printf("LowVibNum=%d,jzmp[%d]=%d\n",LowVibNum,i,jzmp[i]);
				}
			}
			else if((jzmp[i]<UNIT[i].CurrentLowlmt)&&(UNIT[i].VibrationNum!=0))
			{
				jzmp[i]=UNIT[i].CurrentLowlmt;
				if(jzmp[i]!=UNIT[i].AP_Min)
				{
					UnitUpVib[++i2]=i;
					UpVibNum+=1;
//					printf("UpVibNum=%d,jzmp[%d]=%d\n",UpVibNum,i,jzmp[i]);
				}
			}
			if(AP_Adj_Step[i]>PLANT.AP_Deadband+30)	//������������ܿ��������ýϿ�
			{
				if(abs(jzmp[i]-UNIT[i].AP_Setp)<PLANT.AP_Deadband)
					jzmp[i]=UNIT[i].AP_Setp;/*�������Ŀ��ֵ���ϴη���ֵС������ֵ�����ϴη���ֵ����Ŀ��ֵ*/
			}
			else
			{
				if(abs(jzmp[i]-UNIT[i].AP_Setp)<AP_Adj_Step[i])
					jzmp[i]=UNIT[i].AP_Setp;/*�������Ŀ��ֵ���ϴη���ֵС�ڿ���������ֵ�����ϴη���ֵ����Ŀ��ֵ*/
			}
			
			/*ͳ��Ŀ��ֵ��ǰ����Խ������С������й�ֵ*/
			Min=(int)GetUnitCurrentMin(i,jzmp[i]);
			Max=(int)GetUnitCurrentMax(i,jzmp[i]);
			Current_Min+=Min;
			Current_Max+=Max;
			jzmp1[i]=jzmp[i];
//			printf("jzmp[%d]=%d,mp=%d,CurrentMin=%d,CurrentMax=%d\n",i,jzmp[i],mp[i],Min,Max);
		}
	}
	/*������л��鰴�������������䲻�����������Ҵ��ڲ����������Ŀ��ֵ��������������*/
	if(UnitNumber==NotInVib)
	{
		for(i=1;i<=UNIT_NUMB;i++)
		{
			if(UNIT[i].StopAction==1)continue;
			if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].AP_Avail==1))
				jzmp[i]=mp[i];
			UpVibNum=0;
			LowVibNum=0;
		}
	}
	if(UpVibNum>1)  /*�������Ϸ����п����¿��������鰴�մӴ�С˳������*/
	{
		for(i=1;i<UpVibNum;i++)
			for(i1=i+1;i1<=UpVibNum;i1++)
			{
				if((float)jzmp[UnitUpVib[i1]]/factor[UnitUpVib[i1]]>(float)jzmp[UnitUpVib[i]]/factor[UnitUpVib[i]])
				{
					temp=UnitUpVib[i];
					UnitUpVib[i]=UnitUpVib[i1];
					UnitUpVib[i1]=temp;
				}
			}
	}
	if(LowVibNum>1)/*�������·����п����Ͽ��������鰴�մ�С����˳������*/
	{
		for(i=1;i<LowVibNum;i++)
			for(i1=i+1;i1<=LowVibNum;i1++)
			{
				if((float)jzmp[UnitLowVib[i1]]/factor[UnitLowVib[i1]]<(float)jzmp[UnitLowVib[i]]/factor[UnitLowVib[i]])
				{
					temp=UnitLowVib[i];
					UnitLowVib[i]=UnitLowVib[i1];
					UnitLowVib[i1]=temp;
				}
			}
	}
	/*DirectionΪ1��ʾ���Ͽ�������Ϊ-1���¿�����*/
//	printf("!PLANT.AGC_P_Set=%d,Current_Min=%d,Current_Max=%d,PLANT.AP_Dev=%d\n",PLANT.AGC_P_Set,Current_Min,Current_Max,PLANT.AP_Dev);
	if(PLANT.AGC_P_Set<Current_Min)
		Direction=-1;
	else if(PLANT.AGC_P_Set>Current_Max)
		Direction=1;
	else
	{
		if(PLANT.AP_Dev>=0)
			Direction=1;
		else
			Direction=-1;
	}
	
	while(Compute_Num<=3)
	{	
		Min1[Compute_Num]=Min2[Compute_Num]=10000;
		Max1[Compute_Num]=Max2[Compute_Num]=-1;
		if((Direction==-1)&&(Compute_Num!=0))/*�¿�����*/
		{
			i2=UnitUpVib[Compute_Num];
			if(Compute_Num>UpVibNum)break;
			jzmp[i2]=jzmp1[i2]-AP_Step[i2];
			i3=CheckPowerVibZone(i2, jzmp[i2],0);
			if(i3!=0)
			   jzmp[i2]=UNIT[i2].Low_Vibration[i3];
			if(jzmp[i2]<UNIT[i2].AP_Min)jzmp[i2]=UNIT[i2].AP_Min;
			if(jzmp[i2]>UNIT[i2].AP_Max)jzmp[i2]=UNIT[i2].AP_Max;
		}
		else if((Direction==1)&&(Compute_Num!=0))/*�Ͽ�����*/
		{
			i2=UnitLowVib[Compute_Num];
			if(Compute_Num>LowVibNum)break;
			jzmp[i2]=jzmp1[i2]+AP_Step[i2];
			i3=CheckPowerVibZone(i2, jzmp[i2],0);
			if(i3!=0)
				jzmp[i2]=UNIT[i2].Up_Vibration[i3];
			if(jzmp[i2]<UNIT[i2].AP_Min)jzmp[i2]=UNIT[i2].AP_Min;
			if(jzmp[i2]>UNIT[i2].AP_Max)jzmp[i2]=UNIT[i2].AP_Max;
		}

//		Gap[Compute_Num]=PLANT.AGC_P_Set;   
//changed by fengxun,2012-04-09
		if(PLANT.ACE_over_adj==YES)  
			Gap[Compute_Num]=(int)(PLANT.p_sum_agc+PLANT.ace);
		else if(NoAGCUnit_flag==YES)
			Gap[Compute_Num]=PLANT.AGC_P_Set;
		else
			Gap[Compute_Num]=PLANT.AGC_P_Set;

		for(i=1;i<=UNIT_NUMB;i++)
		{
			if(UNIT[i].StopAction==1)continue;
			if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].AP_Avail==1))
			{
				if(jzmp[i]<UNIT[i].AP_Min)jzmp[i]=UNIT[i].AP_Min;
				if(jzmp[i]>UNIT[i].AP_Max)jzmp[i]=UNIT[i].AP_Max;
				Allocation[Compute_Num][i]=jzmp[i];
				Gap[Compute_Num]-=Allocation[Compute_Num][i];
			}
		}
		
		Compute_Num1=0;
		while((Gap[Compute_Num]!=0)&&(Compute_Num1<=10))
		{
			Compute_Num1++;
			for(i=1;i<=UNIT_NUMB;i++)
			{
				num[i]=0;	 
				flag[i]=0;
			}
			for(i=1;i<=UnitNumber;i++)
			{
				i2=0;Max=-32767;
				for(i3=1;i3<=UNIT_NUMB;i3++)
				{
					if(UNIT[i3].StopAction==1)continue;
					if((UNIT[i3].Status==UNIT_IN_GEN_AGC)&&(UNIT[i3].AP_Avail==1)&&(flag[i3]==0))
					{ 
						if(Allocation[Compute_Num][i3]/factor[i3]>=Max)
						{
							Max=Allocation[Compute_Num][i3];
							i2=i3;
						}
					}
				}
				if(i2!=0)
				{
					num[i]=i2;	  /*�Ӵ�С��˳������*/
					flag[i2]=1;   
				} 
			}
			for(i=1;i<=UnitNumber;i++)
			{				
				if(Gap[Compute_Num]<0)
					i2=num[i];
				else
					i2=num[UnitNumber+1-i]; 
				
				if((UNIT[i2].Status==UNIT_IN_GEN_AGC)&&(UNIT[i2].AP_Avail==1))
				{
					Min=GetUnitCurrentMin(i2,Allocation[Compute_Num][i2]);
					Max=GetUnitCurrentMax(i2,Allocation[Compute_Num][i2]);
					p[i2]=Allocation[Compute_Num][i2];
					printf("Min=%d,Max=%d,Allocation[%d][%d]=%d\n",Min,Max,Compute_Num,i2,p[i2]);
					if(abs(Gap[Compute_Num])>AP_Step[i2])
					{
						if(Gap[Compute_Num]>0)
							Allocation[Compute_Num][i2]+=AP_Step[i2];
						else
							Allocation[Compute_Num][i2]-=AP_Step[i2];
						if((Direction==1)&&(Allocation[Compute_Num][i2]<jzmp[i2])&&(Compute_Num1<=2))
//						if((Gap[Compute_Num]>0)&&(Allocation[Compute_Num][i2]<jzmp[i2])&&(Compute_Num1<=2))
							Allocation[Compute_Num][i2]=jzmp[i2];
						if((Direction==-1)&&(Allocation[Compute_Num][i2]>jzmp[i2])&&(Compute_Num1<=2))
//						if((Gap[Compute_Num]<0)&&(Allocation[Compute_Num][i2]>jzmp[i2])&&(Compute_Num1<=2))
							Allocation[Compute_Num][i2]=jzmp[i2];
						if(Allocation[Compute_Num][i2]>Max)Allocation[Compute_Num][i2]=Max;
						if(Allocation[Compute_Num][i2]<Min)Allocation[Compute_Num][i2]=Min;   
					}
					else
					{	
						Allocation[Compute_Num][i2]+=Gap[Compute_Num];
//						if((Direction==1)&&(Allocation[Compute_Num][i2]<jzmp[i2])&&(Compute_Num1<=2))
						if((Gap[Compute_Num]>0)&&(Allocation[Compute_Num][i2]<jzmp[i2])&&(Compute_Num1<=2))
							Allocation[Compute_Num][i2]=jzmp[i2];
//						if((Direction==-1)&&(Allocation[Compute_Num][i2]>jzmp[i2])&&(Compute_Num1<=2))
						if((Gap[Compute_Num]<0)&&(Allocation[Compute_Num][i2]>jzmp[i2])&&(Compute_Num1<=2))
							Allocation[Compute_Num][i2]=jzmp[i2];
						if(Allocation[Compute_Num][i2]>Max)Allocation[Compute_Num][i2]=Max;
						if(Allocation[Compute_Num][i2]<Min)Allocation[Compute_Num][i2]=Min;
					}
					if(Allocation[Compute_Num][i2]>UNIT[i2].AP_Max)
						Allocation[Compute_Num][i2]=UNIT[i2].AP_Max;
					else if(Allocation[Compute_Num][i2]<UNIT[i2].AP_Min)
						Allocation[Compute_Num][i2]=UNIT[i2].AP_Min;
					Gap[Compute_Num]-=Allocation[Compute_Num][i2]-p[i2];
				}
			}
		}
		
		for(i=1;i<=UNIT_NUMB;i++)
		{
			if(UNIT[i].StopAction==1)continue;
			if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].AP_Avail==1))
			{
				Zone1=CalcUnitZone(i, Allocation[Compute_Num][i]);
				Zone2=CalcUnitZone(i, mp[i]);
				
				if(Zone1==Zone2)
				{
					if(Allocation[Compute_Num][i]>Max1[Compute_Num])
						Max1[Compute_Num]=Allocation[Compute_Num][i];
					if(Allocation[Compute_Num][i]<Min1[Compute_Num])
						Min1[Compute_Num]=Allocation[Compute_Num][i];
				}
				else 
				{
					if(Allocation[Compute_Num][i]>Max2[Compute_Num])
						Max2[Compute_Num]=Allocation[Compute_Num][i];
					if(Allocation[Compute_Num][i]<Min2[Compute_Num])
						Min2[Compute_Num]=Allocation[Compute_Num][i];
				}
//				printf("Allocation[%d][%d]=%d,",Compute_Num,i,Allocation[Compute_Num][i]);
			} 
		}
//		printf("\nGap=%d,Min1=%d,Max1=%d,Min2=%d,Max2=%d\n",Gap[Compute_Num],Min1[Compute_Num],
//			Max1[Compute_Num],Min2[Compute_Num],Max2[Compute_Num]);
		Compute_Num++;
	}

	for(i=0;i<3;i++)
	{
		if(Direction==1){if(i>=LowVibNum)break;}
		if(Direction==-1){if(i>=UpVibNum)break;}
		printf("Gap[%d]=%d,Gap[%d]=%d\n",i,Gap[i],i+1,Gap[i+1]);
		printf("Direction=%d,Min1[%d]=%d,Max1[%d]=%d,Min2[%d]=%d,Max2[%d]=%d\n",Direction,
				  i,Min1[i],i,Max1[i],i,Min2[i],i,Max2[i]);
		
		if(((abs(abs(Gap[i])-abs(Gap[i+1]))>PLANT.VZ_Deadband)&&(abs(Gap[i+1])<abs(Gap[i])))	//changeded by fengxun,2010-09-22
		  ||((Min1[i]-Max2[i]>3*PLANT.VZ_Deadband)&&(Min1[i]!=10000)&&(Max2[i]!=-1)&&(Gap[i+1]==0))
		  ||((Min2[i]-Max1[i]>3*PLANT.VZ_Deadband)&&(Min2[i]!=10000)&&(Max1[i]!=-1)&&(Gap[i+1]==0)))
		{
			Result=i+1;
		}
		else
		{
			Result=i;
			break;
		}
	}
	sum_comp=0;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if(UNIT[i].StopAction==1)continue;
		if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].AP_Avail==1))
		{
			UNIT[i].XAP_Setp=Allocation[Result][i];
			printf("in AllocationCalculation:Result=%d,UNIT[%d].XAP_Setp=%d\n",Result,i,UNIT[i].XAP_Setp);
		}
		else if((NoAGCUnit_flag==YES)&&(UNIT[i].P_balance==YES))
			UNIT[i].XAP_Setp=UNIT[i].AP_Yggd;
		else
			UNIT[i].XAP_Setp=UNIT[i].AP_RtValue;
		sum_comp+=UNIT[i].XAP_Setp;
	}  
/*������AGC�޷��������й�ʱ�������������ֶ������ǳ�����鸺��ֵ����ָ����������*/

	printf("PLANT.AP_Setpoint=%f,sum_comp=%f,%s\n",PLANT.AP_Setpoint,sum_comp,DB_NAME_AGC_COMP_DERECT);
	
	if(fabs(PLANT.AP_Setpoint-sum_comp)>PLANT.AP_Deadband) 
	{
		GetResultBy_P_Space();
		sum_comp1=0;
		for(i=1;i<=PLANT.Num_AP_Avail;i++) sum_comp1+=p_space_result.Unit_Result[i].unit_P;
		sum_comp1+=PLANT.p_sum_no_agc;
		if(fabs(sum_comp1-PLANT.AP_Setpoint)<fabs(sum_comp-PLANT.AP_Setpoint))
		{
			for(i=1;i<=PLANT.Num_AP_Avail;i++)
				UNIT[p_space_result.Unit_Result[i].unit_id].XAP_Setp=p_space_result.Unit_Result[i].unit_P;
			sum_comp=sum_comp1;
		}		
	}
	if(PLANT.AP_Setpoint-sum_comp>5)
	{
		AGC_UpdateRTDB_IND ( DB_NAME_AGC_COMP_DERECT, INCREASE );
		AGC_UpdateRTDB_IND (DB_NAME_AGC_LMT_DB_ALM,YES);
		AGC_UpdateRTDB_ANA (DB_NAME_AGC_LMT_DB_ADVICE,(int)(PLANT.AP_Setpoint-sum_comp));
	}
	else if(PLANT.AP_Setpoint-sum_comp<-5)
	{
		AGC_UpdateRTDB_IND ( DB_NAME_AGC_COMP_DERECT, DECREASE );
		AGC_UpdateRTDB_IND (DB_NAME_AGC_LMT_DB_ALM,YES);
		AGC_UpdateRTDB_ANA (DB_NAME_AGC_LMT_DB_ADVICE,(int)(sum_comp-PLANT.AP_Setpoint));
	}
	else
	{
		AGC_UpdateRTDB_IND ( DB_NAME_AGC_COMP_DERECT, NOT );
		AGC_UpdateRTDB_IND (DB_NAME_AGC_LMT_DB_ALM,NOT);
		AGC_UpdateRTDB_ANA (DB_NAME_AGC_LMT_DB_ADVICE,0);
	}
}

void AGC_PowerAllocation()
{ 
	int i;
	
/*	if(PLANT.AP_WorkSP>PLANT.AP_Max)
		PLANT.AP_WorkSP=PLANT.AP_Max;
	else if(PLANT.AP_WorkSP<PLANT.AP_Min)
		PLANT.AP_WorkSP=PLANT.AP_Min;
	PLANT.AGC_P_Set=PLANT.AP_WorkSP-PLANT.p_sum_no_agc; */
	if(PLANT.AP_Setpoint>PLANT.AP_Max)
		PLANT.AP_Setpoint=PLANT.AP_Max;
	else if(PLANT.AP_Setpoint<PLANT.AP_Min)
		PLANT.AP_Setpoint=PLANT.AP_Min;
	PLANT.AGC_P_Set=PLANT.AP_Setpoint-PLANT.p_sum_no_agc;
	AGC_P_Set_Dev = PLANT.AGC_P_Set-PLANT.Last_AGC_P_Set;
	PLANT.Last_AGC_P_Set=PLANT.AGC_P_Set;
	PLANT.AP_Dev=PLANT.AGC_P_Set-PLANT.p_sum_agc;
	
	CalculatePowerZone();
	MinorAdjustPrv();	//added by fengxun for PBG,2010-11-18
	AllocationCalculation();
	if(NoAGCUnit_flag==1)	//����ƽ����������added by fengxun for PBG,2012-04-09
	{
		NoAGCUnit_flag=0;
		PLANT.P_Yggd_ChangeValue=0;
	}

	for(i=1;i<=UNIT_NUMB;i++)
	{
		if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&(UNIT[i].AP_Avail==1)&&(UNIT[i].StopAction!=1))
		{
			if(UNIT[i].XAP_Setp>UNIT[i].AP_Max)UNIT[i].XAP_Setp=UNIT[i].AP_Max;
			if(UNIT[i].XAP_Setp<UNIT[i].AP_Min)UNIT[i].XAP_Setp=UNIT[i].AP_Min;
		}
	}
}

void Unit_Supervision()
{
	int i;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		if((UNIT[i].StartAction==1)&&(UNIT[i].Status==UNIT_IN_GEN_AGC))
			UNIT[i].StartAction=0;
		if((UNIT[i].StopAction==1)&&(UNIT[i].Status!=UNIT_IN_GEN_AGC))
		{
			UNIT[i].StopAction=0;
			AGC_UpdateRTDB_IND ( DB_NAME_Control_Command[i], WCZTHM );
		}
	}
}

int CheckFault()
{
	float plant_unrun_dn[3],plant_unrun_up[3]; 	
	float p_fr_dn,p_fr_up,rt_fr; 
	float p_lmt_dn,p_lmt_up,p_remote; 
	int iec_down,vib_flag;
	int i;
		
	/*�ж�ȫ��������*/
	vib_flag=0;
	for(i=0;i<3;i++)
	{
		plant_unrun_dn[i]=ReadDB_ANA( DB_NAME_QCUNRUN_DNLMT[i+1] );
		plant_unrun_up[i]=ReadDB_ANA( DB_NAME_QCUNRUN_UPLMT[i+1] );
		if(fabs(plant_unrun_up[i]-plant_unrun_dn[i])<5) continue;	//for PBG����С�����������м��
		if((PLANT.AP_Setpoint>plant_unrun_dn[i]+8)&&(PLANT.AP_Setpoint<plant_unrun_up[i]-8))	//ȫ��������Լ��,AGC����,��������8MW
		{
			printf("ȫ���й��趨ֵ%f��ȫ���й�������%7.2f~%7.2f�ڣ���\n",PLANT.AP_Setpoint,plant_unrun_dn[i],plant_unrun_up[i]);
			vib_flag=1;
			break;
		}
		else if((PLANT.AP_Setpoint<=plant_unrun_dn[i]+8)&&(PLANT.AP_Setpoint>plant_unrun_dn[i])) 
		{
			PLANT.AP_Setpoint=plant_unrun_dn[i];
		}
		else if((PLANT.AP_Setpoint>=plant_unrun_up[i]-8)&&(PLANT.AP_Setpoint<plant_unrun_up[i]))
		{
			PLANT.AP_Setpoint=plant_unrun_up[i];
		}
	}
	if(vib_flag==1)
	{
		AGC_UpdateRTDB_IND ( DB_NAME_ALM_Plant_UN_RUN, YES);
		return(HANGUP);
	}
	else
	{
		AGC_UpdateRTDB_IND ( DB_NAME_ALM_Plant_UN_RUN, NOT);
	}
	/*�ж�ͨѶ����AGC�˳�*/	
	/* removed by yyp 2012.12.04
	iec_down=ReadDB_IND(DB_NAME_DD104_DOWN);	//ע�⣬�˵�����̨ͨѶվ104״̬����ó��ļ���㣬ֱ�������ж�
	if((iec_down==YES)&&(PLANT.Control_Right==1))
	{
		iec_flag++;
		if(iec_flag>5)
		{
			printf("���ȿ�����IEC104ͨѶ�жϳ���5���������ڣ���AGC�˳���\n");
			AGC_UpdateRTDB_IND ( DB_NAME_Control_Right,  NOT );
		}
		else
			return(HANGUP);
	}
	else
		iec_flag=0;
	*/
	/*�ж�Ƶ��Խ���й���������*/
/*	p_fr_up = ReadDB_ANA( DB_NAME_AGC_FRUPLMT );
	p_fr_dn = ReadDB_ANA( DB_NAME_AGC_FRDOWNLMT );*/
	p_fr_up = 50.05;
	p_fr_dn = 49.95;
	for(i=1;i<FREQUENCY_NUM+1;i++)
	{
		rt_fr = ReadDB_ANA( DB_NAME_AGC_RTFR[i] );
		if(rt_fr<45||rt_fr>55) continue;		//ȥ����Ч��Ƶ�ʲɼ�ֵ
		if((rt_fr<p_fr_dn)&&(PLANT.AP_Setpoint<PLANT.p_sum-PLANT.AP_Deadband))
		{
			AGC_UpdateRTDB_IND ( DB_NAME_AGC_FRLOW_ERR, YES);
			return(HANGUP);
		}
		else
		{
			AGC_UpdateRTDB_IND ( DB_NAME_AGC_FRLOW_ERR, NOT);
		}
		if((rt_fr>p_fr_up)&&(PLANT.AP_Setpoint>PLANT.p_sum+PLANT.AP_Deadband))
		{
			AGC_UpdateRTDB_IND ( DB_NAME_AGC_FRHIGH_ERR, YES);
			return(HANGUP);
		}
		else
		{
			AGC_UpdateRTDB_IND ( DB_NAME_AGC_FRHIGH_ERR, NOT);
		}
	}
	/*�ж�ˮ������Խ�ޱ���*/
	/*
	if((Watermsg.WaterHead<MinWaterhead)||(Watermsg.WaterHead>MaxWaterhead))
	{
		printf("ˮ������Խ�ޱ�����Watermsg.WaterHead=%f,MinWaterhead=%d,MaxWaterhead=%f\n",Watermsg.WaterHead,MinWaterhead,MaxWaterhead);
		AGC_UpdateRTDB_IND ( DB_NAME_WATERINFO_ERR, YES);
		return(HANGUP);
	}
	else
	{
		AGC_UpdateRTDB_IND ( DB_NAME_WATERINFO_ERR, NOT);
	}
	*/
	p_remote = ReadDB_ANA ( DB_NAME_Remote_Setpoint );
		
	/*�ж��й����ڲ���Խ�ޱ���*/
	/*
	if((abs(PLANT.ace)>PLANT.AP_ChangeMax)&&(PLANT.Mode!=AGC_MODE_NONE)&&(abs(PLANT.P_adj)>PLANT.AP_ChangeMax))
	{
		printf("�й����ڲ���Խ�ޱ�����Watermsg.WaterHead=%f,MinWaterhead=%d,MaxWaterhead=%f\n",Watermsg.WaterHead,MinWaterhead,MaxWaterhead);
		PLANT.AP_Setpoint=PLANT.p_sum;
		AGC_UpdateRTDB_IND  ( DB_NAME_ALM_ChangeMax, YES );   
		set_p_flag=1;
		return(HANGUP);
	}
	else
	{
		AGC_UpdateRTDB_IND  ( DB_NAME_ALM_ChangeMax, NOT );   
	}
	*/
	AGC_UpdateRTDB_IND  ( DB_NAME_ALM_ChangeMax, NOT ); 
	/*�ж��й�����Խ�����ޱ���*/
	p_lmt_dn = ReadDB_ANA ( DB_NAME_P_DOWNLMT );
	p_lmt_up = ReadDB_ANA ( DB_NAME_P_UPLMT );

	if((PLANT.AP_Setpoint<p_lmt_dn-5)&&(PLANT.Mode!=AGC_MODE_NONE))	//5MWΪ����
	{
		AGC_UpdateRTDB_IND  ( DB_NAME_AGC_PLOW_ERR, YES );
		AGC_UpdateRTDB_IND  ( DB_NAME_AGC_POVER_ERR, NOT );
		set_p_flag=1;
		return(HANGUP);
	}
	else
	{
		AGC_UpdateRTDB_IND  ( DB_NAME_AGC_PLOW_ERR, NOT );   
	}
	
	if((PLANT.AP_Setpoint>p_lmt_up+5)&&(PLANT.Mode!=AGC_MODE_NONE))	//5MWΪ����
	{
		PLANT.AP_Setpoint=PLANT.p_sum;
		AGC_UpdateRTDB_IND  ( DB_NAME_AGC_POVER_ERR, YES );   
		AGC_UpdateRTDB_IND  ( DB_NAME_AGC_PLOW_ERR, NOT ); 
		set_p_flag=1;
		return(HANGUP);
	}
	else
	{
		AGC_UpdateRTDB_IND  ( DB_NAME_AGC_POVER_ERR, NOT );   
	}
	set_p_flag=0;
	/*�жϻ����й�ͨ�������״̬����changed by fengxun,2011-12-25*/
	for(i=1;i<=UNIT_NUMB;i++)
	{		
		if(Check_Unit_P_Status(i)==QUIT)
		{
			AGC_UpdateRTDB_IND  ( DB_NAME_QC_AGC,  NOT );
			return(QUIT);
		}
	}
	return(0);
}

void Check_ACE_change()
{
	int unit_stable;
	PLANT.ace= PLANT.AP_Setpoint-PLANT.p_sum;
	if((PLANT.P_adj==0) && (fabs(PLANT.ace)>PLANT.AP_Deadband) && (fabs(PLANT.last_ace)<PLANT.AP_Deadband)&&(PLANT.P_Balance!=1))
	{		
		PLANT.ACE_over_adj=YES;
	}
	else
	{
		PLANT.ACE_over_adj=NOT;
	}
	PLANT.last_ace=PLANT.ace;
}

void AGC_Module()
{
//	float AP_WorkSP;
	int AGC_Recalc,check_sbo;
	int i;
	AGC_Recalc=0;
	check_sbo=0;
//	AP_WorkSP=PLANT.AP_Setpoint;
	PLANT.P_adj=(int)(PLANT.AP_Setpoint-PLANT.AP_WorkSP);	/*��ǰ����ֵ����һ�θ����Ĳ�ֵ*/
	Check_ACE_change();	//added by fengxun 2010-11-20,�ж��Ƿ��Ǹ��ɲ�����С��Χ����
//	if((abs(PLANT.P_adj) > PLANT.AP_Deadband) && (fabs(PLANT.ace)>PLANT.AP_Deadband))	
	if(abs(PLANT.P_adj) > PLANT.AP_Deadband) 	
	{
		printf("�趨ֵ�仯��ACE�����й��������%d:ԭ�趨ֵ=%f,��ǰ�趨ֵ=%f.\n",PLANT.AP_Deadband,PLANT.AP_WorkSP,PLANT.AP_Setpoint);
		PLANT.AP_WorkSP = PLANT.AP_Setpoint;
		AGC_Recalc = 1;
	}
	else if(PLANT.ACE_over_adj==YES)
	{
		printf("ȫ��ʵ���й�ֵ����������!ȫ���й��趨ֵ=%f,ȫ���й�ʵ��ֵ=%f����ֵ�����й��������%d\n",PLANT.AP_Setpoint,PLANT.p_sum,PLANT.AP_Deadband);
		AGC_Recalc=1;
	}
	else if(NoAGCUnit_flag==1)
	{
		printf("ȫ������ƽ�����!\n");
		AGC_Recalc = 1;
	}
	/*	if(PLANT.Num_AP_Avail!=PLANT.Last_Num_AP_Avail)
	{	
		printf("���ػ���̨�������仯!Last_Num_AP_Avail=%f,Num_AP_Avail=%d\n",PLANT.Last_Num_AP_Avail,PLANT.Num_AP_Avail);
		PLANT.Last_Num_AP_Avail=PLANT.Num_AP_Avail;
		AGC_Recalc=1;
	}*/	

	//yyp ����
	

	check_sbo=CheckFault();	//���AGC��ȫ��ָ��Ϸ���

	check_sbo = 0;
	
	if(check_sbo==HANGUP)	//AGC��������ִ��ָ��
	{ 
		AGC_Recalc=0;
//		PLANT.AP_Setpoint=PLANT.p_sum;
		for ( i= 1; i<= UNIT_NUMB; i++ )  
		{
			UNIT[i].CommandSendSbo = NOT;
			if(UNIT[i].Status==UNIT_IN_GEN_AGC)
				UNIT[i].AP_Setp=(int)(UNIT[i].AP_RtValue+0.5);				
		}
//		PLANT.AP_WorkSP=PLANT.p_sum;
		return;
	}
	else if(check_sbo==QUIT)  //AGC�����˳�
	{
		InitData();
		PLANT.Mode=AGC_MODE_NONE;
		AGC_Recalc=0;
	}	

	if((PLANT.Mode==AGC_MODE_NONE)||(PLANT.Num_AP_Avail==0)) /*û�й��ܣ��޳������*/
		return;
	if(AGC_Recalc==1)
	{
		PLANT.XStrStp_Recalc=1;
		AGC_PowerAllocation();
		FillCommandBuf();
	}
	else
		Check_Cmd_ReSend();				//����ϴ������������ֵ�Ƿ�仯���Ƿ���Ҫ�������added by fengxun 2011-11-23
	if(PLANT.Auto_StartStop==1)
	{
		if(PLANT.XStrStp_Recalc==1)
		{
			StartStopCalculation();
			StartStopModule();	
		}
		Unit_Supervision();
		FillCommandBuf();
	}	
}

void Unit_Remote_control()
{
	int changed_flag,i,tmp;	
/*	char sbo_db_name[80];
	for(i=1;i<=UNIT_NUMB;i++)
	{
			UNIT[i].RemoteControlable=0;
			strcpy ( sbo_db_name, DB_NAME_SD_YK[i] );
      strcat ( sbo_db_name, "_YES" );
      sbo_flag = InterLock_Judge ( sbo_db_name );
      if(sbo_flag==1) UNIT[i].RemoteControlable=1;      
  }*/
  
	for(i=1;i<=UNIT_NUMB;i++)
	{
		UNIT[i].AP_Chang_Max=ReadDB_ANA(DB_NAME_AGCYG_STEP[i]);
	}
	tmp=0;
	changed_flag=0;
	for(i=1;i<=UNIT_NUMB;i++)
	{
		tmp=tmp+UNIT[i].RemoteControlable;
		if(UNIT[i].RemoteControlable!=1)
			AGC_UpdateRTDB_ANA(DB_NAME_SD_PSet[i],UNIT[i].AP_RtValue);
	}
	if(tmp==0) 
	{	
		return;  	
	}
	else
	{
		for(i=1;i<=UNIT_NUMB;i++)
		{
			tmp=(int)ReadDB_ANA(DB_NAME_SD_PSet[i]);
			printf("tmp=%d,UNIT[i].AP_Max=%f,UNIT[i].AP_Min=%f,UNIT[i].AP_Chang_Max=%f,fabs(UNIT[i].AP_RtValue-tmp)=%f\n",tmp,UNIT[i].AP_Max,UNIT[i].AP_Min,UNIT[i].AP_Chang_Max,fabs(UNIT[i].AP_RtValue-tmp));
			if(UNIT[i].RemoteControlable==1)
			{    
				if((tmp>UNIT[i].AP_Max)||(tmp<UNIT[i].AP_Min) )
				{
					AGC_UpdateRTDB_IND  ( DB_NAME_Remote_OverPLmtALM[i], YES );									/*��̨����Խ��*/
				}
				else if(fabs(UNIT[i].AP_RtValue-tmp)>UNIT[i].AP_Chang_Max)
				{
					AGC_UpdateRTDB_IND  ( DB_NAME_Remote_OverBCLmtALM[i], YES );									/*��̨���鲽��Խ��*/
				}														
				else if((UNIT[i].Status==UNIT_IN_GEN_AGC)&&((fabs(UNIT[i].AP_RtValue-tmp)>2.5)))		/*���鴦�ڷ���̬�ҵ�������ֵ�뵥��ʵ��ֵ֮���2MW*/
				{
					changed_flag=1;                    		/*�й���Ҫ����*/
					if(ReadDB_IND(DB_NAME_Remote_OverPLmtALM[i])==1) AGC_UpdateRTDB_IND  ( DB_NAME_Remote_OverPLmtALM[i], NOT );									/*��̨����Խ���źŸ���*/
					if(ReadDB_IND(DB_NAME_Remote_OverBCLmtALM[i])==1) AGC_UpdateRTDB_IND  ( DB_NAME_Remote_OverBCLmtALM[i], NOT );									/*��̨���鲽��Խ���źŸ���*/
					UNIT[i].XAP_Setp=(float)tmp;
					UNIT[i].Status=UNIT_IN_GEN_AGC;   //ע�⣺�ñ���������֤�����ʱ�����ڷ���̬
					printf("+++++++++%d�Ż��鵱ǰ�й�Ϊ%5.1f,ʡ����ǰ�´��������й��趨ֵΪ%5.1f+++++++++++++++++++++++++++\n",i,UNIT[i].AP_RtValue,UNIT[i].XAP_Setp);
				}
			}
		}
		if(changed_flag==1) FillCommandBuf();
	}
  /*ʡ������״̬�½�ȫ��ʵ��ֵд��ʡ��ȫ���������й�ȫ������ֵ��*/
	//yyp
	AGC_UpdateRTDB_ANA (DB_NAME_Remote_Setpoint,  PLANT.p_sum );
	AGC_UpdateRTDB_ANA (DB_NAME_AP_Setpoint,  PLANT.p_sum );
}

void main(int argc,char *argv[])
{
	int sbo_flag;

#ifdef WindowsOS
	WORD   		wvr;
	WSADATA 	WSAData;
	int 		status;
	wvr=MAKEWORD(2,2);
	if ((status = WSAStartup(wvr, &WSAData)) != 0) 
	{
		printf("\nplcscan.c:: %d is the err\n",status);
	}
#endif

	gethostname(hostname,20);
	printf("hostname =%s\n",hostname);
#ifdef SUNOS 
	SetModuleName("AGC");
	SetErrLogMode(argc,argv);
	CreateLockFile(".agc.lock");

	signal( SIGINT, SIGINT_handler);
#endif
	if(-1==MountDB(DATABASE_NAME))
	{
		Err_log("Fail to MountDB!\n");
		exit(-1);
	} 
	
	if(!lan_out_init())
	{
		Err_log("Fail to init lan module!\n");
		exit(-1);
	}
	ReadTime ();
	oldday = ntime->tm_mday;

	ReadAGCDefFile();
	if(CurveSetFuc==1)
		ReadCurveDefFile();
	ReadWaterHeadPowerDefFile();
	InitData();

//	src_id = GetHost_Cmd ();		  	

//	signal( SIGINT, SIGINT_handler);
/*	if ( InterLockFileLoad () == -1 )
	{
		printf ( "in AGC: Load InterLock.dat error!\n" );
		exit ( 0 );
	}
*/
	
#ifdef SUNOS
	sprintf(logfilename, "/home/ems/h9000/his/agc/AGCcmd.%02d",ntime->tm_mday);
#else
	sprintf(logfilename, "/home/ems/h9000/his/agc/AGCcmd.%02d",ntime->tm_mday);
#endif
	ReadAGC_DataFromRTDB();
	InitialAGC_Data_On_Screen ();

	for (;;)
	{
		ReadTime ();
		LogFileChangeDayAndWriteTime();
		ReadAGC_DataFromRTDB();
		sbo_flag = ReadDB_IND( DB_NAME_AGC_STATE );		
		if(sbo_flag==1)
		{
			if(AGC_Loop>=AGC_Period)
			{	
				printf("\n-------------New Round----------------\n");
				AGC_Loop=0;
				AGC_Module();
         /*added by fengxun for Single Unit Remote-controling*/
				if(PLANT.Remote_SingleUnit_Control==1)
					Unit_Remote_control();
				else
					continue;
			}		  				
		}
		else
		{
			AGC_UpdateRTDB_ANA ( DB_NAME_AP_Setpoint,  PLANT.p_sum );
			InitialAGC_Data_On_Screen ();
		}
	
		if(Number_ANA>0)
		{
			lan_out ((char *)&ml_buf_ANA,lanhd_ANA,(unsigned char)0);
			Number_ANA=0;
		}
		if(Number_IND>0)
		{
			lan_out ((char *)&ml_buf_IND,lanhd_IND,(unsigned char)0);
			Number_IND=0;
		}
		AGC_Loop++;
#ifdef SUNOS
	sleep(1);
#else
	Sleep(1000);
#endif
	}
}
