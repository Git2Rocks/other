#include	"../../../dms/v4.0a/inc/dms_com.h"
#include	"../../../dps/v4.0a/inc/dps_type_def.h"
#include	"../../../dps/v4.0a/inc/dps_rec_def.h"
#include	"../../../dps/v4.0a/inc/ipc_common.h"
#include	"../../../dps/v4.0a/inc/dps_functions_def.h"

#ifdef		SUN_OS
#include 	<sys/socket.h>  /* for AF_INET        */
#include 	<netinet/in.h>  /* for struct in_addr */
#include 	<arpa/inet.h>   /* for inet_ntoa()    */
#include 	<sys/types.h>
#include 	<sys/ioctl.h>
#include	<fcntl.h>
#include 	<netdb.h>       /* for struct hostent */
#include	<errno.h>
#include 	<pthread.h>

#endif

#if defined(SUN) && defined(_AIX)
#include	<sys/wait.h>
#elif defined(SUN)
#include 	<sys/filio.h>
#include	<wait.h>
#endif



void*	state_broadcast(void*);
void*	state_recv(void*);
void*	interface_manage(void*);
void*	state_respond(void*);
void*	state_request(void*);
void*	pair_host_manage(void* para);
int		UpdateState(char *msg);
void	UpdateHostState(char *hostname, USHORT state);
void	UpdateHostNetState(char *hostname, USHORT net_no, USHORT state);
int		InitStationHostList(void);
int		InitLocalIpAddr(void);
void	UpdateDomainNetState(char *local_domain, char *peer_domain, int net_no, USHORT	net_state);


#define	HEARTBEAT_UDP_PORT		7777
#define	ECHO_SERV_UDP_PORT		7778


#define	HOST_STATE_EXIT				0
#define	HOST_STATE_MAIN				1
#define	HOST_STATE_VICE				2
#define	HOST_STATE_SYSNET_FAIL		3
#define	HOST_STATE_CTRLNET_FAIL		4
#define	HOST_STATE_ISOLATED			5
#define	HOST_STATE_NOT_INIT		0xFF

#define	NET_STATE_NORM		0
#define	NET_STATE_FAIL		1

#define	UDP_BROADCAST_PERIOD	1000
#define	UDP_REQUEST_PERIOD		1000
#define	MAX_MSG_SIZE	(MAX_HOST_NAME_SIZE+2)


#define MAX_THREAD_NUM		7
#define THREAD_NAME_SIZE	32



char	local_hostname[MAX_HOST_NAME_SIZE];
char	localHostPtNameStr[POINT_NAME_SIZE];
char	pair_hostname[MAX_HOST_NAME_SIZE];
char	pairHostPtNameStr[POINT_NAME_SIZE];
USHORT	local_net_active[MAX_HOST_IPADDR_NUM], local_net_fail_state[MAX_HOST_IPADDR_NUM];
char	local_ipaddr[MAX_HOST_IPADDR_NUM][MAX_IPADDR_SIZE];
USHORT	sys_sum_net_num;
USHORT	sys_info_net_num;
USHORT	sys_ctrl_net_num;
int		local_sum_net_num, pair_sum_net_num;
BOOL	ctrl_net_independ_flag;
USHORT	local_host_state, pair_host_state;
int		local_host_pos, local_domain_pos;

struct	
{
	char		hostname[MAX_HOST_NAME_SIZE];
	USHORT		host_active;
	int			net_num;
	USHORT		net_active[MAX_HOST_IPADDR_NUM];
	int			domain_pos;
}		station_host_list[MAX_HOST_NUM];
int		station_host_num=0;

struct
{
	char		domain_name[MAX_DOMAIN_NAME_SIZE];
	int			net_num;
	USHORT		net_active[MAX_HOST_IPADDR_NUM];
	USHORT		net_state[MAX_HOST_IPADDR_NUM];
}		domain_list[MAX_DOMAIN_NUM];
int		domain_num=0;


int	double_host_flag=0;
int	local_host_state_init_flag=0;
int	enable_dhsw_manage_flag=0;


#ifdef	WINDOWS_OS
#define		pthread_t				HANDLE
#define 	bzero(addr, size)		memset(addr, 0, size)
#define		Msleep(ms)				Sleep(ms)
#else
#define		DWORD					pthread_t
#define		closesocket(socket)		close(socket)
#define		Msleep(ms)				usleep(ms*1000)
#endif

#define SYS_SUPERVISE_TIMEOUT	6
int		sysmgrExitFlag;

void* SysSuperviseProcess(void *para)
{
	SYS_COMM_TABLE	*shm_syscomm_addr;
	
	/*      ��ϵͳͨ�Ź����ڴ�    */
	shm_syscomm_addr= (SYS_COMM_TABLE*) LinktoShareMem( SHM_SYSCOMM_TABLE_KEY_CHAR );
	if( shm_syscomm_addr == (SYS_COMM_TABLE*)-1 )
	{
		Err_log("Fail to link sys_comm shm");
		exit(-1);
	}
	
	for(;;)
	{
		sleep(1);
		shm_syscomm_addr->watchdog.sysValue++;
		if(shm_syscomm_addr->watchdog.sysValue>=SYS_SUPERVISE_TIMEOUT)
		{
			shm_syscomm_addr->watchdog.exitFlag= 1;
			if(sysmgrExitFlag==0)
			{
				char	msg[256];

				sysmgrExitFlag= 1;
				sprintf(msg, "%s sysmgr exit", local_hostname);
				BroadCastSms(msg, TRUE);
			}
		}
	}
}


