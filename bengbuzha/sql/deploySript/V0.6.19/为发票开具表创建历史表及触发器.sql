select * into xmis.con_��Ʊ���߱�_history from xmis.con_��Ʊ���߱�

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.con_��Ʊ���߱�_trigger 
   ON xmis.con_��Ʊ���߱�
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @cID INT,@iID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @cID = INSERTED.��ͬID,@iID = INSERTED.��Ʊ�� FROM INSERTED
			insert into xmis.con_��Ʊ���߱�_history select * from xmis.con_��Ʊ���߱� WHERE ��ͬID = @cID and ��Ʊ�� = @iID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @cID = DELETED.��ͬID,@iID = DELETED.��Ʊ�� FROM DELETED
			insert into xmis.con_��Ʊ���߱�_history select * from xmis.con_��Ʊ���߱� WHERE ��ͬID = @cID and ��Ʊ�� = @iID;
		end
END
GO