<%@ page contentType="text/html; charset=gb2312" errorPage="../../include/error.jsp"%>
<%@ page language="java" import="suntek.portal.publicLib.RecordSetObject" %>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />

<%
    //���峣��
    int Init = 0;
    String m_sMenuString="";
    RecordSetObject m_rsAll=null;
    //-----------------------//
    String m_usercode=(String)request.getRemoteUser();
    String m_username =oManager.getCurrentUserName();

    String DetailbaordID = jbportal.PortalUtil.getValue(request.getParameter("DetailbaordID"));
    String DetailBoardType =jbportal.PortalUtil.getValueN(request.getParameter("DetailBoardType"));
    String DetailBoardFunc =jbportal.PortalUtil.getValue(request.getParameter("DetailBoardFunc"));
    String DashboardID =jbportal.PortalUtil.getValue(request.getParameter("DashboardID"));
    String DashboardType =jbportal.PortalUtil.getValueN(request.getParameter("DashboardType"));
    String isHasModule="yes";
    oManager.rsSyncAllModu(m_usercode,true);
    m_rsAll = oManager.rsGetPersonAllModu(m_usercode,false);
    try{
      m_sMenuString =jbportal.PortalUtil.FillClassEx(m_rsAll,"-");
      //System.err.println(m_sMenuString);
      if(m_sMenuString==null || m_sMenuString.equals("")){
        isHasModule="no";
      }
    }
    catch(Exception e){
        System.err.print("Error in PersonalSetting/ModuleMain.jsp,Error Is:"+e.getMessage());
        e.printStackTrace(System.err);
        throw e;
    }
%>
<html>
<title>ģ�����</title>


<link rel="STYLESHEET" type="text/css" href="../../include/tree/css/WebFX-ContextMenu.css">
<link rel="STYLESHEET" type="text/css" href="../../include/tree/css/Node.css">
<link rel="STYLESHEET" type="text/css" href="../../css/WebToolBar/toolbar.css">
<script LANGUAGE="javascript" src="../../include/tree/ContextMenu.js"></script>
<script LANGUAGE="javascript" src="../../include/tree/genMove.js"></script>
<script LANGUAGE="javascript" src="../../include/webtoolbar.js"></script>
<script LANGUAGE="javascript" src="../../include/tree/tTree.js"></script>
<script LANGUAGE="javascript" src="../../include/tree/PortalTree.js"></script>
<script LANGUAGE="javascript">
<!--
//==���￪ʼ Ϊ��ʵ��������ʾ������ģ�Ͷ�������ʵ�������Ĵ���

//ͼƬ·������
var StrLeafImage = "<img src=\"../../images/line.gif\" border=0>";
var StrLeafImage1 = "<img src=\"../../images/line1.gif\" border=0>";
var StrEmptyImage = "<img src=\"../../images/dot.gif\" border=0 style=\"width:15px\">";

var StrCloseImage = "<img src=\"../../images/add.gif\" border=\"0\">";
var StrExpandImage = "<img src=\"../../images/sub.gif\" border=\"0\">";

var StrCloseImageTop = "<img src=\"../../images/top.gif\" border=\"0\">";
var StrExpandImageTop = "<img src=\"../../images/-top.gif\" border=\"0\">";
var StrCloseImageBottom = "<img src=\"../../images/bottom.gif\" border=\"0\">";
var StrExpandImageBottom = "<img src=\"../../images/-bottom.gif\" border=\"0\">";
var StrCloseImageLeft = "<img src=\"../../images/left.gif\" border=\"0\">";
var StrExpandImageLeft = "<img src=\"../../images/-left.gif\" border=\"0\">";

var StrExpandImage2 = "<img src=\"../../images/open.gif\" border=\"0\">";
var StrCloseImage2 = "<img src=\"../../images/close.gif\" border=\"0\">";
var StrPersonalClose = "<img src=\"../../images/personal.gif\" border=\"0\">";
var StrPersonalOpen = "<img src=\"../../images/personalopen.gif\" border=\"0\">";
var StrBackground="../../images/line-bg.gif";
var StrFucntionImage = StrPersonalClose;
//��ǰ�ڵ��ֵ
var StrLastNode="";
var StrNewNodeName="��ģ��";
var StrNewNodeDesc="��ģ��";

