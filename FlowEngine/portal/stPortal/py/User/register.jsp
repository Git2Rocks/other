<%@ page contentType="text/html; charset=GBK" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>Redister</title>
<link href="common/style.css" rel="stylesheet" type="text/css">
<script language="JavaScript">

function isCharsInBag (s, bag)
{ 
	var i,c;
	for (i = 0; i < s.length; i++)
	{ 
		c = s.charAt(i);//�ַ���s�е��ַ�
		if (bag.indexOf(c) < 0) 
			return c;
	}
	return "";
}

function ischinese(s)
{
	var errorChar;
	var badChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	errorChar = isCharsInBag( s, badChar);
	if (errorChar != "" )
	{
		return false;
	}
	return true;
}
	

//���������У�麯��
function isValid(){
     	
	if((form1.CODE.value.length>20))
	{	
	    alert("\��¼�ʻ����ȳ������ƣ�");
		document.form1.CODE.focus();
		return false;
	}
	
	if(!ischinese(form1.CODE.value))   
	{
		alert("\��¼�ʻ���������ĸ������ϣ�");
		document.form1.CODE.focus();
		return false;
	}

	if(form1.CODE.value=="")
	{
		document.form1.CODE.focus();
		alert("\�������½�ʻ���");
		return false;
	}
	if( form1.pwd.value =="" ) 
	{
        alert("\���������룡");
        document.form1.pwd.focus();
        return false;
    }
	
	if((form1.pwd.value.length<5)||(form1.pwd.value.length>20))
	{//����Ϊ5��20֮������ֻ�����ĸ
		alert("\���볤�Ȳ�����Ҫ���������������룡");
		document.form1.pwd.focus();
		return false;
	}
	if( form1.repwd.value =="" ) 
	{
        alert("\������ȷ�����룡");
        document.form1.repwd.focus();
        return false;
    }
	if(form1.pwd.value!=form1.repwd.value)
	{
		alert("\������������벻һ�£�");
		document.form1.repwd.focus();
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

<body>
<br>
<br>
<br>
<form method="post" action="registerServer.jsp" name="form1" onSubmit="return isValid();">
<table width="600"  border="0" align="center" cellpadding="0" cellspacing="0" style="BORDER-COLLAPSE: collapse">
  <tr>
    <td colspan="2"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
      <TR>
            <TD vAlign=top width=7><IMG height=22 alt="" src="images/rnavleft.gif" width=10></TD>
            <TD width="100%" class=SubTitleRed2><img src="images/arrow_write.gif" width="15" height="15" border="0" align="absmiddle"> �û�ע�� - ����ϸ��д������Ŀ����*�ŵ���Ŀ������д��</TD>
            <TD vAlign=top width=7><IMG height=22 alt="" src="images/rnavright.gif" width=10></TD>
        </TR>
    </table></td>
  </tr>

  <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ��¼�ʻ� <font color="red">*</font></td>
    <td class="Tabcell"><input name="CODE" type="text" class="textfield2" id="CODE" size="20" maxlength="20">
    0~20λ a-z;A-Z;0-9����ĸ������� </td>
  </tr>
    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ���� <font color="red">*</font></td>
    <td class="Tabcell"><input name="pwd" type="password" class="textfield2" id="pwd" size="20" maxlength="20">
5~20λ a-z;A-Z;0-9����ĸ������� </td>
  </tr>
    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ȷ������ <font color="red">*</font></td>
    <td class="Tabcell"><input name="repwd" type="password" class="textfield2" id="repwd" size="20" maxlength="20"></td>
  </tr>
    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> �����û�����/��ҵ���� <font color="red">*</font></td>
    <td class="Tabcell"><input name="name" type="text" class="textfield2" id="name" size="50" maxlength="40"></td>
	</tr>
	    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ����/�������֤���� <font color="red">*</font></td>
    <td class="Tabcell"><input name="identify" type="text" class="textfield2" id="identify" size="30" maxlength="40"></td>
  </tr>

  <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> �����ʼ� <font color="red">*</font></td>
    <td class="Tabcell"><input name="mail" type="text" class="textfield2" id="mail" size="30" maxlength="30"></td>
  </tr>
    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ��ַ <font color="red">*</font></td>
    <td class="Tabcell"><input name="address" type="text" class="textfield2" id="address" size="50" maxlength="100"></td>
  </tr>

    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> �̶��绰 <font color="red">*</font></td>
    <td class="Tabcell"><input name="tel" type="text" class="textfield2" id="tel" size="30" maxlength="20">
    </td>
  </tr>
    <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> �ƶ��绰</td>
    <td class="Tabcell"><input name="mobile" type="text" class="textfield2" id="mobile" size="30" maxlength="15"></td>
  </tr>
      <tr align="left">
    <td width="30%" class="Tabcell"  style="COLOR: black; BACKGROUND-COLOR: #f1f1f1"> ��ע</td>
    <td class="Tabcell"><textarea name="remark" cols="50" rows="6" class="textfield2" id="remark"></textarea></td>
  </tr>
      <tr align="right">
    <td colspan="2" class="Tabcell">
	<input name="button" type="submit" class="GoBt" id="button" value="ע��" >	
	<input name="button" type="reset" class="GoBt" id="button" value="ȡ��" >	
	</td>
    </tr>
</table>
</form>
<script language="javascript">
	document.all.item("CODE").focus();
</script>
</body>
</html>
