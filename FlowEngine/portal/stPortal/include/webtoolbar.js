////////////////////////////////////////////////////////////////////////////////////
////����������windows��񹤾���
////This Program generate windows style toolbar
////����:������
////Author:Dickhome
////Modify:2001-11-11
////ʹ���÷���:1.�ڵ���ҳ������Ŀ¼����������Ŀ¼CSS��WebToolBar
////		   2.CSS�з���toolbar.css�ļ���WebToolBar����webtoolbar.js(���ļ�)
////           3.�ڵ���ҳ����AddToolBarItem���밴Ť����GenToolBarV(ͼƬ�ı����½ṹ)
////			 ��GenToolBar(ͼƬ�ı����ҽṹ)	�������蹤��������
////		   4.����ͨ����ʾΪpublic�ĺ������ù��������ԡ�
////////////////////////////////////////////////////////////////////////////////////

var toolbarImgNormal  = new Array()//��������״̬��ͼƬ����
var toolbarImgOver	  = new Array()//��������ƶ�״̬��ͼƬ����
var toolbarImgDown    = new Array()//������갴��״̬��ͼƬ����

var toolbarText = new Array()//���水Ť��������
var toolbarWidth  = new Array()//���水Ť�������
var toolbarSplit  = new Array()//���水Ťǰ���Ƿ���ָ�������

var toolbarAction  = new Array()//���水Ť������ʱ����������
var toolbarName	   = new Array()//���水Ť������

var toolbarCount=0      //��Ť����

var toolbarHeight =22   //�߶�----�ⲿ���������
var toolbarHandle = true//������ǰ���Ƿ���Ҫ�ѱ�-------�ⲿ���������

//���ù������߶�
//lHeight:�߶�
//public
function SetToolBarHeight(lHeight)
{
	toolbarHeight=lHeight
}

//�����Ƿ��аѱ�
//lFlag=true(��),false(û��)
//public
function SetToolBarHandle(lFlag)
{
	toolbarHandle = lFlag
}
//����һ����Ť
//sImgxxxx,ͼƬ��·��
//plblic
function AddToolBarItem(sImgNormal,sImgOver,sImgDown,sText,sWidth,sSplit,sAction)
{
	toolbarImgNormal[toolbarCount]=sImgNormal
	toolbarImgOver[toolbarCount]=sImgOver
	toolbarImgDown[toolbarCount]=sImgDown



	toolbarText[toolbarCount] = sText
	toolbarWidth[toolbarCount] = sWidth
	toolbarSplit[toolbarCount] = sSplit

	toolbarAction[toolbarCount] = sAction

	toolbarName[toolbarCount] = "Tool"+toolbarCount //�˷���û��ָ�����Ʋ���,��������һ������

	toolbarCount=toolbarCount+1

}

//����һ����Ť,�˷�����AddToolBarItem���ƣ�����һ������,ָ���ð�Ť������
//sImgxxxx,ͼƬ��·��
//plblic
function AddToolBarItemEx(sName,sImgNormal,sImgOver,sImgDown,sText,sWidth,sSplit,sAction)
{
	toolbarImgNormal[toolbarCount]=sImgNormal
	toolbarImgOver[toolbarCount]=sImgOver
	toolbarImgDown[toolbarCount]=sImgDown



	toolbarText[toolbarCount] = sText
	toolbarWidth[toolbarCount] = sWidth
	toolbarSplit[toolbarCount] = sSplit

	toolbarAction[toolbarCount] = sAction

	toolbarName[toolbarCount] = sName


	toolbarCount=toolbarCount+1

}

//ȡ�ù�������Html����,ͼƬ���ִ�ֱ��ʽ
//public
function GenToolBarV()
{
	//alert(toolbarCount)

	sBarPad = "<TABLE bgColor=#d4d0c8 border=0 cellPadding=0 cellSpacing=0 style=\"BORDER-BOTTOM: #808080 1px solid; BORDER-LEFT: #ffffff 1px solid; BORDER-RIGHT: #808080 1px solid; BORDER-TOP: #ffffff 1px solid\"  width=\"100%\"><TBODY><TR>"
	if (toolbarHandle)
	{
		sBarPad =sBarPad + GenHandle()
	}
	sBarPad += "<TD><TABLE border=0 cellPadding=0 cellSpacing=0><TR><TD noWrap width=4></TD>"

	for (i=0;i<toolbarCount;i++)
	{
		sBarPad += GenTool(i,true)
	}


	sBarPad =sBarPad + "</TR></TBODY></TABLE>"
	//alert(sBarPad)
	return sBarPad

}

//ȡ�ù�������Html����,ͼƬ����ˮƽ��ʽ
//public
function GenToolBar()
{
	//alert(toolbarCount)

	sBarPad = "<TABLE bgColor=#d4d0c8 border=0 cellPadding=0 cellSpacing=0 style=\"BORDER-BOTTOM: #808080 1px solid; BORDER-LEFT: #ffffff 1px solid; BORDER-RIGHT: #808080 1px solid; BORDER-TOP: #ffffff 1px solid\"  width=\"100%\"><TBODY><TR>"
	if (toolbarHandle)
	{
		sBarPad =sBarPad + GenHandle()
	}
	sBarPad += "<TD><TABLE border=0 cellPadding=0 cellSpacing=0><TR><TD noWrap width=4></TD>"

	for (i=0;i<toolbarCount;i++)
	{
		sBarPad += GenTool(i,false)
	}


	sBarPad =sBarPad + "</TR></TBODY></TABLE>"
	//alert(sBarPad)
	return sBarPad

}

