<%@ page contentType="text/html; charset=gb2312" errorPage="../include/error.jsp"%>
<%@ page import="com.minstone.portal.PortalConstants" %>
<%@ page import="com.minstone.util.database.RecordSetObject" %>
<%@ page import="java.util.*,java.sql.*,jbportal.PortalUtil" %>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
    jbportal.FieldInfo  finfo=new jbportal.FieldInfo();
    String addtype=request.getParameter("addtype");
    String m_sMenuString = "";
    RecordSetObject m_rsAll = null;
    String m_username = "";

    //���벿���б�
    finfo.setDEPTID("FRAM_CODE");
    finfo.setDEPTNAME("DEPT_NAME");
    finfo.setDEPTPARENTID("PARA_CODE");
    finfo.setRECVALUE("DEPT_CODE");
    finfo.setTOPVALUE("");
    finfo.setLOWFLAG("low_flag");//�Ƿ��ӽڵ�
    finfo.setSELECTNAME("our_select");
    finfo.setMODUTYPE("type");

    m_rsAll=oManager.getUserDeptGroupInfo(PortalConstants.DEPARTMENT);
    try
      {
        m_sMenuString = PortalUtil.FillClass(m_rsAll,"NULL",finfo);
      }
      catch(Exception e)
      {
         throw e;
      }

    //�����û����б�
    finfo.setDEPTID("GROP_CODE");
    finfo.setDEPTNAME("GROP_NAME");
    finfo.setDEPTPARENTID("type");
    finfo.setRECVALUE("GROP_CODE");
    finfo.setTOPVALUE("");
    finfo.setLOWFLAG("low_flag");//�Ƿ��ӽڵ�
    finfo.setSELECTNAME("our_select");
    finfo.setMODUTYPE("type");
    m_rsAll=oManager.getUserDeptGroupInfo(PortalConstants.GROUP);
    try
      {
        m_sMenuString += PortalUtil.FillClass(m_rsAll,"2",finfo);
      }
      catch(Exception e)
      {
         throw e;
      }

    //�����û��б�
    finfo.setDEPTID("USER_CODE");
    finfo.setDEPTNAME("USER_NAME");
    finfo.setDEPTPARENTID("FRAM_CODE");
    finfo.setRECVALUE("USER_CODE");
    finfo.setTOPVALUE("");
    finfo.setLOWFLAG("low_flag");//�Ƿ��ӽڵ�
    finfo.setSELECTNAME("our_select");
    finfo.setMODUTYPE("type");
    m_rsAll=oManager.getUserDeptGroupInfo(PortalConstants.USER);
    try
      {
        m_sMenuString += PortalUtil.FillClass(m_rsAll,"-",finfo);
      }
      catch(Exception e)
      {
         throw e;
      }
    String modu_id=session.getAttribute("modu_id").toString();
    Vector userlist=new Vector();
    session.setAttribute("userlist",userlist);
%>
<html>
<META HTTP-EQUIV="pragma" CONTENT="no-cache">
<title>����û�Ȩ��</title>
<link rel="STYLESHEET" type="text/css" href="../include/tree/css/WebFX-ContextMenu.css">
<link rel="STYLESHEET" type="text/css" href="../include/tree/css/Node.css">
<link rel="STYLESHEET" type="text/css" href="../css/WebToolBar/toolbar.css">
<script type="text/javascript" src="../include/tree/ContextMenu.js"></script>
<script type="text/javascript" src="../include/webtoolbar.js"></script>
<%
//�ļ�tTree.js���й���ģ�Ͷ����һЩ���õ�ǰ̨����
	String l_first=null;

	l_first = "oArray = new tArray();" ;
	l_first = l_first + "oArray.Add('cate_desc','��֯�ܹ�');" ;
	l_first = l_first + "oArray.Add('cate_value','-1');" ;
	l_first = l_first + "oTree.Add('-1',null,oArray);"  ;
	l_first = l_first +" oArray = new tArray();" ;
	l_first = l_first + "oArray.Add('cate_desc','����/�û��б�');" ;
	l_first = l_first + "oArray.Add('cate_value','0');" ;
	l_first = l_first + "oTree.Add('0','-1',oArray);"  ;
	l_first = l_first +" oArray = new tArray();" ;
	l_first = l_first + "oArray.Add('cate_desc','�û����б�');" ;
	l_first = l_first + "oArray.Add('cate_value','2');" ;
	l_first = l_first + "oTree.Add('2','-1',oArray);"  ;
    /*
	l_first = l_first +" oArray = new tArray();" ;
	l_first = l_first + "oArray.Add('cate_desc','�û��б�');" ;
	l_first = l_first + "oArray.Add('cate_value','1');" ;
	l_first = l_first + "oTree.Add('1','-1',oArray);"  ;
    */
	l_first = l_first +" oArray = new tArray();" ;
	l_first = l_first + "oArray.Add('cate_desc','EveryOne(�����û�)');" ;
	l_first = l_first + "oArray.Add('cate_value','AllPortalUser');" ;
	l_first = l_first + "oArray.Add('cate_type','2');" ;
	l_first = l_first + "oTree.Add('AllPortalUser','-1',oArray);"  ;

	m_sMenuString = l_first + m_sMenuString;

