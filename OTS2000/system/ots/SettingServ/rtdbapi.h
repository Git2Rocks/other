#ifndef _RTDBAPI_H
#define _RTDBAPI_H
#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA
// <body of your header file>



/********************************************************
//    ��ȡ������
///
*********************************************************/
// ��ȡ��ǰ��Ч��¼��
//szDbName:���ݿ����ƣ�szTabName��������
//������Ч��¼��
extern "C"
{
	int GetRecNum(LPCSTR szDbName,LPCSTR szTabName);
}
// ��ȡ������ά��
//szDbName:���ݿ����ƣ�szTabName��������
//���ر�ά��
extern "C"
{
	int GetTabDimension(LPCSTR szDbName,LPCSTR szTabName);
}
//��ȡ����ֶ���
//szDbName:���ݿ����ƣ�szTabName��������
//���ر��ֶ���
extern "C"
{
	int GetTabFldNum(LPCSTR szDbName,LPCSTR szTabName);
}
//��ȡ����ֶ�����
//nFldNum:�ֶκţ���1��ʼ; szDbName:���ݿ����ƣ�szTabName��������
//szFldName:���ص��ֶ�����
//���غ����Ƿ�ɹ�ִ��
extern "C"
{
	BOOL GetTabFldName(int nFldNum,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName);
}
//��ȡ����ֶ���������
//szDbName:���ݿ����ƣ�szTabName��������
//szFldName:�ֶ�����,cDataType:���ص��ֶ�����
//char:c,short:s,int:i,long:l,float:f,double:d,
//unsigned char:C,unsigned short:S,unsigned int:I,unsigned long:L
//�����ֶ����͵��ֽڳ���
extern "C"
{
	int GetTabFldType(LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char& cDataType);
}

/********************************************************
//    ��ȡ��¼��
///
*********************************************************/
//���ؼ��ֶ�ȡ��¼��(Ҫ��ؼ��������������У�
//szDbName:���ݿ����ƣ�szTabName��������
//scKeyFldName���ؼ���������pBuf����Źؼ�����ֵ
extern "C"
{
	int GetIndex(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,char* pBuf);
}

/********************************************************
//    ��ȡ��ֵ
///
*********************************************************/
//���ؼ��ֶ�ȡ��ֵ
//szDbName:���ݿ����ƣ�szTabName��������
//scKeyFldName���ؼ���������szKeyValue���ؼ�����ֵ
//szFldName��Ҫ��ȡ������pBuf����ֵ�����
//����ֵ��TRUEΪ��ȷִ�У�FALSEΪ�д���
AFX_EXT_CLASS BOOL GetFldValue(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,LPCSTR szKeyValue,LPCSTR szFldName,char* pBuf);

//��ȡ��ֵ(�������κα�
//szDbName:���ݿ����ƣ�
//szFldName��Ҫ��ȡ������pBuf����ֵ�����
//����ֵ��TRUEΪ��ȷִ�У�FALSEΪ�д���
AFX_EXT_CLASS BOOL GetFldValue(LPCSTR szDbName,LPCSTR szFldName,char* pBuf);

//����¼�Ŷ�ȡ��ֵ
//index:��¼�ţ���1��ʼ��
//szDbName:���ݿ����ƣ�szTabName��������
//szFldName��Ҫ��ȡ������pBuf����ֵ�����
//����ֵ��TRUEΪ��ȷִ�У�FALSEΪ�д���
AFX_EXT_CLASS BOOL GetFldValue(int index,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);


/********************************************************
//    �޸���ֵ
///
*********************************************************/
//���ؼ����޸���ֵ
//szDbName:���ݿ����ƣ�szTabName��������
//scKeyFldName���ؼ���������szKeyValue���ؼ�����ֵ
//szFldName��Ҫ�޸�������pBuf����ֵ�����
//����ֵ��TRUEΪ��ȷִ�У�FALSEΪ�д���
AFX_EXT_CLASS BOOL UpdateFldValue(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,LPCSTR szKeyValue,LPCSTR szFldName,char* pBuf);


//�޸���ֵ(�������κα�
//szDbName:���ݿ����ƣ�
//szFldName��Ҫ��ȡ������pBuf����ֵ�����
//����ֵ��TRUEΪ��ȷִ�У�FALSEΪ�д���
AFX_EXT_CLASS BOOL UpdateFldValue(LPCSTR szDbName,LPCSTR szFldName,char* pBuf);


