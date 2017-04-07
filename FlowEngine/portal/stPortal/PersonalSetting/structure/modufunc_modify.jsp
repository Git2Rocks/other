<%@ page contentType="text/html; charset=gb2312" errorPage="../../include/error.jsp"%>
<%@ page language="java" import="java.util.*,java.sql.*,com.minstone.util.database.RecordSetObject" %>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
    String m_Title = "";
    String m_href = "";
    String m_Description = "";
    String m_href_desc = "";
    String m_AllowMinimize = "";
    String m_Width = "";
    String m_Zone = "";
    String m_HeightUnitType = "";
    String m_HeightEnabled = "";
    String m_IsVisible = "";
    String m_AllowRemove = "";
    String m_IsIncluded = "";
    String m_WidthEnabled = "";
    String m_WidthUnitType = "";
    String m_Height = "";
    String m_HasFrame = "";
    String m_FrameState = "";
    String m_RequiresIsolation = "";
    String m_RefreshInterval="0";

    String sCheckedNo = "";
    String sCheckedYes = "";
    RecordSetObject m_Rstemp = null;
    //��ʾλ�ö���
    String m_aryDis1[] = {"�Ϸ�����", "������"};
    String m_aryDis2[] = {"�м�����","�ҷ�����"};
    String m_aryDis3[] = {"�·�����"};
    String m_aryVal1[] = {"4","1"};
    String m_aryVal2[] = {"3","2"};
    String m_aryVal3[] = {"5"};
    String m_aryImg1[] = {"../../images/topbanner.gif", "../../images/leftcolumn.gif"};
    String m_aryImg2[] = {"../../images/centercolumn.gif", "../../images/rightcolumn.gif"};
    String m_aryImg3[] = {"../../images/bottombanner.gif"};

    //��ʾ״̬����

    String m_aryFrameState1[] = {"չ��״̬","����״̬"};
    String m_aryFrameState2[] = {"0","1"};
    String m_aryFrameState3[] = {"../../images/expanded.gif", "../../images/minimized.gif"};

    //����Select�������

    String m_UnitType[] = {"����","Ӣ��","����","����","��","�ٷֱ�"};
    String m_UnitTypeValue[] = {"cm","in","mm","px","pt","%"};

    String m_usercode=(String)request.getRemoteUser();
    String m_username =oManager.getCurrentUserName();

    String m_ModuTitle =jbportal.PortalUtil.getValue(request.getParameter("title"));
    String m_func_type =jbportal.PortalUtil.getValueN(request.getParameter("func_type"));
    String m_func_id =jbportal.PortalUtil.getValue(request.getParameter("func_id"));
    String m_modu_type =jbportal.PortalUtil.getValueN(request.getParameter("modu_type"));
    String m_modu_id =jbportal.PortalUtil.getValue(request.getParameter("modu_id"));
    //System.err.println("title"+m_ModuTitle);
	//System.err.println("func_type"+m_func_type);
	//System.err.println("func_id"+m_func_id);
	//System.err.println("modu_type"+m_modu_type);
	//System.err.println("modu_id"+m_modu_id);
    //������Դ�����m_Source="stportal"��Ҫ���⴦��
    String m_Source =jbportal.PortalUtil.getValue(request.getParameter("Source"));

    m_Rstemp = oManager.rsGetPersonModuFunction(m_usercode, m_modu_id,m_modu_type,m_func_id,m_func_type,m_Source);

    if (m_Rstemp.getRowCount()>0)
    {
      m_Title			=jbportal.PortalUtil.getValue(m_Rstemp.getString("Title",0));
      m_href			=jbportal.PortalUtil.getValue(m_Rstemp.getString("href",0));
      m_Description		=jbportal.PortalUtil.getValue(m_Rstemp.getString("Description",0));
      m_href_desc		        =jbportal.PortalUtil.getValue(m_Rstemp.getString("href_desc",0));
      m_AllowMinimize		=jbportal.PortalUtil.getValue(m_Rstemp.getString("AllowMinimize",0));
      m_Width			=jbportal.PortalUtil.getValueN(m_Rstemp.getString("Width",0));
      m_Zone			=jbportal.PortalUtil.getValueN(m_Rstemp.getString("Zone",0));
      m_HeightUnitType		=jbportal.PortalUtil.getValue(m_Rstemp.getString("HeightUnitType",0));
      m_HeightEnabled		=jbportal.PortalUtil.getValueN(m_Rstemp.getString("HeightEnabled",0));
      m_IsVisible		        =jbportal.PortalUtil.getValue(m_Rstemp.getString("IsVisible",0));
      m_AllowRemove		=jbportal.PortalUtil.getValue(m_Rstemp.getString("AllowRemove",0));
      m_IsIncluded		=jbportal.PortalUtil.getValue(m_Rstemp.getString("IsIncluded",0));
      m_WidthEnabled		=jbportal.PortalUtil.getValueN(m_Rstemp.getString("WidthEnabled",0));
      m_WidthUnitType		=jbportal.PortalUtil.getValue(m_Rstemp.getString("WidthUnitType",0));
      m_Height			=jbportal.PortalUtil.getValueN(m_Rstemp.getString("Height",0));
      m_HasFrame		        =jbportal.PortalUtil.getValue(m_Rstemp.getString("HasFrame",0));
      m_FrameState		=jbportal.PortalUtil.getValue(m_Rstemp.getString("FrameState",0));
      m_RequiresIsolation		=jbportal.PortalUtil.getValue(m_Rstemp.getString("RequiresIsolation",0));
      m_RefreshInterval=jbportal.PortalUtil.getValueN(m_Rstemp.getString("REFRESHINTERVAL",0));
    }
    else
    {
      m_func_id="";
    }
    //��ʾλ��
    if (m_Zone.equals("")) m_Zone = "3";
    String m_StrZone1 =jbportal.PortalUtil.LArrayRadios("Zone", m_aryDis1, m_aryVal1,m_aryImg1,m_Zone);
    String m_StrZone2 =jbportal.PortalUtil.LArrayRadios("Zone", m_aryDis2, m_aryVal2,m_aryImg2,m_Zone);
    String m_StrZone3 =jbportal.PortalUtil.LArrayRadios("Zone", m_aryDis3, m_aryVal3,m_aryImg3,m_Zone);

    //Ԥ��״̬
    if (m_FrameState.equals("")) m_FrameState="0";
    String m_StrFrameState = jbportal.PortalUtil.LArrayRadios("FrameState", m_aryFrameState1, m_aryFrameState2,m_aryFrameState3,m_FrameState);
    //�̶��߶�
    if (m_HeightEnabled.equals("") || m_HeightEnabled.equals("0")){
      m_HeightEnabled = "0";
      sCheckedNo = "CHECKED=''";
      sCheckedYes = "";
    }
    else{
      sCheckedYes = "CHECKED=''";
      sCheckedNo = "";
    }
    String sOnClick = " onClick='JavaScript:IniHeightEnabled();' ";
    String m_StrHeightEnabled1 = "<INPUT TYPE='RADIO' NAME='HeightEnabled' VALUE='1' " + sCheckedYes + sOnClick + " >Yes&nbsp;</INPUT>";
    String m_StrHeightEnabled2 = "<INPUT TYPE='RADIO' NAME='HeightEnabled' VALUE='0' " + sCheckedNo + sOnClick + " >No&nbsp;</INPUT>";
    //�߶ȵ�λ
    String m_StrHeightUnitType = jbportal.PortalUtil.ArrayOptions(m_UnitTypeValue,m_UnitType,m_HeightUnitType);
    //�̶����
    if (m_WidthEnabled.equals("") || m_WidthEnabled.equals("0")){
      m_WidthEnabled = "0";
      sCheckedNo = "CHECKED=''";
      sCheckedYes = "";
    }
    else{
      sCheckedYes = "CHECKED=''";
      sCheckedNo = "";
    }
    sOnClick = " onClick='JavaScript:IniWidthEnabled();' ";
    String m_StrWidthEnabled1 = "<INPUT TYPE='RADIO' NAME='WidthEnabled' VALUE='1' " + sCheckedYes + sOnClick + " >Yes&nbsp;</INPUT>";
    String m_StrWidthEnabled2 = "<INPUT TYPE='RADIO' NAME='WidthEnabled' VALUE='0' " + sCheckedNo + sOnClick + " >No&nbsp;</INPUT>";
    //��ȵ�λ
    String m_StrWidthUnitType = jbportal.PortalUtil.ArrayOptions(m_UnitTypeValue,m_UnitType,m_WidthUnitType);
    //����ҳ��ķ�������
    String ms_ThisURL = "modufunc_modify.jsp?func_id=" + m_func_id +
                             "&func_type=" + m_func_type +
                             "&modu_id=" + m_modu_id +
                             "&modu_type=" + m_modu_type;

    String ms_BackURL = "funcList.jsp?modu_id=" + m_modu_id +"&modu_type=" + m_modu_type;