%>
<script type="text/javascript" src="../include/tree/tTree.js"></script>
<script type="text/javascript">
<!--
//==���￪ʼ Ϊ��ʵ��������ʾ������ģ�Ͷ�������ʵ�������Ĵ���

//ͼƬ·������
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

var StrExpandImage2 = "<img src=\"../images/personalopen.gif\" border=\"0\">";
var StrCloseImage2 = "<img src=\"../images/personal.gif\" border=\"0\">";
var StrFucntionImage = "<img src=\"../images/personal.gif\" border=\"0\">";
var StrBackground="../images/line-bg.gif";
//��ǰ�ڵ��ֵ
var StrLastNode="";
var StrNewNodeName="�¹���";
var StrNewNodeDesc="�¹���";

var StrStatus="";
var sMsg="";
//--�������-------------------------------------------------------------

function tNode(a_NodeName,a_ParaName,a_ParaNode,a_tAry,a_Tree)
{
	this.nodeName = a_NodeName; //������
	this.paraName = a_ParaName; //��㸸����
	this.paraNode = a_ParaNode; //���ĸ����
	this.array = a_tAry; //����������������������ȣ�����һ��tArray��ǿ��������
	this.tree = a_Tree; //������ڵ�tTree��������
	this.children = new tArray(); //���Ķ��Ӽ��ϣ���һ��tArray�����

	this.Update = tNodeUpdate; //����һ�����ķ���
	this.toString = tNodetoString; //Debug�õĴ�������Ϣ�ķ���
	this.isLeaf = tNodeisLeaf; //�жϱ�����Ƿ�Ҷ�ӽ��ķ���
	this.Layer = tNodeLayer; //���ر���������еĵڼ��㣬��0��ʼ����
	this.Index = tNodeIndex; //������ͬһ���б�����ǵڼ�����㣬��0��ʼ����
	this.BrotherCount = tNodeBrotherCount; //����ͬһ�����ж��ٸ��ֵܽ�㣬�����Լ�

	//�������ͨ�õģ��������Ϊ��ʵ��������ʾ��д��
	this.RenderTable = tNodeRenderTable;
	this.HideTable = tNodeHideTable;
	this.ExpandImage = tNodeExpandImage;
	this.ExpandNode = tExpandNode;
	this.OnClick = tNodeOnClick;
	this.OnContextMenu = tNodeOnContextMenu;
	this.VLine = tNodeVLine;
	this.AdjustPic = tNodeAdjustPic;
}

/*
function tNodeVLine()
���ܣ�����һ������ǰ��Ӧ�÷�ʲô����style
���룺
�����
*/
function tNodeVLine()
{
	var l_td = document.all.item(this.nodeName + "_vline");
	if ( l_td == null ){
		return;
	}
	if (!( this.paraNode != null
			&& this.paraNode.Index() == ( this.paraNode.BrotherCount() -1 )))
	{
		l_td.style.backgroundPositionX = "4px";
		l_td.style.backgroundImage = "url(../images/line-bg.gif)";
		l_td.style.backgroundRepeat = "repeat-y";
	}
}

