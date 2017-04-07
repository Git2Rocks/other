/*********************************************************************************
**	This include file  is designed for  struct of data on dl476-92		**
**                                                                          	**
**	History									**
**										**
**	Date		author		comments				**
**	2004.5		Yuan/Hong	First version				**
**										**
*********************************************************************************/
#ifndef DL476STD
#define DL476STD

#define dl476debug

#define HPUX

//#define ALPHA_UNIX
/*#define LINUX*/
/*#define MSWIN32*/


#ifdef ALPHA_UNIX
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <sys/errno.h>
#include        <netinet/in.h>
#include        <netdb.h>
#include        <string.h>
#include        <stdio.h>
#include        <signal.h>
#include        <stdlib.h>
#include        <fcntl.h>
#include        <xti.h>
#include        <unistd.h>
#include        <time.h>
#include	<math.h>

/* #include <sys$common:[syslib]socket.h> */

#define RECV_FLAGS      0
#define SOCKET          short
#define SOCKET_ERROR    (-1)
#define INVALID_SOCKET  (-1)
#define closesocket(x)  shutdown(x,0)
#define fflush(x)       getchar()

#endif

#ifdef LINUX

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <math.h>

#define RECV_FLAGS      (0)
#define SOCKET_ERROR    (-1)
#define SOCKET          int
#define INVALID_SOCKET  (-1)
#define closesocket(x)  close(x)
#define _toupper(x)     toupper(x)

#endif


#ifdef HPUX

/* known to work under HPUX */
/* compile with cc -Aa for ANSI compatible */

#define _HPUX_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <math.h>

#define RECV_FLAGS      (0)
#define SOCKET_ERROR    (-1)
#define SOCKET          int
#define INVALID_SOCKET  (-1)
#define closesocket(x)  close(x)
#define BIG_ENDIAN      (1)
 
#endif


#ifdef MSWIN32

/* known to work under Windows 95 and Windows NT, MSVC 5.0 */

/*
 * note when using MSVC/C++ 5.0 - create workspace as a win32 console app and
 *  change project/settings/link Object/library modules list to include wsock32.lib
 */

#include <windows.h>
#include <winbase.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#pragma pack(1)

#define RECV_FLAGS  0

#define	 sleep(sec)		Sleep(sec*1000)
#define	 usleep(sec)	Sleep(sec/1000)

#endif

//#include        "../../../../system/lan/v4.0a/inc/lan_common.h"
#include        "../../../../system/lan/v4.0a/inc/lan_private.h" 
#include        "../../../../system/dps/v4.0a/inc/dps_type_def.h"
#include        "../../../../system/dps/v4.0a/inc/dps_rec_def.h"
#include        "../../../../system/dps/v4.0a/inc/ipc_common.h"


#define		WAN_PORT			51000

#define		MAX_REMOTE_NODE			10
#define		MAX_LOCAL_NODE			2

#define		ANA_TABLE			2
#define		SW_TABLE			3
#define		SWCTRL_TABLE			4

#define		MAX_DATA_SIZE			20000	/* all point number*/

#define		MAX_BLOCK_SIZE			2000 //2048
#define		MAX_TABLE_NUM			35
#define		MAX_APDU_SIZE			MAX_BLOCK_SIZE*2

#define		MAX_SWCTRL_SIZE			600

/*****		������ ctr����			******/

#define		A_ASSOCIATE			0X01
#define		A_ASSOCIATE_ACK			0X02
#define		A_ASSOCIATE_NAK     		0X03
#define		A_RELEASE			0X04
#define		A_RELEASE_ACK			0X05
#define		A_RELEASE_NAK			0X06
#define		A_ABOR				0X07
#define		A_RESET				0X08
#define		A_RESET_ACK			0X09
#define  	A_DATA        			0x0a
#define	 	A_UNLAST_DATA    		0x8a
#define  	A_DATA_ACK         		0x0b    
#define  	A_DATA_NCK         		0x0c 

#define		NO_PARA_SECTION			0
#define		PARA_SECTION			0X80  

/******		����ģʽrun_mode����		******/

