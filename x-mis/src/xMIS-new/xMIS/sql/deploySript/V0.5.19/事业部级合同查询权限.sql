--SELECT * FROM xmis.sec_��ɫ ORDER BY ��ɫID

DECLARE @iid INT
SELECT @iid = MAX(��ɫID) + 1 FROM xmis.sec_��ɫ
INSERT INTO xmis.sec_��ɫ
        ( ��ɫID, ��ɫ����, ��ɫ����, �ܼ� )
VALUES  ( @iid, -- ��ɫID - smallint
          '��ҵ������ͬ��ѯԱ', -- ��ɫ���� - char(30)
          '��ѯ����ҵ������ͬ����Ŀ��Ϣ', -- ��ɫ���� - nvarchar(1000)
          -1  -- �ܼ� - smallint
          )


INSERT INTO xmis.sec_��Ա��ɫ        ( ��ԱID, ��ɫID )
SELECT xmis.hr_��Ա.��ԱID, @iid FROM xmis.hr_��Ա,xmis.hr_��Ա���Ź�ϵ��,xmis.org_���Ź������ű�
WHERE xmis.hr_��Ա.��ԱID = xmis.hr_��Ա���Ź�ϵ��.��ԱID AND xmis.hr_��Ա���Ź�ϵ��.����ID  = xmis.org_���Ź������ű�.����ID
AND (xmis.org_���Ź������ű�.������ID = 1 ) AND xmis.hr_��Ա.��ԱID > 0


DECLARE @maxRoleID INT , @maxDataRoleID INT
SELECT @maxRoleID = MAX(ID) FROM xmis.sec_��ɫ�û�����Ȩ�޶����
SELECT @maxDataRoleID = MAX( ����Ȩ��ID ) FROM xmis.sec_����Ȩ�޶����

--SELECT @iid, @maxRoleID, @maxDataRoleID
--13	52	26

INSERT INTO xmis.sec_��ɫ�û�����Ȩ�޶����
        ( ID ,
          ��ɫ����ԱID ,
          ҵ��ģ��ID ,
          ҵ����ģ��ID ,
          ҵ����ID ,
          ����Ȩ��ID ,
          �Ƿ��ǽ�ɫ����
        )
SELECT @maxRoleID+1,@iid,ҵ��ģ��ID,ҵ����ģ��ID,ҵ����ID,����Ȩ��ID,�Ƿ��ǽ�ɫ���� FROM xmis.sec_��ɫ�û�����Ȩ�޶���� WHERE ID = 21

INSERT INTO xmis.sec_����Ȩ�޶����
        ( ����Ȩ��ID ,
          Ȩ��ID ,
          �����ֶ�ID ,
          �����ID ,
          �����ֶ�ֵ ,
          �Ƿ��������ֶ� ,
          sql�Ӿ� ,
          �Ƿ���Ҫ����
        )
SELECT @maxDataRoleID+1,@maxRoleID+1,�����ֶ�ID,�����ID,'self-divID',�Ƿ��������ֶ�,sql�Ӿ�,�Ƿ���Ҫ���� FROM xmis.sec_����Ȩ�޶���� WHERE Ȩ��ID = 21



INSERT INTO xmis.sec_��ɫ�û�����Ȩ�޶����
        ( ID ,
          ��ɫ����ԱID ,
          ҵ��ģ��ID ,
          ҵ����ģ��ID ,
          ҵ����ID ,
          ����Ȩ��ID ,
          �Ƿ��ǽ�ɫ����
        )
SELECT @maxRoleID+2,@iid,ҵ��ģ��ID,ҵ����ģ��ID,ҵ����ID,����Ȩ��ID,�Ƿ��ǽ�ɫ���� FROM xmis.sec_��ɫ�û�����Ȩ�޶���� WHERE ID = 22

INSERT INTO xmis.sec_����Ȩ�޶����
        ( ����Ȩ��ID ,
          Ȩ��ID ,
          �����ֶ�ID ,
          �����ID ,
          �����ֶ�ֵ ,
          �Ƿ��������ֶ� ,
          sql�Ӿ� ,
          �Ƿ���Ҫ����
        )
SELECT @maxDataRoleID+2,@maxRoleID+2,�����ֶ�ID,�����ID,'self-divID',�Ƿ��������ֶ�,sql�Ӿ�,�Ƿ���Ҫ���� FROM xmis.sec_����Ȩ�޶���� WHERE Ȩ��ID = 22


INSERT INTO xmis.sec_��ɫ�û�����Ȩ�޶����
        ( ID ,
          ��ɫ����ԱID ,
          ҵ��ģ��ID ,
          ҵ����ģ��ID ,
          ҵ����ID ,
          ����Ȩ��ID ,
          �Ƿ��ǽ�ɫ����
        )
SELECT @maxRoleID+3,@iid,ҵ��ģ��ID,ҵ����ģ��ID,ҵ����ID,����Ȩ��ID,�Ƿ��ǽ�ɫ���� FROM xmis.sec_��ɫ�û�����Ȩ�޶���� WHERE ID = 34

INSERT INTO xmis.sec_����Ȩ�޶����
        ( ����Ȩ��ID ,
          Ȩ��ID ,
          �����ֶ�ID ,
          �����ID ,
          �����ֶ�ֵ ,
          �Ƿ��������ֶ� ,
          sql�Ӿ� ,
          �Ƿ���Ҫ����
        )
SELECT @maxDataRoleID+3,@maxRoleID+3,�����ֶ�ID,�����ID,'self-divID',�Ƿ��������ֶ�,sql�Ӿ�,�Ƿ���Ҫ���� FROM xmis.sec_����Ȩ�޶���� WHERE Ȩ��ID = 34




--SELECT * FROM xmis.sec_��ɫ�û�����Ȩ�޶���� WHERE ��ɫ����ԱID = 7

--SELECT * FROM xmis.sec_����Ȩ�޶���� WHERE Ȩ��ID IN (SELECT ID FROM xmis.sec_��ɫ�û�����Ȩ�޶���� WHERE ��ɫ����ԱID = 7)