//����¼���޸���ֵ
//index:��¼�ţ���1��ʼ��
//szDbName:���ݿ����ƣ�szTabName��������
//szFldName��Ҫ�޸�������pBuf����ֵ�����
//����ֵ��TRUEΪ��ȷִ�У�FALSEΪ�д���
AFX_EXT_CLASS BOOL UpdateFldValue(int index,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);

/********************************************************
//    ���Ӽ�¼
///
*********************************************************/
//����һ����¼�������ȵ��øú��������󰴼�¼���޸ĸ���ֵ
//szDbName:���ݿ����ƣ�szTabName��������
//����ֵ����ȷ�򷵻ؼ�¼�ţ�����Ϊ-1
extern "C"
{
	int AddOneRecord(LPCSTR szDbName,LPCSTR szTabName);
}

/********************************************************
//    ɾ����¼
///
*********************************************************/
//ɾ�����һ����¼
AFX_EXT_CLASS BOOL DeleteOneRecord(LPCSTR szDbName,LPCSTR szTabName);

//ɾ������һ����¼
//index Ϊ��¼��
AFX_EXT_CLASS BOOL DeleteOneRecord(int index,LPCSTR szDbName,LPCSTR szTabName);

//ɾ�����м�¼
AFX_EXT_CLASS BOOL DeleteAllRecord(LPCSTR szDbName,LPCSTR szTabName);


/***************************************
// ��������ļ��е�ֵ
//
**************************************************/
AFX_EXT_CLASS char* GetCfgValue(const char *VarString);

/***********************************
//���ӷ�����
//
*******************************************/
extern "C"
{
	BOOL ConnectHost();
}
extern "C"
{
	void DisConnectHost();
}
/******************************************
//�û���¼����Ȩ�޶�д
//
************************************************/
//���ڴ��ж�ȡ�û���

AFX_EXT_CLASS	void GetUserName(LPCSTR szUserName);

//д�û������ڴ���

AFX_EXT_CLASS	void UpdateUserName(LPCSTR szUserName);

//���û�Ȩ��

AFX_EXT_CLASS	int GetUserPrior();

//д�û�Ȩ��

AFX_EXT_CLASS	void UpdateUserPrior(int nPrior);

//��ȡ�û�����

AFX_EXT_CLASS	void GetUserPsw(LPCSTR szUserPsw);

//д�û�����

AFX_EXT_CLASS	void UpdateUserPsw(LPCSTR szUserPsw);


/************************************************
//ֱ�ӷ������ݿ��ַ
//
*************************************************/
AFX_EXT_CLASS LPVOID GetRTDBInfoPnt( LPSTR szDbInfoStr);
AFX_EXT_CLASS LPVOID GetRTDBPnt( LPSTR szDbStr);


//2005-6-14
/*************************************
//���ݿ⿽��
//
//
******************************************/
//�ӷ��������ݿ��п������ݵ��������ݿ�
//szDbName Ϊ���ݿ�����
AFX_EXT_CLASS BOOL CopyRTDBFromServer(LPCSTR szDbName);
//���������ݿ����ݿ��������������ݿ���
//szDbName Ϊ���ݿ�����
AFX_EXT_CLASS BOOL CopyRTDBToServer(LPCSTR szDbName);

//��ȡĳ�ֶε����м�¼ֵ
//
AFX_EXT_CLASS BOOL GetFldAllRec(LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);
//дĳ�ֶε����м�¼ֵ
//
AFX_EXT_CLASS BOOL UpdateFldAllRec(LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf,DWORD dwSize);

/*************************************************
//�����Լ��˳�����Ʊ״̬
//
**************************************************/
//�������Ʊ״̬
AFX_EXT_CLASS BOOL IntoOprStatus(BOOL bInit=FALSE);
//�˳�����Ʊ״̬
AFX_EXT_CLASS BOOL OutOprStatus();


