--1) org_��˾
INSERT INTO xmis.org_ҵ���ϵ
        ( ҵ���ϵID, ��ϵ����, ��ϵ���� )
VALUES  ( -1, -- ҵ���ϵID - smallint
          '', -- ��ϵ���� - char(50)
          ''  -- ��ϵ���� - char(10)
          )

insert into xmis.org_��˾(��˾ID,��˾����,������д,�޸�ʱ��,�޸���ID,ҵ���ϵID) 
values(1,'������ˮ��ˮ��Ƽ��������޹�˾','��ˮ�Ƽ�',CURRENT_TIMESTAMP,-1,-1)

--2) org_����
ALTER TABLE xmis.org_���� ALTER COLUMN �������� VARCHAR(100)
ALTER TABLE xmis.org_���� ALTER COLUMN ������д VARCHAR(40)

INSERT INTO xmis.org_����
        ( ����ID ,
          �������� ,
          ������д ,
          �绰1 ,
          ����1 ,
          �绰2 ,
          ����2 ,
          ������ID ,
          ��ϵ��ID ,
          ��ַ ,
          ���� ,
          ���� ,
          ��ַ
        )
VALUES  ( 1 , -- ����ID - LongID
          '�����ҵ��' , -- �������� - char(10)
          '�����ҵ��' , -- ������д - char(10)
          NULL , -- �绰1 - Tel
          NULL , -- ����1 - Tel
          NULL , -- �绰2 - Tel
          NULL , -- ����2 - Tel
          NULL , -- ������ID - LongID
          NULL , -- ��ϵ��ID - LongID
          NULL , -- ��ַ - LongString
          NULL , -- ���� - LongString
          NULL , -- ���� - ShortID
          NULL  -- ��ַ - LongString
        )

INSERT INTO xmis.org_����
        ( ����ID ,
          �������� ,
          ������д ,
          �绰1 ,
          ����1 ,
          �绰2 ,
          ����2 ,
          ������ID ,
          ��ϵ��ID ,
          ��ַ ,
          ���� ,
          ���� ,
          ��ַ
        )
VALUES  ( 2 , -- ����ID - LongID
          '����һ��' , -- �������� - char(10)
          '' , -- ������д - char(10)
          NULL , -- �绰1 - Tel
          NULL , -- ����1 - Tel
          NULL , -- �绰2 - Tel
          NULL , -- ����2 - Tel
          NULL , -- ������ID - LongID
          NULL , -- ��ϵ��ID - LongID
          NULL , -- ��ַ - LongString
          NULL , -- ���� - LongString
          NULL , -- ���� - ShortID
          NULL  -- ��ַ - LongString
        )
        
INSERT INTO xmis.org_����
        ( ����ID ,
          �������� ,
          ������д ,
          �绰1 ,
          ����1 ,
          �绰2 ,
          ����2 ,
          ������ID ,
          ��ϵ��ID ,
          ��ַ ,
          ���� ,
          ���� ,
          ��ַ
        )
VALUES  ( 3 , -- ����ID - LongID
          '���̶���' , -- �������� - char(10)
          '' , -- ������д - char(10)
          NULL , -- �绰1 - Tel
          NULL , -- ����1 - Tel
          NULL , -- �绰2 - Tel
          NULL , -- ����2 - Tel
          NULL , -- ������ID - LongID
          NULL , -- ��ϵ��ID - LongID
          NULL , -- ��ַ - LongString
          NULL , -- ���� - LongString
          NULL , -- ���� - ShortID
          NULL  -- ��ַ - LongString
        )        

INSERT INTO xmis.org_����
        ( ����ID ,
          �������� ,
          ������д ,
          �绰1 ,
          ����1 ,
          �绰2 ,
          ����2 ,
          ������ID ,
          ��ϵ��ID ,
          ��ַ ,
          ���� ,
          ���� ,
          ��ַ
        )
