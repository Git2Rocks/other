USE bbz
go
IF OBJECT_ID('sp_getLiulangValue') IS NOT NULL 
    BEGIN
        DROP PROCEDURE sp_getLiulangValue
    END
GO
CREATE PROCEDURE sp_getLiulangValue
    (
      @ap_w_level DECIMAL(5, 3) ,			--բ��ˮλ
      @bp_w_level DECIMAL(5, 3) ,			--բ��ˮλ
      @gate_open_degree_2 DECIMAL(5, 3) ,	--12��բ����
      @gate_open_num_2 DECIMAL(5, 3) ,		--12��բ��������
      @gate_open_degree_1 DECIMAL(5, 3) , 	--28��բ����
      @gate_open_num_1 DECIMAL(5, 3),		--28��բ��������
      @elec_machine INT						--��� ����
      --@ve NVARCHAR(500) OUTPUT
    )
AS 
    BEGIN 
		
		
        DECLARE @waterHeadPrep DECIMAL(18, 4) --ˮͷϵ��
        DECLARE @ditchWide DECIMAL(18, 4) --����
        DECLARE @netWidePrep SMALLINT --����ϵ��
        DECLARE @yiQiangR DECIMAL(18, 2) --��ǽ�뾶
		
        DECLARE @kongLiuYanLiuStates DECIMAL(18, 3) --���������жϱ�־
        DECLARE @yanMoChuLiuZiYouChuLiuStates DECIMAL(18, 3) --���ɳ�������û�����жϱ�־
		
        DECLARE @liuLiangXiShu DECIMAL(18, 4) --����ϵ����ֵ
        
        DECLARE @elecXiShu DECIMAL(18,4)		--�������ϵ��
        DECLARE @elecLiuLiang DECIMAL(18,4)		--��վ����
        
        SET @waterHeadPrep = 9
        SET @ditchWide = 141.7 + 12.65 * 2
        SET @netWidePrep = 10
        SET @yiQiangR = 30
                
        SET @kongLiuYanLiuStates = 0.65
        SET @yanMoChuLiuZiYouChuLiuStates = 0.8
        SET @liuLiangXiShu = 0.951
        
        SET @elecXiShu = 25
		SET @elecLiuLiang = @elec_machine * @elecXiShu
        
        
        IF ( @ap_w_level = 0
             OR @bp_w_level = 0
           ) 
            BEGIN
                SELECT  '0' AS ����
                RETURN
            END
        ELSE 
            IF ( @gate_open_degree_2 <> 0
                 AND @gate_open_num_2 <> 0
               ) 
                BEGIN
                    SELECT  --measure_date ,
                            @ap_w_level AS ����ˮλ ,					--A2
                            @bp_w_level AS ����ˮλ ,					--B2
                            @gate_open_degree_2 AS ���� ,				--C2
                            @gate_open_num_2 AS �������� ,				--D2
                            @ap_w_level - @waterHeadPrep AS բ��ˮͷ ,	--E2
                            @bp_w_level - @waterHeadPrep AS բ��ˮͷ ,	--F2
                            @ditchWide AS ���� ,						--G2
                            @gate_open_num_2 * @netWidePrep AS ���� ,	--H2
                            @yiQiangR ��ǽ�뾶 ,						--I2
                            @gate_open_degree_2 / ( @ap_w_level
                                                    - @waterHeadPrep ) ���������ж�ֵ ,	--B5/B6
                            ( @bp_w_level - @waterHeadPrep ) / ( @ap_w_level
                                                              - @waterHeadPrep ) ��û�������ɳ����ж�ֵ	--E5/E6
                    INTO    #waterLevel_1
                
                
                    SELECT  * ,
                            CASE WHEN ���������ж�ֵ >= @kongLiuYanLiuStates
                                 THEN '����'
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
                            xmis.f_getWuKanKuanDingYanLiuLangXiShu(��ǽ�뾶 / ����,
                                                              ���� / ����, 'r/B') AS [mֵ] ,		--E9/E12
                            բ��ˮͷ / բ��ˮͷ AS [hs/Ho] ,												--F9
                            xmis.f_getWuKanKuanDingYanLiuLangXiShu(բ��ˮͷ / բ��ˮͷ,
                                                              0, 'null') AS [������ûϵ����ֵ] ,		--G9
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
                            [��������ˮ��hc] * 0.5 * ( SQRT(1 + 8 * [Vc] * [Vc]
                                                      / ( 9.8 * [��������ˮ��hc] ))
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

		
                    SELECT  CASE WHEN [hs/Ho] > 0.98
                                 THEN CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              0), @gate_open_num_1
                                      * ( xmis.f_get28SingleValue(@ap_w_level,
                                                              @bp_w_level,
                                                              @gate_open_degree_1) )+ @elecLiuLiang) )
                                 ELSE CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18,
                                                              0), ( ����
                                                              + @gate_open_num_1
                                                              * xmis.f_get28SingleValue(@ap_w_level,
                                                              @bp_w_level,
                                                              @gate_open_degree_1) + @elecLiuLiang)))
                            END AS ����
                    FROM    #waterLevel_8				
					
					return
					
                END
            ELSE 
                IF ( @gate_open_degree_2 = 0
                     OR @gate_open_num_2 = 0
                   ) 
                    BEGIN
                        SELECT  CONVERT(NVARCHAR(50), CONVERT(DECIMAL(18, 0), @gate_open_num_1
                                * ( xmis.f_get28SingleValue(@ap_w_level,
                                                            @bp_w_level,
                                                            @gate_open_degree_1) )+ @elecLiuLiang))  AS ����
						RETURN 
                    END

                
		
        --RETURN @ve
    END



		/*

DECLARE @vde NVARCHAR(100)

EXEC xmis.sp_getLiulangValue 17.09,17.05,99,12,@vde OUTPUT

SELECT @vde

		*/


--xmis.sp_getLiulangValue 18.53,14.05,1.1,12,0.3,28,2
--xmis.sp_getLiulangValue 0,14.05,1.1,12,0.3,28
--xmis.sp_getLiulangValue 18.53,14.05,0,12,0.3,28
--xmis.sp_getLiulangValue 18.53,14.05,1.1,12,0,28






