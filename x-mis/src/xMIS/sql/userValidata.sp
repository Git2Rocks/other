/*
	Procedure :	userValidata.sp  
   	Purpose   :	
	
	Amend History                                       
	---------------------------------------------------------------  
	  No.   Date        	Amend By	Reason  
	---------------------------------------------------------------
	  1   	06/28/2010    	����       	create 

*/

Use xmis
go
IF OBJECT_ID('userValidata') IS NOT NULL
BEGIN
    DROP PROCEDURE userValidata
END
GO
create proc userValidata (
			 @loginName VARCHAR(20), @password VARCHAR(20)
)

as

Begin

	DECLARE @user_id INT
	
	IF NOT EXISTS (
	SELECT 
		1 
	FROM 
		xmis.hr_��Ա userTab 
	WHERE 
		(CONVERT(VARCHAR(20),userTab.��ԱID) = @loginName OR userTab.��¼�� = @loginName) 
		AND RTRIM(userTab.����) = @password
	) 
	RETURN 0
	

	SELECT 
		@user_id = userTab.��ԱID 
	FROM 
		xmis.hr_��Ա userTab 
	WHERE 
		(CONVERT(VARCHAR(20),userTab.��ԱID) = @loginName OR userTab.��¼�� = @loginName) 
		AND RTRIM(userTab.����) = @password


	SELECT 	@user_id USER_ID
		, empDept.����ID dept_id
		, empDept.ְ�� POSITION
		, CASE WHEN deptDept.������ID IS NULL THEN empDept.����ID ELSE deptDept.������ID END division_id
		
	INTO 	#user
	FROM 	xmis.hr_��Ա���Ź�ϵ�� empDept
		, xmis.org_���Ź������ű� deptDept
	WHERE 	empDept.��ԱID = @user_id
		AND empDept.�Ƿ��ְ =1 
		AND empDept.����ID *= deptDept.����ID
		
	
	SELECT	USER_ID
		, dept_id
		, position
		, division_id
		, deptCompy.��˾ID company_id
		, RTRIM(emp.����)+RTRIM(emp.����) emp_name
		, dept.�������� dept_name
		, division.�������� division_name
		, compy.��˾���� compy_name
		
		
	FROM	#user 
		,xmis.org_���Ź�����˾�� deptCompy
		,xmis.hr_��Ա emp
		,xmis.org_���� dept
		,xmis.org_���� division
		,xmis.org_��˾ compy
		
	WHERE	division_id = deptCompy.����ID
		AND deptCompy.�Ƿ�ֱ�� = 1
		AND emp.��ԱID = USER_ID
		AND dept.����ID = dept_id
		AND division.����ID = division_id
		AND compy.��˾ID = deptCompy.��˾ID
		
		

End

return
go
GRANT EXECUTE ON userValidata TO public
go



--userValidata 'jk-admin','admin'

