SET NOCOUNT ON 
DECLARE @contractType INT
SET @contractType = 1 


SELECT  xmis.con_��ͬ.* ,
        CONVERT(VARCHAR(10), xmis.con_��ͬ.�ʱ�����, 1) AS start_date ,
        CONVERT(VARCHAR(10), xmis.con_��ͬ.�ʱ���ֹ, 1) AS end_date ,
        CONVERT(VARCHAR(10), xmis.con_��ͬ.����ʱ��, 1) AS update_date ,
        xmis.prj_��Ŀ.��Ŀ���� ,
        xmis.prj_��Ŀ.��Ŀ���� ,
        contract.��ͬ��� contractNo ,
        contract.��� abbreviation ,
        aCompany.��˾���� aCompany_name ,
        aCompany.������д aCompany_abb ,
        bCompany.��˾���� bCompany_name ,
        aDept.�������� aDept_name ,
        bDept.�������� bDept_name ,
        RTRIM(aEmp.����) + RTRIM(aEmp.����) aEmp_name ,
        RTRIM(bEmp.����) + RTRIM(bEmp.����) bEmp_name ,
        RTRIM(cEmp.����) + RTRIM(cEmp.����) cEmp_name ,
        xmis.con_�����ͬ��Դ.���� AS �����ͬ��Դ ,
        CASE WHEN xmis.con_��ͬ.����ID IS NULL THEN '��'
             WHEN xmis.con_��ͬ.����ID = -1 THEN '��'
             ELSE xmis.sys_����.���ҷ���
        END AS ���ҷ��� ,
        CONVERT(SMALLINT, NULL) AS ��Ӧ�����ͬ����ID ,
        CONVERT(SMALLINT, NULL) AS ��Ӧ�����ͬ������
INTO    #contractList
FROM    xmis.con_��ͬ ,
        xmis.prj_��Ŀ ,
        xmis.con_��ͬ AS contract ,
        xmis.org_��˾ AS aCompany ,
        xmis.org_��˾ AS bCompany ,
        xmis.org_���� AS aDept ,
        xmis.org_���� AS bDept ,
        xmis.hr_��Ա AS aEmp ,
        xmis.hr_��Ա AS bEmp ,
        xmis.hr_��Ա AS cEmp ,
        xmis.con_�����ͬ��Դ ,
        xmis.sys_����
WHERE   xmis.con_��ͬ.��ͬ����ID = @contractType
        AND xmis.prj_��Ŀ.��ĿID =* xmis.con_��ͬ.��ĿID
        AND xmis.con_��ͬ.����ͬID *= contract.��ͬID
        AND aCompany.��˾ID =* xmis.con_��ͬ.�׷���˾ID
        AND bCompany.��˾ID =* xmis.con_��ͬ.�ҷ���˾ID
        AND aDept.����ID =* xmis.con_��ͬ.�׷�����ID
        AND bDept.����ID =* xmis.con_��ͬ.�ҷ�����ID
        AND aEmp.��ԱID =* xmis.con_��ͬ.�׷�����ID
        AND bEmp.��ԱID =* xmis.con_��ͬ.�ҷ�����ID
        AND cEmp.��ԱID =* xmis.con_��ͬ.�Ǽ���ID
        AND xmis.con_�����ͬ��Դ.�����ͬ��ԴID =* xmis.con_��ͬ.�����ͬ��ԴID
        AND xmis.con_��ͬ.����ID*=xmis.sys_����.����ID
 

DELETE  #contractList
WHERE   ��ͬ����ID = 2
        AND ��ͬID IN ( SELECT DISTINCT
                                ����ͬID
                      FROM      xmis.con_��ͬ
                      WHERE     ��ͬ����ID = 2 )

SELECT  ��ͬID ,
        SUM(�տ���) AS �տ�ϼ�
INTO    #charged
FROM    xmis.con_�տ���ϸ��
GROUP BY ��ͬID

SELECT  ��ͬID ,
        SUM(��Ʊ���) AS �ѿ���Ʊ���ϼ�
INTO    #invoice
FROM    xmis.con_��Ʊ���߱�
GROUP BY ��ͬID

