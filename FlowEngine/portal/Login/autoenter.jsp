<%@ page contentType="text/html;charset=GBK" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head></head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��ӭ��½���ݷ�خ������������ϵͳ!</title>
<%
  //���ie����
  response.setHeader("Cache-Control", "no-store");	//HTTP 1.1
  response.setHeader("Pragma", "no-cache");		//HTTP 1.0
  response.setDateHeader("Expires", 0);			//prevents  caching   at   the   proxy
  
  //�������http://jww:8001/Login/enter.jsp?nexUrl=1,����Զ���½��ָ������ĳҳ�档
	String nexUrl=request.getParameter("nexUrl");
	if(nexUrl==null) nexUrl="";
	if(!nexUrl.equals("")) 
	  session.setAttribute("target_url_type","1");   //�ڶ���������½����ҳ��ı�ʶ

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
%>
<%

    request.setCharacterEncoding("GBK");
    String userAgent=request.getHeader("User-Agent");
    String version="",agentInfo="";
    //System.out.println("����λ�ã�"+userAgent.indexOf("v"));
    if(userAgent.indexOf("MSIE")!=-1){
      String[] version1=userAgent.split(";");
      version =version1[1];
      agentInfo=version1[version1.length-1]+";"+version1[version1.length-2];
      //System.out.println("agentInfo:"+agentInfo+","+version);
      if(agentInfo.indexOf("MAXTHON")!=-1){
        out.println("<script language='javascript'>alert('��������Ϊ���Ρ�Ϊ�˸�����ʹ�ñ�ϵͳ����ʹ��Microsoft IE6.0���߸��߰汾��');</script>");
      }
      else if(agentInfo.indexOf("Tencent")!=-1 ){
        out.println("<script language='javascript'>alert('��������Ϊ��Ѷ��Ϊ�˸�����ʹ�ñ�ϵͳ����ʹ��Microsoft IE6.0���߸��߰汾��');</script>");
      }
      else if(agentInfo.indexOf("Firefox")!=-1 ){
        out.println("<script language='javascript'>alert('��������Ϊ�����Ϊ�˸�����ʹ�ñ�ϵͳ����ʹ��Microsoft IE6.0���߸��߰汾��');</script>");
      }
      else{
          version=version.replaceAll(" ","");
	  //System.out.println("ie�汾��:"+version.substring(4,5));
          if(Integer.parseInt(version.substring(4,5))<6)
             out.println("<script language='javascript'>alert('Ϊ�˸�����ʹ�ñ�ϵͳ����ʹ��Microsoft IE 6.0����ߵİ汾����¼ϵͳ���ڡ��������ġ���Ŀ�������µ�IE����');</script>");
   }
    }else {
      out.println("<script language='javascript'>alert('����������IE�ṹ�������ȡ�Ϊ�˸�����ʹ�ñ�ϵͳ����ʹ��Microsoft IE6.0���߸��߰汾��');</script>");
    }
   
/*
IE��ҳͷ��Ϣ:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; .NET CLR 1.1.4322)
���        :Mozilla/5.0 (Windows; U; Windows NT 5.2; zh-CN; rv:1.8.1) Gecko/20061010 Firefox/2.0
��Ѷ	      :Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; TencentTraveler ; .NET CLR 1.1.4322)
����        :Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; TencentTraveler ; .NET CLR 1.1.4322; MAXTHON 2.0)
*/
%>
<SCRIPT LANGUAGE="JAVASCRIPT">
<!--
function login(){
  login_server.submit();
}

function window_onload()
{
	LoginGuest();
}

function LoginGuest()
{
	document.all.item("j_username").value='zlguest';
	document.all.item("j_password").value='11';
	login();
	
}
//-->

</SCRIPT>
<body onload="return window_onload()" >
<form name="login_server" onSubmit= method="post" action="<%=targetUrl%>/j_security_check" id="login_server" >
<table width="1006" height="640" border="0" cellpadding="0" cellspacing="0" >
        <tr> 
          <td height="27" class="enterword1" width="432"></td>
					�������롣����
          <td width="574" colspan="2">��</td>
        </tr>
				<tr>
          <td height="28" class="enterword1" width="432"></td>
          <td width="124">
					<input name="j_username" type="hidden" class="defaultinput" size="124" tabindex="1"></td>
				</tr>
				<tr> 
				  <td height="27" class="enterword1" width="432"></td>
				  <td width="124">
					<input name="j_password" type="hidden" class="defaultinput" size="124" tabindex="2"></td>

			  </tr>              
</table>
</form>
</body>
</html>