int	main(int argc, char *argv[])
{ 
	char		err_str[128];
	pthread_t	h_thread[MAX_THREAD_NUM];
	DWORD		h_terminated;
	void*		(*thread[MAX_THREAD_NUM])();
	char		thread_name[MAX_THREAD_NUM][THREAD_NAME_SIZE];
	int			thread_num;
	int			i;

#ifdef	WINDOWS_OS
	WSADATA		WSAData;
#endif

	CreateLockFile(".host_mgr.lock");
	if(-1==InitSysLog(H9000_MODULE_HMGR, "Hmgr"))
	{
		Err_log("Fail to InitSysLog!\n");
		exit(-1);
	}

#ifdef	WINDOWS_OS
	if(WSAStartup(MAKEWORD(2,2), &WSAData) != 0)
	{
		Err_log("Fail to initialize net!\n");
		exit(-1);
	}
#endif

  	if(-1==MountDB(NULL))
  	{
		Err_log("Fail to MountDB!\n");
		exit(-1);
  	} 
  	 
  	if(!lan_out_init())
  	{
		Err_log("Fail to init lan module!\n");
		exit(-1);
  	} 

	if(gethostname(local_hostname, sizeof(local_hostname)))	
  	{
		Err_log("Fail to gethostname!\n");
		exit(-1);
  	} 

	if(strlen(local_hostname)>= MAX_HOST_NAME_SIZE)
  	{
		sprintf(err_str, "hostname too long: %s", local_hostname);
		Err_log(err_str);
		exit(-1);
  	} 

	if(-1==GetHostStatePtNameStr(local_hostname, localHostPtNameStr))	
	{
		sprintf(err_str, "Fail to find %s state point in DB", local_hostname);
		Err_log(err_str);
	}

	sys_info_net_num= GetSysNetNum();
	sys_ctrl_net_num= GetCtrlNetNum();
	ctrl_net_independ_flag= IsCtrlNetIndepend();
	if(ctrl_net_independ_flag)
		sys_sum_net_num= sys_info_net_num+sys_ctrl_net_num;
	else
		sys_sum_net_num= sys_info_net_num;

	if(-1==GetHostIpaddrNum(local_hostname, &local_sum_net_num))
	{
		sprintf(err_str, "Fail to find %s ipaddr num", local_hostname);
		Err_log(err_str);
		exit(-1);
	}

	if(local_sum_net_num==0  || !IsHostStateManage(local_hostname))
	{
		for(;;)
		{
			UpdateHostState(local_hostname, HOST_STATE_MAIN);
			for(i=0; i<local_sum_net_num; i++)
				UpdateHostNetState(local_hostname, (USHORT)i, NET_STATE_NORM);

			Msleep(2000);
		}
	}

	if(-1==InitLocalIpAddr())
	{ 
		Err_log("Fail to initialize local ipaddr list");
		exit(-1);
	}

	if(-1==InitStationHostList())
	{ 
		Err_log("Fail to initialize host list");
		exit(-1);
	}


	thread_num= 0;
	thread[thread_num]= state_broadcast;
	strcpy(thread_name[thread_num++], "state_broadcast");
	thread[thread_num]= state_recv;
	strcpy(thread_name[thread_num++], "state_recv");
	thread[thread_num]= interface_manage;
	strcpy(thread_name[thread_num++], "interface_manage");
	thread[thread_num]= SysSuperviseProcess;
	strcpy(thread_name[thread_num++], "SysSuperviseProcess");

	//double hosts
	thread[thread_num]= state_respond;
	strcpy(thread_name[thread_num++], "state_respond");
	thread[thread_num]= state_request;
	strcpy(thread_name[thread_num++], "state_request");
	thread[thread_num]= pair_host_manage;
	strcpy(thread_name[thread_num++], "pair_host_manage");

	if(-1!=GetDhswHostName(pair_hostname))
	{
		if(-1==GetHostStatePtNameStr(pair_hostname, pairHostPtNameStr))	
		{
			sprintf(err_str, "Fail to find %s state point in DB", pair_hostname);
			Err_log(err_str);
			exit(-1);
		}
		if(-1==GetHostIpaddrNum(pair_hostname, &pair_sum_net_num))
		{
			sprintf(err_str, "Fail to get %s ipaddr num", pair_hostname);
			Err_log(err_str);
			exit(-1);
		}
		if(local_sum_net_num!=pair_sum_net_num)
		{
			sprintf(err_str, "Host net num must be equal with pair host: local %d, pair %d", 
				local_sum_net_num, pair_sum_net_num);
			Err_log(err_str);
			exit(-1);
		}
		thread_num= 7; //double hosts
		double_host_flag= 1;
		enable_dhsw_manage_flag= 0;
		local_host_state_init_flag= 0;
	}
	else
	{
		thread_num= 4; //single host
		UpdateHostState(local_hostname, HOST_STATE_MAIN);
		enable_dhsw_manage_flag= 1;
		local_host_state_init_flag= 1;
	}

#ifdef	WINDOWS_OS
	for(i=0; i<thread_num; i++)
	{
		h_thread[i]= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread[i], 0, 0, NULL);
		if(!h_thread[i])
  		{
			sprintf(err_str, "Fail to create thread %s!", thread_name[i]);
			Err_log(err_str);
			exit(-1);
  		} 
	}
  	
	while( h_terminated= WaitForMultipleObjects(thread_num, h_thread, FALSE, INFINITE) )
	{
		if(h_terminated<WAIT_OBJECT_0 || h_terminated>(WAIT_OBJECT_0+thread_num-1))
		{
			Err_log("WaitForMultipleObjects return error");
			continue;
		}

		i= h_terminated-WAIT_OBJECT_0;
		sprintf(err_str, "restart thread %d", i);
		Err_log(err_str);

		h_thread[i]= CreateThread(NULL, 0, 
			(LPTHREAD_START_ROUTINE)thread[i], 0, 0, NULL);
		if(!h_thread[i])
  		{
			sprintf(err_str, "Fail to create thread %s", thread_name[i]);
			Err_log(err_str);
			exit(-1);
  		} 
  	}
#else
	for(i=0; i<thread_num; i++)
	{
 		if( pthread_create(&h_thread[i], NULL, thread[i], NULL) )
 		{
			sprintf(err_str, "Fail to create thread %s!", thread_name[i]);
			Err_log(err_str);
			exit(-1);
  		} 
	}

	for(;;)
		sleep(100000);
#endif

}

int InitLocalAdapterInfo(void);

int InitLocalIpAddr(void)
{
	int	netNo;
	
	for(netNo=0; netNo<local_sum_net_num; netNo++)
	{
		if(-1==GetHostIpaddr(local_hostname, netNo, local_ipaddr[netNo]))
			return -1;
	}

	return InitLocalAdapterInfo();
}