#define		RULE_0				0X10
#define		RULE_1_SERV			0X20
#define		RULE_1_CLIT			0X30

#define		GROUP_TRAN			0X0A
#define		SINGLE_TRAN			0X05

/******		״̬��ʶstatus_flag����	  	******/

#define		HOST_ONLINE			127	
#define		HOST_OFFLINE			0

/******		ԭ����reason_flag����	 	******/

#define		OS_SUCCESS			1
#define		PRIORITY_ERR			2
#define		ASKMODE_ERR	 		3
#define		NOT_HOST			4
#define		SOURCEID_ERR			5
#define		DESTID_ERR			6
#define		LOW				7
#define		RUNMODE_ERR			8
#define		DATABASE_ERR			9
#define		DATAINDEX_ERR			10
#define		UNKNOWN_APDU			11
#define		UNKNOWN_DATA			12
#define		PROTOCOL_ERR			13


/******		���ݿ����Ͷ��� 			******/
#define  	B_ALL_INT			1	   	/*ȫ���������Ϳ� NO USE*/
#define  	B_ALL_REAL			2	   	/*ȫ������ʵ�Ϳ�*/
#define  	B_ALL_SW       		3	   	/*ȫ״̬����*/

#define		B_GROUP_INT			4		/*������������Ϳ�*/
#define		B_GROUP_REAL		5		/*���������ʵ�Ϳ�*/
#define		B_GROUP_SW			6		/*����״̬����*/

#define  	B_CHANG_INT			7  		/*�仯���������Ϳ�*/
#define  	B_CHANG_REAL		8  		/*�仯������ʵ�Ϳ�*/
#define  	B_CHANG_SW			9	   	/*�仯״̬����*/

#define		B_TIME_REAL			11	   	/*ʱ�������ʵ�Ϳ�*/
#define  	B_TIME_SW       	12	   	/*ʱ��״̬����*/

#define	 	B_CONTROL			22		/*���������*/
#define	 	B_ADJUST			23		/*���������*/
#define		B_CTRL_BACK			25		/*���������*/
#define	 	B_ADJ_BACK			26		/*���������*/
#define		B_CTRL_RUN			40		/*��������ִ��*/
#define		B_ADJ_RUN			41		/*��������ִ��*/
#define		B_CURSE				42		/*��������*/
#define		B_CTRL_RET			43		/*���ƽ������*/

#define	 	B_ANASET			50		/*ģ�������*/
#define	 	B_ANASET_BACK		51		/*ģ�������*/
#define		B_ANASET_RUN		52		/*ģ������ִ��*/


/******		���ݿ鳤�ȶ��� 				******/
#define  	ONE_CHANG_SW		3	   	/*�仯״̬����*/
#define  	ONE_CHANG_REAL		7  		/*�仯������ʵ�Ϳ� */
#define		ONE_TIME_SW		11		/*ʱ��״̬����	*/
#define		ONE_TIME_REAL		13		/*ʱ��仯������ʵ�Ϳ� */

/******		�������͡���������			******/
#define		R_APOWER		1
#define		R_RPOWER		2
#define		R_BREAKER		3
#define		R_SWITCH		4
#define		R_UNIT			5
#define		R_GATE			6
#define		R_AGC_SET		7
#define		R_DEVICE		8
#define		R_UNIT_TST		9
#define		R_SYS_MODE_SET	10

#define		S_OPEN			1
#define		S_CLOSE			2
#define		S_ON			3
#define		S_OFF			4

/******		�����붨��				******/

   
#define  	DATA_UNCHANG      	0x40    
#define  	DATA_INVALID      	0x20     
#define  	DATA_ALARM        	0x10     
#define  	DATA_MANSET      	0x08  /*4.0ģ�������ֶ����ã�ȡ�������״̬*/   
#define	  	DATA_ESTIMATE   	0x04    
#define		DATA_NEGATIVE		0x8000

/******		״̬�붨��				******/

#define		CLOSE			0x00		/* �պϻ�����״̬*/
#define		OPEN			0x01		/*  �Ͽ����쳣״̬ */