VALUES  ( 4 , -- ����ID - LongID
          '��������' , -- �������� - char(10)
          '' , -- ������д - char(10)
          NULL , -- �绰1 - Tel
          NULL , -- ����1 - Tel
          NULL , -- �绰2 - Tel
          NULL , -- ����2 - Tel
          NULL , -- ������ID - LongID
          NULL , -- ��ϵ��ID - LongID
          NULL , -- ��ַ - LongString
          NULL , -- ���� - LongString
          NULL , -- ���� - ShortID
          NULL  -- ��ַ - LongString
        )        

INSERT INTO xmis.org_����
        ( ����ID ,
          �������� ,
          ������д ,
          �绰1 ,
          ����1 ,
          �绰2 ,
          ����2 ,
          ������ID ,
          ��ϵ��ID ,
          ��ַ ,
          ���� ,
          ���� ,
          ��ַ
        )
VALUES  ( 5 , -- ����ID - LongID
          '�����Ĳ�' , -- �������� - char(10)
          '' , -- ������д - char(10)
          NULL , -- �绰1 - Tel
          NULL , -- ����1 - Tel
          NULL , -- �绰2 - Tel
          NULL , -- ����2 - Tel
          NULL , -- ������ID - LongID
          NULL , -- ��ϵ��ID - LongID
          NULL , -- ��ַ - LongString
          NULL , -- ���� - LongString
          NULL , -- ���� - ShortID
          NULL  -- ��ַ - LongString
        )        

INSERT INTO xmis.org_����
        ( ����ID ,
          �������� ,
          ������д ,
          �绰1 ,
          ����1 ,
          �绰2 ,
          ����2 ,
          ������ID ,
          ��ϵ��ID ,
          ��ַ ,
          ���� ,
          ���� ,
          ��ַ
        )
VALUES  ( 6 , -- ����ID - LongID
          '������' , -- �������� - char(10)
          '' , -- ������д - char(10)
          NULL , -- �绰1 - Tel
          NULL , -- ����1 - Tel
          NULL , -- �绰2 - Tel
          NULL , -- ����2 - Tel
          NULL , -- ������ID - LongID
          NULL , -- ��ϵ��ID - LongID
          NULL , -- ��ַ - LongString
          NULL , -- ���� - LongString
          NULL , -- ���� - ShortID
          NULL  -- ��ַ - LongString
        )        

INSERT INTO xmis.org_����
        ( ����ID ,
          �������� ,
          ������д ,
          �绰1 ,
          ����1 ,
          �绰2 ,
          ����2 ,
          ������ID ,
          ��ϵ��ID ,
          ��ַ ,
          ���� ,
          ���� ,
          ��ַ
        )
VALUES  ( 7 , -- ����ID - LongID
          '��Ŀ����' , -- �������� - char(10)
          '' , -- ������д - char(10)
          NULL , -- �绰1 - Tel
          NULL , -- ����1 - Tel
          NULL , -- �绰2 - Tel
          NULL , -- ����2 - Tel
          NULL , -- ������ID - LongID
          NULL , -- ��ϵ��ID - LongID
          NULL , -- ��ַ - LongString
          NULL , -- ���� - LongString
          NULL , -- ���� - ShortID
          NULL  -- ��ַ - LongString
        )        

--3��org_���Ź�����˾��
INSERT INTO xmis.org_���Ź�����˾��
        ( ��˾ID, ����ID, �Ƿ�ֱ�� )
VALUES  ( 1, -- ��˾ID - LongID
          1, -- ����ID - LongID
          1  -- �Ƿ�ֱ�� - bit
          )
          
INSERT INTO xmis.org_���Ź�����˾��
        ( ��˾ID, ����ID, �Ƿ�ֱ�� )
VALUES  ( 1, -- ��˾ID - LongID
          2, -- ����ID - LongID
          0  -- �Ƿ�ֱ�� - bit
          )          
          
INSERT INTO xmis.org_���Ź�����˾��
        ( ��˾ID, ����ID, �Ƿ�ֱ�� )
VALUES  ( 1, -- ��˾ID - LongID
          3, -- ����ID - LongID
          0  -- �Ƿ�ֱ�� - bit
          )