int	GetDomainPos(char *domain, int host_net_num)
{
	int		i;
	
	for(i=0; i<domain_num; i++)
	{
		if(!strcmp(domain, domain_list[i].domain_name))
		{
			if(host_net_num>domain_list[i].net_num)
				domain_list[i].net_num= host_net_num;
			return i;
		}
	}
	if(domain_num>=MAX_DOMAIN_NUM)
		return -1;
	strcpy(domain_list[domain_num].domain_name, domain);
	domain_list[domain_num].net_num= host_net_num;
	for(i=0; i<MAX_HOST_IPADDR_NUM; i++)
		domain_list[domain_num].net_state[i]= 1;
	domain_num++;
	return (domain_num-1);
}


int	InitStationHostList(void)
{
	int		i, all_host_num, local_host_defined= 0;
	UCHAR	local_stn_id, stn_id;
	char	hostname[MAX_HOST_NAME_SIZE];
	char	local_domain[MAX_DOMAIN_NAME_SIZE], domain[MAX_DOMAIN_NAME_SIZE];
	char	err_str[256];

	if(-1==GetLocalHostStnId(&local_stn_id))
		return -1;
	if(-1==GetHostDomain(local_hostname, local_domain))
		return -1;

	all_host_num= GetSysHostNum();

	station_host_num= 0;
	for(i=1; i<=all_host_num; i++)
	{
		if(-1==GetHostNameById(i, hostname))
			continue;

		if(-1==GetHostStnId(hostname, &stn_id))
			continue;
	
		if(stn_id!=local_stn_id)
			continue;

		if(!IsHostStateManage(hostname))
			continue;
		
		if(-1==GetHostDomain(hostname, domain))
			return -1;

		if(!strcmp(hostname, local_hostname))
		{
			local_host_pos= station_host_num;
			local_domain_pos= GetDomainPos(domain, local_sum_net_num);
			if(-1==local_domain_pos)
			{
				sprintf(err_str, "Too much domain defined(max %d)", MAX_DOMAIN_NUM);
				Err_log(err_str);
				return -1;
			}
			local_host_defined= 1;
		}
		else
		{
			strcpy(station_host_list[station_host_num].hostname, hostname);
			if(-1==GetHostIpaddrNum(hostname, &station_host_list[station_host_num].net_num))
				station_host_list[station_host_num].net_num= 0;
			station_host_list[station_host_num].domain_pos= GetDomainPos(domain, 
				station_host_list[station_host_num].net_num);
			if(-1==station_host_list[station_host_num].domain_pos)
			{
				sprintf(err_str, "Too much domain defined(max %d)", MAX_DOMAIN_NUM);
				Err_log(err_str);
				return -1;
			}

			station_host_num++;
		}
	}
	if(!local_host_defined)
	{
		sprintf(err_str, "Local host isn't defined in host list");
		Err_log(err_str);
		return -1;
	}
	return 0;
}


void *state_broadcast(void *para)
{
	char	err_str[128];
	char	broadcast_ipaddr[MAX_NET_NUM][MAX_IPADDR_SIZE];
	USHORT	host_state;
	int		broad_sock;
	int		broadcast= 1;
	struct  sockaddr_in broad_addr;
	char	msg[MAX_MSG_SIZE];
	int		i, ret;


	while(!local_host_state_init_flag)
		Msleep(1000);

	for(i=0; i<local_sum_net_num; i++)
	{
		if(-1==GetBroadcastIpaddr(i, broadcast_ipaddr[i]))
		{
			sprintf(err_str, "Fail to find broadcast ipaddr %d", i);
			Err_log(err_str);
			exit(-1);
		}
		if(-1==inet_addr(broadcast_ipaddr[i]))
		{ 
			sprintf(err_str, "broadcast ipaddr %s error", broadcast_ipaddr[i]);
			Err_log(err_str);
			exit(-1);
		}
	}

	for(;;)
	{
		if(-1==(broad_sock=socket(AF_INET, SOCK_DGRAM, 0)))
		{ 
			Err_log("Fail to open broadcast socket");
			Msleep(1000);
			continue;
		}
		
		if(-1==setsockopt(broad_sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)))
		{ 
			Err_log("Fail to set broadcast socket");
			closesocket(broad_sock);
			Msleep(1000);
			continue;
		}
		for(;;)
		{
			if(-1==GetIndPtStateByNameStr(localHostPtNameStr, &host_state))
			{
				Msleep(1000);
				continue;
			}

			ret= 0;
			for(i=0; i<local_sum_net_num; i++)
			{
				bzero((char *)&broad_addr, sizeof(broad_addr));
				broad_addr.sin_family     =AF_INET;
				broad_addr.sin_port       =htons(HEARTBEAT_UDP_PORT);
				broad_addr.sin_addr.s_addr=inet_addr(broadcast_ipaddr[i]);

				memset(msg, 0, sizeof(msg));
				strcpy(msg, local_hostname);
				msg[MAX_HOST_NAME_SIZE]= i;
				msg[MAX_HOST_NAME_SIZE+1]= (UCHAR)host_state;
				if(sizeof(msg)!=sendto(broad_sock, msg, sizeof(msg), 0, 
					(struct sockaddr *)&broad_addr, sizeof(broad_addr)))
				{
					sprintf(err_str, "Fail to send net%d broadcast msg", i+1);
					Err_log(err_str);
					ret= -1;
					continue;
				}
				SendTraceMsg(H9000_LOG_SEND,0,"Send HB to net%d : host_state= %d", i+1, host_state);	
			}

			if(ret==-1)
			{
				closesocket(broad_sock);
				Msleep(1000);
				break;
			}

			Msleep(UDP_BROADCAST_PERIOD);
		}
	}
}

int		recv_valid_flag;
void *state_recv(void *para)
{
	char	err_str[128];
	int		recv_sock;
	struct  sockaddr_in recv_addr, from_addr;
	char	msg[MAX_MSG_SIZE];
	int		recv_len, from_len;

	for(;;)
	{
		if(-1==(recv_sock=socket(AF_INET, SOCK_DGRAM, 0)))
		{ 
			recv_valid_flag= 0;
			Err_log("Fail to open recv socket");
			Msleep(1000);
			continue;
		}

		bzero((char *)&recv_addr, sizeof(recv_addr));
		recv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
		recv_addr.sin_family     =AF_INET;
		recv_addr.sin_port       =htons(HEARTBEAT_UDP_PORT);

		if(bind(recv_sock, (struct sockaddr *)&recv_addr, sizeof(recv_addr)))
		{
			SendTraceMsg(H9000_LOG_ERROR,0,"Fail to bind recv socket upd port=%d, errno= %d", HEARTBEAT_UDP_PORT, errno);
			recv_valid_flag= 0;
			closesocket(recv_sock);
			Msleep(1000);
			continue;
		}

		recv_valid_flag= 1;
		for(;;)
		{
			from_len= sizeof(from_addr);
			recv_len= recvfrom(recv_sock, msg, sizeof(msg), 0, (struct sockaddr *)&from_addr, &from_len);
			if(recv_len!=sizeof(msg))
			{
				sprintf(err_str, "Recv heartbeat msg len error: %d", recv_len);
				Err_log(err_str);
				closesocket(recv_sock);
				break;
			}
			
			SendTraceMsg(H9000_LOG_RECV,0,"Recv HB from %s(%d) %s", msg, msg[MAX_HOST_NAME_SIZE+1], inet_ntoa(from_addr.sin_addr));	

			UpdateState(msg);
		}
	}
}

