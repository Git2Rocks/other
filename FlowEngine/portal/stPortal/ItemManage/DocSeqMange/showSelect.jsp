<%@ page contentType="text/html; charset=GBK" %>
<%@ page errorPage="../errorPage.jsp" %>
<%@ page import="minstone.ItemManage.BaseDbManage"%>
<%@ page import="minstone.ItemManage.WorkItem"%>
<%@ page import="java.util.Vector,java.util.Enumeration"%>
<%@ page import="oamodule.publiclib.util.RecordSetObject"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head></head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>ѡ��</title>

<link rel="stylesheet" type="text/css" href="../Common/Public.css">
<script>
  function showSelect(sValue){
  	//window.alert(sValue);
		window.returnValue = sValue;
		window.close();
  }
</script>
<table width="100%" cellpadding="3" cellspacing="1" class="boarder">
      <tr  class="headline-bg">
      <td width="40%"><div align="center">�ֺ�</div></td>
      <td width="60%"><div align="center">����</div></td>
      </tr>
<%
      request.setCharacterEncoding("GBK");
      String names="",desc="",reValue="";
      Vector vResult = new Vector();
      BaseDbManage db=new BaseDbManage(request.getRemoteUser());
      vResult =db.getShowSelDocSeq(request.getRemoteUser());
      if(!vResult.isEmpty()){
        for (int i=0;i<vResult.size();i++) {
          Vector vResultRow=new Vector();
          vResultRow=(Vector)vResult.elementAt(i);	//������ȡ������ֶ���ʾ
            names =(String)vResultRow.elementAt(0);	//�ֺ�
            desc =(String)vResultRow.elementAt(1);	//����
            if(names==null) names="";
            if(desc==null) desc="";

            reValue=names;		//����ֵ
 %>
            <tr class="content-bg" style="cursor:hand;"><a onclick=showSelect('<%=reValue%>');>
            <td><%=names%></td>
            <td><%=desc%></td>
            </a></tr>
<%}}%>
            </table>

</body>
</html>