//�������ļӼ�š����ߡ��ļ���ͼƬ
function tNodeAdjustPic(a_expand)
{
	var l_tb = document.all.item(this.nodeName + '_childrentable');
	var l_expand = document.all.item(this.nodeName + "_expand");
	l_dis = l_tb.style.display;

	l_folder = document.all.item(this.nodeName + '_folder');

	l_expand.style.cursor = ( this.children.count > 0 ) ? "hand" : "";

	if ( l_dis == '' && this.children.count > 0 )
	{
		l_expand.innerHTML = this.ExpandImage(1);
		if (this.array.Find('ExpandImage') != null ) //������Զ����չ��ͼƬ����
			l_folder.innerHTML = this.array.Find('ExpandImage');
		else //������ȱʡ��չ��ͼƬ
			l_folder.innerHTML = StrExpandImage2;
	}else{
		l_expand.innerHTML = this.ExpandImage(0);
		if (this.array.Find('CloseImage') != null ) //������Զ��������ͼƬ����
			l_folder.innerHTML = this.array.Find('CloseImage');
		else //������ȱʡ������ͼƬ
			if (this.array.Find("cate_type") =="0")
				{l_folder.innerHTML = StrCloseImage2;}
			else
				{l_folder.innerHTML = StrFucntionImage;}
	}

	this.VLine();
}

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

//����OnClick�¼�
function tNodeOnClick()
{
	var elem = window.event.srcElement;
	var strNodeID;

	strNodeID=elem.id;
	SetDBFocus(strNodeID);
    if (strNodeID!="" && strNodeID!="2^undefined^�û����б�"&&strNodeID!="0^undefined^����/�û��б�"&&strNodeID!="1^undefined^�û��б�"&&strNodeID!="-1^undefined^��֯�ܹ�"){
      url="AddUserList.jsp?addtype=<%=request.getParameter("addtype")%>";
      url=url+"&amp;adduser="+strNodeID;
      url=URLEncoding(url);
      window.userlist.location=url;
    }
}