SELECT  ��ͬID ,
        SUM(�վݽ��) AS �ѿ��վݽ��ϼ�
INTO    #receipt
FROM    xmis.con_�վ���ϸ��
GROUP BY ��ͬID

SELECT  xmis.con_�տ�������.��ͬID ,
        xmis.con_�տ�������.�տ�����
INTO    #warning_date
FROM    xmis.con_�տ�������

SELECT  xmis.con_�տ�������.��ͬID ,
        #warning_date.�տ����� AS warning_date ,
        SUM(xmis.con_�տ�������.�տ���) AS warning_amt ,
        0 AS warninged_flag ,
        NULL AS warning_days
INTO    #warning_detail
FROM    xmis.con_�տ������� ,
        #warning_date
WHERE   xmis.con_�տ�������.��ͬID = #warning_date.��ͬID
        AND ( xmis.con_�տ�������.�տ����� <= #warning_date.�տ�����
              OR #warning_date.�տ����� IS NULL
            )
GROUP BY xmis.con_�տ�������.��ͬID ,
        #warning_date.�տ�����

UPDATE  #warning_detail
SET     warning_amt = warning_amt - �տ�ϼ� ,
        warninged_flag = 1
FROM    #charged ,
        #warning_detail
WHERE   #charged.��ͬID = #warning_detail.��ͬID
        AND �տ�ϼ� >= warning_amt
UPDATE  #warning_detail
SET     warning_days = CASE WHEN DATEDIFF(d, GETDATE(), warning_date) < -30
                            THEN -30
                            WHEN DATEDIFF(d, GETDATE(), warning_date) >= -30
                                 AND DATEDIFF(d, GETDATE(), warning_date) < -15
                            THEN -15
                            WHEN DATEDIFF(d, GETDATE(), warning_date) >= -15
                                 AND DATEDIFF(d, GETDATE(), warning_date) < -7
                            THEN -7
                            WHEN DATEDIFF(d, GETDATE(), warning_date) >= -7
                                 AND DATEDIFF(d, GETDATE(), warning_date) < 0
                            THEN -1
                            WHEN DATEDIFF(d, GETDATE(), warning_date) = 0
                            THEN 1
                            WHEN DATEDIFF(d, GETDATE(), warning_date) > 0
                                 AND DATEDIFF(d, GETDATE(), warning_date) <= 7
                            THEN 7
                            WHEN DATEDIFF(d, GETDATE(), warning_date) > 7
                                 AND DATEDIFF(d, GETDATE(), warning_date) <= 15
                            THEN 15
                            WHEN DATEDIFF(d, GETDATE(), warning_date) > 15
                                 AND DATEDIFF(d, GETDATE(), warning_date) <= 30
                            THEN 30
                            WHEN warning_date IS NULL THEN NULL
                            ELSE DATEDIFF(d, GETDATE(), warning_date)
                       END
WHERE   warninged_flag = 0
SELECT  ��ͬID ,
        MAX(warning_date) AS warning_date ,
        MAX(warning_amt) AS warning_amt ,
        MAX(warning_days) AS warning_days
INTO    #warning
FROM    #warning_detail
WHERE   warning_days <= 30
        AND warninged_flag = 0
GROUP BY ��ͬID

SELECT  xmis.con_�տ�������.��ͬID ,
        MIN(xmis.con_�տ�������.�տ�����) AS warning_date ,
        0 AS warning_amt ,
        31 AS warning_days
INTO    #warning_info
FROM    xmis.con_�տ������� ,
        #warning
