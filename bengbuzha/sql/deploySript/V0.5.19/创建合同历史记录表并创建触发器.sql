select * into xmis.con_��ͬ_history from con_��ͬ where 1=2

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.con_��ͬ_trigger 
   ON xmis.con_��ͬ
   AFTER UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	insert into xmis.con_��ͬ_history select * from deleted;

END
GO
