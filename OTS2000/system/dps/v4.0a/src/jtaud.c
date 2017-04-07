

#include	<windows.h>
#include	<stdio.h>
#include	"../../../dms/v4.0a/inc/dms_com.h"

#include	"../inc/jtaud.h"


/*
����һ��: 

	jTTSPreInit			��ʼ��֮ǰ����ϵͳ����ȡ������
	jTTSInit			��ʼ��jTTS���ģ���ȡ����
	jTTSEnd				�ͷ�jTTS����ռ���ڴ�
	jTTSSetLogFile		����ϵͳ�ļ�¼��־�ļ�

	jTTSSetPlay			ȷ�������豸�ͷ��������еĻص�����
						(��׼�汾��ֻ֧��ȱʡ�����豸)
	jTTSPlay			���÷����豸�Ķ�ָ�����ı�
	jTTSStop			��ֹ��ǰ���Ķ�
	jTTSPause			��ͣ��ǰ���Ķ�
	jTTSResume			�ָ���ǰ���Ķ�
	jTTSSetParam		���ò���
	jTTSGetParam		�õ�����
	jTTSSet2			ͨ���ṹ�ķ�ʽһ�������������ϳɵ����в���
	jTTSGet2			ͨ���ṹ�ķ�ʽһ���Ի�������ϳɵ����в���
	jTTSPlayToFileEx	���ı����������ϳɣ������д�������ļ�������ʹ�ô���ĺϳɲ�����
	                    ʹ���µĻص����������Իش��û�ָ��������

	(��׼�汾��֧�����º���)
	jTTSSessionStart	��ʼֱ�ӵõ��������������ϳɹ���
	jTTSSessionConfig2	���������ϳɹ��̵Ĳ�����ʹ���µĽṹ
	jTTSSessionGetDataEx	���������ϳɣ�ֱ�ӵõ���������ʹ���ڲ�������
	jTTSSessionStop			��ֱֹ�ӵõ��������������ϳɹ���

-----------------------
����������Ϊ����ǰ�汾���ݶ�����:
1.0
	jTTSSet				ͨ���ṹ�ķ�ʽһ�������������ϳɵ����в���(Ϊ1.0����ݱ�������ʹ��jTTSSet2)
	jTTSGet				ͨ���ṹ�ķ�ʽһ���Ի�������ϳɵ����в���(Ϊ1.0����ݱ�������ʹ��jTTSGet2)
	jTTSPlayToFileConfig		���ı����������ϳɣ������д�������ļ�������ʹ�ô���ĺϳɲ���
								(Ϊ1.0����ݱ�������ʹ��jTTSPlayToFileConfig2)
	jTTSSessionConfig	���������ϳɹ��̵Ĳ���
						(Ϊ1.0����ݱ�������ʹ��jTTSSessionConfig2)

2.0
	jTTSSessionGetData	���������ϳɣ�ֱ�ӵõ�������
						(Ϊ2.0����ݱ�������ʹ��jTTSSessionConfig2)

	jTTSSetPlayToFile	ȷ���������ļ������еĻص�����
	jTTSPlayToFile		���ı����������ϳɣ������д�������ļ�
						(��׼�汾��ֻ֧��WAV�ļ�)
	jTTSPlayToFileConfig2		���ı����������ϳɣ������д�������ļ�������ʹ�ô���ĺϳɲ���

2.1
	jTTSSetCodePage		���������ϳ��ı��Ĵ��뼯
	jTTSGetCodePage		�õ���ǰ�����ϳ��ı��Ĵ��뼯
	jTTSSetVoiceID		���������ϳ����õ�����
	jTTSGetVoiceID		�õ���ǰ�����ϳ����õ�����
	jTTSSetPitch		���������ϳɵĻ�Ƶ
	jTTSGetPitch		�õ������ϳɵĻ�Ƶ
	jTTSSetVolume		���������ϳɵ�����
	jTTSGetVolume		�õ������ϳɵ�����
	jTTSSetSpeed		���������ϳɵ�����
	jTTSGetSpeed		�õ������ϳɵ�����
	jTTSSetPuncMode		���������ϳɵı������Ķ���ʽ
	jTTSGetPuncMode		�õ������ϳɵı������Ķ���ʽ
	jTTSSetDigitMode	���������ϳɵ����ִ��Ķ���ʽ
	jTTSGetDigitMode	�õ������ϳɵ����ִ��Ķ���ʽ
	jTTSSetEngMode		���������ϳɵ�Ӣ�Ĵ��Ķ���ʽ
	jTTSGetEngMode		�õ������ϳɵ�Ӣ�Ĵ��Ķ���ʽ
	jTTSSetRemoteTryTime		����Զ�̺ϳ�ʱ���ӵ����Դ���
	jTTSGetRemoteTryTime		�õ�Զ�̺ϳ�ʱ���ӵ����Դ���
	jTTSSetRemoteLoadBalance	����Զ�̺ϳ�ʱ�Ƿ�ʹ�ø���ƽ�����
	jTTSGetRemoteLoadBalance	�õ�Զ�̺ϳ�ʱ�Ƿ�ʹ�ø���ƽ�����
*/




