// TransferConfig.cpp: implementation of the CTransferConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "transferfile.h"
#include "TransferConfig.h"
#include "transferfileDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTransferConfig::CTransferConfig()
{
	CString CurExeFilePath="";				//��ִ���ļ�������·�����ļ���
	int i,j,curPos;
	CString strtmp="";
	TCHAR exeFullPath[MAX_PATH];			// MAX_PATH��API�ж����˰ɣ�������128 
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	strtmp=exeFullPath;						//��ȡ��ǰ����·�����ļ�����
	CurExeFilePath="";
	j=1;
	m_ftpTransMode=0;
	while(j>=0)
	{
		j=strtmp.Find("\\");
		CurExeFilePath=CurExeFilePath+strtmp.Left(j+1);
		strtmp=strtmp.Right(strtmp.GetLength()-j-1);
		curPos=j;
	};

	strConfigFileName=CurExeFilePath+"config.ini";
	for(i=0;i<MaxFileType;i++)
	{
		m_srcFileSel[i]=0;
	}
}

CTransferConfig::~CTransferConfig()
{

}

////�������ļ���ȡ����������Ϣ
bool CTransferConfig::GetConfigFromFile()
{

	int i,j;
	char chReturn[200];
	char buffer[2];
	CString strline,strtmp;
	CString DstIP,DstType,Passwd,Status,Username,DstDriver;	
	CString srcFileSel,srcDriver,srcVersion;
	//��ȡ������Ϣ
	GetPrivateProfileString("COMMMON","srcDriver","Err",chReturn,200,strConfigFileName);
	m_srcDriver=chReturn;
	GetPrivateProfileString("COMMMON","srcVersion","Err",chReturn,200,strConfigFileName);
	m_srcVersion=chReturn;
	GetPrivateProfileString("COMMMON","PrjName","Err",chReturn,200,strConfigFileName);
	m_prjName=chReturn;
	GetPrivateProfileString("COMMMON","srcFileSel","Err",chReturn,200,strConfigFileName);
	for(i=0;i<MaxFileType;i++)
	{
		strtmp=chReturn[i];
		m_srcFileSel[i]=atoi(strtmp);
	}
	//m_ftpTransMode = GetPrivateProfileInt("GLOBAL","ftpMode",0,strConfigFileName); 
	//m_ShowMode= GetPrivateProfileInt("GLOBAL","ShowMode",0,strConfigFileName); 
	m_ftpTransMode =1;
	m_ShowMode=1;
	//��ȡĿ�������ĸ���
	m_dstCount = GetPrivateProfileInt("DSTCOMPUTERS","dstCount",0,strConfigFileName); 

	
	//��ȡÿ��Ŀ����������Ϣ
	for(i=0;i<m_dstCount;i++)
	{
		if(i<10)
		{
			sprintf(buffer,"%d",i);
			strtmp="Dst0" ;
			strtmp=strtmp+buffer;
		}
		else
		{
			sprintf(buffer,"%d",i);
			strtmp="Dst" ;
			strtmp=strtmp+buffer;
		}
		//��ȡһ��
		GetPrivateProfileString("DSTCOMPUTERS",strtmp,"Err",chReturn,200,strConfigFileName);
		strline=chReturn;
		//��һ������д��m_config��dstcomputer

		strline.TrimLeft();
		strline.TrimRight();
		strline.Replace("	"," ");
		//��ȡIP�������
		j=strline.Find(" ");
		DstIP=strline.Left(j);
		if(DstIP=="null")
		{
			DstIP="";
		}
		strline=strline.Right(strline.GetLength()-j-1);
		strline.TrimLeft();
		//��ȡ�û���
		j=strline.Find(" ");
		Username=strline.Left(j);
		if(Username=="null")
		{
			Username="";
		}
		strline=strline.Right(strline.GetLength()-j-1);
		strline.TrimLeft();
		//��ȡ����
		j=strline.Find(" ");
		Passwd=strline.Left(j);
		if(Passwd=="null")
		{
			Passwd="";
		}
		strline=strline.Right(strline.GetLength()-j-1);
		strline.TrimLeft();
		//��ȡ�̷�
		j=strline.Find(" ");
		DstDriver=strline.Left(j);
		strline=strline.Right(strline.GetLength()-j-1);
		strline.TrimLeft();
		//��ȡ����
		j=strline.Find(" ");
		DstType=strline.Left(j);
		strline=strline.Right(strline.GetLength()-j-1);
		strline.TrimLeft();
		//��ȡ״̬
		Status=strline;
		//����m_config
		m_dstComputer[i].DstIP=DstIP;
		m_dstComputer[i].Username=Username;
		m_dstComputer[i].Passwd=Passwd;
		m_dstComputer[i].DstDriver=DstDriver;
		m_dstComputer[i].DstType=atoi(DstType);
		m_dstComputer[i].Status=atoi(Status);
	}
	//��ʼ��Դ�ļ����˲���
	m_srcFileList[0][0]="*.def";				
	m_srcFileList[1][0]="*.*";		
	m_srcFileList[2][0]="*.*";			
	m_srcFileList[3][0]="*.*";			
	m_srcFileList[4][0]="*.DBIN";			
	m_srcFileList[4][1]="*.dbin";			
	m_srcFileList[4][2]="*.drbin";			
	m_srcFileList[4][3]="*.mrbin";			
	m_srcFileList[5][0]="*.wav";		


	//��ʼ���ļ����ͣ�0Ϊ�ı���1Ϊ������
	m_fileType[0]=0;						//def
	m_fileType[1]=0;						//gen
	m_fileType[2]=1;						//dat
	m_fileType[3]=1;						//bin
	m_fileType[4]=1;						//dsp
	m_fileType[5]=1;						//wav
					
	
	//��ʼ���ļ��б����
	m_srcFileNum[0]=1;
	m_srcFileNum[1]=1;
	m_srcFileNum[2]=1;
	m_srcFileNum[3]=1;
	m_srcFileNum[4]=4;
	m_srcFileNum[5]=1;
	return true;
}


