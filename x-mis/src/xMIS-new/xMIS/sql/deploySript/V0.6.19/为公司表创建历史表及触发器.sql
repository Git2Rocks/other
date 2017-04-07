select * into xmis.org_��˾_history from xmis.org_��˾

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.org_��˾_trigger 
   ON xmis.org_��˾
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @compID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @compID = INSERTED.��˾ID FROM INSERTED
			insert into xmis.org_��˾_history select * from xmis.org_��˾ WHERE ��˾ID = @compID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @compID = DELETED.��˾ID FROM DELETED
			insert into xmis.org_��˾_history select * from xmis.org_��˾ WHERE ��˾ID = @compID;
		end
END
GO