var sMsg="";
var sToolBar="property";

//�����Ҽ��˵��¼�
function tNodeOnContextMenu()
{

}
//��������
function ChangeNodeIndex(a_node)
{
	var l_strchild,l_oNode;
	var l_SQL;
	l_SQL="";
	if (a_node.paraNode!=null)
		{

			for (l_strchild in a_node.paraNode.children.nodes)
			{
				l_oNode = a_node.paraNode.children.nodes[l_strchild];
				l_SQL += l_oNode.nodeName + "," + l_oNode.Index() + ";"
			}
		ModuleMain.HOrder.value = l_SQL;
		ModuleMain.target="update";
		ModuleMain.action="_AdjustOrder.jsp";
		ModuleMain.submit ();
		ModuleMain.HOrder.value = "";
		SetDBFocus(a_node.nodeName+"_Value");
		}

}

/*ɾ����ǰѡ�еĽڵ�
*/
function OnDelete(){
		var TrID,NodeName,NodeDesc;
		var oNode,bReturn;

		if ( StrLastNode != "" && StrLastNode != "0_Value" ){

			//�õ���ǰ�е�ID
			NodeName = StrLastNode.substr(0,StrLastNode.length-6);
			//�õ���ǰ�Ľڵ�
			oNode = oTree.Find(NodeName)
			//�õ��ڵ������
			NodeDesc = oNode.array.Find('cate_desc')
			//�жϵ�ǰ�ڵ��Ƿ����ӽڵ㣬�����������ɾ��
			if (oNode.children.count > 0 )
				{
					alert("����ɾ���ڵ�["+NodeDesc+"]���ӽڵ㡣");
					return;
				}
			bReturn=confirm("ȷ��Ҫɾ���ڵ�["+NodeDesc+"]��?");
			if (bReturn!=true)
				{
					return;
				}
			//�����ݿ�ɾ��
			document.all.item("HNodeValue").value = NodeName;
			ModuleMain.target="update";
			ModuleMain.action="_TreeAdd.jsp?m_Operation=del";
			ModuleMain.submit ();
			document.all.item("HNodeValue").value = "";
		}

}

//ɾ���û��ĸ��Ի�ģ�����ã��ָ���ȱʡ��ģ������
function RestoreModule()
{
	//ѯ���û�
	bReturn=confirm("ȷ��Ҫ�ָ���ȱʡ��ģ��������?���ѡ���ǣ�ģ���˳�򽫻ָ���ȱʡ��״̬��");
	//ִ��ɾ��
	if( bReturn )
	{
		ModuleMain.target="";
		ModuleMain.action="_RestoreModule.jsp";
		ModuleMain.submit ();
	}

}

//�ָ���ǰģ��ĵ�ȱʡ�Ű�����
function RestoreLayout()
{
	//����Ǹ���ģ�飬����Ҫ�ָ�
	var l_NodeValue,oNode,l_modutype;
	var l_desc;

	if (StrLastNode=="" || StrLastNode=="0_Value") { alert("����ѡ������ģ��");return;}

	l_NodeValue = StrLastNode.substr(0,StrLastNode.length-6);

	oNode = oTree.Find(l_NodeValue);
	l_modutype = oNode.array.Find("cate_type");
	l_NodeValue = oNode.array.Find("cate_value");

	if( 1 == l_modutype )
	{
		alert("��ǰģ���Ǹ���ģ�飬���ָܻ��Ű棡");
		return;
	}
	bReturn=confirm("ȷ��Ҫ�ָ���ǰģ���ȱʡ�Ű�������?���ѡ���ǣ���ǰģ����Ű潫�ָ���ȱʡ��״̬��");
	//ִ�лָ�
	if( bReturn )
	{
		ModuleMain.target="main";
		ModuleMain.action="_RestoreLayout.jsp?modu_id=" + l_NodeValue +
						  "&modu_type=" + l_modutype;
		ModuleMain.submit ();
	}

}



//����ǰ�ڵ�����һ���ӽڵ�
function OnAddNew(){
	//�����ǰû��ѡ�нڵ��򷵻�
	var paraTable,TrID,l_array,oTr,oNode,sReturn,oPara;
	var para_id,modu_id,modu_title,modu_description

	if (StrLastNode=="")
		return;
	//����õ���ص�����,������һ���½ڵ�
	para_id=StrLastNode.substr(0,StrLastNode.length-6);
	//
	AddToDB(para_id);
}

//�����ݿ����һ����¼,�����µļ�¼��NodeValue
function AddToDB(a_paraid)
{

	if (a_paraid == '0') {a_paraid='';}
	document.all.item("HNodeValue").value = a_paraid;
	document.all.item("HNodeName").value = StrNewNodeName;
	document.all.item("HNodeDesc").value = StrNewNodeDesc;
	ModuleMain.target="update";
	ModuleMain.action="_TreeAdd.jsp?m_Operation=add";
	ModuleMain.submit ();
	document.all.item("HNodeValue").value = "";
	document.all.item("HNodeName").value = "";
	document.all.item("HNodeDesc").value = "";
}

//����һ���µĽڵ�
function AddNewNode(a_NewNodeID)
{
	//�����ǰû��ѡ�нڵ��򷵻�
	var paraTable,TrID,l_array,oTr,oNode,sReturn,oPara;
	var para_id,modu_id,modu_title,modu_description

	if (StrLastNode=="")
		return;

	//����õ���ص�����,������һ���½ڵ�
	para_id=StrLastNode.substr(0,StrLastNode.length-6);

	//


	//�õ��µĽڵ��
	modu_id=a_NewNodeID;
	modu_title=StrNewNodeName;
	modu_description=StrNewNodeDesc;


	l_array = new tArray();
	l_array.Add('cate_desc', modu_description);
	l_array.Add('cate_value',modu_id);
	l_array.Add('cate_para',para_id);

	sReturn=oTree.Add(modu_id,para_id,l_array);


	//�õ���ǰtr����
	TrID= para_id  + "_tr";

	//paraTable=document.all.item(TrID).parentElement.parentElement;
	//��������Ĵ�Table����һ��<TR>
	paraTable=document.all.item(para_id+"_childrentable");

	oTr=paraTable.insertRow();
	oTr.id = modu_id+"_tr";

	//�õ���ǰ�ڵ�
	oNode = oTree.Find(modu_id);

	//�ڵ�ǰ�ڵ�������һ���ӽڵ㣬Ĭ��ΪnewModule
	GetTD1(oNode,oTr);

	SetDBFocus(modu_id + "_Value");
	paraTable.style.display="";

	oTree.AdjustPic();
}

//�����������ɾ��������������ʾ����
function MsgError(a_Error)
{
	alert('����'+ a_Error);
}
//-->
</script>


<script LANGUAGE="javascript">
<!--
var oTree,ifExpandTree = 1;
oTree = new tTree();
oArray = new tArray();
oArray.Add('cate_desc','<%=m_username%>�������');
oArray.Add('cate_value','0');
oTree.Add('0',null,oArray);
<%=m_sMenuString%>


//set the user css
function CSSSetting()
{
	window.showModalDialog("CSSSetting.jsp","","dialogHeight:150px;center:yes;edge:raised;scroll:no;status:no;unadorned:yes;");
}
//����OnClick�¼�
function tNodeOnClick()
{
	var elem = window.event.srcElement;
	var strNodeID;

	strNodeID=elem.id;

        //alert('function=SetDBFocus()');
	SetDBFocus(strNodeID);
}


//����ڵ�ĵ������
function GetNewPage(strNodeID){
	//�õ��ڵ����
	var l_NodeValue,oNode,l_modutype;
	var l_desc;
	l_NodeValue = strNodeID.substr(0,strNodeID.length-6);

	//0 : �޸� 1 :����
	if ( parent != null )
	{
		oNode = oTree.Find(l_NodeValue);
		l_modutype = oNode.array.Find("cate_type");
		l_NodeValue = oNode.array.Find("cate_value");
		l_desc = oNode.array.Find("cate_desc");


		window.main.location="ModuleDetails.jsp?m_moduid=" + l_NodeValue +
							  "&modu_type=" + l_modutype + "&Title=" + l_desc;
	}
}