//����·����Ϣ
bool CTransferConfig::SetConfigDir()
{
	int i;
	//��ʼ��Դ�ļ�Ŀ¼
	m_srcFileDir[0]=m_srcDriver+":\\home\\ems\\h9000\\"+"def";				//�����ļ�
	m_srcFileDir[1]=m_srcDriver+":\\home\\ems\\h9000\\"+"gen";				//�����ı��ļ�
	m_srcFileDir[2]=m_srcDriver+":\\home\\ems\\h9000\\"+"dat";				//�����ļ�
	m_srcFileDir[3]=m_srcDriver+":\\home\\ems\\h9000\\"+"bin";				//ִ���ļ�
	m_srcFileDir[4]=m_srcDriver+":\\home\\ems\\h9000\\"+"dsp";				//�����ļ�
	m_srcFileDir[5]=m_srcDriver+":\\home\\ems\\h9000\\"+"wav";				//�����ļ�
	
	for(i=0;i<m_dstCount;i++)
	{
		
		m_dstComputer[i].PortNum=21;
		//��ʼ��PC��Ŀ��Ŀ¼
		if(m_dstComputer[i].DstType==0)						
		{
		m_dstComputer[i].DstFileDir[0]=m_dstComputer[i].DstDriver+
			"$\\home\\ems\\h9000\\"+"def";				
		m_dstComputer[i].DstFileDir[1]=m_dstComputer[i].DstDriver+
			"$\\home\\ems\\h9000\\"+"gen";				
		m_dstComputer[i].DstFileDir[2]=m_dstComputer[i].DstDriver+
			"$\\home\\ems\\h9000\\"+"dat";				
		m_dstComputer[i].DstFileDir[3]=m_dstComputer[i].DstDriver+
			"$\\home\\ems\\h9000\\"+"bin";				
		m_dstComputer[i].DstFileDir[4]=m_dstComputer[i].DstDriver+
			"$\\home\\ems\\h9000\\"+"dsp";				
		m_dstComputer[i].DstFileDir[5]=m_dstComputer[i].DstDriver+
			"$\\home\\ems\\h9000\\"+"wav";				
		}
		else												//��ʼ��Unix��Ŀ��Ŀ¼
		{
			//����Ŀ¼
			m_dstComputer[i].DstFileDir[0]="/home/ems/h9000/def";			
			m_dstComputer[i].DstFileDir[1]="/home/ems/h9000/gen";			
			m_dstComputer[i].DstFileDir[2]="/home/ems/h9000/dat";			
			m_dstComputer[i].DstFileDir[3]="/home/ems/h9000/bin";			
			m_dstComputer[i].DstFileDir[4]="/home/ems/h9000/dsp";			
			m_dstComputer[i].DstFileDir[5]="/home/ems/h9000/wav";			
		}
	}
	return true;	
}

