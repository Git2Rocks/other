<%@ page contentType="text/html; charset=GBK" %>
<%@ page errorPage="../errorPage.jsp" %>
<%@ page import="minstone.ItemManage.BaseDbManage"%>
<%@ page import="minstone.ItemManage.WorkItem"%>
<%@ page import="java.util.Vector,java.util.Enumeration"%>
<%@ page import="oamodule.publiclib.util.RecordSetObject"%>

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�޸��ֺ�</title>
<link rel="stylesheet" type="text/css" href="../Common/Public.css">
<script language="javascript" src="../Common/Common.js"></script>
<script language="javascript" src="../Common/i_CheckInput.js"></script>
</head>
<%
	request.setCharacterEncoding("GBK");

	BaseDbManage db=new BaseDbManage(request.getRemoteUser());
	String itemCode=request.getParameter("workItemCode");
	String itemName="";
	String itemNo="";
	String itemDesc="";
	String vaildRightCode="";
	String vaildRightName="";
	String itemValid="0";

	String actionFlag=request.getParameter("actionFlag");
	if(actionFlag==null) actionFlag="";
	if(!actionFlag.equals("saveIt")){
          if(itemCode==null)
		itemCode="";
	  else{
		RecordSetObject rsoChargeList =db.getDocSeq(itemCode);
		if(rsoChargeList!=null && rsoChargeList.getRowCount()>0){
                 for(int index=0;index<1;index++){ //��һ����¼
			itemName=rsoChargeList.getString("DOCNUM_AREA",index);
			itemNo=rsoChargeList.getString("ITEM_NO",index);
                        itemDesc=rsoChargeList.getString("DOCNUM_AREA_DESC",index);
                        vaildRightCode=rsoChargeList.getString("VALID_DEPTCODE",index);
                        vaildRightName=rsoChargeList.getString("VALID_DEPTNAME",index);
			itemValid=rsoChargeList.getString("ITEM_VALID",index);
                  }
                if(itemName==null) itemName="";
                if(itemNo==null) itemNo="";
                if(itemDesc==null) itemDesc="";
                if(vaildRightCode==null) vaildRightCode="";
                if(vaildRightName==null) vaildRightName="";
		}
	}
%>
<script language="javascript">
function doSave(){
    frmUpdateItem.actionFlag.value="saveIt";
    frmUpdateItem.submit();
}

function selRight(){

	//ͨ��������ͨ�õĲ���ѡ��ʽ
  var sFeatures = "dialogWidth:670px;dialogHeight:580px;center:yes;status:no";
  var sPath = "/FlowEngineWeb/workflow/Public/FrameList.jsp?selFlag=4";
  //��ʽΪ 222:3;333:3;test1=�û�3���û�2���û�1;
  var sReturn = showModalDialog(sPath,"",sFeatures);
  if(sReturn==null)
    return;
  var aTmp = sReturn.split("=");
  sReturn=aTmp[0];
  //alert(sReturn);
  document.all.item("vaildRightCode").value= sReturn;
  document.all.item("vaildRightName").value= aTmp[1];
}

</script>
<body bgcolor="#ffffff">
<div align="center"><strong><font size="+3">�޸��ֺ�</font></strong> </div>
<form name="frmUpdateItem" method="post" action="DocSeqUpdate.jsp" target="">
   <table width="100%" cellpadding="3" cellspacing="1" class="boarder">
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF"><div align="center">�ֺ�����</div></td>
      <td colspan="2" width="75%" bgcolor="#FFFFFF">
        <input name="itemCode" type="text" value="<%=itemCode%>" class="TextUtil_input" style="width:100%;" readonly>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF"><div align="center">�ֺŵ���</div></td>
      <td colspan="2" width="75%" bgcolor="#FFFFFF">
        <input name="itemName" type="text" value="<%=itemName%>" class="TextUtil_input" style="width:100%;">
		</td>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF"><div align="center">�ֺű���</div></td>
      <td colspan="2" width="75%" bgcolor="#FFFFFF">
        <input name="itemNo" type="text" value="<%=itemNo%>" class="TextUtil_input" style="width:100%;">
		</td>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF"><div align="center">�ֺ�����</div></td>
      <td colspan="2" width="75%" bgcolor="#FFFFFF">
        <input name="itemDesc" type="text" value="<%=itemDesc%>" class="TextUtil_input" style="width:100%;">
		</td>
    </tr>
    <tr class="content-bg">
      <td width="25%" bgcolor="#FFFFFF"><div align="center">ʹ��Ȩ��</div></td>
      <td width="75%" bgcolor="#FFFFFF">
        <input name="vaildRightName" type="text" value="<%=vaildRightName%>" class="TextUtil_input" style="width:100%;"></td>
      <td><div align="center"><img onclick="javascript:selRight()" style="cursor:hand;" src="../Common/Images/icon_urge.gif" width="16" height="16" alt="ѡ��ʹ��Ȩ��"></div></td>
		</td>
    </tr>
    <tr class="content-bg">
      <td bgcolor="#FFFFFF"><div align="center">�Ƿ���Ч</div></td>
      <td colspan="2" bgcolor="#FFFFFF">
        <input name="itemValid" type="checkbox" value="1" <%if(itemValid=="1"){ out.print(" checked ");}%>>
      </td>
  </tr>
</table>
  <p align="center">
		<input name="itemCode" type="hidden" id="itemCode" value="<%=itemCode%>" >
		<input name="itemName" type="hidden" id="itemName" value="<%=itemName%>" >
		<input name="itemNo" type="hidden" id="itemNo" value="<%=itemNo%>" >
		<input name="itemDesc" type="hidden" id="itemDesc" value="<%=itemDesc%>" >
		<input name="vaildRightCode" type="hidden" id="vaildRightCode" value="<%=vaildRightCode%>" >
		<input name="actionFlag" type="hidden" id="actionFlag" >
    <input name="btnSave" type="button" class="Btn_common" value="����" onclick="javascript:doSave();">
    <input name="btnCancel" type="button" class="Btn_common" value="ȡ��" onclick="javascript:document.location='DocSeqList.jsp';">
  </p>
</form>
</body>
<%}else{
	itemCode=request.getParameter("itemCode");
	itemName=request.getParameter("itemName");
	itemNo=request.getParameter("itemNo");
	itemDesc=request.getParameter("itemDesc");
	vaildRightCode=request.getParameter("vaildRightCode");
	vaildRightName=request.getParameter("vaildRightName");
	String sValid=request.getParameter("itemValid");
    	itemValid ="0";
	if(sValid==null){
       		itemValid ="0";
	}else{
      	itemValid ="1";
	}

	WorkItem workItem=new WorkItem();
	workItem.setITEM_CODE(itemCode);
	workItem.setITEM_NAME(itemName);
	workItem.setITEM_NO(itemNo);
	workItem.setITEM_DESC(itemDesc);
	workItem.setITEM_VALID(itemValid);
	workItem.setITEM_RIGHTCODE(vaildRightCode);
	workItem.setITEM_RIGHTNAME(vaildRightName);

	boolean bSuccess=db.updateDocSeq(workItem);

%>
<body>
<table width="100%" height="100%" border="0">
	<tr>
    <td>
        <%if(bSuccess){%>
          <script> alert("�޸��ֺ����Գɹ���");document.location="DocSeqList.jsp";</script>
				<%}else{%>
						<p>�ֺű���:<%=itemCode%>;�ֺ�����:<%=itemName%>;�ֺű��:<%=itemNo%>;�ֺ�����:<%=itemDesc%>;�Ƿ���Ч:<%=itemValid%></p>
            <p align="center">�޸��ֺ�ʧ��!</p>
      			alert("�޸��ֺ�����ʧ�ܣ�");
     </td>
		<%}%>
  </tr>
</table>
</body>
<%}%>
</html>