#define ERR_NONE			0
#define	ERR_ALREADYINIT	1
#define	ERR_NOTINIT			2 
#define	ERR_MEMORY			3
#define	ERR_INVALIDHWND		4
#define	ERR_INVALIDFUNC		5
#define	ERR_OPENLIB			6
#define	ERR_READLIB			7
#define	ERR_PLAYING		8
#define	ERR_DONOTHING			9
#define ERR_INVALIDTEXT		10
#define	ERR_CREATEFILE			11
#define	ERR_WRITEFILE		12
#define	ERR_FORMAT				13
#define	ERR_INVALIDSESSION		14
#define	ERR_TOOMANYSESSION		15
#define	ERR_MORETEXT			16
#define	ERR_CONFIG				17
#define	ERR_OPENDEVICE			18
#define	ERR_RESETDEVICE		19
#define	ERR_PAUSEDEVICE		20
#define	ERR_RESTARTDEVICE		21
#define	ERR_STARTTHREAD		22
#define	ERR_BEGINOLE		23
#define	ERR_NOTSUPPORT			24
#define	ERR_SECURITY		25
#define	ERR_CONVERT			26
#define	ERR_PARAM				27
#define	ERR_INPROGRESS		  28
#define	ERR_INITSOCK			29
#define	ERR_CREATESOCK			30
#define	ERR_CONNECTSOCK		31
#define	ERR_TOOMANYCON			32
#define	ERR_CONREFUSED			33
#define	ERR_SEND				34
#define	ERR_RECEIVE			35
#define	ERR_SERVERSHUTDOWN		36
#define	ERR_OUTOFTIME			37
#define	ERR_CONFIGTTS			38
#define	ERR_SYNTHTEXT			39
#define	ERR_CONFIGVERSION		40

// Log File Flag
#define LOG_TEXT	0x01	// �Ƿ�����־�ļ��м�¼�ϳɵ��ı�
#define LOG_SESSION	0x02	// �Ƿ��¼ÿ��Session���̵���ϸ�������

#define WM_JTTS_NOTIFY	(WM_USER + 0x4999)

// wParam of WM_JTTS_NOTIFY or JTTSCALLBACKPROC
#define NOTIFY_BEGIN		0	// lParam: not use 
#define NOTIFY_END			1	// lParam: not use
#define NOTIFY_PROGRESS		2	// lParam: bytes of content have been read
#define NOTIFY_PROGRESS2	3	// lParam: end postion of content will be read in next session

#define STATUS_NOTINIT	0
#define STATUS_READING	1
#define STATUS_PAUSE	2
#define STATUS_IDLE		3

// CodePage���ڴ˰汾�У�CP_GB2312��CP_GBK��Ч
#define CP_GB2312		0	
#define CP_GBK			1	
#define CP_BIG5			2

// VoiceID���ڴ˰汾�У�ֻ��ʹ��VID_FEMALE1
#define VID_MALE1		0
#define VID_FEMALE1		1

// Volume, Speed, Pitch
#define VOLUME_MIN	0
#define VOLUME_MAX	9
#define SPEED_MIN	0
#define SPEED_MAX	9
#define PITCH_MIN	0
#define PITCH_MAX	9

// PuncMode
#define PUNC_OFF		0
#define PUNC_ON			1

// DigitMode���ڴ˰汾�У�������DIGIT_AUTO_TELEGRAM���޷��Զ��жϵ����ִ�������������
#define DIGIT_AUTO_NUMBER	0
#define DIGIT_TELEGRAM		1
#define DIGIT_NUMBER		2
#define DIGIT_AUTO_TELEGRAM	3

#define DIGIT_AUTO			DIGIT_AUTO_NUMBER