//����ڵ�ĵ������
function GetNewPage(strNodeID){
	//�õ��ڵ����
	var l_NodeValue,oNode;

	l_NodeValue = strNodeID.substr(0,strNodeID.length-6);

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


/*
function tNodeHideTable()
���ܣ�������һ�����ǰ��ļӺš����ŵ��¼�
���룺
�����
*/
function tNodeHideTable()
{
  var l_tb,l_dis,l_expand,l_folder;
  l_tb = document.all.item(this.nodeName + '_childrentable');
  l_dis = l_tb.style.display;
  l_expand = document.all.item(this.nodeName + '_expand');
  l_folder = document.all.item(this.nodeName + '_folder');
  if ( l_dis == 'none' )
  {
    this.ExpandNode();
    l_tb.style.display = '';
    l_expand.innerHTML = this.ExpandImage(1,0);
    l_folder.innerHTML = StrExpandImage2;
  }else{
    l_tb.style.display = 'none';
    l_expand.innerHTML = this.ExpandImage(0,0);
    if (this.array.Find("cate_type")=="0")
    {l_folder.innerHTML = StrCloseImage2;}
    else
    {l_folder.innerHTML = StrFucntionImage;}
  }
}

/*
function tNodeExpandImage(a_expand)
���ܣ��ж�һ������ǰ��Ӧ�÷��ĸ��Ӻš����ŵ�ͼƬ
���룺
	a_expand��������Ƿ�չ��״̬��1��չ����0������
�����
	Ӧ�÷ŵ�ͼƬ���ַ���
*/
function tNodeExpandImage(a_expand)
{
	//�Ӽ���ͼƬ
	if ( this.children.count > 0 ) //��Ҷ�ӽ��
	{
		if ( this.Layer() == 0 && this.BrotherCount() == 1 ) //��һ����ֻ��һ�����
			return (a_expand == 1) ? StrExpandImage : StrCloseImage;
		else if ( this.Index() == 0 && this.Layer() == 0 ) //��һ��ĵ�һ�����
			return (a_expand == 1) ? StrExpandImageTop : StrCloseImageTop;
		else if ( this.Index() == this.BrotherCount() - 1 ) //һ���е����һ�����
			return (a_expand == 1) ? StrExpandImageBottom : StrCloseImageBottom;
		else
			return (a_expand == 1) ? StrExpandImageLeft : StrCloseImageLeft; //һ��Ľ��
	}else{ //Ҷ�ӽ��
		if ( this.Index() == this.BrotherCount() - 1 ) //һ���е����һ�����
			return StrLeafImage1;
		else
			return StrLeafImage; //��һ���е����һ�����
	}
}

/*
function tNodeRenderTable()
���ܣ�����һ�����Ľ��棬����html�ַ���
���룺
�����
	������html�ַ���
*/
function tNodeRenderTable()
{
	var l_name,l_node,l_return = "";
	l_return += "<tr id='" + this.nodeName + "_tr'>\n";

	//��������
	l_node = this.paraNode;
	if ( l_node != null )
	{
		l_return += "<td id='" + this.nodeName + "_vline' style=\"width:18px;";
	if ( ! ( this.paraNode != null
			&& this.paraNode.Index() == ( this.paraNode.BrotherCount() -1 )
			)
		)
	{
		l_return += "background-position-x:4px;background-repeat:repeat-y;background-image:url("+StrBackground+");";
		l_return += "\">";
		l_return +="&nbsp;</td>\n";
	}
	else
	{
		l_return += "\">&nbsp;</td>\n";
	}
	}

	l_return += "<td style=\"width:4px\"></td>\n";

	l_return += "<td>\n";

	l_return += "<table border=0 cellspacing=0 cellpadding=0>";
	l_return += "<tr >";

	l_return += "<td style=\"width:0%\">";
	l_return += "<span id='" + this.nodeName + "_expand'";
	l_return += " onclick=\"javascript:oTree.Find('" + this.nodeName + "').HideTable();\"";

	//�Ӽ���ͼƬ
	if ( this.children.count > 0 ) //��Ҷ�ӽ��
	{
		l_return += " style=\"cursor:hand;width:18px\">";
	}else{ //Ҷ�ӽ��
		l_return += " style=\"width:18px\">";
	}
	l_return += this.ExpandImage(this.tree.ShowOnRender);
	l_return += "</span>";
	l_return += "</td >";

	l_return += "<td style=\"width:0%\">";

	//�ļ���ͼƬ
	l_return += "<span id='" + this.nodeName + "_folder'>";
	if (this.array.Find('cate_type')==0)
	{	l_return += StrCloseImage2;}
	else
	{	l_return += StrFucntionImage;}
	l_return += "</span>";

	l_return += "</td>";
	l_return += "<td align=left>";

	//���������
	l_return += "<div nodeName=\"" + this.nodeName + "\"";
	l_return += " onmousedownex=\"javascript:oTree.Find('" + this.nodeName + "').onmousedownex();\"";
	l_return += " onmouseupex=\"javascript:oTree.Find('" + this.nodeName + "').onmouseupex();\"";
	l_return += " id='" + this.nodeName + "_Move'";
	l_return += " class=moveme style=\"position:relative;\">";
	l_return += "<input id='" + this.nodeName+"^"+this.array.Find('cate_type')+"^"+this.array.Find('cate_desc') + "' type=text readonly style=\"height:13px;cursor:hand;border:0\"";
	l_return += " onclick=\"javascript:oTree.Find('" + this.nodeName + "').OnClick();\"";
	l_return += " oncontextmenu=\"javascript:oTree.Find('" + this.nodeName + "').OnContextMenu()\"";
	l_return += " class=\"node\"";
	l_return += " value=\"";
	l_return += this.array.Find('cate_desc');
	l_return += "\"></input>";
	l_return += "</div>";

	l_return += "</td>";

	l_return += "</tr>";

	//�ӷ����table
	l_return += "<tr>";

	l_return += "<td colspan=3>";
	l_return += "<table border=0 cellspacing=0 cellpadding=0 width=\"100%\"";
	if ( this.tree.ShowOnRender == 0 )
		l_return += " style=\"display:none\"";
	l_return += " id='" + this.nodeName + "_childrentable'>\n";
    if(this.tree.ShowOnRender==1 && this.Layer()==0){
      for ( l_name in this.children.nodes )
      {
        l_node = this.children.nodes[l_name];
        l_return += l_node.RenderTable();
      }
    }
	l_return += "</table>\n";
	l_return += "</td>";
	l_return += "</tr>";
	l_return += "</table>";
	//����
	l_return += "</td>\n";
	l_return += "</tr>\n";
	return l_return;
}
/**
 * �����ӽڵ�
 * @return
 */
function tExpandNode(){
  var l_return = "";
  var l_ctbl = document.all.item(this.nodeName + '_childrentable');
  if(!this.isRender){
    l_return += "<table border=0 cellspacing=0 cellpadding=0 width=\"100%\"";
    l_return += " id='" + this.nodeName + "_childrentable'>\n";

    for ( l_name in this.children.nodes )
    {
            l_node = this.children.nodes[l_name];
            l_return += l_node.RenderTable();
    }

    l_return += "</table>\n";

    l_ctbl.outerHTML = l_return;
    l_ctbl.style.display = '';
    this.isRender = true;
  }
}
//--����-------------------------------------------------------------

function tTree() //��������
{
	this.nodes = new tArray(); //���Ľ�㼯��
	this.count = tTreeCount; //���Ľ�����
	this.Add = tAddNode; //����һ�����ķ���
	this.Find = tFindNode; //���ݴ����ҵ�һ�����ķ���
	this.Remove = tRemoveNode; //ɾ��һ�����ķ���
	this.Update = tUpdateNode; //����һ�����ķ���
	this.toString = tTreetoString; //����Debugʱ������������Ϣ�ķ���

//�������ͨ�õģ��������Ϊ��ʵ��������ʾ��д��
	this.ShowOnRender = 0; //ȱʡ���Ŀ�ʼ״̬�ǲ�չ����
	this.RenderTable = tRenderTable;
	this.AdjustPic = tAdjustPic;
	this.UpdateEx = tUpdateNodeEx;
	this.ExpandNode = tExpandNode;
}

function tUpdateNodeEx(a_nodeName,a_paraName,a_ary)
{
	var l_tAry = new tArray(), l_s;
	for ( l_s in a_ary )
	{
		l_tAry.Add( l_s, a_ary[l_s] );
	}
	this.Update(a_nodeName,a_paraName,l_tAry);
}

function tAdjustPic()
{
	var l_node;
	for ( l_node in this.nodes.nodes )
	{
		this.nodes.Find(l_node).AdjustPic();
	}
}

/*
function tRenderTable(a_ShowOnRender)
���ܣ�����һ�����Ľ��棬����html�ַ���
���룺
	a_ShowOnRender���Ƿ�չ����������1��չ����0������
�����
	������html�ַ���
*/
function tRenderTable(a_ShowOnRender)
{
	var l_name,l_node,l_return = "";

	this.ShowOnRender = a_ShowOnRender;

	l_return += "<table ID=oTable border=0 cellspacing=0 cellpadding=0>\n";
	for ( l_name in this.nodes.nodes )
	{
		l_node = this.nodes.nodes[l_name];
		if ( l_node.paraNode != null )
			continue;
		l_return += l_node.RenderTable();
	}
	l_return += "</table>\n";
	return l_return;
}


//==������� Ϊ��ʵ��������ʾ������ģ�Ͷ�������ʵ�������Ĵ���

//-->
</script>


<script type="text/javascript">
<!--
var oTree,ifExpandTree = 1;
oTree = new tTree();
<%=m_sMenuString%>

function window_onload()
{
	var oNode;
//	ContextMenu.intializeContextMenu(); //��ʼ���Ҽ��˵���ֻ��Ҫ��ҳ��onload��ʱ�����һ��
	ShowTree();
	DivResize();

	//չ����
	oNode = oTree.Find('-1');
	if (oNode!=null){
		oNode.HideTable();
	}
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
<SCRIPT type="text/VBScript">
Function URLEncoding(vstrIn)
  strReturn = ""
  For t = 1 To Len(vstrIn)
  ThisChr = Mid(vStrIn,t,1)
  If Abs(Asc(ThisChr)) < &HFF Then
  strReturn = strReturn & ThisChr
  Else
  innerCode = Asc(ThisChr)
  If innerCode < 0 Then
  innerCode = innerCode + &H10000
  End If
  Hight8 = (innerCode And &HFF00)\ &HFF
  Low8 = innerCode And &HFF
  strReturn = strReturn & "%" & Hex(Hight8) & "%" & Hex(Low8)
  End If
  Next
  URLEncoding = strReturn
  End Function
</script>
<link rel="STYLESHEET" type="text/css" href="../include/Public.css">

<body leftmargin="0" topmargin="0">
<table border="1" height="100%" width=100%>
<tr>
	<td height="100%" width=30% valign="top">
          <div id="divDebug"></div>
          <div id="divRender" style="width:230;overflow-x:auto;overflow-y:auto;"></div>
	</td>
        <td valign="top" width=70%>
          <iframe name="userlist" FRAMEBORDER=1 width=100% height=100% src="AddUserList.jsp">
          </iframe>
        </td>
</tr>
</table>

</body>
</html>