//���û��ڽ�������ѡ�������������Ϣд���ļ�
bool CTransferConfig::WriteConfigToFile()
{
	int i;
	char buffer[2];
	CString strline,strtmp;
	CString DstIP,DstType,Passwd,Status,Username,DstDriver;	
	CString srcFileSel,srcDriver,srcVersion;
	
	//д�빲����Ϣ
	WritePrivateProfileString("COMMMON","srcDriver",m_srcDriver,strConfigFileName);
	//WritePrivateProfileString("COMMMON","srcVersion",m_srcVersion,strConfigFileName);
	strtmp="";
	for(i=0;i<MaxFileType;i++)
	{
		sprintf(buffer,"%d",m_srcFileSel[i]);
		strtmp=strtmp+buffer;
	}
	WritePrivateProfileString("COMMMON","srcFileSel",strtmp,strConfigFileName);

	
	//д��Ŀ�������ĸ���
	sprintf(buffer,"%d",m_dstCount);
	WritePrivateProfileString("DSTCOMPUTERS","dstCount",buffer,strConfigFileName); 
	
	//д��ÿ��Ŀ����������Ϣ
	for(i=0;i<m_dstCount;i++)
	{
		if(i<10)
		{
			sprintf(buffer,"%d",i);
			strtmp="Dst0" ;
			strtmp=strtmp+buffer;
		}
		else
		{
			sprintf(buffer,"%d",i);
			strtmp="Dst";
			strtmp=strtmp+buffer;
		}
		strline="";
		//���������IP��ַ
		strline=strline+m_dstComputer[i].DstIP;
		//�û���
		m_dstComputer[i].Username.TrimLeft();
		m_dstComputer[i].Username.TrimRight();
		if(m_dstComputer[i].Username.GetLength()>=1)
		{
			strline=strline+"\t\t"+m_dstComputer[i].Username;
		}
		else
		{
			strline=strline+"\t\t"+"null";
		}
		//����
		m_dstComputer[i].Passwd.TrimLeft();
		m_dstComputer[i].Passwd.TrimRight();
		if(m_dstComputer[i].Passwd.GetLength()>=1)
		{
			strline=strline+"\t\t"+m_dstComputer[i].Passwd;
		}
		else
		{
			strline=strline+"\t\t"+"null";
		}
		//�̷�
		m_dstComputer[i].DstDriver.TrimLeft();
		m_dstComputer[i].DstDriver.TrimRight();
		if(m_dstComputer[i].DstDriver.GetLength()>=1)
		{
			strline=strline+"\t\t"+m_dstComputer[i].DstDriver;
		}
		else
		{
			strline=strline+"\t\t"+"null";
		}
		//����
		sprintf(buffer,"%d",m_dstComputer[i].DstType);
		strline=strline+"\t\t"+buffer;
		//״̬
		sprintf(buffer,"%d",m_dstComputer[i].Status);
		strline=strline+"\t\t"+buffer;
		WritePrivateProfileString("DSTCOMPUTERS",strtmp,strline,strConfigFileName); 
	}
	for(i=m_dstCount;i<MaxDstNum;i++)
	{
		if(i<10)
		{
			sprintf(buffer,"%d",i);
			strtmp="Dst0" ;
			strtmp=strtmp+buffer;
		}
		else
		{
			sprintf(buffer,"%d",i);
			strtmp="Dst";
			strtmp=strtmp+buffer;
		}
		strline="";
		WritePrivateProfileString("DSTCOMPUTERS",strtmp,strline,strConfigFileName); 
	}
	return true;
}

//ɾ��ָ�������
bool CTransferConfig::DelDst(int nDst)					
{
	int i;
	if(nDst>m_dstCount-1) 
		return false;
	if(nDst==m_dstCount-1)
	{
		m_dstCount=m_dstCount-1;
		return true;
	}
	for(i=nDst;i<m_dstCount-1;i++)
	{
		m_dstComputer[i]=m_dstComputer[i+1];
	}
	m_dstCount=m_dstCount-1;
	return true;
}

//���û��ڽ�������ѡ���Ŀ������������Ϣд���ļ�
bool CTransferConfig::WriteDstConfigToFile()
{
	return true;
}