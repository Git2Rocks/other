/*********************************/
/*���ܣ�����װ�ز���ȷ��ҳ����̬����*/
/*������TipsPagePath  ָ������ȷ��ҳ��·��*/
/*      Msg           ָ��Ҫȷ�ϵ����*/
/*      ActionPage    ָ��������Ҫ�ύ����ҳ�棨������ϸ·���������ȣ��磺/OaBorderModule/CarManage/Manage/CarInfo/_Del.jsp?sRecords=25��*/
/*����ֵ������ֵ*/
/*********************************/
function ActionWindow(TipsPagePath,Msg,ActionPage)
{
  strFeatures = "dialogWidth:400px;dialogHeight:250px;center:yes;status:no";
  sPath = TipsPagePath + "TipsWindow.jsp?Msg=" + Msg + "&ActionPage=" + escape(ActionPage);
  var bflag=showModalDialog(sPath,window,strFeatures);
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
/*���ܣ�����װ�ز���ʧ����ʾҳ����̬����*/
/*������TipsPagePath  ָ������ʧ����ʾҳ��·��*/
/*      Msg           ָ��ʧ����ʾ���*/
/*      ErrorInfo     ָ�����²���ʧ�ܵĳ�����Ϣ*/
/*********************************/
function ErrorWindow(TipsPagePath,Msg,ErrorInfo)
{
    strFeatures = "dialogWidth:460px;dialogHeight:100px;center:yes;status:no";
    sPath = TipsPagePath + "ErrorWindow.jsp?Msg=" + Msg + "&ErrorInfo=" + ErrorInfo;
    showModalDialog(sPath,window,strFeatures);
}
/*********************************/
/*���ܣ�����װ�ز����ɹ���ʾҳ����̬����*/
/*������TipsPagePath  ָ�������ɹ���ʾҳ��·��*/
/*      Msg           ָ���ɹ���ʾ���*/
/*********************************/
function SucceedWindow(TipsPagePath,Msg)
{
    strFeatures = "dialogWidth:380px;dialogHeight:230px;center:yes;status:no";
    sPath = TipsPagePath + "SucceedWindow.jsp?Msg=" + Msg;
    return showModalDialog(sPath,window,strFeatures);
}
/*********************************/
/*���ܣ�����װ��ѡ���û�ҳ����̬����*/
/*������PageURL        ָ���û�ѡ��ҳ���磺/OaBorderModule/Public/FrameList.jsp*/
/*      sOldUserCode   ָ��ԭ���û��Ĵ���*/
/*      sOldUserName   ָ��ԭ���û�������*/
/*      sNewUserCode   �õ���ѡ���û��Ĵ���*/
/*      sNewUserName   �õ���ѡ���û�������*/
/*********************************/
function ChooseUserWindow(PageURL,sOldUserCode,sOldUserName,sNewUserCode,sNewUserName)
{
    strFeatures = "dialogWidth:550px;dialogHeight:480px;center:yes;status:no";
    if (sOldUserCode != "" && sOldUserName != "")
        sOldUserInfo = sOldUserCode + "=" + sOldUserName;
    else
        sOldUserInfo = "";
    var bflag=showModalDialog(PageURL,sOldUserInfo,strFeatures);
    if (bflag != "" && bflag != "undefined" && bflag != undefined)
    {
        sArr1 = bflag.split("=");
        if (sArr1.length == 2)
        {
            sNewUserCode = sArr1[0];
            sNewUserName = sArr1[1];
        }
    }
}