INSERT INTO xmis.org_���Ź�����˾��
        ( ��˾ID, ����ID, �Ƿ�ֱ�� )
VALUES  ( 1, -- ��˾ID - LongID
          4, -- ����ID - LongID
          0  -- �Ƿ�ֱ�� - bit
          )
INSERT INTO xmis.org_���Ź�����˾��
        ( ��˾ID, ����ID, �Ƿ�ֱ�� )
VALUES  ( 1, -- ��˾ID - LongID
          5, -- ����ID - LongID
          0  -- �Ƿ�ֱ�� - bit
          )
                    
INSERT INTO xmis.org_���Ź�����˾��
        ( ��˾ID, ����ID, �Ƿ�ֱ�� )
VALUES  ( 1, -- ��˾ID - LongID
          6, -- ����ID - LongID
          0  -- �Ƿ�ֱ�� - bit
          )
           
INSERT INTO xmis.org_���Ź�����˾��
        ( ��˾ID, ����ID, �Ƿ�ֱ�� )
VALUES  ( 1, -- ��˾ID - LongID
          7, -- ����ID - LongID
          0  -- �Ƿ�ֱ�� - bit
          )
          
--4)xmis.org_���Ź������ű�
INSERT INTO xmis.org_���Ź������ű�
        ( ����ID, ������ID )
VALUES  ( 2, -- ����ID - LongID
          1  -- ������ID - LongID
          )
INSERT INTO xmis.org_���Ź������ű�
        ( ����ID, ������ID )
VALUES  ( 3, -- ����ID - LongID
          1  -- ������ID - LongID
          )
INSERT INTO xmis.org_���Ź������ű�
        ( ����ID, ������ID )
VALUES  ( 4, -- ����ID - LongID
          1  -- ������ID - LongID
          )
INSERT INTO xmis.org_���Ź������ű�
        ( ����ID, ������ID )
VALUES  ( 5, -- ����ID - LongID
          1  -- ������ID - LongID
          )
INSERT INTO xmis.org_���Ź������ű�
        ( ����ID, ������ID )
VALUES  ( 6, -- ����ID - LongID
          1  -- ������ID - LongID
          )
INSERT INTO xmis.org_���Ź������ű�
        ( ����ID, ������ID )
VALUES  ( 7, -- ����ID - LongID
          1  -- ������ID - LongID
          )
                    
                    
-- 5)xmis.hr_��Ա
INSERT INTO xmis.sys_�Ա�
        ( �Ա�ID, �Ա� )
VALUES  ( 1, -- �Ա�ID - ShortID
          '��'  -- �Ա� - char(10)
          )
INSERT INTO xmis.sys_�Ա�
        ( �Ա�ID, �Ա� )
VALUES  ( 0, -- �Ա�ID - ShortID
          'Ů'  -- �Ա� - char(10)
          )          
ALTER TABLE xmis.hr_��Ա DROP COLUMN �ǳ�
ALTER TABLE xmis.hr_��Ա ALTER COLUMN �����ļ� IMAGE
ALTER TABLE xmis.hr_��Ա ALTER COLUMN ��Ƭ IMAGE
ALTER TABLE xmis.hr_��Ա ADD ��¼�� VARCHAR(20)

ALTER TABLE xmis.hr_��Ա��ʷ�� DROP COLUMN �ǳ�
ALTER TABLE xmis.hr_��Ա��ʷ�� ADD ��¼�� VARCHAR(20)
ALTER TABLE xmis.hr_��Ա��ʷ�� ALTER COLUMN ��Ƭ IMAGE
ALTER TABLE xmis.hr_��Ա��ʷ�� ADD �����ļ� IMAGE