/*************************************************
//ͼ��ϵͳ���������ӿں���
//
**************************************************/
//��ȡ������ţ�������ţ����ñ����������򷵻�ֵ<=0
//szVarNameΪ��������
AFX_EXT_CLASS int GetPsgVarIndex(LPCSTR szVarName);
//������Ŷ�ȡ����ֵ
//index������ţ�ivalue��fvalue�� cvalueΪ����ֵ
AFX_EXT_CLASS BOOL GetPsgVarValue(int index,int& ivalue);
AFX_EXT_CLASS BOOL GetPsgVarValue(int index,float& fvalue);
AFX_EXT_CLASS BOOL GetPsgVarValue(int index,char* cvalue);
//��������޸ı���ֵ
//index������ţ�ivalue��fvalue�� cvalueΪ����ֵ
AFX_EXT_CLASS BOOL SetPsgVarValue(int index,int ivalue);
AFX_EXT_CLASS BOOL SetPsgVarValue(int index,float fvalue);
AFX_EXT_CLASS BOOL SetPsgVarValue(int index,char* cvalue);
//���ݱ������ƶ�ȡ����ֵ
//szVarName�������ƣ�ivalue��fvalue�� cvalueΪ����ֵ
AFX_EXT_CLASS BOOL GetPsgVarValue(LPCSTR szVarName,int& ivalue);
AFX_EXT_CLASS BOOL GetPsgVarValue(LPCSTR szVarName,float& fvalue);
AFX_EXT_CLASS BOOL GetPsgVarValue(LPCSTR szVarName,char* cvalue);
//���ݱ��������޸ı���ֵ
//szVarName�������ƣ�ivalue��fvalue�� cvalueΪ����ֵ
AFX_EXT_CLASS BOOL SetPsgVarValue(LPCSTR szVarName,int ivalue);
AFX_EXT_CLASS BOOL SetPsgVarValue(LPCSTR szVarName,float fvalue);
AFX_EXT_CLASS BOOL SetPsgVarValue(LPCSTR szVarName,char* cvalue);

/********************************************
//PSS����������
//
*********************************************/
//����ָ��������
AFX_EXT_CLASS BOOL ConnectHostByName(LPCSTR strHostName);

//��������õ�PSS����������
AFX_EXT_CLASS int GetPssServerNum();

//���PSS������������
//index��1��ʼ��szServerName����PSS�����������ƣ���������ֵΪFALSE��û����ȷ���PSS������������
AFX_EXT_CLASS BOOL GetPssServerName(int index,LPCSTR szServerName);
//���PSS�������ĵ�ǰ״̬������ֵ1��ʾ��PSS������ϵͳ������״̬��0��ʾû������ϵͳ
//index��1��ʼ
AFX_EXT_CLASS int GetPssServerStatus(int index);


////////////////////////////////////////////////////////
//ǰ�汾����
AFX_EXT_CLASS BOOL GetInFldValue(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,LPCSTR szKeyValue,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL GetOutFldValue(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,LPCSTR szKeyValue,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL GetInFldValue(LPCSTR szDbName,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL GetOutFldValue(LPCSTR szDbName,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL GetInFldValue(int index,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL GetOutFldValue(int index,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL UpdateInFldValue(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,LPCSTR szKeyValue,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL UpdateOutFldValue(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,LPCSTR szKeyValue,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL UpdateInFldValue(LPCSTR szDbName,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL UpdateOutFldValue(LPCSTR szDbName,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL UpdateInFldValue(int index,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);
AFX_EXT_CLASS BOOL UpdateOutFldValue(int index,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);
////////////
extern "C"
{
 BOOL GetFldValue1(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,LPCSTR szKeyValue,LPCSTR szFldName,char* pBuf);
}
extern "C"
{
	BOOL GetFldValue2(LPCSTR szDbName,LPCSTR szFldName,char* pBuf);
}
extern "C"
{
	BOOL GetFldValue3(int index,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);
}
extern "C"
{
	BOOL UpdateFldValue1(LPCSTR szDbName,LPCSTR szTabName,LPCSTR scKeyFldName,LPCSTR szKeyValue,LPCSTR szFldName,char* pBuf);
}
extern "C"
{
	BOOL UpdateFldValue2(LPCSTR szDbName,LPCSTR szFldName,char* pBuf);
}
extern "C"
{
	BOOL UpdateFldValue3(int index,LPCSTR szDbName,LPCSTR szTabName,LPCSTR szFldName,char* pBuf);
}
extern "C"
{
	BOOL DeleteOneRecord1(LPCSTR szDbName,LPCSTR szTabName);
}
extern "C"
{
	BOOL DeleteOneRecord2(int index,LPCSTR szDbName,LPCSTR szTabName);
}

extern "C"
{
	BOOL GetCfgValueByName(LPCSTR   szVarString,char* szValue);
}

#undef AFX_DATA
#define AFX_DATA

#endif