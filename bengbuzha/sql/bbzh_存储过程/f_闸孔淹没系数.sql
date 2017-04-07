USE bbz
go
IF OBJECT_ID('f_getZhaKongYanMoXiShu') IS NOT NULL 
    BEGIN
        DROP FUNCTION f_getZhaKongYanMoXiShu
    END
GO
CREATE FUNCTION f_getZhaKongYanMoXiShu ( @eH DECIMAL(9, 3) )
RETURNS DECIMAL(9, 3)
AS 
    BEGIN 
		/* բ����ûϵ�� (����) */
		
        DECLARE @prevEH DECIMAL(9, 3) ,
            @nextEH DECIMAL(9, 3)
        DECLARE @prevVE DECIMAL(9, 4) ,
            @nextVE DECIMAL(9, 4)
        
        DECLARE @ve DECIMAL(9, 4)
        SET @ve = 0
		
		IF (@eH<0)
			SET @eH = 0
            
        IF EXISTS ( SELECT  1
                    FROM    xmis.gczl_llgs_բ����ûϵ��
                    WHERE   Ǳ���� = @eH) 
            BEGIN
                SELECT  @ve = բ����ûϵ��
                FROM    xmis.gczl_llgs_բ����ûϵ��
                WHERE   Ǳ���� = @eH
            END
        ELSE 
            BEGIN
                SELECT  @prevEH = MAX(Ǳ����)
                FROM    xmis.gczl_llgs_բ����ûϵ��
                WHERE   Ǳ���� < @eH
                
                SELECT  @nextEH = MIN(Ǳ����)
                FROM    xmis.gczl_llgs_բ����ûϵ��
                WHERE   Ǳ���� > @eH
				
                SELECT  @prevVE = բ����ûϵ��
                FROM    xmis.gczl_llgs_բ����ûϵ��
                WHERE   Ǳ���� = @prevEH
                
                SELECT  @nextVE = բ����ûϵ��
                FROM    xmis.gczl_llgs_բ����ûϵ��
                WHERE   Ǳ���� = @nextEH
				
				/* �ڲ巨
				Y= Y1+(Y2-Y1)/(X2-X1)*(X-X1)
				*/
				
                SET @ve = -(-@prevVE -(@nextVE - @prevVE)/(@nextEH - @prevEH)*(@eH-@prevEH))
            END
			
        RETURN @ve
    END



		/*
select sqrt(2*9.8) 
select 43.56*sqrt(2*9.8)  *power(8.11000,1.5)

select power(8.11000,1.5)

SELECT * FROM xmis.gczl_llgsh_��Եƽ��բ�Ŵ�������ϵ��

		
		*/

--select xmis.f_getZhaKongYanMoXiShu(0.995)

