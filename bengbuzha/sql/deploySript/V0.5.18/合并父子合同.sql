
ALTER TABLE xmis.con_��ͬ ALTER COLUMN ��ע NVARCHAR(800)
ALTER TABLE xmis.con_��ͬ ALTER COLUMN ��ͬ��Ҫ NVARCHAR(2500)


SELECT  *
INTO    #parent
FROM    xmis.con_��ͬ
WHERE   ��ͬID IN ( SELECT DISTINCT
                            ����ͬID
                  FROM      xmis.con_��ͬ
                  WHERE     ��ͬ����ID = 1
                            AND ����ͬID IS NOT NULL )
                            --����ͬ
UNION ALL
SELECT  *
FROM    xmis.con_��ͬ
WHERE   ��ͬ����ID = 1
        AND ����ͬID IS NOT NULL
        --�Ӻ�ͬ
        

UPDATE  #parent
SET     ��ͬ��Ҫ = ''
WHERE   ��ͬ��Ҫ IS NULL
UPDATE  #parent
SET     ��ע = ''
WHERE   ��ע IS NULL


--�ϲ��Ӻ�ͬ���ܽ�ժҪ����ע�������뵽����ͬ
DECLARE cur CURSOR  FOR SELECT ��ͬID,����ͬID,��ͬ�ܶ�,��ͬ��Ҫ,��ע  FROM #parent WHERE ����ͬID IS NOT NULL
DECLARE @contratID INT ,
    @parentID INT ,
    @amt DECIMAL(16, 9) ,
    @abs NVARCHAR(2800) ,
    @remark NVARCHAR(500)

OPEN cur
FETCH NEXT FROM cur INTO @contratID , @parentID , @amt , @abs , @remark 
    
WHILE @@fetch_status = 0 
    BEGIN
        IF ( @parentID IS NOT NULL )
			-- child contract
            BEGIN
                
                UPDATE  #parent
                SET     ��ͬ�ܶ� = ��ͬ�ܶ� + @amt ,
                        ��ͬ��Ҫ = ��ͬ��Ҫ + ',' + CONVERT(NVARCHAR(100), @contratID)
                        + ')' + @abs ,
                        ��ע = CONVERT(NVARCHAR(500), ��ע) + ','
                        + CONVERT(NVARCHAR(100), @contratID) + ')' + @remark
                WHERE   ��ͬID = @parentID
            END

        FETCH NEXT FROM cur INTO @contratID , @parentID , @amt , @abs , @remark 

    END
CLOSE cur
DEALLOCATE cur

UPDATE  #parent
SET     ����ͬID = ��ͬID
WHERE   ����ͬID IS NULL

--create new contractID
DECLARE @maxID INT
SELECT  @maxID = MAX(xmis.con_��ͬ.��ͬID)
FROM    xmis.con_��ͬ

DECLARE cur1 CURSOR  FOR SELECT ����ͬID FROM #parent WHERE ��ͬID = ����ͬID
DECLARE @oldID INT ,
    @forCount INT
SELECT  @forCount = 1

OPEN cur1
FETCH NEXT FROM cur1 INTO @oldID 
    
WHILE @@fetch_status = 0 
    BEGIN
        UPDATE  #parent
        SET     ����ͬID = @maxID + @forCount
        WHERE   ����ͬID = @oldID
                
        SELECT  @forCount = @forCount + 1
        FETCH NEXT FROM cur1 INTO @oldID 

    END
CLOSE cur1
DEALLOCATE cur1

--��ԭ�ȵĸ���ͬ��Ϊ����ͬIDΪ�Լ����Ӻ�ͬ
UPDATE  xmis.con_��ͬ
SET     ����ͬID = ��ͬID
WHERE   ��ͬID IN ( SELECT  DISTINCT
                            ����ͬID
                  FROM      xmis.con_��ͬ
                  WHERE     ��ͬ����ID = 1
                            AND ����ͬID IS NOT NULL )
                            --����ͬ

