<%@ page contentType="text/html; charset=gb2312" errorPage="../../include/error.jsp"%>
<%@ page language="java" import="java.util.*,java.sql.*,jbportal.PortalUtil,com.minstone.util.database.RecordSetObject" %>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
  String m_ModuID = "";
  String m_usercode = "";

  String m_Title = "";
  String m_para_id = "";
  String m_Description	= "";
  String m_DashBoardOrder = "";
  String m_DashBoardImageLarge = "";
  String m_DashBoardImageSmall = "";

  m_ModuID = request.getParameter("m_ModuID");
  if (m_ModuID == null) m_ModuID = "";

  String m_Operation = request.getParameter("m_Operation");
  if (m_Operation == null) m_Operation = "";

  m_usercode=(String)request.getRemoteUser();
  String m_username =oManager.getCurrentUserName();
  if (m_Operation.equals("0")){
    RecordSetObject m_Rstemp=null;
    m_Rstemp = oManager.rsGetPersonModu(m_usercode,m_ModuID);
    if (m_Rstemp.getRowCount()>0){
      m_Title			= PortalUtil.getValue(m_Rstemp.getString("title",0));
      m_para_id			= PortalUtil.getValue(m_Rstemp.getString("para_id",0));
      m_Description		= PortalUtil.getValue(m_Rstemp.getString("Description",0));
      m_DashBoardOrder		= PortalUtil.getValue(m_Rstemp.getString("DashBoardOrder",0));
      m_DashBoardImageLarge	= PortalUtil.getValue(m_Rstemp.getString("DashBoardImageLarge",0));
      m_DashBoardImageSmall	= PortalUtil.getValue(m_Rstemp.getString("DashBoardImageSmall",0));
    }
    else{
      m_ModuID="";
    }
  }
%>
<html>
<link rel="STYLESHEET" type="text/css" href="../../include/Public.css">

<script type="text/javascript" src="../../include/i_CheckInput.js"></script>
<script type="text/javascript" src="../../include/i_ExpandJScript.js"></script>
<script type="text/javascript" src="../../include/i_LockControls.js"></script>

<script type="text/javascript">
<!--
function Save(){
	//����ǰҪ��֤�����Ƿ���ȷ,������鲻�����򷵻�
	if (ValidateInput()==false)
		return;
	ModuleDetails.action = "_ModuleDetailsOperator.jsp";
	ModuleDetails.submit();
}

function GetHelp(){
	alert("��Ǹ����ȱ!");
}

//���������Ƿ�Ϸ�
function ValidateInput()
{
	var l_strErrDesc;
	l_strErrDesc = Validate_Input();
	if ( l_strErrDesc == ""){
		return true;
	}
	alert(l_strErrDesc);
	return false;
}

//����loadʱ���¼�
function window_onload()
{
	var sArray,sModuID;

	sModuID='<%=m_ModuID%>';

	if (parent!=null && sModuID!="")
		{
		  sArray = new Array();
		  sArray["cate_desc"]= '<%=m_Title%>';
		  sArray['cate_value']= sModuID
		  sArray['cate_para']= '<%=m_para_id%>';
		  parent.document.all.item(sModuID + "_Value").value ='<%=m_Title%>';

		  parent.oTree.UpdateEx(sModuID,'<%=m_para_id%>',sArray);
		}
	if (sModuID=="")
		{
			LockControls();
		}
}

window.attachEvent("onload",window_onload);
//-->
</script>

<body leftmargin="0" topmargin="0" rightmargin="0">
	<form ACTION="ModuleDetails.jsp" METHOD="post" id="ModuleDetails" name="ModuleDetails">
		<table width="100%" cellspacing="0" cellpadding="0">
			<tr>
				<td class="TdHeader"><%=m_Title%></td>
			</tr>
		</table>
		<table height=100% valign="middle" align="center">
		<TR><TD>
			<table width="450" Class="Table_Normal" align="center" cellspacing="0" cellpadding="0">
			  <tr class="TrHeader">
			    <td colspan="3">����ģ�����</td>
			    <td align="right">
					<table width="30" cellpadding="0" cellspacing="0" border="0">
						<tr><td align="right">
								<img src="../../images/help.gif" align="center" style="cursor=hand;" onclick="javascript:GetHelp();" alt="����" WIDTH="16" HEIGHT="14">
							</td>
							<td align="right">
								<img src="../../images/close_no.gif" align="center" alt="�˳�" WIDTH="16" HEIGHT="14">
							</td>
						</tr>
					</table>
			    </td>
			  </tr>
			  <tr>
			    <td colspan="4">&nbsp;</td>
			  </tr>
			  <tr>
			    <td width="17%">&nbsp;ģ�����ƣ�</td>
			    <td width="33%">
					<input name="title" class="input_Normal" value="<%=m_Title%>" maxlen="30" autocheck="1" propname="ģ������" cannull="0">
				</td>
			    <td width="17%">&nbsp;��ʾ˳��</td>
			    <td width="33%"><input name="DashBoardOrder" class="input_ReadOnly" Readonly value="<%=m_DashBoardOrder%>" autocheck="1" propname="��ʾ˳�������" datatype="1"></td>
			  </tr>
			  <tr>

			    <td width="16%">&nbsp;ģ��������</td>
			    <td colspan="3"><input name="Description" class="input_Normal" value="<%=m_Description%>" style="width:356;"></td>
			  </tr>
			  <tr>
			    <td width="17%">&nbsp;�� ͼ �꣺</td>
			    <td width="33%"><input name="DashBoardImageLarge" class="Input_Normal" value="<%=m_DashBoardImageLarge%>"></td>
			    <td width="16%">&nbsp;С ͼ �꣺</td>
			    <td width="34%"><input name="DashBoardImageSmall" class="Input_Normal" value="<%=m_DashBoardImageSmall%>"></td>
			  </tr>
			  <tr><td colspan="4">&nbsp;</td></tr>
			  <tr>
					<td colspan="4" align="right">
						<input type="button" id="ok" name="ok" value="ȷ    ��" class="Input_Button" onclick="javascript:Save();">&nbsp;
					</td>
			  </tr>
			  <tr><td colspan="4">&nbsp;</td></tr>
			</table>
		</TR></TD>
	</table>

		<input type="hidden" name="modu_id" value="<%=m_ModuID%>">
		<input type="hidden" name="para_id" value="<%=m_para_id%>">
	</form>
</body>
</html>