INSERT INTO xmis.hr_��Ա
        ( ��ԱID ,
          ���� ,
          ���� ,
          �Ա�ID ,
          �칫��ַID ,
          ��ͥ��ַ ,
          ְ�� ,
          �ƶ��绰 ,
          ��λ�绰 ,
          ��λ�ֻ� ,
          סլ�绰 ,
          ������� ,
          �����ʼ� ,
          ��ż���� ,
          �������� ,
          ���� ,
          ѧ��ID ,
          ��ע ,
          ��ҳ ,
          ������òID ,
          ���� ,
          �س� ,
          ��Ƭ ,
          ����״̬ID ,
          �޸���ID ,
          �޸�ʱ�� ,
          ���� ,
          ���� ,
          �����ļ� ,
          ��¼��
        )
VALUES  ( -1 , -- ��ԱID - LongID
          'For �����ҵ��' , -- ���� - ShortString
          'Administrator' , -- ���� - ShortString
          1 , -- �Ա�ID - ShortID
          NULL , -- �칫��ַID - ShortID
          NULL , -- ��ͥ��ַ - VeryLongString
          NULL , -- ְ�� - ShortString
          NULL , -- �ƶ��绰 - Tel
          NULL , -- ��λ�绰 - Tel
          NULL , -- ��λ�ֻ� - Tel
          NULL , -- סլ�绰 - Tel
          NULL , -- ������� - Tel
          NULL , -- �����ʼ� - LongString
          '' , -- ��ż���� - varchar(50)
          '' , -- �������� - varchar(255)
          '' , -- ���� - varchar(50)
          NULL , -- ѧ��ID - ShortID
          NULL , -- ��ע - VeryLongString
          NULL , -- ��ҳ - LongString
          NULL , -- ������òID - ShortID
          NULL , -- ���� - VeryLongString
          NULL , -- �س� - VeryLongString
          NULL , -- ��Ƭ - binary
          NULL , -- ����״̬ID - AutoNo_Small
          -1 , -- �޸���ID - LongID
          CURRENT_TIMESTAMP , -- �޸�ʱ�� - smalldatetime
          'admin' , -- ���� - LongString
          NULL , -- ���� - bit
          NULL , -- �����ļ� - binary
          'JK-admin'  -- ��¼�� - varchar(20)
        )                    
        
INSERT INTO xmis.hr_��Ա
        ( ��ԱID ,
          ���� ,
          ���� ,
          �Ա�ID ,
          �칫��ַID ,
          ��ͥ��ַ ,
          ְ�� ,
          �ƶ��绰 ,
          ��λ�绰 ,
          ��λ�ֻ� ,
          סլ�绰 ,
          ������� ,
          �����ʼ� ,
          ��ż���� ,
          �������� ,
          ���� ,
          ѧ��ID ,
          ��ע ,
          ��ҳ ,
          ������òID ,
          ���� ,
          �س� ,
          ��Ƭ ,
          ����״̬ID ,
          �޸���ID ,
          �޸�ʱ�� ,
          ���� ,
          ���� ,
          �����ļ� ,
          ��¼��
        )
VALUES  ( 1 , -- ��ԱID - LongID
          '��' , -- ���� - ShortString
          '��' , -- ���� - ShortString
          1 , -- �Ա�ID - ShortID
          NULL , -- �칫��ַID - ShortID
          NULL , -- ��ͥ��ַ - VeryLongString
          NULL , -- ְ�� - ShortString
          NULL , -- �ƶ��绰 - Tel
          NULL , -- ��λ�绰 - Tel
          NULL , -- ��λ�ֻ� - Tel
          NULL , -- סլ�绰 - Tel
          NULL , -- ������� - Tel
          NULL , -- �����ʼ� - LongString
          '' , -- ��ż���� - varchar(50)
          '' , -- �������� - varchar(255)
          '' , -- ���� - varchar(50)
          NULL , -- ѧ��ID - ShortID
          NULL , -- ��ע - VeryLongString
          NULL , -- ��ҳ - LongString
          NULL , -- ������òID - ShortID
          NULL , -- ���� - VeryLongString
          NULL , -- �س� - VeryLongString
          NULL , -- ��Ƭ - binary
          NULL , -- ����״̬ID - AutoNo_Small
          -1 , -- �޸���ID - LongID
          CURRENT_TIMESTAMP , -- �޸�ʱ�� - smalldatetime
          'wzy' , -- ���� - LongString
          NULL , -- ���� - bit
          NULL , -- �����ļ� - binary
          'wzy'  -- ��¼�� - varchar(20)
        )        
        
