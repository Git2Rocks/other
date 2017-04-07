/**************************************************************************************************************
added by yyp on 2008.5.26 for H9000 V4.0

	data structrue define for CIP		

Modifying History:

**************************************************************************************************************/
#ifndef	_AB_PLC
#define	_AB_PLC

#ifdef __cplusplus
extern "C" {
#endif
#define CPUSLOT 0
#define ENETSLOT 1
#define CNETSLOT 2
#define CNETIDM 9
#define CNETIDS 10
#define TAGLEN	30
#define MAX_TAGS 10
#define TAGNAME "MW"
#define HEADTAG	1
#define	SEND_SIZE_AB 1024
#define SEGBYTE 2			//yyp
#define BYTE_ID 0XC2
#define SHORT_ID 0XC3
#define INT_ID   0XC4
#define FLOAT_ID 0XCC
#define ROUTE_SIZE 4
#define ROUTE_SIZE_EXT 8

//��ű�ǩ���ƺ�Ԫ�صĸ����Ľṹ��
typedef struct _TagAndElements
{
	char strName[TAGLEN];  //����
	unsigned short int usintElements;  //Ԫ����
}TagAndElements;

//���Ҫд�ı�ǩ���ơ�Ԫ�ظ�����ֵ���͡�ֵ
typedef struct _TagsWrite
{
	char strName[TAGLEN];
    char bDataType;
	char bReserver;
	unsigned short int usintElements; 
	unsigned short int uintAddtionalLength;
}TagsWrite;
    
//IOS�ִ�
typedef struct _IOS
{
	char bExtendedSymbolSegment; //�ִ�����,0x91Ϊ��ǩ����
	char      bDataSize;   //��ǩ���Ƶ��ֽ�����
	char      *bData;      //��ǩ����
	char      *pad;        //��ǩ���Ƶ��ַ���Ϊ����ʱ������ֽ�
}IOS;//RequirePath;

//���ڽ���
typedef struct _ServiceReply
{
	char bService; //��������,0xccΪ����Ӧ,0xcdΪд��Ӧ
	char bReserved;
	char bGeneralStatus;  //��׼״̬�ֽ�
	char bAdditonalStatusSize; //��չ״̬�ֵĳ���
	char cReplyData[MAX_QUERY_SIZE_AB]; //���ص�����ֵ
}ServiceReply;


typedef struct _ValueToWrite
{
	char bDataType;
	char bReserve;
	unsigned short int usintElements;
	char data[SEND_SIZE_AB];
}ValueToWrite;



//��װЭ��ͷ,24�ֽ�
typedef struct _EncapsulationCIPHead
{
	short int sintCommand;   
	//�������,0x65:RegisterSession,0x66: UnRegisterSession,0x04:ListServices, 
	//0x63:ListIdentity, 0x64:ListInterface, 0x6f:SendRRData,0x70:SendUnitData
	short int sintLength;  //CIPЭ���ֽ�������������װЭ��
	int       intSessionHandle;  //�Ự���,��Ŀ�귽����ԭʼ��
	int       intStatus;         //״̬��,�ɹ�Ϊ0��ԭʼ��Ӧ���ô�ֵΪ0
	char      bSenderContext[8];  //���ͷ������ģ����ݴ�ֵ�ж���Ӧ��������Ӧ�ķ���
	int       intOption;          //��ѡ�ӦΪ0
}EncapsulationCIPHead;


//��ַ��������
typedef struct _AddressAndDataItem
{
	short int sintTypeID;  //��ַ������������,��ӦUnConnected Message, AddressӦ��Ϊ0x00,
	//DataӦ��Ϊ0xb2;
	short int sintLength;  //��ַ�����ݵ����ݲ��ֳ���
}AddressAndDataItem;

//���������ר������
typedef struct _CommandSpecificData
{
    int intInterfaceHandle;  //�ӿھ��,CIP��ӦΪ0��
	short int sintTimeout;   //������ʱ��ָ��װЭ��
	short int sintItemCount; //��ַ�����ݵ�������һ��Ϊ2
	short int sintAddressTypeID; //��ַ,0x0000
	short int sintAddressItemLength; //0x0000
	short int sintDataTypeID;    //����,0x00b2
	short int sintDataItemLength;  //���ֶκ�����ݵ��ֽ���
}CommandSpecificData;

//CIPЭ��
typedef struct _CommondIndustrialProtocol
{
	char bService;  //��������, 0x52Ϊ�����ӷ��ͷ�������
	char bRequestPath;  //����·��16bit��(Ϊ2)
	char bLogicalClassSegment;  //�߼��࣬20:ָ8λ�߼���
	char bClass;                //�࣬06:ָ���ӹ������࣬
	char bLogicalInstanceSegment; //�߼�ʵ��,24:ָ8λ�߼�ʵ��
	char bInstance;             //ʵ��,01:ʵ��01
}CommonIndustrialProtocol;

//�����������Ӧ������
typedef struct _ServiceRequestData
{
	char bPriorityAndTime_tick;  //����Ȩ�ͳ�ʱ����
	char bTime_out_ticks;  //��ʱʱ�䳣��
	unsigned short int sintMessageRequestSize; //�����ĵ��ֽ���
	char bService;  //��������,0x0a:��������
	char bRequestPathSize;    //�������·�����ֽ���,���ֶκ󲻺�RoutePath�����ݵ��ֽ���
	char bRequestPathClassSegment; //�������·�����������Ķ�
	char bClass;                   //������
	char bRequestPathInstacneSegment; //�������·����ʵ�������Ķ�
	char bInstance;                //ʵ��
	//Ҫ��
}ServiceRequestData;

//���ڽ���
typedef struct _ServiceRequestResponseData
{
	char bService; //�������ͣ���Ӧ0x8a;��������
	char bReserved; 
	char bGeneralStatus; //��׼״̬�ֽ�
	char bAddtionalStatusSize; //��չ״̬������
}ServiceRequestReponseData;

//������
typedef struct _MessageRequest
{
	char bService;  //��������,0x0a:��������
	char bRequestPathSize;    //
	char bRequestPathClassSegment;
	char bClass;
	char bRequestPathInstacneSegment;
	char bInstance;
	//Ҫ��
}MessageRequest;

//�������
typedef struct _ServicesAggregate
{
	unsigned short int usintNumberOfServices; //������
}ServicesAggregate;

typedef struct _RoutePath
{
	char bRoutePathSizeWord;	//16bit����0x01
	char BResever;				//����   :0
	char bPath[ROUTE_SIZE_EXT];	//·�ɵ�ַ������ֱ�ӷ�����CPU Ϊ 01 00 ,����01��ʾ���أ�00Ϊ�ۺ�
	//char bExtendLinkAddress;  //�Ƿ���չ���ӵ�ַ:01
	//char bLinkAddress;        //��ַ:0
}RoutePath;

typedef struct _recCIP
{
	unsigned char bService;  //��������,0x8a:��������
	unsigned char bReserve;
	unsigned char bGeneralStatus;   //�������
	unsigned char bAddtionalStatusSizeWords;  //��չ��������ִ�С
}recCIP;

typedef struct _recServices
{
	char bService;  //�������
	char bReserve;  //����
}recServices;

typedef struct _RecordTask
{
	short dwContext;
	BOOL blFinished;
}RecordTask;

//�����
typedef struct _ServicePackRead
{
	char bService;				//�������ͣ� 0x4cΪ��, 0x4dΪд
	char bRequirePathWords;		//IOS�ִ���16bit��
	char bExtendedSymbolSegment; //�ִ�����,0x91Ϊ��ǩ����
	char bDataSize;				//��ǩ���Ƶ��ֽ�����
	char TagName[TAGLEN];
	short IOIType;				//0x29 for two byte	
	short StartPos;				//��Ҫ��������鿪ʼλ��
	short ElementNum;			//����Ԫ����
}ServicePackRead;


//�����
typedef struct _ServicePackWrite
{
	char bService;				//�������ͣ� 0x4cΪ��, 0x4dΪд
	char bRequirePathWords;		//IOS�ִ���16bit��
	char bExtendedSymbolSegment; //�ִ�����,0x91Ϊ��ǩ����
	char bDataSize;				//��ǩ���Ƶ��ֽ�����
	char TagName[TAGLEN];
	short IOIType;				//0x29 for two byte	
	short StartPos;				//��Ҫ��������鿪ʼλ��
	char bDataType;
	char bReserve;
	short ElementNum;			//����Ԫ����
	char data[SEND_SIZE_AB];
}ServicePackWrite;


typedef struct _CIPRequest
{
	EncapsulationCIPHead eciphead;		//��װͷ��
	CommandSpecificData cpfhead;		//CPFͷ��
	CommonIndustrialProtocol ciphead;	//CIP ������
	ServiceRequestData sendhead;		//����ͷ
	ServicesAggregate tagnum;			//�������
	short offset[MAX_TAGS];				//ƫ�Ƶ�ַ
	ServicePackRead	srvdata[MAX_TAGS];		//�����
	RoutePath path; 
}CIPRequest;

typedef struct _CIPWrite
{
	EncapsulationCIPHead eciphead;		//��װͷ��
	CommandSpecificData cpfhead;		//CPFͷ��
	CommonIndustrialProtocol ciphead;	//CIP ������
	ServiceRequestData sendhead;		//����ͷ
	ServicesAggregate tagnum;			//�������
	short offset[MAX_TAGS];				//ƫ�Ƶ�ַ
	ServicePackWrite srvdata[MAX_TAGS];		//�����,ע��,ͬһ��tag��srvdata��wrdata�����洢
	RoutePath path; 
}CIPWrite;

typedef struct _CIPResponse
{
	EncapsulationCIPHead eciphead;		//��װͷ��
	CommandSpecificData cpfhead;		//CPFͷ��
	recCIP ciphead;						//CIP ������
	ServicesAggregate tagnum;			//�������
	short offset[MAX_TAGS];				//ƫ�Ƶ�ַ
	ServiceReply srvdata[MAX_TAGS];		//�����
}CIPResponse;

CIPRequest g_ciprq;
CIPWrite g_cipwt;
CIPResponse g_ciprp;
int SessionHandle;
int dwSenderContext;

int CvtReadToBuf(char *buffer,int *p_bytesend, CIPRequest ciprq, BOOL readslave);
int CvtWriteToBuf(char *buffer,int *p_bytesend, CIPWrite cipwt, BOOL readslave);

#ifdef __cplusplus
}
#endif

#endif


