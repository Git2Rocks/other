select * into xmis.hr_��Ա_history from xmis.hr_��Ա

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.hr_��Ա_trigger 
   ON xmis.hr_��Ա
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @ID INT, @oldID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = INSERTED.��ԱID FROM INSERTED
			insert into xmis.hr_��Ա_history select * from xmis.hr_��Ա WHERE ��ԱID = @ID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = DELETED.��ԱID FROM DELETED
			insert into xmis.hr_��Ա_history select * from xmis.hr_��Ա WHERE ��ԱID = @ID;
		end
END
GO