INSERT INTO xmis.hr_��Ա
        ( ��ԱID ,
          ���� ,
          ���� ,
          �Ա�ID ,
          �칫��ַID ,
          ��ͥ��ַ ,
          ְ�� ,
          �ƶ��绰 ,
          ��λ�绰 ,
          ��λ�ֻ� ,
          סլ�绰 ,
          ������� ,
          �����ʼ� ,
          ��ż���� ,
          �������� ,
          ���� ,
          ѧ��ID ,
          ��ע ,
          ��ҳ ,
          ������òID ,
          ���� ,
          �س� ,
          ��Ƭ ,
          ����״̬ID ,
          �޸���ID ,
          �޸�ʱ�� ,
          ���� ,
          ���� ,
          �����ļ� ,
          ��¼��
        )
VALUES  ( 2 , -- ��ԱID - LongID
          '��' , -- ���� - ShortString
          '��' , -- ���� - ShortString
          1 , -- �Ա�ID - ShortID
          NULL , -- �칫��ַID - ShortID
          NULL , -- ��ͥ��ַ - VeryLongString
          NULL , -- ְ�� - ShortString
          NULL , -- �ƶ��绰 - Tel
          NULL , -- ��λ�绰 - Tel
          NULL , -- ��λ�ֻ� - Tel
          NULL , -- סլ�绰 - Tel
          NULL , -- ������� - Tel
          NULL , -- �����ʼ� - LongString
          '' , -- ��ż���� - varchar(50)
          '' , -- �������� - varchar(255)
          '' , -- ���� - varchar(50)
          NULL , -- ѧ��ID - ShortID
          NULL , -- ��ע - VeryLongString
          NULL , -- ��ҳ - LongString
          NULL , -- ������òID - ShortID
          NULL , -- ���� - VeryLongString
          NULL , -- �س� - VeryLongString
          NULL , -- ��Ƭ - image
          NULL , -- ����״̬ID - AutoNo_Small
          -1 , -- �޸���ID - LongID
          CURRENT_TIMESTAMP , -- �޸�ʱ�� - smalldatetime
          'tedl' , -- ���� - LongString
          NULL , -- ���� - bit
          NULL , -- �����ļ� - image
          'tedl'  -- ��¼�� - varchar(20)
        )        
        
--6)xmis.hr_��Ա���Ź�ϵ��
INSERT INTO xmis.hr_��Ա���Ź�ϵ��
        ( ��ԱID, ����ID, ְ��, �Ƿ��ְ )
VALUES  ( -1, -- ��ԱID - LongID
          6, -- ����ID - LongID
          '', -- ְ�� - char(10)
          1  -- �Ƿ��ְ - bit
          )

INSERT INTO xmis.hr_��Ա���Ź�ϵ��
        ( ��ԱID, ����ID, ְ��, �Ƿ��ְ )
VALUES  ( 1, -- ��ԱID - LongID
          6, -- ����ID - LongID
          '����', -- ְ�� - char(10)
          1  -- �Ƿ��ְ - bit
          )
INSERT INTO xmis.hr_��Ա���Ź�ϵ��
        ( ��ԱID, ����ID, ְ��, �Ƿ��ְ )
VALUES  ( 2, -- ��ԱID - LongID
          6, -- ����ID - LongID
          '', -- ְ�� - char(10)
          1  -- �Ƿ��ְ - bit
          )

--7) xmis.prj_XXX
          
ALTER TABLE xmis.prj_��Ŀ ADD ��Ŀ���� VARCHAR(100)
ALTER TABLE xmis.prj_��Ŀ����� ADD �������� VARCHAR(100)   


INSERT INTO xmis.prj_��Ŀ״̬
        ( ��Ŀ״̬ID, ��Ŀ״̬, ��Ŀ״̬����, �Ƿ��Զ��� )
