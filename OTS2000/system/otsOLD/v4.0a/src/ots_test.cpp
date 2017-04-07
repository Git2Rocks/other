// ots_test.cpp : Defines the entry point for the console application.
//
#define DEBUG
#include "stdafx.h"
#include <QApplication>
#include <QtGui>
#include <QtCore/QCoreApplication>
#include <QSqlDatabase>   
#include <QSqlQuery>
#include <QVariant>
#include "/home/ems/system/ots/ots_hdb/inc/ots_hdb.h" 
#include "/home/ems/system/ots/ots_hdb/inc/ots.h"

CURVE_SHM_DATA	*pCurve;
void hdb_test();
void insert_test();
void update_test();
void delete_test();
void select_test();
void new_task();
int LoadSimulog();
int SetObjCond();

int main(int argc, char* argv[])
{
	int mode,speed,i,type,tmp;

	if(MountDB(DB_NAME) == -1)
	{
		printf("\n==== otstest.c: call MountDB(DATABASE_NAME) error\n");		
		exit(0);
	}
	if(lan_init_all() == FALSE)
	{
		printf("\n==== otstest.c: call Lan_init_all() error\n");		
		exit(0);
	}
	ReadOtsDefFile();	
	//yyp debug
	/*
	pCurve = (CURVE_SHM_DATA*) LinktoShareMem( SHM_TREND_KEY_CHAR );
	if( pCurve == (CURVE_SHM_DATA*)-1 )
	{
		Err_log(  "Fail to  Real curve shm");
		printf("otstest: RealCurve::  LinktoShareMem Error !!!!\n");
		exit(0) ;
	}

	if(get_hdb_shm()==FALSE)
	{
		exit(0);
	}

	get_ots_shm();

	//���µ����ݿ�ӿڿ����

	if(ConnectHDB()!=(int)TRUE)
	{
		printf("�������ݿ�ʧ��\n");
		//return FALSE;
	}
	else
	{
		printf("�������ݿ�ɹ�\n");
		if( InitOTSHdb()!=TRUE )
		{
			printf("InitOTSHdb ʧ��\n");
			return FALSE;
		}
		else
		{
			printf("InitOTSHdb �ɹ�\n");
		}
	}

	*/

	i=0;
	for(;;)
	{
		printf("\n\n\n======== ��ѡ��: ========\n"); 
		printf("\n\n   01.�鿴���湲����"); 

		printf("\n\n   02.д�����ӻ��湲����"); 

		printf("\n\n   03.�����ٶ�ѡ��"); 

		printf("\n\n   04.ֹͣ/���з���"); 

		printf("\n\n   05.�鿴ʵʱ���߹�����"); 

		printf("\n\n   06.������ʷ�����"); 

		printf("\n\n   07.�´�������"); 

		printf("\n\n   08.��ʱ����"); 

		printf("\n\n   09.���������豸���������������"); 

		printf("\n\n   0.�˳�\n");

		printf("\n====������(1-10):");
		  
		scanf("%d",&mode);
		if(mode==1)
		{
			printf(" \n(^_^) ots share memory:(^_^)\n");
			printf("\n runflag = %d",shm_ots_addr->runflag);
			printf("\n speed = %d",shm_ots_addr->speed);
			printf("\n childflag = %d",shm_ots_addr->childflag);
			printf("\n screen pos = [%d,%d]",shm_ots_addr->child.pos.x,shm_ots_addr->child.pos.y);
			printf("\n delay = %d ",shm_ots_addr->child.time_len);
			printf("\n child file name = %s ",shm_ots_addr->child.name);
			printf("\n dbinflag = %d",shm_ots_addr->dbinflag);
			printf("\n dbinname = %s ",shm_ots_addr->dbinname);
			printf("\n cur dbinname = %s ",shm_ots_addr->data_point.curname);
			printf("\n cur yc num = %d ",shm_ots_addr->data_point.ycnum);
			printf("\n cur yx num = %d ",shm_ots_addr->data_point.yxnum);
			printf("\n");
		}
		else if(mode==2)
		{
			printf("\n====������childflag:");
			scanf("%d",&tmp);			
			shm_ots_addr->childflag = tmp;
			printf("\n====������x:");
			scanf("%d",&tmp);	
			shm_ots_addr->child.pos.x = tmp;
			printf("\n====������y:");
			scanf("%d",&tmp);	
			shm_ots_addr->child.pos.y = tmp;
			printf("\n====������time_len:");
			scanf("%d",&tmp);	
			shm_ots_addr->child.time_len = tmp;
			printf("\n====������dbinflag:");
			scanf("%d",&tmp);	
			shm_ots_addr->dbinflag = tmp;
			strcpy(shm_ots_addr->child.name,"bs_jzby1f.sbin");
			strcpy(shm_ots_addr->dbinname,"bs_jzby1f.sbin");
		}
		else if(mode==3)
		{
			printf("\n====�������ٶ�(2,4,8,16,32,64):");
			scanf("%d",&speed);
			shm_ots_addr->speed = speed; 
		}
		else if(mode==4)
		{
			printf("\n====���������(0-ֹͣ 1-���� 2-��ͣ):");
			scanf("%d",&type);
			shm_ots_addr->runflag = type; 
		}
		else if(mode==5)
		{
			printf(" \n(^_^) curve share memory:(^_^)\n");	
			printf("\n nextpt = %d",pCurve->nextpt);
			printf("\n reload = %d", pCurve->reloadflag);
			printf("\n overlapflag = %d",pCurve->overlapflag);
			printf("\n isstop = %d",pCurve->isstop);
			printf("\n");
		}
		else if(mode==6)
		{
			hdb_test();
		}
		else if(mode==7)
		{
			new_task();
		}
		else if(mode==8)
		{
			/*
			shm_ots_addr->data_scene.requestflag = 1;
			shm_ots_addr->data_scene.type =2;
			shm_ots_addr->data_scene.stn_id=1;
			shm_ots_addr->data_scene.dev_id=1;
			strcpy(shm_ots_addr->data_scene.name,"yyptest");
			
			printf("���������޸ģ�\n");
			*/
			//printf("shm island =%d\n",shm_recv_addr->island);
			//printf(" shm write_sec_flag =%d\n ",shm_hdb_addr->write_sec_flag);
			//WrIND("BS.BS_F1.POL.JZ_BY",257);

			//BdPollingCmd(1,1);
			//printf("all data polling cmd send\n");
			SetAllPtScanEnable();
			printf("Set all pt scan enable ok\n");
			
		}
		else if(mode == 9)
		{
			if( SetObjCond() ==  TRUE )
			{
				printf("SetObjCond success!\n");
			}
			else
			{
				printf("SetObjCond failed!\n");
			}
		}
		else if(mode == 9)
		{
			if( LoadSimulog() ==  TRUE )
			{
				printf("LoadSimulog success!\n");
			}
			else
			{
				printf("LoadSimulog failed!\n");
			}
		}
		else if(mode==0)
		{
			exit(0);
		}
		else
		{
			continue;
		}
	}
	CloseHDB(db_conn);
	return 0;

}

