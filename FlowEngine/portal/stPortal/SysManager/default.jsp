<%@ page contentType="text/html; charset=gb2312" %>
<%@ page language="java" import="java.util.*" %>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
    boolean m_IfManager=false;
    String m_StartURL=null;
    String m_PageTitle="ϵͳ����";
    String m_StartID=null;
    String m_Css=null;
    String temp = null;
    String DetailBoardID = "";
    String DetailBoardType = "";
    m_Css=oManager.getCurrentUserCSSFileName();
    if(m_Css==null||m_Css.equals(""))
      m_Css="standard.css";
	m_Css = "../css/"+m_Css;
	//������ϵͳ�������ڣ��ж��û��Ƿ�ϵͳ����Ա�����������û�й���ģ������Ȩ��
    m_IfManager=oManager.currentUserIsAdmin();
    DetailBoardID = request.getParameter("DetailBoardID");
    if (DetailBoardID == null)
        DetailBoardID = "0001";

    DetailBoardType = request.getParameter("DetailBoardType");
    if (DetailBoardType == null)
        DetailBoardType = "1";

    String DashboardID = request.getParameter("DashboardID");
    if (DashboardID == null)
        DashboardID = "0001";

    String DashboardType = request.getParameter("DashboardType");
    if (DashboardType == null)
        DashboardType = "0";


    temp = DetailBoardID;
    if (temp != null)
      {
        m_StartURL = "../PersonalSetting/structure/ModuleMain.jsp";
        m_StartURL = m_StartURL + "?DetailbaordID=" + DetailBoardID + "&DetailBoardType=" + DetailBoardType ;
        m_StartURL = m_StartURL + "&DashboardID=" + DashboardID + "&DashboardType=" + DashboardType ;
        m_StartURL = m_StartURL + "&DetailBoardFunc=" + request.getParameter("DetailBoardFunc");
        m_StartID = "PersonStru";
          //  m_StartURL = "../PersonalSetting/structure/ModuleMain.jsp";
          //  m_StartURL = m_StartURL + "?DetailbaordID=" + DetailBoardID + "&DetailBoardType=" + DetailBoardType;
          //  m_StartID = "PersonStru";
      }
    else{
      if (m_IfManager){
        m_StartURL = "ModuFrame.jsp";
        m_StartID = "administrator";
      }
      else{
        m_StartURL = "../PersonalSetting/module/ModuleMain.jsp";
        m_StartID = "Personalmodu";
      }
    }
%>
<HTML>
<HEAD>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title><%=m_PageTitle%></title>
<LINK ID="lnkStylesheet" rel="stylesheet" href="<%=m_Css%>" />
<SCRIPT type="text/javascript">
<!--
	var StrCurrNode='<%=m_StartID%>';
	var StrCurrURL='<%=m_StartURL%>';
	var m_CurrentBoardID = '<%=DashboardID%>';
	var m_DetailBoardID =  '<%=DetailBoardID%>';
	var m_CurrentBoardType =  '<%=DashboardType%>';
	var m_DetailBoardType =  '<%=DetailBoardType%>';
    var strOldURL="";

	window.attachEvent("onload",window_onload);

	function ChangePage(a_url,item)
	{
		IFrame1.document.location=a_url;
		if (StrCurrNode != "")
		{
          document.all.item(StrCurrNode).className="DashNavDashArea";
		}
		item.className="DashNavCurDashArea";
		StrCurrNode=item.id;

	}

	function window_onload()
	{
		if (StrCurrNode != "")
		{
			document.all.item(StrCurrNode).className="DashNavCurDashArea";
		}
		IFrame1.window.location = StrCurrURL;

	}

	function Return()
	{
		var url;
		url = "../default.jsp?DashboardID=" + m_CurrentBoardID + "&DashboardType=" + m_CurrentBoardType;
		url += "&DetailBoardID=" + m_DetailBoardID + "&DetailBoardType=" + m_DetailBoardType;
		window.location = url;
	}
    function clearSession(){
      try{
        //�������ˢ�´������ǹرմ��ڡ�
        if(IECloseMonitor.isWindowClosing()){
          xhreq = new ActiveXObject("Microsoft.XMLHTTP");
          xhreq.open("GET", "/portallogout?windowclose=1", false);
          xhreq.setRequestHeader("Content-Type","text/html");
          xhreq.send();
          var returnValue= xhreq.statusText;
        }
        else{
        }
      }
      catch(e){}
    }
