<%@ page contentType="text/html;charset=GBK" %>
<%@ page import="shecasafeapi.SafeEngine" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<title>CA�û���¼!</title>
<head></head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link href="../css/style.css" rel="stylesheet" type="text/css">
<style type="text/css">
</style>
<%
	if (request.getProtocol().compareTo("HTTP/1.0") == 0)
		response.setHeader("Pragma", "no-cache");
	else if (request.getProtocol().compareTo("HTTP/1.1") == 0)
		response.setHeader("Cache-Control", "no-cache");
	response.setDateHeader("Expires", 0);

	//begin ca
	String userDir = System.getProperty("user.dir");
    String fileSeparator = System.getProperty("file.separator");
    String path=userDir+fileSeparator+"CA"+fileSeparator;
  	shecasafeapi.SafeEngine myobj = new shecasafeapi.SafeEngine();
	String strServerCert = "",strRandom = "",strCert = "",strSigned = "", strEnvelope = "";
	int i = 0;
	//�豸���ͣ�9--usb��2--�ļ�
    int PriKeyDevType=9;
    String strPrivKeyDevParam="COM1";
	String strPriKeyPass="123456";
    int lPriKeyTimeout=0;
	//�豸���ͣ�9--usb��2--�ļ�
    int CertChainDevType=9;
    String strCertChainDevParam="COM1";
	String strCertChainPass="123456";
	//�豸���ͣ�9--usb��2--�ļ�
	int CertDevType=9;
    String strCertDevParam="COM1";
	String strCertPass="123456";
    boolean isUsb=false;
    if(!isUsb){
    	//�豸���ͣ�9--usb��2--�ļ�
    	PriKeyDevType=2;
    	strPrivKeyDevParam=path+"userkey.key";
		strPriKeyPass="123456";
    	lPriKeyTimeout=1000;
		//�豸���ͣ�9--usb��2--�ļ�
    	CertChainDevType=2;
    	strCertChainDevParam=path+"CertChain.spc";
		strCertChainPass="123456";
		//�豸���ͣ�9--usb��2--�ļ�
		CertDevType=2;
    	strCertDevParam=path+"usercert.der";
		strCertPass="123456";
	}
    //=====================================================
    i=myobj.shecaInitEnviroment(PriKeyDevType,strPrivKeyDevParam, strPriKeyPass, lPriKeyTimeout, CertChainDevType, strCertChainDevParam, strCertChainPass);
	  String actionFlag=request.getParameter("actionFlag");
	  if(actionFlag==null) actionFlag="";
    if(!actionFlag.equals("login")){
    	if (i!=0){
			out.println("<script>alert(\"��ʼ��safeengine����:"+i+"\");</script>");
			myobj.shecaClearEnviroment();
		  }
      else{
      //out.println("<script>alert(\"��ʼ��safeengine�ɹ�:"+i+"\");</script>");
			//��ȡ������֤��
			//strServerCert = myobj.shecaGetSelfCertificate(2, path+"usercert.der", "");
      strServerCert = myobj.shecaGetSelfCertificate(CertDevType, strCertDevParam, strCertPass);
			if (myobj.getErrorCode()!=0){
				out.println("<script>alert(\"��ȡ������֤�����\");</script>");
				myobj.shecaClearEnviroment();
			}
			else{
				//out.println("<script>alert(\"��ȡ������֤��ɹ�\");</script>");
				//���������
				java.util.Random RandNum = new java.util.Random();
				int RandomData = RandNum.nextInt(1000000);
				strRandom = ""+ RandomData;
				session.putValue("random",strRandom);
			}
		}
        //end ca
		String submitCount=(String)session.getAttribute("submitCount");
		if(submitCount==null)
		submitCount="0";
		int iSubCount=Integer.parseInt(submitCount);
        String rSrvPort=String.valueOf(request.getServerPort());
        String rSrvName=request.getServerName();
		String targetUrl=(String)session.getAttribute("j_target_url");
		if(targetUrl==null)
        	targetUrl="";
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

<SCRIPT LANGUAGE="JAVASCRIPT">
<!--
function login(){
  document.all.item("actionFlag").value="login";
  login_server.submit();
}
function reset(){
    login_server.reset();
}
function window_onload(){
    document.all.item("pwd").focus();
}
function checkUserPwd(){
    if(doTest()){
    	login();
    }
}
//-->
</SCRIPT>
<BODY  margin="2" scroll="no">
<OBJECT ID="SafeEngineCtl" CLASSID="CLSID:B48B9648-E9F0-48A3-90A5-8C588CE0898F" width="0" height="0" border=0 codebase="SafeEngineCOM.cab#Version=1,2,0,0" ></OBJECT>
<form name="login_server" method="post" action="userlogin_ca.jsp" id="login_server" >
	<TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
        <TR class=subTab align=middle>
          <TD vAlign=bottom height=30>CA�û���<INPUT class=textfield maxLength=20 
            size=16 name="username"></TD></TR>
        <TR class=subTab align=middle>
          <TD vAlign=bottom height=30>CA���룺<INPUT class=textfield type=password 
            maxLength=20 size=16 name="pwd"> </TD></TR>
        <TR align=right>
          <TD vAlign=bottom height=30>
          	<!--<INPUT class=GoBt id=button onclick="openregister()" type=button value=ע�� name=button target="_top"> -->
						<INPUT class=GoBt id=button onclick=javascript:login(); type=submit value=��¼ name=button> 
						<INPUT class=GoBt id=button type=reset value=ȡ�� name=button> 
					<input type="hidden" name="actionFlag" value="">
					<input type=hidden name=sCert value="<%=strCert%>">
					<input type=hidden name=sSign value="<%=strSigned%>">
					<input type=hidden name=sEnvelope value="<%=strEnvelope%>">
         </TD>
        </TR></TBODY></TABLE>
</form>

<!------ca��֤ ��javascript------start----->
<script languang="javascript" src="ca.js"></script>
<script languang="javascript">
function toStr(code){
	return printStatus(code)+"!ErrorCode="+code;
}
function doTest()
{
	/* Change the path and password below */
	strpassword=document.login_server.pwd.value;

	/* ��ʼ������usb */
	SafeEngineCtl.SEH_InitialSession(9,"COM1", strpassword, 0, 9, "COM1", strpassword);
	if(SafeEngineCtl.ErrorCode!=0)
	{
		alert("��½ʧ��,"+toStr(SafeEngineCtl.ErrorCode));
		return false;
	}
	/* ��ȡ�Լ�֤�� */
	strCert = SafeEngineCtl.SEH_GetSelfCertificate(9,"COM1",strpassword);
	if(SafeEngineCtl.ErrorCode!=0)
	{
		alert("SEH_GetSelfCertificate Error. Return:" + toStr(SafeEngineCtl.ErrorCode));
		return false;
	}
	document.login_server.sCert.value = strCert;
	/*��ȡ�û���*/
	var certUserName=SafeEngineCtl.SEH_GetCertDetail(strCert,17);
	var userName=document.login_server.username.value;
    if(certUserName!=userName){
		alert("�û�����֤���û�����ƥ�䣡");
		return false;
    }
	/* ��֤������֤�� */
	SafeEngineCtl.SEH_VerifyCertificate("<%=strServerCert%>");
	if(SafeEngineCtl.ErrorCode!=0)
	{
		alert("SEH_VerifyCertificate Error. Return:" +toStr(SafeEngineCtl.ErrorCode));
		SafeEngineCtl.SEH_ClearSession();
		return false;
	}

	/* ǩ������� */
	strSigned = SafeEngineCtl.SEH_SignData("<%=strRandom%>", 3);
	if(SafeEngineCtl.ErrorCode!=0)
	{
		alert("SEH_SignData Error. Return:" + toStr(SafeEngineCtl.ErrorCode));
		SafeEngineCtl.SEH_ClearSession();
		return false;
	}
	document.login_server.sSign.value = strSigned;

	/* �÷�����֤���������� */
	strEnvelope = SafeEngineCtl.SEH_Envelope(1, "<%=strRandom%>", "<%=strServerCert%>");
	if(SafeEngineCtl.ErrorCode!=0)
	{
		alert("SEH_Envelope(Enc) Error. Return:" + toStr(SafeEngineCtl.ErrorCode));
		SafeEngineCtl.SEH_ClearSession();
		return false;
	}
	document.login_server.sEnvelope.value = strEnvelope;

	/* �ͷ� */
	SafeEngineCtl.SEH_ClearSession();
	return true;
}
</script>
<%}else{
boolean bCaPass=false;
if (i != 0){
	System.err.print("��ʼ��safeengine����"+i);
	myobj.shecaClearEnviroment();
}
else{
	strServerCert  = myobj.shecaGetSelfCertificate(CertDevType, strCertDevParam, strCertPass);
	if (myobj.getErrorCode() != 0){
		System.out.println("<script>alert(\"��ȡ������֤�����\");</script>");
		myobj.shecaClearEnviroment();;
	}
	else{
		String strClientCert = request.getParameter("sCert");
		strSigned = request.getParameter("sSign");
		strEnvelope = request.getParameter("sEnvelope");
		//��֤�ͻ���֤��
		i=myobj.shecaVerifyCertificate(strClientCert);
		if (i!=0){
			System.err.println("<script>alert(\"��֤�ͻ���֤�����\");</script>");
			myobj.shecaClearEnviroment();
		}
		else{//���������ŷ�
			String strData = myobj.shecaEnvelope(2, strEnvelope, strServerCert);
			if (myobj.getErrorCode() != 0){
				System.err.println("<script>alert(\"�������ŷ����\");</script>");
				myobj.shecaClearEnviroment();
			}
			else{
				//��֤�ͻ���ǩ��
				i=myobj.shecaVerifySignData(strData, 3, strSigned, strClientCert);
				if (i != 0){
					System.err.println("<script>alert(\"��֤ǩ������\");</script>");
					myobj.shecaClearEnviroment();
				}
				else{
					myobj.shecaClearEnviroment();
					//String a=session.getValue("random");
					if (!(session.getValue("random").equals(strData))){
						System.err.println("���������strData is "+strData+"\nsession is "+session.getValue("random"));
					}
					else{
						//CA֤����֤ͨ��
						bCaPass=true;
					}
				}			// end if VerifySignData
			}				//end if Envelope
		}					//end if VerifyCertificate
	}						//end if GetSelfCertificate
}							//end if InitEnviroment
if(bCaPass){
	String loginPwd=request.getParameter("pwd");
	String loginUser=request.getParameter("username");
	System.err.println("username="+loginUser+"pwd="+loginPwd);
%>
<body>
<form name="formLogin" method="post" action="<%=request.getContextPath()%>/j_security_check">
<input name="j_password" type="hidden" value="<%=loginPwd%>">
<input name="j_username" type="hidden" value="<%=loginUser%>">
</form>
</body>
</html>
<script language="javascript">
   document.formLogin.submit();
</script>
<%}else{
	response.sendRedirect("userlogin_ca.jsp");
}
}
%>

