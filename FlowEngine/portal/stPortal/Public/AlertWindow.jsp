<%@ page contentType="text/html; charset=GBK" %>
<%
%>
<html>
<head>
<title>��Ϣ��ʾ</title>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<script type="text/javascript">
window.onload = initWindow;

function initWindow()
{
    var sMsg = window.dialogArguments;
    document.all.item("MsgUtil").innerHTML = sMsg;
}
function Ok()
{
    window.close();
}
</script>
<style>
Body{
  background-color:white;
  font-size:10.8pt;
  font-family: ����;
  margin:0px 0px 0px 0px;  /*top right bottom left*/
  padding:0px 0px 0px 0px;
  scrollbar-face-color: #DEE3E7;                 /*�����������¼�ͷ��������ɫ*/
  scrollbar-highlight-color: #FFFFFF;
  scrollbar-shadow-color: #DEE3E7;               /*���ɹ���ʱ��ͷ����ɫ�͹������ҡ��±߿��Լ����¼�ͷ�����ҡ��±߿����ɫ*/
  scrollbar-3dlight-color: #D1D7DC;              /*���������ϱ߿�����¼�ͷ�������ϱ߿����ɫ*/
  scrollbar-arrow-color:  #006699;               /*�ɹ���ʱ��ͷ����ɫ*/
  scrollbar-track-color: #EFEFEF;                /*�������������ɫ*/
  scrollbar-darkshadow-color: #98AAB1;           /*�������ҡ��±߿�����¼�ͷ�����ҡ��±߿����ɫ*/
}
.standardBtn{
  width:60px;
  height:20px;
  padding-top:2px;
  border:1px #939eb2 solid;
  background-image:url('images/standardBtn_bg.gif');
  background-repeat:repeat-x;
  text-align:center;
  cursor:hand;
  font-size:10.8pt;
}
</style>
</head>
<body scroll="no" style="background-color:#D3E0FF;">
<table width="380" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td style="background-image:url('images/Tips_bg.jpg');background-repeat:no-repeat;background-position:left top;height:120px;">
      <table width="100%" border="0" cellpadding="0" cellspacing="0" style="table-layout:fixed;">
        <tr>
          <td width="35%" align="center">
            <img src="images/Tips_Alert.gif" border="0">
          </td>
          <td id="MsgUtil" name="MsgUtil" width="53%">
            &nbsp;
          </td>
          <td width="12%">
            &nbsp;
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td align="center" valign="top" style="height:30px;">
      <input type="button" name="CancleBtn" class="standardBtn" value="�ر�" onclick="javascript:Ok();">
    </td>
  </tr>
</table>
</body>
</html>
