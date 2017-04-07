<link rel="STYLESHEET" type="text/css" href="css/WebFX-ContextMenu.css">
<SCRIPT type="text/javascript" src="ContextMenu.js"></SCRIPT>
<%
//�ļ�tTree.js���й���ģ�Ͷ����һЩ���õ�ǰ̨����
%>
<SCRIPT type="text/javascript" src="tTree.js"></SCRIPT>
<script type="text/javascript">
<!--
//==���￪ʼ Ϊ��ʵ��������ʾ������ģ�Ͷ�������ʵ�������Ĵ���

//ͼƬ·������
var StrLeafImage = "<img src=\"images/line.gif\" border=0>";
var StrLeafImage1 = "<img src=\"images/line1.gif\" border=0>";
var StrEmptyImage = "<img src=\"images/dot.gif\" border=0 style=\"width:15px\">";

var StrCloseImage = "<img src=\"images/add.gif\" border=\"0\">";
var StrExpandImage = "<img src=\"images/sub.gif\" border=\"0\">";

var StrCloseImageTop = "<img src=\"images/top.gif\" border=\"0\">";
var StrExpandImageTop = "<img src=\"images/-top.gif\" border=\"0\">";
var StrCloseImageBottom = "<img src=\"images/bottom.gif\" border=\"0\">";
var StrExpandImageBottom = "<img src=\"images/-bottom.gif\" border=\"0\">";
var StrCloseImageLeft = "<img src=\"images/left.gif\" border=\"0\">";
var StrExpandImageLeft = "<img src=\"images/-left.gif\" border=\"0\">";

var StrExpandImage2 = "<img src=\"images/open.gif\" border=\"0\"><span style=\"width:5px\"></span>";
var StrCloseImage2 = "<img src=\"images/close.gif\" border=\"0\"><span style=\"width:5px\"></span>";


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
	this.OnClick = tNodeOnClick;
	this.OnContextMenu = tNodeOnContextMenu;
}

//�����Ҽ��˵��¼�
function tNodeOnContextMenu()
{
   var popupoptions
   popupoptions = [
   						new ContextItem("ˢ�±�ҳ",function(){window.location.reload();}),
						new ContextItem("Disabled Item",null,true),
						new ContextSeperator(),
						new ContextItem("��ӡ",function(){window.print()}),
						new ContextItem("�鿴������",function(){tNodeOnClick();document.body.focus();}),
						new ContextSeperator(),
   						new ContextItem("����",function(){alert('����');document.body.focus();})
   				  ]
   ContextMenu.display(popupoptions)
}

