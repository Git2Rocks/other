<%@ page contentType="text/html; charset=GBK" %>

<%
  //ǿ��ҳ��ˢ��
  response.setHeader("Pragma","No-cache");
  response.setHeader("Cache-Control","no-cache");
  response.setDateHeader("Expires", 0);
%>

<html>
<head>
<link href="/stPortal/images/new.css" rel="stylesheet" type="text/css">
<jsp:useBean id="UserConform" scope="page" class="net.kingsoft.user.UserConform"/>
</head>
<body bgcolor="#FFFFFF" text="#000000">
<%
/**����˵��
<��ҳ>
���ڵ�����������,��ʵֻ�����򵥵ĸĶ�,���ǿ�ʼ�߼��Ƚ���,���˰���ſ���, �������������㷨û�б�, Ϊ��ֹ���˸���һ����, ������ʵʵд��ע��....
˼·: ÿ������ҳ��ǰ, ������������:
pPage				��ǰҳ��
mMode				�����������, ��Ϊ��ҳ����ҳ�ļ���˳���ǲ�ͬ��
mUserName		��һ��ҳ�濪ʼ���Ǹ��û�.
�������
MAX					ÿҳ�����ʾ��Ŀ
mAllRows			�ܼ�¼��
mAllPage			��ҳ��
resultRow			ʣ������, �����һҳ����MAX������ʱ, ȡʵ��ʣ���ֵ
�����������...*/
int MAX=10;
UserConform.setMAXROW(MAX);
int resultRow=0,mPage,mAllRows,mAllPage,mPageRow;
String mUserName,mMode,mPageStr;
mPage=1;
if(request.getParameter("pPage")!=null)
	mPage=Integer.parseInt(request.getParameter("pPage"));
mAllRows=UserConform.countRow();
mAllPage=(mAllRows+MAX-1)/MAX;//ȡ����ҳ��
mMode=request.getParameter("pMode");
if(mMode == null)
	mMode="0";
mUserName=request.getParameter("pUserName");
if(mUserName == null)
	mUserName="";
if(mMode.equals("0"))
{
	resultRow=UserConform.queryUser(mUserName);
}
if(mMode.equals("1"))
{
	resultRow=UserConform.upQuery(mUserName);
//	if(mUserName.equals(""))
//		mPage=mAllPage-1;
}
if(resultRow>MAX)
	mPageRow=MAX;
else
	mPageRow=resultRow;