//����ָ�������İ�Ť�Ƿ�check
//index:0��ʼ
//flag:true:check
//pulbic
function SetCheck(sName,flag)
{
	if(document.all.item(sName)!=null)
	{
		if (flag)
			document.all.item(sName).className="check"
		else
			document.all.item(sName).className="out"
	}
	else
	{

		alert("ָ���İ�Ť���Ʋ�����()");
	}
}



//���ɰѱ�
//private
function GenHandle()
{
	var sHandle=""
	if (toolbarHandle)
	{
		sHandle ="<TD noWrap width=10>"
        sHandle +="<TABLE border=0 cellPadding=0 cellSpacing=0 height=" + toolbarHeight
        sHandle +=  " style=\"BORDER-BOTTOM: #808080 1px solid; MARGIN-BOTTOM: 2px; MARGIN-LEFT: 4px; MARGIN-TOP: 2px\" width=3>"
        sHandle +=  "<TBODY>"
		sHandle +=	  "<TR>"
        sHandle +=      "<TD bgColor=#ffffff width=1>��</TD>"
        sHandle +=      "<TD bgColor=#d4d0c8 width=1>��</TD>"
        sHandle +=		"<TD bgColor=#808080 width=1>��</TD>"
        sHandle +=	   "</TR>"
        sHandle +=  "</TBODY>"
        sHandle +="</TABLE>"
		sHandle +="</TD>"
	}
	return sHandle
}

//���ɷָ���
//private
function GenSplit()
{
		var sSplit
		sSplit = "<TD noWrap width=10>"
        sSplit += "<DIV align=center>"
        sSplit += "<TABLE border=0 cellPadding=0 cellSpacing=0 height=" + toolbarHeight
        sSplit += " style=\"MARGIN-BOTTOM: 2px; MARGIN-TOP: 2px\">"
        sSplit += " <TBODY>"
        sSplit += " <TR>"
        sSplit += "<TD bgColor=#808080 width=1>��</TD>"
        sSplit += "<TD bgColor=#ffffff width=1>��</TD>"
        sSplit += "</TR>"
        sSplit += "</TBODY>"
        sSplit += "</TABLE>"
        sSplit += "</DIV>"
        sSplit += "</TD>"
        return sSplit
}

//����һ����Ť
//index,��Ť����
//vertical,ͼƬ�����Ƿ�ֱ
//private
function GenTool(index,vertical)
{
	var sTool
	var sOnClick
	var sOnMouseDown
	var sOnMouseOut
	var sOnMouseOver
	var sOnMouseUp
	var sWidth
	var sTmp
	var sImg="Img"+index
//	var sTool="Tool"+index
	sOnClick = " onclick=\"javascript:" + toolbarAction[index] + ";\" "
	//sOnClick = " onclick=\"javascript:funHello();\" "
	//sOnClick = "onclick=\"addPad('default')\" "
	sOnMouseDown = " onmousedown=\"OnDown(this)\" "
	sOnMouseOut = " onmouseout=\"OnOut(this),document.all."+sImg+".src='"+ toolbarImgNormal[index]+"'\" "
	if (toolbarImgOver[index]!='')
	{
		sTmp= toolbarImgOver[index]
	}else
	{
		sTmp= toolbarImgNormal[index]
	}

	sOnMouseOver=  " onmouseover=\"OnOver(this),document.all."+sImg+".src='"+ sTmp +"'\" "

	sOnMouseUp=  " onmouseup=\"this.className='over',document.all."+sImg+".src='"+ toolbarImgNormal[index]+"'\" "
	sWidth	  =" width='" + toolbarWidth[index] +"'"
	sHeight   =  toolbarHeight
	if (sHeight<10)
	{
		sHeight = 10
	}
	sHeight = " height='" +sHeight  +"' "
	sTool = "<TD><TABLE  border=0 cellPadding=0 cellSpacing=0 id="+toolbarName[index]

	sTool += sOnClick
	sTool += sOnMouseDown
	sTool += sOnMouseOut
	sTool += sOnMouseOver
	sTool += sOnMouseUp
	sTool += sWidth + sHeight
	sTool += "><TBODY><TR><TD><DIV align=center>"
	sTool += "<TABLE border=0 cellPadding=0 cellSpacing=0>"
	if (!vertical)
	{
		sTool += "<TBODY><TR> <TD>"
		sTool += " <P style=\"MARGIN-RIGHT: 2px\"><IMG border=0 "
		sTool += " height=16 id="+sImg+"  src=\""
		sTool +=  toolbarImgNormal[index] + "\" width=16>"
		sTool += "</P></TD>"
		sTool += "<TD><P style=\"MARGIN-RIGHT: 5px; MARGIN-TOP: 2px;\">"
		sTool += toolbarText[i]
		sTool += "</P></TD></TR></TBODY></TABLE></DIV></TD></TR></TBODY></TABLE></TD>"
    }else
    {
		sTool += "<TBODY><TR> <TD align=center>"
		sTool += " <P style=\"MARGIN-RIGHT: 2px\"><IMG border=0 "
		sTool += " height=16 id="+sImg+"  src=\""
		sTool +=  toolbarImgNormal[index] + "\" width=16>"
		sTool += "</P></TD>"
		sTool += "<TR><TD align=center><P style=\"MARGIN-RIGHT: 5px; MARGIN-TOP: 2px;\">"
		sTool += toolbarText[i]
		sTool += "</P></TD><TR></TR></TBODY></TABLE></DIV></TD></TR></TBODY></TABLE></TD>"
    }


    if (toolbarSplit[index]=="1")
    {
		sTool = GenSplit() +sTool
    }
    return sTool
}


function OnOver(obj)
{

	if (obj.className!='check')
				obj.className='over'

}

function OnOut(obj)
{

	if (obj.className!='check')
				obj.className='out'
}

function OnDown(obj)
{

	if (obj.className!='check')
				obj.className='down'
}