// EngMode
#define ENG_AUTO			0	/* �Զ���ʽ */
#define ENG_SAPI			1	/* ǿ��SAPI��ʽ */
#define ENG_LETTER			2	/* ǿ�Ƶ���ĸ��ʽ */
#define ENG_LETTER_PHRASE	3	/* ����ĸ����¼���ʷ�ʽ */

enum JTTSPARAM
{
	PARAM_CODEPAGE,			// CP_xxx
	PARAM_VOICEID,			// VID_xxx
	PARAM_PITCH,			// PITCH_MIN - PITCH_MAX
	PARAM_VOLUME,			// VOLUME_MIN - VOLUME_MAX
	PARAM_SPEED,			// SPEED_MIN - SPEED_MAX
	PARAM_PUNCMODE,			// PUNCMODE_xxx
	PARAM_DIGITMODE,		// DIGITMODE_xxx
	PARAM_ENGMODE,			// ENGMODE_xxx
};

enum JTTSREMOTEPARAM
{
	PARAM_REMOTE_TRYTIMES,			// �Ϸ�ֵ��1 - 100, ȱʡֵ��10
	PARAM_REMOTE_LOADBALANCE,		// �Ϸ�ֵ��TRUE, FALSE, ȱʡֵ��FALSE
};

#define FORMAT_WAV			0	// PCM Native (ĿǰΪ16KHz, 16Bit)
// �������ݽ���רҵ����֧��
#define FORMAT_VOX_6K		1	// OKI ADPCM, 6KHz, 4bit (Dialogic Vox)
#define FORMAT_VOX_8K		2	// OKI ADPCM, 8KHz, 4bit (Dialogic Vox)
#define FORMAT_ALAW_8K		3	// A��, 8KHz, 8Bit
#define FORMAT_uLAW_8K		4	// u��, 8KHz, 8Bit
#define FORMAT_WAV_8K8B		5	// PCM, 8KHz, 8Bit
#define FORMAT_WAV_8K16B	6	// PCM, 8KHz, 16Bit
#define FORMAT_WAV_16K8B	7	// PCM, 16KHz, 8Bit
#define FORMAT_WAV_16K16B	8	// PCM, 16KHz, 16Bit

#define FORMAT_FIRST		0
#define FORMAT_LAST			8

#define JTTS_VERSION	0x0002	// version 2.0 

typedef struct 
{
	WORD wVersion;
	UINT nCodePage;
	UINT nVoiceID;
	int nPitch;
	int nVolume;
	int nSpeed;
	int nPuncMode;
	int nDigitMode;
	int nEngMode;
}JTTSCONFIG2;

struct JTTSREMOTECONFIG
{
	WORD wVersion;
	int nTryTimes;
	BOOL bLoadBalance;
};

typedef BOOL (* JTTSCALLBACKPROC)(WORD wParam, LONG lParam);
typedef BOOL (* JTTSCALLBACKPROCEX)(WORD wParam, LONG lParam, DWORD dwUserData);

//------------------------------------------------------------------------
// ϵͳ����

typedef  int ERRCODE; 

ERRCODE jTTSSetSerialNo(const char * pszSerialNo);
ERRCODE jTTSPreInit(int * arrayVoiceID, int nCount);
ERRCODE jTTSInit(const char * pcszLibPath);
ERRCODE jTTSEnd();
void    jTTSSetLogFile(const char* pcszLogFile, DWORD dwLogFlag);

//------------------------------------------------------------------------
// ���ź��� 

// ��׼�汾�н�֧��uDeviceID == WAVE_MAPPER(-1), ��ȱʡ�������豸
ERRCODE jTTSSetPlay(UINT uDeviceID, HWND hwnd, JTTSCALLBACKPROC lpfnCallback);
ERRCODE jTTSPlay(const char * pcszText);
ERRCODE jTTSStop();
ERRCODE jTTSPause();
ERRCODE jTTSResume();
int		jTTSGetStatus();

//------------------------------------------------------------------------
// ���ŵ��ļ����� 

// ��׼�汾�н�֧��nFormat = FORMAT_WAV, ��д��WAV�ļ���ʽ
// pConfig == NULLʱ��ʹ��ϵͳ��Config
// dwFlag, Ŀǰ���ã�����Ϊ0
ERRCODE jTTSPlayToFileEx();

//------------------------------------------------------------------------
// ���ú��� 
ERRCODE jTTSSet2();
ERRCODE jTTSGet2();
ERRCODE jTTSSetParam();
DWORD   jTTSGetParam();

