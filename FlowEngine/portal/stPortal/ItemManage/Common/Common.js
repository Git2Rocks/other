/*********************************/
/*���ܣ�����װ�ز���ȷ��ҳ����̬����*/
/*������TipsPagePath  ָ������ȷ��ҳ��·��*/
/*      Msg           ָ��Ҫȷ�ϵ����*/
/*      ActionPage    ָ��������Ҫ�ύ����ҳ�棨������ϸ·���������ȣ��磺/OaBorderModule/CarManage/Manage/CarInfo/_Del.jsp?sRecords=25��*/
/*����ֵ������ֵ*/
/*********************************/
function ActionWindow(TipsPagePath,Msg,ActionPage)
{
  strFeatures = "dialogWidth:380px;dialogHeight:180px;center:yes;status:no";
  sPath = TipsPagePath + "TipsWindow.jsp?ActionPage=" + escape(ActionPage);
  var bflag=showModalDialog(sPath,Msg,strFeatures);
  return bflag;
}
/*********************************/
/*���ܣ�����װ�ز���ȷ��ҳ����̬����*/
/*������TipsPagePath  ָ������ȷ��ҳ��·��*/
/*      Msg           ָ��Ҫȷ�ϵ����*/
/*����ֵ������ֵ*/
/*********************************/
function ConfirmWindow(TipsPagePath,Msg)
{
  strFeatures = "dialogWidth:380px;dialogHeight:180px;center:yes;status:no";
  sPath = TipsPagePath + "ConfirmWindow.jsp";
  var bflag=showModalDialog(sPath,Msg,strFeatures);
  return bflag;
}
function ConfirmWindow_Ex(TipsPagePath,Msg)
{
  strFeatures = "dialogWidth:380px;dialogHeight:180px;center:yes;status:no";
  sPath = TipsPagePath + "ConfirmWindow_Ex.jsp";
  var bflag=showModalDialog(sPath,Msg,strFeatures);
  return bflag;
}
/*********************************/
/*���ܣ�����װ�ز�������ҳ����̬����*/
/*������TipsPagePath  ָ����������ҳ��·��*/
/*      Msg           ָ��Ҫ��������*/
/*********************************/
function AlertWindow(TipsPagePath,Msg)
{
    strFeatures = "dialogWidth:460px;dialogHeight:100px;center:yes;status:no";
    sPath = TipsPagePath + "AlertWindow.jsp?Msg=" + Msg;
    showModalDialog(sPath,window,strFeatures);
}
/*********************************/
/*���ܣ�����װ�ز����ɹ���ʾҳ����̬����*/
/*������TipsPagePath  ָ�������ɹ���ʾҳ��·��*/
/*      Msg           ָ���ɹ���ʾ���*/
/*********************************/
function SucceedWindow(TipsPagePath,Msg)
{
  strFeatures = "dialogWidth:380px;dialogHeight:180px;center:yes;status:no";
  sPath = TipsPagePath + "SucceedWindow.jsp";
  showModalDialog(sPath,Msg,strFeatures);
}
/*********************************/
/*���ܣ��������ڴ�����ʾҳ����̬����*/
/*������TipsPagePath  ָ�����ڴ�����ʾҳ��·��*/
/*      FuncName      ָ����������*/
/*      FuncPara      ָ����������*/
/*********************************/
function openHaddleingWindow(TipsPagePath,FuncName,FuncPara,DialogType){
  var obj;
  strFeatures = "dialogWidth:380px;dialogHeight:50px;center:yes;status:no";
  sPath = TipsPagePath + "haddleingPage.jsp?funcName="+FuncName+"&funcPara="+FuncPara;
  if(arguments.length==3)
    obj=showModalDialog(sPath,window,strFeatures);
  if(arguments.length==4){
    if(DialogType==1)
      obj=showModalDialog(sPath,window,strFeatures);
    if(DialogType==2)
      obj=showModelessDialog(sPath,window,strFeatures);
  }
  return obj;
}
//����Ϊ����������
function checkPage(TipsPagePath,pageCount)
{
    var pageNo = document.all.item("c_page").value;
    if(pageNo == "") {
        AlertWindow(TipsPagePath,"��������ҳ�룡");
        document.all.item("c_page").focus();
        return false;
    }else if(isNaN(pageNo)) {
        AlertWindow(TipsPagePath,"����ע�⣬����д��ҳ�벻��һ�����֣�");
        document.all.item("c_page").value="";
        document.all.item("c_page").focus();
        return false;
    }else if(parseInt(pageNo)<1 || parseInt(pageNo)>pageCount){
        AlertWindow(TipsPagePath,"����ע�⣬ҳ��Ҫ�ڣ�1��" + pageCount + "����Χ�ڣ�");
        document.all.item("c_page").value="";
        document.all.item("c_page").focus();
        return false;
    }
    return true;
}

function isSubmit(pageCount)
{
    if(checkPage(pageCount) == false)
       return false;

    gotoPage(document.all.item("c_page").value);
    return true;
}

function selectMan(aShowName,aHiddenName,aSelFlag,aFrameFlag)
{
    var show = document.all.item(aShowName).value;
    var value = document.all.item(aHiddenName).value;
    var feature = "dialogWidth:563px;dialogHeight:480px;center:yes;status:no";
    var url = "Public/FrameList.jsp?selFlag=" + aSelFlag + "&frameFlag=" + aFrameFlag;
    var tmp = showModalDialog(url,value + "=" + show,feature);
    if(tmp != null){
        var users = tmp.split("=");
        document.all.item(aShowName).value = users[1];
        document.all.item(aHiddenName).value = users[0];
    }
}

function selectList(aUrlPara,aControlName,aHiddenName)
{
    var feature = "dialogWidth:477px;dialogHeight:473px;center:yes;status:no";
    var url = 'SelectListFrame.jsp?' + aUrlPara;
    var struct = window.showModalDialog(url,this,feature);
    if (struct != null){
        document.all.item(aControlName).value = struct[0];
        document.all.item(aHiddenName).value = struct[1];
    }
    return;
}

function selectButton(aUrlPara,aControlList)
{
    var feature = "dialogWidth:477px;dialogHeight:293px;center:yes;status:no";
    var url = 'SelectButtonFrame.jsp?' + aUrlPara;
    var struct = window.showModalDialog(url,this,feature);
    if (struct != null){
        var controlStruct = aControlList.split(";");
        var i = 0;
        for(i=0;i<controlStruct.length;i++){
          var control = document.all.item(controlStruct[i]);
          if(control != null){
            var value = "";
            for(j=0;j<struct.length;j++){
              if(struct[j][i] == "&nbsp;")
                 continue;
              if(value != "")
                value += ";";
              value += struct[j][i];
            }
            control.value = value;
          }
        }
    }
    return;
}

function my_unescape(aValue)
{
  return unescape(aValue);
  //return aValue;
}

//�����˵��ֶεĳ���
function UserInfo(sUserCode){
  var feature = "dialogWidth:605px;dialogHeight:393px;center:yes;status:no";
  var path = "UserInfo.jsp?sUserCode="+sUserCode;
  showModalDialog(path,"",feature);
}