#define		HIGH_PRIORITY		1
#define		LOW_PRIORITY		2


/*****	Э����Ƶ�APDU��ͷ			*****/
/*#define	NARI*/

#define	GB_HEAD		0xffff

typedef struct   						   
{
#ifdef NARI
	unsigned	short	nari_head1;
	unsigned	short	nari_head2;
#endif	
	unsigned	char	ctr; 
  	unsigned	char  	run_mode;
  	unsigned	char  	status_flag;
  	unsigned	char  	reason;
  	unsigned	short	length;
} PROTOCOL_HEAD;

typedef	struct
{
	PROTOCOL_HEAD		head;
	unsigned	char	para[10];
}PROTOCOL_APDU;


/*****	��������Ӧ���APDU		*****/
typedef struct  
{ 
	unsigned	char  	ctr;
  	unsigned	char  	nr;
  	unsigned	char  	extend;
  	unsigned	char  	reason;
} DATACK_APDU;
                 

/*****	�������ݵ�APDU��ͷ			*****/


#define	GB_HEAD 0xffff
typedef struct   						   
{
	unsigned	char	ctr; 
  	unsigned	char  	nr;
  	unsigned	char  	ns;
  	unsigned	char  	priority;
  	unsigned	short	length;
} BASEDATA_HEAD;

#define	APDU_HEAD_SIZE		sizeof(BASEDATA_HEAD)

/*****	�������ݿ�Ķ���			*****/
typedef struct  				 					
{ 
	unsigned	char 	bid;
	unsigned	char	tableno;
	unsigned	short 	length;
 	unsigned	char	data[MAX_BLOCK_SIZE];

}DATA_BLOCK;

#define	BLOCK_HEAD_SIZE	4

typedef struct  				 					
{ 
	unsigned	char	data[MAX_BLOCK_SIZE];

}COMM_BLOCK;

typedef struct
{	
	BASEDATA_HEAD 	head;
/*	union
	{
		DATA_BLOCK		basedata;	
		COMM_BLOCK		cmd;
	}block;
*/	unsigned	char	block[MAX_APDU_SIZE];
}DATA_APDU;


/******		���ݽṹ����				******/

typedef struct{
		unsigned short	number;
		char		name[MAX_REMOTE_NODE][60];
		char		ip[MAX_REMOTE_NODE][60];

}NODE_DEF;

typedef struct
{
		unsigned char	no;
		unsigned char	type;
		char		file[60];
		unsigned short	ptnum;
		unsigned short	baseaddr;
}TABLE_DEF;


typedef struct
{
		float			band;
		float			value;
		float			oldvalue;
		unsigned char	quality;
}REAL_DATA;

typedef struct
{
		unsigned char	value;
		unsigned char	oldvalue;
}SW_DATA;

typedef struct
{
		unsigned char	tableno;
		unsigned char	tabletype;
		char		name[60];
		unsigned char	stn_id;/*zwj for v4.0*/
		unsigned char	dev_id;
		unsigned char	data_type;
		unsigned short	point_id;
		union
		{
			REAL_DATA	real;
			SW_DATA		sw;
		}data;		
}DATA_INDEX;


typedef struct
{
		unsigned char	tableno;
		unsigned char	tabletype;
		char		name[60];
		unsigned char	stn_id;/*zwj for v4.0*/
		unsigned char	dev_id;
		unsigned char	data_type;
		unsigned short	point_id;
}SWCTRL_INDEX;

/****************************************/
NODE_DEF		lnode,rnode;
short			hot_rnode;

TABLE_DEF		table[MAX_TABLE_NUM];

DATA_INDEX		dataindex[MAX_DATA_SIZE];
unsigned short	index_num;

SWCTRL_INDEX	swctrl[MAX_SWCTRL_SIZE];
unsigned short	swctrl_num;

DATA_APDU		datapdu,cmdapdu;

DATA_BLOCK		datablock;
extern		SHM_RECORD	*shm_rec_addr;
#define			ALLTIME		2
short			allflag; 

#endif