int LoadSimulog()
{
	//ͳһ��������������
	DB_FMT data,cdata;
	DMS_COMMON	dms_rec;
	int	data_type;
	char timestr[22];
	char curid;
	int i,j;
	GetCurTimeStr(timestr);
	if ( SimulogDataLoad () == -1 )
	{
		printf ( "simulog.dat error!\n" );
		return FALSE;
	}

	data.table_id=TABLE_SCENE;
	cdata.table_id = TABLE_SCENE_DATA;
	InitDbData(&data,data.table_id);
	InitDbData(&cdata,cdata.table_id);	
	
	//����Ҫscene���ʵ��ֶ�flag��Ϊ1
	data.flag.flag_scene.datetime =TRUE;
	data.flag.flag_scene.dev_id =TRUE;
	data.flag.flag_scene.name =TRUE;
	data.flag.flag_scene.remark =TRUE;
	data.flag.flag_scene.scene_id =TRUE;
	data.flag.flag_scene.src =TRUE;
	data.flag.flag_scene.station_id =TRUE;
	data.flag.flag_scene.user_id =TRUE;

	//����Ҫscene_data���ʵ��ֶ�flag��Ϊ1
	cdata.flag.flag_scene_data.data =TRUE;
	cdata.flag.flag_scene_data.logicalname =TRUE;
	cdata.flag.flag_scene_data.scene_id =TRUE;

	//���scene����ÿ���ֶε�ֵ
	strcpy(data.seg.seg_scene.datetime,timestr);
	data.seg.seg_scene.dev_id =1;

	data.seg.seg_scene.src =0;
	data.seg.seg_scene.station_id =1;
	data.seg.seg_scene.user_id = 0;

	for(i=0;i<n_scene;i++)
	{
		curid = GetInexistenceIdInHdb(TABLE_SCENE);
		data.seg.seg_scene.scene_id = curid;
		strcpy(data.seg.seg_scene.name,scenedb[i].scene_name);
		strcpy(data.seg.seg_scene.remark,scenedb[i].scene_name);
		//���ýӿں���������ΪDB_FMT�ṹ��
		if( InsertOneRec(&data) != TRUE)
		{
			printf("����scene���� %s ʧ��\n",scenedb[i].scene_name);
			return FALSE;
		}
		else
		{
			printf("����scene���� %s �ɹ�\n",scenedb[i].scene_name);		
		}
		cdata.seg.seg_scene_data.scene_id = curid;

		for( j=scenedb[i].head; j<scenedb[i].head+scenedb[i].num; j++ )
		{
			strcpy(cdata.seg.seg_scene_data.logicalname,scenesegdb[j].name);
			if ( ReadEntryByNameStr ( scenesegdb[j].name, &dms_rec ) == -1 )
			{
				printf ("in Scene: id=%d name= %s is not found in database.\n",i,scenesegdb[i].name );
				continue;
			}
			else
			{
				data_type	= dms_rec.point.data_type;	//wdk 2008.3.22
				//yyp 2009.2.11
				MySleep(20);

				switch	( data_type )
				{
				case	ANA_TYPE:
				case	PARAM_TYPE:
						cdata.seg.seg_scene_data.data =  scenesegdb[j].data.value ;
						break;
				case	POL_TYPE:
				case	SOE_TYPE:
				case	SYSMSG_TYPE:
				case	DEVOBJ_TYPE:
						cdata.seg.seg_scene_data.data =  (float)scenesegdb[j].data.status ;
						break;
				default:
					break;
				}
			}
			//���ýӿں���������ΪDB_FMT�ṹ��
			if( InsertOneRec(&cdata) != TRUE)
			{
				printf("����scenedata���� %s ʧ��\n", scenesegdb[j].name);
				continue;
			}
			else
			{
				printf("����scenedata���� %s �ɹ�\n", scenesegdb[j].name);		
			}							
		}
	}

	/******************************************
	* �����¼ʾ���������
	******************************************/		
	return TRUE;
}