if(resultRow<0)
{
%>
ϵͳ����
<%
}
else
{
%>
<br>
<br><div align="center">
<table width="90%"  border="0" cellpadding="3" cellspacing="1" bgcolor="#999999" style="BORDER-COLLAPSE: collapse">
  <tr align="left">
    <td height="25" colspan="5" class="topback">
      <div class="fontw"><strong><font color="#FFFFFF"><strong><img src="/stPortal/images/folder_inbox.gif" width="16" height="16" hspace="5" align="absmiddle"></strong>�û����</font></strong></div>
      <div align="center" class="fontw"></div>
      <div align="center" class="fontw"></div>
      <div align="center" class="fontw"></div>
      <div align="center" class="fontw"></div></td>
  </tr>
  <tr>
    <td height="23" align="center" bgcolor="#F6f6f3"><strong><font color="#666666">�û��ʺ�</font></strong></td>
    <td width='14%' height="23" align="center" bgcolor="f6f6f3"><font color="#666666"><strong>�û���</strong></font></td>
    <td width='8%' height="23" align="center" bgcolor="f6f6f3"><font color="#666666"><strong>�Ƿ���׼</strong></font></td>
    <td width='8%' height="23" align="center" bgcolor="f6f6f3"><font color="#666666"><strong>�鿴</strong></font></td>
    <td width='8%' height="23" align="center" bgcolor="f6f6f3"><font color="#666666"><strong>ɾ��</strong></font></td>
  </tr>
  <%      int i;
        for(i=0;i<mPageRow;i++)
		{
			String user_code = UserConform.getUSER_CODE(i);
			String user_name = UserConform.getFULL_NAME(i);
			String user_pwd = UserConform.getUSER_PWD(i);
%>
  <tr>
    <td width='8%' height="23" align='center' bgcolor="#FFFFFF" class="Tabcell1"><a href="javascript:void(0)" onclick="javascript:ShowUserInfo('<%=user_code%>')"><%=user_code%></a></td>
    <td width='14%' height="23" align='center' bgcolor="#FFFFFF" class="Tabcell1"><%=user_name%></td>
    <td width='8%' height="23" align='center' bgcolor="#FFFFFF" class="Tabcell1"><a href="addUser.jsp?pUserName=<%=user_code%>&pPWD=<%=user_pwd%>">��׼ע��</a></td>
    <td width='8%' height="23" align='center' bgcolor="#FFFFFF" class="Tabcell1"><a href="javascript:void(0)" onclick="javascript:ShowUserInfo('<%=user_code%>')">�鿴</a></td>
    <td width='8%' height="23" align='center' bgcolor="#FFFFFF" class="Tabcell1"><a href="javascript:void(0)" onclick="javascript:DeleteUser('<%=user_code%>')"  >ɾ��</a></td>
  </tr>
  <%
		}
%>
  <%
}
%>
  <tr>
    <td height="23" colspan="5" align="left" bgcolor="#FFFFFF" class="Tabcell1" style="padding-right:15px;">
      <div align="left" valign="bottom">��<%=mAllRows%> ����¼</div>
      <div align="right">
        <%	if(mPage != 1)
        {
%>
        <a href="userConform.jsp">��ҳ</a>
        <%
	}
	if(mPage>1)
	{
%>
        <a href="userConform.jsp?pPage=<%=(mPage-1)%>&pMode=1&pUserName=<%=UserConform.getUSER_CODE(0)%>">��һҳ</a>
        <%
	}
	if(mPage < mAllPage)
	{
%>
        <a href="userConform.jsp?pPage=<%=(mPage+1)%>&pMode=0&pUserName=<%=UserConform.getUSER_CODE(9)%>">��һҳ</a>
        <%
	}
	if(mPage < mAllPage)
	{
%>
        <a href="userConform.jsp?pMode=1&pPage=<%=(mAllPage)%>">βҳ</a>
        <%
	}
%>
        ��<%=mPage%>ҳ ��<%=mAllPage%>ҳ </div></td>
  </tr>
</table>
<script language="javascript">
//-----------------------------------------------------------
//���ܣ��쿴�û���Ϣ
//-----------------------------------------------------------
function ShowUserInfo(usercode)
{
  var sFeatures;
  sFeatures = "dialogHeight:650px;dialogWidth:820px;";
  sFeatures = sFeatures + "center:yes;edge:raised;scroll:no;status:no;unadorned:yes;"
  var URL="show_user.jsp?pUserName=" + usercode;
  var sReturn = window.showModalDialog(URL,"",sFeatures);
  if (sReturn != "" && sReturn != undefined)
  {
    oFrm = parent.document.frames("LeftFrm");
    if (oFrm.ModifyNode != null)
      oFrm.ModifyNode("220_222_225",sReturn);
  }
}

//-----------------------------------------------------------
//���ܣ�ɾ���û���Ϣ
//-----------------------------------------------------------
function DeleteUser(usercode)
{
		if(window.confirm("�Ƿ�ɾ���û�"))
		{
				var sFeatures;
				var returnValue;
			  sFeatures = "dialogHeight:650px;dialogWidth:820px;";
			  sFeatures = sFeatures + "center:yes;edge:raised;scroll:no;status:no;unadorned:yes;"
			  
			  var URL="delUser.jsp?pUserName="+usercode;
			  returnValue = window.showModalDialog(URL,"",sFeatures);
			  if(returnValue=="ok" ){
			  	refurbish();
			  	}
		}
			
}
function refurbish(){
	
		window.location.reload();
	
	}
</script>
</body>
</html>