#ifndef	_VIP_CMD_HEADER_H
#define	_VIP_CMD_HEADER_H



//***DEFINITIONS FOR VIP COMMUNICATION***************************************

//Record for one VIP-R Block

#define IL_DATA_NUM	10
#define R_DATA_NUM	30

//2�������ͣ�10�������ͣ�30��������
typedef struct  
{
  USHORT		len;
  USHORT		msg_id;
  USHORT		yk_flag; //ָʾ�ĸ�������������һλ��Ч(ң������)
  USHORT		yt_flag; //ָʾ�ĸ���������Ч(ң������)
  UINT			IL_VALUE[IL_DATA_NUM];	//ң������: 
  float			R_VALUE[R_DATA_NUM];	//ң������: ȫ���й�������ȫ���޹�������1F�й�������1F�޹�����...
}T_VIP_R;


typedef struct 
{
	USHORT	port;
	USHORT	msg_id;
	char	ipaddr[48];
}VIP_CONFIG;

#endif
