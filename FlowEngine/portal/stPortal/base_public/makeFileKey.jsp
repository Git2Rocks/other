<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="com.minstone.fileLogin"%>
<%@ page import="oamodule.publiclib.DBService"%>
<%@ page import java.util.*%>
<%
  request.setCharacterEncoding("GBK");

  if(DBService.isAdmin(request.getRemoteUser())){

  String userCode="admin_oa";
  String userName="����";
  String userPwdBase="",userCodeBase="";
  String dirverName = request.getParameter("dirverSave");
  if(dirverName==null ) dirverName="A:";

  String actionFlag = request.getParameter("actionFlag");
  if(actionFlag==null) actionFlag="";
  if(actionFlag.equals("make")){
    String strTemp = request.getParameter("actionValue");
    StringTokenizer temp=new StringTokenizer(strTemp,";"); //�ֿ�������¼
    while(temp.hasMoreTokens()){
      String temp1 = temp.nextToken();
      fileLogin fl=new fileLogin();
    	userCodeBase=fl.getBASE64(temp1);	//�����û�
    	userPwdBase=fl.getBASE64(fl.getUserPwd(temp1)); //��������
    	if(dirverName.equals("A:")) temp1="";  //�����A�̣���ҪĿ¼
    	System.out.println(temp1+"�û�����Կ�̣�"+userCodeBase+","+userPwdBase);

%>
    <META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
    <script Language="VBScript" src="getUserFile_VB.js"></script>
    <script language="javascript">
    	  var allResult=writeIntoFile("<%=dirverName%>","<%=userPwdBase%>","WriteKey","<%=temp1%>"); //vbscriptдkey�ļ�
        if(allResult==0) {
	        var returnU=writeIntoFile("<%=dirverName%>","<%=userCodeBase%>","WriteUser","<%=temp1%>");  //vbscriptдkey�ļ�
	        if(returnU==0) {
	         alert("<%=temp1%>������Կ�̳ɹ�!");
	        }else
	         alert("<%=temp1%>������Կ��ʧ��!");
        }else
	         alert("<%=temp1%>������Կ��ʧ��!");

    </script>
<%  }
  }%>
<script>

function funMakeFileKey(){

	var temps=document.all.item("selUserCodes").value;
  if(temps=="" || temps==null){
  	temps=document.all.item("selUserNames").value;
  	if(temps=="" || temps==null){
  		temps= funcgetSelID();
  	  if(temps=="" || temps==null){
  			alert("��ѡ����ؼ�¼");return;
  	  }
  	}
  }
  document.all.item("dirverSave").value = window.prompt("������̷�","A:");

  document.all.item("actionValue").value=temps;  //��¼ѡ����û�
  document.frmMakeFileKey.action="makeFileKey.jsp";
  document.frmMakeFileKey.actionFlag.value="make";
  document.frmMakeFileKey.target="";
  document.frmMakeFileKey.submit();
}
//��ȡ��¼
function funcgetSelID(){
  var mystr="";
  var selCount=0;
  var str=document.all.item("userID");
  if(str==null) str="";
  if(str.length!=null){
	//alert("Ŀǰ�ݲ�֧������������") return;
        for(i=0;i<str.length;i++){
          if(str[i].checked){//���ÿ����¼�Ƿ���ѡ��
            mystr=mystr+str[i].value+";";
          }
        }
  }else  {
  	if(str.checked) mystr=str.value;
  }

  if(str.length!=null)	mystr=mystr.substring(0,mystr.length-1);
  return mystr;
}

//�Ƿ�ȫѡ
function funIfSelectAll(selectId,usedID){
   //usedID Ϊÿ����¼��ѡ�Ŀؼ�;selectId Ϊȫѡ�Ŀؼ�
  if(selectId.checked)
    //alert("ȫѡ");
    if(usedID.length!=null){
    	for(i=0;i<usedID.length;i++){
      usedID[i].checked=true;
    	}
    }else
    	usedID.checked=true;
  else
    //alert("��ȫѡ");
    if(usedID.length!=null){
     for(i=0;i<usedID.length;i++){
      usedID[i].checked=false;
     }
    }else
    	usedID.checked=false;
}

function funSelUserCodes(){
  var sFeatures = "dialogWidth:670px;dialogHeight:580px;center:yes;status:no";
  var sPath = "/FlowEngineWeb/workflow/Public/FrameList.jsp?selFlag=4&frameFlag=2&userCode=";
  //��ʽΪ 222:3;333:3;test1=�û�3���û�2���û�1;
  var sReturn = showModalDialog(sPath,"",sFeatures);
  if(sReturn==null)
    return;
  var aTmp = sReturn.split("=");
  document.all.item("selUserCodes").value=aTmp[0];
  document.all.item("selUserNames").value=aTmp[1];
}
</script>
<html>
<head>
<title>������Կ���ļ�
</title>
</head>
<body bgcolor="#ffffff" >
	<form name="frmMakeFileKey" method="post" action="" target="">
	  <input name="buttons" type="button" value="ѡ���û�" onclick="funSelUserCodes();"><br>
    <textArea id="selUserNames" name="selUserNames"  cols="100" rows="3" value="" size="100"></TEXTAREA>
		<input name="buttonm" type="button" value="������Կ��" onclick="funMakeFileKey();">
		<table width="100%">
		  <tr class="">
		    <td width="2%" align="left"><input type="checkbox" id="selID" onClick="javascript:funIfSelectAll(selID,userID);"></td>
		    <td width="4%" align="center"><strong>�û��ʻ�</strong></td>
		    <td width="8%" align="center"><strong>�û�����</strong></td>
		  </tr>
		  <tr bgcolor="#FFFFFF" style="cursor:hand;">
		      <td align="left" ><input type="checkbox" id="userID"  value='<%=userCode%>'></td>
		      <td align="center" ><%=userCode%></td>
		      <td align="center" ><%=userName%></td>
		  </tr>
		</table>
	<input type="hidden" name="actionFlag"  value="">
	<input type="hidden" name="actionValue" value="">
	<input type="hidden" name="selUserCodes" value="">
	<input type="hidden" name="dirverSave" value="">
	</form>
</body>
</html>
<%}else
%>��ϵͳ����Ա��
