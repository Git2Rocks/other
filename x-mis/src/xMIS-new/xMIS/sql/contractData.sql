--drop table #year,#contractFromKZHB,#tableName,#company,#division,#contractRelation
--delete from [backup].dbo.contractFromKZHB_temp

USE [backup]

BEGIN

    USE [backup]

    CREATE TABLE #year ( year VARCHAR(4) )
	
	INSERT  #year    VALUES  ( '2011' )
	INSERT  #year
    VALUES  ( '2010' )
    INSERT  #year
    VALUES  ( '2009' )
    INSERT  #year
    VALUES  ( '2008' )
    INSERT  #year
    VALUES  ( '2007' )
    INSERT  #year
    VALUES  ( '2006' )

    CREATE TABLE #division
        (
          div_id INT ,
          div_code VARCHAR(10) ,
          div_name NVARCHAR(40)
        )

    INSERT  INTO #division
    VALUES  ( 461, 'KZ', '�Ƽ�������' ) 
    INSERT  INTO #division
    VALUES  ( 460, 'JC', '�����ҵ��' ) 
    INSERT  INTO #division
    VALUES  ( 465, 'SD', 'ˮ��ˮ�����̲�' ) 
    INSERT  INTO #division
    VALUES  ( 457, 'TS', '���������̲�' ) 
    INSERT  INTO #division
    VALUES  ( 458, 'ZB', '����װ����ҵ��' ) 
    INSERT  INTO #division
    VALUES  ( 459, 'YX', '�������б��Ϲ��̲�' ) 
    INSERT  INTO #division
    VALUES  ( 463, 'SY', 'ˮ����е�����о�����' ) 
    INSERT  INTO #division
    VALUES  ( 466, 'NY', '����Դ��ҵ��' ) 
    
    INSERT  INTO #division
    VALUES  ( 800, 'WS', '����' ) 
    INSERT  INTO #division
    VALUES  ( 801, 'TZ', '����' ) 
    --INSERT  INTO #division
    --VALUES  ( 802, 'QT', '����' )
   
    
    
    SELECT  '[' + year + '-' + div_code + ']' table_name
    INTO    #tableName
    FROM    #year ,
            #division



