<%@ page contentType="text/html; charset=GBK" %>
<%@ page errorPage="../errorPage.jsp" %>
<%@ page import="minstone.ItemManage.BaseDbManage"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�޸���Ŀ</title>
<link rel="stylesheet" type="text/css" href="../Common/Public.css">
<script language="javascript" src="../Common/Common.js"></script>
<script language="javascript" src="../Common/i_CheckInput.js"></script>
</head>

<%
	request.setCharacterEncoding("GBK");

	String itemCode=request.getParameter("workItemCode");
	String itemName=request.getParameter("workItemName");
	String itemNo=request.getParameter("workItemNo");
	String itemDesc=request.getParameter("workItemDesc");
	if(itemCode==null) itemCode="";
	if(itemName==null) itemName="";
	if(itemNo==null) itemNo="";
	if(itemDesc==null) itemDesc="";

	String itemValid="0";
	BaseDbManage db=new BaseDbManage(request.getRemoteUser());
	String actionFlag=request.getParameter("actionFlag");
	if(actionFlag==null) actionFlag="";
	if(!actionFlag.equals("saveIt")){
%>
<script language="javascript">
function doSave(){
    frmUpdateItem.actionFlag.value="saveIt";
    frmUpdateItem.submit();
}
</script>
<body bgcolor="#ffffff">
<div align="center"><strong><font size="+3">�޸���Ŀ</font></strong> </div>
<form name="frmUpdateItem" method="post" action="ItemUpdate.jsp" target="">
   <table width="100%" cellpadding="3" cellspacing="1" class="boarder">
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF">����</td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="itemCode" type="text" value="<%=itemCode%>" class="TextUtil_input" style="width:100%;" readonly>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF">��Ŀ����</td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="itemName" type="text" value="<%=itemName%>" class="TextUtil_input" style="width:100%;">
		</td>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF">��Ŀ����</td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="itemNo" type="text" value="<%=itemNo%>" class="TextUtil_input" style="width:100%;">
		</td>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF">��Ŀ����</td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="itemDesc" type="text" value="<%=itemDesc%>" class="TextUtil_input" style="width:100%;">
		</td>
    </tr>
    <tr class="content-bg">
      <td bgcolor="#FFFFFF">�Ƿ���Ч</td>
      <td bgcolor="#FFFFFF">
        <input name="itemValid" type="checkbox" value="1" <%if(itemValid=="1"){ out.print(" checked ");}%>>
      </td>
  </tr>
</table>
  <p align="center">
		<input name="itemCode" type="hidden" id="itemCode" value="<%=itemCode%>" >
		<input name="itemName" type="hidden" id="itemName" value="<%=itemName%>" >
		<input name="itemNo" type="hidden" id="itemNo" value="<%=itemNo%>" >
		<input name="itemDesc" type="hidden" id="itemDesc" value="<%=itemDesc%>" >
		<input name="actionFlag" type="hidden" id="actionFlag" >
    <input name="btnSave" type="button" class="Btn_common" value="����" onclick="javascript:doSave();">
    <input name="btnCancel" type="button" class="Btn_common" value="ȡ��" onclick="javascript:document.location='ItemList.jsp';">
  </p>
</form>
</body>
<%}else{
		itemCode=request.getParameter("itemCode");
		itemName=request.getParameter("itemName");
		itemNo=request.getParameter("itemNo");
		itemDesc=request.getParameter("itemDesc");
		String sValid=request.getParameter("itemValid");
		if(sValid==null){
			itemValid ="0";
		}else{
     	itemValid="1";
		}

	boolean bSuccess=db.updateWorkItem(itemCode,itemName,itemNo,itemDesc,itemValid);
%>
<body>
<table width="100%" height="100%" border="0">
	<tr>
    <td>
        <%if(bSuccess){%>
          <script> alert("�޸���Ŀ���Գɹ���");document.location="ItemList.jsp";</script>
				<%}else{%>
						<p>��Ŀ����:<%=itemCode%>;��Ŀ����:<%=itemName%>;��Ŀ���:<%=itemNo%>;��Ŀ����:<%=itemDesc%>;�Ƿ���Ч:<%=itemValid%></p>
            <p align="center">�޸���Ŀʧ��!</p>
      			alert("�޸���Ŀ����ʧ�ܣ�");
     </td>
		<%}%>
  </tr>
</table>
</body>
<%}%>
</html>