void hdb_test()
{
	int ret;
	char sql_str[200];
	//QSqlQuery db_opr("",db_conn);
	//SelectPtHdb(1);
	//sprintf(sql_str,"update ots.train_info set fault_id = null where host_id=5 ");
	//strcpy(sql_str,"update ots.train_info set task_id = null  where host_id = 3 ");
	//printf("sql = %s\n",sql_str );
	//ret = db_opr.exec(QString::fromLocal8Bit(sql_str));
	//printf("hostname=%s, host=%d\n",g_host_name,g_host_id);

	//insert_test();
	//update_test();
	//delete_test();
	select_test();

}

void new_task()
{

	int		send_task_id;
	int		task_id;
	char	send_time[22];
	int		host_id;
	char	start_time[22];
	short	status;
	char	end_time[22];
	float	score;
	int		time_len;

	//foreign key
	char	task_name[30];
	char	userinfo_name[20];

	//ͳһ��������������
	DB_FMT data;
	InitDbData(&data,TABLE_TRAIN_INFO);	
	
	//����Ҫ���ʵ��ֶ�flag��Ϊ1
	data.flag.flag_train_info.task_id=TRUE;
	data.flag.flag_train_info.scene_id=TRUE;
	data.flag.flag_train_info.fault_id=TRUE;
	data.flag.flag_train_info.task_status=TRUE;
	data.flag.flag_train_info.scene_status=TRUE;
	data.flag.flag_train_info.fault_status=TRUE;

	//������ÿ���ֶε�ֵ
	data.seg.seg_train_info.task_id=1;
	data.seg.seg_train_info.scene_id=1;
	data.seg.seg_train_info.fault_id=1;
	data.seg.seg_train_info.task_status=1;
	data.seg.seg_train_info.scene_status=1;
	data.seg.seg_train_info.fault_status=1;

	//���ò�ѯ����flag
	data.cond_flag.flag_train_info.host_id=TRUE;
	data.cond_seg.seg_train_info.host_id=g_host_id;
	
	//���ýӿں���������ΪDB_FMT�ṹ��
	if( UpdateOneRec(&data) != TRUE)
	{
		printf("��������ʧ��\n");		
	}
	else
	{
		printf("�������ݳɹ�\n");		
	}
	
}


