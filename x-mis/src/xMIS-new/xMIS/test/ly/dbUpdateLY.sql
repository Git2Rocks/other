     SELECT *  FROM xmis.add_��ַ
 WHERE ��ַID  LIKE 'x-id-generator%'  
  
  SELECT * FROM xmis.hr_��Ա 
   WHERE �칫��ַID  LIKE 'x-id-generator%'  
   
--Ϊ��ˮ�Ƽ�����Ա ���Ĭ�ϵİ칫��ַID
 update xmis.hr_��Ա set �칫��ַID='x-id-generator-'+CONVERT(VARCHAR(50),��ԱID) WHERE �칫��ַID IS null 
 	and   ��ԱID IN ( 
 	SELECT ��ԱID FROM xmis.hr_��Ա���Ź�ϵ�� WHERE ����ID IN(
  SELECT ����ID FROM xmis.org_���Ź�����˾�� WHERE ��˾ID=1) )
  
 --���ĵ�ַID����ϸ��ַ
 INSERT INTO xmis.add_��ַ
        ( ��ַID ,
          ��ϸ��ַ 
        )
        SELECT �칫��ַID,�칫��ַ FROM xmis.hr_��Ա WHERE �칫��ַID LIKE 'x-id-generator%'  
        
 --���ĳ���ID�����ء��ʱ�
 UPDATE xmis.add_��ַ 
 SET ����ID='1',
 ����='������',�ʱ�=100038 WHERE ��ַID  LIKE 'x-id-generator%' 
 
 
 
 
  --�������ֲ�ѯ ĳ����˾��ĳ��
  SELECT RTRIM(a.����)+RTRIM(a.����) NAME ,a.��ԱID FROM
  xmis.hr_��Ա a,
  xmis.hr_��Ա���Ź�ϵ�� b,
  xmis.org_���Ź�����˾�� c 
  WHERE a.��ԱID=b.��ԱID 
  AND b.����ID=c.����ID 
  AND c.��˾ID=?
 

 --������ԱID ��ѯ ����Ա�ڵ��·�� ���ϼ���ID
SELECT ��˾ID,a.����ID,a.������ID,a.��ԱID
  FROM xmis.org_���Ź�����˾��
  left join (
  SELECT ��ԱID  ,hd.����ID ,
  case when dd.������ID IS null then hd.����ID else dd.������ID end as ������ID
  FROM xmis.hr_��Ա���Ź�ϵ�� as hd
  left join xmis.org_���Ź������ű� dd on  hd.����ID = dd.����ID ) a 
  on a.������ID = xmis.org_���Ź�����˾��.����ID
  where �Ƿ�ֱ�� = 1  AND ��ԱID = ?
  
 --���ݲ���ID ��ѯ �˲��Žڵ��·�� ���ϼ���ID  
 SELECT ��˾ID
      ,case when dd.������ID IS null then dc.����ID else dd.������ID end as ��ҵ��ID
      ,dc.����ID
  FROM xmis.org_���Ź�����˾�� dc
  left join xmis.org_���Ź������ű� dd on dc.����ID = dd.����ID and dc.�Ƿ�ֱ�� = 0
  WHERE dc.����ID = 518
  
 -- ���ϡ����ݲ���ID ��ѯ �˲��Žڵ��·�� ���ϼ���ID ��ǰ
 select c.��˾ID,a.��ҵ��ID,a.����ID from xmis.org_���Ź�����˾�� c
  join (
  select d.����ID
  ,case when dd.������ID IS null then d.����ID else dd.������ID end as ��ҵ��ID
  from xmis.org_���� as d 
  left join xmis.org_���Ź������ű� dd on d.����ID = dd.����ID) as a
  on c.����ID = a.��ҵ��ID and c.�Ƿ�ֱ�� = 1
  where a.����ID = 1
  
  
  
    UPDATE xmis.HR_��Ա set ����޸�����=rtrim(�޸�ʱ��) where ����޸����� IS NULL AND ��ԱID in (
  SELECT ��ԱID FROM xmis.hr_��Ա���Ź�ϵ�� WHERE ����ID IN(
  SELECT ����ID FROM xmis.org_���Ź�����˾�� WHERE ��˾ID=1)
  )
  
  UPDATE xmis.HR_��Ա set ����޸���ID=rtrim(�޸���ID) where ����޸���ID IS NULL AND ��ԱID in (
  SELECT ��ԱID FROM xmis.hr_��Ա���Ź�ϵ�� WHERE ����ID IN(
  SELECT ����ID FROM xmis.org_���Ź�����˾�� WHERE ��˾ID=1)
  )
  
  
    UPDATE xmis.sec_��ɫ SET ȫ��Ա����־=1 WHERE ��ɫID NOT  IN (5,9)
    UPDATE xmis.sec_��ɫ SET ȫ��Ա����־=0 WHERE ��ɫID   IN (5,9)
    
    
    UPDATE xmis.sec_ҵ����ģ��� SET ҵ����ģ��url='crmMaint.do?method=getCompanyInfo&companyID=1&tab=1' 
    WHERE ҵ����ģ��ID=10
  
    
    
-- 2012-12-3   
     
