<%@ page contentType="text/html; charset=GBK" %>
<%@ page errorPage="../errorPage.jsp" %>
<%@ page import="minstone.ItemManage.BaseDbManage"%>
<%@ page import="minstone.ItemManage.WorkItem"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>����ʵʩ��Ŀ</title>
<link rel="stylesheet" type="text/css" href="../Common/Public.css">
<script language="javascript" src="../Common/Common.js"></script>
<script language="javascript" src="../Common/i_CheckInput.js"></script>
</head>
<script language="javascript">
window.name="frmNewWorkItemName";
function doSave(){
    frmNewWorkItemName.actionFlag.value="saveIt";
    frmNewWorkItemName.submit();
}
</script>
<%	request.setCharacterEncoding("GBK");
	String actionFlag=request.getParameter("actionFlag");
	if(actionFlag==null) actionFlag="";
	if(!actionFlag.equals("saveIt")){
%>

<body bgcolor="#ffffff">
<div align="center"><strong><font size="+3">����ʵʩ��Ŀ</font></strong> </div>
<form name="frmNewWorkItemName" method="post" action="ItemNew.jsp" target="frmNewWorkItemName">
  <table width="100%" cellpadding="3" cellspacing="1" class="boarder">
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF">����</td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="itemCode" type="text" class="TextUtil_input" style="width:100%;" >
		</td>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF">��Ŀ����</td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="itemName" type="text" class="TextUtil_input" style="width:100%;" >
		</td>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF">��Ŀ����</td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="itemNo" type="text" class="TextUtil_input" style="width:100%;" >
		</td>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF">��Ŀ����</td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="itemDesc" type="text" class="TextUtil_input" style="width:100%;" >
		</td>
    </tr>
    <tr class="content-bg">
      <td bgcolor="#FFFFFF">�Ƿ���Ч</td>
      <td bgcolor="#FFFFFF">
        <input name="itemValid" type="checkbox" value="1">
      </td>
  </tr>
</table>
  <p align="center">
	<input name="actionFlag" type="hidden" id="actionFlag" >
    <input name="btnSave" type="button" class="Btn_common" value="����" onclick="javascript:doSave();">
    <input name="btnCancel" type="button" class="Btn_common" value="ȡ��" onclick="javascript:document.location='ItemList.jsp';">
  </p>
</form>
</body>
<%}else{
	String itemCode=request.getParameter("itemCode");
	String itemName=request.getParameter("itemName");
	String itemNo=request.getParameter("itemNo");
	String itemDesc=request.getParameter("itemDesc");
	String sValid=request.getParameter("itemValid");
    	String itemValid ="0";
	if(sValid==null){
       		itemValid ="0";
	}else{
      	itemValid ="1";
	}

	BaseDbManage db=new BaseDbManage(request.getRemoteUser());
	WorkItem workItem=new WorkItem();
	workItem.setITEM_CODE(itemCode);
	workItem.setITEM_NAME(itemName);
	workItem.setITEM_NO(itemNo);
	workItem.setITEM_DESC(itemDesc);
	workItem.setITEM_VALID(itemValid);

	boolean bSuccess=db.addWorkItem(workItem);
%>
<body>
<table width="100%" height="100%" border="0">
  <tr>
    <td>
        <%if(bSuccess){%>
          <script> document.location ="ItemList.jsp";</script>
		<%}else{%>
            <p align="center">�½���Ŀʧ��!���кſ����ظ���</p>
      		<p align="center"><a href="ItemList.jsp">����</a></p></td>
		<%}%>
  </tr>
</table>
</body>
<%}%>
</html>