void insert_test()
{
	//ͳһ��������������
	DB_FMT data;
	data.table_id=TABLE_TASK_GRP;
	InitDbData(&data,data.table_id);
	
	//����Ҫ���ʵ��ֶ�flag��Ϊ1
	data.flag.flag_task_grp.task_grp_id =TRUE;
	data.flag.flag_task_grp.name=TRUE;
	data.flag.flag_task_grp.remark=FALSE;

	//������ÿ���ֶε�ֵ
	data.seg.seg_task_grp.task_grp_id =17;
	strcpy(data.seg.seg_task_grp.name,"���");
	strcpy(data.seg.seg_task_grp.remark,"");

	//���ýӿں���������ΪDB_FMT�ṹ��
	if( InsertOneRec(&data) != TRUE)
	{
		printf("��������ʧ��\n");		
	}
	else
	{
		printf("�������ݳɹ�\n");		
	}

	//����Ҫ���ʵ��ֶ�flag��Ϊ1
	data.flag.flag_task_grp.name=TRUE;
	data.flag.flag_task_grp.remark=TRUE;

	//������ÿ���ֶε�ֵ
	strcpy(data.seg.seg_task_grp.name,"yangyp3-5");
	strcpy(data.seg.seg_task_grp.remark,"test3-5");

	//���ò�ѯ����flag
	data.cond_flag.flag_task_grp.task_grp_id=TRUE;
	data.cond_seg.seg_task_grp.task_grp_id=1;
	
	//���ýӿں���������ΪDB_FMT�ṹ��
	if( UpdateOneRec(&data) != TRUE)
	{
		printf("��������ʧ��\n");		
	}
	else
	{
		printf("�������ݳɹ�\n");		
	}

	/******************************************
	* �����¼ʾ���������
	******************************************/

}

void update_test()
{
	//ͳһ��������������
	DB_FMT data;
	/******************************************
	* ���¼�¼ʾ�����뿪ʼ
	******************************************/
	//�ڸ�ֵ֮ǰ��Ҫ�����ֶ�ֵ�����Գ�ʼ��

	data.table_id=TABLE_TASK_GRP;
	InitDbData(&data,data.table_id);
	
	//����Ҫ���ʵ��ֶ�flag��Ϊ1
	data.flag.flag_task_grp.name=TRUE;
	data.flag.flag_task_grp.remark=TRUE;

	//������ÿ���ֶε�ֵ
	strcpy(data.seg.seg_task_grp.name,"yangyptt");
	strcpy(data.seg.seg_task_grp.remark,"testtt");

	//���ò�ѯ����flag
	data.cond_flag.flag_task_grp.task_grp_id=TRUE;
	data.cond_seg.seg_task_grp.task_grp_id=100;
	
	//���ýӿں���������ΪDB_FMT�ṹ��
	if( UpdateOneRec(&data) != TRUE)
	{
		printf("��������ʧ��\n");
	}
	else
	{
		printf("�������ݳɹ�\n");		
	}

	/******************************************
	* ���¼�¼ʾ���������
	******************************************/
}


