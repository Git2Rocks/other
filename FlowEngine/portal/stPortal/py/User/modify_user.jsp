<%@ page contentType="text/html; charset=GBK" %>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�û������޸�</title>
<link href="common/style.css" rel="stylesheet" type="text/css">
<script language="JavaScript">
<!--���������У�麯��-->
function isValid(){
     	
	if((form1.CODE.value.length>20))
	{	
	    alert("\�ʻ����ȳ������ƣ�");
		document.form1.CODE.focus();
		return false;
	}   

	if(form1.CODE.value=="")
	{
		document.form1.CODE.focus();
		alert("\�������½�ʻ���");
		return false;
	}
	if((form1.name.value.length>40))
	{	
	    alert("\����/��ҵ���Ƴ��ȳ������ƣ�");
		document.form1.name.focus();
		return false;
	}   
	if(form1.name.value=="")
	{
		document.form1.name.focus();
		alert("\����������û�����/��ҵ���ƣ�");
		return false;
	}
	if(form1.identify.value=="")
	{
		document.form1.identify.focus();
		alert("\���������/�������֤���룡");
		return false;
	}
	if((form1.identify.value.length>40))
	{	
	    alert("\����/�������֤���볤�ȳ������ƣ�");
		document.form1.identify.focus();
		return false;
	}
	if(form1.mail.value=="")
	{
		alert("\����������ʼ���ַ��");
		document.form1.mail.focus();
		return false;
	}
	
	if((form1.mail.value.indexOf('@',0)==-1)||(form1.mail.value.indexOf('.',0)==-1)||(form1.mail.value.length<6))
	{
		alert("\��������Ϸ��ĵ����ʼ���ַ��");
		document.form1.mail.focus();
		return false;
	}
	if(form1.address.value=="")
	{
		alert("\�������ַ��");
		document.form1.address.focus();
		return false;
	}

	if((form1.address.value.length>200))
	{	
	    alert("\��ַ�ȳ������ƣ�");
		document.form1.address.focus();
		return false;
	}
	if(form1.tel.value=="")
	{
		alert("\������̶��绰���룡");
		document.form1.tel.focus();
		return false;
	}
	
	if((form1.tel.value.length>20))
	{	
	    alert("\�绰���볤�ȳ������ƣ�");
		document.form1.tel.focus();
		return false;
	}
	
	if((form1.remark.value.length>200))
	{	
	    alert("\��ע���ȳ������ƣ�");
		document.form1.remark.focus();
		return false;
	}
}
</script>
</head>
<jsp:useBean id="userfile" scope="session" class="net.kingsoft.user.Userfile"/>
<!--�����ϼ�ҳ�洫�ݵ��û���-->
<!--��ȡ������û���Ϣ�Ա���ʾ-->
<%
String m_usercode = (String)session.getAttribute(suntek.security.Security.m_sUser);
String m_username = oManager.getCurrentUserName();
String err = "";

//�ж��Ƿ���Ĭ���û�
if(!m_usercode.equals("guest"))
{
	userfile.setUSER_CODE(m_usercode);
	userfile.selectUser();
}
else
{
	//���������123����ݼ�����
	err="modify_result.jsp?regReturn=123";
%>
	<jsp:forward page="<%=err%>"/>
<%	
}
%>

<!--ʹ����������ʾ���ݿ�ԭ������-->


<body>
<form method="post" action="modifyServer.jsp" name="form1" onSubmit="return isValid();">
<table width="600"  border="0" align="center" cellpadding="0" cellspacing="0" style="BORDER-COLLAPSE: collapse">
  <tr>
    <td colspan="2"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
      <TR>
            <TD vAlign=top width=7><IMG height=22 alt="" src="images/rnavleft.gif" width=10></TD>
            <TD width="100%" class=SubTitleRed2><img src="images/arrow_write.gif" width="15" height="15" border="0" align="absmiddle"> �û�ע�������޸� - ����ϸ��д������Ŀ����*�ŵ���Ŀ������д��</TD>
            <TD vAlign=top width=7><IMG height=22 alt="" src="images/rnavright.gif" width=10></TD>
        </TR>
    </table></td>
  </tr>

  <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ��¼�ʻ�</td>
    <td class="Tabcell"><input name="CODE" type="text" class="textfield2" id="CODE" size="30" maxlength="20" value="<%=userfile.getUSER_CODE()%>" readonly></td>
  </tr>
    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> �����û�����/��ҵ����*</td>
    <td class="Tabcell"><input name="name" type="text" class="textfield2" id="name" size="50" maxlength="40" value="<%=userfile.getFULL_NAME()%>"></td>
	</tr>
	    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ����/�������֤����*</td>
    <td class="Tabcell"><input name="identify" type="text" class="textfield2" id="identify" size="30" maxlength="40" value="<%=userfile.getUSER_IDEN()%>"></td>
  </tr>

  <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> �����ʼ�*</td>
    <td class="Tabcell"><input name="mail" type="text" class="textfield2" id="mail" size="30" maxlength="30" value="<%=userfile.getE_MAIL()%>"></td>
  </tr>
    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ��ַ*</td>
    <td class="Tabcell"><input name="address" type="text" class="textfield2" id="address" size="50" maxlength="100" value="<%=userfile.getUSER_ADDR()%>"></td>
  </tr>

    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> �̶��绰*</td>
    <td class="Tabcell"><input name="tel" type="text" class="textfield2" id="tel" size="30" maxlength="20" value="<%=userfile.getUSER_TEL()%>">
    </td>
  </tr>
    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> �ƶ��绰</td>
    <td class="Tabcell"><input name="mobile" type="text" class="textfield2" id="mobile" size="30" maxlength="15" value="<%=userfile.getMOBI_TEL()%>"></td>
  </tr>
      <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ��ע</td>
    <td class="Tabcell"><textarea name="remark" cols="50" rows="6" class="textfield2" id="remark"><%=userfile.getUSER_DESC()%></textarea></td>
  </tr>
      <tr align="right">
    <td colspan="2" class="Tabcell">
	<input name="button" type="submit" class="GoBt" id="button" value="�޸�" >	
	<input name="button" type="reset" class="GoBt" id="button" value="ȡ��" >	
	</td>
    </tr>
</table>
</form>
</body>
</html>
