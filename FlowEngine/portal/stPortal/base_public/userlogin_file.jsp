<%@ page contentType="text/html;charset=GBK" %>
<%@ page import="com.minstone.fileLogin"%>
  <script type="text/VBScript" src="getUserFile_VB.js"></script>
  <%
  //���ie����
  response.setHeader("Cache-Control", "no-store");	//HTTP 1.1
  response.setHeader("Pragma", "no-cache");		//HTTP 1.0
  response.setDateHeader("Expires", 0);			//prevents  caching   at   the   proxy
  %>
  <%
  request.setCharacterEncoding("GBK");
  String actionFlag = request.getParameter("actionFlag");
  if(actionFlag==null) actionFlag="";
  String newLoginFlag = request.getParameter("newLoginFlag");
  if(newLoginFlag==null) newLoginFlag="";

  if(actionFlag.equals("fileLoginFlag")){
    String user = request.getParameter("j_username");
    String pwd = request.getParameter("j_password");
    String newPwd="",newPwdBase="",oldPwd="";
    String driverS=request.getParameter("driveSource");
    if(driverS==null) driverS="A:";
    boolean ifOk=false;
    fileLogin fl=new fileLogin();
    if(newLoginFlag.equals("newLogin")){
      //System.out.println("newLogin:"+newLoginFlag);
      oldPwd=request.getParameter("oldPwd");
      newPwd=pwd;
      try{
        //System.out.println(user+oldPwd+newPwd);
        if(fl.updatePwd(user,oldPwd, newPwd)){
          //System.out.println("���³ɹ���");
          %>
          <html>
          <head>
          </head>
          <body >
          <form name="getFileLogin3" id="getFileLogin3" method="post" action="j_security_check">
          <input type="hidden" name="j_username" value="<%=user%>">
          <input type="hidden" name="j_password" value="<%=pwd%>">
          </form>
          </body>
          </html>
          <script type="text/javascript">
          	//alert("newlogin:<%=user%><%=pwd%>");
	          document.getFileLogin3.submit();
          </script>
          
          <%}
          }catch (Exception ex){
            System.out.println( user+"���������뵽���ݿ�ʧ��!");
          }
        }
        else{
          try{
            //System.out.println("����ǰ�û������룺"+user+","+pwd+","+driverS);
            user=fl.getFromBASE64(user);
            pwd=fl.getFromBASE64(pwd);
            oldPwd=pwd;

            //System.out.println("���ܺ��û������룺"+user+","+oldPwd+","+driverS);
            try{
              if(fl.updatePwd(user,oldPwd, oldPwd)){ //��֤�Ƿ����д�����ݿ�
              	ifOk = true;
              }else{%>
              	<script type="text/javascript">
	            	  alert("�����û��������������ȷ�ԡ�");
	            	  document.location="/stPortal/default.jsp";
	              </script>
	              <%
            	}
              //System.out.println( user+"��֤�Ƿ����д�����ݿ�ɹ�!");
            }catch (Exception ex){
              System.out.println( user+"��֤�Ƿ����д�����ݿ�ʧ��!");
            }

            if(ifOk){
              newPwd=fl.getStrRandom(99999999);
              pwd=newPwd;  //���������½�����Ұ����������֮��д��������
              newPwdBase=fl.getBASE64(newPwd);
              %>
              <html>
              <head>
              <script type="text/javascript">
              function window_onload2(){
                document.getFileLogin2.target="_top"
                var ifok="-1";
                var s="<%=newPwdBase%>";
                ifok=writeIntoFile("<%=driverS%>","<%=newPwdBase%>","WriteKey","");  //vbscriptдkey�ļ�
                if(ifok=="-1"){
                  alert("������д��key��ʧ�ܣ�����ϵ����Ա���IE��ȫ��������ã�");
                  document.getFileLogin2.action="/stPortal/default.js";
                }else{
                  var allResult=getfileContent();
                  var s1=allResult.split(";");
                  s1=s1[1];
                  if(s!=s1){
                    alert("У��д����Կ�̵������벻��ȷ������ϵ����Ա���IE��ȫ��������á�");
                    document.getFileLogin2.action="/stPortal/default.js";
                  }else{
                    //�ύ��֤�������޸����ݿ�
                    document.getFileLogin2.action="userlogin_file.jsp";
                    document.getFileLogin2.actionFlag.value="fileLoginFlag";
                    document.getFileLogin2.newLoginFlag.value="newLogin";
                  }
                }

                document.getFileLogin2.submit();
              }
              </script>
              </head>
              <body onload="javascript:window_onload2();">
              <form name="getFileLogin2" id="getFileLogin2" method="post" action="j_security_check">
              <input type="hidden" name="j_username" value="<%=user%>">
              <input type="hidden" name="j_password" value="<%=pwd%>">
              <input type="hidden" name="oldPwd" value="<%=oldPwd%>">
              <input type="hidden" name="actionFlag" value="">
              <input type="hidden" name="newLoginFlag" value="">
              </form>
              </body>
              </html>
              <%
              }              
            }catch (Exception ex){%>
              <script type="text/javascript">
	            	  alert("��Կ�������д����������Ա��ϵ������������"+"<%=ex%>");
	            	  document.location="/stPortal/default.jsp";
	            </script>
            <%}
          }
        }
        else{
          %>

          <HTML><HEAD><TITLE>�û���¼��</TITLE>
            <META http-equiv=Content-Type content="text/html; charset=gb2312">
              <META content="Microsoft.Net" name=Creator>
                <link href="../css/style.css" rel="stylesheet" type="text/css">

                <SCRIPT type="text/javascript">
                function login()
                {
                  var allResult=ifOkDriverFile();  //vbscriptȡkey�ļ�
                  if(allResult=="-1") {
                    alert("��ȡ��Կ�������⣬��ȷ��:��Կ���Ƿ��Ѿ����롢�Ƿ�д����;��Կ�ļ��Ƿ��д��ȷ��������ϵ����Ա�����Ļ����������á�");
                    return;
                  }else{
                    allResult=getfileContent();
                    if(allResult=="-1") {
                      alert("��ȡ��Կ������ʧ�ܣ���ȷ���Ƿ������Կ��.");
                      return;
                    }
                    var result=allResult.split(";");
	                  document.all.item("j_username").value=result[0];
	                  document.all.item("j_password").value=result[1];
	
	                  if(result[0]=="") {
	                    alert("��ȡ��Կ���û�����ʧ�ܣ���ȷ����Կ�̵��û��ļ��Ƿ���ȷ.");
	                    return;
	                  }
	                  if(result[1]=="") {
	                    alert("��ȡ��Կ����������ʧ�ܣ���ȷ����Կ�̵������ļ��Ƿ���ȷ��");
	                    return;
	                  }
                  }
                  
                  document.login_server.action="userlogin_file.jsp";
                  document.login_server.actionFlag.value="fileLoginFlag";
                  document.login_server.driveSource.value=result[2];
                  document.login_server.target="_top"

                  document.login_server.submit();
                }

                function keyDown() {
                  //var keycode = String.fromCharCode(event.keyCode);
                  if ( event.keyCode == "13" ){
                    var oUserName=document.all.item("j_username");
                    var oPwd=document.all.item("j_password");
                    if(oUserName.value =="" ) {
                      alert("�û����ܿ�!");
                      oUserName.focus();
                    }
                    if(oUserName.value !="" && oPwd.value ==""){
                      //alert("���벻�ܿ�!");
                      oPwd.focus();
                    }
                    if(oUserName.value !="" && oPwd.value !="")
                    login();
                  }
                }
                </SCRIPT>

                <META content="MSHTML 6.00.3790.2491" name=></HEAD>
                <BODY  margin="2" scroll="no">
                  <TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
                    <TBODY>
                      <TR>
                        <TD class=SubTitle align=left width="80%">
                          <IMG height=15 src="../images/arrow_login.gif" width=15 align=absMiddle border=0>
                            �û���¼</TD></TR>
                            <TR vAlign=top>
                              <TD class=subWebTab align=left colSpan=3>
                                <FORM id="login_server" name="login_server" action="j_security_check" method="post"  target="_top">
                                  <TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
                                    <TBODY>
                                      <TR class="subTab" align="middle" style="visibility:hidden">
                                        <TD vAlign="bottom" height="30">
                                          �û��� <INPUT class="textfield" maxLength="20" value="" size="16" id="j_username" name="j_username" onkeydown="javascript:keyDown();"></TD></TR>
                                          <TR align=right>
                                            <TD vAlign="bottom" height="30" >
                                              <SPAN align="LEFT" style="COLOR:RED;FONT:12pt">�������Կ�̣������¼��</SPAN>
                                              <!--<INPUT class=GoBt id=button onclick="openregister()" type=button value=ע�� name=button target="_top">-->
                                                <!--<INPUT class="GoBt" id="button" onclick="javascript:login();" type="button" value="��¼" name="button">-->
                                                  <INPUT class="GoBt" id="button" type="reset" value="ȡ��" name="button" style="visibility:hidden">
                                                    <input type="hidden" name="actionFlag" value="">
                                                    <input type="hidden" name="driveSource" value="">

                                            </TD></TR>
                                            <TR class="subTab" align="middle" style="visibility:">
                                              <TD vAlign="bottom" height="30">
                                                <INPUT class="GoBtPicture" id="button" onclick="javascript:login();" type="button" value="" name="button">
                                              </TD></TR>
                                              <TR class="subTab" align="middle" style="visibility:">
                                                <TD vAlign="bottom" height="30">
                                                </TD></TR>
                                                <TR>
                                                  <TD colspan=3 class=subTab vAlign=bottom align=left height="" style="FONT:10pt">
                                                    <A href="/STPublish/view/ViewRecord.jsp?id=2518" target="_blank">
                                                      Ϊ���ð칫�������û�����</A></TD>
                                                </TR>
                                                <TR class="subTab" align="middle" style="visibility:hidden">
                                                  <TD vAlign="bottom" height="30">
                                                    ���룺 <INPUT class="textfield" type="password" value="" maxLength="20" size="16" id="j_password" name="j_password" onkeydown="javascript:keyDown();"> </TD></TR>

                                    </TBODY></TABLE></FORM>

                                                  </TD></TR></TBODY></TABLE>
                                                  <SCRIPT language=javascript>
                                                  //��������ʹ��focus
                                                  //document.all.item("j_username").focus();
                                                  </SCRIPT>
                                                  </BODY></HTML>
                                                  <%}%>
