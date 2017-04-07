//==���￪ʼ Ϊ��ʵ��������ʾ������ģ�Ͷ�������ʵ�������Ĵ���

//ͼƬ·������
var StrLeafImage = "<img src=\"./Tree/images/line.gif\" border=0>";
var StrLeafImage1 = "<img src=\"./Tree/images/line1.gif\" border=0>";
var StrEmptyImage = "<img src=\"./Tree/images/dot.gif\" border=0 style=\"width:15px\">";

var StrCloseImage = "<img src=\"./Tree/images/add.gif\" border=\"0\">";
var StrExpandImage = "<img src=\"./Tree/images/sub.gif\" border=\"0\">";

var StrCloseImageTop = "<img src=\"./Tree/images/addtop.gif\" border=\"0\">";
var StrExpandImageTop = "<img src=\"./Tree/images/plustop.gif\" border=\"0\">";
var StrCloseImageBottom = "<img src=\"./Tree/images/addbottom.gif\" border=\"0\">";
var StrExpandImageBottom = "<img src=\"./Tree/images/plusbottom.gif\" border=\"0\">";
var StrCloseImageLeft = "<img src=\"./Tree/images/addleft.gif\" border=\"0\">";
var StrExpandImageLeft = "<img src=\"./Tree/images/plusleft.gif\" border=\"0\">";

var StrExpandImage2 = "<img src=\"./Tree/images/open.gif\" border=\"0\">";
var StrCloseImage2 = "<img src=\"./Tree/images/close.gif\" border=\"0\">";
var strReportImage="<img src=\"./Tree/images/report.gif\" border=\"0\">";

//��ǰ�ڵ��ֵ
var StrLastNode="";

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
			l_folder.innerHTML = '<img src="' + this.array.Find('ExpandImage') + '" border=0>';
		else //������ȱʡ��չ��ͼƬ
			l_folder.innerHTML = StrExpandImage2;
	}else{
		l_tb.style.display = 'none';
		l_expand.innerHTML = this.ExpandImage(0);
		if (this.array.Find('CloseImage') != null ) //������Զ��������ͼƬ����
			l_folder.innerHTML = '<img src="' + this.array.Find('CloseImage') + '" border=0>';
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
	l_return += "<tr>\n";

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
		l_return += "background-position-x:4px;background-repeat:repeat-y;background-image:url(../common/tree/images/line-bg.GIF);";
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

	l_return += "<td style=\"width:0%\">";

	//�ļ���ͼƬ
	l_return += "<span id='" + this.nodeName + "_folder'>";
	if(this.array.Find("cate_type")==0){
		if ( this.tree.ShowOnRender == 1 && this.children.count > 0)
			if (this.array.Find('ExpandImage') != null ) //������Զ����չ��ͼƬ����
				l_return += '<img src="' + this.array.Find('ExpandImage') + '" border=0>';
			else //������ȱʡ��չ��ͼƬ
				l_return += StrExpandImage2;
		else
			if (this.array.Find('CloseImage') != null ) //������Զ��������ͼƬ����
				l_return +=  '<img src="' + this.array.Find('CloseImage') + '" border=0>';
			else //������ȱʡ������ͼƬ
				l_return += StrCloseImage2;
	}
	else{
		l_return +=strReportImage;
	}
	l_return += "</span>";

	l_return += "</td>";
	l_return += "<td align=left>";

	//���������
	l_return += "<input type=text id=" + this.nodeName + " class=\"TreeNode\" readonly "
	l_return += "style=\"background-color:transparent;border:0;height:17px;cursor:hand\"";
	l_return += " onclick=\"javascript:oTree.Find('" + this.nodeName + "').OnClick();\"";
	l_return += " oncontextmenu=\"javascript:oTree.Find('" + this.nodeName + "').OnContextMenu()\"";
	l_return += " value=\"";
	l_return += this.array.Find('cate_desc');
	l_return += "\"></input>";

	l_return += "</td>";

	l_return += "</tr>";

	//�ӷ����table
	l_return += "<tr>";

	l_return += "<td colspan=3>";
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

////////////////////////////////////////////////////////////////////////////////
// ����Ĵ�����Ϊ����ʾ������ Treeview
var j;
var xt;
var leftcolInt;

/*
	OnTreeViewButtonClick����ʾ������ Treeview �˵�
*/

function OnTreeViewButtonClick()
{

	j = 0;
	if (document.all.item("divLeftMenu").offsetWidth == 0)
	{	//to right
		document.all.item("treeviewbutton").src = "../common/tree/images/hidetree.gif";
		document.all.item("treeviewbutton").title = L_TreeViewHide_Text;
		TreeView_GoRight();
	}
	else
	{	//to left

		leftcolInt = document.all.item("divLeftMenu").offsetWidth
		xt = leftcolInt;
		document.all.item("treeviewbutton").src = "../common/tree/images/showtree.gif";
		document.all.item("treeviewbutton").title = L_TreeViewShow_Text;
		TreeView_GoLeft();
	}
}

function TreeView_GoRight()
{
   		xt = xt + 20 ;
    	if (xt < leftcolInt ){
		   	document.all.item("divLeftMenu").style.pixelWidth = xt;
			setTimeout('TreeView_GoRight()',10);
		}
		else
		{
			document.all.item("divLeftMenu").style.pixelWidth = leftcolInt;
		}
	}

function TreeView_GoLeft()
{
	xt = xt - 20 ;
    if (xt > -20)
    {
		if (xt < 0) { xt =0; }

		document.all.item("divLeftMenu").style.pixelWidth = xt;
		setTimeout('TreeView_GoLeft()',10);
	}
}

// Click
function tNodeOnClick()
{
	var deptseq
	if( StrLastNode != "" )
		document.all.item(StrLastNode).className = "TreeNode";
	StrLastNode=this.nodeName;
	document.all.item(StrLastNode).className = "TreeNodeSelected";
	//m_DetailBoardID = this.nodeName;
	//m_DetailBoardType= this.array.Find("cate_type");
	deptseq = this.array.Find("cate_value");

	//document.all.ifrmDashBoardContent.src = "DashboardContent.asp?DashboardID=" + m_DetailBoardID + "&DashboardType=" + m_DetailBoardType;
	//alert(document.all.userlist.src)
	//document.all.userlist.src="userlist.asp?deptseq="+deptseq
	OnTreeNodeClick(deptseq)

}
//OnContextMenu
function tNodeOnContextMenu()
{


}