%>
<html>
<link rel="STYLESHEET" type="text/css" href="../../include/Public.css">

<script type="text/javascript" src="../../include/i_CheckInput.js"></script>
<script type="text/javascript" src="../../include/i_ExpandJScript.js"></script>
<script type="text/javascript" src="../../include/i_LockControls.js"></script>

<script type="text/javascript">
<!--
function Save(){
	var Page_Source;

	//����ǰҪ��֤�����Ƿ���ȷ,������鲻�����򷵻�
	if (ValidateInput()==false)
		return;

	Page_Source = '<%=m_Source%>';
	//alert(Page_Source);
	if (Page_Source=="stportal")
	{
		window.close();
		return;
	}
	else
	{
		modufunc_modify.action = "_ModuFunctionOperator.jsp";
		modufunc_modify.submit();
	}
}

function GetHelp(){
	alert("��Ǹ��������ȱ!");
}

function Exit()
{
	if ('<%=m_Source%>'=="stportal")
		{
			window.close() ;
		}
	else
	{
		window.location = '<%=ms_BackURL%>';
	}
}
//���������Ƿ�Ϸ�
function ValidateInput()
{
	var l_strErrDesc;
	l_strErrDesc = Validate_Input();
	if ( l_strErrDesc == ""){
		return true;
	}
	//alert(l_strErrDesc);
	return false;
}

