		
	/* ֻ�����峣�������� */		
	/*  ����OIX���õ���һЩ�����ڷ�������ͷ�ļ��еĳ���  */
	/**********************************
       SYN by hcl 2007.12.10
    ***********************************/
	
#define	    ALARM_FONT	0
#define	    DBTAB_FONT	0
#define	    SGZY_FONT	0
#define	    TREND_FONT	0
#define	    SBO_FONT	0

#define	    ALM_AUD_TIME  3


/*  define  different  color for interlock  check  */  
#define UNPASS_COLOR    RED1    
#define PASSED_COLOR    GREEN	
#define SYMBOL_COLOR	YELLOW

/*  define  different  color for data quality fault or manual  */  
#define FAULT_COLOR	RED1
#define MANUAL_COLOR	YELLOW

#define RAISE_TIME  10
/****************hcl for double screen*************/
 /*��ʾ���ֱ�������*/

#define LENFORPOINTER 1000     /*���ںϲ�����crt_n�Ĳ���*/
#define STND_WIDTH 1270	       /*1280��׼���*/
#define STND_HEIGHT 1024       /*��׼�߶�*/

#define MAX_DSP_MOD 10

#define KICKOFFTIME  60*60*1000   /*60���Ӳ��������û�����!*/


//int SCREEN_WIDTH_MOD[MAX_DSP_MOD]={1024,1280,1600};

/*************************************************/


/************************************************************************/
/*  ��ӡͼƬ add by hcl                                */
#define SOFTCPY_MODE 0   /*��������ģʽ */
#define NORMAL_MODE  1   /*Ĭ��ֵ��ӡ���棬ֱ����Ļ��ͼģʽ*/
#define RTP_MODE     2   /*��ӡ�����棬��Ļȡ����ӡ*/
#define SGZY_MODE    3   /*��ӡ���ƣ��¹�׷�䣬��Ļȡ����ӡ*/

/************************************************************************/
#define LAYERNUM 16 //�������
int SelectLayer[MAX_CRT_NUMBER][LAYERNUM];
typedef struct{
int UseFilter;
int changeflag;
}USERFILETER;
USERFILETER UseLayerFilter[MAX_CRT_NUMBER];

#define EVENT_MAX_NUM 3 //�¼�һ����������

