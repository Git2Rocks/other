<%@ page contentType="text/html; charset=gb2312" errorPage="../include/error.jsp"%>
<%@ page language="java" import="com.minstone.util.database.RecordSetObject" %>

<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />

<%
     jbportal.FieldInfo  finfo=new jbportal.FieldInfo();
     finfo.setDEPTID("modu_id");
     finfo.setDEPTNAME("title");
     finfo.setDEPTPARENTID("para_id");
     finfo.setRECVALUE("modu_id");
     finfo.setTOPVALUE("");
     finfo.setLOWFLAG("low_flag");//�Ƿ��ӽڵ�
     finfo.setSELECTNAME("our_select");
     finfo.setMODUTYPE("modu_type");
     String m_sMenuString="";
     String m_sSQl = "select * from modu_def order by para_id asc,DashBoardOrder asc";
     RecordSetObject m_rsAll=null;
	  m_rsAll = oManager.RunQuery("","","","",true,false,m_sSQl);
      try{
	    m_sMenuString = jbportal.PortalUtil.FillClass(m_rsAll,"NULL",finfo);
      }
      catch(Exception e)
      {
        throw e;
      }
%>
<html>
<title>ģ�����</title>

<link rel="STYLESHEET" type="text/css" href="../include/tree/css/WebFX-ContextMenu.css">
<link rel="STYLESHEET" type="text/css" href="../include/tree/css/Node.css">
<link rel="STYLESHEET" type="text/css" href="../css/WebToolBar/toolbar.css">
<script type="text/javascript" src="../include/tree/ContextMenu.js"></script>
<script type="text/javascript" src="../include/tree/genMove.js"></script>
<script type="text/javascript" src="../include/webtoolbar.js"></script>
<script type="text/javascript" src="../include/tree/tTree.js"></script>
<script type="text/javascript" src="../include/tree/PortalTree.js"></script>
<script type="text/javascript">
<!--
var StrLeafImage = "<img src=\"../images/line.gif\" border=0>";
var StrLeafImage1 = "<img src=\"../images/line1.gif\" border=0>";
var StrEmptyImage = "<img src=\"../images/dot.gif\" border=0 style=\"width:15px\">";

var StrCloseImage = "<img src=\"../images/add.gif\" border=\"0\">";
var StrExpandImage = "<img src=\"../images/sub.gif\" border=\"0\">";

var StrCloseImageTop = "<img src=\"../images/top.gif\" border=\"0\">";
var StrExpandImageTop = "<img src=\"../images/-top.gif\" border=\"0\">";
var StrCloseImageBottom = "<img src=\"../images/bottom.gif\" border=\"0\">";
var StrExpandImageBottom = "<img src=\"../images/-bottom.gif\" border=\"0\">";
var StrCloseImageLeft = "<img src=\"../images/left.gif\" border=\"0\">";
var StrExpandImageLeft = "<img src=\"../images/-left.gif\" border=\"0\">";

var StrExpandImage2 = "<img src=\"../images/open.gif\" border=\"0\">";
var StrCloseImage2 = "<img src=\"../images/close.gif\" border=\"0\">";
var StrBackground="../images/line-bg.gif";
var StrFucntionImage = StrCloseImage2;

var StrNewNodeName="�½ڵ�";
var StrNewNodeDesc="�½ڵ�";
var StrNewPersonalize="1";
var StrNewAllowUse="1";

var oTree,ifExpandTree = 1;
oTree = new tTree();
oArray = new tArray();
oArray.Add('cate_desc','����̨');
oArray.Add('cate_value','0');
oTree.Add('0',null,oArray);
<%=m_sMenuString%>
//����ڵ�ĵ������
function GetNewPage(strNodeID){
	//�õ��ڵ����
	var l_moduID;
	l_moduID = strNodeID.substr(0,strNodeID.length-6);
    //alert("l_moduID="+l_moduID);
	//0 : �޸� 1 :����
	window.main.location="ModuleDetails.jsp?m_ModuID=" + l_moduID + "&m_Operation=0";
}