//����loadʱ���¼�
function window_onload()
{
	var sArray,sFuncID;
	var sZone;

	sFuncID='<%=m_func_id%>';

	IniHeightEnabled();
	IniWidthEnabled();
	IniCheckded();
	if (sFuncID=="")
		{
			if ('<%=m_Source%>'=="stportal")
			{
			alert("��¼������");
			window.close();

			return;}
			else
			{LockControls();}
		}


}

function IniHeightEnabled()
{
	//1���ж��Ƿ�����߶��Լ���λ
	var bEnabled;
	bEnabled = document.all.item("HeightEnabled")[1].checked;  //yes
	//��Disabled����
	document.all.item("Height").disabled=bEnabled;
	document.all.item("HeightUnitType").disabled=bEnabled;
	//��bgcolor����
	if (bEnabled==true){
		document.all.item("Height").style.backgroundColor="#c0c0c0";
		document.all.item("HeightUnitType").style.backgroundColor="#c0c0c0";
	}
	else
	{
		document.all.item("Height").style.backgroundColor=document.all.item("Height").currentStyle.getAttribute("backgroundColor",2);
		document.all.item("HeightUnitType").style.backgroundColor=document.all.item("HeightUnitType").currentStyle.getAttribute("backgroundColor",2);
	}
}

function IniWidthEnabled()
{
	//1���ж��Ƿ�����߶��Լ���λ
	var bEnabled;
	bEnabled = document.all.item("WidthEnabled")[1].checked;  //yes
	//��Disabled����
	document.all.item("Width").disabled=bEnabled;
	document.all.item("WidthUnitType").disabled=bEnabled;
	//��bgcolor����
	if (bEnabled==true){
		document.all.item("Width").style.backgroundColor="#c0c0c0";
		document.all.item("WidthUnitType").style.backgroundColor="#c0c0c0";
	}
	else
	{
		document.all.item("Width").style.backgroundColor=document.all.item("Width").currentStyle.getAttribute("backgroundColor",2);
		document.all.item("WidthUnitType").style.backgroundColor=document.all.item("WidthUnitType").currentStyle.getAttribute("backgroundColor",2);
	}
}

