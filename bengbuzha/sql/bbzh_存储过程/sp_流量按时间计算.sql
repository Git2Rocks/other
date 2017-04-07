USE bbz
go
IF OBJECT_ID('sp_getLiulangTotalValue') IS NOT NULL 
    BEGIN
        DROP PROCEDURE sp_getLiulangTotalValue
    END
GO
CREATE PROCEDURE sp_getLiulangTotalValue
    (
      @begDate CHAR(10) ,
      @endDate CHAR(10) ,
      @floodgateType SMALLINT 
    )
AS 
    BEGIN 

        DECLARE @ve DECIMAL(9, 4)
        SET @ve = 0
		SET NOCOUNT ON 
        DECLARE @waterHeadPrep DECIMAL(18, 4) --ˮͷϵ��
        DECLARE @ditchWide DECIMAL(18, 4) --����
        DECLARE @netWidePrep SMALLINT --����ϵ��
        DECLARE @yiQiangR DECIMAL(18, 2) --��ǽ�뾶
		
        DECLARE @kongLiuYanLiuStates DECIMAL(18, 3) --���������жϱ�־
        DECLARE @yanMoChuLiuZiYouChuLiuStates DECIMAL(18, 3) --���ɳ�������û�����жϱ�־
		
        DECLARE @liuLiangXiShu DECIMAL(18, 4) --����ϵ����ֵ


        DECLARE @elecXiShu DECIMAL(18,4)		--�������ϵ��
        
        --IF @floodgateType = 12 
			--12��բ ��������
        BEGIN
            SET @waterHeadPrep = 9
            SET @ditchWide = 141.7 + 12.65 * 2
            SET @netWidePrep = 10
            SET @yiQiangR = 30
                
            SET @kongLiuYanLiuStates = 0.65
            SET @yanMoChuLiuZiYouChuLiuStates = 0.8
            SET @liuLiangXiShu = 0.951
                
            SELECT  tab_seed ,
                    measure_date ,
                    ap_w_level AS ����ˮλ ,					--A2
                    bp_w_level AS ����ˮλ ,					--B2
                    gate_open_degree_2 AS ���� ,				--C2
                    gate_open_num_2 AS �������� ,				--D2
                    ap_w_level - @waterHeadPrep AS բ��ˮͷ ,	--E2
                    bp_w_level - @waterHeadPrep AS բ��ˮͷ ,	--F2
                    @ditchWide AS ���� ,						--G2
                    gate_open_num_2 * @netWidePrep AS ���� ,	--H2
                    @yiQiangR ��ǽ�뾶 ,						--I2
                    gate_open_degree_2 / ( ap_w_level - @waterHeadPrep ) ���������ж�ֵ ,	--B5/B6
                    ( bp_w_level - @waterHeadPrep ) / ( ap_w_level
                                                        - @waterHeadPrep ) ��û�������ɳ����ж�ֵ	--E5/E6
            INTO    #waterLevel_1
            FROM    xmis.gczl_water_level_info
            WHERE   measure_date < DATEADD(D, 1, @endDate)
                    AND measure_date >= @begDate
                    AND gate_open_num_2 > 0		--��բ��ˮ
                    AND gate_open_degree_2 > 0
                
            SELECT  * ,
                    CASE WHEN ���������ж�ֵ >= @kongLiuYanLiuStates THEN '����'
                         ELSE '����'
                    END AS ����������ж� ,														--
                    CASE WHEN ���������ж�ֵ >= @kongLiuYanLiuStates THEN 10
                         ELSE 20
                    END AS ������������� ,														--
                    CASE WHEN ��û�������ɳ����ж�ֵ >= @yanMoChuLiuZiYouChuLiuStates
                         THEN '��û����'
                         ELSE '���ɳ���'
                    END AS ��û�������ɳ����ж� ,												--
                    CASE WHEN ��û�������ɳ����ж�ֵ >= @yanMoChuLiuZiYouChuLiuStates
                         THEN 3
                         ELSE 5
                    END AS ��û�������ɳ������� ,												--
                    ��ǽ�뾶 / ���� AS [r/B] ,													--C9/C12
                    ���� / ���� AS [B/Bo] ,														--D9/D12
                    xmis.f_getWuKanKuanDingYanLiuLangXiShu(��ǽ�뾶 / ����, ���� / ����,
                                                           'r/B') AS [mֵ] ,		--E9/E12
                    բ��ˮͷ / բ��ˮͷ AS [hs/Ho] ,												--F9
                    xmis.f_getWuKanKuanDingYanLiuLangXiShu(բ��ˮͷ / բ��ˮͷ, 0,
                                                           'null') AS [������ûϵ����ֵ] ,		--G9
                    ���������ж�ֵ AS [e/H] ,													--C15
                    xmis.f_getVerticalShrikCoefficient(���������ж�ֵ) AS [��ֱ����ϵ����ֵ] 	--D15
            INTO    #waterLevel_2
            FROM    #waterLevel_1
                        
				
            SELECT  * ,
                    ���� * [��ֱ����ϵ����ֵ] AS [��������ˮ��hc] ,								--E15
                    @liuLiangXiShu * [��ֱ����ϵ����ֵ] AS [����ϵ����ֵ] 						--F15
            INTO    #waterLevel_3
            FROM    #waterLevel_2
                
            SELECT  * ,
                    @liuLiangXiShu * SQRT(2 * 9.8 * ( բ��ˮͷ - ��������ˮ��hc )) AS [Vc] 		--H15
            INTO    #waterLevel_4
            FROM    #waterLevel_3
                
                
            SELECT  * ,
                    [��������ˮ��hc] * 0.5 * ( SQRT(1 + 8 * [Vc] * [Vc] / ( 9.8
                                                              * [��������ˮ��hc] ))
                                         - 1 ) AS [hc"(hc"��hs)] 								--I15
            INTO    #waterLevel_5
            FROM    #waterLevel_4
                                             
				
            SELECT  * ,
                    ( բ��ˮͷ - [hc"(hc"��hs)] ) / ( բ��ˮͷ - [hc"(hc"��hs)] ) AS Ǳ���� 		--J15
            INTO    #waterLevel_6
            FROM    #waterLevel_5
                
            SELECT  * ,
                    xmis.f_getZhaKongYanMoXiShu(Ǳ����) AS [��ֵ] ,								--K15
                    0.6 - 0.176 * CONVERT(DECIMAL(18, 10), ���� / բ��ˮͷ) AS [����������ϵ����ֵ]	--F22
            INTO    #waterLevel_7
            FROM    #waterLevel_6
				
            SELECT  * ,
                    ����������ж� + ��û�������ɳ����ж� AS �������� ,
                    CASE ������������� + ��û�������ɳ�������
                      WHEN 13
                      THEN 
							/*
							������û���� 
							Q=��m��B(2g)^0.5H^1.5
							=E9*G9*H2*(2*9.8)^0.5*E2^1.5
							*/ [mֵ] * [������ûϵ����ֵ] * ���� * SQRT(2 * 9.8)
                           * POWER(բ��ˮͷ, 1.5)
                      WHEN 15 THEN 
							/*
							�������ɳ���
							Q=��mB(2g)^0.5H^1.5
							=E12*H2*(2*9.8)^0.5*E2^1.5
							*/ [mֵ] * ���� * SQRT(2 * 9.8) * POWER(բ��ˮͷ, 1.5)
                      WHEN 23
                      THEN 
							/*
							������û����
							Q=�Ҧ�Be(2gH)^0.5
							=K15*F15*H2*C2*SQRT(2*9.8*E2)
							*/ [��ֵ] * [����ϵ����ֵ] * ���� * ���� * SQRT(2 * 9.8 * բ��ˮͷ)
                      WHEN 25 THEN 
							/*
							�������ɳ���
							Q=��Be(2gH)^0.5
							=F22*E22*D22*SQRT(2*9.8*C22)
							*/ [����������ϵ����ֵ] * ���� * ���� * SQRT(2 * 9.8 * բ��ˮͷ)
                    END AS ����
            INTO    #waterLevel_8
            FROM    #waterLevel_7

			--28��բ����
            SELECT  tab_seed ,
                    measure_date ,
                    ap_w_level AS ����ˮλ ,					--A2
                    bp_w_level AS ����ˮλ ,					--B2
                    gate_open_degree_1 AS ���� ,				--C2
                    gate_open_num_1 AS �������� ,				--D2
                    ap_w_level - @waterHeadPrep AS բ��ˮͷ ,	--E2
                    bp_w_level - @waterHeadPrep AS բ��ˮͷ ,	--F2
                    gate_open_num_1 * xmis.f_get28SingleValue(ap_w_level,
                                                              bp_w_level,
                                                              gate_open_degree_1) AS ����
            INTO    #waterLevel_9
            FROM    xmis.gczl_water_level_info
            WHERE   measure_date < DATEADD(D, 1, @endDate)
                    AND measure_date >= @begDate
                    AND gate_open_num_1 > 0		--��բ��ˮ
                    AND gate_open_degree_1 > 0
                    
			--��վ����
			SET @elecXiShu = 25
			
            SELECT  tab_seed ,
                    measure_date ,
                    ap_w_level AS ����ˮλ ,					--A2
                    bp_w_level AS ����ˮλ ,					--B2
                    gate_open_degree_1 AS ���� ,				--C2
                    gate_open_num_1 AS �������� ,				--D2
                    ap_w_level - @waterHeadPrep AS բ��ˮͷ ,	--E2
                    bp_w_level - @waterHeadPrep AS բ��ˮͷ ,	--F2
                    elec_machine AS ����� ,
                    CONVERT(DECIMAL(18,2), @elecXiShu * elec_machine) AS ��վ����
            INTO #waterLevel_10
            FROM xmis.gczl_water_level_info WHERE elec_machine >0
			
                
            IF @begDate = @endDate 
                BEGIN
                
                    SELECT  CONVERT(NVARCHAR(100), NULL) AS A ,
                            CONVERT(NVARCHAR(100), NULL) AS B ,
                            CONVERT(NVARCHAR(100), NULL) AS C ,
                            CONVERT(NVARCHAR(100), NULL) AS D ,
                            CONVERT(NVARCHAR(100), NULL) AS E ,
                            CONVERT(NVARCHAR(100), NULL) AS F ,
                            CONVERT(NVARCHAR(100), NULL) AS G ,
                            CONVERT(NVARCHAR(100), NULL) AS H ,
                            CONVERT(NVARCHAR(100), NULL) AS I ,
                            CONVERT(NVARCHAR(100), NULL) AS J ,
                            CONVERT(NVARCHAR(100), NULL) AS K ,
                            CONVERT(NVARCHAR(100), NULL) AS L
                    INTO    #water_Temp
                       
					
                    IF EXISTS ( SELECT  1
                                FROM    #waterLevel_8
                                WHERE   CONVERT(CHAR(10), measure_date, 23) = @begDate ) 
                        BEGIN
                            INSERT  INTO #water_Temp
                                    SELECT  '<font color=red>12��բ������ϸ</font>' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  '����ˮλ' ,
                                            '����ˮλ' ,
                                            '����e' ,
                                            '��������n' ,
                                            'բ��ˮͷH' ,
                                            'բ��ˮͷh' ,
                                            '����B' ,
                                            '����b' ,
                                            '��ǽ�뾶r' ,
                                            '' ,
                                            '' ,
                                            ''
                                    UNION ALL
                                    SELECT  CONVERT(NVARCHAR(50), ����ˮλ) ,
                                            CONVERT(NVARCHAR(50), ����ˮλ) ,
                                            CONVERT(NVARCHAR(50), ����) ,
                                            CONVERT(NVARCHAR(50), ��������) ,
                                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), բ��ˮͷ)) ,
                                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), բ��ˮͷ)) ,
                                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), ����)) ,
                                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), ����)) ,
                                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), ��ǽ�뾶)) ,
                                            '' ,
                                            '' ,
                                            ''
                                    FROM    #waterLevel_8
                                    UNION ALL
                                    SELECT  '' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  '' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  CASE �������������
                                              WHEN 10 THEN '����'
                                              ELSE '����'
                                            END ,
                                            'e/H' ,
                                            '' ,
                                            '' ,
                                            '' ,
                                            CASE ��û�������ɳ�������
                                              WHEN 3 THEN '��û����'
                                              ELSE '���ɳ���'
                                            END ,
                                            'hs/Ho' ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    FROM    #waterLevel_8
                                    UNION ALL
                                    SELECT  CASE �������������
                                              WHEN 10 THEN 'e/H��0.65'
                                              ELSE 'e/H��0.65'
                                            END ,
                                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), ���������ж�ֵ)) ,
                                            '' ,
                                            '' ,
                                            '' ,
                                            CASE ��û�������ɳ�������
                                              WHEN 3 THEN 'hs/Ho��0.8'
                                              ELSE 'hs/Ho��0.8'
                                            END ,
                                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), ��û�������ɳ����ж�ֵ)) ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    FROM    #waterLevel_8
                                    UNION ALL
                                    SELECT  '' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  '' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  '��������' ,
                                            '���㹫ʽ' ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   'r/B'
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   'r/B'
                                              WHEN 23 THEN 
									--������û����
                                                   'e/H'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   'բ��ˮͷH'
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   'b/Bo'
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   'b/Bo'
                                              WHEN 23 THEN 
									--������û����
                                                   '��ֱ����ϵ����ֵ'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   '����e'
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   '��mֵ'
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   '��mֵ'
                                              WHEN 23 THEN 
									--������û����
                                                   '��������ˮ��hc'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   '����B'
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   'hs/Ho'
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   '����'
                                              WHEN 23 THEN 
									--������û����
                                                   '����ϵ����ֵ'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   '����ϵ����ֵ'
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   '���ֵ'
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23 THEN 
									--������û����
                                                   'բ��ˮͷH'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   '����'
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   '����'
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23 THEN 
									--������û����
                                                   'Vc'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   ''
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23 THEN 
									--������û����
                                                   'hc"(hc"��hs)'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   ''
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23 THEN 
									--������û����
                                                   'Ǳ����'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   ''
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23 THEN 
									--������û����
                                                   '���ֵ'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   ''
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23 THEN 
									--������û����
                                                   '����'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END
                                    FROM    #waterLevel_8
                                    UNION ALL
                                    SELECT  �������� ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   'Q=��m��B(2g)^0.5H^1.5'
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   'Q=��mB(2g)^0.5H^1.5'
                                              WHEN 23 THEN 
									--������û����
                                                   'Q=�Ҧ�Be(2gH)^0.5'
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   'Q=��Be(2gH)^0.5'
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13
                                              THEN 
									--������û���� 
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), [r/B]))
                                              WHEN 15
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), [r/B]))
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), [e/H]))
                                              WHEN 25
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), բ��ˮͷ))
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13
                                              THEN 
									--������û���� 
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), [B/Bo]))
                                              WHEN 15
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), [B/Bo]))
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(9,
                                                              4), [��ֱ����ϵ����ֵ]))
                                              WHEN 25
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), ����))
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13
                                              THEN 
									--������û���� 
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(9,
                                                              3), [mֵ]))
                                              WHEN 15
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(9,
                                                              3), [mֵ]))
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(9,
                                                              3), [��������ˮ��hc]))
                                              WHEN 25
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), ����))
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13
                                              THEN 
									--������û���� 
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), [hs/Ho]))
                                              WHEN 15
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              4), ����))
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(9,
                                                              6), [����ϵ����ֵ]))
                                              WHEN 25
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(9,
                                                              6), [����������ϵ����ֵ]))
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13
                                              THEN 
									--������û���� 
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), [������ûϵ����ֵ]))
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), բ��ˮͷ))
                                              WHEN 25
                                              THEN 
									--�������ɳ���
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              4), ����))
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13
                                              THEN 
									--������û����
                                                   CASE WHEN [hs/Ho] > 0.98
                                                        THEN '<font color=red> hs/Ho��0.98,�޷���������</font>'
                                                        ELSE CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              4), ����))
                                                   END
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(9,
                                                              6), [Vc]))
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   ''
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), [hc"(hc"��hs)]))
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   ''
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(5,
                                                              2), Ǳ����))
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   ''
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(9,
                                                              3), [��ֵ]))
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END ,
                                            CASE ������������� + ��û�������ɳ�������
                                              WHEN 13 THEN 
									--������û���� 
                                                   ''
                                              WHEN 15 THEN 
									--�������ɳ���
                                                   ''
                                              WHEN 23
                                              THEN 
									--������û����
                                                   CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              4), ����))
                                              WHEN 25 THEN 
									--�������ɳ���
                                                   ''
                                            END
                                    FROM    #waterLevel_8
                        END
                        
                    IF EXISTS ( SELECT  1
                                FROM    #waterLevel_9
                                WHERE   CONVERT(CHAR(10), measure_date, 23) = @begDate ) 
                        BEGIN
                            INSERT  INTO #water_Temp
                                    SELECT  '' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  '' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  '<font color=red>28��բ����:</font>' ,
                                            ���� ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    FROM    #waterLevel_9
                                    WHERE   CONVERT(CHAR(10), measure_date, 23) = @begDate
                                    UNION ALL
                                    SELECT  '' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  '' AS A ,
                                            '' AS B ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    UNION ALL
                                    SELECT  '<font color=red>��վ����:</font>' ,
                                            ��վ���� ,
                                            '' AS C ,
                                            '' AS D ,
                                            '' AS E ,
                                            '' AS F ,
                                            '' AS G ,
                                            '' AS H ,
                                            '' AS I ,
                                            '' AS J ,
                                            '' AS K ,
                                            '' AS L
                                    FROM    #waterLevel_10
                                    WHERE   CONVERT(CHAR(10), measure_date, 23) = @begDate
                        END
                        
                    SELECT  *
                    FROM    #water_Temp
					
                END
            ELSE 
                BEGIN
					
					
                    SELECT  w_8.tab_seed, CONVERT(CHAR(10), w_8.measure_date, 23) ���� ,
                            w_8.����ˮλ ,
                            w_8.����ˮλ ,
                            w_8.���� AS [12��բ����] ,
                            w_8.�������� AS [12��բ��������] ,
                            w_9.���� AS [28��բ����] ,
                            w_9.�������� AS [28��բ��������] ,
                            CONVERT(DECIMAL(5, 2), w_8.բ��ˮͷ) AS բ��ˮͷ ,
                            CONVERT(DECIMAL(5, 2), w_8.բ��ˮͷ) AS բ��ˮͷ ,
                            w_8.�������� AS [12��բ��������] ,
                            CASE WHEN [hs/Ho] > 0.98
                                 THEN '<font color=red> hs/Ho��0.98,�޷���������</font>'
                                 ELSE CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              2), w_8.����))
                            END AS [12��բ����] ,
                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18, 2), w_9.����)) AS [28��բ����] ,
                            CASE WHEN [hs/Ho] > 0.98
                                 THEN CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              2), w_9.����))
                                 ELSE CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              2), ( w_8.����
                                                              + w_9.���� )))
                            END AS ������
					INTO #waterLevel_11                            
                    FROM    #waterLevel_8 AS w_8 ,
                            #waterLevel_9 AS w_9
                    WHERE   w_8.tab_seed = w_9.tab_seed
                    UNION
                    SELECT  w_8.tab_seed, CONVERT(CHAR(10), w_8.measure_date, 23) ���� ,
                            w_8.����ˮλ ,
                            w_8.����ˮλ ,
                            w_8.���� AS [12��բ����] ,
                            w_8.�������� AS [12��բ��������] ,
                            NULL AS [28��բ����] ,
                            NULL AS [28��բ��������] ,
                            CONVERT(DECIMAL(5, 2), w_8.բ��ˮͷ) AS բ��ˮͷ ,
                            CONVERT(DECIMAL(5, 2), w_8.բ��ˮͷ) AS բ��ˮͷ ,
                            w_8.�������� AS [12��բ��������] ,
                            CASE WHEN [hs/Ho] > 0.98
                                 THEN '<font color=red> hs/Ho��0.98,�޷���������</font>'
                                 ELSE CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              2), w_8.����))
                            END AS [12��բ����] ,
                            NULL AS [28��բ����] ,
                            CASE WHEN [hs/Ho] > 0.98
                                 THEN '<font color=red> hs/Ho��0.98,�޷���������</font>'
                                 ELSE CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              2), ( w_8.���� )))
                            END AS ������
                    FROM    #waterLevel_8 AS w_8 ,
                            #waterLevel_9 AS w_9
                    WHERE   w_8.tab_seed NOT IN ( SELECT    tab_seed
                                                  FROM      #waterLevel_9 )
                    UNION
                    SELECT  w_9.tab_seed, CONVERT(CHAR(10), w_9.measure_date, 23) ���� ,
                            w_9.����ˮλ ,
                            w_9.����ˮλ ,
                            NULL AS [12��բ����] ,
                            NULL AS [12��բ��������] ,
                            w_9.���� AS [28��բ����] ,
                            w_9.�������� AS [28��բ��������] ,
                            CONVERT(DECIMAL(5, 2), w_9.բ��ˮͷ) AS բ��ˮͷ ,
                            CONVERT(DECIMAL(5, 2), w_9.բ��ˮͷ) AS բ��ˮͷ ,
                            NULL AS [12��բ��������] ,
                            NULL AS [12��բ����] ,
                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18, 2), w_9.����)) AS [28��բ����] ,
                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18, 2), ( w_9.���� ))) AS ������
                    FROM    #waterLevel_8 AS w_8 ,
                            #waterLevel_9 AS w_9
                    WHERE   w_9.tab_seed NOT IN ( SELECT    tab_seed
                                                  FROM      #waterLevel_8 )
                    --ORDER BY ���� DESC
                    
                    SELECT  w_11.���� ,
							w_11.����ˮλ,
							w_11.����ˮλ,
                            w_11.[12��բ����] ,
                            w_11.[12��բ��������] ,
                            w_11.[28��բ����] ,
                            w_11.[28��բ��������] ,
                            w_10.�����,
                            w_11.բ��ˮͷ ,
                            w_11.բ��ˮͷ ,
                            w_11.[12��բ��������] ,
                            w_11.[12��բ����] ,
                            w_11.[28��բ����] ,
                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18, 2),w_10.��վ����)) AS ��վ����,
                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18, 2),������+w_10.��վ����)) AS ������
                    FROM #waterLevel_11 w_11, #waterLevel_10 w_10
                    WHERE w_11.tab_seed = w_10.tab_seed
                    UNION 
                    SELECT  w_11.���� ,
							w_11.����ˮλ,
							w_11.����ˮλ,
                            w_11.[12��բ����] ,
                            w_11.[12��բ��������] ,
                            w_11.[28��բ����] ,
                            w_11.[28��բ��������] ,
                            NULL AS �����,
                            w_11.բ��ˮͷ ,
                            w_11.բ��ˮͷ ,
                            w_11.[12��բ��������] ,
                            w_11.[12��բ����] ,
                            w_11.[28��բ����] ,
                            NULL ��վ����,
                            w_11.������
                    FROM #waterLevel_11 w_11, #waterLevel_10 w_10
                    WHERE w_11.tab_seed NOT IN (SELECT tab_seed FROM  #waterLevel_10)
                    UNION 
                    SELECT  CONVERT(CHAR(10), w_10.measure_date, 23) ,
							w_10.����ˮλ,
							w_10.����ˮλ,
                            NULL [12��բ����] ,
                            NULL [12��բ��������] ,
                            NULL [28��բ����] ,
                            NULL [28��բ��������] ,
                            w_10.�����,
                            CONVERT(DECIMAL(5, 2), w_10.բ��ˮͷ) AS բ��ˮͷ ,
                            CONVERT(DECIMAL(5, 2), w_10.բ��ˮͷ) AS բ��ˮͷ ,
                            NULL [12��բ��������] ,
                            NULL [12��բ����] ,
                            NULL [28��բ����] ,
                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18, 2),w_10.��վ����)) as ��վ����,
                            CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18, 2),w_10.��վ����)) AS ������
                    FROM #waterLevel_11 w_11, #waterLevel_10 w_10 
                    WHERE w_10.tab_seed NOT IN (SELECT tab_seed FROM  #waterLevel_11)
                    ORDER BY ���� DESC
                    
                    
					
                END
			
        END
        --ELSE
			--28��բ ��������
          --  BEGIN
            --    RETURN NULL
          --  END
			
        --RETURN @ve
    END



		/*
select sqrt(2*9.8) 
select 43.56*sqrt(2*9.8)  *power(8.11000,1.5)

select power(8.11000,1.5)

SELECT * FROM xmis.gczl_llgsh_��Եƽ��բ�Ŵ�������ϵ��


		
		*/

--SELECT  0.951 * SQRT(2 * 9.8 * ( 8.11 - 2.576 ))

--xmis.sp_getLiulangTotalValue '2010-09-17','2015-09-17',12
--xmis.sp_getLiulangTotalValue '2014-05-05','2014-05-05',12
--xmis.sp_getLiulangTotalValue '2013-09-28','2013-09-28',12
--xmis.sp_getLiulangTotalValue '2011-11-21','2011-11-21',12


    