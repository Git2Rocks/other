<%@page contentType="text/html; charset=gb2312"%>
<html>
<head>
<link href="/stPortal/images/new.css" rel="stylesheet" type="text/css">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ͻ����ϵǼǱ�</title>
<script type="text/javascript">


function MM_jumpMenu(selObj){

	if(selObj.options[0].selected){
		document.all.item("e_enterprise_type").value="";
	}

	if(selObj.options[1].selected){
		document.all.item("e_enterprise_type").value="��Ӫ��ҵ";
	}

	if(selObj.options[2].selected){
		document.all.item("e_enterprise_type").value="������ҵ";
	}


}
function checkAccount(){
    	var account=document.forms["form1"].account;
    	if(account.value!=""){
      		document.frames["accountexists"].location.replace("accountexists.do?account="+e_account.value);
    	}
    	else{
      		account.focus();
    	}
  	}

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

function isNum(s)
{
	var errorChar;
	var badChar = "0123456789xX.";
	errorChar = isCharsInBag( s, badChar);
	if (errorChar != "" )
	{
		return false;
	}
	return true;
}

function isPhoneNum(s)
{
	var errorChar;
	var badChar = "0123456789-";
	errorChar = isCharsInBag( s, badChar);
	if (errorChar != "" )
	{
		return false;
	}
	return true;
}


//���������У�麯��
function isValid(){

	if(form1.e_account.value=="")
	{//�ʺ�Ϊ��
		document.form1.e_account.focus();
		alert("\�������½�ʻ���");
		return false;
	}
	if((form1.e_account.value.length>20))
	{ //�ʺŴ���
	    alert("\��¼�ʻ����Ȳ��ܴ���20��");
		document.form1.e_account.focus();
		return false;
	}
	if(form1.e_account.value.length < 5)
	{//�ʺ�����
	    alert("\��¼�ʻ����Ȳ���С��5��");
		document.form1.e_account.focus();
		return false;
	}
	if(!ischinese(form1.e_account.value))
	{//�ʺ�����
		alert("\��¼�ʻ���������ĸ������ϣ�");
		document.form1.e_account.focus();
	return false;
	}

	if( form1.e_password.value =="" )
	{//����Ϊ��
        alert("\���������룡");
        document.form1.e_password.focus();
        return false;
    }
	if((form1.e_password.value.length<5)||(form1.e_password.value.length>20))
	{//����Ϊ5��20֮������ֻ�����ĸ
		alert("\���볤�Ȳ�����Ҫ���������������룡");
		document.form1.e_password.focus();
		return false;
	}
	if( form1.re_e_password.value =="" )
	{//ȷ����Ϊ��
        alert("\������ȷ�����룡");
        document.form1.re_e_password.focus();
        return false;
    }
	if(form1.e_password.value!=form1.re_e_password.value)
	{//����ȷ��
		alert("\����������ȷ�����벻һ�£�");
		document.form1.re_e_password.focus();
		return false;
	}
	if((form1.e_name.value.length>40))
	{//��ҵ���Ƴ���
	    alert("\��ҵ���Ƴ��Ȳ��ܳ���40��");
		document.form1.e_name.focus();
		return false;
	}
	if(form1.e_name.value=="")
	{//��ҵ����Ϊ��
		document.form1.e_name.focus();
		alert("\��������ҵ���ƣ�");
		return false;
	}
	if(form1.e_address.value=="")
	{//��ַΪ��
		alert("\�������ַ��");
		document.form1.e_address.focus();
		return false;
	}
	if((form1.e_address.value.length>200))
	{//��ַ����
	    alert("\��ַ�ȳ������ƣ�");
		document.form1.e_address.focus();
		return false;
	}
	if(form1.e_post_code.value=="")
	{//�ʱ��ʽ
	    alert("\�ʱ಻��Ϊ�գ�");
		document.form1.e_post_code.focus();
		return false;
	}
	if(!isNum(form1.e_post_code.value))
	{//�ʱ��ʽ
	    alert("\�ʱ���������֣�");
		document.form1.e_post_code.focus();
		return false;
	}
	if(form1.e_phone.value=="")
	{//�̶��绰Ϊ��
		alert("\������̶��绰���룡");
		document.form1.e_phone.focus();
		return false;
	}
	if(!isPhoneNum(form1.e_phone.value))
	{//�̶��绰��ʽ
		alert("\����Ĺ̶��绰�����ʽ���ԣ�");
		document.form1.e_phone.focus();
		return false;
	}
	if(form1.e_phone.value.length>20)
	{//�̶��绰����
	    alert("\�̶��绰���볤�ȳ������ƣ�");
		document.form1.e_phone.focus();
		return false;
	}
//	if(form1.e_org_code.value=="")
//	{//��֯�ṹ����Ϊ��
//	    alert("\��������֯�������룡");
//		document.form1.e_org_code.focus();
//		return false;
//	}
//	if(form1.e_enterprise_type.value==""){

	//    	alert("\��ѡ����ҵ���ͣ�");
	//		return false;
	//}
	//if(form1.e_register_fund.value=="")
	//{
	//    alert("\������ע���ʽ�");
	//	document.form1.e_register_fund.focus();
	//	return false;
	//}
	//if(!isNum(form1.e_register_fund.value))
	//{
	//    alert("\ע���ʽ���������֣�");
	//	document.form1.e_register_fund.focus();
	//	return false;
	//}
	//if(form1.e_artificial_person.value=="")
	//{
	//    alert("\�����뷨�˴������ƣ�");
	//	document.form1.e_artificial_person.focus();
	//	return false;
	//}


	if(form1.e_commission_name.value=="")
	{
	    alert("\�����������������");
		document.form1.e_commission_name.focus();
		return false;
	}
	if(form1.e_commission_identity.value=="")
	{
	    alert("\��������������֤���룡");
		document.form1.e_commission_identity.focus();
		return false;
	}
	if(!isNum(form1.e_commission_identity.value))
	{
	    alert("\���������֤������������֣�");
		document.form1.e_commission_identity.focus();
		return false;
	}
	if(form1.e_commission_mobile.value==""){
	    alert("\�������ֻ�����Ϊ�գ�");
		document.form1.e_commission_mobile.focus();
		return false;
	}
	if(!isNum(form1.e_commission_mobile.value))
	{
	   	alert("\�������ֻ����ͱ���Ϊ���֣�");
		document.form1.e_commission_mobile.focus();
		return false;
	}
	if(form1.e_mail.value=="")
	{
		alert("\����������ʼ���ַ��");
		document.form1.e_mail.focus();
		return false;
	}
	if((form1.e_mail.value.indexOf('@',0)==-1)||(form1.e_mail.value.indexOf('.',0)==-1)||(form1.e_mail.value.length<6))
	{
		alert("\��������Ϸ��ĵ����ʼ���ַ��");
		document.form1.e_mail.focus();
		return false;
	}

}


	function submitForm(){

	if(isValid()!=false){

		document.form1.CODE.value=document.form1.e_account.value;
		document.form1.pwd.value=document.form1.e_password.value;
		document.form1.name.value=document.form1.e_name.value;
		document.form1.identify.value=document.form1.e_pidentity_card.value;
		document.form1.tel.value=document.form1.e_phone.value;
		document.form1.mobile.value=document.form1.e_mobile_phone.value;
		document.form1.mail.value=document.form1.e_mail.value;
		document.form1.address.value=document.form1.e_address.value;
		document.form1.remark.value=document.form1.e_remark.value;
		document.form1.submit();
	}

}
	function resetButton(){

		document.form1.e_account.value="";
		document.form1.e_password.value="";
		document.form1.re_e_password.value="";
		document.form1.e_name.value="";
		document.form1.e_address.value="";
		document.form1.e_post_code.value="";
		document.form1.e_phone.value="";
		document.form1.e_org_code.value="";
		document.form1.e_register_fund.value="";
		document.form1.e_artificial_person.value="";
		document.form1.e_commission_name.value="";
		document.form1.e_commission_identity.value="";
		document.form1.e_commission_mobile.value="";
		document.form1.e_mail.value="";

	}

	function checkUserCode(){

	    var userCode	=document.all.item("e_account").value;
		if(userCode!=""){
			if(userCode.indexOf(" ")!=-1){
				alert("�ʺ��в��ð����ո����������룡");
			}else{
				var path="checkUserCode.jsp?userCode="+userCode;
			   	var strFeatures = "dialogWidth:300px;dialogHeight:200px;center:yes;status:no;scroll:no";
			   	var msg=window.showModalDialog(path,window,strFeatures);
			}
		}
}




  </script>