//��ʼ��CheckBox
function IniCheckded()
{
	if ('<%=m_IsVisible%>'=='0')
		{document.all.item("IsVisible").checked=false;}
	else
		{document.all.item("IsVisible").checked=true;}

	if ('<%=m_AllowRemove%>'=='0')
		{document.all.item("AllowRemove").checked=false;}
	else
		{document.all.item("AllowRemove").checked=true;}

	if ('<%=m_IsIncluded%>'=='0')
		{document.all.item("IsIncluded").checked=false;}
	else
		{document.all.item("IsIncluded").checked=true;}

	if ('<%=m_HasFrame%>'=='0')
		{document.all.item("HasFrame").checked=false;}
	else
		{document.all.item("HasFrame").checked=true;}

	if ('<%=m_AllowMinimize%>'=='0')
		{document.all.item("AllowMinimize").checked=false;}
	else
		{document.all.item("AllowMinimize").checked=true;}

	if ('<%=m_RequiresIsolation%>'=='0')
		{document.all.item("RequiresIsolation").checked=false;}
	else
		{document.all.item("RequiresIsolation").checked=true;}
}
window.attachEvent("onload",window_onload);

//-->
</script>

<body leftmargin="0" topmargin="0" rightmargin="0">
<form ACTION="modufunc_modify.jsp" METHOD="post" id="modufunc_modify" name="modufunc_modify">
	<table width=100% height=100% align="center" valign="middle" cellpadding="0" cellspacing="0">
	<TR><TD>
	<table width="100%" cellspacing="0" cellpadding="0">
			<tr>
				<td class="TdHeader"><%=m_Title%></td>

			</tr>
	</table>
	<div>
	<table width="100%" height="95%" align="center" valign="middle">
	<tr><td valign="middle" align="center">
	<table width="80%" cellpadding="0" cellspacing="0" class="Table_Normal" align="center" valign="middle">
	<tr class="TrHeader">
		    <td ><%=m_Title%>�趨</td>
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
	<td colspan="2" WIDTH="100%">
	<table width="100%" cellpadding="0" cellspacing="0" class="InnerTable" align="center">
		<tr>
			<td>&nbsp;</td>
			<td>
			<table WIDTH="100%" CELLPADDING="0" CELLSPACING="0" border="0" Class="InnerTable">
				<tr>
					<td CLASS="CustSectionRight" width="100%" colspan="3">
					<fieldset style="padding:6px;width:100%">
						<legend>
							<span id="usersetting">���趨</span>
						</legend>
						<table WIDTH="100%" class="InnerTable">
							<tr>
								<td CLASS="CustSectionRight"><input type="label" style="width:30" class="Input_Label" Value="����:" id="label2" name="label2"></td>
								<td CLASS="CustSectionRight">
									<input type="text" maxlength="100" name="Title" style="width:180; overflow:hidden" class="input_ReadOnly" readonly value="<%=m_Title%>">
								</td>
								<td CLASS="CustSectionRight"><input type="label" style="width:30" class="Input_Label" Value="����:" id="label1" name="label1"></td>
								<td CLASS="CustSectionRight">
									<textarea NAME="Description" ROWS="1" STYLE="width:180" class="input_ReadOnly" readonly><%=m_Description%></textarea>
								</td>
							</tr>
							<tr>
								<td CLASS="CustCheckboxText">����:</td>
								<td CLASS="CustCheckboxText" colspan="3">
									<input TYPE="text" NAME="href" STYLE="width:420;overflow:hidden" class="input_ReadOnly" readonly value="<%=m_href%>">
								</td>
							</tr>
							<tr>
								<td CLASS="CustCheckboxText">����˵��:</td>
								<td CLASS="CustCheckboxText" Colspan="3">
									<input TYPE="TEXT" NAME="href_desc" STYLE="width:420;overflow:hidden" class="input_ReadOnly" readonly value="<%=m_href_desc%>">
								</td>
							</tr>
						</table>
					</fieldset>
					</td>
				</tr>
				<tr>
					<td CLASS="CustSectionRight" width="50%" valign="TOP">
					<fieldset style="padding:4px;width:100%;height:220px">
						<legend>
							<span id="usersetting">λ���趨</span>
						</legend>
						<table WIDTH="100%" class="InnerTable">
							<tr>
								<td class="CustCheckbox">
									<input TYPE="CHECKBOX" NAME="IsIncluded" VALUE="1">����
								</td>
								<td class="CustCheckbox">
									<input TYPE="CHECKBOX" NAME="IsVisible" VALUE="1">��ʾ����
								</td>
								<td class="CustCheckbox">
									<input TYPE="CHECKBOX" NAME="HasFrame" VALUE="1">��ʾ������
								</td>
							</tr>
							<tr>
								<td CLASS="CustCheckbox">
									<input TYPE="CHECKBOX" NAME="AllowRemove" VALUE="1">�ɹر�
								</td>
								<td class="CustCheckbox">
									<input TYPE="CHECKBOX" NAME="AllowMinimize" VALUE="1">����С��
								</td>
								<td class="CustCheckbox">
								</td>
							</tr>
						</table>
						��ʾλ��:
						<table class="InnerTable">
						<%=m_StrZone1%>
						<%=m_StrZone2%>
						<%=m_StrZone3%>
						</table>
                        <TABLE class="InnerTable">
							<TR>
								<TD>ˢ��Ƶ��</TD>
								<TD CLASS="CustCheckboxText">
									<INPUT Type="text"  STYLE="WIDTH:80;OVERFLOW:HIDDEN" NAME="RefreshInterval" class="input_Number"  autocheck="1" datatype="1" propname="ˢ��Ƶ��" VALUE=<%=m_RefreshInterval%> >
								</TD>
								<TD>��</TD>
							</TR>
						</TABLE>
					</fieldset>
				</td>
				<td CLASS="CustSectionRight" width="50%" valign="TOP">
					<fieldset style="padding:4px;width:100%;height:220px">
						<legend>
							<span id="usersetting">�����趨</span>
						</legend>
						Ԥ��״̬
						<table class="InnerTable">
							<%=m_StrFrameState%>
						</table>
						�̶��߶�:
						<br />
						<table class="InnerTable">
							<tr>
								<td>
									<%=m_StrHeightEnabled1%>
								</td>
								<td>
									<%=m_StrHeightEnabled2%>
								</td>
								<td>
									<input TYPE="text" NAME="Height" STYLE="WIDTH:.5IN;OVERFLOW:HIDDEN" class="input_Normal" autocheck="1" datatype="1" propname="�߶�" value="<%=m_Height%>">
								</td>
								<td>
									<select NAME="HeightUnitType" SIZE="1" SYTLE="WIDTH:.5IN" class="DrawSelect">
										<%=m_StrHeightUnitType%>
									</select>
								</td>
							<tr>
						</table>
						�̶����:
						<br />
						<table CLASS="InnerTable">
							<tr>
								<td>
									<%=m_StrWidthEnabled1%>
								</td>
								<td>
									<%=m_StrWidthEnabled2%>
								</td>
								<td>
									<input TYPE="text" NAME="Width" STYLE="WIDTH:.5IN;OVERFLOW:HIDDEN" class="input_Normal" autocheck="1" datatype="1" propname="���" value="<%=m_Width%>">
								</td>
								<td>
									<select NAME="WidthUnitType" SIZE="1" SYTLE="WIDTH:.5IN" class="DrawSelect">
										<%=m_StrWidthUnitType%>
									</select>
								</td>
							</tr>
						<table>
							<tr>
								<td CLASS="CustCheckbox">
									<input TYPE="CHECKBOX" NAME="RequiresIsolation" VALUE="1">
								</td>
								<td CLASS="CustCheckboxText">
								�Զ�����
								</td>
							</tr>
						</table>
					</fieldset>
				</td>
			</tr>
			<tr>
				<td class="CustButtonSectionRight" NOWRAP colspan="4" align="right">
					<input class="Input_Button" TYPE="Button" value="ȷ  ��" id="Button1" name="Button1" onclick="javascript:Save();">
					<input class="Input_Button" TYPE="Button" value="ȡ  ��" id="Button1" name="Button1" onclick="javascript:Exit();">
				</td>
				<td CLASS="CustSpacer">&nbsp;</td>
			</tr>
				<TR>
					<TD>&nbsp;</TD>
					<TD>&nbsp;</TD>
				</TR>
		</table>
		</td>
	</tr>

</table>
</td>
</tr>
</table>
</div>
</TD></TR></TABLE>
<input type="hidden" name="func_id" value="<%=m_func_id%>">
<input type="hidden" name="modu_id" value="<%=m_modu_id%>">
<input type="hidden" name="func_type" value="<%=m_func_type%>">
<input type="hidden" name="modu_type" value="<%=m_modu_type%>">
<input type="hidden" name="BackURL" value="<%=ms_BackURL%>">
</form>
</body>
</html>
