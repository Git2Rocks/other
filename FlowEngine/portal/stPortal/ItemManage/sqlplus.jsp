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
  String sqlStr="",procedure="";
  String result="";  	//ִ�н��
  Connection Conn = null;
  Statement st = null;
  ResultSet rs= null;
  BaseDbManage db=new BaseDbManage(request.getRemoteUser());

  //���ҳ��ֱ�Ӵ��洢���̵Ĳ��� �� sqlplus.jsp?procedure=....
  procedure=request.getParameter("procedure");	//�洢��������
  if(!procedure.equals("")){
     result=db.sqlPlusProcedure(procedure);
     out.println(result);
  }else{ //���ҳ��û�в��������ý���ķ�ʽ����
  String sqlType=request.getParameter("sqlplusType");
  if(sqlType.equals("1")){//sql������select��update��delete
  	sqlStr=request.getParameter("sqlStr");		//�û��ʺ�
  	if(sqlStr==null) sqlStr="";
  	if(!sqlStr.equals("")){
		result=db.sqlPlusCommit(sqlStr);
  	}
 }
 if(sqlType.equals("2")){//�洢����
  	procedure=request.getParameter("sqlStr");	//�洢��������
  	if(procedure==null) procedure="";
  	if(!procedure.equals("")){
    		result=db.sqlPlusProcedure(procedure);
  	}
 }

 %>
<html>
<form name="sqlplus" action="sqlplus.jsp" method="POST">
   <table width="95%" border="1" cellspacing="0" cellpadding="2" align="CENTER" bgcolor="" bordercolor="">
     <tr>
	<td>
	<input type="radio" name="sqlplusType" value="1" align="MIDDLE">sql���
	<input type="radio" name="sqlplusType" value="2" align="MIDDLE">�洢����
	</td>
     </tr>
     <tr>
	<td>
	<input type="text"   name="sqlStr" value="<%=sqlStr%>" size="120"><br>
	<input type="Submit" name="other_funtion" value="�ύsql���" align="MIDDLE">
	<input type="Reset" value="���" align="MIDDLE">
	</td>
     </tr>
    </table>
</form>
ִ�н��:<%=result%><br>
</html>
<%}%>