function ShowNode(a_NodeValue)
{

	var l_NodeValue = a_NodeValue.substr(0,a_NodeValue.length-6);

	oNode = oTree.Find(l_NodeValue);

        //alert("function=SetDBFocus()");
	SetDBFocus(a_NodeValue );

	oTemp = oNode.paraNode;
	while ( !(oTemp.nodeName == "0") )
	{
		l_tb = document.all.item(oNode.nodeName + '_childrentable');
		l_dis = l_tb.style.display;
		if ( l_dis == 'none' )
		{
			oTemp.HideTable();
		}
		oTemp = oTemp.paraNode;
	}
}

//���ýڵ�Ľ���
function SetDBFocus(strNodeID)
{
	if (StrLastNode != "")
	{
			document.all.item(StrLastNode).style.fontWeight = 'normal';
	}

	document.all.item(strNodeID).style.fontWeight = 'bold';
        StrLastNode = strNodeID;

	if (StrLastNode=="" || StrLastNode=="0_Value")
		SwitchPage( "property" );	 //Switch to the first page
        //alert("function=ShowPropertyPage()");
	ShowPropertyPage();
}

//select which page to show, property? function list? or layout page
function SwitchPage( sNewToolBar )
{
	if ( sToolBar != "" )
		SetCheck( sToolBar,false );
	SetCheck( sNewToolBar, true );
	sToolBar = sNewToolBar;
	ShowPropertyPage();
}

function ShowPropertyPage()
{
	if( sToolBar == "property")
	{
		if( StrLastNode != "")
        {
        	GetNewPage( StrLastNode);
        }
		else
        {
			window.main.location = "ModuleDetails.jsp";
        }
	}
	else if(sToolBar == "funclist")
	{
		GetFuncList();
	}
	else
	{
                //alert("function=Layout()");
		Layout();
	}
}
//==������� Ϊ��ʵ��������ʾ������ģ�Ͷ�������ʵ�������Ĵ���
function Layout()
{
	var l_moduID,oNode,l_modutype,l_desc;
	var l_allowpersonize;

	if (StrLastNode=="" || StrLastNode=="0_Value") { alert("����ѡ������ģ��");return;}

	l_moduID = StrLastNode.substr(0,StrLastNode.length-6);

	//�ж��Ƿ�������Ի�
	if ( parent != null  )
	{
		oNode = oTree.Find(l_moduID);
		l_modutype = oNode.array.Find("cate_type");

		l_moduID = oNode.array.Find("cate_value");
                //alert('l_modutype='+ l_modutype + ';l_moduID=' + l_moduID);
		l_desc = oNode.array.Find("cate_desc");
		l_allowpersonize = oNode.array.Find("cate_allowpersonize");

		if (l_allowpersonize==0)
		{
			alert("ģ��(" + l_desc + ")���������Ի�!" );
			return;
		}

		window.main.location="DragAdmin.jsp?modu_id=" + l_moduID + "&modu_type=" + l_modutype;
	}

}

//�õ���Ӧ�Ĺ����б�
function GetFuncList()
{
	var l_moduID,l_nodeName,oNode;
	var l_NodeValue,l_desc,l_modutype,l_allowpersonize;

	if (StrLastNode=="" || StrLastNode=="0_Value") { alert("����ѡ������ģ��");return;}
	l_moduID = StrLastNode.substr(0,StrLastNode.length-6);

	//0 : �޸� 1 :����
	if ( parent != null )
	{
		oNode = oTree.Find(l_moduID);
		l_modutype = oNode.array.Find("cate_type");
		l_NodeValue = oNode.array.Find("cate_value");
		l_desc = oNode.array.Find("cate_desc");
		l_allowpersonize = oNode.array.Find("cate_allowpersonize");

		if (l_allowpersonize==0)
		{
			alert("ģ��(" + l_desc + ")���������Ի�!" );
			return;
		}
        window.main.location="funcList.jsp?modu_id=" + l_NodeValue +
							 "&modu_type="+l_modutype;
	}

}
function window_onload()
{
	var oNode;
	ShowTree();
	DivResize();

	//չ�����ĵ�һ��
	oNode = oTree.Find('0');
	if (oNode!=null){
		oNode.HideTable();
	}

	if( m_isHasModel=="yes" && m_DetailBoardID != "" )
	{
		if (m_DetailBoardFunc=='funclist')
		{
			ShowNode( m_DashBoardID + "-" + m_DashBoardType +"_Value");
			SwitchPage(m_DetailBoardFunc);
		}
		else
		{
			ShowNode( m_DetailBoardID + "-" + m_DetailBoardType +"_Value");
			SwitchPage("property");
		}
	}
	else
		SwitchPage("property");
}
function ShowTree()
{

	ifExpandTree = ( ifExpandTree == 1 ) ? 0 : 1; //�л��Ƿ�չ�����н��ı�־
	document.all.item('divRender').innerHTML = oTree.RenderTable(ifExpandTree);
//	document.all.item('divDebug').innerText = oTree.toString();
}

