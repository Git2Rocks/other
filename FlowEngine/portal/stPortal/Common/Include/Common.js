/*********************************/
/*���ܣ�����װ�ز�������ҳ����̬����*/
/*������TipsPagePath  ָ����������ҳ��·��*/
/*      Msg           ָ��Ҫ��������*/
/*********************************/
function AlertWindow(TipsPagePath,Msg)
{
  strFeatures = "dialogWidth:380px;dialogHeight:210px;center:yes;status:no";
  sPath = TipsPagePath + "AlertWindow.jsp";
  showModalDialog(sPath,Msg,strFeatures);
}

/*********************************/
/*���ܣ�����װ�ز���ȷ��ҳ����̬����*/
/*������TipsPagePath  ָ������ȷ��ҳ��·��*/
/*      Msg           ָ��Ҫȷ�ϵ����*/
/*����ֵ������ֵ*/
/*********************************/
function ConfirmWindow(TipsPagePath,Msg)
{
  strFeatures = "dialogWidth:380px;dialogHeight:230px;center:yes;status:no";
  sPath = TipsPagePath + "ConfirmWindow.jsp";
  bflag = showModalDialog(sPath,Msg,strFeatures);
  return bflag;
}
/*********************************/
/*���ܣ�����װ�ز����ɹ���ʾҳ����̬����*/
/*������TipsPagePath  ָ�������ɹ���ʾҳ��·��*/
/*      Msg           ָ���ɹ���ʾ���*/
/*********************************/
function SucceedWindow(TipsPagePath,Msg)
{
  strFeatures = "dialogWidth:380px;dialogHeight:210px;center:yes;status:no";
  sPath = TipsPagePath + "SucceedWindow.jsp";
  showModalDialog(sPath,Msg,strFeatures);
}
function openFrameList(aShowName,aHiddenName,aSelFlag,aFrameFlag,aFrameLevel,aFrameLevelTo,aFrameList,
						dispGroupNode,dispPersGroupNode,dispAllUserNode,groupNodeDesc,
						persGroupNodeDesc,groupList,dataSource,modifyMode){
	var show = document.getElementById(aShowName).value;
    var value = document.getElementById(aHiddenName).value;
    var feature = "dialogWidth:720px;dialogHeight:615px;center:yes;status:no;help:no";
    var url = "/FlowEngineWeb/workflow/Public/FrameList.jsp?selFlag=" + aSelFlag + "&frameFlag=" + aFrameFlag+"&frameLevel="+aFrameLevel+"&frameLevelTo="+aFrameLevelTo+"&frameList="+aFrameList;
    url=url+"&dispGroupNode="+dispGroupNode+"&dispPersGroupNode="+dispPersGroupNode+"&dispAllUserNode="+dispAllUserNode;
	url=url+"&groupNodeDesc="+groupNodeDesc+"&persGroupNodeDesc="+persGroupNodeDesc+"&groupList="+groupList+"&dataSource="+dataSource;
    url=url+"&modifyMode="+modifyMode;
    var tmp = showModalDialog(url,value + "=" + show,feature);
    if(tmp != null){
        var users = tmp.split("=");
        document.getElementById(aShowName).value = users[1];
        document.getElementById(aHiddenName).value = users[0];
    }
}