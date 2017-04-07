<%@ page contentType="text/html; charset=gb2312" errorPage="../../include/error.jsp"%>
<%@ page language="java" import="java.util.*,java.sql.*,com.minstone.util.database.RecordSetObject,jbportal.PortalUtil" %>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
    jbportal.FieldInfo  finfo=new jbportal.FieldInfo();
    finfo.setDEPTID("func_id");
    finfo.setDEPTNAME("title");
    finfo.setDEPTPARENTID("modu_id");
    finfo.setRECVALUE("func_id");
    finfo.setTOPVALUE("");
    finfo.setLOWFLAG("low_flag");//�Ƿ��ӽڵ�
    finfo.setSELECTNAME("our_select");
    finfo.setMODUTYPE("Modu_Type");

	String m_sMenuString = "";
	RecordSetObject m_rsAll = null;

    String m_usercode=(String)request.getRemoteUser();
    String m_username =oManager.getCurrentUserName();
	String m_sSQL = "(SELECT pers_modu.modu_id AS func_id, pers_modu.para_id AS modu_id, " +
			 "pers_modu.Title, pers_modu.DashBoardOrder AS seq, 0 AS modu_type " +
			 " FROM  pers_modu Where para_id is null and user_code = '" + m_usercode + "' " +
			 ") union (Select func_id,modu_id,Title,0 as seq,1 as modu_type from pers_func where user_code='" + m_usercode + "') " +
			 "  order by modu_id asc,seq asc";

	m_rsAll = oManager.RunQuery ("","","","",true,false,m_sSQL);
	try
          {
	    m_sMenuString = PortalUtil.FillClass(m_rsAll,"NULL",finfo);
          }
          catch(Exception e){
             throw e;
          }

%>
<html>
<title>���ܹ���</title>
<link rel="STYLESHEET" type="text/css" href="../../include/tree/css/WebFX-ContextMenu.css">
<link rel="STYLESHEET" type="text/css" href="../../include/tree/css/Node.css">
<link rel="STYLESHEET" type="text/css" href="../../css/WebToolBar/toolbar.css">
<script type="text/javascript" src="../../include/tree/ContextMenu.js"></script>
<script type="text/javascript" src="../../include/webtoolbar.js"></script>
<script type="text/javascript" src="../../include/tree/tTree.js"></script>
<script type="text/javascript" src="../../include/tree/PortalTree.js"></script>
<script type="text/javascript">
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

var StrExpandImage2 = "<img src=\"../../images/personalopen.gif\" border=\"0\">";
var StrCloseImage2 = "<img src=\"../../images/personal.gif\" border=\"0\">";
var StrFucntionImage = "<img src=\"../../images/function.gif\" border=\"0\">";
var StrBackground="../../images/line-bg.gif";

//��ǰ�ڵ��ֵ
var StrLastNode="";
var StrNewNodeName="�¹���";
var StrNewNodeDesc="�¹���";

var StrStatus="";
var sMsg="";


//�����Ҽ��˵��¼�
function tNodeOnContextMenu()
{
	/*
   popupoptions = [
   						new ContextItem("ˢ�±�ҳ",function(){window.location.reload();}),
						new ContextItem("Disabled Item",null,true),
						new ContextSeperator(),
						new ContextItem("��ӡ",function(){window.print()}),
						new ContextItem("�鿴������",function(){tNodeOnClick();document.body.focus();}),
						new ContextSeperator(),
   						new ContextItem("����",function(){alert('����');document.body.focus();})
   				  ]

   ContextMenu.display(popupoptions)*/
}