void GetLocalNetLineState(int local_line_connected[]);

void *interface_manage(void* para)
{
	int		i, j;
	int		local_info_net_num, local_info_net_norm, local_ctrl_net_norm;
	int		local_line_connected[MAX_HOST_IPADDR_NUM];
	int		local_all_net_norm;

	Msleep(UDP_BROADCAST_PERIOD*2);

	for(;;)
	{
		if(!recv_valid_flag)
		{
			Msleep(UDP_BROADCAST_PERIOD*2);
			continue;
		}
		
		/*�鿴ÿ�����ڵ���������״̬*/
#ifdef _AIX
		for(j=0; j<local_sum_net_num; j++)
			local_line_connected[j]= local_net_active[j];
#else
		GetLocalNetLineState(local_line_connected);
#endif
		
		//���豾���������ھ�����
		local_all_net_norm= 1;
		for(j=0; j<local_sum_net_num; j++)
		{
			if(local_net_active[j])  /*���յ���������������*/
			{
				if(!local_line_connected[j]) //�������Ӳ�����,���ܸյ���
				{
					SendTraceMsg(H9000_LOG_WARN,0, "net%d received msg but unlined", j+1);
					continue; //���账��
				}
				else //������������
				{
					SendTraceMsg(H9000_LOG_INFO,0, "net%d received msg and lined: fail_state=%d", j+1, local_net_fail_state[j]);

					UpdateHostNetState(local_hostname, (USHORT)j, NET_STATE_NORM);

					local_net_fail_state[j]= 0; //����������״̬

					for(i=0; i<station_host_num; i++)/*������������Ķ�Ӧ����ӿ�*/
					{
						if(station_host_list[i].domain_pos!=local_domain_pos)/*�����Ǳ��������*/
							continue;
						if(j>=station_host_list[i].net_num)/*�����������ʵ������ӿ�*/
							continue;

						if(station_host_list[i].net_active[j])
							station_host_list[i].net_active[j]= 0;/*�������������ӿ�״̬*/
						else
							UpdateHostNetState(station_host_list[i].hostname, (USHORT)j, NET_STATE_FAIL);
					}

					for(i=0; i<domain_num; i++) //����������״̬
					{
						if(i==local_domain_pos)/*��������*/
							continue;
						if(j>=domain_list[i].net_num)/*���ʵ������ӿ�*/
							continue;
						if(domain_list[i].net_state[j] && !domain_list[i].net_active[j])
							UpdateDomainNetState(domain_list[local_domain_pos].domain_name, 
								domain_list[i].domain_name, j, NET_STATE_FAIL);
						else if(!domain_list[i].net_state[j] && domain_list[i].net_active[j])
							UpdateDomainNetState(domain_list[local_domain_pos].domain_name, 
								domain_list[i].domain_name, j, NET_STATE_NORM);
						domain_list[i].net_state[j]= domain_list[i].net_active[j];
						domain_list[i].net_active[j]= 0;/*������������״̬*/
					}
					
				}
			}
			else 	/*���ղ�����������������*/
			{
				if(local_line_connected[j]) //������������,����Ϊ����ϵͳ��Ҳ���ܸղ�������
				{
					SendTraceMsg(H9000_LOG_WARN,0, "net%d recv no msg but lined: fail_state=%d", j+1, local_net_fail_state[j]);
					if(local_net_fail_state[j]>0) 
					{
						local_net_fail_state[j]--;
						local_all_net_norm= 0;
					}
				}
				else //�������Ӳ�����
				{
					SendTraceMsg(H9000_LOG_ERROR,0, "net%d recv no msg and unlined", j+1);
					UpdateHostNetState(local_hostname, (USHORT)j, NET_STATE_FAIL);
					local_net_fail_state[j]= 30; /*��¼������ӿڹ���״̬*/
					local_all_net_norm= 0;
				}
			}
	
		}/*for(j)*/
		

		//��鱾��ʵ����Ϣ������
		if(local_sum_net_num<sys_info_net_num)
			local_info_net_num= local_sum_net_num; /*��������ӿ�������������ϵͳ��Ϣ����������*/
		else
			local_info_net_num= sys_info_net_num;

		local_info_net_norm= 0;
		for(i=0; i<local_info_net_num; i++) /*��鱾����Ϣ���Ƿ�����*/
		{
			if(local_net_active[i] && local_line_connected[i]) /*�յ��㲥��������������*/
			{
				local_info_net_norm= 1;
				break;
			}
		}
		SendTraceMsg(H9000_LOG_INFO,0, "local info net state: %d", local_info_net_norm);
		
		if(ctrl_net_independ_flag && (local_sum_net_num>sys_info_net_num)) /*��������������ʵ�ʵĿ�����*/
		{
			local_ctrl_net_norm= 0;
			for(i=local_info_net_num; i<local_sum_net_num; i++) /*��鱾���������Ƿ�����*/
			{
				if(local_net_active[i] && local_line_connected[i]) /*�յ��㲥��������������*/
				{
					local_ctrl_net_norm= 1;
					break;
				}
			}
		}
		else
			local_ctrl_net_norm= local_info_net_norm; /*����Ϣ��״̬һ��*/
		SendTraceMsg(H9000_LOG_INFO,0, "local ctrl net state: %d", local_ctrl_net_norm);

		if(!local_info_net_norm) /*���籾����Ϣ������������������޷�������Ϣ*/
		{                        /*���°���������״̬��׼��飬�������Ƿ��յ��㲥��*/
			local_info_net_norm= 0;
			for(i=0; i<local_info_net_num; i++) /*��鱾����Ϣ���Ƿ�����*/
			{
				if(local_line_connected[i] && !local_net_fail_state[i]) /*�������Ӳ������ڷǹ���״̬*/
				{
					local_info_net_norm= 1;
					break;
				}
			}

			if((local_sum_net_num>sys_info_net_num) && ctrl_net_independ_flag) /*�����Ŀ�����*/
			{
				local_ctrl_net_norm= 0;
				for(i=local_info_net_num; i<local_sum_net_num; i++) /*��鱾���������Ƿ�����*/
				{
					if(local_line_connected[i] && !local_net_fail_state[i]) /*�������Ӳ������ڷǹ���״̬*/
					{
						local_ctrl_net_norm= 1;
						break;
					}
				}
			}
			else
				local_ctrl_net_norm= local_info_net_norm;  /*����Ϣ��״̬һ��*/
		}

		if(local_info_net_norm && local_ctrl_net_norm) /*��Ϣ���Ϳ�����������*/
		{
			if(double_host_flag) /*˫�����*/
				local_host_state= HOST_STATE_MAIN;
			else
				UpdateHostState(local_hostname, HOST_STATE_MAIN);
		}
		else if(!local_info_net_norm && !local_ctrl_net_norm) /*���������������*/
		{
			if(double_host_flag) /*˫�����*/
				local_host_state= HOST_STATE_ISOLATED;
			else
				UpdateHostState(local_hostname, HOST_STATE_ISOLATED);
		}
		else if(!local_info_net_norm && local_ctrl_net_norm) /*��Ϣ��������*/
		{
			if(double_host_flag) /*˫�����*/
				local_host_state= HOST_STATE_SYSNET_FAIL;
			else
				UpdateHostState(local_hostname, HOST_STATE_SYSNET_FAIL);
		}
		else if(local_info_net_norm && !local_ctrl_net_norm) /*������������*/
		{
			if(double_host_flag) /*˫�����*/
				local_host_state= HOST_STATE_CTRLNET_FAIL;
			else
				UpdateHostState(local_hostname, HOST_STATE_CTRLNET_FAIL);
		}

		for(i=0; i<local_sum_net_num; i++) /*�������������ӿ�״̬*/
			local_net_active[i]= 0;

		for(i=0; i<station_host_num; i++) /*�������������״̬*/
		{
			if(station_host_list[i].domain_pos!=local_domain_pos)/*�����Ǳ��������*/
				continue;
			if(!strcmp(station_host_list[i].hostname, pair_hostname)) /*���������������״̬*/
				continue;
			
			if(station_host_list[i].host_active)
				station_host_list[i].host_active= 0;
			else
			{
				if(local_all_net_norm && (local_sum_net_num>=station_host_list[i].net_num))
					UpdateHostState(station_host_list[i].hostname, HOST_STATE_EXIT);
			}
		}

		enable_dhsw_manage_flag= 1;
		
		Msleep(UDP_BROADCAST_PERIOD*2);
	}
}



