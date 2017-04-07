USE bbz
go
IF OBJECT_ID('f_get28SingleValue') IS NOT NULL 
    BEGIN
        DROP FUNCTION f_get28SingleValue
    END
GO
CREATE FUNCTION f_get28SingleValue
    (
      @ap_w_level DECIMAL(5, 3) ,			--բ��ˮλ
      @bp_w_level DECIMAL(5, 3) ,			--բ��ˮλ
      @gate_open_degree_1 DECIMAL(5, 3) 	--28��բ����
    )
RETURNS DECIMAL(9, 3)
AS 
    BEGIN
		/* 
		28��բ������������ 
		
		z��ˮλ�բ��ˮλ-բ��ˮλ��������0.60�ף�Ҫ��e=0.58��e=0.67֮���ڲ塣
		
		����z=2.25,բ�ſ���Ϊe=0.60��ʱ���Ȳ�e=0.58��ʱ������=29��e=0.67��ʱ������=34.2,
		ÿ��������Ϊ34.2-29=5.2,0.67-0.58=0.09��ÿ��������5.2/9=0.58��
		�ټ���e=0.60ʱ��������29+0.58*2=30.16
		
		*/
		
        DECLARE @first_E DECIMAL(9, 3) ,		--���ȷ�Χ
            @sec_E DECIMAL(9, 3)
        DECLARE @first_value DECIMAL(9, 4) ,
            @sec_value DECIMAL(9, 4)
        
        DECLARE @z DECIMAL(9, 4) ,
            @singleValue DECIMAL(9, 2)
        
        SET @z = @ap_w_level - @bp_w_level
        SET @singleValue = 0
        
        IF EXISTS ( SELECT  1
                    FROM    xmis.gczl_llgs_28�׽���բ��������������
                    WHERE   e_value = @gate_open_degree_1 ) 
            BEGIN
                SELECT  @singleValue = value
                FROM    xmis.gczl_llgs_28�׽���բ��������������
                WHERE   e_value = @gate_open_degree_1
                        AND z_value = @z
            END
        ELSE 
            BEGIN
                SELECT  @first_E = MAX(e_value)
                FROM    xmis.gczl_llgs_28�׽���բ��������������
                WHERE   e_value < @gate_open_degree_1
                
                SELECT  @sec_E = MIN(e_value)
                FROM    xmis.gczl_llgs_28�׽���բ��������������
                WHERE   e_value > @gate_open_degree_1
				
                SELECT  @first_value = value
                FROM    xmis.gczl_llgs_28�׽���բ��������������
                WHERE   e_value = @first_E
                        AND z_value = @z
                
                SELECT  @sec_value = value
                FROM    xmis.gczl_llgs_28�׽���բ��������������
                WHERE   e_value = @sec_E
                        AND z_value = @z
				
				/* �ڲ巨
				Y= Y1+(Y2-Y1)/(X2-X1)*(X-X1)
				*/
				
				
                SET @singleValue = @first_value + ( @sec_value - @first_value )
                    / ( @sec_E - @first_E ) * ( @gate_open_degree_1 - @first_E )
                    
            END

        IF ( @singleValue IS NULL ) 
            SET @singleValue = 0

			
        RETURN   @singleValue

    END




--select xmis.f_get28SingleValue(18.53,18.05,0.3)



