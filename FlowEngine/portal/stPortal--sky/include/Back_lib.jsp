<%--
	Function GetBackCom()
		Set GetBackCom = Server.CreateObject ("BackCom.cBack")
	End Function

	'-------------------------------------------------------------
	'���ܣ�ҳ�淵�س�ʼ����
	'������as_key��Ϊ�������ı�ʾֵ��as_Value��ΪҪ���ر�������URL
	'����ֵ��������һ������URL��Ϊ�ձ�ʾû����һ����
	'-------------------------------------------------------------
	Function BackInit(as_key,as_Value)
		Dim lo_Back
		Set lo_Back = GetBackCom()
		lo_Back.SavePage Cstr(as_key),Cstr(as_Value)
		BackInit = lo_Back.GetPage(Cstr(as_key))
	End Function

	'-------------------------------------------------------------
	'���ܣ�ȡ������ҳ��
	'������as_key��Ϊ�������ı�ʾֵ
	'����ֵ��������һ������URL��Ϊ�ձ�ʾû����һ����
	'-------------------------------------------------------------
	Function BackGetPage(as_key)
		Dim lo_Back
		Set lo_Back = GetBackCom()
		BackGetPage = lo_Back.GetPage(Cstr(as_key))
	End Function

	'-------------------------------------------------------------
	'���ܣ�ɾ�����г���
	'-------------------------------------------------------------
	Sub BackDel()
		Dim lo_Back
		Set lo_Back = GetBackCom()
		lo_Back.RemoveAll
	End Sub

--%>