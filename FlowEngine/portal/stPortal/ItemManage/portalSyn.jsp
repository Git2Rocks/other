<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="java.util.*,
                 java.sql.*"%>
<%@ page import="minstone.ItemManage.BaseDbManage"%>

<%

  //String user = request.getRemoteUser();
  String user="";

  String framName = null;
  String bulletinUrl = null;
  String dept =null;
  Connection Conn = null;
  Statement st = null;
  ResultSet rs= null;

  String sqlStr=request.getParameter("sqlStr");;		//�û��ʺ�
  if(sqlStr==null) sqlStr="";
  String result="";  	//ִ�н��
  if(!sqlStr.equals("")){
	BaseDbManage db=new BaseDbManage(request.getRemoteUser());
    	result=db.sqlPlusCommit(sqlStr);
 }

 %>
<html>
<form name="portalSyn_hs" action="portalSyn.jsp" method="POST">
	<%
		sqlStr="delete from user_modu";
	%>
  <input type="hidden" name="sqlStr" value="<%=sqlStr%>" size="220">
  <br>
	&nbsp;&nbsp;&nbsp;&nbsp;Ŀǰϵͳportal��Ŀ�ĵ����Ǹ��Ի��ģ����ϵͳ����Ա������portal����Ŀ��Ӧ�ý���ͬ���������û�����ϵͳ������Ա����Ŀһ�¡�
	<br>&nbsp;&nbsp;&nbsp;
	<input type="Submit" name="other_funtion" value="��ʼͬ��" align="MIDDLE">
</form>
ִ�н��:<%=result%><br>
</html>