//����ڵ�ĵ������
function GetNewPage(strNodeID){
	//�õ��ڵ����
	var l_NodeValue,oNode;

	l_NodeValue = strNodeID.substr(0,strNodeID.length-6);

	//0 : �޸� 1 :����
	window.main.location="FunctionDetails.jsp?m_NodeValue=" + l_NodeValue + "&m_Status=" + StrStatus ;
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
	GetNewPage(strNodeID);
}
/*ɾ����ǰѡ�еĽڵ�
*/
function OnDelete(){
                //����õ���ص�����,������һ���½ڵ�
                para_id=StrLastNode.substr(0,StrLastNode.length-6);
                  //alert(para_id);
                //�жϽڵ������Ƿ���0--��ʾ��ģ��
                oNode=oTree.Find(para_id);
                  //alert(para_id);
                if (oNode==null){return;}

                sModutype = oNode.array.Find("cate_type");

                  //alert(para_id);
                if (sModutype=="0") {alert("�Բ��𣬲���ɾ��ģ�飡"); return;}

		var TrID,NodeName,NodeDesc;
		var oNode,bReturn;

		if (StrLastNode != ""&&StrLastNode!="0_Value"){

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

			//�����ݿ�ɾ��
			document.all.item("HNodeValue").value = NodeName;
			document.all.item("NodeDesc").value = NodeDesc;
			ModuleMain.target="update";
			ModuleMain.action="_DelConfirm.jsp?m_Operation=del";
			ModuleMain.submit();
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
	var para_id,modu_id,modu_title,modu_description,sModutype

	if (StrLastNode=="")
		return;
	//����õ���ص�����,������һ���½ڵ�
	para_id=StrLastNode.substr(0,StrLastNode.length-6);
    if(para_id=="0" || para_id==null){
		alert("�Բ���ֻ����ģ������ӹ��ܣ�����ѡ��һ��ģ�顣");
		return;
    }
	//�жϽڵ������Ƿ���0--��ʾ��ģ��
	oNode=oTree.Find(para_id);

	if (oNode==null){return;}

	sModutype = oNode.array.Find("cate_type");
	if (sModutype=="1") {alert("�Բ���ֻ����ģ������ӹ��ܣ�"); return;}
	//
	AddToDB(para_id);
}

//�����ݿ����һ����¼,�����µļ�¼��NodeValue
function AddToDB(a_paraid)
{
        //alert(a_paraid);
	document.all.item("HNodeValue").value = a_paraid;
	document.all.item("HNodeName").value = StrNewNodeName;
	document.all.item("HNodeDesc").value = StrNewNodeDesc;
	ModuleMain.target="update";
	ModuleMain.action="_FunctionModi.jsp?m_Operation=add";
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
	//
	//�õ��µĽڵ��
	modu_id=a_NewNodeID;
	modu_title=StrNewNodeName;
	modu_description=StrNewNodeDesc;


	l_array = new tArray();
	l_array.Add('cate_desc', modu_description);
	l_array.Add('cate_value',modu_id);
	l_array.Add('cate_para',para_id);
	l_array.Add('cate_type',"1");

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

	StrStatus="true";
	SetDBFocus(modu_id + "_Value");
	StrStatus="";
	paraTable.style.display="";

	oTree.AdjustPic();
}

//�����������ɾ��������������ʾ����
function MsgError(a_Error)
{
	alert('����'+ a_Error);
}
//==������� Ϊ��ʵ��������ʾ������ģ�Ͷ�������ʵ�������Ĵ���

//-->
</script>


<script type="text/javascript">
<!--
var oTree,ifExpandTree = 1;
oTree = new tTree();
oArray = new tArray();
oArray.Add('cate_desc','<%=m_username%>���˹���');
oArray.Add('cate_value','0');
oArray.Add('cate_type','0')
oTree.Add('0',null,oArray);
<%=m_sMenuString%>

function window_onload()
{
	var oNode;
//	ContextMenu.intializeContextMenu(); //��ʼ���Ҽ��˵���ֻ��Ҫ��ҳ��onload��ʱ�����һ��
	ShowTree();
	DivResize();

	//չ�����ĵ�һ��
	oNode = oTree.Find('0');
	if (oNode!=null){
		oNode.HideTable();
	}

	window.main.location="FunctionDetails.jsp";
}

function ShowTree()
{

	ifExpandTree = ( ifExpandTree == 1 ) ? 0 : 1; //�л��Ƿ�չ�����н��ı�־
	document.all.item('divRender').innerHTML = oTree.RenderTable(ifExpandTree);
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
<link rel="STYLESHEET" type="text/css" href="../../include/Public.css">

<body leftmargin="0" topmargin="0">
<table border="1" height="100%">
<tr>
	<td height="100%" valign="top">
		<form ACTION="FunctionMain.jsp" METHOD="post" id="ModuleMain" name="ModuleMain">
			<!--div id="TitleDiv" style="height:12">
				<table class="menutitle" width="100%" cellspacing="0" cellpadding="0" border="0">
					<tr>
						<td>���ܹ���</td>
						<td width="20"><img id="Refresh" alt="ˢ��" src="../../images/refresh.gif" class="image" onclick="JavaScript:RefreshPage()" WIDTH="11" HEIGHT="11"></td>
						<td width="20"><img id="AddNew" alt="����" src="../../images/Plus.gif" onclick="JavaScript:OnAddNew();" class="image" WIDTH="11" HEIGHT="11"></td>
						<td width="20"><img id="Delete" alt="ɾ��" src="../../images/minus.gif" onclick="JavaScript:OnDelete();" class="image" WIDTH="11" HEIGHT="11"></td>
					</tr>
				</table>
			</div-->

			<div id="divDebug"></div>
			<div id="divRender" style="width:200;overflow-x:auto;overflow-y:auto;"></div>
			<input type=hidden name="HNodeValue" value>
			<input type=hidden name="HNodeName" value>
			<input type=hidden name="HNodeDesc" value>
			<input type=hidden name="NodeDesc" value>
		</form>
	</td>

	<td width="100%">
		<table border="1" width="100%" height="100%">
			<tr>
				<td>
					<div id="toolbar"></div>
					<script type="text/javascript">
						SetToolBarHeight(40);
						AddToolBarItemEx("refresh","../../images/refresh.gif","","","ˢ��","60","0","RefreshPage()");
						AddToolBarItemEx("addnew","../../images/createfolder.gif","","","��������","60","1","OnAddNew()");
						AddToolBarItemEx("delete","../../images/delete.gif","","","ɾ������","60","0","OnDelete()");
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


