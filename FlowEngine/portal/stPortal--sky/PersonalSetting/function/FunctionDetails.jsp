<%@ page contentType="text/html; charset=gb2312" errorPage="../../include/error.jsp"%>
<%@ page language="java" import="java.util.*,java.sql.*,jbportal.PortalUtil,suntek.portal.publicLib.RecordSetObject" %>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
    String  m_StrWidthUnitType = "";
    String sCheckedNo = "";
    String sOnClick = "";
    String sCheckedYes = "";
    String m_modu_id = "";
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
    String m_moduTitle = "";
    String m_StrFrameState = "";
    String m_StrHeightUnitType = "";
    String m_RefreshInterval="0";
    //��ʾλ�ö���

    String[] m_aryDis1 = {"�Ϸ�����", "������"};
    String[] m_aryDis2 = {"�м�����","�ҷ�����"};
    String[] m_aryDis3 = {"�·�����"};
    String[] m_aryVal1 = {"4","1"};
    String[] m_aryVal2 = {"3","2"};
    String[] m_aryVal3 = {"5"};
    String[] m_aryImg1 = {"../../images/topbanner.gif", "../../images/leftcolumn.gif"};
    String[] m_aryImg2 = {"../../images/centercolumn.gif", "../../images/rightcolumn.gif"};
    String[] m_aryImg3 = {"../../images/bottombanner.gif"};

	 //��ʾ״̬����

	String[] m_aryFrameState1 = {"չ��״̬","����״̬"};
	String[] m_aryFrameState2 = {"0","1"};
	String[] m_aryFrameState3 = {"../../images/expanded.gif", "../../images/minimized.gif"};

	String[] m_UnitType = {"����","Ӣ��","����","����","��","�ٷֱ�"};
	String[] m_UnitTypeValue = {"cm","in","mm","px","pt","%"};
    String m_func_id = request.getParameter("m_NodeValue");
    String m_Status = request.getParameter("m_Status");

    String m_usercode=(String)request.getRemoteUser();
    String m_username =oManager.getCurrentUserName();
    if (m_func_id==null){
          m_func_id="";
    }
    //out.print(m_func_id);
    if (m_Status==null){
          m_Status="";
    }

    RecordSetObject m_Rstemp=null;
    m_Rstemp = oManager.rsGetPersonFunc(m_usercode,m_func_id);

    if(m_Rstemp.getRowCount()>0)
    {
      m_modu_id        =PortalUtil.getValue(m_Rstemp.getString("modu_id",0));
      m_Title          =PortalUtil.getValue(m_Rstemp.getString("Title",0));
      m_href           =PortalUtil.getValue(m_Rstemp.getString("href",0));
      m_Description    =PortalUtil.getValue(m_Rstemp.getString("Description",0));
      m_href_desc      =PortalUtil.getValue(m_Rstemp.getString("href_desc",0));
      m_AllowMinimize  =PortalUtil.getValue(m_Rstemp.getString("AllowMinimize",0));
      m_Width          =PortalUtil.getValueN(m_Rstemp.getString("Width",0));
      m_Zone           =PortalUtil.getValueN(m_Rstemp.getString("Zone",0));
      m_HeightUnitType =PortalUtil.getValue(m_Rstemp.getString("HeightUnitType",0));
      m_HeightEnabled  =PortalUtil.getValueN(m_Rstemp.getString("HeightEnabled",0));
      m_IsVisible      =PortalUtil.getValue(m_Rstemp.getString("IsVisible",0));
      m_AllowRemove    =PortalUtil.getValue(m_Rstemp.getString("AllowRemove",0));
      m_IsIncluded     =PortalUtil.getValue(m_Rstemp.getString("IsIncluded",0));
      m_WidthEnabled   =PortalUtil.getValueN(m_Rstemp.getString("WidthEnabled",0));
      m_WidthUnitType  =PortalUtil.getValue(m_Rstemp.getString("WidthUnitType",0));
      m_Height         =PortalUtil.getValueN(m_Rstemp.getString("Height",0));
      m_HasFrame       =PortalUtil.getValue(m_Rstemp.getString("HasFrame",0));
      m_FrameState     =PortalUtil.getValue(m_Rstemp.getString("FrameState",0));
      m_RequiresIsolation	=PortalUtil.getValue(m_Rstemp.getString("RequiresIsolation",0));
      m_moduTitle      =PortalUtil.getValue(m_Rstemp.getString("moduTitle",0));
      m_RefreshInterval =PortalUtil.getValue(m_Rstemp.getString("RefreshInterval",0));
    }
    else{
      m_func_id = "";
    }

	//��ʾλ��
	if(m_Zone.equals(""))
    {
      m_Zone = "3";
    }

	String m_StrZone1 = PortalUtil.LArrayRadios("Zone", m_aryDis1, m_aryVal1,m_aryImg1,m_Zone);
	String m_StrZone2 = PortalUtil.LArrayRadios("Zone", m_aryDis2, m_aryVal2,m_aryImg2,m_Zone);
	String m_StrZone3 = PortalUtil.LArrayRadios("Zone", m_aryDis3, m_aryVal3,m_aryImg3,m_Zone);

	//Ԥ��״̬
	if (m_FrameState.equals(""))
                m_FrameState="0";

	m_StrFrameState = PortalUtil.LArrayRadios("FrameState", m_aryFrameState1, m_aryFrameState2,m_aryFrameState3,m_FrameState);

	//�̶��߶�

	if (m_HeightEnabled.equals("") || m_HeightEnabled.equals("0")){
		m_HeightEnabled = "0";
		sCheckedNo = "CHECKED='/'/";
		sCheckedYes = "";
    }
	else{
		sCheckedYes = "CHECKED='/'/";
		sCheckedNo = "";
    }
	sOnClick = " onClick='JavaScript:IniHeightEnabled();' ";

	String m_StrHeightEnabled1 = "<INPUT TYPE=RADIO NAME=HeightEnabled VALUE=1 " + sCheckedYes + sOnClick + " >Yes&nbsp;</INPUT>";
	String m_StrHeightEnabled2 = "<INPUT TYPE=RADIO NAME=HeightEnabled VALUE=0 " + sCheckedNo + sOnClick + " >No&nbsp;</INPUT>";

	//�߶ȵ�λ
	m_StrHeightUnitType = PortalUtil.ArrayOptions(m_UnitTypeValue,m_UnitType,m_HeightUnitType);

	//�̶����

	if (m_WidthEnabled.equals("") || m_WidthEnabled.equals("0"))
          {
		m_WidthEnabled = "0";
		sCheckedNo = "CHECKED='/'/";
		sCheckedYes = "";
          }
	else
          {
		sCheckedYes = "CHECKED='/'/";
		sCheckedNo = "";
	}

	sOnClick = " onClick=JavaScript:IniWidthEnabled(); ";

	String m_StrWidthEnabled1 = "<INPUT TYPE=RADIO NAME=WidthEnabled VALUE=1 " + sCheckedYes + sOnClick + " >Yes&nbsp;</INPUT>";
	String m_StrWidthEnabled2 = "<INPUT TYPE=RADIO NAME=WidthEnabled VALUE=0 " + sCheckedNo + sOnClick + " >No&nbsp;</INPUT>";

	//��ȵ�λ
	m_StrWidthUnitType = PortalUtil.ArrayOptions(m_UnitTypeValue,m_UnitType,m_WidthUnitType);