WHERE   xmis.con_�տ�������.��ͬID NOT IN ( SELECT ��ͬID
                                     FROM   #warning )
        AND �տ����� >= GETDATE()
GROUP BY xmis.con_�տ�������.��ͬID
UPDATE  #warning_info
SET     warning_amt = xmis.con_�տ�������.�տ���
FROM    xmis.con_�տ������� ,
        #warning_info
WHERE   xmis.con_�տ�������.��ͬID = #warning_info.��ͬID
        AND xmis.con_�տ�������.�տ����� = #warning_info.warning_date
INSERT  INTO #warning
        SELECT  *
        FROM    #warning_info 

SELECT  #contractList.* ,
        CASE WHEN #charged.�տ�ϼ� IS NULL THEN 0
             ELSE #charged.�տ�ϼ�
        END AS �տ�ϼ� ,
        #contractList.��ͬ�ܶ� - CASE WHEN #charged.�տ�ϼ� IS NULL THEN 0
                                  ELSE #charged.�տ�ϼ�
                             END AS δ�տ���ϼ� ,
        CASE WHEN #invoice.�ѿ���Ʊ���ϼ� IS NULL THEN 0
             ELSE #invoice.�ѿ���Ʊ���ϼ�
        END AS �ѿ���Ʊ���ϼ� ,
        CASE WHEN #receipt.�ѿ��վݽ��ϼ� IS NULL THEN 0
             ELSE #receipt.�ѿ��վݽ��ϼ�
        END AS �ѿ��վݽ��ϼ� ,
        CASE WHEN #invoice.�ѿ���Ʊ���ϼ� IS NULL THEN 0
             WHEN #invoice.�ѿ���Ʊ���ϼ� = 0 THEN 0
             ELSE #invoice.�ѿ���Ʊ���ϼ� - CASE WHEN #charged.�տ�ϼ� IS NULL THEN 0
                                           ELSE #charged.�տ�ϼ�
                                      END
        END AS �ѿ�Ʊδ���˽��ϼ� ,
        #warning.warning_date ,
        #warning.warning_amt - CASE WHEN #charged.�տ�ϼ� IS NULL THEN 0
                                    ELSE #charged.�տ�ϼ�
                               END AS warning_amt ,
        CASE WHEN #warning.warning_days IS NULL THEN -31
             ELSE #warning.warning_days
        END AS warning_days
INTO    #sumInfo
FROM    #contractList ,
        #charged ,
        #invoice ,
        #warning ,
        #receipt
WHERE   #contractList.��ͬID*=#charged.��ͬID
        AND #contractList.��ͬID*=#invoice.��ͬID
        AND #contractList.��ͬID*= #warning.��ͬID
        AND #contractList.��ͬID*= #receipt.��ͬID
SELECT  #sumInfo.* ,
        CONVERT(DECIMAL(18, 2), 0) AS MB ,
        CONVERT(DECIMAL(18, 2), 0) AS unMB ,
        CONVERT(DECIMAL(18, 2), 0) AS pay_amt
INTO    #prev
FROM    #sumInfo
WHERE   1 = 2
IF ( @contractType = 1 ) 
    BEGIN
        SELECT  DISTINCT
                xmis.fas_GL_accvouch.year ,
                xmis.fas_GL_accvouch.iperiod ,
                xmis.fas_GL_accvouch.ino_id
        INTO    #income_vouch
        FROM    xmis.fas_GL_accvouch
        WHERE   xmis.fas_GL_accvouch.iperiod > 0
                AND xmis.fas_GL_accvouch.iperiod <= 12
                AND NOT ( year = 2011
                          AND iperiod = 8
                          AND ino_id IN ( 327, 466 )
                        )
        CREATE INDEX i_t_incom_yii ON #income_vouch(year,iperiod,ino_id)
        SELECT  xmis.fas_GL_accvouch.year ,
                xmis.fas_GL_accvouch.iperiod ,
                xmis.fas_GL_accvouch.ino_id ,
                SUM(mc) - SUM(md) income_amt ,
                project_code ,
                citem_id
        INTO    #income
        FROM    xmis.fas_GL_accvouch ,
                #income_vouch ,
                xmis.fas_fitemss00 ,
                xmis.fas_codeType
        WHERE   xmis.fas_GL_accvouch.year = xmis.fas_fitemss00.year
                AND xmis.fas_GL_accvouch.citem_id = xmis.fas_fitemss00.citemcode
                AND xmis.fas_fitemss00.bclose = 0
                AND xmis.fas_GL_accvouch.year = #income_vouch.year
                AND xmis.fas_GL_accvouch.iperiod = #income_vouch.iperiod
                AND xmis.fas_GL_accvouch.ino_id = #income_vouch.ino_id
                AND xmis.fas_codeType.type = 0
                AND xmis.fas_GL_accvouch.ccode = xmis.fas_codeType.ccode
                AND project_code IS NOT NULL
        GROUP BY xmis.fas_GL_accvouch.year ,
                xmis.fas_GL_accvouch.iperiod ,
                xmis.fas_GL_accvouch.ino_id ,
                project_code ,
                citem_id
        SELECT  citem_id ,
                CASE WHEN cbegind_c LIKE '��' THEN -1 * mb
                     ELSE 0
                END AS income_mb
        INTO    #qch
        FROM    xmis.fas_GL_accass ,
                xmis.fas_codeType
        WHERE   year = 2008
                AND iperiod = 1
                AND citem_class = 00
                AND xmis.fas_codeType.type = 0
                AND xmis.fas_GL_accass.ccode = xmis.fas_codeType.ccode
        UNION ALL
        SELECT  citem_id ,
                CASE WHEN cbegind_c LIKE '��' THEN mb
                     ELSE 0
                END
        FROM    xmis.fas_GL_accass ,
                xmis.fas_codeType
        WHERE   year = 2008
                AND iperiod = 1
                AND citem_class = 00
                AND xmis.fas_codeType.type = 0
                AND xmis.fas_GL_accass.ccode = xmis.fas_codeType.ccode
        UNION ALL
        SELECT  citem_id ,
                SUM(mc)
        FROM    xmis.fas_GL_accvouch
        WHERE   xmis.fas_GL_accvouch.iperiod > 0
                AND xmis.fas_GL_accvouch.iperiod <= 12
                AND ccode = '51010102'
                OR ( year = 2011
                     AND iperiod = 8
                     AND ino_id = 466
                   )
        GROUP BY citem_id
        SELECT  citem_id ,
                CASE WHEN cbegind_c LIKE '��' THEN mb
                     ELSE 0
                END AS payout_mb
        INTO    #qcjcb
        FROM    xmis.fas_GL_accass ,
                xmis.fas_codeType
        WHERE   year = 2008
                AND iperiod = 1
                AND citem_class = 00
                AND xmis.fas_codeType.type = 1
                AND xmis.fas_GL_accass.ccode = xmis.fas_codeType.ccode
        UNION ALL
        SELECT  citem_id ,
                CASE WHEN cbegind_c LIKE '��' THEN -1 * mb
                     ELSE 0
                END
        FROM    xmis.fas_GL_accass ,
                xmis.fas_codeType
        WHERE   year = 2008
                AND iperiod = 1
                AND citem_class = 00
                AND xmis.fas_codeType.type = 1
                AND xmis.fas_GL_accass.ccode = xmis.fas_codeType.ccode
        UNION ALL
        SELECT  citem_id ,
                SUM(md)
        FROM    xmis.fas_GL_accvouch
        WHERE   xmis.fas_GL_accvouch.iperiod > 0
                AND xmis.fas_GL_accvouch.iperiod <= 12
                AND ccode IN ( '41010187', '4101012033' )
                OR ( year = 2011
                     AND iperiod = 8
                     AND ino_id = 327
                   )
        GROUP BY citem_id
        SELECT  project_code ,
                SUM(income_mb) AS MB
        INTO    #gl
        FROM    #qch ,
                xmis.fas_fitemss00
        WHERE   xmis.fas_fitemss00.year = 2008
                AND #qch.citem_id = xmis.fas_fitemss00.citemcode
        GROUP BY project_code
        UNION ALL
        SELECT  #income.project_code ,
                SUM(mc) - SUM(md)
        FROM    xmis.fas_GL_accvouch ,
                #income ,
                xmis.fas_codeType
        WHERE   xmis.fas_GL_accvouch.year = #income.year
                AND xmis.fas_GL_accvouch.iperiod = #income.iperiod
                AND xmis.fas_GL_accvouch.ino_id = #income.ino_id
                AND xmis.fas_GL_accvouch.citem_id = #income.citem_id
                AND xmis.fas_codeType.type = 0
                AND xmis.fas_GL_accvouch.ccode = xmis.fas_codeType.ccode
        GROUP BY #income.project_code
        HAVING  SUM(income_amt) <> 0
        SELECT  project_code ,
                SUM(MB) MB
        INTO    #glTotal
        FROM    #gl
        GROUP BY project_code
        SELECT  project_code ,
                SUM(payout_mb) AS pay_amt
        INTO    #purchase
        FROM    #qcjcb ,
                xmis.fas_fitemss00
        WHERE   xmis.fas_fitemss00.year = 2008
                AND #qcjcb.citem_id = xmis.fas_fitemss00.citemcode
        GROUP BY project_code
        UNION ALL
        SELECT  project_code ,
                SUM(md - mc)
        FROM    xmis.fas_GL_accvouch ,
                #income_vouch ,
                xmis.fas_fitemss00 ,
                xmis.fas_codeType
        WHERE   xmis.fas_GL_accvouch.year = xmis.fas_fitemss00.year
                AND xmis.fas_GL_accvouch.citem_id = xmis.fas_fitemss00.citemcode
                AND xmis.fas_fitemss00.bclose = 0
                AND xmis.fas_GL_accvouch.year = #income_vouch.year
                AND xmis.fas_GL_accvouch.iperiod = #income_vouch.iperiod
                AND xmis.fas_GL_accvouch.ino_id = #income_vouch.ino_id
                AND xmis.fas_codeType.type = 1
                AND xmis.fas_GL_accvouch.ccode = xmis.fas_codeType.ccode
                AND project_code IS NOT NULL
        GROUP BY project_code
        HAVING  SUM(md - mc) <> 0
        SELECT  project_code ,
                SUM(pay_amt) pay_amt
        INTO    #purchaseTotal
        FROM    #purchase
        GROUP BY project_code
        SELECT  #glTotal.project_code ,
                MB ,
                pay_amt
        INTO    #glInfo
        FROM    #glTotal ,
                #purchaseTotal
        WHERE   #glTotal.project_code *= #purchaseTotal.project_code
        INSERT  INTO #prev
                SELECT  #sumInfo.* ,
                        CASE WHEN MB IS NULL THEN 0
                             ELSE MB
                        END AS MB ,
                        ��ͬ�ܶ� - CASE WHEN MB IS NULL THEN 0
                                    ELSE MB
                               END AS unMB ,
                        CASE WHEN pay_amt IS NULL THEN 0
                             ELSE pay_amt
                        END AS pay_amt
                FROM    #sumInfo ,
                        #glInfo
                WHERE   #sumInfo.��Ŀ���� *= #glInfo.project_code
    END
ELSE 
    BEGIN
        INSERT  INTO #prev
                SELECT  #sumInfo.* ,
                        CONVERT(DECIMAL(9, 2), 0) AS MB ,
                        CONVERT(DECIMAL(9, 2), 0) AS unMB ,
                        CONVERT(DECIMAL(9, 2), 0) AS pay_amt
                FROM    #sumInfo
    END 
IF @contractType = 2 
    BEGIN 

        UPDATE  #prev
        SET     ��Ӧ�����ͬ����ID = xmis.con_��ͬ.�ҷ�����ID ,
                ��Ӧ�����ͬ������ = xmis.con_��ͬ.��ͬ������
        FROM    xmis.con_��ͬ ,
                #prev ,
                xmis.con_����֧����ͬ��Ӧ��
        WHERE   xmis.con_����֧����ͬ��Ӧ��.֧���Ӻ�ͬID = #prev.��ͬID
                AND xmis.con_��ͬ.��ͬID = xmis.con_����֧����ͬ��Ӧ��.�����ͬID
    END 
SELECT  #prev.*
INTO    #result
FROM    #prev
WHERE   ( �ҷ�����ID IN ( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) )

SELECT  #result.*
INTO    #resultC
FROM    #result
WHERE   1 = 2

INSERT  INTO #resultC
        SELECT  *
        FROM    #result
        ORDER BY MB DESC

SELECT  IDENTITY( INT,1,1 ) AS row_no ,
        #resultC.*
INTO    #resultA
FROM    #resultC 

SELECT  *
FROM    #resultA
WHERE   row_no = ( SELECT   MAX(row_no)
                   FROM     #resultA
                 )
UNION ALL
SELECT  *
FROM    #resultA
WHERE   row_no >= 1
        AND row_no < 21