void *state_respond(void *para)
{
	USHORT	host_state;
	int		wait_sock;
	struct  sockaddr_in local_addr, client_addr;
	int		recv_len, addr_len;
	char	send_msg[MAX_MSG_SIZE], recv_msg[MAX_MSG_SIZE];
	char	err_str[128];

	for(;;)
	{
		if(-1==(wait_sock=socket(AF_INET, SOCK_DGRAM, 0)))
		{ 
			Err_log("Fail to open respond socket");
			Msleep(1000);
			continue;
		}

		bzero((char *)&local_addr, sizeof(local_addr));
		local_addr.sin_addr.s_addr=htonl(INADDR_ANY);
		local_addr.sin_family     =AF_INET;
		local_addr.sin_port       =htons(ECHO_SERV_UDP_PORT);

		if(bind(wait_sock, (struct sockaddr *)&local_addr, sizeof(local_addr)))
		{ 
			Err_log("Fail to bind respond socket");
			closesocket(wait_sock);
			Msleep(1000);
			continue;
		}

		for(;;)
		{
			memset(recv_msg, 0, sizeof(recv_msg));
			addr_len= sizeof(client_addr);
			recv_len= recvfrom(wait_sock, recv_msg, sizeof(recv_msg), 0, (struct sockaddr*)&client_addr, &addr_len);
			if(recv_len!=sizeof(recv_msg))
			{
				sprintf(err_str, "Received request msg len error: %d", recv_len);
				Err_log(err_str);
				closesocket(wait_sock);
				Msleep(1000);
				break;
			}

			SendTraceMsg(H9000_LOG_INFO,0,"Respond recv addr: %s, port: %d ", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

			if(strcmp(pair_hostname, recv_msg))
			{
				sprintf(err_str, "Received host isn't pair host: %s", recv_msg);
				Err_log(err_str);
				continue;
			}
						
			if(-1==UpdateState(recv_msg))
				continue;

			if(-1==GetIndPtStateByNameStr(localHostPtNameStr, &host_state))
			{
				Msleep(1000);
				continue;
			}
			if(!local_host_state_init_flag)
				host_state= HOST_STATE_NOT_INIT;

			memset(send_msg, 0, sizeof(send_msg));
			strcpy(send_msg, local_hostname);
			send_msg[MAX_HOST_NAME_SIZE]= recv_msg[MAX_HOST_NAME_SIZE];
			send_msg[MAX_HOST_NAME_SIZE+1]= (char)host_state;
			
			if(sizeof(send_msg)!=sendto(wait_sock, send_msg, sizeof(send_msg), 0, 
				(struct sockaddr *)&client_addr, addr_len))
			{
				sprintf(err_str, "Fail to send respond msg");
				Err_log(err_str);
				closesocket(wait_sock);
				break;
			}
			
			SendTraceMsg(H9000_LOG_INFO,0,"Respond send addr: %s, port: %d ", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		}
	}
}



void *state_request(void *para)
{
	char	ipaddr[MAX_IPADDR_SIZE];
	USHORT	host_state;
	int		request_sock;
	struct	sockaddr_in	server_addr;
	int		send_len, recv_len;
	char	send_msg[MAX_MSG_SIZE], recv_msg[MAX_MSG_SIZE];
	char	err_str[128];
	USHORT	net_no;
	fd_set	readfds;
	struct	timeval tv;
	int		ret;
	int		j;
	char	pair_ipaddr[MAX_HOST_IPADDR_NUM][MAX_IPADDR_SIZE];

	for(j=0; j<pair_sum_net_num; j++)
	{
		if(-1==GetHostIpaddr(pair_hostname, j, ipaddr))
		{ 
			sprintf(err_str, "Fail to get host %s ipaddr %d", pair_hostname, j);
			Err_log(err_str);
			pair_ipaddr[j][0]= 0;
		}
		else
			strcpy(pair_ipaddr[j], ipaddr);
	}

	net_no= 0;
	for(;;)
	{
		if(-1==(request_sock=socket(AF_INET, SOCK_DGRAM, 0)))
		{ 
			Err_log("Fail to open request socket");
			Msleep(1000);
			continue;
		}

		ret= 1;

#ifdef	WINDOWS_OS
		if( ioctlsocket(request_sock, FIONBIO, &ret) )
#else
		if( -1==ioctl(request_sock, FIONBIO, &ret) )
#endif
		{ 
			Err_log("Fail to set request socket nonblock");
			closesocket(request_sock);
			Msleep(1000);
			continue;
		}

		for(;;)
		{
			bzero((char *)&server_addr, sizeof(server_addr));
			server_addr.sin_family	=AF_INET;
			server_addr.sin_port= htons(ECHO_SERV_UDP_PORT);

			if(-1==(server_addr.sin_addr.s_addr=inet_addr(pair_ipaddr[net_no])))
			{ 
				sprintf(err_str, "Host %s ipaddr %s error", pair_hostname, pair_ipaddr[net_no]);
				Err_log(err_str);
				net_no= (net_no+1)%local_sum_net_num;
				Msleep(1000);
				continue;
			}

			if(-1==GetIndPtStateByNameStr(localHostPtNameStr, &host_state))
			{
				Msleep(1000);
				continue;
			}
			if(!local_host_state_init_flag)
				host_state= HOST_STATE_NOT_INIT;

			memset(send_msg, 0, sizeof(send_msg));
			strcpy(send_msg, local_hostname);
			send_msg[MAX_HOST_NAME_SIZE]= (char)net_no;
			send_msg[MAX_HOST_NAME_SIZE+1]= (UCHAR)host_state;
			
			send_len= sendto(request_sock, send_msg, sizeof(send_msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
			if(sizeof(send_msg)!=send_len)
			{
				sprintf(err_str, "Send msg len error: %d", send_len);
				Err_log(err_str);
				net_no= (net_no+1)%local_sum_net_num;
				closesocket(request_sock);
				break;
			}
			
			SendTraceMsg(H9000_LOG_INFO,0,"Request send addr: %s, port: %d ", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

			FD_ZERO(&readfds);
			FD_SET(request_sock, &readfds);
			tv.tv_sec= 1;
			tv.tv_usec= 0;
			if((ret=select(request_sock+1, &readfds, NULL, NULL, &tv))<=0)
			{
				SendTraceMsg(H9000_LOG_ERROR,0,"net%d recv request msg timeout", net_no+1);
				
				net_no= (net_no+1)%local_sum_net_num;
				closesocket(request_sock);
				break;
			}

			memset(recv_msg, 0, sizeof(recv_msg));
			recv_len= recvfrom(request_sock, recv_msg, sizeof(recv_msg), 0, NULL, NULL);
			if(recv_len!=sizeof(recv_msg))
			{
// 				if(-1==recv_len)
// 					SendTraceMsg(H9000_LOG_ERROR,0,"net%d recv request msg timeout", net_no+1);
// 				else
// 					SendTraceMsg(H9000_LOG_ERROR,0,"Received respond msg len error: %d errno= %d", recv_len, errno);

				net_no= (net_no+1)%local_sum_net_num;
				closesocket(request_sock);
				break;
			}
			
			if(strcmp(pair_hostname, recv_msg))
			{
				sprintf(err_str, "net%d received host isn't pair host from: %s", net_no+1, recv_msg);
				Err_log(err_str);
				net_no= (net_no+1)%local_sum_net_num;
				continue;
			}

			UpdateState(recv_msg);

			Msleep(UDP_REQUEST_PERIOD);
		}
		Msleep(1000);
	}
}



void *pair_host_manage(void* para)
{
	USHORT		curr_local_state, db_local_state, db_pair_state;	
	int			pair_host;

	for(pair_host=0; pair_host<station_host_num; pair_host++)
	{
		if(!strcmp(station_host_list[pair_host].hostname, pair_hostname))
			break;
	}
	if(pair_host>=station_host_num)
	{ 
		Err_log("Fail to find pair host");
		Msleep(1000);
		return (void*)-1;
	}

	while(!enable_dhsw_manage_flag) /*�ȴ����������������״̬*/
		Msleep(UDP_BROADCAST_PERIOD);

	if(pair_host_state==HOST_STATE_MAIN) /*�������Ϊ����*/
	{
		UpdateHostState(pair_hostname, HOST_STATE_MAIN);
		if(local_host_state==HOST_STATE_MAIN) /*����״̬����*/
			curr_local_state= HOST_STATE_VICE;
		else
			curr_local_state= local_host_state;
		
		UpdateHostState(local_hostname, curr_local_state);
	}
	else if(pair_host_state==HOST_STATE_VICE) /*�������Ϊ����*/
	{
		if(local_host_state==HOST_STATE_MAIN) /*����״̬����*/
			UpdateHostState(pair_hostname, HOST_STATE_VICE);
		else
			UpdateHostState(pair_hostname, HOST_STATE_MAIN);
		curr_local_state= local_host_state;
		UpdateHostState(local_hostname, curr_local_state);
	}
	else /*�������Ϊ����״̬*/
	{
		curr_local_state= local_host_state;
		UpdateHostState(local_hostname, curr_local_state);
		UpdateHostState(pair_hostname, pair_host_state);
	}

	local_host_state_init_flag= 1; /*ȷ��������״̬�󣬿��Զ���㲥��*/

	for(;;)
	{
		Msleep(UDP_REQUEST_PERIOD*3); /*2*/

		/*ȡ���������ݿ���״̬*/
		if(-1==GetIndPtStateByNameStr(localHostPtNameStr, &db_local_state))
			continue;
		if(-1==GetIndPtStateByNameStr(pairHostPtNameStr, &db_pair_state))
			continue;

		if(!station_host_list[pair_host].host_active) /*�������δ����*/
		{
			if(db_pair_state!=HOST_STATE_EXIT) /*�����������Ϊ�˳�*/
				UpdateHostState(pair_hostname, HOST_STATE_EXIT);

			UpdateHostState(local_hostname, local_host_state);
			curr_local_state= local_host_state;/*���ݱ�������״̬���ñ���Ϊ���ػ���ϵ�״̬*/
			SendTraceMsg(H9000_LOG_WARN,0,"�Է��˳�, ������ǰ״̬: %d", curr_local_state);
			continue; 
		}

		station_host_list[pair_host].host_active= 0;

		if(curr_local_state==HOST_STATE_MAIN) /*��ǰ��Ϊ��������*/
		{
			SendTraceMsg(H9000_LOG_WARN,0,"��ǰ����״̬");

			if(local_host_state==HOST_STATE_MAIN) /*������������*/
			{
				if(db_local_state==HOST_STATE_VICE||db_pair_state==HOST_STATE_MAIN) /*�����л���*/
				{
					SendTraceMsg(H9000_LOG_WARN,0,"�ֶ��л�������״̬");

					UpdateHostState(local_hostname, HOST_STATE_VICE);
					UpdateHostState(pair_hostname, HOST_STATE_MAIN);
					curr_local_state= HOST_STATE_VICE;
				}
				else if(pair_host_state==HOST_STATE_MAIN) /*���������Ϊ����*/
				{ 
					SendTraceMsg(H9000_LOG_WARN,0,"˫������״̬��Ϊ����");
					
					if(strcmp(local_hostname, pair_hostname)<0)
					{
						SendTraceMsg(H9000_LOG_WARN,0,"��������״̬");

						UpdateHostState(local_hostname, HOST_STATE_MAIN);
						UpdateHostState(pair_hostname, HOST_STATE_VICE);
						curr_local_state= HOST_STATE_MAIN;
					}
					else
					{
						SendTraceMsg(H9000_LOG_WARN,0,"�л�������״̬");

						UpdateHostState(local_hostname, HOST_STATE_VICE);
						UpdateHostState(pair_hostname, HOST_STATE_MAIN);
						curr_local_state= HOST_STATE_VICE;
					}
				}			
				/*����SYSMGR�˳������������Ϊ����*/
				else if(1==sysmgrExitFlag && pair_host_state==HOST_STATE_VICE) 
				{
					SendTraceMsg(H9000_LOG_WARN,0,"����SYSMGR�˳�,�л�������״̬");
					
					UpdateHostState(local_hostname, HOST_STATE_VICE);
					UpdateHostState(pair_hostname, HOST_STATE_MAIN);
					curr_local_state= HOST_STATE_VICE;
				}
				else if(db_local_state!=HOST_STATE_MAIN) /*���򱣳ֱ�������״̬*/
					UpdateHostState(local_hostname, HOST_STATE_MAIN);
			}
			else /*�����������*/
			{
				SendTraceMsg(H9000_LOG_WARN,0,"�л�������״̬");

				UpdateHostState(pair_hostname, HOST_STATE_MAIN); /*��������л�Ϊ����*/
				UpdateHostState(local_hostname, local_host_state);/*���ݱ�������״̬���ñ���Ϊ���ϵ�״̬*/
				curr_local_state= local_host_state;
			}
		}
		else if(curr_local_state==HOST_STATE_VICE) /*��ǰ��Ϊ��������*/
		{
			SendTraceMsg(H9000_LOG_WARN,0,"��ǰ����״̬");

			if(local_host_state==HOST_STATE_MAIN) /*������������*/
			{
				if(db_local_state==HOST_STATE_MAIN||db_pair_state==HOST_STATE_VICE
					||pair_host_state!=HOST_STATE_MAIN) /*�����л���*/
				{
					SendTraceMsg(H9000_LOG_WARN,0,"�ֶ��л�������״̬: db_local= %d, db_pair= %d, pair_host= %d",
						db_local_state, db_pair_state, pair_host_state);

					UpdateHostState(local_hostname, HOST_STATE_MAIN);
					UpdateHostState(pair_hostname, HOST_STATE_VICE);
					curr_local_state= HOST_STATE_MAIN;
				}
				else if(db_local_state!=HOST_STATE_VICE) /*���򱣳ֱ�������״̬*/
					UpdateHostState(local_hostname, HOST_STATE_VICE);
			}
			else /*�����������*/
			{
				SendTraceMsg(H9000_LOG_WARN,0,"�л�������״̬");

				UpdateHostState(pair_hostname, HOST_STATE_MAIN); /*�������Ϊ����*/
				UpdateHostState(local_hostname, local_host_state);/*���ݱ�������״̬���ñ���Ϊ���ϵ�״̬*/
				curr_local_state= local_host_state;
			}
		}
		else /*��ǰ��Ϊ����״̬����*/
		{
			SendTraceMsg(H9000_LOG_WARN,0,"��ǰ����״̬");

			if(local_host_state==HOST_STATE_MAIN) /*��������ָ�����*/
			{
				SendTraceMsg(H9000_LOG_WARN,0,"����ָ�����");

				if(pair_host_state==HOST_STATE_MAIN) /*���������Ϊ����*/
				{
					SendTraceMsg(H9000_LOG_WARN,0,"�Է�Ϊ����״̬�������л�������");

					UpdateHostState(pair_hostname, HOST_STATE_MAIN);
					UpdateHostState(local_hostname, HOST_STATE_VICE);
					curr_local_state= HOST_STATE_VICE; /*�����л�Ϊ����*/
				}
				else /*���������Ϊ����״̬������˫����������ԭ��ͬʱ���������ϣ����ڻָ�������*/
				{
					SendTraceMsg(H9000_LOG_WARN,0,"˫�����ӹ��ϻָ�");

					if(strcmp(local_hostname, pair_hostname)<0)
					{
						UpdateHostState(local_hostname, HOST_STATE_MAIN);
						UpdateHostState(pair_hostname, HOST_STATE_VICE);
						curr_local_state= HOST_STATE_MAIN;
					}
					else
					{
						UpdateHostState(local_hostname, HOST_STATE_VICE);
						UpdateHostState(pair_hostname, HOST_STATE_MAIN);
						curr_local_state= HOST_STATE_VICE;
					}
				}			
			}
			else /*����������Ȼ����*/
			{
				SendTraceMsg(H9000_LOG_WARN,0,"��ǰ��Ȼ����");

				UpdateHostState(local_hostname, local_host_state);
				curr_local_state= local_host_state;
			}
		}
	}
}



int	UpdateState(char *msg)
{
	char	err_str[128];
	char	received_host[MAX_HOST_NAME_SIZE];
	USHORT	net_no, host_no;
	UCHAR	host_state;

	if(strlen(msg)>=MAX_HOST_NAME_SIZE)
	{
		sprintf(err_str, "Received hostname error: %s", msg);
		Err_log(err_str);
		return -1;
	}
	strcpy(received_host, msg);
	if(!strcmp(received_host, local_hostname))
		return 0;

	for(host_no=0; host_no<station_host_num; host_no++)
	{
		if(!strcmp(station_host_list[host_no].hostname, received_host))
			break;
	}
	if(host_no>=station_host_num)
		return 0;

	net_no= msg[MAX_HOST_NAME_SIZE];
	if(net_no>=local_sum_net_num)
	{
		sprintf(err_str, "Received net error: %d", net_no);
		Err_log(err_str);
		return -1;
	}
	local_net_active[net_no]= 1;
	station_host_list[host_no].host_active= 1;
	station_host_list[host_no].net_active[net_no]= 1;
	domain_list[station_host_list[host_no].domain_pos].net_active[net_no]= 1;

	if(station_host_list[host_no].domain_pos != local_domain_pos)
		return 0;

	UpdateHostNetState(received_host, net_no, NET_STATE_NORM);

	host_state= msg[MAX_HOST_NAME_SIZE+1];
	if(host_state==HOST_STATE_NOT_INIT)
		return 0;

	if(host_state>=16)
	{
		sprintf(err_str, "Received host state error: %d", host_state);
		Err_log(err_str);
		return -1;
	}
	
	if(double_host_flag && !strcmp(received_host, pair_hostname))
		pair_host_state= host_state;
	else
		UpdateHostState(received_host, (UCHAR)host_state);
	return 0;
}


int GetHostNetStatePtId(char *hostname, USHORT net_no, POINTER *point)
{
	if(net_no<sys_info_net_num)
		return GetHostSysNetStatePtId(hostname, net_no, point);
	else
		return GetHostCtrlNetStatePtId(hostname, (USHORT)(net_no-sys_info_net_num), point);
}


BOOL GetLocalBroadcastPrvg(char *local_host, char *info_host)
{
	int			i, j, net_norm;
	USHORT		state;
	POINTER		point;
	
	if(!strcmp(info_host, local_host)) /*������Ϣ����������,����������Ϣ�űȽ��Ⱥ�˳��*/
		return TRUE;
	for(i=0; i<local_host_pos; i++)
	{
		if(!strcmp(info_host, station_host_list[i].hostname))
			continue;
		if(station_host_list[i].domain_pos!=local_domain_pos)/*�����Ǳ��������*/
			continue;

		net_norm= 1;
		for(j=0; j<station_host_list[i].net_num;j++)
		{
			if(-1==GetHostNetStatePtId(station_host_list[i].hostname, (USHORT)j, &point))
				continue;
			GetIndPtStateById(&point, &state);
			if(state!=NET_STATE_NORM)
			{
				net_norm= 0;
				break;
			}
		}
		if(net_norm!=1)
			continue;
		

		if(-1==GetHostStatePtId(station_host_list[i].hostname, &point))
			continue;		
		GetIndPtStateById(&point, &state);
		if(state==HOST_STATE_MAIN || state==HOST_STATE_VICE || state==HOST_STATE_CTRLNET_FAIL)
			return FALSE;
	}
	return TRUE;
}

void	UpdateHostState(char *hostname, USHORT state)
{
	USHORT			old_state;
	POINTER			point;
	WR_VAR_UNION	new_value;
	IOST			iost={0};
	DATE_TIME		update_time;
	enum RW_FLAG	rw_flag=0;
	char			message[128];

	if(-1==GetHostStatePtId(hostname, &point))
		return;
	
	GetIndPtStateById(&point, &old_state);
	if(old_state!=state)
	{
		if(GetLocalBroadcastPrvg(local_hostname, hostname))
		{
			BroadCastIndPtState(point, 0, state);
			new_value.ind.rt_state= state;
			GetSysTime( &update_time);
			rw_flag |= RW_UPDATE_TIME|RW_RT_VALUE|RW_UPDATED;
			SetPtValueIostById(&point, new_value,iost, update_time, rw_flag );
			sprintf(message, "Broadcast hostname %s state %d", hostname, state);
			Err_log(message);
		}
	}
}


void	UpdateHostNetState(char *hostname, USHORT net_no, USHORT state)
{
	USHORT		old_state;
	POINTER		point;
	char		message[128];

	if(-1==GetHostNetStatePtId(hostname, net_no, &point))
		return;

	GetIndPtStateById(&point, &old_state);
	if(old_state!=state)
	{
		if(GetLocalBroadcastPrvg(local_hostname, hostname))
		{
			BroadCastIndPtState(point, 0, state);
			sprintf(message, "Broadcast hostname %s net%d state %d", hostname, net_no+1, state);
			Err_log(message);
		}
	}
}


void	UpdateDomainNetState(char *local_domain, char *peer_domain, int net_no, USHORT	net_state)
{
	char		entry_name[128], message[128];
	POINTER		point;
	USHORT		old_state;

	if(-1==GetHostStnId(local_hostname, &point.stn_id))
		return;

	if(-1==GetHostSysLcuId(local_hostname, &point.dev_id))
		return;

	point.data_type= POL_TYPE;

	if(strcmp(local_domain, peer_domain))
		sprintf(entry_name, "%s_%s_N%d", local_domain, peer_domain, net_no);
	else
		sprintf(entry_name, "%s_%s_N%d", peer_domain, local_domain, net_no);

	if(-1==GetEntryIdByName(entry_name, &point))
		return;

	GetIndPtStateById(&point, &old_state);
	if(old_state!=net_state)
	{
		BroadCastIndPtState(point, 0, net_state);
		sprintf(message, "Broadcast %s state %d", entry_name, net_state);
		Err_log(message);
	}
}




