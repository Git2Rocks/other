select * into xmis.con_�վ���ϸ��_history from xmis.con_�վ���ϸ��

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.con_�վ���ϸ��_trigger 
   ON xmis.con_�վ���ϸ��
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @cID INT,@iID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @cID = INSERTED.��ͬID,@iID = INSERTED.�վ�ID FROM INSERTED
			insert into xmis.con_�վ���ϸ��_history select * from xmis.con_�վ���ϸ�� WHERE ��ͬID = @cID and �վ�ID = @iID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @cID = DELETED.��ͬID,@iID = DELETED.�վ�ID FROM DELETED
			insert into xmis.con_�վ���ϸ��_history select * from xmis.con_�վ���ϸ�� WHERE ��ͬID = @cID and �վ�ID = @iID;
		end
END
GO