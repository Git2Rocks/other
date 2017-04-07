select * into xmis.con_����֧����ͬ��Ӧ��_history from xmis.con_����֧����ͬ��Ӧ��

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.con_����֧����ͬ��Ӧ��_trigger 
   ON xmis.con_����֧����ͬ��Ӧ��
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @ID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = INSERTED.��ӦID FROM INSERTED
			insert into xmis.con_����֧����ͬ��Ӧ��_history select * from xmis.con_����֧����ͬ��Ӧ�� WHERE ��ӦID = @ID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = DELETED.��ӦID FROM DELETED
			insert into xmis.con_����֧����ͬ��Ӧ��_history select * from xmis.con_����֧����ͬ��Ӧ�� WHERE ��ӦID = @ID;
		end
END
GO