//����OnClick�¼�
function tNodeOnClick()
{
	alert('��ã��ҵĴ����� ' + this.nodeName + '��\nף����� :)');
	self.status = "hello";
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
		l_tb.style.display = '';
		l_expand.innerHTML = this.ExpandImage(1);
		if (this.array.Find('ExpandImage') != null ) //������Զ����չ��ͼƬ����
			l_folder.innerHTML = this.array.Find('ExpandImage');
		else //������ȱʡ��չ��ͼƬ
			l_folder.innerHTML = StrExpandImage2;
	}else{
		l_tb.style.display = 'none';
		l_expand.innerHTML = this.ExpandImage(0);
		if (this.array.Find('CloseImage') != null ) //������Զ��������ͼƬ����
			l_folder.innerHTML = this.array.Find('CloseImage');
		else //������ȱʡ������ͼƬ
			l_folder.innerHTML = StrCloseImage2;
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
		if ( this.BrotherCount() == 1 ) //һ����ֻ��һ�����
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
	l_return += "<tr>\n";

	//��������
	l_node = this.paraNode;
	if ( l_node != null )
	{
		l_return += "<td style=\"width:18px;";
		if ( !( l_node.Layer() == 0 && l_node.Index() == (l_node.BrotherCount() - 1) ) )
		{
			l_return += "background-position-x:4px;background-repeat:repeat-y;background-image:url(images/line-bg.gif);";
		}
		l_return += "\"></td>\n";
	}

	l_return += "<td style=\"width:4px\"></td>\n";

	l_return += "<td>\n";

	l_return += "<table border=0 cellspacing=0 cellpadding=0>";
	l_return += "<tr>";

	l_return += "<td style=\"width:0%\">";
	l_return += "<span";

	//�Ӽ���ͼƬ
	if ( this.children.count > 0 ) //��Ҷ�ӽ��
	{
		l_return += " id='" + this.nodeName + "_expand' style=\"cursor:hand;width:18px\"";
		l_return += " onclick=\"javascript:oTree.Find('" + this.nodeName + "').HideTable();\">";
		l_return += this.ExpandImage(this.tree.ShowOnRender);
	}else{ //Ҷ�ӽ��
		l_return += " style=\"width:18px\">";
		l_return += this.ExpandImage(this.tree.ShowOnRender);
	}
	l_return += "</span>";
	l_return += "</td>";

	l_return += "<td>";

	//�ļ���ͼƬ
	l_return += "<span id='" + this.nodeName + "_folder'>";
	l_return += StrCloseImage2;
	l_return += "</span>";

	//���������
	l_return += "<a href=\"#\"";
	l_return += " onclick=\"javascript:oTree.Find('" + this.nodeName + "').OnClick();\"";
	l_return += " oncontextmenu=\"javascript:oTree.Find('" + this.nodeName + "').OnContextMenu()\"";
	l_return += ">";
	l_return += this.array.Find('cate_desc');
	l_return += "</a>";

	l_return += "</td>";

	l_return += "</tr>";

	//�ӷ����table
	l_return += "<tr>";

	l_return += "<td colspan=2>";
	l_return += "<table border=0 cellspacing=0 cellpadding=0 width=\"100%\"";
	if ( this.tree.ShowOnRender == 0 )
		l_return += " style=\"display:none\"";
	l_return += " id='" + this.nodeName + "_childrentable'>\n";

	for ( l_name in this.children.nodes )
	{
		l_node = this.children.nodes[l_name];
		l_return += l_node.RenderTable();
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

	l_return += "<table border=0 cellspacing=0 cellpadding=0>\n";
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

<SCRIPT type="text/javascript">
<!--
var oTree,ifExpandTree = 1;
oTree = new tTree();
<%
  String m_sMenuString = "oArray = new tArray(); oArray.Add('cate_desc','��ҵ��Ϣ'); oArray.Add('cate_value','0012'); oTree.Add('0012','0',oArray); oArray = new tArray(); oArray.Add('cate_desc','�ƶ���֪'); oArray.Add('cate_value','00120001'); oTree.Add('00120001','0012',oArray); oArray = new tArray(); oArray.Add('cate_desc','��ҵ��̬'); oArray.Add('cate_value','00120002'); oTree.Add('00120002','0012',oArray); oArray = new tArray(); oArray.Add('cate_desc','��˾��Ϣ'); oArray.Add('cate_value','00120003'); oTree.Add('00120003','0012',oArray);";
%>
<%=m_sMenuString%>

function window_onload()
{
	ContextMenu.intializeContextMenu(); //��ʼ���Ҽ��˵���ֻ��Ҫ��ҳ��onload��ʱ�����һ��
	ShowTree();
}

function ShowTree()
{
//	document.all.item('divDebug').innerText = oTree.toString();
	ifExpandTree = ( ifExpandTree == 1 ) ? 0 : 1; //�л��Ƿ�չ�����н��ı�־
	document.all.item('divRender').innerHTML = oTree.RenderTable(ifExpandTree);
}

window.attachEvent("onload",window_onload);
//-->
</SCRIPT>
<body leftmargin="0" topmargin="0">
<a href="#" onclick="javascript:ShowTree();">�������ǵ�����</a>
<br>
<br>
<div id=divDebug></div>
<div id=divRender></div>
</body>
</html>