--insert new contract
INSERT  INTO xmis.con_��ͬ
        ( ��ͬID ,
          ��ͬ��� ,
          ��ͬ���� ,
          ��� ,
          ����ͬID ,
          ǩ������ ,
          �׷���˾ID ,
          �׷�����ID ,
          �ҷ���˾ID ,
          �ҷ�����ID ,
          ��ͬ�ܶ� ,
          ����ID ,
          ��ͬ����ID ,
          �׷�����ID ,
          �ҷ�����ID ,
          ��ͬ��Ҫ ,
          ��ע ,
          �Ǽ���ID ,
          ����ʱ�� ,
          ��ͬ��Դ����ID ,
          �����ͬ��ԴID ,
          �ʱ����� ,
          �ʱ���ֹ ,
          �ʱ��ڶ��� ,
          ������ϵ��ID ,
          �ʱ����� ,
          �ʱ��ڼ�����λ ,
          ��ĿID ,
          ��ͬ������
        )
        SELECT  ����ͬID , --new contractID
                ��ͬ��� ,
                ��ͬ���� ,
                ��� ,
                NULL ,
                ǩ������ ,
                �׷���˾ID ,
                �׷�����ID ,
                �ҷ���˾ID ,
                �ҷ�����ID ,
                ��ͬ�ܶ� ,
                ����ID ,
                ��ͬ����ID ,
                �׷�����ID ,
                �ҷ�����ID ,
                ��ͬ��Ҫ ,
                ��ע ,
                �Ǽ���ID ,
                ����ʱ�� ,
                ��ͬ��Դ����ID ,
                �����ͬ��ԴID ,
                �ʱ����� ,
                �ʱ���ֹ ,
                �ʱ��ڶ��� ,
                ������ϵ��ID ,
                �ʱ����� ,
                �ʱ��ڼ�����λ ,
                ��ĿID ,
                ��ͬ������
        FROM    #parent
        WHERE   ��ͬID IN ( SELECT    ����ͬID
                          FROM      xmis.con_��ͬ
                          WHERE     ��ͬ����ID = 1
                                    AND ����ͬID = ��ͬID )
                            --����ͬ



