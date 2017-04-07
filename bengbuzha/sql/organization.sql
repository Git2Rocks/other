USE [backup]
CREATE TABLE #dept(SID INT IDENTITY(1,1), NAME NVARCHAR(40))
INSERT INTO #dept
        ( NAME )
SELECT DISTINCT ��λ FROM dbo.��˾���� WHERE ��λ NOT IN ('���ϵͳ��ҵ��')

CREATE TABLE #emp(SID INT IDENTITY(1,1), NAME NVARCHAR(40), dept_name NVARCHAR(40), sex NVARCHAR(2), post NVARCHAR(20))
INSERT INTO #emp
        ( NAME, dept_name,sex,post )
SELECT ����,��λ,�Ա�,ְλ���� FROM dbo.��˾���� WHERE ��λ NOT IN ('ˮ���Զ�����ҵ��', '���ϵͳ��ҵ��')




DECLARE @maxDeptID INT
SELECT @maxDeptID = MAX(����ID) FROM xmis.xmis.org_����

DECLARE @maxEmpID INT
SELECT @maxEmpID = MAX(xmis.xmis.hr_��Ա.��ԱID) FROM xmis.xmis.hr_��Ա

--��Ա
INSERT INTO xmis.xmis.hr_��Ա
        ( ��ԱID ,
          ���� ,
          ���� ,
          �Ա�ID ,
          ְ�� ,
          �޸���ID ,
          �޸�ʱ�� ,
          ���� ,
          ��¼�� 
        )
SELECT @maxEmpID+ SID, SUBSTRING(#emp.NAME,2,LEN(NAME)-1), SUBSTRING(#emp.NAME,0,2),CASE WHEN sex = '��' THEN 1 ELSE 0 END,
post,-1,GETDATE(),'000000',NAME
FROM #emp


--����
INSERT INTO xmis.xmis.org_����
        ( ����ID ,
          �������� ,
          ������д 
        )
SELECT   @maxDeptID + sid , -- ����ID - int
          name , -- �������� - varchar(100)
          name  -- ������д - varchar(40)
         FROM #dept

--��Ա���Ź�ϵ
INSERT INTO xmis.xmis.hr_��Ա���Ź�ϵ��
        ( ��ԱID, ����ID, �Ƿ��ְ, ID )
SELECT @maxEmpID + #emp.SID, @maxDeptID + #dept.SID, 1,@maxEmpID + #emp.SID+'-' + @maxDeptID + #dept.SID FROM #dept,#emp WHERE dept_name = #dept.NAME 

--���Ź�����˾
INSERT INTO xmis.xmis.org_���Ź�����˾��
        ( ��˾ID, ����ID, �Ƿ�ֱ�� )
SELECT  1, @maxDeptID + sid ,1 FROM #dept

--��Ա��ɫ
INSERT INTO xmis.xmis.sec_��Ա��ɫ
        ( ��ԱID, ��ɫID )
SELECT @maxEmpID + SID, 5
FROM #emp



