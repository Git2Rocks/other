<%--@ include file="ASPUtil_lib.jsp" --%>
<%!
          public String GetValue(String aValue)
          {
                    String sValue = null;
                    if (aValue==null)
                              sValue = "";
                    else
                              sValue = aValue;

                    return sValue;
          }

	public String GetValueN(String aValue)
          {
		String sValueN=null;
                    if (aValue==null)
			sValueN = "0";
		else
			sValueN = aValue;

                    return sValueN;
	}

%>
<%--
	//�õ���ǰ�û���������
	public GetCurrentUser(user_name)
          {
                    /*
		dim oRight,oDct_User

		set oRight = Server.createObject("FlatSysManager.Run")
		set oDct_User = server.CreateObject ("Scripting.Dictionary")


		set oDct_User = oRight.GetCurrentUser()

		GetCurrentUser = oDct_User("user_code")
		user_name = oDct_User("user_name")
                    */
	}

	//���ݿ������Ϣ����
	public ShowDBError(a_type ,a_Return,a_sRedirect)
		String sError = "";

                    if (a_type == "update")
                        char c_type == "U";
                    else if (a_type == "delete")
                        char c_type == "D";

		switch(i_type)
                    {

			Case "U" :
				switch(a_Return)
                                        {
					case 0 :
                                                            break;
					case -1 :
						sError="���ݱ���ʧ�ܣ��������Թ���";
                                                            break;
					case -2 :
						sError="���ݱ�������з������������ˢ�º��������ԣ�";
                                                            break;
					case -3 :
						sError="���ݱ�������У��������ݿ����Ѿ�������ͬ�ļ�¼����ȷ�Ϻ����ԣ�";
                                                            break;
					default:

				}
			Case "D" :
				switch(a_Return)
                                        {
					case 0 :
                                                            break;
					case -1 :
						sError = "����ɾ��ʧ�ܣ����������ԣ�";
                                                            break;
					case -2 :
						sError = "�������������ط��Ѿ���ʹ�ã�����ɾ����";
                                                            break;
                                                  default:
				}
			defaule:
		}

		if sError == ""
                          return
		//htmRenderErrorMessage sError,a_sRedirect

	}
--%>