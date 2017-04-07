/************************************************************
*  FILE NAME:           dsp_iec104_info.c   			*
*  FUNCTION:            Display message of iec104 communication	*
*			frame saved in shared memory		*
*  NAME :  					        	*
*  DATE:                Sept.,2006                		*
*								*
************************************************************/
#include "../inc/iec104_com.h"

char infobuf[1024];

SHM_BUF *shm_buf_addr;
int shm_id_buf;

struct shm_rec *shm_rec_addr;
int shm_id_rec;

void Endproc(int sig_no)
{
	int i;

	printf("  ---- DSP_IEC_INFO exit signal %d received!  ----\n",sig_no);
	exit(0);
} 
                                                                
int main(int argc,char *argv[])
{ 
	char	tmp[1024];
	int	ptr, headptr,i,len;

	i = 0;
	signal(SIGKILL,Endproc);
	signal(SIGTERM,Endproc);
	signal(SIGINT,Endproc);

	printf("\n### dsp_iec104_info: for display the transmitted packet message of IEC104 ***\n\n");
	for(;;)
	{
		printf("Please Select the station bellow to display \n\n");
		
		printf("\t1 SBX-DL (����Ϫ)\n");;
		printf("\t2 GZ-DL (����)\n");
		printf("\t3 BS-DL (����)\n");
		printf("\t4 TK-DL (�п�)\n");
		printf("\t5 HJ-DL (�齭)\n");
		printf("\t6 WQX-DL (��ǿϪ)\n");
		printf("\t7 LJT-DL (���̲)\n");
		printf("\t8 DP-DL (��ƺ)\n");
		printf("\t9 ZXK-DL (��Ϫ��)\n");
		printf("\t10 MJT-DL (����)\n");
		printf("\t11 WMP-DL (������)\n");
		printf("\t12 JWZ-DL (��β��)\n");
		printf("\t13 HMF-DL (���ӷ�)\n");
		printf("\t14 QD-DL (ǭ��)\n");
		
		printf("\t15 SBX-DX (����Ϫ)\n");;
		printf("\t16 GZ-DX (����)\n");
		printf("\t17 BS-DX (����)\n");
		printf("\t18 TK-DX (�п�)\n");
		printf("\t19 HJ-DX (�齭)\n");
		printf("\t20 WQX-DX (��ǿϪ)\n");
		printf("\t21 LJT-DX (���̲)\n");
		printf("\t22 DP-DX (��ƺ)\n");
		printf("\t23 ZXK-DX (��Ϫ��)\n");
		printf("\t24 MJT-DX (����)\n");
		printf("\t25 WMP-DX (������)\n");
		printf("\t26 JWZ-DX (��β��)\n");
		printf("\t27 HMF-DX (���ӷ�)\n");
		printf("\t28 QD-DX (ǭ��)\n");
		
		printf("\nPlease Select the station ( number 1 --28 ):");

		scanf("%d",&i);
		if(i < 1 || i>28)
		{
			printf("\n\nWrong Number %d! Please Select the station again\n\n",i);
			sleep(1);
			continue;			
		}
	

/*      ��ȡ��¼�������ڴ��ַ  */
		shm_buf_addr=( SHM_BUF *)LinktoShareMem(SHM_BUF_KEY_CHAR+i);

		printf ( "the shm_buf_addr is:0x%x\n",shm_buf_addr );

		if ((long *)shm_buf_addr==(long *)-1)
		{
			printf("\n::Error shmat shm_buf_addr: errno=%d\n",errno);
			continue;
		}
		else
			printf("\n:: shmat shm_buf_addr: OK!\n");
		break;
	}

	ptr = 0;
	for(;;)
	{
		headptr = shm_buf_addr->header_ptr;
		if(ptr == headptr)
		{
			sleep(1);
			continue;
		}
		else if(ptr < headptr)
		{
			len = headptr-ptr;
			if(len > 1022)
				len = 1022;
			memcpy(tmp, &shm_buf_addr->buf[ptr], len);
			tmp[len] = 0;
			printf("%s",tmp);
			ptr = ptr + len;
			continue;
		}
		else
		{
			len = DSP_INFO_SIZE-ptr;
			if(len > 1022)
			{
				len = 1022;
				memcpy(tmp, &shm_buf_addr->buf[ptr], len);
				tmp[len] = 0;
				printf("%s",tmp);
				ptr = ptr + len;
				continue;
			}
			memcpy(tmp, &shm_buf_addr->buf[ptr], len);
			tmp[len] = 0;
			printf("%s",tmp);
			if(headptr > 1022)
			{
				len = 1022;
				memcpy(tmp, &shm_buf_addr->buf[0], len);
				tmp[len] = 0;
				printf("%s",tmp);
				ptr = len;
				continue;
			}
			memcpy(tmp, &shm_buf_addr->buf[0], headptr);
			tmp[headptr] = 0;
			printf("%s",tmp);
			ptr = headptr;
		}
	}
}

