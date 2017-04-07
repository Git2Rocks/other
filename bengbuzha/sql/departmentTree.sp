/*
	Procedure :	departmentTree.sp  
   	Purpose   :	
	
	Amend History                                       
	---------------------------------------------------------------  
	  No.   Date        	Amend By	Reason  
	---------------------------------------------------------------
	  1   	06/28/2010    	����       	create 

*/

Use xmis
go
IF OBJECT_ID('departmentTree') IS NOT NULL
BEGIN
    DROP PROCEDURE departmentTree
END
GO
create proc departmentTree (
			@divisionID int
)

as

BEGIN

SELECT 	xmis.org_���Ź������ű�.����ID dept_id
	,xmis.org_����.�������� dept_name
INTO #deptTemp
FROM	xmis.org_���Ź������ű�, xmis.org_����
WHERE 	xmis.org_���Ź������ű�.������ID = @divisionID 
	AND xmis.org_���Ź������ű�.����ID = xmis.org_����.����ID
	
	
SELECT #deptTemp.*,xmis.hr_��Ա���Ź�ϵ��.��ԱID user_id INTO #deptTree
FROM #deptTemp, xmis.hr_��Ա���Ź�ϵ��
WHERE xmis.hr_��Ա���Ź�ϵ��.����ID =* #deptTemp.dept_id AND  ��ԱID>0


SELECT #deptTree.*, RTRIM(xmis.hr_��Ա.����)+RTRIM(xmis.hr_��Ա.����) user_name FROM #deptTree, xmis.hr_��Ա
WHERE #deptTree.user_id *= xmis.hr_��Ա.��ԱID ORDER BY dept_id

	
End

return
go
GRANT EXECUTE ON departmentTree TO public
go


--departmentTree 1