%>
<html>
<link rel="STYLESHEET" type="text/css" href="../../include/Public.css">

<script language="javascript" src="../../include/i_CheckInput.js"></script>
<script language="javascript" src="../../include/i_ExpandJScript.js"></script>
<script language="javascript" src="../../include/i_LockControls.js"></script>

<script LANGUAGE="javascript">
<!--
function Save(){
	//����ǰҪ��֤�����Ƿ���ȷ,������鲻�����򷵻�
	if (ValidateInput()==false)
		return;
	FunctionDetails.action = "_FunctionDetailsOperator.jsp";
	FunctionDetails.submit();
}

function GetHelp(){
	alert("��Ǹ��������ȱ!");
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
	var sArray,sFuncID;
	var sZone;

	sFuncID='<%=m_func_id%>';
	//if (parent!=null&&parent.menu!=null&&sFuncID!="")---*zxc 6.13*---
	if (parent!=null&&sFuncID!="")
        {
          //alert("m_func_id="+m_func_id);
		  sArray = new Array();
		  sArray["cate_desc"]= '<%=m_Title%>';
		  sArray['cate_value']= sFuncID
		  sArray['cate_para']= '<%=m_modu_id%>';
		  sArray['cate_type']='1';
		  /*parent.menu.document.all.item(sFuncID + "_Value").value ='<%=m_Title%>';
		  parent.menu.oTree.UpdateEx(sFuncID,'<%=m_modu_id%>',sArray);---*zxc 6.13*---*/
		  parent.document.all.item(sFuncID + "_Value").value ='<%=m_Title%>';
		  parent.oTree.UpdateEx(sFuncID,'<%=m_modu_id%>',sArray);
    }
	IniHeightEnabled();
	IniWidthEnabled();
	IniCheckded();
	if (sFuncID=="")
		{
			LockControls();
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
	if ('<%=m_IsVisible%>'==0)
		{document.all.item("IsVisible").checked=false;}
	else
		{document.all.item("IsVisible").checked=true;}

	if ('<%=m_AllowRemove%>'==0)
		{document.all.item("AllowRemove").checked=false;}
	else
		{document.all.item("AllowRemove").checked=true;}

	if ('<%=m_IsIncluded%>'==0)
		{document.all.item("IsIncluded").checked=false;}
	else
		{document.all.item("IsIncluded").checked=true;}

	if ('<%=m_HasFrame%>'==0)
		{document.all.item("HasFrame").checked=false;}
	else
		{document.all.item("HasFrame").checked=true;}

	if ('<%=m_AllowMinimize%>'==0)
		{document.all.item("AllowMinimize").checked=false;}
	else
		{document.all.item("AllowMinimize").checked=true;}

	if ('<%=m_RequiresIsolation%>'==0)
		{document.all.item("RequiresIsolation").checked=false;}
	else
		{document.all.item("RequiresIsolation").checked=true;}
}
window.attachEvent("onload",window_onload);
//-->
</script>

<body leftmargin="0" topmargin="0" rightmargin="0">
<form ACTION="FunctionDetails.jsp" METHOD="post" id="FunctionDetails" name="FunctionDetails">

	<table width="100%" cellspacing="0" cellpadding="0">
			<tr>
				<td class="TdHeader"><%=m_Title%></td>

			</tr>
			<tr><td>&nbsp;</td></tr>
	</table>
	<div>
	<TABLE width="80%" cellpadding="0" cellspacing="0" class="Table_Normal" align=center>
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
	<TR>
	<TD colspan="2" WIDTH=100%>
	<TABLE width="100%" cellpadding="0" cellspacing="0" class="InnerTable" align=center>
		<tr>
			<TD>&nbsp;</TD>
			<TD>
			<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" border="0" Class="InnerTable">
				<TR>
					<TD CLASS="CustSectionRight" width="100%" colspan="3">
					<fieldset style="padding:6px;width:100%">
						<legend>
							<span id="usersetting">���趨</span>
						</legend>
						<TABLE WIDTH="100%" class="InnerTable">
							<TR>
								<TD CLASS="CustSectionRight"><input type="label" style="width:30" class="Input_Label" Value="����:"></TD>
								<TD CLASS="CustSectionRight" >
									<input type="text" maxlength="100" name="Title" style="width:180; overflow:hidden" class="input_Normal" autocheck="1" propname="����" cannull="0"  value="<%=m_Title%>" >
								</TD>
								<TD CLASS="CustSectionRight"><input type="label" style="width:30" class="Input_Label" Value="����:" id=label1 name=label1></TD>
								<TD CLASS="CustSectionRight" >
									<TEXTAREA NAME="Description" ROWS="1" STYLE="width:180" class="input_Normal" ><%=m_Description%></TEXTAREA>
								</TD>
							</TR>
							<TR>
								<TD CLASS="CustCheckboxText" >����:</TD>
								<TD CLASS="CustCheckboxText" colspan="3" >
									<INPUT TYPE="text" NAME="href" STYLE="width:420;overflow:hidden" class="input_Normal" value="<%=m_href%>">
								</TD>
							</TR>
							<TR>
								<TD CLASS="CustCheckboxText" >����˵��:</TD>
								<TD CLASS="CustCheckboxText" Colspan="3" >
									<INPUT TYPE="TEXT" NAME="href_desc" STYLE="width:420;overflow:hidden" class="input_Normal" value="<%=m_href_desc%>">
								</TD>
							</TR>
						</TABLE>
					</fieldset>
					</TD>
				</TR>
				<TR>
					<TD CLASS="CustSectionRight" width="50%" valign="TOP">
					<fieldset style="padding:4px;width:100%;height=220px">
						<legend>
							<span id="usersetting" >λ���趨</span>
						</legend>
						<TABLE WIDTH="100%" class="InnerTable">
							<TR>
								<TD class="CustCheckbox">
									<INPUT TYPE="CHECKBOX" NAME="IsIncluded" VALUE=1 >����
								</TD>
								<TD class="CustCheckbox">
									<INPUT TYPE="CHECKBOX" NAME="IsVisible" VALUE=1 >��ʾ����
								</TD>
								<TD class="CustCheckbox">
									<INPUT TYPE="CHECKBOX" NAME="HasFrame" VALUE=1 >��ʾ������
								</TD>
							</TR>
							<TR>
								<TD CLASS="CustCheckbox">
									<INPUT TYPE="CHECKBOX" NAME="AllowRemove" VALUE=1>�ɹر�
								</TD>
								<TD class="CustCheckbox">
									<INPUT TYPE="CHECKBOX" NAME="AllowMinimize" VALUE=1>����С��
								</TD>
								<TD class="CustCheckbox">
								</TD>
							</TR>
						</TABLE>
						��ʾλ��:
						<TABLE class="InnerTable">
						<%=m_StrZone1%>
						<%=m_StrZone2%>
						<%=m_StrZone3%>
						</TABLE>
                        			<TABLE class="InnerTable">
							<TR>
								<TD>ˢ��Ƶ��</TD>
								<TD CLASS="CustCheckboxText">
									<INPUT Type="text"  STYLE="WIDTH:80;OVERFLOW:HIDDEN" NAME="RefreshInterval" class="input_Number"  autocheck="1" datatype="1" propname="ˢ��Ƶ��" VALUE="<%=m_RefreshInterval%>">
								</TD>
								<TD>��</TD>
							</TR>
						</TABLE>
					</fieldset>
				</TD>
				<TD CLASS="CustSectionRight" width="50%" valign="TOP">
					<fieldset style="padding:4px;width:100%;height=220px">
						<legend>
							<span id="usersetting" >�����趨</span>
						</legend>
						Ԥ��״̬
						<TABLE class="InnerTable">
							<%=m_StrFrameState%>
						</TABLE>
						�̶��߶�:
						<BR />
						<TABLE class="InnerTable">
							<TR>
								<TD>
									<%=m_StrHeightEnabled1%>
								</TD>
								<TD>
									<%=m_StrHeightEnabled2%>
								</TD>
								<TD>
									<INPUT TYPE="text" NAME="Height" STYLE="WIDTH:.5IN;OVERFLOW:HIDDEN" class="input_Normal"  autocheck="1" datatype="1" propname="�߶�" value="<%=m_Height%>">
								</TD>
								<TD>
									<SELECT NAME="HeightUnitType" SIZE="1" SYTLE="WIDTH:.5IN" class="DrawSelect">
										<%=m_StrHeightUnitType%>
									</SELECT>
								</TD>
							<TR>
						</TABLE>
						�̶����:
						<BR />
						<TABLE CLASS="InnerTable">
							<TR>
								<TD>
									<%=m_StrWidthEnabled1%>
								</TD>
								<TD>
									<%=m_StrWidthEnabled2%>
								</TD>
								<TD>
									<INPUT TYPE="text" NAME="Width" STYLE="WIDTH:.5IN;OVERFLOW:HIDDEN" class="input_Normal"  autocheck="1" datatype="1" propname="���" value="<%=m_Width%>">
								</TD>
								<TD>
									<SELECT NAME="WidthUnitType" SIZE="1" SYTLE="WIDTH:.5IN" class="DrawSelect">
										<%=m_StrWidthUnitType%>
									</SELECT>
								</TD>
							</TR>
						<TABLE>
                                                            <TABLE>
							<TR>
								<TD CLASS="CustCheckbox">
									<INPUT TYPE="CHECKBOX" NAME="RequiresIsolation" VALUE=1 >
								</TD>
								<TD CLASS="CustCheckboxText">
								�Զ�����
								</TD>
							</TR>
						</TABLE>
					</fieldset>
				</TD>
			</TR>
			<TR>
				<TD class="CustButtonSectionRight" NOWRAP="" colspan="4" align="right">
					<INPUT class="Input_Button" TYPE="Button"  value="ȷ  ��"  id=Button1 name=Button1 onclick="javascript:Save();">
				</TD>
				<TD CLASS="CustSpacer">&nbsp;</TD>
			</TR>
		</TABLE>
		</TD>
	</TR>
	<TR>
		<TD>&nbsp;</TD>
		<TD>&nbsp;</TD>
	</TR>
</TABLE>
</TD>
</TR>
</TABLE>
</div>
<input type="hidden" name="func_id" value=<%=m_func_id%>>
<input type="hidden" name="modu_id" value=<%=m_modu_id%>>
<input type="hidden" name="m_status" value=<%=m_Status%>>
</form>
</body>
</html>