--��������
--SELECT * FROM xmis.con_�տ������� WHERE ��ͬID IN (SELECT ��ͬID FROM #parent WHERE ����ͬID IS NOT null)
--SELECT * FROM xmis.con_�տ������� WHERE ��ͬID IN (SELECT ��ͬID FROM #parent WHERE ����ͬID IS null)

DROP  TABLE #paymentcondition
SELECT  *
INTO    #paymentcondition
FROM    xmis.con_�տ�������
WHERE   1 = 2
go
ALTER TABLE #paymentcondition ADD iid INT IDENTITY(1,1)
go
INSERT  INTO #paymentcondition
        ( ��ͬID ,
          �տ�����ID ,
          �տ��������� ,
          ��Ӧ��Ŀ״̬ ,
          �ӳ����� ,
          �տ����� ,
          �ֶ����� ,
          �տ�ٷֱ� ,
          �տ��� ,
          �ֶ�����ԭ��
        )
        SELECT  ��ͬID ,
                �տ�����ID ,
                �տ��������� ,
                ��Ӧ��Ŀ״̬ ,
                �ӳ����� ,
                �տ����� ,
                �ֶ����� ,
                �տ�ٷֱ� ,
                �տ��� ,
                �ֶ�����ԭ��
        FROM    xmis.con_�տ�������
        WHERE   ��ͬID IN ( SELECT    ��ͬID
                          FROM      #parent )
        ORDER BY �տ�����ID


UPDATE  #paymentcondition
SET     ��ͬID = ����ͬID
FROM    #parent ,
        #paymentcondition
WHERE   #parent.��ͬID = #paymentcondition.��ͬID
        AND ����ͬID IS NOT NULL
        
INSERT  INTO xmis.con_�տ�������
        ( ��ͬID ,
          �տ�����ID ,
          �տ��������� ,
          ��Ӧ��Ŀ״̬ ,
          �ӳ����� ,
          �տ����� ,
          �ֶ����� ,
          �տ�ٷֱ� ,
          �տ��� ,
          �ֶ�����ԭ��
        )
        SELECT  ��ͬID ,
                iid ,
                �տ��������� ,
                ��Ӧ��Ŀ״̬ ,
                �ӳ����� ,
                �տ����� ,
                �ֶ����� ,
                �տ�ٷֱ� ,
                �տ��� ,
                �ֶ�����ԭ��
        FROM    #paymentcondition


--�տ���ϸ
--SELECT * FROM xmis.con_�տ���ϸ�� WHERE ��ͬID IN (SELECT ��ͬID FROM #parent WHERE ����ͬID IS NOT null)
--SELECT * FROM xmis.con_�տ���ϸ�� WHERE ��ͬID IN (SELECT ��ͬID FROM #parent WHERE ����ͬID IS  null)

--DROP TABLE #paymentdetal
SELECT  *
INTO    #paymentdetal
FROM    xmis.con_�տ���ϸ��
WHERE   1 = 2
go
ALTER TABLE #paymentdetal ADD iid INT IDENTITY(1,1)
go

INSERT  INTO #paymentdetal
        ( ��ͬID ,
          �տ�ID ,
          �տ��� ,
          �տ����� ,
          ������ ,
          Ʊ��ɨ�� ,
          �Ǽ��� ,
          �Ǽ����� ,
          ��ע
        )
        SELECT  ��ͬID ,
                �տ�ID ,
                �տ��� ,
                �տ����� ,
                ������ ,
                Ʊ��ɨ�� ,
                �Ǽ��� ,
                �Ǽ����� ,
                ��ע
        FROM    xmis.con_�տ���ϸ��
        WHERE   ��ͬID IN ( SELECT    ��ͬID
                          FROM      #parent )
        ORDER BY �տ�ID


UPDATE  #paymentdetal
SET     ��ͬID = ����ͬID
FROM    #parent ,
        #paymentdetal
WHERE   #parent.��ͬID = #paymentdetal.��ͬID
        AND ����ͬID IS NOT NULL


INSERT  INTO xmis.con_�տ���ϸ��
        ( ��ͬID ,
          �տ�ID ,
          �տ��� ,
          �տ����� ,
          ������ ,
          Ʊ��ɨ�� ,
          �Ǽ��� ,
          �Ǽ����� ,
          ��ע
        )
        SELECT  ��ͬID ,
                iid ,
                �տ��� ,
                �տ����� ,
                ������ ,
                Ʊ��ɨ�� ,
                �Ǽ��� ,
                �Ǽ����� ,
                ��ע
        FROM    #paymentdetal



--Ʊ����ϸ
--SELECT  * FROM    xmis.con_��Ʊ���߱� WHERE   ��ͬID IN ( SELECT    ��ͬID                  FROM      #parent                  WHERE     ����ͬID IS NOT NULL )
--UNION ALL 
--SELECT  * FROM    xmis.con_��Ʊ���߱� WHERE   ��ͬID IN ( SELECT    ��ͬID                  FROM      #parent                  WHERE     ����ͬID IS  NULL )


SELECT  *
INTO    #invoiceDetial
FROM    xmis.con_��Ʊ���߱�
WHERE   1 = 2
go
ALTER TABLE #invoiceDetial ADD iid INT IDENTITY(1,1)
go
INSERT  INTO #invoiceDetial
        ( ��ͬID ,
          ��Ʊ�� ,
          ��Ʊ��� ,
          �������� ,
          ������ ,
          ɨ��� ,
          �Ǽ��� ,
          �Ǽ����� ,
          ��ע ,
          ��Ʊ��� ,
          �ռ��� ,
          �ʼ����
        )
        SELECT  ��ͬID ,
                ��Ʊ�� ,
                ��Ʊ��� ,
                �������� ,
                ������ ,
                ɨ��� ,
                �Ǽ��� ,
                �Ǽ����� ,
                ��ע ,
                ��Ʊ��� ,
                �ռ��� ,
                �ʼ����
        FROM    xmis.con_��Ʊ���߱�
        WHERE   ��ͬID IN ( SELECT    ��ͬID
                          FROM      #parent )
        ORDER BY ��Ʊ��


UPDATE  #invoiceDetial
SET     ��ͬID = ����ͬID
FROM    #parent ,
        #invoiceDetial
WHERE   #parent.��ͬID = #invoiceDetial.��ͬID
        AND ����ͬID IS NOT NULL


INSERT  INTO xmis.con_��Ʊ���߱�
        ( ��ͬID ,
          ��Ʊ�� ,
          ��Ʊ��� ,
          �������� ,
          ������ ,
          ɨ��� ,
          �Ǽ��� ,
          �Ǽ����� ,
          ��ע ,
          ��Ʊ��� ,
          �ռ��� ,
          �ʼ����
        )
        SELECT  ��ͬID ,
                iid ,
                ��Ʊ��� ,
                �������� ,
                ������ ,
                ɨ��� ,
                �Ǽ��� ,
                �Ǽ����� ,
                ��ע ,
                ��Ʊ��� ,
                �ռ��� ,
                �ʼ����
        FROM    #invoiceDetial


--�վ���ϸ��
--SELECT * FROM xmis.con_�վ���ϸ�� WHERE ��ͬID IN (SELECT ��ͬID FROM #parent WHERE ����ͬID IS NOT null)
--UNION ALL 
--SELECT  * FROM    xmis.con_�վ���ϸ�� WHERE   ��ͬID IN ( SELECT    ��ͬID                   FROM      #parent                  WHERE     ����ͬID IS  NULL )

SELECT  *
INTO    #receiptDetial
FROM    xmis.con_�վ���ϸ��
WHERE   1 = 2
go
ALTER TABLE #receiptDetial ADD iid INT IDENTITY(1,1)
go

INSERT  INTO #receiptDetial
        ( �վ�ID ,
          �վݽ�� ,
          �վ����� ,
          ������ ,
          Ʊ��ɨ�� ,
          ��ͬID ,
          �Ǽ��� ,
          �Ǽ����� ,
          ��ע ,
          �վݱ�� ,
          �ռ��� ,
          �ʼ����
        )
        SELECT  �վ�ID ,
                �վݽ�� ,
                �վ����� ,
                ������ ,
                Ʊ��ɨ�� ,
                ��ͬID ,
                �Ǽ��� ,
                �Ǽ����� ,
                ��ע ,
                �վݱ�� ,
                �ռ��� ,
                �ʼ����
        FROM    xmis.con_�վ���ϸ��
        WHERE   ��ͬID IN ( SELECT    ��ͬID
                          FROM      #parent )
        ORDER BY �վ�ID


UPDATE  #receiptDetial
SET     ��ͬID = ����ͬID
FROM    #parent ,
        #receiptDetial
WHERE   #parent.��ͬID = #receiptDetial.��ͬID
        AND ����ͬID IS NOT NULL
        
        
INSERT  INTO xmis.con_�վ���ϸ��
        ( �վ�ID ,
          �վݽ�� ,
          �վ����� ,
          ������ ,
          Ʊ��ɨ�� ,
          ��ͬID ,
          �Ǽ��� ,
          �Ǽ����� ,
          ��ע ,
          �վݱ�� ,
          �ռ��� ,
          �ʼ����
        )
        SELECT  iid ,
                �վݽ�� ,
                �վ����� ,
                ������ ,
                Ʊ��ɨ�� ,
                ��ͬID ,
                �Ǽ��� ,
                �Ǽ����� ,
                ��ע ,
                �վݱ�� ,
                �ռ��� ,
                �ʼ����
        FROM    #receiptDetial
        

--��֧��Ӧ
--SELECT  * FROM    xmis.con_����֧����ͬ��Ӧ�� WHERE   �����ͬID IN ( SELECT  ��ͬID FROM    #parent WHERE   ����ͬID IS NOT NULL ) 
--SELECT  * FROM    xmis.con_����֧����ͬ��Ӧ�� WHERE   �����ͬID IN ( SELECT  ��ͬID FROM    #parent WHERE   ����ͬID IS NULL ) 


SELECT  *
INTO    #incomeMapping
FROM    xmis.con_����֧����ͬ��Ӧ��
WHERE   1 = 2
go
ALTER TABLE #incomeMapping ADD iid INT IDENTITY(1,1)
go
INSERT  INTO #incomeMapping
        ( �����ͬID ,
          ֧����ͬID ,
          ��ӦID ,
          ��� ,
          ��ע ,
          ֧���Ӻ�ͬID 
        )
        SELECT  �����ͬID ,
                ֧����ͬID ,
                ��ӦID ,
                ��� ,
                ��ע ,
                ֧���Ӻ�ͬID
        FROM    xmis.con_����֧����ͬ��Ӧ��
        WHERE   �����ͬID IN ( SELECT  ��ͬID
                            FROM    #parent )
        ORDER BY ��ӦID


UPDATE  #incomeMapping
SET     �����ͬID = ����ͬID
FROM    #parent ,
        #incomeMapping
WHERE   #parent.��ͬID = #incomeMapping.�����ͬID
        AND ����ͬID IS NOT NULL
        
INSERT  INTO xmis.con_����֧����ͬ��Ӧ��
        ( �����ͬID ,
          ֧����ͬID ,
          ��ӦID ,
          ��� ,
          ��ע ,
          ֧���Ӻ�ͬID 
        )
        SELECT  �����ͬID ,
                ֧����ͬID ,
                iid ,
                ��� ,
                ��ע ,
                ֧���Ӻ�ͬID
        FROM    #incomeMapping


s
--����
--SELECT  COUNT(*) FROM    xmis.sys_����
--SELECT DISTINCT ������������ID FROM    xmis.sys_���� 

SELECT  *
INTO    #attachment
FROM    xmis.sys_����
WHERE   ������������ID = 1
        AND 1 = 2 
go        
ALTER TABLE #attachment ADD iid INT IDENTITY(1,1)
go
INSERT  INTO #attachment
        ( ����ID ,
          �ϴ�ʱ�� ,
          �ϴ��� ,
          �������� ,
          �ļ��� ,
          �������� ,
          ������������ID ,
          ��������ֶ� ,
          REFID
        )
        SELECT  ����ID ,
                �ϴ�ʱ�� ,
                �ϴ��� ,
                �������� ,
                �ļ��� ,
                �������� ,
                ������������ID ,
                ��������ֶ� ,
                REFID
        FROM    xmis.sys_����
        ORDER BY ����ID

UPDATE  #attachment
SET     REFID = ����ͬID
FROM    #parent ,
        #attachment
WHERE   #parent.��ͬID = #attachment.REFID
        AND ����ͬID IS NOT NULL
        
        
INSERT  INTO xmis.sys_����
        ( ����ID ,
          �ϴ�ʱ�� ,
          �ϴ��� ,
          �������� ,
          �ļ��� ,
          �������� ,
          ������������ID ,
          ��������ֶ� ,
          REFID
        )
        SELECT  iid ,
                �ϴ�ʱ�� ,
                �ϴ��� ,
                �������� ,
                �ļ��� ,
                �������� ,
                ������������ID ,
                ��������ֶ� ,
                REFID
        FROM    #attachment
        