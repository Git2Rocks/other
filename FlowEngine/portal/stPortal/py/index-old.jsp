<%@ page contentType="text/html; charset=GBK" %>
<%
 String currentUser=request.getRemoteUser();
 if(currentUser==null) currentUser="";
%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��ҳ</title>
<style type="text/css">
<!--
body {
	margin-left: 0px;
	margin-top: 0px;
	margin-right: 0px;
	margin-bottom: 0px;
	background-color: #0d58b5;
}
-->
</style></head>

<body>
<table width="738" height="430" border="0" align="center" cellpadding="0" cellspacing="1" bgcolor="#FFFFFF" style="margin-top:95px; ">
  <tr>
    <td height="131" valign="top" bgcolor="2391BE"><img src="logo.jpg" width="738" height="131"></td>
  </tr>
  <tr>
    <td height="165" align="center" valign="bottom" bgcolor="2FA6DA">
    <img src="2_r2_c2.jpg" width="738" height="165">
    </td>
  </tr>
  <tr>
    <td height="123" bgcolor="1183B0"> 
	     <TABLE width="65%" align="center" class=list_table>
              <TBODY>
              <%if(currentUser.equals("guest") || currentUser.equals("admin_public")){%>
              <TR align="center">			  
                <TD style="font-size:13px;color:white;">
	   				      <A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0024&DashboardType=0'" target=_blank>
	   				      <img src="3.jpg" width="75" height="75"></A>
					        <BR><strong>������ѯ</strong></A>
				        </TD>
				  			<TD style="font-size:13px;color:white;">
				  				<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0025&DashboardType=0'" target=_blank>
				  				<IMG src="1.jpg" width="77" height="76"   border=0></A>
								  <BR><strong>����Ͷ��</strong></A> 
							  </TD>								
                <TD style="font-size:13px;color:white;">
                	<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0003&DashboardType=0'" target=_blank>
									<IMG src="6.jpg" width="76" height="75"  border=0></A>
									<BR><strong>����ָ��</strong></A>
								</TD>
					      <TD style="font-size:13px;color:white;">
                	<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0004&DashboardType=0'" target=_blank>
									<IMG src="4.jpg" width="76" height="75"   border=0></A>
									<BR><strong>��������</strong></A>
								</TD>
								<TD style="font-size:13px;color:white;">
				  				<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0028&DashboardType=0'" target=_blank>
				  				<IMG src="5.jpg" width="76" height="75"  border=0>
								  <BR><strong>���ܲ�ѯ</strong></A>
								</TD>
								<TD style="font-size:13px;color:white;">
								  <table>
								    <tr align="center">
								     <td style="font-size:13px;color:red;" background="5.jpg" width="76" height="37" >
						  				<A style="cursor:hand" onclick="javascript:window.location='/stPortal/py/userLogin_new.jsp'" target=_blank>
						  				<strong>���ϵ�½</strong></A>
								  	 </td>
								   </tr>
								   <tr align="center">
								     <td style="font-size:13px;color:red;" background="6.jpg" width="76" height="34" >
						  				<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0015&DashboardType=0'" target=_blank>
						  				<strong>�ι���</strong></A>
								  	 </td>
								   </tr>
								   </table>
								   <BR><strong><span bgcolor="1183B0">.</span></strong></A>
								</TD>
              </TR>             
            <%}else{%>
              <TR align="center">			  
                <TD style="font-size:13px;color:white;">
	   				      <A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0008&DashboardType=0'" target=_blank>
	   				      <img src="3.jpg" width="75" height="75"></A>
					        <BR><strong>������ѯ</strong></A>
				        </TD>
				  			<TD style="font-size:13px;color:white;">
				  				<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0035&DashboardType=0'" target=_blank>
				  				<IMG src="1.jpg" width="77" height="76"   border=0></A>
								  <BR><strong>����Ͷ��</strong></A> 
							  </TD>								
                <TD style="font-size:13px;color:white;">
                	<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0003&DashboardType=0'" target=_blank>
									<IMG src="6.jpg" width="76" height="75"  border=0></A>
									<BR><strong>����ָ��</strong></A>
								</TD>
					      <TD style="font-size:13px;color:white;">
                	<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0004&DashboardType=0'" target=_blank>
									<IMG src="4.jpg" width="76" height="75"   border=0></A>
									<BR><strong>��������</strong></A>
								</TD>
								<TD style="font-size:13px;color:white;">
				  				<A style="cursor:hand" onclick="javascript:window.location='/stPortal/default.jsp?DashboardID=0037&DashboardType=0'" target=_blank>
				  				<IMG src="5.jpg" width="76" height="77"  border=0>
								  <BR><strong>���ܲ�ѯ</strong></A>
								</TD>
              </TR>    
            <%}%>

    </TBODY></TABLE>    
	</td>
  </tr>  
</table>
    <div align="center" style="font-size: 12px;color:white">
	    <br><br>(����ʹ��IE6.0���ϡ�1024��768�������)<br>
			���������������ߣ�84690905 ����֧�����ߣ�84690905<br>
			��ICP��05094920�� <br>
 		</div>
</body>
</html>