//-------------------------------------------------------------
// Զ�̺ϳɲ�������
ERRCODE jTTSSetRemote();
ERRCODE jTTSGetRemote();
ERRCODE jTTSSetRemoteParam();
DWORD   jTTSGetRemoteParam();

//------------------------------------------------------------------------
// �ϳɹ��̵ײ㺯�� 

// ����jTTSSessionϵ�к�������רҵ����֧��
ERRCODE jTTSSessionStart(D);
ERRCODE jTTSSessionConfig2();
ERRCODE jTTSSessionRemoteConfig();
ERRCODE jTTSSessionGetDataEx();
ERRCODE jTTSSessionStop();
ERRCODE jTTSSessionGetReadBytes();

// -------------------------------------------------------------------------------------
// �������ݽṹ�ͺ�����Ϊ��1.0�汾����
struct JTTSCONFIG
{
	UINT nCodePage;
	UINT nVoiceID;
	int nPitch;
	int nVolume;
	int nSpeed;
	int nPuncMode;
	int nDigitMode;
};

ERRCODE jTTSPlayToFileConfig();
ERRCODE jTTSSet();
ERRCODE jTTSGet();
ERRCODE jTTSSessionConfig();

// ���º�����Ϊ��2.0�汾����
ERRCODE jTTSSessionGetData();
ERRCODE jTTSSetPlayToFile();
ERRCODE jTTSPlayToFile();
ERRCODE jTTSPlayToFileConfig2();

// ���º�����Ϊ��2.1�汾����
ERRCODE jTTSSetCodePage(int nCodePage);
int		jTTSGetCodePage();
ERRCODE jTTSSetVoiceID(int nVoiceID);
int		jTTSGetVoiceID();
ERRCODE jTTSSetPitch(int nPitch);
int		jTTSGetPitch();
ERRCODE jTTSSetVolume(int nVolume);
int		jTTSGetVolume();
ERRCODE jTTSSetSpeed (int nSpeed);
int		jTTSGetSpeed();
ERRCODE jTTSSetPuncMode(int bPuncMode);
int		jTTSGetPuncMode();
ERRCODE jTTSSetDigitMode(int nDigitMode);
int		jTTSGetDigitMode();
ERRCODE jTTSSetEngMode(int nEngMode);
int		jTTSGetEngMode();
ERRCODE jTTSSetRemoteTryTime(int nTryTime);
int		jTTSGetRemoteTryTime();
ERRCODE jTTSSetRemoteLoadBalance(BOOL bLoadBalance);
BOOL	jTTSGetRemoteLoadBalance();



BOOL	g_CallBackProc(WORD wParam, LONG lParam);
static BOOL		g_bFinishPlay = FALSE;
static BOOL		g_bInit = FALSE;
static BOOL		bOutputFile = FALSE;
static char		outputFileName[256];

#define	JTTS_LIBRARY_PATH1	"\\tts\\jttts\\bin"
#define	JTTS_LIBRARY_PATH2	"\\�����ϳ�\\bin"


