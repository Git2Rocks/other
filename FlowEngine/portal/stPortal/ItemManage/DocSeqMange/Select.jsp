<%@ page contentType="text/html; charset=GBK" %>
<%
	//request.setCharacterEncoding("GBK");
%>
<link rel="stylesheet" type="text/css" href="../Common/Public.css">
<html>
<script>

 function initWindow(){
  }
 //�ܷ�����Ӧ
 function canSend(){
	return true;
 }

 function trimStr(a_strVal){
	return(a_strVal.replace(/^\s*|\s*$/g,""));
 }
 //�ܷ񱣴���Ӧ
 function canSave(){
	return true;
 }
 //���ع�����������ʾ����Ϣ
 function getMessage(){
	return message;
 }
 //������Ӧ
 function send(){
	return true;
 }
 //������Ӧ
 function save(){
	return true;
 }

 function selectButton(){
	var sFeatures;
	sFeatures = "dialogHeight:500px;dialogWidth:400px;";
	sFeatures = sFeatures + "center:yes;edge:raised;help:no;scroll:yes;status:no;unadorned:yes;resizable:yes"
	var sReturn = window.showModalDialog("showSelect.jsp",null,sFeatures);
	if (sReturn != null)
	{
    document.all.item("Main1_Text8").value=sReturn; //�������ã���ʾ�ڱ�ҳ��
		window.parent.document.all.item("Main1_Text88").value=sReturn; //���ϵĿؼ�����û��"Main1_"�Ŷ�Ӧ����
	}
}
</script>
<body scroll="no">
<form action="" target="_self" method="post" name="" id="">
<table>
  <tr>
  	<td>
   		<input type="button" class="" value="ѡ��" onclick="javascript:selectButton();" >
  	</td>
  </tr>
</table>
<input type="hidden" name="Main1_Text8" value=""> <!---��������------>
</form>
</body>
</html>
