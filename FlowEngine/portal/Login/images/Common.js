/*********************************/
/*���ܣ�����װ�ز�������ҳ����̬����*/
/*������TipsPagePath  ָ����������ҳ��·��*/
/*      Msg           ָ��Ҫ��������*/
/*********************************/
function AlertWindow(TipsPagePath,Msg)
{
  strFeatures = "dialogWidth:460px;dialogHeight:100px;center:yes;status:no";
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