--��ɫ�����ӵ����е�����       
UPDATE xmis.sec_��ɫ SET ��ʾ��־=0 WHERE ��ɫID IN (1,6,10,12,15,16,105,106,107,108)
   UPDATE xmis.sec_��ɫ SET ��ʾ��־=1 WHERE ��ɫID not IN (1,6,10,12,15,16,105,106,107,108)
  
  
  UPDATE xmis.sec_��ɫ SET ȫ��Ա����־=1 WHERE ��ɫID IN (5,9)
	UPDATE xmis.sec_��ɫ SET ȫ��Ա����־=0 WHERE ��ɫID NOT IN (5,9)
		
		UPDATE xmis.sec_��ɫ SET ����=1 WHERE ��ɫID=2
		UPDATE xmis.sec_��ɫ SET ����=200 WHERE ��ɫID=3
		UPDATE xmis.sec_��ɫ SET ����=202 WHERE ��ɫID=4
		UPDATE xmis.sec_��ɫ SET ����=300 WHERE ��ɫID=5

		UPDATE xmis.sec_��ɫ SET ����=101 WHERE ��ɫID=7
		UPDATE xmis.sec_��ɫ SET ����=203 WHERE ��ɫID=8
		UPDATE xmis.sec_��ɫ SET ����=201 WHERE ��ɫID=11
		UPDATE xmis.sec_��ɫ SET ����=100 WHERE ��ɫID=14   
-- �޸Ľ�ɫIDΪ13��ˮ���Զ�����ҵ������Ա��Ӧ�� [���ż����еĽ�ɫ��־]=1 
  UPDATE xmis.sec_��Ա��ɫ SET [���ż����еĽ�ɫ��־]=1 
  
  WHERE ��ɫID=13 AND ��ԱID IN (
   SELECT    p.��ԱID  
        
 FROM   
        xmis.sec_��Ա��ɫ AS b ,
        xmis.hr_��Ա AS p ,
        XMIS.hr_��Ա���Ź�ϵ�� pd ,
        XMIS.ORG_���Ź�����˾�� c ,
        xmis.org_���� d
 WHERE  
         b.��ԱID = p.��ԱID
        AND p.��ԱID > 0
      
        AND pd.����ID = c.����ID
        AND d.����ID = pd.����ID 
        AND c.��˾ID = 1
        AND c.�Ƿ�ֱ�� = 1
        AND P.��ԱID = PD.��ԱID
        AND  b.��ɫID=13
         AND d.����ID = 2
       )   
 
       
  -- �޸Ľ�ɫIDΪ13�������ҵ������Ա��Ӧ�� [���ż����еĽ�ɫ��־]=1 
  UPDATE xmis.sec_��Ա��ɫ SET  ���ż����еĽ�ɫ��־ =1 
  
  WHERE ��ɫID=13 AND ��ԱID IN (
   SELECT     
        p.��ԱID  
        
 FROM   xmis.sec_��ɫ AS a ,
        xmis.sec_��Ա��ɫ AS b ,
        xmis.hr_��Ա AS p ,
        XMIS.hr_��Ա���Ź�ϵ�� pd ,
        XMIS.ORG_���Ź������ű� dd ,
        xmis.xmis.org_���Ź�����˾�� c ,
        xmis.org_���� d
 WHERE  a.��ɫID = b.��ɫID
        AND b.��ԱID = p.��ԱID
        AND a.��ʾ��־ = 1
        AND a.ȫ��Ա����־ = 0
        AND pd.����ID = dd.����ID
        AND dd.����ID = pd.����ID
        AND dd.������ID = d.����ID
        AND p.��ԱID = PD.��ԱID
        AND p.��ԱID > 0
        AND dd.������ID = 1
        AND dd.������ID = c.����ID
        AND  b.��ɫID=13
       )
 --
   INSERT INTO xmis.sec_ҵ����ģ���
          ( ҵ����ģ��ID ,
            ҵ����ģ������ ,
            ҵ����ģ��url ,
            ҵ����ģ������ ,
            ҵ����ģ��ͼ��˵�� ,
            ҵ����ģ���ʶ ,
            �ύ�� ,
            �ύʱ�� ,
            �ύ״̬ ,
            ��ע ,
            ״̬�����¼ ,
            ����޸����� ,
            ����޸���ID
          )
  VALUES  ( 40 , -- ҵ����ģ��ID - int
            '��ɫ����' , -- ҵ����ģ������ - nvarchar(50)
            'securityMaint.do?method=getSecurityInfoList' , -- ҵ����ģ��url - nvarchar(200)
            '��ɫ����' , -- ҵ����ģ������ - nvarchar(50)
            '' , -- ҵ����ģ��ͼ��˵�� - nvarchar(50)
            '' , -- ҵ����ģ���ʶ - nvarchar(50)
            '' , -- �ύ�� - int
            2012-12-04 , -- �ύʱ�� - smalldatetime
            0 , -- �ύ״̬ - int
            N'' , -- ��ע - nvarchar(200)
            N'' , -- ״̬�����¼ - nvarchar(200)
            '2012-12-04 00:10:22' , -- ����޸����� - datetime
            0  -- ����޸���ID - int
          )  
          
 ---         
          
   INSERT INTO xmis.sec_ҵ��ģ���Ӧ��
          ( ҵ��ģ��ID ,
            ҵ����ģ��ID ,
            ҵ����ģ������˳�� ,
            ����޸����� ,
            ����޸���ID
          )
  VALUES  ( 7 , -- ҵ��ģ��ID - int
            40 , -- ҵ����ģ��ID - int
            2 , -- ҵ����ģ������˳�� - int
            '2012-12-04 00:37:21' , -- ����޸����� - datetime
            0  -- ����޸���ID - int
          )