<link href="css/common.css" rel="stylesheet" type="text/css">
</head>

<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0" rightmargin="0" bottommargin="0">
<table width="100%" height="100%" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td align="center"><br>
      <table width="650" border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td align="center"> <table width="650" border="0" align="center" cellpadding="3" cellspacing="1" bgcolor="#669966" class="zy1">
              <form method="post" action="registerServer.jsp" name="form1" focus="e_account">
                <input name="modify"  type="hidden" value="1"/>
                <input name="e_type" type="hidden" value="��λ">
                <tr bgcolor="#CCFFCC">
                  <td height="25" colspan="2" align="center"><font color="#006600" size="3"><strong>�ͻ����ϵǼǱ�</strong></font></td>
                </tr>
                <tr align="center" bgcolor="#F6f6f3">
                  <td height="25" colspan="2"><strong><font color="#990000">Ϊ�˱�֤˳���ύ�������ϣ���׼ȷ��д�����������!</font></strong></td>
                </tr>
                <tr bgcolor="#FFFFFF">
                  <td height="25" align="left">�����ʺ�:<br> <font color="#666666">
                    5~20λa-z;A-Z;0-9����ĸ������� </font> </td>
                  <td height="25"> <input name="e_account" type="text" size="20" maxlength="20">
                    <font color="#FF0000">*</font>���� 
                    <input name="button" type="button" onClick="checkUserCode();" value="����ʺ�">
                  </td>
                </tr>
                <tr bgcolor="f6f6f3">
                  <td width="211" height="25" align="left"> �� ��:<br> <font color="#666666">5~20λ
                    a-z;A-Z;0-9����ĸ�������</font> </td>
                  <td height="25"> <input name="e_password" type="password" size="20" maxlength="20">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr bgcolor="#FFFFFF">
                  <td width="211" height="25" align="left"> ȷ������:<br> <font color="#FF0000"><font color="#666666">5~20λ
                    a-z;A-Z;0-9����ĸ�������</font> </font> </td>
                  <td height="25"> <input name="re_e_password" type="password" size="20" maxlength="20">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr bgcolor="f6f6f3">
                  <td height="25" align="left"> ��ҵ����:<br> <font color="#666666">������������ҵ����</font>
                  </td>
                  <td height="25"> <input name="e_name" type="text" size="20" maxlength="40">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr bgcolor="#FFFFFF">
                  <td height="25" align="left"> ��ַ:<br> <font color="#666666">����������Ч����ϵ��ַ</font><font color="red">&nbsp;</font>
                  </td>
                  <td height="25"> <input name="e_address" type="text" size="50" maxlength="200">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr bgcolor="f6f6f3">
                  <td height="25" align="left"> �ʱ�:</td>
                  <td height="25"> <input name="e_post_code" type="text" size="20" maxlength="6">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr bgcolor="#FFFFFF">
                  <td height="25" align="left"> �̶��绰:</td>
                  <td height="25"> <input name="e_phone" type="text" size="20" maxlength="20">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr bgcolor="#f6f6f3">
                  <td height="25" align="left"> ��֯��������:</td>
                  <td height="25"> <input name="e_org_code" type="text" size="20" maxlength="20">
                   </td>
                </tr>
                <tr bgcolor="#FFFFFF">
                  <td height="25" align="left"> ��ҵ����:</td>
                  <td height="25"> <input type="hidden" name="e_enterprise_type" >
                    <select name="select_enterprise_type" onChange="MM_jumpMenu(this)">
                      <option selected>------��ѡ��------</option>
                      <option>��Ӫ��ҵ</option>
                      <option>������ҵ</option>
                    </select>
                    </td>
                </tr>
                <tr bgcolor="#F6f6f3">
                  <td height="25" align="left"> ע���ʽ�/Ͷ�ʹ�ģ:</td>
                  <td height="25"> <input name="e_register_fund" type="text" size="20" maxlength="20">
                    ��Ԫ������ң� </td>
                </tr>
                <tr bgcolor="#FFFFFF">
                  <td height="25" align="left"> ���˴�������:</td>
                  <td height="25"> <input name="e_artificial_person" type="text" size="20" maxlength="20">
                    </td>
                </tr>
                <tr bgcolor="#F6f6f3">
                  <td height="25" align="left"> ����������:</td>
                  <td height="25"> <input name="e_commission_name" type="text" size="20" maxlength="20">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr bgcolor="#FFFFFF">
                  <td height="25" align="left"> ���������֤��:</td>
                  <td height="25"> <input name="e_commission_identity" type="text" size="20" maxlength="20">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr bgcolor="#F6f6f3">
                  <td height="25" align="left"> �������ֻ�:</td>
                  <td height="25"> <input name="e_commission_mobile" type="text" size="20" maxlength="20">
                    <font color="#FF0000">*</font></td>
                </tr>
                <tr bgcolor="#FFFFFF">
                  <td height="25" align="left"> �����˵�������:</td>
                  <td height="40" bgcolor="#FFFFFF">
                    <input name="e_mail" type="text" size="20" maxlength="20">
                    <font color="#FF0000">*</font> </td>
                </tr>
                <tr align="center" bgcolor="f6f6f3">
                  <td height="40" colspan="2"> <table width="20%" height="25" border="0" cellpadding="0" cellspacing="0">
                      <tr align="center">
                        <td width="50%" height="25"><a href="javascript:submitForm()"><img src="./images/1.GIF" width="50" height="25" border="0"></a></td>
                        <td width="50%" height="25"><a href="javascript:resetButton()"><img src="./images/2.GIF" width="50" height="25" border="0"></a></td>
                      </tr>
                    </table></td>
                </tr>
                  <input name="e_pidentity_card" type="hidden" size="20" value="">
                  <input name="e_mobile_phone" type="hidden" size="20" value="">
                  <input name="e_commission_phone" type="hidden" size="20" value="">
                  <input name="e_remark" type="hidden" value="">
                <input type="hidden" name="CODE" value="">
                <input type="hidden" name="pwd" id="pwd" value="">
                <input type="hidden" name="name" id="name" value="">
                <input type="hidden" name="identify" id="identify" value="">
                <input type="hidden" name="mail" id="mail" value="">
                <input type="hidden" name="address" id="address" value="">
                <input type="hidden" name="tel" id="tel" value="">
                <input type="hidden" name="mobile" id="mobile" value="">
                <input type="hidden" name="remark" id="remark" value="">
              </form>
            </table>

     </table></td></tr>

</table>
</body>
</html>
