// TransferConfig.h: interface for the CTransferConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFERCONFIG_H__056C79E4_E0D9_4C2F_9F51_7B62320E49F7__INCLUDED_)
#define AFX_TRANSFERCONFIG_H__056C79E4_E0D9_4C2F_9F51_7B62320E49F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//����
const int MaxFileType=8;			//�ļ�������
const int MaxDstNum=20;				//���Ŀ��������	
const int MAXFILE=20000;				//�����ѡ�ļ���
#endif // !defined(AFX_TRANSFERCONFIG_H__056C79E4_E0D9_4C2F_9F51_7B62320E49F7__INCLUDED_)
//�Զ������ͣ�Ŀ����������
struct DstComputer
{
	CString DstIP;					//Ŀ������IP��ַ
	CString Username;				//�û���
	CString Passwd;					//����
	int PortNum;					//�˿ں�
	CString DstDriver;				//Ŀ���̷�
	CString DstFileDir[MaxFileType];		//ÿһ�ִ����ļ���·������ΪUnix����Ϊ����·��
	CString DstUnixDir[MaxFileType];		//ר�����Unix�����洢Unix���ľ���·��
	int DstType;					//Ŀ���������ͣ�0ΪPC��1ΪUnix
	int Status;						//�Ƿ����ã�0Ϊ���ã�1Ϊ����
};


//���������࣬�洢�������ļ���ȡ������������Ϣ
class CTransferConfig
{
public:
	CTransferConfig();						//���캯��
	virtual ~CTransferConfig();				//��������
public:
	bool GetConfigFromFile();				//�������ļ���ȡ����������Ϣ
	bool WriteConfigToFile();				//���û��ڽ�������ѡ�������������Ϣд���ļ�
	bool WriteDstConfigToFile();			//���û��ڽ�������ѡ���Ŀ������������Ϣд���ļ�
	bool SetConfigDir();	
	bool DelDst(int nDst);					//ɾ��ָ�������
public:
	CString strConfigFileName;				//�����ļ�����·��
	CString m_prjName;						//��Ŀ����
	CString m_srcDriver;					//Դ�̷�
	CString m_srcVersion;					//Դ�汾
	int m_srcFileSel[MaxFileType];			//��ѡ��������ļ�
	int m_srcFileNum[MaxFileType];			//ÿ�ִ����ļ��ĸ�����ͨ���Ҳ��һ��	
	CString m_srcFileDir[MaxFileType];		//ÿһ�ִ����ļ������·��
	CString m_srcFileList[MaxFileType][MAXFILE];		//ÿһ�ִ����ļ������ļ��б�����
	int m_fileType[MaxFileType];			//�ļ����ͣ�0Ϊ�ı���1Ϊ������
	int m_dstCount;							//Ŀ����������Ŀ
	DstComputer m_dstComputer[20];			//Ŀ����������
	int m_ftpTransMode;						//�ļ����䷽ʽ��0Ϊbat��1Ϊftp�෽ʽ
	int m_ShowMode;							//���Ϊbat���У�0Ϊ����ʾ���ڣ�1Ϊ��ʾ����
};