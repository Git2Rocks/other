<%@ page language="java" import="java.util.*" pageEncoding="GBK"%>
<%@taglib prefix="c" uri="http://java.sun.com/jstl/core"%>
<%
//String rootPath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+request.getContextPath(); 
String rootPath =request.getContextPath(); 
%>
<link rel="stylesheet" type="text/css"
	href="<%=rootPath%>/stPortal/Common/Css/IM.css">
<title>��<c:out value='${receiver}'/>������</title>
<script language="javascript"
	src="<%=rootPath%>/stPortal/Common/Include/HttpSubmit.js"></script>
<script language="vbscript"
	src="<%=rootPath%>/stPortal/Common/Include/encode.vbs"></script>
<script type="text/javascript">
function oper(operMethod){
//func='save'����
//func='send'����
var receiver_code=MsgFram.all.receiver_code.value;
var sendid=MsgFram.all.sendid.value;
//var content=MsgFram.all.content.value;
var msgInfo=MsgFram.content.value;
//alert("receiver_code="+receiver_code+" msgInfo="+msgInfo);
  if(msgInfo==null||msgInfo.length==0)
	{
	alert("��Ϣ���ݲ���Ϊ�գ�");
	  return;
	}
  if(msgInfo.length>400)
	{
	  alert("���͵���Ϣ���ݹ���");
	  return;
	}
var spath = 'service=msg&func='+operMethod+"&receiver_code="+receiver_code+"&content="+msgInfo;
	if(sendid!="" && sendid!=null){
	spath +="&sendid="+sendid;
	}
    msg = HttpSubmitString(spath,"<%=rootPath%>/stPortal/portalSvl");
  if (msg== '0'){ 
      	  alert("����ʧ�ܡ���");   
    	   return ;
     }else if(msg!= '0' && msg!=null){
     if(operMethod=="send")
	      MsgFram.content.value="";
	   //getRcvMsg();
	   //ȡ��ǰʱ��
	   var currentDate = new Date();  //��ǰ����
	   var date = currentDate.getDate(); //��ǰ����
	   date = ((date < 10) ? "0" : "") + date;
	   var month = currentDate.getMonth() + 1; //��ǰ�·�
	   month = ((month < 10) ? "0" : "") + month;
	   var year=currentDate.getYear();
	   var hours = currentDate.getHours();
	   hours = ((hours < 10) ? "0" : "") + hours;
	   var minutes = currentDate.getMinutes();
	   minutes = ((minutes < 10) ? "0" : "") + minutes;
	   var seconds = currentDate.getSeconds();
	   seconds = ((seconds < 10) ? "0" : "") + seconds;
	   var currentTime=year+"-"+month+"-"+date+" "+hours+":"+minutes+":"+seconds;
	   var message='\n['+" "+currentTime+' ] <c:out value="${sender}"/> ˵��'+'\n  '+msgInfo;
	   document.frames("docRcvMsg").document.body.innerText+=message;
	   getToButton();
	   if(operMethod=='save'){
	   document.getElementById("sendid").value=message;
	   alert("����ɹ���");
	   }
     return true;
	}else{
		alert("�������ʧ��");
		return false;
	}
    //var b= window.confirm("������ͳɹ�����,�Ƿ�رձ༭����?");   
    //if(b)this.close();     
}

function recall(){
var receivercode=document.getElementById("sender_code").value;
var sendid=MsgFram.all.sendid.value;
var content=MsgFram.all.content.value;
if(sendid==""){
alert("����������,���ܻظ�!");
return;
}
window.location="<%=rootPath%>/stPortal/portalSvl?service=msg&func=showEditWindow&flg=recall&receiver_code="+receivercode;
}

NS4 = (document.layers) ? true : false;
function checkEnter(element){     
    var code = 0;
    if (NS4)
        code = this.event.which;
    else
        code = this.event.keyCode;
    if (code==13){
         if(element.name=='content')//content-�ı����Name
         {
       		oper('send');
	   		document.all.item("content").focus();
		 }
	}
}

//�õ����µļ�¼
function getRcvMsg()
{
var receiver_code=MsgFram.receiver_code.value;
var receiver=MsgFram.receiver.value;
var spath='<%=rootPath%>/stPortal/portalSvl?service=msg&func=newMsgs&receiver_code='+receiver_code;
document.frames("docRcvMsg").location=spath;
//document.frames("docRcvMsg").location.reload();
  }
//�ѹ���������Ϊ��׶�
function getToButton()
{
  document.frames("docRcvMsg").scrollTo(0,document.frames("docRcvMsg").document.body.scrollHeight);
}
</script>
<body scroll="no" leftMargin="2" topMargin="2">
	<form name="MsgFram" action="">
		<input type="hidden" name="sender_code"
			value="<c:out value='${sender_code}'/>">
		<input type="hidden" name="receiver_code"
			value="<c:out value='${receiver_code}'/>">
		<input type="hidden" name="receiver"
			value="<c:out value='${receiver}'/>">
		<input type="hidden" name="sendid" id="sendid" value="<c:out value='${sendid}'/>">

		<table width="100%" align="center" border="0" cellpadding="0"
			cellspacing="0" class="tablebg">
			<tr>
				<td align="left">
					<legend>
						<Iframe id="docRcvMsg" name="docRcvMsg"
							src='<%=rootPath%>/stPortal/OnlineUser/ListMsgWin.jsp'
							width="100%" height="170px" scrolling="auto" frameborder="no"
							border="0" framespacing="0" noresize leftMargin="0" topMargin="0"></Iframe>
					</legend>
				</td>
			</tr>
		</table>
		<table width="100%" align="center" border="0" cellpadding="0"
			cellspacing="1" class="tablebg">
			<tr>
				<td align="center">
					<fieldset>
						<legend>
							<font size="2">������Ϣ</font>
						</legend>
						<TEXTAREA NAME="content" ROWS="6" COLS="89" class="pop_input" onKeyPress="checkEnter(this);"
							style="background-image:url(./stPortal/images/IM/frame_bg.gif);"></TEXTAREA>
					</fieldset>
				</td>
			</tr>
		</table>
		<table width="100%">
			<tr>
				<td align="right">
					<c:choose>
						<c:when test="${empty sendid}">
						<INPUT TYPE="button" name="" onClick="oper('send');" value="����"
						style="padding: 2 4 0 4;font-size:12px;height:23;background-color:#ece9d8;border-width:1;cursor:hand">
						</c:when>
						<c:otherwise>						
						<INPUT TYPE="button" name="" onClick="recall();" value="�ظ�"
						style="padding: 2 4 0 4;font-size:12px;height:23;background-color:#ece9d8;border-width:1;cursor:hand">
					</c:otherwise>
					</c:choose>
					<INPUT TYPE="button" name="" onClick="window.close();" value="�ر�"
						style="padding: 2 4 0 4;font-size:12px;height:23;background-color:#ece9d8;border-width:1;cursor:hand">
				</td>
			</tr>
		</table>
	</form>