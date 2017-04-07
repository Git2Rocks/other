insert into xmis.con_��ͬ_history select * from xmis.con_��ͬ

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.con_��ͬ_trigger 
   ON xmis.con_��ͬ
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @ID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = INSERTED.��ͬID FROM INSERTED
			insert into xmis.con_��ͬ_history select * from xmis.con_��ͬ WHERE ��ͬID = @ID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = DELETED.��ͬID FROM DELETED
			insert into xmis.con_��ͬ_history select * from xmis.con_��ͬ WHERE ��ͬID = @ID;
		end
END
GO