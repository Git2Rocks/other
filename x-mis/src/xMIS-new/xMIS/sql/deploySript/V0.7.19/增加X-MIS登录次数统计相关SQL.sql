  update xmis.sec_ҵ����ģ��� 
  set ҵ����ģ��url = 'developProgressMaint.do?method=getMonthAccounting'
  ,ҵ����ģ������='X-MIS��¼����ͳ��'
  ,ҵ����ģ������ = 'X-MIS��¼����ͳ��'
  where ҵ����ģ��ID = 17
  
  insert into xmis.sec_ҵ���ܱ� values(31,'X-MIS��¼����ͳ��','developProgressMaint.do?method=getMonthAccounting','X-MIS��¼����ͳ��',null,37,null,null,null,null,null,null,null)
  
  insert into xmis.sec_��ɫ�û�����Ȩ�޶����
  values(102,-1,8,17,31,5,0,getdate(),-1)
  insert into xmis.sec_��ɫ�û�����Ȩ�޶����
  values(103,163,8,17,31,5,0,getdate(),-1)
  insert into xmis.sec_��ɫ�û�����Ȩ�޶����
  values(104,10,8,17,31,5,0,getdate(),-1)