function DivResize(){
	//�ı���ʾ���Ĵ�С
	document.all.item('divRender').style.height = document.body.offsetHeight -10;
}

var m_DetailBoardID = '<%=DetailbaordID%>';
var m_DetailBoardType = '<%=DetailBoardType%>';

var m_DetailBoardFunc = '<%=DetailBoardFunc%>';
var m_DashBoardID  ='<%=DashboardID%>';
var m_DashBoardType = '<%=DashboardType%>';
var m_isHasModel = '<%=isHasModule%>';

window.onresize=DivResize;

window.attachEvent("onload",window_onload);
//-->
//-->



</script>
<!--������Base������������ȱʡtarget -->
<link rel="STYLESHEET" type="text/css" href="../../include/Public.css">

<body leftmargin="0" topmargin="0">
<table border="1" height="100%">
<tr>
	<td height="100%" valign="top">
		<form ACTION="ModuleMain.jsp" METHOD="post" id="ModuleMain" name="ModuleMain">
			<!--div id="TitleDiv" style="height:12">
				<table class="menutitle" width="100%" cellspacing="0" cellpadding="0" border="0">
					<tr>
						<td>ģ�����</td>
						<td width="20"><img id="funclist" alt="�����б�" src="../../images/go.gif" class="image" onclick="JavaScript:GetFuncList();" WIDTH="16" HEIGHT="16"></td>
						<td width="20"><img id="go" alt="���ù���" src="../../images/showtree.gif" class="image" onclick="JavaScript:Layout();" WIDTH="16" HEIGHT="16"></td>
						<td width="20"><img id="Refresh" alt="ˢ��" src="../../images/refresh.gif" class="image" onclick="JavaScript:RefreshPage()" WIDTH="11" HEIGHT="11"></td>
					</tr>
				</table>
			</div-->

			<div id="divDebug"></div>
			<div id="divRender" style="width:200;overflow-x:auto;overflow-y:auto;"></div>
			<input type=hidden name="HNodeValue" value="">
			<input type=hidden name="HNodeName" value="">
			<input type=hidden name="HNodeDesc" value="">
			<input type=hidden name="HOrder" value="">
		</form>
	</td>

	<td width="100%">
		<table border="1" width="100%" height="100%">
			<tr>
				<td>
					<div id="toolbar"></div>
					<script language="javascript">
						SetToolBarHeight(40);
						AddToolBarItemEx("property","../../images/properties_h.gif","","","����","60","0","SwitchPage('property')");
						AddToolBarItemEx("funclist","../../images/go.gif","","","�����б�","60","0","SwitchPage('funclist')");
						AddToolBarItemEx("layout","../../images/showtree.gif","","","�Ű�","60","0","SwitchPage('layout')");
						AddToolBarItemEx("restoremodule","../../images/undo.gif","","","ģ��ָ�","60","1","RestoreModule()");
						AddToolBarItemEx("restorelayout","../../images/dbprops.gif","","","�Ű�ָ�","60","0","RestoreLayout()");
						AddToolBarItemEx("refresh","../../images/refresh.gif","","","ˢ��","60","1","RefreshPage()");
						//AddToolBarItemEx("navlink","../../images/navlink.gif","","","������","60","1","CSSSetting()");
						window.document.getElementById("toolbar").innerHTML=GenToolBarV();
					</script>
				</td>
			</tr>
			<tr height="100%">
				<td>
					<iframe name="main" FRAMEBORDER=1 width=100% height=100% src="">
					</iframe>
					<iframe name="update" width=0 height=0 src="">
					</iframe>
				</td>
			</tr>
		</table>
	</td>

</tr>
</table>
</body>
</html>