VALUES  ( 1, -- ��Ŀ״̬ID - ShortID
          '��Ŀ����', -- ��Ŀ״̬ - LongString
          NULL, -- ��Ŀ״̬���� - VeryLongString
          0  -- �Ƿ��Զ��� - bit
          )

   
INSERT INTO xmis.prj_��Ŀ״̬
        ( ��Ŀ״̬ID, ��Ŀ״̬, ��Ŀ״̬����, �Ƿ��Զ��� )
VALUES  ( 2, -- ��Ŀ״̬ID - ShortID
          '��Ŀ���', -- ��Ŀ״̬ - LongString
          NULL, -- ��Ŀ״̬���� - VeryLongString
          0  -- �Ƿ��Զ��� - bit
          )
INSERT INTO xmis.prj_��Ŀ״̬
        ( ��Ŀ״̬ID, ��Ŀ״̬, ��Ŀ״̬����, �Ƿ��Զ��� )
VALUES  ( 101, -- ��Ŀ״̬ID - ShortID
          '��Ŀ���׸��Ѹ�', -- ��Ŀ״̬ - LongString
          NULL, -- ��Ŀ״̬���� - VeryLongString
          1  -- �Ƿ��Զ��� - bit
          )


INSERT INTO xmis.prj_��Ŀ
        ( ��ĿID ,
          ��Ŀ���� ,
          ��Ŀ��ͬID ,
          �������� ,
          ��Ŀ״̬ID ,
          ��Ŀ����ID ,
          ��Ŀ����ID,
          ��Ŀ����
        )
VALUES  ( 1 , -- ��ĿID - LongID
          NULL , -- ��Ŀ���� - ShortString
          NULL , -- ��Ŀ��ͬID - LongID
          NULL , -- �������� - smalldatetime
          1 , -- ��Ŀ״̬ID - ShortID
          NULL,  -- ��Ŀ����ID - ShortID
          'Proj_Test_1'
        )


INSERT INTO xmis.prj_��Ŀ
        ( ��ĿID ,
          ��Ŀ���� ,
          ��Ŀ��ͬID ,
          �������� ,
          ��Ŀ״̬ID ,
          ��Ŀ����ID,
          ��Ŀ����
        )
VALUES  ( 2 , -- ��ĿID - LongID
          NULL , -- ��Ŀ���� - ShortString
          NULL , -- ��Ŀ��ͬID - LongID
          NULL , -- �������� - smalldatetime
          101 , -- ��Ŀ״̬ID - ShortID
          NULL,  -- ��Ŀ����ID - ShortID
          'Proj_Test_2'
        )
        
        
INSERT INTO xmis.prj_��Ŀ
        ( ��ĿID ,
          ��Ŀ���� ,
          ��Ŀ��ͬID ,
          �������� ,
          ��Ŀ״̬ID ,
          ��Ŀ����ID,
          ��Ŀ����
        )
VALUES  ( 3 , -- ��ĿID - LongID
          NULL , -- ��Ŀ���� - ShortString
          NULL , -- ��Ŀ��ͬID - LongID
          NULL , -- �������� - smalldatetime
          101 , -- ��Ŀ״̬ID - ShortID
           NULL,  -- ��Ŀ����ID - ShortID
          'Proj_Test_3'
        )
        
INSERT INTO xmis.prj_��Ŀ�����
        ( ��Ŀ����ID ,
          ��ĿID ,
          ������ID ,
          �нӲ���ID ,
          ���鷽�� ,
          �����ѵ� ,
          ��������ID ,
          �������ʱ�� ,
           ��������ID ,
          ��������
        )
VALUES  ( 1 , -- ��Ŀ����ID - LongID
          1 , -- ��ĿID - LongID
          1 , -- ������ID - LongID
          6 , -- �нӲ���ID - LongID
          NULL , -- ���鷽�� - VeryLongString
          NULL , -- �����ѵ� - VeryLongString
          NULL , -- ��������ID - ShortID
          NULL , -- �������ʱ�� - smalldatetime
          NULL  -- ��������ID - ShortID
        )  
        
