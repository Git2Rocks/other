<%@ page contentType="text/html;charset=GBK" %>
<HTML><HEAD><TITLE>�û���¼.</TITLE>
<META http-equiv=Content-Type content="text/html; charset=gb2312">
<link href="../css/style.css" rel="stylesheet" type="text/css">
  <%
  //���ie����
  response.setHeader("Cache-Control", "no-store");	//HTTP 1.1
  response.setHeader("Pragma", "no-cache");		//HTTP 1.0
  response.setDateHeader("Expires", 0);			//prevents  caching   at   the   proxy
  
  /*
  String targetUrl=(String)session.getAttribute("j_target_url");
	if(targetUrl==null)      	targetUrl="";
	String protocol=request.getProtocol();
	if(protocol==null) protocol="";
	int index=protocol.indexOf("/");
	if(index>0){
  	protocol=protocol.substring(0,index);
	}
	if(targetUrl.equals("")){
     targetUrl=protocol+"://"+request.getServerName()+":"+request.getServerPort()+request.getContextPath()+"/stPortal/default.jsp";
	}
  */		
  %>
  
<SCRIPT language=javascript>
function login()
{
		var userName=document.all.item("j_username");
  	var passWord=document.all.item("j_password");
		if(userName.value !="" && passWord.value !=""){
			var ifCookie=document.all.item("ifCookie");
			if(ifCookie.checked){
				//alert("checked");
				SetCookie ('userName', userName.value,exp);
				SetCookie ('passWord', passWord.value,exp);
			}else{
				DeleteCookie('userName');
				DeleteCookie('passWord');
			}
  	  var ret="";
	    //��½OA gzg-exoa 10.197.32.150
			//ret=loginWithBasic("http://10.197.32.150/exoa/default.asp",userName.value,passWord.value,"1");
			//if(ret==false) return;
			//��½exchange gzg-mail 10.197.32.200
			//ret=loginWithBasic("http://10.197.32.200/exchange",userName.value,passWord.value,"2");
			//if(ret==false) return;
	    //�Ż���¼
	    login_server.submit(); 
	 	   
 	  }  else{
 	  	alert("�û���������Ϊ��!");
 	  } 
		
}
//����xmlHttp 
  function CreateXMLHttp()
  {
   var xmlHttp = false;
   if(typeof XMLHttpRequest != 'undefined')
   {
    xmlHttp = new XMLHttpRequest();
    return xmlHttp;
   }else if(window.ActiveXObject)
   {
    var IEXMLHttpVersion =["MSXML2.XMLHttp.4.0","MSXML2.XMLHttp.3.0","MSXML2.XMLHttp.5.0","MSXML2.XMLHttp.6.0","MSXML2.XMLHttp","Microsoft.XMLHttp"];
    //ѭ��΢��IE�汾
    for(var i= 0 ;i < IEXMLHttpVersion.length; i++)
    {
     try
     {
        var xmlHttp = new ActiveXObject(IEXMLHttpVersion[i]);
        return xmlHttp;
     }catch(e)
     {
       //alert(i);alert(xmlHttp);
       xmlHttp= false;
     }
    }      
    }else
    {
     throw new Error("XMLHttp object could be created.");
     xmlHttp= false;
    }
    return xmlHttp;
  }
function loginWithBasic(url,userCode,passWord,sysID){

	  var sysTishi="";
		//alert(url+userCode+passWord);
		var xmlhttp = CreateXMLHttp();// new ActiveXObject("Msxml2.XMLHTTP.3.0");
    //alert(typeof xmlhttp);alert(xmlhttp);
		if( typeof xmlhttp !="object"){
			document.all.item("xmlHttpType").value=typeof xmlhttp;
			if(xmlhttp==false){
			 var url="setupXML.htm";
			 var sFeatures= "dialogHeight:300px;dialogWidth:400px;";
  		 sFeatures = sFeatures + "center:yes;edge:raised;scroll:auto;status:no;unadorned:yes;"
  		 window.showModalDialog(url,window,sFeatures);
			 return false;
			}
		}
		//alert("new");
		xmlhttp.open("GET",url, false,userCode,passWord);
		//alert("open");
		xmlhttp.send();
		//alert("send");
		var book = xmlhttp.status;
		if(book!="200"){
			if(sysID=="1")
				sysTishi="OAϵͳ";
			else
				sysTishi="����ϵͳ";
			//alert("���ε�¼ʧ�ܣ����ش�����룺"+book+"���Ż�ϵͳ��"+sysTishi+"���û����벻һ�¡�");
		}

}
function keyDown() { 
	//var keycode = String.fromCharCode(event.keyCode);
 	if ( event.keyCode == "13" ){
 	 var userName=document.all.item("j_username");
   var passWord=document.all.item("j_password");
   if(userName.value =="" ) {         	
     	alert("�û����ܿ�!");
     	userName.focus();
     	return;
   }
   if(userName.value !="" && passWord.value ==""){
   		//alert("���벻�ܿ�!");     	
    	passWord.focus();
    	return;
    }
   login();
 }  
}
function selectAll(id){
	id.select();
}
</SCRIPT>