//���ýڵ�Ľ���
function SetDBFocus(strNodeID)
{
	if (StrLastNode != "")
	{
		//try{
			document.all.item(StrLastNode).style.fontWeight = 'normal';
		//}
	}
	document.all.item(strNodeID).style.fontWeight = 'bold';
	StrLastNode = strNodeID;
	//GetNewPage(strNodeID);
	if (StrLastNode=="" || StrLastNode=="0_Value")
		SwitchPage( "property" );	 //Switch to the first page
	ShowPropertyPage();
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
        //alert(l_SQL);
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
                             // alert(NodeName);
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

//�����ݿ�ɾ�����ݺ���ɾ���ڵ�
function OnDeleteNode(NodeName)
{
	var oNode,sPara;
	var strNodeID="",i,l_s;

	oNode = oTree.Find(NodeName);

	//�ж��Ƿ����ֵܽڵ㣬������򽫽����ƶ����ֵܽڵ㡣
	//���û���ֵܽڵ����ƶ����ýڵ�ĸ��ڵ��ϡ�
	if (oNode.paraNode==null)
		{	strNodeID="";		}
	else
		{
			for (l_s in oNode.paraNode.children.nodes)
			{
				if (l_s!=NodeName){
					strNodeID=l_s;
					break;
					}
			}
			if (strNodeID=="")
				{
					strNodeID=oNode.paraNode.nodeName;
				}
		}
	TrID = NodeName + "_TR";
	document.all.item(TrID).removeNode(true);
	oTree.Remove(NodeName);
	StrLastNode = "";
	oTree.AdjustPic();
	if (strNodeID!=""&&strNodeID!="undefined")
	{	strNodeID=strNodeID+"_Value";}
	SetDBFocus(strNodeID);

}
//����ǰ�ڵ�����һ���ӽڵ�
function OnAddNew(){
	//�����ǰû��ѡ�нڵ��򷵻�
	var paraTable,TrID,l_array,oTr,oNode,sReturn,oPara;
	var para_id,modu_id,modu_title,modu_description
	if (StrLastNode=="")
		return;
    //SwitchPage("property");
	//����õ���ص�����,������һ���½ڵ�
	para_id=StrLastNode.substr(0,StrLastNode.length-6);
	AddToDB(para_id);
}

//�����ݿ����һ����¼,�����µļ�¼��NodeValue
function AddToDB(a_paraid)
{

	if (a_paraid == '0') {a_paraid='';}
	document.all.item("HNodeValue").value = a_paraid;
	document.all.item("HNodeName").value = StrNewNodeName;
	document.all.item("HNodeDesc").value = StrNewNodeDesc;
    document.all.item("HNodePersonalize").value=StrNewPersonalize;
    document.all.item("HNodeAllowUse").value=StrNewAllowUse;
	ModuleMain.target="update";
	ModuleMain.action="_TreeAdd.jsp?m_Operation=add";
	ModuleMain.submit();
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
    //  alert('id=' + modu_id);
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
function Layout()
{
    var l_moduID;
    if (StrLastNode=="" || StrLastNode=="0_Value")
    {
        alert("����ѡ������ģ��");
        return;
    }
    l_moduID = StrLastNode.substr(0,StrLastNode.length-6);
    window.main.location="DragAdmin.jsp?modu_id=" + l_moduID;
}

//�õ���Ӧ�Ĺ����б�
function GetFuncList()
{
    var l_moduID,l_nodeName,oNode;

    if (StrLastNode=="" || StrLastNode=="0_Value") { alert("����ѡ������ģ��");return;}
    l_moduID = StrLastNode.substr(0,StrLastNode.length-6);
    //0 : �޸� 1 :����
    window.main.location="funcList.jsp?modu_id=" + l_moduID ;
}
//�õ���Ӧ�Ĺ����б�
function GetModuRightList()
{
    var l_moduID,l_nodeName,oNode;

    if (StrLastNode=="" || StrLastNode=="0_Value") { alert("����ѡ������ģ��");return;}
    l_moduID = StrLastNode.substr(0,StrLastNode.length-6);
    //0 : �޸� 1 :����
    window.main.location="moduRightList.jsp?modu_id=" + l_moduID;
}
//select which page to show, property(ģ��)? function list(����)? or layout page(�Ű�)
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
    //alert(StrLastNode);
	if( sToolBar == "property")
	{
		if( StrLastNode != "")
			GetNewPage( StrLastNode);
		else
			window.main.location = "ModuleDetails.jsp";
	}
	else if(sToolBar == "funclist")
	{
		GetFuncList();
	}
	else if(sToolBar=="modurightlist"){
        GetModuRightList()
    }
    else
	{
		Layout();
	}
}

function window_onload()
{
	var oNode;
//	ContextMenu.intializeContextMenu(); //��ʼ���Ҽ��˵���ֻ��Ҫ��ҳ��onload��ʱ�����һ��
	ShowTree();
	DivResize();

	SwitchPage("property");

	//չ�����ĵ�һ��
	oNode = oTree.Find('0');
	if (oNode!=null){
		oNode.HideTable();
	}
}

function ShowTree()
{

	ifExpandTree = ( ifExpandTree == 1 ) ? 0 : 1; //�л��Ƿ�չ�����н��ı�־
	document.all.item('divRender').innerHTML = oTree.RenderTable(ifExpandTree);

	//document.all.item('divDebug').innerText = oTree.toString();
}

function DivResize(){
	//�ı���ʾ���Ĵ�С
	document.all.item('divRender').style.height = document.body.offsetHeight -10;
}

window.onresize=DivResize;

window.attachEvent("onload",window_onload);
//-->
</script>
<!--������Base������������ȱʡtarget -->
<link rel="STYLESHEET" type="text/css" href="../include/Public.css">
<body leftmargin="0" topmargin="0">
<table border="1" height="100%">
<tr>
	<td height="100%" valign="top">
		<form ACTION="ModuleFrame.jsp" METHOD="post" id="ModuleMain" name="ModuleMain">

		<div id="divDebug"></div>
		<div id="divRender" style="width:200;overflow-x:auto;overflow-y:auto;"></div>
		<input type="hidden" name="HNodeValue" value>
		<input type="hidden" name="HNodeName" value>
		<input type="hidden" name="HNodeDesc" value>
		<input type="hidden" name="HOrder" value>
        <input type="hidden" name="HNodePersonalize" value>
		<input type="hidden" name="HNodeAllowUse" value>
		</form>
	</td>

	<td width="100%">
		<table border="1" width="100%" height="100%">
			<tr>
				<td>
					<div id="toolbar"></div>
					<script type="text/javascript">
						SetToolBarHeight(40);
						AddToolBarItemEx("property","../images/properties_h.gif","","","����","60","0","SwitchPage('property')");
						AddToolBarItemEx("funclist","../images/go.gif","","","�����б�","60","0","SwitchPage('funclist')");
                        AddToolBarItemEx("modurightlist","../images/go.gif","","","Ȩ��","60","0","SwitchPage('modurightlist')");
						AddToolBarItemEx("layout","../images/showtree.gif","","","�Ű�","60","0","SwitchPage('layout')");
						AddToolBarItemEx("refresh","../images/refresh.gif","","","ˢ��","60","1","RefreshPage()");
						AddToolBarItemEx("addnew","../images/createfolder.gif","","","����ģ��","60","1","OnAddNew()");
						AddToolBarItemEx("delete","../images/delete.gif","","","ɾ��ģ��","60","0","OnDelete()");
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