void delete_test()
{
	//ͳһ��������������
	DB_FMT data;
	/******************************************
	* ɾ����¼ʾ�����뿪ʼ
	******************************************/
	//�ڸ�ֵ֮ǰ��Ҫ�����ֶ�ֵ�����Գ�ʼ��

	data.table_id=TABLE_TASK_GRP;
	InitDbData(&data,data.table_id);

	//���ò�ѯ����flag
	data.cond_flag.flag_task_grp.task_grp_id=TRUE;
	data.cond_seg.seg_task_grp.task_grp_id=2;
	
	//���ýӿں���������ΪDB_FMT�ṹ��
	if( DeleteOneRec(&data) != TRUE)
	{
		printf("ɾ������ʧ��\n");		
	}
	else
	{
		printf("ɾ�����ݳɹ�\n");		
	}

	/******************************************
	* ɾ����¼ʾ���������
	******************************************/
}

void select_test()
{
	//ͳһ��������������
	DB_FMT data;
	DATA_TASK_GRP seg;
	/******************************************
	* ��ѯ��¼ʾ�����뿪ʼ
	******************************************/
	//�ڸ�ֵ֮ǰ��Ҫ�����ֶ�ֵ�����Գ�ʼ��

	//data.table_id=TABLE_TASK_GRP;
	//data.table_id=TABLE_TASK;
	//data.table_id=TABLE_USERINFO;
	data.table_id=TABLE_TRAIN_INFO;
	InitDbData(&data,data.table_id);

	//��ѯ����Ҫָ���ֶΣ�Ĭ�Ϸ��������ֶΣ�����б�������
	//��ѹ��ĵ�����ֶ�һ������
	
	//���ò�ѯ����
	//data.cond_flag.flag_task_grp.task_grp_id=TRUE;
	//data.cond_seg.seg_task_grp.task_grp_id=3;
	
	//���ýӿں���������ΪDB_FMT�ṹ��
	if( SelectRecs(&data) != TRUE)
	{
		printf("��ѯ����ʧ��\n");		
	}
	else
	{
		printf("��ѯ���ݳɹ�\n");
		printf("���ز�ѯ��¼ %d ��\n",data.rownum);		
	}
	int i;	
	/*
	for(i=0;i<data.rownum;i++)
	{
		printf("i=%d	id=%d	name=%s	remark=%s\n",
			i,data_task_grp[i].task_grp_id,data_task_grp[i].name,data_task_grp[i].remark);
	}
	*/
	/*
	for(i=0;i<data.rownum;i++)
	{
		printf("i=%d	id=%d	name=%s	grp_id=%d\n",
			i,data_task[i].task_id,data_task[i].name,data_task[i].task_grp_id);
	}
	*/
	/******************************************
	* ��ѯ��¼ʾ���������
	******************************************/	
}


int SetObjCond()
{
	unsigned char	stnid,devid;
	POINTER pt;
	DMS_COMMON      rs;
	ENTRY_DEVOBJ_VAL obj_value;
	FB_STATUS1	fb_status1;
	short			old_status;
	LCUID lcuno;
	unsigned int stn_num,dev_num,point_num;
	int i,j;

	GetStationNum(&stn_num);
	for(j=1;j<=stn_num;j++)
	{
		UCHAR	stnid;
		if(-1==GetStnIdByIndex(j, &stnid))
			continue;
		if(-1==GetGroupNumById(stnid, &dev_num))
			continue;
		for(devid=1;devid<=dev_num;devid++)
		{
			point_num=0;
			if(-1==GetEntryNumById(stnid, devid, DEVOBJ_TYPE, &point_num) )
			{
				//return FALSE;
				continue;
			}
			if(point_num<=0) continue;
			pt.stn_id = stnid;
			pt.dev_id = devid;
			pt.data_type = DEVOBJ_TYPE;

			for(i=0;i<point_num;i++)
			{
				pt.pt_id = i;
				if(ReadEntryById( &pt, &rs) ==-1) continue;
				obj_value = rs.var.devobj;
				if(obj_value.fb_status1.condc0 == 1 && obj_value.fb_status1.condc1 == 1)
				{
					continue;
				}
				obj_value.fb_status1.condc0 =1;
				obj_value.fb_status1.condc1 =1;
				SetDevObjPtVarById( &pt, obj_value );
			}
		}
	}
	return TRUE;
}