/*================*/
    CREATE TABLE #contractFromKZHB
        (
          year varchar(4),
          SID INT IDENTITY(1, 1) ,
          id INT ,                                                            
          division_id INT ,                    --����ID
          division_code NVARCHAR(10) ,         --���ű��
          division_name NVARCHAR(100) ,        --��������
          project_id INT,                      --��ĿID
          project_code NVARCHAR(40) ,          --��Ŀ����
          contract_type INT ,                  --��ͬ����
          contract_id INT ,                    --��ͬID
          contract_code NVARCHAR(40) ,         --��ͬ����
          CONTRACT_NAME NVARCHAR(200) ,        --��ͬ����
          contract_amt FLOAT ,                 --��ͬ�ܶ�
          company_name NVARCHAR(60) ,         --��˾����
          company_id INT ,                     --��˾ID
          begin_date NVARCHAR(20) ,            --��ͬ��ʼʱ��
          end_date NVARCHAR(20) ,              --��ͬ��ֹʱ��
          contract_manager NVARCHAR(20) ,      --��Ŀ������
          contarct_manager_id INT ,            --��Ŀ������ID
          contract_date NVARCHAR(10) ,         --����ʱ��   
          remark NVARCHAR(200) ,               --��ע
          sign_name NVARCHAR(20) ,             --������       
          sign_id INT                          --������ID    
        )


    DECLARE @sql VARCHAR(8000) ,
            @sql1 VARCHAR(8000) ,
            @sql11 VARCHAR(8000) ,
            @sql2 VARCHAR(8000) ,
            @sql21 VARCHAR(8000) ,
            @execSQL VARCHAR(8000) ,
            @execSQL1 VARCHAR(8000) ,
            @execSQL2 VARCHAR(8000) ,
            @execSQL11 VARCHAR(8000) ,
            @execSQL21 VARCHAR(8000) ,
            @TableName VARCHAR(100)





    SET @sql = 'INSERT INTO #contractFromKZHB
        ( year,
			id ,
          division_code ,      --���ű��
          project_code ,       --��Ŀ����
          contract_type ,      --��ͬ����  1:�����ͬ��2:֧����ͬ
          contract_code ,      --��ͬ����
          CONTRACT_NAME ,      --��ͬ����
          contract_amt ,       --��ͬ�ܶ�
          company_name ,       --��˾����
          begin_date ,         --��ͬ��ʼʱ��
          end_date ,           --��ͬ��ֹʱ��
          contract_manager ,   --��Ŀ������
          sign_name ,          --������
          contract_date ,      --����ʱ��
          remark               --��ע
        )'
        
        set @sql1 = '
        SELECT  ''T_year'',
				���1 ,
                ''divCode'' ,
                ��˾��� ,
                1 ,
                ��˾��� ,
                ��Ŀ���� ,
                ��ˮ�Ƽ������Ժ�ͬ * 10000 ,
                CASE WHEN LEN(��Լ��)>60 
					 THEN SUBSTRING(��Լ��,CHARINDEX('')'',��Լ��)+1,CHARINDEX(''('',��Լ��)-CHARINDEX('')'',��Լ��)-1)
					 ELSE ��Լ��
				END ,
                CASE WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) = LEN(LTRIM(RTRIM(SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)))) then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-'')) + ''01''   
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) != LEN(LTRIM(RTRIM(SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)))) then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) <= 0 then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-'')) + ''-01''
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and CHARINDEX(''='',SUBSTRING(��ͬ��Ч����,CHARINDEX(''='',��ͬ��Ч����)+1,10))>0 THEN RTRIM(REPLACE(��ͬ��Ч����, ''='', ''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''.'',��ͬ��Ч����)+1,10))>0 THEN RTRIM(REPLACE(��ͬ��Ч����, ''.'', ''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and CHARINDEX(''='',SUBSTRING(��ͬ��Ч����,CHARINDEX(''='',��ͬ��Ч����)+1,10))<=0 and CHARINDEX(''='',��ͬ��Ч����) > 0 then RTRIM(REPLACE(��ͬ��Ч����, ''='', ''-'')) + ''-01''
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''.'',��ͬ��Ч����)+1,10))<=0 and CHARINDEX(''.'',��ͬ��Ч����) > 0 then RTRIM(REPLACE(��ͬ��Ч����, ''.'', ''-'')) + ''-01''
					 ELSE NULL
				END ,
				CASE WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10)) > 0 and F22 IS null and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) = LEN(LTRIM(RTRIM(SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)))) then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-'')) + ''01'' 
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10)) > 0 and F22 IS null and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) != LEN(LTRIM(RTRIM(SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10))))  then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10)) > 0 and F22 IS null and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) <= 0 then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-'')) + ''-01''
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and F22 IS NOT NULL and CHARINDEX(''='',SUBSTRING(F22,CHARINDEX(''='',F22)+1,10))>0 then RTRIM(REPLACE(F22, ''='', ''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and F22 IS NOT NULL and CHARINDEX(''='',SUBSTRING(F22,CHARINDEX(''='',F22)+1,10))<=0 and CHARINDEX(''='',F22)>0 then RTRIM(REPLACE(F22, ''='', ''-'')) + ''-01''
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and F22 IS NOT NULL and CHARINDEX(''.'',SUBSTRING(F22,CHARINDEX(''.'',F22)+1,10))>0 then RTRIM(REPLACE(F22, ''.'', ''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and F22 IS NOT NULL and CHARINDEX(''.'',SUBSTRING(F22,CHARINDEX(''.'',F22)+1,10))<=0 and CHARINDEX(''.'',F22)>0 then RTRIM(REPLACE(F22, ''.'', ''-'')) + ''-01''
					 ELSE NULL
				END ,
                CASE WHEN CHARINDEX(''��'',F23) > 0 THEN SUBSTRING(F23,0,CHARINDEX(''��'',F23))
				ELSE F23
				END  ,
                CASE WHEN CHARINDEX(''20'', ��ͬ�������ڼ��ͽ���) > 0
                     THEN SUBSTRING(��ͬ�������ڼ��ͽ���, 0,
                                    CHARINDEX(''20'', ��ͬ�������ڼ��ͽ���))
                     ELSE ��ͬ�������ڼ��ͽ���
                END ,
                CASE WHEN CHARINDEX(''20'', ��ͬ�������ڼ��ͽ���) > 0 
                     THEN RTRIM(REPLACE(SUBSTRING(��ͬ�������ڼ��ͽ���,
                                            CHARINDEX(''20'',
                                                      ��ͬ�������ڼ��ͽ���),
                                            10), ''.'', ''-''))
                     ELSE NULL
                END ,'
      set @sql11 ='
                CASE WHEN ��ˮ�Ƽ������� IS NOT NULL
                     THEN ''�г�:''
                          + CONVERT(NVARCHAR(20), CONVERT(DECIMAL(10, 2), ��ˮ�Ƽ�������  * 10000))
                     ELSE ''''
                END + CASE WHEN F16 IS NOT NULL
                           THEN '' �޳�:''
                                + CONVERT(NVARCHAR(20), CONVERT(DECIMAL(10, 2), F16
                                * 10000))
                           ELSE ''''
                END + CASE WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10)) <= 0 and F22 IS null and RTRIM(LTRIM(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10))) !=''''
						   THEN '' ��ͬ��ֹʱ��:''+SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,LEN(��ͬ��Ч����))
						   WHEN F22 IS NOT NULL AND CHARINDEX(''.'',F22) <= 0 AND CHARINDEX(''='',F22) <= 0
						   THEN '' ��ͬ��ֹʱ��:''+F22
						   ELSE ''''
				END + CASE WHEN CHARINDEX(''��'',F23) > 0 THEN '' ��ͬ�����ˣ�'' + F23
						   ELSE ''''
				END + CASE WHEN LEN(��Լ��)>60 
						   THEN '' ԭ��˾���ƣ�'' + ��Լ��
					       ELSE ''''
				END
        FROM    dbo.sourceTab
        WHERE   ���1 > 0
                AND ���2 IS NULL'
        set @sql2 = '   
        UNION
        SELECT  ''T_year'',
				���2 ,
                ''divCode'' ,
                ��˾��� ,
                2 ,
                ��˾��� ,
                ��Ŀ���� ,
                (CASE WHEN ��ˮ�Ƽ�֧���Ժ�ͬ�����ͳ�� IS NULL THEN 0 
					  ELSE CONVERT(DECIMAL(10, 2), ��ˮ�Ƽ�֧���Ժ�ͬ�����ͳ��) 
				      END + CASE WHEN F18 IS NULL THEN 0 
		              ELSE CONVERT(DECIMAL(10, 2), F18)
					  END )* 10000
                 ,
                CASE WHEN LEN(��Լ��)>60 
					 THEN SUBSTRING(��Լ��,CHARINDEX('')'',��Լ��)+1,CHARINDEX(''('',��Լ��)-CHARINDEX('')'',��Լ��)-1)
					 ELSE ��Լ��
				END ,
                CASE WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) = LEN(LTRIM(RTRIM(SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)))) then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-'')) + ''01''   
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) != LEN(LTRIM(RTRIM(SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10))))  then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-''))+1,10)) <= 0 then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,0,CHARINDEX(''-'',��ͬ��Ч����)),''.'',''-'')) + ''-01''
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and CHARINDEX(''='',SUBSTRING(��ͬ��Ч����,CHARINDEX(''='',��ͬ��Ч����)+1,10))>0 THEN RTRIM(REPLACE(��ͬ��Ч����, ''='', ''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''.'',��ͬ��Ч����)+1,10))>0 THEN RTRIM(REPLACE(��ͬ��Ч����, ''.'', ''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and CHARINDEX(''='',SUBSTRING(��ͬ��Ч����,CHARINDEX(''='',��ͬ��Ч����)+1,10))<=0 and CHARINDEX(''='',��ͬ��Ч����) > 0 then RTRIM(REPLACE(��ͬ��Ч����, ''='', ''-'')) + ''-01''
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''.'',��ͬ��Ч����)+1,10))<=0 and CHARINDEX(''.'',��ͬ��Ч����) > 0 then RTRIM(REPLACE(��ͬ��Ч����, ''.'', ''-'')) + ''-01''
					 ELSE NULL
				END ,
                CASE WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10)) > 0 and F22 IS null and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) = LEN(LTRIM(RTRIM(SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)))) then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-'')) + ''01'' 
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10)) > 0 and F22 IS null and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) > 0 and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) != LEN(LTRIM(RTRIM(SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10))))  then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10)) > 0 and F22 IS null and CHARINDEX(''-'',SUBSTRING(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''),CHARINDEX(''-'',REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-''))+1,10)) <= 0 then RTRIM(REPLACE(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10),''.'',''-'')) + ''-01''
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and F22 IS NOT NULL and CHARINDEX(''='',SUBSTRING(F22,CHARINDEX(''='',F22)+1,10))>0 then RTRIM(REPLACE(F22, ''='', ''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and F22 IS NOT NULL and CHARINDEX(''='',SUBSTRING(F22,CHARINDEX(''='',F22)+1,10))<=0 and CHARINDEX(''='',F22)>0 then RTRIM(REPLACE(F22, ''='', ''-'')) + ''-01''
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and F22 IS NOT NULL and CHARINDEX(''.'',SUBSTRING(F22,CHARINDEX(''.'',F22)+1,10))>0 then RTRIM(REPLACE(F22, ''.'', ''-''))
					 WHEN CHARINDEX(''-'',��ͬ��Ч����) <= 0 and F22 IS NOT NULL and CHARINDEX(''.'',SUBSTRING(F22,CHARINDEX(''.'',F22)+1,10))<=0 and CHARINDEX(''.'',F22)>0 then RTRIM(REPLACE(F22, ''.'', ''-'')) + ''-01''
					 ELSE NULL
				END ,
                CASE WHEN CHARINDEX(''��'',F23) > 0 THEN SUBSTRING(F23,0,CHARINDEX(''��'',F23))
				ELSE F23
				END ,
                CASE WHEN CHARINDEX(''20'', ��ͬ�������ڼ��ͽ���) > 0
                     THEN SUBSTRING(��ͬ�������ڼ��ͽ���, 0,
                                    CHARINDEX(''20'', ��ͬ�������ڼ��ͽ���))
                     ELSE ��ͬ�������ڼ��ͽ���
                END ,
                CASE WHEN CHARINDEX(''20'', ��ͬ�������ڼ��ͽ���) > 0 
                     THEN RTRIM(REPLACE(SUBSTRING(��ͬ�������ڼ��ͽ���,
                                            CHARINDEX(''20'',
                                                      ��ͬ�������ڼ��ͽ���),
                                            10), ''.'', ''-''))
                     ELSE NULL
                END ,'
                set @sql21 = '
                CASE WHEN ��ˮ�Ƽ������� IS NOT NULL
                     THEN ''�г�:''
                          + CONVERT(NVARCHAR(20), CONVERT(DECIMAL(10, 2), ��ˮ�Ƽ�������
                          * 10000))
                     ELSE ''''
                END + CASE WHEN F16 IS NOT NULL
                           THEN '' �޳�:''
                                + CONVERT(NVARCHAR(20), CONVERT(DECIMAL(10, 2), F16
                                * 10000))
                           ELSE ''''
                END + CASE WHEN CHARINDEX(''-'',��ͬ��Ч����) > 0 and CHARINDEX(''.'',SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10)) <= 0 and F22 IS null and RTRIM(LTRIM(SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,10))) !=''''
						   THEN '' ��ͬ��ֹʱ��:''+SUBSTRING(��ͬ��Ч����,CHARINDEX(''-'',��ͬ��Ч����)+1,LEN(��ͬ��Ч����))
						   WHEN F22 IS NOT NULL AND CHARINDEX(''.'',F22) <= 0 AND CHARINDEX(''='',F22) <= 0
						   THEN '' ��ͬ��ֹʱ��:''+F22
						   ELSE ''''
				END + CASE WHEN CHARINDEX(''��'',F23) > 0 THEN '' ��ͬ�����ˣ�'' + F23
						   ELSE ''''
				END + CASE WHEN LEN(��Լ��)>60 
						   THEN '' ԭ��˾���ƣ�'' + ��Լ��
					       ELSE ''''
				END
        FROM    dbo.sourceTab
        WHERE   ���2 > 0
                AND ���1 IS NULL'



    DECLARE cur CURSOR  FOR SELECT  table_name FROM #tableName 
    
    OPEN cur
    FETCH NEXT FROM cur INTO @TableName
    
    
    
    WHILE @@fetch_status = 0 
        BEGIN
			
            SET @execSQL1 = REPLACE(@sql1, 'T_year', SUBSTRING(@TableName, 2,4))   --��T_year�滻Ϊ���
            SET @execSQL2 = REPLACE(@sql2, 'T_year', SUBSTRING(@TableName, 2,4))
            
            SET @execSQL1 = REPLACE(@execSQL1, 'divCode',SUBSTRING(@TableName, 7,LEN(@TableName) - 7))
            SET @execSQL2 = REPLACE(@execSQL2, 'divCode',SUBSTRING(@TableName, 7,LEN(@TableName) - 7))
            
            
            
            SET @execSQL11 = REPLACE(@sql11, 'sourceTab', @TableName)   --��sourceTab�滻Ϊ@TableName
            SET @execSQL21 = REPLACE(@sql21, 'sourceTab', @TableName)
            
            
            
            
            
            
            
            
            
            print(@TableName)
			
            EXEC (@sql+@execSQL1+@execSQL11+@execSQL2+@execSQL21)
            FETCH NEXT FROM cur INTO @TableName
        END
    CLOSE cur
    DEALLOCATE cur

                
    UPDATE  #contractFromKZHB
    SET     contract_date = CASE WHEN RIGHT(contract_date, 1) = '-'
                                 THEN LEFT(contract_date,
                                           LEN(contract_date) - 1)
                                 ELSE contract_date
                            END 
	--������һλΪ��-������ȥ��



    UPDATE  #contractFromKZHB
    SET     division_id = div_id
    FROM    #contractFromKZHB ,
            #division
    WHERE   division_code = div_code
    
    --���ò���ID


    CREATE TABLE #company
        (
          sid INT IDENTITY(1, 1) ,
          id INT ,
          NAME NVARCHAR(60)
        )
    
    INSERT  INTO #company
            ( NAME 
            )
            SELECT DISTINCT
                    #contractFromKZHB.company_name
            FROM    #contractFromKZHB ,
                    xmis.xmis.org_��˾
            WHERE   company_name IS NOT NULL
                    AND company_name <> xmis.xmis.org_��˾.��˾����
                    
 
    DECLARE @maxCompID INT
	
	
	
	select @maxCompID = MAX(xmis.xmis.org_��˾.��˾ID) from xmis.xmis.org_��˾
	
	
	
	
	insert into xmis.xmis.org_��˾(��˾ID,��˾����,������д,ҵ���ϵID,�޸���ID,�޸�ʱ��)
	select @maxCompID + sid, NAME, NAME, -1, -1, GETDATE() from #company
	
	
	
	
	update #contractFromKZHB set company_id = @maxCompID + #company.sid 
	from #contractFromKZHB, #company 
	where #contractFromKZHB.company_name = #company.NAME

	update #contractFromKZHB set contarct_manager_id = xmis.xmis.hr_��Ա.��ԱID 
	from #contractFromKZHB, xmis.xmis.hr_��Ա
	where #contractFromKZHB.contract_manager = xmis.xmis.hr_��Ա.��¼��
	
	update #contractFromKZHB set sign_id = xmis.xmis.hr_��Ա.��ԱID 
	from #contractFromKZHB, xmis.xmis.hr_��Ա
	where #contractFromKZHB.sign_name = xmis.xmis.hr_��Ա.��¼��
	
	update #contractFromKZHB set sign_id = -1 where sign_id is null
	update #contractFromKZHB set contract_amt = 0 where contract_amt is null
	
	
	
	
	-- TZ > NY  ���� ��Ϊ ����Դ
	update #contractFromKZHB set division_id = (select d.div_id from #division d where d.div_code = 'NY'),division_code = 'NY' where division_id = 801 and division_code = 'TZ'
	-- WS > JC  ���� ��Ϊ ���
	update #contractFromKZHB set division_id = (select d.div_id from #division d where d.div_code = 'JC'),division_code = 'JC' where division_id = 800 and division_code = 'WS'
	
	--�޸�2011
	--begin_date
	update #contractFromKZHB set begin_date = '2010-12-01' where year = '2011' and  begin_date = '2010-12-'
	
	update #contractFromKZHB set begin_date = '2011-5-01' where year = '2011' and  begin_date = '2011-5-'
	--contract_date
	update #contractFromKZHB set contract_date = '2010-12-30' where  year = '2011' and contract_date = '201012-30'
	update #contractFromKZHB set contract_date = '2011-7-01' where  year = '2011' and contract_date = '2011-7'
	
	update #contractFromKZHB set contract_date = '2011-5-01' where  year = '2011' and contract_date = '2011-5'
	update #contractFromKZHB set contract_date = '2011-8-29' where  year = '2011' and contract_date = '2011-8-296'
	--end_date 
	
	update #contractFromKZHB set end_date = '2013-5-01' where year = '2011' and  end_date = '20113-5-01'
	update #contractFromKZHB set end_date = '2012-5-01' where year = '2011' and  end_date = '5012-5-01'
	--end
	
	
	--�޸�2010
	--begin_date
	update #contractFromKZHB set begin_date = '2010-5-1' where year = '2010' and  begin_date = '2010-5-'
	--contract_date
	update #contractFromKZHB set contract_date = '2010-1-1' where  year = '2010' and contract_date = '2010-1'
	update #contractFromKZHB set contract_date = '2010-4-1' where year = '2010' and  contract_date = '2010-4'
	update #contractFromKZHB set contract_date = '2010-11-1' where year = '2010' and  contract_date = '2010-11'
	update #contractFromKZHB set contract_date = '2010-7-1' where year = '2010' and  contract_date = '2010-7'
	update #contractFromKZHB set contract_date = null,remark = remark + ' �������ڣ�2010.22.25' where year = '2010' and  contract_date = '2010-22-25'
	update #contractFromKZHB set contract_date = '2011-2-28', remark = remark + ' �������ڣ�2011.2.29' where year = '2010' and  contract_date = '2011-2-29'
	update #contractFromKZHB set contract_date = NULL,remark = remark + ' �������ڣ�2010.9.12.4' where year = '2010' and project_code = 'BITC-JC-2010-JS-001'
	update #contractFromKZHB set contract_date = NULL,remark = remark + ' �������ڣ�2010.12.121' where year = '2010' and project_code = 'BITC-TS-2010-JS-023/Q04'
	--end_date
	update #contractFromKZHB set end_date = '2010-12-31' where year = '2010' and  end_date = '2010-01'
	update #contractFromKZHB set end_date = '2011-9-1' where year = '2010' and  end_date = '20119-01'
	update #contractFromKZHB set end_date = '2011-8-1' where year = '2010' and  end_date = '201108-01'
	update #contractFromKZHB set remark = remark + ' ��ͬ��ֹ���ڣ�2010' where year = '2010' and  project_code = 'BITC-SY-2010-JS-005'
	
	--end
	
	--�޸�2009
	--contract_date
	update #contractFromKZHB set contract_date = '2009-4-1' where year = '2009' and  contract_date = '2009-4'
	update #contractFromKZHB set contract_date = '2009-5-1' where year = '2009' and  contract_date = '2009-5'
	update #contractFromKZHB set contract_date = '2009-7-1' where year = '2009' and  contract_date = '2009-7'
	update #contractFromKZHB set contract_date = '2009-8-31',remark = remark + ' �������ڣ�2009.8.32' where year = '2009' and  contract_date = '2009-8-32'
	update #contractFromKZHB set contract_date = null,remark = remark + ' �������ڣ�20101.1.13' where year = '2009' and  contract_date = '20101-1-13'
	update #contractFromKZHB set contract_date = '2009-7-15' where year = '2009' and  contract_date = '209-7-15'
	
	update #contractFromKZHB set contract_date = '2009-9-01' where year = '2009' and  contract_date = '2009-9'
	--begin_date
	update #contractFromKZHB set begin_date = '2009-6-01' where begin_date = '2009-6-'
	--end_date
	update #contractFromKZHB set end_date = '2009-12-01' where year = '2009' and end_date = '22009-12-01'
 	--end
	
	--�޸�2008
	--contract_date
	update #contractFromKZHB set contract_date = '2008-1-1' where year = '2008' and  contract_date = '2008-1'
	update #contractFromKZHB set contract_date = '2008-3-1' where year = '2008' and  contract_date = '2008-3'
	update #contractFromKZHB set contract_date = '2008-4-1' where year = '2008' and  contract_date = '2008-4'
	update #contractFromKZHB set contract_date = '2008-5-1' where year = '2008' and  contract_date = '2008-5'
	update #contractFromKZHB set contract_date = '2008-8-1' where year = '2008' and  contract_date = '2008-8'
	update #contractFromKZHB set contract_date = '2008-9-1' where year = '2008' and  contract_date = '2008-9'
	update #contractFromKZHB set contract_date = '2007-12-1' where year = '2008' and  contract_date = '2007-12'
	update #contractFromKZHB set contract_date = '2010-8-1' where year = '2008' and  contract_date = '2010-8'
	
	update #contractFromKZHB set contract_date = null,remark = remark + ' �������ڣ�2007-15-26' where year = '2008' and  contract_date = '2007-15-26'
	--begin_date
	update #contractFromKZHB set begin_date = '2008-10-1' where year = '2008' and  begin_date = '200810-01'
	update #contractFromKZHB set begin_date = '2008-1-1' where year = '2008' and  begin_date = '28-1-01'
	update #contractFromKZHB set begin_date = '2008-8-1' where year = '2008' and  begin_date = '208-8-01'
	update #contractFromKZHB set begin_date = '2008-5-1' where year = '2008' and  begin_date = '208-5-01'
	update #contractFromKZHB set begin_date = '2008-9-01' where year = '2008' and  begin_date = '208-9-01'
	--end_date
	update #contractFromKZHB set end_date = '2011-3-1' where year = '2008' and  end_date = '3011-3-01'
	update #contractFromKZHB set end_date = null,remark = remark + ' ��ͬ��ֹ���ڣ�2010.' where year = '2008' and  end_date = '2010--01'
	update #contractFromKZHB set remark = remark + ' ��ͬ��ʼ���ڣ�2009' where year = '2008' and  project_code = 'BITC-NY-2008-JS-001/Q12'
	
	update #contractFromKZHB set end_date = null,remark = remark + ' ��ͬ��ֹ���ڣ�2008-13-01' where year = '2008' and  end_date = '2008-13-01'
	--END-2008
	
	--�޸�2007
	--contract_date
	update #contractFromKZHB set contract_date = '2006-11-1' where year = '2007' and  contract_date = '2006-11'
	update #contractFromKZHB set contract_date = '2006-12-1' where year = '2007' and  contract_date = '2006-12'
	update #contractFromKZHB set contract_date = '2007-1-1' where year = '2007' and  contract_date = '2007-1'
	update #contractFromKZHB set contract_date = '2007-3-1' where year = '2007' and  contract_date = '2007-3'
	update #contractFromKZHB set contract_date = '2007-5-1' where year = '2007' and  contract_date = '2007-5'
	update #contractFromKZHB set contract_date = '2007-6-1' where year = '2007' and  contract_date = '2007-6'
	update #contractFromKZHB set contract_date = '2007-8-1' where year = '2007' and  contract_date = '2007-8'
	update #contractFromKZHB set contract_date = '2007-9-1' where year = '2007' and  contract_date = '2007-9'
	update #contractFromKZHB set contract_date = '2007-10-1' where year = '2007' and  contract_date = '2007-10'
	update #contractFromKZHB set contract_date = '2007-11-1' where year = '2007' and  contract_date = '2007-11'
	update #contractFromKZHB set contract_date = '2007-12-1' where year = '2007' and  contract_date = '2007-12'
	update #contractFromKZHB set contract_date = '2008-3-1' where year = '2007' and  contract_date = '2008-3'
	update #contractFromKZHB set contract_date = '2008-8-1' where year = '2007' and  contract_date = '2008-8'
	update #contractFromKZHB set contract_date = '2008-12-1' where year = '2007' and  contract_date = '2008-12'
	update #contractFromKZHB set contract_date = '2008-2-29' where year = '2007' and  contract_date = '2008-2-30'
	update #contractFromKZHB set contract_date = '2008-3-18' where year = '2007' and  contract_date = '2008-318'
	--begin_date
	update #contractFromKZHB set begin_date = '2007-11-21' where year = '2007' and  begin_date = '2007-1121-01'
	update #contractFromKZHB set begin_date = '2007-12-12' where year = '2007' and  begin_date = '207-12-12'
	update #contractFromKZHB set begin_date = '2006-12-8' where year = '2007' and  begin_date = '200612-8-01'
	update #contractFromKZHB set begin_date = '2007-9-22' where year = '2007' and  begin_date = '20079-22-01'
	--end_date
	
	update #contractFromKZHB set end_date = '2008-12-01' where year = '2007' and  end_date = '208-12-01'
	--END
	
	--�޸�2005,06
	--contract_date
	update #contractFromKZHB set contract_date = '2006-6-6' where year = '2006' and  contract_date = '20006-6-6'
	update #contractFromKZHB set contract_date = '2006-7-25' where year = '2006' and  contract_date = '20006-7-25'
	update #contractFromKZHB set contract_date = '2006-11-1' where year = '2006' and  contract_date = '2006-11'
	update #contractFromKZHB set contract_date = '2008-5-1' where year = '2006' and  contract_date = '2008-5'
	update #contractFromKZHB set contract_date = '2006-5-1' where year = '2006' and  contract_date = '2006-05'
	update #contractFromKZHB set contract_date = '2007-1-1' where year = '2006' and  contract_date = '2007-1'
	update #contractFromKZHB set contract_date = '2006-6-1' where year = '2006' and  contract_date = '2006-6'
	update #contractFromKZHB set contract_date = '2005-3-1' where year = '2006' and  contract_date = '2005-3'
	update #contractFromKZHB set contract_date = '2006-8-1' where year = '2006' and  contract_date = '2006-8'
	update #contractFromKZHB set contract_date = '2006-9-1' where year = '2006' and  contract_date = '2006-9'
	update #contractFromKZHB set contract_date = '2007-3-1' where year = '2006' and  contract_date = '2007-3'
	update #contractFromKZHB set contract_date = '2005-12-1' where year = '2006' and  contract_date = '2005-12'
	--begin_date
	update #contractFromKZHB set begin_date = '2007-10-19' where year = '2006' and  begin_date = '2007-1019-01'
	--end_date
	update #contractFromKZHB set end_date = '2006-11-01' where year = '2006' and  end_date = '06-11-01'
	
	update #contractFromKZHB set end_date = '2007-12-5' where year = '2006' and  end_date = '07-12-5'
	update #contractFromKZHB set end_date = '2008-3-1' where year = '2006' and  end_date = '08-3-1'
	update #contractFromKZHB set end_date = '2007-11-30' where year = '2006' and  end_date = '11-30-01'
	update #contractFromKZHB set end_date = '2007-2-28' where year = '2006' and  end_date = '2007-2-30'
	--end
	
	insert into contractFromKZHB_temp
	(
		  year ,
          SID ,
          id,                                                    
          division_id ,                    
          division_code ,        
          division_name ,      
          project_code ,         
          contract_type ,                 
          contract_id ,                    
          contract_code ,         
          CONTRACT_NAME ,       
          contract_amt ,          
          company_name ,        
          company_id ,                
          begin_date ,          
          end_date ,             
          contract_manager ,     
          contarct_manager_id ,       
          contract_date ,      
          remark ,             
          sign_name ,         
          sign_id                  
	)
	
	select 
		  year ,
          SID ,
          id,                                                    
          division_id ,                    
          division_code ,        
          division_name ,      
          project_code ,         
          contract_type ,                 
          contract_id ,                    
          contract_code ,         
          CONTRACT_NAME ,       
          contract_amt ,          
          company_name ,        
          company_id ,                
          begin_date ,          
          end_date ,             
          contract_manager ,     
          contarct_manager_id ,       
          contract_date ,      
          remark ,             
          sign_name ,         
          sign_id from #contractFromKZHB where contract_code in (
	select a.contract_code as code --,COUNT(*) as num 
	from #contractFromKZHB a group by a.contract_code 
	having COUNT(*) > 1 and contract_code is not null) order by contract_code
	
	delete from #contractFromKZHB where contract_code in (
	select a.contract_code as code --,COUNT(*) as num 
	from #contractFromKZHB a group by a.contract_code 
	having COUNT(*) > 1 and contract_code is not null) 
	
	DECLARE @maxContID INT
	select @maxContID = MAX(xmis.xmis.con_��ͬ.��ͬID) from xmis.xmis.con_��ͬ	
	
	update #contractFromKZHB set contract_id = @maxContID + SID
	
	print(@maxContID)
	
	
	
	
	--�����ͬ	
	INSERT INTO xmis.xmis.con_��ͬ
        ( ��ͬID ,
          ��ͬ���� ,
          ��ͬ��� ,
          ��ͬ������ ,
          ��ͬ����ID ,
          ��ͬ�ܶ� ,
          ����ID ,
          �׷���˾ID ,
          �׷�����ID ,
          �׷�����ID ,
          ��� ,
          ǩ������ ,
          �ҷ�����ID ,
          �ҷ�����ID ,
          �ҷ���˾ID ,
          �ʱ����� ,
          �ʱ���ֹ ,
          ��ע ,
          �Ǽ���ID ,
          ����ʱ��
        )
        SELECT  #contractFromKZHB.contract_id ,
                #contractFromKZHB.CONTRACT_NAME ,
                #contractFromKZHB.contract_code ,
                #contractFromKZHB.contarct_manager_id ,
                contract_type,
                #contractFromKZHB.contract_amt ,
                1 ,
                company_id , null, null,
                SUBSTRING(CONTRACT_NAME,0,30) ,
                cast(contract_date as DATETIME),
                division_id ,
                sign_id ,
                1 ,
                cast(begin_date as DATETIME) ,
                cast(end_date as DATETIME) ,
                CASE WHEN LEN(remark)>100 then SUBSTRING(remark,0,100) 
					 else remark
				end ,
                -1 ,
                GETDATE()
        FROM    #contractFromKZHB
        WHERE   contract_type = 1
        UNION
        SELECT  #contractFromKZHB.contract_id ,
                #contractFromKZHB.CONTRACT_NAME ,
                #contractFromKZHB.contract_code ,
                #contractFromKZHB.contarct_manager_id ,
                contract_type ,
                #contractFromKZHB.contract_amt ,
                1 ,
                1 , division_id, sign_id,
                SUBSTRING(CONTRACT_NAME,0,30) ,
                cast(contract_date as DATETIME),
                null ,
                null ,
                company_id ,
                cast(begin_date as DATETIME) ,
                cast(end_date as DATETIME) ,
                CASE WHEN LEN(remark)>100 then SUBSTRING(remark,0,100) 
					 else remark
				end ,
                -1 ,
                GETDATE()
        FROM    #contractFromKZHB
        WHERE   contract_type = 2
        
        
    update #contractFromKZHB set project_id = 522 + SID
	
	INSERT INTO xmis.xmis.prj_��Ŀ
		([��ĿID]
        ,[��Ŀ����]
        ,[��Ŀ��ͬID]
        ,[��������]
        ,[��Ŀ״̬ID]
        ,[��Ŀ����ID]
        ,[��Ŀ����]
        ,[��Ŀ����ID]
        ,[������ID]
        ,[����ʱ��]
	    )
	
	select project_id + ''
        ,project_code
        ,contract_id
        ,cast(begin_date as DATETIME)
        ,-1
        ,null
        ,SUBSTRING(CAST(CONTRACT_NAME as varchar(100)),0,100)
        
        ,null
        ,-1
        ,GETDATE()
	from #contractFromKZHB
	

	
	
	create table #contractRelation(
		SID INT IDENTITY(1, 1),
		��ӦID int,
		sr_contract_id int,
		zhch_contract_id int ,
		amt FLOAT,
		֧���Ӻ�ͬID int
		);	
	
	insert into #contractRelation(
			sr_contract_id,
			zhch_contract_id,
			amt
	)
	select sr.contract_id,zhch.contract_id,zhch.contract_amt from 
	(select contract_id,contract_code from #contractFromKZHB where CHARINDEX('/Q',contract_code) <= 0 and CHARINDEX('/W',contract_code) <= 0) sr
	,(select contract_id,contract_code,contract_amt from #contractFromKZHB where CHARINDEX('/Q',contract_code) > 0 or CHARINDEX('/W',contract_code) > 0) zhch
	where sr.contract_code = SUBSTRING(zhch.contract_code,0,CHARINDEX('/',zhch.contract_code)) 
	
	DECLARE @maxContRelationID INT
	select @maxContRelationID = MAX(xmis.xmis.con_����֧����ͬ��Ӧ��.��ӦID) from xmis.xmis.con_����֧����ͬ��Ӧ��
	update #contractRelation set ��ӦID = @maxContRelationID + SID
	
	DECLARE @minContID INT
	select @minContID = min(xmis.xmis.con_��ͬ.��ͬID) from xmis.xmis.con_��ͬ
	update #contractRelation set ֧���Ӻ�ͬID = @minContID - SID
	
	INSERT INTO xmis.xmis.con_��ͬ
        ( ��ͬID ,
          ��ͬ���� ,
          ��ͬ��� ,
          ��ͬ������ ,
          ��ͬ����ID ,
          ��ͬ�ܶ� ,
          ����ID ,
          �׷���˾ID ,
          �׷�����ID ,
          �׷�����ID ,
          ��� ,
          ǩ������ ,
          �ҷ�����ID ,
          �ҷ�����ID ,
          �ҷ���˾ID ,
          �ʱ����� ,
          �ʱ���ֹ ,
          ��ע ,
          �Ǽ���ID ,
          ����ʱ�� ,
          ����ͬID
        )
        
        select #contractRelation.֧���Ӻ�ͬID,
			   zhch.CONTRACT_NAME,
			   zhch.contract_code + '-' + cast(zhch.contract_amt as varchar),
			   zhch.contarct_manager_id,
			   zhch.contract_type,
			   zhch.contract_amt,
			   1,
			   1,
			   zhch.division_id,
			   zhch.sign_id,
			   SUBSTRING(zhch.CONTRACT_NAME,0,30) ,
			   cast(zhch.contract_date as DATETIME),
			   null ,
               null ,
               zhch.company_id,
               cast(zhch.begin_date as DATETIME) ,
               cast(zhch.end_date as DATETIME) ,
               CASE WHEN LEN(zhch.remark)>100 then SUBSTRING(zhch.remark,0,100) 
					 else zhch.remark
			   end ,
               -1 ,
               GETDATE(),
               #contractRelation.zhch_contract_id
		from 
		(select * from #contractFromKZHB where CHARINDEX('/Q',contract_code) > 0 or CHARINDEX('/W',contract_code) > 0) as zhch,
		#contractRelation
		where #contractRelation.zhch_contract_id = zhch.contract_id
        
		select * from #contractRelation
		
		insert into xmis.xmis.con_����֧����ͬ��Ӧ��(
		[�����ͬID]
		,[֧����ͬID]
		,[��ӦID]
		,[���]
		,[��ע]
		,[֧���Ӻ�ͬID]
		 )
		 select 
		 sr_contract_id,
		 zhch_contract_id,
		 ��ӦID,
		 amt,
		 null,
		 ֧���Ӻ�ͬID
		 from #contractRelation
		 
      	end
               
               
	UPDATE xmis.con_��ͬ SET ��ĿID = xmis.prj_��Ŀ.��ĿID FROM xmis.con_��ͬ, xmis.prj_��Ŀ 
	WHERE xmis.con_��ͬ.��ĿID IS NULL AND xmis.con_��ͬ.��ͬID = xmis.prj_��Ŀ.��Ŀ��ͬID
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	