var treeHtml="";                                       //����˵�����html
var arrTree=new Array();                               //�˵������нڵ���ɵ�����
var treeNodeIDs="";                                    //�˵������нڵ�ID�ԡ������ָ�����ɵ��ַ���
var treeBlankWidth=16;                                 //��һ���ڵ�����һ���ڵ�֮�����������Ŀ��
var treeImageWidth=16;                                 //չ�����۵���ʾͼƬ�Ŀ��
var treeExpandImage="/stPortal/images/tree_arrow_show.gif";      //չ����ʾͼƬ
var treeCloseImage="/stPortal/images/tree_arrow_hide.gif";       //�۵���ʾͼƬ
var treeLayerFlag=1;                                   //�˵�����ǰ���ʾ
var treeSelectedTd="";                                 //��־�˵�����ǰ��ѡ�еĽڵ�
var treeIfExpand=1;                                    //��treeIfExpand=1ʱ���˵����ڵ�չ������treeIfExpand=0ʱ���˵����ڵ��۵�


/************************/
/*���ܣ����ɲ˵���*/
/*������*/
/*   aDivName��ָ���˵�������λ�õ�div����*/
/*aExpandFlag����aExpandFlag=1ʱ���˵����ڵ�չ������aExpandFlag=0ʱ���˵����ڵ��۵�*/
/************************/
function initTree(aDivName,aExpandFlag){
  treeIfExpand=aExpandFlag;
  if(treeNodeIDs!=null && treeNodeIDs!=""){
    var arrTemp=treeNodeIDs.split(";");
    for(i=0;i<arrTemp.length-1;i++){
      var strIndex=arrTemp[i];
      if(arrTree[strIndex]!=null && arrTree[strIndex]["pid"]==""){
        createTree(arrTree[strIndex],1);
      }
    }
    treeHtml="<table id=\"treeTable\" name=\"treeTable\" width=\"160\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">"+treeHtml+"</table>";
    document.all.item(aDivName).innerHTML=treeHtml;
  }
}
/************************/
/*���ܣ�����˵������飬�ݴ���ȫ�ֱ���arrTree��*/
/*������*/
/*       aID���ڵ�ID*/
/*      aPID�����ڵ�ID*/
/*     aDesc���ڵ�����*/
/*aClickFunc������ڵ���ɵĲ�������ȡֵ����ʱ��Ĭ��nodeClick()������ȡֵ���磺��Test();��*/
function addNode(aID,aPID,aDesc,aClickFunc){
  if(aID==null || aID=="")
    return;
  if(aPID!=null && aPID!=""){
    if(arrTree[aPID]==null)
      arrTree[aID]=null;
    else{
      var temp=arrTree[aPID]["children"];
      if(temp=="")
        arrTree[aPID]["children"]=aID;
      else
        arrTree[aPID]["children"]=temp+";"+aID;
    }
  }else{
    aPID="";
  }
  var arrNode=new Array();
  arrNode["id"]=aID;
  arrNode["pid"]=aPID;
  arrNode["desc"]=aDesc;
  var clickFunc="nodeClick();";
  if(aClickFunc!=null && aClickFunc!="")
    clickFunc=aClickFunc
  arrNode["clickfunc"]=clickFunc;
  arrNode["children"]="";
  arrTree[aID]=arrNode;
  treeNodeIDs=treeNodeIDs+aID+";";
}
/************************/
/*���ܣ��������ڵ��html���ݴ���ȫ�ֱ���treeHtml��*/
/*������*/
/* aNode���ڵ�����*/
/*aIndex���ڵ��Σ����ڵ�Ϊ1�����ε���*/
/************************/
function createTree(aNode,aIndex){
  var strStyle=" style=\"display:block;\"";
  if(treeIfExpand==1)
    strStyle=" style=\"display:block;\"";
  else
    strStyle=" style=\"display:none;\"";
  var tableHead="<tr id=\""+aNode["pid"]+"_children\" name=\""+aNode["pid"]+"_children\""+strStyle+"><td><table id=\""+aNode["pid"]+"_table\" name=\""+aNode["pid"]+"_table\" width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">";
  var tableTail="</table></td></tr>";
  if(treeLayerFlag==aIndex)
    treeHtml=treeHtml+getNodeHtml(aNode,aIndex);
  else{
    if(treeLayerFlag>aIndex){
      var tempTail="";
      while(treeLayerFlag-1>=aIndex){
        tempTail=tempTail+tableTail
        treeLayerFlag=treeLayerFlag-1;
      }
      treeHtml=treeHtml+tempTail+getNodeHtml(aNode,aIndex);
      treeLayerFlag=aIndex;
    }else{
      treeHtml=treeHtml+tableHead+getNodeHtml(aNode,aIndex);
      treeLayerFlag=aIndex;
    }
  }
  if(aNode["children"]!=""){
    var arrTemp = aNode["children"].split(";");
    var tempIndex=0;
    while(tempIndex<arrTemp.length){
      var tempNode=arrTree[arrTemp[tempIndex]];
      tempIndex=tempIndex+1;
      createTree(tempNode,aIndex+1);
    }
  }
}
/************************/
/*���ܣ�����createTree*/
/************************/
function getNodeHtml(aNode,aIndex){
  var tempID=aNode["id"];
  var tempPID=aNode["pid"];
  var breakHtml="<tr id=\""+tempID+"_break\" name=\""+tempID+"_break\" nodeID=\""+tempID+"\"><td width=\"100%\" class=\"breakL1\"></td></tr>";
  var imageHtml="";
  var tempBreak;
  var tempHtml;
  var hasChildren=false;

  if(aNode["children"]!=""){
    hasChildren=true;
    tempBreak=treeBlankWidth*aIndex;
    var tempImage=treeExpandImage;
    var tempExpand=1;
    if(treeIfExpand==1){
      tempImage=treeExpandImage;
      tempExpand=1;
    }else{
      tempImage=treeCloseImage;
      tempExpand=0;
    }
    imageHtml="<img id=\""+tempID+"_img\" name=\""+tempID+"_img\" nodeID=\""+tempID+"\" nodePID=\""+tempPID+"\" level=\""+aIndex+"\" expandFlag=\""+tempExpand+"\" src=\""+tempImage+"\" border=\"0\" style=\"cursor:hand;\">";
  }else{
    tempBreak=treeBlankWidth*aIndex+treeImageWidth;
    imageHtml="";
  }
  var trHtml="";
  if(!hasChildren)
  	trHtml="<tr onclick=\"javascript:selectNodeAndExpandNode(false);\" id=\""+tempID+"_tr\" name=\""+tempID+"_tr\" nodeID=\""+tempID+"\" nodePID=\""+tempPID+"\" level=\""+aIndex+"\"><td id=\""+tempID+"_td\" name=\""+tempID+"_td\" nodeID=\""+tempID+"\" nodePID=\""+tempPID+"\" level=\""+aIndex+"\" nodeClass=\"normalL"+aIndex+"\" width=\"100%\" class=\"normalL"+aIndex+"\" style=\"padding-left:"+tempBreak+"px;\">"+imageHtml+"<span id=\""+tempID+"_word\" name=\""+tempID+"_word\" nodeID=\""+tempID+"\" nodePID=\""+tempPID+"\" level=\""+aIndex+"\" style=\"cursor:hand;\">"+aNode["desc"]+"</span></td></tr>";
  else
  	trHtml="<tr onclick=\"javascript:selectNodeAndExpandNode(true);\" id=\""+tempID+"_tr\" name=\""+tempID+"_tr\" nodeID=\""+tempID+"\" nodePID=\""+tempPID+"\" level=\""+aIndex+"\"><td id=\""+tempID+"_td\" name=\""+tempID+"_td\" nodeID=\""+tempID+"\" nodePID=\""+tempPID+"\" level=\""+aIndex+"\" nodeClass=\"normalL"+aIndex+"\" width=\"100%\" class=\"normalL"+aIndex+"\" style=\"padding-left:"+tempBreak+"px;\">"+imageHtml+"<span id=\""+tempID+"_word\" name=\""+tempID+"_word\" nodeID=\""+tempID+"\" nodePID=\""+tempPID+"\" level=\""+aIndex+"\" style=\"cursor:hand;\">"+aNode["desc"]+"</span></td></tr>";
  if(aIndex==1 && treeHtml!="")
    tempHtml=breakHtml+trHtml;
  else
    tempHtml=trHtml;
  return tempHtml;
}
function selectNodeAndExpandNode(hasChildren){
	var obj=window.event.srcElement;
  	var objNode=arrTree[obj.nodeID];
  	if(objNode!=null){
		if(hasChildren){
			expandOrClose();
			selectNode();
		}
		else{
			selectNode();
		}
		var lClickFunc=objNode["clickfunc"];
		//alert(lClickFunc);
		if(lClickFunc!=null)
			eval(lClickFunc);
	}
}
/************************/
/*���ܣ�չ�����۵����ڵ�*/
/************************/
function expandOrClose(){
  var obj=window.event.srcElement;
  var objImage=document.all.item(obj.nodeID+"_img");
  var objTable=document.all.item(obj.nodeID+"_children");
  if(objImage.expandFlag=="1"){
    objImage.src=treeCloseImage;
    objImage.expandFlag="0";
    objTable.style.display="none";
  }else{
    objImage.src=treeExpandImage;
    objImage.expandFlag="1";
    objTable.style.display="block";
  }
}
/************************/
/*���ܣ����ѡ�����ڵ�*/
/************************/
function selectNode(){
  var obj=window.event.srcElement;
  var objTd=document.all.item(obj.nodeID+"_td");
  if(treeSelectedTd!=""){
    var objOld=document.all.item(treeSelectedTd);
    objOld.className=objOld.nodeClass;
  }
  objTd.className="selectL";
  treeSelectedTd=obj.nodeID+"_td";
}
/************************/
/*���ܣ�������ڵ���ɲ���*/
/************************/
function nodeClick(){
  var objWord=window.event.srcElement;
  alert(objWord.innerText);
}
/************************/
/*���ܣ���Ӳ˵����ڵ�*/
/*������*/
/*       aID���ڵ�ID*/
/*     aDesc���ڵ�����*/
/*aClickFunc������ڵ���ɵĲ�������ȡֵ����ʱ��Ĭ��nodeClick()������ȡֵ���磺��Test();��*/
/************************/
function addTreeNode(aID,aDesc,aClickFunc){
  if(treeSelectedTd==""){
    AlertWindow("Public/","����ѡ��ڵ㣡");
    return;
  }else{
    if(arrTree[aID]!=null){
      AlertWindow("Public/","�Ѿ�������ͬID�Ľڵ㣡");
      return;
    }
    var currentTd=document.all.item(treeSelectedTd);
    var newNodeLevel=parseInt(currentTd.level)+1;
    var oNode=arrTree[currentTd.nodeID];
    var strChildren=oNode["children"];
    if(strChildren==""){
      //��ӽڵ�����
      addNode(aID,oNode["id"],aDesc,aClickFunc);
      //����½ڵ�
      var newNodeHtml=getNodeHtml(arrTree[aID],newNodeLevel);
      var newTr=document.createElement("tr");
      var currentTr=currentTd.parentElement;
      currentTr.insertAdjacentElement("AfterEnd",newTr);
      newTr.id=oNode["id"]+"_children";
      newTr.name=oNode["id"]+"_children";
      var tempHtml="<table id=\""+oNode["id"]+"_table\" name=\""+oNode["id"]+"_table\" width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">"+newNodeHtml+"</table>";
      var newTd = newTr.insertCell();
      newTd.innerHTML=tempHtml;
      //����ԭѡ�нڵ��չ����ʾ
      var imageHtml="<img id=\""+oNode["id"]+"_img\" name=\""+oNode["id"]+"_img\" nodeID=\""+oNode["id"]+"\" nodePID=\""+oNode["pid"]+"\" level=\""+currentTd.level+"\" expandFlag=\"1\" src=\""+treeExpandImage+"\" border=\"0\" style=\"cursor:hand;\">";
      var oldHtml=currentTd.innerHTML;
      currentTd.innerHTML=imageHtml+oldHtml;
      currentTd.style.paddingLeft=treeBlankWidth*parseInt(currentTd.level);
      //������ǰѡ�нڵ�
      currentTd.className=currentTd.nodeClass;
      document.all.item(aID+"_td").className="selectL";
      treeSelectedTd=aID+"_td";
    }else{
      //��ӽڵ�����
      addNode(aID,oNode["id"],aDesc,aClickFunc);
      //����½ڵ�
      oTable=document.all.item(oNode["id"]+"_table");
      var newTr=oTable.insertRow();
      newTr.id=aID+"_tr";
      newTr.name=aID+"_tr";
      newTr.nodeID=aID;
      newTr.nodePID=oNode["id"];
      newTr.level=newNodeLevel;
      var newTd=newTr.insertCell(0);
      newTd.id=aID+"_td";
      newTd.name=aID+"_td";
      newTd.nodeID=aID;
      newTd.nodePID=oNode["id"];
      newTd.level=newNodeLevel;
      newTd.nodeClass="normalL"+newNodeLevel;
      newTd.className="selectL";
      newTd.width="100%";
      var paddingLeft=treeBlankWidth*parseInt(newNodeLevel)+treeImageWidth;
      newTd.style.paddingLeft=paddingLeft+"px";
      //newTd.attachEvent("onclick",selectNode);
      newTd.innerHTML="<span id=\""+aID+"_word\" name=\""+aID+"_word\" nodeID=\""+aID+"\" nodePID=\""+oNode["id"]+"\" level=\""+newNodeLevel+"\" style=\"cursor:hand;\">"+aDesc+"</span></td>";
      //������ǰѡ�нڵ�
      currentTd.className=currentTd.nodeClass;
      treeSelectedTd=aID+"_td";
    }
  }
}
/************************/
/*���ܣ���Ӳ˵������ڵ�*/
/*������*/
/*       aID���ڵ�ID*/
/*     aDesc���ڵ�����*/
/*aClickFunc������ڵ���ɵĲ�������ȡֵ����ʱ��Ĭ��nodeClick()������ȡֵ���磺��Test();��*/
/************************/
function addTreeRoot(aID,aDesc,aClickFunc){
  if(arrTree[aID]!=null){
    AlertWindow("Public/","�Ѿ�������ͬID�Ľڵ㣡");
    return;
  }
  //��ӽڵ�����
  addNode(aID,"",aDesc,aClickFunc);
  //��ӽڵ�
  var oTable=document.all.item("treeTable")
  if(oTable.rows.length>=1){
    var oBreakTr=oTable.insertRow();
    oBreakTr.id=aID+"_break";
    oBreakTr.name=aID+"_break";
    oBreakTr.nodeID=aID;
    var oBreakTd=oBreakTr.insertCell(0);
    oBreakTd.width="100%";
    oBreakTd.className="breakL1";
  }
  var oTr=oTable.insertRow();
  oTr.id=aID+"_tr";
  oTr.name=aID+"_tr";
  oTr.nodeID=aID;
  oTr.nodePID="";
  oTr.level=1;
  var oTd=oTr.insertCell(0);
  oTd.id=aID+"_td";
  oTd.name=aID+"_td";
  oTd.nodeID=aID;
  oTd.nodePID="";
  oTd.level=1;
  oTd.nodeClass="normalL1";
  oTd.className="selectL";
  oTd.width="100%";
  var paddingLeft=treeBlankWidth+treeImageWidth;
  oTd.style.paddingLeft=paddingLeft+"px";
  //oTd.attachEvent("onclick",selectNode);
  oTd.innerHTML="<span id=\""+aID+"_word\" name=\""+aID+"_word\" nodeID=\""+aID+"\" nodePID=\"\" level=\"1\" style=\"cursor:hand;\">"+aDesc+"</span></td>";
  //������ǰѡ�нڵ�
  if(treeSelectedTd!="")
    document.all.item(treeSelectedTd).className=document.all.item(treeSelectedTd).nodeClass;
  treeSelectedTd=aID+"_td";
}
/************************/
/*���ܣ��޸Ĳ˵����ڵ�*/
/*������*/
/*     aDesc���ڵ�����*/
/*aClickFunc������ڵ���ɵĲ�������ȡֵ����ʱ��Ĭ��nodeClick()������ȡֵ���磺��Test();��*/
/************************/
function modifyTreeNode(aDesc,aClickFunc){
  if(aDesc == null || aDesc==""){
    AlertWindow("Public/","�ڵ���������Ϊ�գ�");
    return;
  }
  if(treeSelectedTd==""){
    AlertWindow("Public/","����ѡ��ڵ㣡");
    return;
  }
  var currentTd=document.all.item(treeSelectedTd);
  var nodeID=currentTd.nodeID;
  var level=currentTd.level;
  var oNode=arrTree[nodeID];
  oNode["desc"]=aDesc;
  if(aClickFunc != null && aClickFunc != "")
    oNode["clickfunc"]=aClickFunc;
  var objWord=document.all.item(nodeID+"_word");
  var sHtml="<span id=\""+nodeID+"_word\" name=\""+nodeID+"_word\" nodeID=\""+nodeID+"\" nodePID=\""+oNode["pid"]+"\" level=\""+level+"\" style=\"cursor:hand;\">"+aDesc+"</span></td>";
  objWord.outerHTML=sHtml;
}
/************************/
/*���ܣ�ɾ���˵����ڵ�*/
/************************/
function deleteTreeNode(){
  if(treeSelectedTd==""){
    AlertWindow("Public/","����ѡ��ڵ㣡");
    return;
  }
  var currentTd=document.all.item(treeSelectedTd);
  var nodeID=currentTd.nodeID;
  var oNode=arrTree[nodeID];
  var strChildren=oNode["children"];
  if(strChildren==""){
    var sTips="��ȷ��Ҫɾ���ڵ�\""+oNode["desc"]+"\"��"
  }else{
    AlertWindow("Public/","����ɾ���˽ڵ��µ������ӽڵ㣡");
    return;
  }
  var sReturn = ConfirmWindow("Public/",sTips);
  if(sReturn=="True"){
    var nodePID=currentTd.nodePID;
    if(nodePID==""){    //Ҫɾ���Ľڵ�Ϊ���ڵ�
      //ɾ���ڵ�
      var oTable=document.all.item("treeTable");
      var oTr=document.all.item(nodeID+"_tr");
      oTr.removeNode(true);
      var oBreakTr=document.all.item(nodeID+"_break");
      if(oBreakTr!=null)
        oBreakTr.removeNode(true);
      else{
        if(oTable.rows.length>=1)
          oTable.rows.item(0).removeNode(true);
      }
      //ɾ���ڵ�����
      arrTree[nodeID]=null;
      //������ǰѡ�нڵ�
      if(oTable.rows.length>=1){
        var tempID=oTable.rows.item(0).nodeID;
        treeSelectedTd=tempID+"_td";
        document.all.item(treeSelectedTd).className="selectL";
      }else{
        treeSelectedTd="";
      }
    }else{              //Ҫɾ���Ľڵ�Ϊ�Ǹ��ڵ�
      var oPNode=arrTree[nodePID];
      var strPChildren=oPNode["children"];
      var arrTemp=strPChildren.toString().split(";");
      if(arrTemp.length==1){   //Ҫɾ���Ľڵ�û���ֵܽڵ�
        //ɾ���ڵ�
        var oTr=document.all.item(nodePID+"_children");
        oTr.removeNode(true);
        //�������ڵ��չ����ʾ
        var oPTd=document.all.item(nodePID+"_td");
        var oPWord=document.all.item(nodePID+"_word");
        var level=oPTd.level;
        var paddingLeft=treeBlankWidth*parseInt(level)+treeImageWidth;
        oPTd.style.paddingLeft=paddingLeft+"px";
        oPTd.innerHTML=oPWord.outerHTML;
        //������ѡ�нڵ�
        oPTd.className="selectL";
        treeSelectedTd=nodePID+"_td";
        //�������ڵ��children����
        oPNode["children"]="";
      }
      if(arrTemp.length>1){     //Ҫɾ���Ľڵ����ֵܽڵ�
        //ɾ���ڵ�
        var oTr=document.all.item(nodeID+"_tr");
        oTr.removeNode(true);
        //������ѡ�нڵ�
        document.all.item(nodePID+"_td").className="selectL";
        treeSelectedTd=nodePID+"_td";
        //�������ڵ��children����
        var temp="";
        for(i=0;i<arrTemp.length;i++){
          if(arrTemp[i]!=nodeID){
            if(temp=="")
              temp=arrTemp[i];
            else
              temp=temp+";"+arrTemp[i];
          }
        }
        oPNode["children"]=temp;
      }
      //ɾ���ڵ�����
      arrTree[nodeID]=null;
    }
  }
}