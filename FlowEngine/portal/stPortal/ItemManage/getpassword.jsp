<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="java.util.*,
                 java.sql.*"%>
<%@ page import="minstone.ItemManage.BaseDbManage"%>
<%@ page import="minstone.ItemManage.WorkItem"%>
<%@ page import="java.util.Vector,java.util.Enumeration"%>
<%@ page import="oamodule.publiclib.util.RecordSetObject"%>

<%

  //String user = request.getRemoteUser();
  String user="";

  String framName = null;
  String bulletinUrl = null;
  String dept =null;
  Connection cn = null;
  Statement st = null;
  ResultSet rs= null;
  BaseDbManage db=new BaseDbManage(request.getRemoteUser());
  String userCode=request.getParameter("user");;		//�û��ʺ�
  if(userCode==null) userCode="";
  String userName="";  	//�û�����
  String passWord="";  	//����
  String sysDesc="";  	//���ڵ���
  String caSn="";  			//ca�ʺ�

  if(!userCode.equals("")){
    RecordSetObject rsoList =db.getPassWord(userCode);
    if(rsoList!=null && rsoList.getRowCount()>0){
     for(int index=0;index<1;index++){ //��һ����¼
	userCode=rsoList.getString("U_NAME",index);
        passWord=rsoList.getString("U_PASSWORD",index);
        caSn=rsoList.getString("CA_SN",index);
        userName=rsoList.getString("USER_NAME",index);
	sysDesc=rsoList.getString("SYS_DESC",index);
	if(userCode==null) userCode="";
    	if(passWord==null) passWord="";
    	if(caSn==null) caSn="";
    	if(userName==null) userName="";
    	if(sysDesc==null) sysDesc="";
     }
    }

 }

 %>
<html>
<form name="getpassword" action="getpassword.jsp" method="POST">
	<input type="text"   name="user" value="<%=user%>">
	<input type="Submit" name="other_funtion" value="ȷ��" align="MIDDLE">
	<input type="Reset" value="���" align="MIDDLE">
</form>
�û��ʺţ�<%=userCode%><br>
�û�������<%=userName%><br>
���룺<%=passWord%><br>
���ڵ�����<%=sysDesc%><br>
ca�ʺţ�<%=caSn%><br>
</html>