INSERT INTO xmis.prj_��Ŀ�����
        ( ��Ŀ����ID ,
          ��ĿID ,
          ������ID ,
          �нӲ���ID ,
          ���鷽�� ,
          �����ѵ� ,
          ��������ID ,
          �������ʱ�� ,
          ��������ID ,
          ��������
        )
VALUES  ( 2 , -- ��Ŀ����ID - LongID
          1 , -- ��ĿID - LongID
          1 , -- ������ID - LongID
          6 , -- �нӲ���ID - LongID
          NULL , -- ���鷽�� - VeryLongString
          NULL , -- �����ѵ� - VeryLongString
          NULL , -- ��������ID - ShortID
          NULL , -- �������ʱ�� - smalldatetime
          NULL  -- ��������ID - ShortID
        )  
                       
         
INSERT INTO xmis.prj_��Ŀ�����
        ( ��Ŀ����ID ,
          ��ĿID ,
          ������ID ,
          �нӲ���ID ,
          ���鷽�� ,
          �����ѵ� ,
          ��������ID ,
          �������ʱ�� ,
          ��������ID ,
          ��������
        )
VALUES  ( 3 , -- ��Ŀ����ID - LongID
          1 , -- ��ĿID - LongID
          1 , -- ������ID - LongID
          6 , -- �нӲ���ID - LongID
          NULL , -- ���鷽�� - VeryLongString
          NULL , -- �����ѵ� - VeryLongString
          NULL , -- ��������ID - ShortID
          NULL , -- �������ʱ�� - smalldatetime
          NULL  -- ��������ID - ShortID
        )  
        
        
INSERT INTO xmis.prj_��Ŀ�����
        ( ��Ŀ����ID ,
          ��ĿID ,
          ������ID ,
          �нӲ���ID ,
          ���鷽�� ,
          �����ѵ� ,
          ��������ID ,
          �������ʱ�� ,
          ��������ID ,
          ��������
        )
VALUES  ( 4 , -- ��Ŀ����ID - LongID
          2 , -- ��ĿID - LongID
          1 , -- ������ID - LongID
          6 , -- �нӲ���ID - LongID
          NULL , -- ���鷽�� - VeryLongString
          NULL , -- �����ѵ� - VeryLongString
          NULL , -- ��������ID - ShortID
          NULL , -- �������ʱ�� - smalldatetime
          NULL  -- ��������ID - ShortID
        )  
                
INSERT INTO xmis.xmis.prj_��Ŀ�����Ա
        ( ��Ŀ����ID, ��Ŀ��ԱID, �е�����, �Ƿ����� )
VALUES  ( 1, -- ��Ŀ����ID - LongID
          1, -- ��Ŀ��ԱID - LongID
          NULL, -- �е����� - LongString
          0  -- �Ƿ����� - bit
          )
          
INSERT INTO xmis.xmis.prj_��Ŀ�����Ա
        ( ��Ŀ����ID, ��Ŀ��ԱID, �е�����, �Ƿ����� )
VALUES  ( 2, -- ��Ŀ����ID - LongID
          1, -- ��Ŀ��ԱID - LongID
          NULL, -- �е����� - LongString
          0  -- �Ƿ����� - bit
          )          
          
INSERT INTO xmis.xmis.prj_��Ŀ�����Ա
        ( ��Ŀ����ID, ��Ŀ��ԱID, �е�����, �Ƿ����� )
VALUES  ( 3, -- ��Ŀ����ID - LongID
          2, -- ��Ŀ��ԱID - LongID
          NULL, -- �е����� - LongString
          0  -- �Ƿ����� - bit
          )    
          
INSERT INTO xmis.xmis.prj_��Ŀ�����Ա
        ( ��Ŀ����ID, ��Ŀ��ԱID, �е�����, �Ƿ����� )
VALUES  ( 4, -- ��Ŀ����ID - LongID
          2, -- ��Ŀ��ԱID - LongID
          NULL, -- �е����� - LongString
          0  -- �Ƿ����� - bit
          )     
          
          
       