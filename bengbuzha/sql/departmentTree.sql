SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

ALTER  proc departmentTree (
			@userID int
)

as

Begin

DECLARE @deptID INT

SELECT @deptID = xmis.hr_��Ա���Ź�ϵ��.����ID  FROM xmis.hr_��Ա���Ź�ϵ�� WHERE xmis.hr_��Ա���Ź�ϵ��.��ԱID = @userID

SELECT xmis.org_����.����ID dept_id,xmis.org_����.�������� dept_name INTO #deptTemp
FROM xmis.org_����, xmis.org_���Ź������ű�
WHERE
xmis.org_���Ź������ű�.����ID = xmis.org_����.����ID AND 
xmis.org_���Ź������ű�.������ID = (
SELECT xmis.org_���Ź������ű�.������ID FROM xmis.org_���Ź������ű� WHERE ����ID = @deptID )


SELECT #deptTemp.*,xmis.hr_��Ա���Ź�ϵ��.��ԱID user_id INTO #deptTree
FROM #deptTemp, xmis.hr_��Ա���Ź�ϵ��
WHERE xmis.hr_��Ա���Ź�ϵ��.����ID =* #deptTemp.dept_id AND  ��ԱID>0


SELECT #deptTree.*, RTRIM(xmis.hr_��Ա.����)+RTRIM(xmis.hr_��Ա.����) user_name FROM #deptTree, xmis.hr_��Ա
WHERE #deptTree.user_id *= xmis.hr_��Ա.��ԱID ORDER BY dept_id

	
End

return

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