int	InitAudioLibraryJT(int nPitch, int nVolume, int nSpeed, char *outputFile)
{
	int		iErr;
	char	err_str[128];
	
	//This structure includes all parameters used by audio composing.
	JTTSCONFIG2 sConfig =
	{ 
		2,					//version number
		CP_GB2312,			//code set (CP_GB2312, CP_GBK, CP_BIG5) 
		VID_FEMALE1,		//voice type 
		nPitch,				//base pitch (0-9). more bigger, more higher.
		nVolume,			//volume of voice (0-9). more bigger, more higher.
		nSpeed,				//speed  of voice (0-9). more bigger, more faster.
		PUNC_OFF,			//the punctuation can be read or not.(PUNC_ON,PUNC_OFF)
		DIGIT_AUTO_TELEGRAM,//the mode of reading digital string.
							//( DIGIT_TELEGRAM, DIGIT_NUMBER, DIGIT_AUTO_NUMBER, DIGIT_AUTO_TELEGRAM )
		ENG_LETTER			//the mode of reading English
							//( ENG_AUTO,  ENG_SAPI, ENG_LETTER,  ENG_LETTER_PHRASE )
	};

	//set serial number
	if( (iErr=jTTSSetSerialNo("0E7A438C6736"))!=ERR_NONE )
	{
		sprintf(err_str, "jTTSSetSerialNo() error! (errcode=%d)\n",iErr); 
		Err_log(err_str);
		return -1;
	}

	//initialize audio library
	if( (iErr=jTTSInit(JTTS_LIBRARY_PATH1))!=ERR_NONE )
	{
		if( (iErr=jTTSInit(JTTS_LIBRARY_PATH2))!=ERR_NONE )
		{
			sprintf(err_str, "jTTSInit() error! (errcode=%d, path=%s)\n",iErr,JTTS_LIBRARY_PATH2);  
			Err_log(err_str);
			return -1;
		}
	}

	if(GetExLangState())
		sConfig.nEngMode= ENG_AUTO;
	else
		sConfig.nEngMode= ENG_LETTER;

	//set parameter for audio composing
	if( (iErr= jTTSSet2(&sConfig))!=ERR_NONE )
	{
		sprintf(err_str, "jTTSSet2() error! (errcode=%d)\n",iErr);  
		Err_log(err_str);
		return -1;
	}

	if(outputFile)
	{
		strcpy(outputFileName, outputFile);
		bOutputFile = TRUE;
	}
	else
	{
		//set audio device(-1 means default device),  set callback function.
		if( (iErr=jTTSSetPlay(-1, NULL, g_CallBackProc ))!=ERR_NONE )
		{
			sprintf(err_str, "jTTSSetPlay() error! (errcode=%d)\n",iErr);  
			Err_log(err_str);
			return -1;
		}
	}

	Err_log("Success to init JT audio lib");
	g_bInit= TRUE;
	return 0;
}


int PlayStrAudioJT(char *str)
{
	int		iErr;
	char	err_str[128];

	if(!g_bInit)
	{  
		sprintf(err_str, "No init JT audio kernal\n"); 
		Err_log(err_str);
		return -1;
	}

	if(bOutputFile)
	{
		if((iErr=jTTSPlayToFileEx(str, outputFileName, FORMAT_WAV_8K8B, NULL, 0, NULL, 0x12345678))!=ERR_NONE )
		{
			sprintf(err_str, "jTTSPlayToFileEx() error! (errcode=%d)\n", iErr);  
			Err_log(err_str);
			return -1;
		}
		return 0;
	}


	//read text and audio play 
	g_bFinishPlay= FALSE;
	if( (iErr=jTTSPlay(str))!=ERR_NONE )
	{  
		sprintf(err_str, "jTTSPlay() error! (errcode=%d)\n",iErr); 
		Err_log(err_str);
		if(iErr==ERR_PLAYING)
			Sleep(2000);
		return -1;
	}
	else
	{	//because jTTSPlay() create a thread for audio play, so waiting for thread finished.
		while( !g_bFinishPlay ) 
			Sleep(100);			
	}
	Sleep(500);
	return 0;
}

int CreateStrAudFileJT(char *str, char *outAudFile)
{
	int		iErr;
	char	err_str[128];

	if(!g_bInit)
	{  
		sprintf(err_str, "No init JT audio kernal\n"); 
		Err_log(err_str);
		return -1;
	}

	if(!outAudFile)
	{  
		sprintf(err_str, "outAudFile is null\n"); 
		Err_log(err_str);
		return -1;
	}

	if((iErr=jTTSPlayToFileEx(str, outAudFile, FORMAT_WAV_8K8B, NULL, 0, NULL, 0x12345678))!=ERR_NONE )
	{
		sprintf(err_str, "jTTSPlayToFileEx() error! (errcode=%d)\n", iErr);  
		Err_log(err_str);
		return -1;
	}
	Sleep(100);
	return 0;
}


BOOL g_CallBackProc(WORD wParam, LONG lParam)
{
	switch(wParam)
	{
	case NOTIFY_BEGIN:
		//printf("Callback Func - Notify - Begin\n");
		break;
	case NOTIFY_END:
		//printf("Callback Func - Notify - End\n");
		g_bFinishPlay = TRUE;
		break;
	case NOTIFY_PROGRESS:
		//printf("Callback Func - Notify - %ld End\n", lParam);
		break;
	case NOTIFY_PROGRESS2:
		//printf("Callback Func - Notify - Will Read To %ld\n", lParam);
		break;
	default:
		//printf("Callback Func - Notify - Unknow\n");
		break;
	}
	return TRUE;
}


int ReleaseAudioLibraryJT(void)
{
	if(g_bInit)
		jTTSEnd();
	g_bInit= 0;
	return 0;
}