//-->
</SCRIPT>

</HEAD>
<BODY onunload="javascript:clearSession();" topmargin="0" leftmargin="0" bgcolor="White" scroll="no">
<OBJECT id="IECloseMonitor" style="display:none" classid="clsid:2BA5FD98-D118-469C-868F-351BC58EA0AA" codeBase="../../Login/IECloseMonitor.dll"></OBJECT>
<table border="0" cellpadding="0" cellspacing="0" width="100%" HEIGHT=100%>
	<tr><td>
		<table border="0" class="DashTitleArea" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>
					<table height="100%" cellpadding="0" cellspacing="0" border="0">
						<tr class="DashTitleGroup">
							<td class="DashTitleImage"></td>
							<td class="DashTitle"><span id="DashTitle">
								<nobr><%=m_PageTitle%></nobr></span>
							</td>
							<td class="DashTitleSpacer">
								<img width="150px" height="1px" src="../include/pixel.gif" alt="">
							</td>
						</tr>
					</table>
				</td>
				<td>
					<table border="0" cellpadding="0" cellspacing="0" align="right">
						<tr>
							<td class="DashCommandArea">
							<nobr>
							</nobr>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</td></tr>
	<tr><td valign="top">
	<TABLE cellspacing="0" cellpadding="0" width="100%" class="DashNavArea" border="0" >
			<TR>
				<% if(m_IfManager){%>
                <TD id="SystemSetup" class="DashNavDashArea" onclick="JavaScript:ChangePage('SystemSetupMain.jsp',this);this.blur();">
					<A class="DashNavLink" href="#" title="ϵͳ����" onclick="this.blur()">
					<nobr>ϵͳ����</nobr></A>
				</TD>
				<TD id="administrator" class="DashNavDashArea"  onclick="JavaScript:ChangePage('ModuFrame.jsp',this);this.blur();">
					<A class="DashNavLink" href="#" title="����ģ��" onclick="this.blur()">
					<nobr>����ģ��</nobr></A>
				</TD>
				<TD id="functionadmin" class="DashNavDashArea" onclick="JavaScript:ChangePage('FunctionMain.jsp',this);this.blur();">
					<A class="DashNavLink" href="#" title="���ù���" onclick="this.blur()">
					<nobr>���ù���</nobr></A>
				</TD>
				<%}%>
				<TD id="Personalmodu" class="DashNavDashArea" onclick="JavaScript:ChangePage('../PersonalSetting/module/ModuleMain.jsp',this);this.blur();">
					<A class="DashNavLink" href="#" title="����ģ��" onclick="this.blur()">
					<nobr>����ģ��</nobr></A>
				</TD>
				<TD id="PersonFunc" class="DashNavDashArea" onclick="JavaScript:ChangePage('../PersonalSetting/function/FunctionMain.jsp',this);this.blur();">
					<A class="DashNavLink" href="#" title="���˹���" onclick="this.blur()">
					<nobr>���˹���</nobr></A>
				</TD>
				<TD id="PersonStru" class="DashNavDashArea" onclick="JavaScript:ChangePage('../PersonalSetting/structure/ModuleMain.jsp',this);this.blur();">
					<A class="DashNavLink" href="#" title="���˷�����" onclick="this.blur()">
					<nobr>���˷�����</nobr></A>
				</TD>
				<TD id="ReturnMain" class="DashNavDashArea" onclick="JavaScript:Return();this.blur();">
					<A class="DashNavLink" href="#" title="����������" onclick="this.blur()">
					<nobr>����������</nobr></A>
				</TD>
				<TD width="100%">&nbsp;</TD>
			</TR>
	</TABLE>
		</td></tr>
		<tr><td height="100%">
			<TABLE HEIGHT=100% width="100%">
				<TR><TD>
				<IFRAME ID=IFrame1 FRAMEBORDER=0 width="100%" height="100%" SCROLLING=NO></IFRAME>
				</TD>
                </TR>
			</TABLE>
		</td></tr>
</table>
</BODY>
</HTML>
