
#ifndef SIMMCOMM_H
#define SIMMCOMM_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Ѳ��ϵͳ�����ϵͳ��ͨѶ�ӿ�
//
#define XHStatOpened		0
#define XHStatClosed		1
#define FUHE_Opened			7	//�����ɷֵ�բ
#define FUHE_Closed			8	//�����ɺϵ�բ

//���ڽ�ʦ����ѧԱ����������
typedef struct{
	int		rank;			//��ѹ�ȼ�
	BYTE	student;		//ѧԱ��
	BYTE	unit;			//��Ԫ��
	BYTE	phase;			//ABC����ָʾ 0-A,1-B,2-C,3-ȫ��
	BYTE	device_type;	//�豸����
	BYTE	device_index;	//���豸�ڸõ�Ԫ��ͬ���豸�е����к�
	BYTE	weather;		//����
	BYTE	wind;			//����
	float	scale;		//�豸����
	float	pos[4];		//λ��x,y,z�ͳ���
	char	model[64];	//ģ������
}MODEL_MESSAGE;

#define OPERATE_DATA_LENGTH	112

#define OPERATE_COMM_NORMAL	100		//Ѳ�Ӳ�����¼����������
#define OPERATE_COMM_ERR	101		//Ѳ�Ӳ�����¼��һ��������
#define OPERATE_COMM_FAULT	102		//Ѳ�Ӳ�����¼�����ش������
	
#define SIMCOMM_ECHO		255		//��Ӧ��ʦ��

//ѧԱ�����ʦ�����͵ı�λ���ݣ�Ϊ��ͳһ�����ѧԱ���ͽ�ʦ���䶼��OPERATE_DATA_LENGTH
#define TTS_ID_LENGTH				32

//ѧԱ�����ʦ�����͵ı�λ����
typedef struct{
	int		student;		//ѧԱ��
	char	id[TTS_ID_LENGTH];
	int		state;
	float	value;
	char	opr_msg[OPERATE_DATA_LENGTH];		//ѧԱ�����ʦ�����͵Ĳ�����¼����
}COMM_MSG;

int		ProcessTTSData(unsigned char *Buffer);
int		ProcessTTSControl(char *code, int abc, int toStat, int Rank);
int		ProcessTTSBiao(char *code, int Bdevicetype, float fValue, int Rank);
int		ProcessTTSEVT(int nDeviceType, char *code, int abc, int toStat, int nSubType);
int		FindDevice(char *code, int type, int phase,  int *Rank);
int		ProcessStudentData( COMM_MSG *pMsg, int nWorkerIndex );
int		ProcessTeacherData( MODEL_MESSAGE *pMsg );
int		ProcessTTSGuide( char *code, int nVaule );
int		ProcessTTSReset();

void loadconfig();
void InsertErrLog(char *err,WORD nType);
UINT TimerThread(LPVOID lParam);

#endif