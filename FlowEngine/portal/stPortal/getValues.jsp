<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="java.util.*,java.sql.*"%>
<%@ page import="baseserverjb.BaseServerClient,baseserverjb.IFramework"%>

<html>
<head>
<title></title>
</head>

<%
  request.setCharacterEncoding("GBK");
  //String[] tels=request.getParameterValues("tels");
  String tels=request.getParameter("tels");
  if(tels==null) tels="";
  if(tels.equals("undefined")) tels="";
  String smsMsg=request.getParameter("smsMsg");
  if(smsMsg==null) smsMsg="";
  
  String sendResult="";
  String actionFlag=request.getParameter("actionFlag");
  if(actionFlag==null) actionFlag="";
  
  if(actionFlag.equals("doSend")){
  String currentUser=request.getRemoteUser();
  Connection con = null;
  Statement stm = null;
  PreparedStatement pstm = null;
  ResultSet rs = null;
	String sql = "";
	try{ 
		con = BaseServerClient.getWizardConnection();
		//stm = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_UPDATABLE);
		sql = "INSERT into sms_tbl(sms_seq,send_user,mobl_nmbr,sms_msg,"
		    +" send_stat,send_nmbr,sms_type,save_time) values(?,?,?,?,0,0,0,sysdate) ";
		//stm.executeUpdate(sql);
    
	  pstm = con.prepareStatement(sql);
    pstm.setLong(1,System.currentTimeMillis());
    pstm.setString(2, currentUser);
    pstm.setString(3, tels);
    pstm.setString(4, smsMsg);
    pstm.execute();
    pstm.close();
    con.commit();//�ύ
    out.println("<script language='javascript'>alert('���ͳɹ���');window.close();opener.window.close();</script>");
     sendResult="���ͳɹ���";
	}catch(Exception ex){
		  ex.printStackTrace();
		  out.println("<script language='javascript'>alert('����ʧ�ܣ�');window.close();</script>");
                  sendResult="����ʧ�ܣ���";
	} finally{
		if (stm != null) {
		    stm.close();
		    stm = null;
		  }
	  if (con != null){
      con.close();
      con = null;
    }
	}
}else{
%>
<script language="javascript" type="">
function doSend(){
	var temp=document.all.item("tels").value;
        var smsMsg=document.all.item("smsMsg").value;

	if(temp.length>4000){
		alert("�ֻ��ܳ��ȳ���4000�ַ�����ֶη��ͣ�");
		return;
	}
       if(temp.length==0 || smsMsg.length==0){
		alert("����д�ֻ������ݣ�");
		return;
	}

	postForm.actionFlag.value="doSend";
  postForm.submit();
}
</script>

<link rel="stylesheet" type="text/css" href="../Common/Css/Public.css">
  <body>
  <form id="postForm" action="getValues.jsp" method="POST">
    <table width="95%" height="100%" border="0" align=center>
    <tr>
      <td width="100%" height="100%" align=center> <font size="6"><strong>���ŷ���</strong></font>
      <br>
      <fieldset>
        <legend>����</legend>
        <table width="100%" border="0" cellspacing="0"  id="whereClause">
          <tr>
            <td width="20%" align="left" bgcolor="#CCCC99">
						  <div align="center"><strong>�ֻ�����:</strong></div></td>
            </td>
            <td width="80%" align="left" bgcolor="">
						  <TEXTAREA cols="50"  rows="3" width="100%" height="100%" name="tels" ><%=tels%></TEXTAREA>
            </td> 
          </tr>
          <tr>
            <td width="20%" align="left" bgcolor="#CCCC99">
						  <div align="center"><strong>��������:</strong></div></td>
            </td>
            <td width="80%" align="left" bgcolor="">
						  <TEXTAREA style="width:100%"  class="" id="smsMsg" ROWS="20" name="smsMsg"  cols="" ><%=smsMsg%></TEXTAREA>
            </td>              
          </tr>
          <tr>
            <td width="100%" align="center" bgcolor="" colspan="2">
						 <input type="button" class="Btn_common" name="btnOK" value="����" id="btnOK" onclick="javacript:doSend();">
						 <input type="button" class="Btn_common" name="btnOK" value="�ر�" id="btnOK" onclick="javacript:window.close();">
            </td>  
          </tr>
        </table>
     </fieldset>
     </td>  
   </tr>
   </table>
   <input name="actionFlag" type="hidden" id="actionFlag" value="">
  </form>      
      
  </body>
  </html>
<%}%>