<SCRIPT language=javascript>
<!-- Begin
var expDays = 30;
var exp = new Date(); 
exp.setTime(exp.getTime() + (expDays*24*60*60*1000));

//cookie������
function SetCookie (name, value) {
	var argv = SetCookie.arguments;  
	var argc = SetCookie.arguments.length;  
	var expires = (argc > 2) ? argv[2] : null;  
	var path = (argc > 3) ? argv[3] : null;  
	var domain = (argc > 4) ? argv[4] : null;  
	var secure = (argc > 5) ? argv[5] : false;  
	document.cookie = name + "=" + escape (value) + 
	((expires == null) ? "" : ("; expires=" + expires.toGMTString())) + 
	((path == null) ? "" : ("; path=" + path)) +  
	((domain == null) ? "" : ("; domain=" + domain)) +    
	((secure == true) ? "; secure" : "");
}
//Cookie��ɾ��
function DeleteCookie (name) {
	var exp = new Date();  
	exp.setTime (exp.getTime() - 1);  
	var cval = GetCookie (name);  
	document.cookie = name + "=" + cval + "; expires=" + exp.toGMTString();
}
//ȡCookie��ֵ
function getCookieVal (offset) {
	var endstr = document.cookie.indexOf (";", offset);  
	if (endstr == -1)    
	endstr = document.cookie.length;  
	return unescape(document.cookie.substring(offset, endstr));
}
//ȡCookie��ֵ
function GetCookie (name) {
	var arg = name + "=";  
	var alen = arg.length;  
	var clen = document.cookie.length;  
	var i = 0;  
	while (i < clen) {
		var j = i + alen;    
		if (document.cookie.substring(i, j) == arg)      
		return getCookieVal (j);    
		i = document.cookie.indexOf(" ", i) + 1;    
		if (i == 0) break;   
	}  
	return null;
}
//ȡ�û��������cookie
function getUserPwdCookie () {
	var temp=GetCookie('userName');
	if(temp==null ) temp="";
	document.all.item("j_username").value=temp;
	temp=GetCookie('passWord');
	if(temp==null ) temp="";
	document.all.item("j_password").value=temp;
	if(temp!=null){
		 document.all.item("ifCookie").checked=true;
	}
	
}
//  End -->
</SCRIPT>

<META content="MSHTML 6.00.3790.2491" name=></HEAD>
<BODY  margin="2" scroll="no" onload="getUserPwdCookie();">
<TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
  <TBODY>
  <TR>
    <TD class=SubTitle align=left width="80%"><IMG height=15 
      src="../images/arrow_login.gif" width=15 align=absMiddle border=0> 
  �û���¼</TD></TR>
  <TR vAlign=top>
    <TD class=subWebTab align=left colSpan=2>
      <FORM id="login_server" name="login_server" action="j_security_check" method="post"  target=_top>
      <TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
        <TBODY>
        <TR class=subTab align=middle>
          <TD vAlign="bottom" height="30">�û��� <INPUT class="textfield" maxLength="20" 
            size="16" id="j_username" name="j_username" onkeydown="javascript:keyDown();" onclick="javascript:selectAll(this);" onfocus="javascript:selectAll(this);"></TD></TR>
        <TR class="subTab" align=middle>
          <TD vAlign="bottom" height="30">���룺
          <INPUT class="textfield" type="password" 
            maxLength="20" size="16" id="j_password" name="j_password" onkeydown="javascript:keyDown();" onclick="javascript:selectAll(this);" onfocus="javascript:selectAll(this);">
          <input type="hidden" name="j_forwardurl" size="9" value="/stPortal/default.jsp">
          </TD></TR>
        <TR align=right>
          <TD vAlign="bottom" height="30">
<!--<INPUT class=GoBt id=button onclick="openregister()" type=button value=ע�� name=button target="_top"> -->
��¼�û�����<INPUT  id="button"  type="checkbox" name="ifCookie">
<INPUT class="GoBt" id="button" onclick="javascript:login();" type="button" value="��¼" name="button"> 
<INPUT class="GoBt" id="button" type="reset" value="ȡ��" name="button"> 
        </TD></TR></TBODY></TABLE></FORM>
      <TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
        <TBODY>
        <TR onmouseover="this.style.backgroundColor='#f1f1f1';" onmouseout="this.style.backgroundColor='#ffffff';" align=right>
          <TD colspan=3 class=subTab vAlign=bottom align=left height="">
          	���ڴ˵�¼�칫�Զ���ϵͳ��
          	<A href="/res/UserGuideBook/readmeOA.htm" target="_blank">
          		Ϊ�˸��ð칫��������ʹ�û�����</A></TD>        
        </TR>
        </TBODY></TABLE></TD></TR></TBODY></TABLE>
<SCRIPT language=javascript>
	document.all.item("j_username").focus();
</SCRIPT>
<INPUT type="hidden" name="xmlHttpType"  value=""> 
</BODY></HTML>
