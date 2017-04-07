select * into xmis.prj_��Ŀ״̬_history from xmis.prj_��Ŀ״̬

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.prj_��Ŀ״̬_trigger 
   ON xmis.prj_��Ŀ״̬
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @ID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = INSERTED.��Ŀ״̬ID FROM INSERTED
			insert into xmis.prj_��Ŀ״̬_history select * from xmis.prj_��Ŀ״̬ WHERE ��Ŀ״̬ID = @ID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = DELETED.��Ŀ״̬ID FROM DELETED
			insert into xmis.prj_��Ŀ״̬_history select * from xmis.prj_��Ŀ״̬ WHERE ��Ŀ״̬ID = @ID;
		end
END
GO