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
	m_srcFileList[0][0]="*.*";				//���ݿ��ı��ļ�
	m_srcFileList[1][0]="DATABASE.OUT";		//���ݿ������ļ�
	m_srcFileList[2][0]="*.txt";			//�����������ۺϼ����ı�
	m_srcFileList[3][0]="*.dat";			//�����������ۺϼ��������ļ�
	m_srcFileList[4][0]="*.DBIN";			//�����ļ�1
	m_srcFileList[4][1]="*.dbin";			//�����ļ�2
	m_srcFileList[4][2]="*.drbin";			//�����ļ�3
	m_srcFileList[4][3]="*.mrbin";			//�����ļ�4	
	m_srcFileList[5][0]="*.wav";			//�����ļ�
	m_srcFileList[6][0]="*.FAIL";			//�¹�׷���ļ�
	m_srcFileList[7][0]="ems_config.txt";	//��Ŀ�����ļ�

	//��ʼ���ļ����ͣ�0Ϊ�ı���1Ϊ������
	m_fileType[0]=0;						//���ݿ��ı��ļ�
	m_fileType[1]=1;						//���ݿ������ļ�
	m_fileType[2]=0;						//�����������ۺϼ����ı�
	m_fileType[3]=1;						//�����������ۺϼ��������ļ�
	m_fileType[4]=1;						//�����ļ�1\2\3\4
	m_fileType[5]=1;						//�����ļ�
	m_fileType[6]=1;						//�¹�׷���ļ�
	m_fileType[7]=0;						//��Ŀ�����ļ�
	
	//��ʼ���ļ��б����
	m_srcFileNum[0]=1;
	m_srcFileNum[1]=1;
	m_srcFileNum[2]=1;
	m_srcFileNum[3]=1;
	m_srcFileNum[4]=4;
	m_srcFileNum[5]=1;
	m_srcFileNum[6]=1;
	m_srcFileNum[7]=1;
	return true;
}


//����·����Ϣ
bool CTransferConfig::SetConfigDir()
{
	int i;
	//��ʼ��Դ�ļ�Ŀ¼
	m_srcFileDir[0]=m_srcDriver+":\\users\\ems\\project\\"+ m_prjName +"dms\\"+m_srcVersion+"\\gen";				//���ݿ��ı��ļ�
	m_srcFileDir[1]=m_srcDriver+":\\users\\ems\\project\\"+ m_prjName +"dms\\"+m_srcVersion+"\\db";				//���ݿ������ļ�
	m_srcFileDir[2]=m_srcDriver+":\\users\\ems\\project\\"+ m_prjName +"pas\\"+m_srcVersion+"\\DATA";				//�����������ۺϼ����ı�
	m_srcFileDir[3]=m_srcDriver+":\\users\\ems\\project\\"+ m_prjName +"pas\\"+m_srcVersion+"\\DATA";				//�����������ۺϼ��������ļ�
	m_srcFileDir[4]=m_srcDriver+":\\users\\ems\\project\\"+ m_prjName +"oix\\"+m_srcVersion+"\\DSP";				//�����ļ�1��2��3��4
	m_srcFileDir[5]=m_srcDriver+":\\users\\ems\\project\\"+ m_prjName +"dps\\"+m_srcVersion+"\\AUD";				//�����ļ�
	m_srcFileDir[6]=m_srcDriver+":\\users\\ems\\project\\"+ m_prjName +"pas\\"+m_srcVersion+"\\DATA";	
	m_srcFileDir[7]=m_srcDriver+":\\users\\ems\\project\\"+ m_prjName +"cmm\\"+m_srcVersion+"\\def";	
	//�¹�׷���ļ�
	for(i=0;i<m_dstCount;i++)
	{
		
		m_dstComputer[i].PortNum=21;
		//��ʼ��PC��Ŀ��Ŀ¼
		if(m_dstComputer[i].DstType==0)						
		{
		m_dstComputer[i].DstFileDir[0]=m_dstComputer[i].DstDriver+
			"$\\users\\ems\\project\\"+ m_prjName +"dms\\"+m_srcVersion+"\\gen";				//���ݿ��ı��ļ�
		m_dstComputer[i].DstFileDir[1]=m_dstComputer[i].DstDriver+
			"$\\users\\ems\\project\\"+ m_prjName +"dms\\"+m_srcVersion+"\\db";				//���ݿ������ļ�
		m_dstComputer[i].DstFileDir[2]=m_dstComputer[i].DstDriver+
			"$\\users\\ems\\project\\"+ m_prjName +"pas\\"+m_srcVersion+"\\DATA";				//�����������ۺϼ����ı�
		m_dstComputer[i].DstFileDir[3]=m_dstComputer[i].DstDriver+
			"$\\users\\ems\\project\\"+ m_prjName +"pas\\"+m_srcVersion+"\\DATA";				//�����������ۺϼ��������ļ�
		m_dstComputer[i].DstFileDir[4]=m_dstComputer[i].DstDriver+
			"$\\users\\ems\\project\\"+ m_prjName +"oix\\"+m_srcVersion+"\\DSP";				//�����ļ�1
		m_dstComputer[i].DstFileDir[5]=m_dstComputer[i].DstDriver+
			"$\\users\\ems\\project\\"+ m_prjName +"dps\\"+m_srcVersion+"\\AUD";				//�����ļ�
		m_dstComputer[i].DstFileDir[6]=m_dstComputer[i].DstDriver+
			"$\\users\\ems\\project\\"+ m_prjName +"pas\\"+m_srcVersion+"\\DATA";				//�¹�׷���ļ�
		m_dstComputer[i].DstFileDir[7]=m_dstComputer[i].DstDriver+
			"$\\users\\ems\\project\\"+ m_prjName +"cmm\\"+m_srcVersion+"\\def";				//��Ŀ�����ļ�
		}
		else												//��ʼ��Unix��Ŀ��Ŀ¼
		{
		//����Ŀ¼
		m_dstComputer[i].DstFileDir[0]="/DMSGEN";			//���ݿ��ı��ļ�
		m_dstComputer[i].DstFileDir[1]="/DMSDB";			//���ݿ������ļ�
		m_dstComputer[i].DstFileDir[2]="/PASDATA";			//�����������ۺϼ����ı�
		m_dstComputer[i].DstFileDir[3]="/PASDATA";			//�����������ۺϼ��������ļ�
		m_dstComputer[i].DstFileDir[4]="/OIXDSP";			//�����ļ�1��2��3��4
		m_dstComputer[i].DstFileDir[5]="/AUD";				//�����ļ�
		m_dstComputer[i].DstFileDir[6]="/PASDATA";			//�¹�׷���ļ�
		m_dstComputer[i].DstFileDir[7]="/PRJDEF";			//��Ŀ�����ļ�
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
	WritePrivateProfileString("COMMMON","srcVersion",m_srcVersion,strConfigFileName);
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
	for(i=m_dstCount;i<11;i++)
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