<%@ page contentType="text/html; charset=GBK" %>
<%@ page errorPage="../errorPage.jsp" %>
<%@ page import="minstone.ItemManage.BaseDbManage"%>
<%@ page import="java.util.Vector,java.util.Enumeration"%>
<%@ page import="oamodule.publiclib.util.RecordSetObject"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��ѯ����б�</title>
<link rel="stylesheet" type="text/css" href="./Common/Public.css">
</head>
<script>
//��ѯ����ҳ������
function toUrl(num,pagesize,tableName){
    //alert(num);
    window.location.href="queryList.jsp?pageNo="+num+"&pagesize="+pagesize+"&tableName="+tableName;
}
</script>
<%
	request.setCharacterEncoding("GBK");
	BaseDbManage db=new BaseDbManage(request.getRemoteUser());
	String columnPercent ="",columnList="";
	String sTableName=request.getParameter("tableName");
	if(sTableName==null) sTableName="";
	if(!sTableName.equals("")){
	String contentList="";//ͨ�õĲ�ѯ���
	String actionFlag=request.getParameter("actionFlag");
	if(actionFlag==null) actionFlag="";
	if(actionFlag.equals("DeleteFlag")){
        	System.out.println("ɾ����¼ ");
    	}
        //ÿҳ����Ϊ10��
	String sPageSize = request.getParameter("pagesize");
	if(sPageSize==null) sPageSize="0";
	int pageSize=0;
	pageSize=Integer.parseInt(sPageSize);
	//RecordSetObject rsoLiverBed=db.getDocSeq();
	//�ڼ�ҳ��ҳ��
        String pageStr=(String)request.getParameter("pageNo");
        if(pageStr==null || pageStr.equals(""))
          pageStr="1";
        int pageNo = java.lang.Integer.parseInt(pageStr);
        if(pageNo==0) pageNo=1;
        //ÿҳ����Ϊ10��
        if(pageSize==0)   pageSize = 10;
	//���ֶ�����
	Vector vTableColumn=new Vector();
        vTableColumn =db.getQueryTable(sTableName);
        int columnSize=vTableColumn.size();
        //�õ�����������������������
        Vector vResult=new Vector();
        vResult=db.getQueryList(sTableName,pageNo,pageSize);
        //���㷭ҳ����
        int count=Integer.parseInt((String)vResult.elementAt(0));
        int pageCount=(int)((count-1)/pageSize + 1);
%>
<script language="javascript">
function doDelete(workItemCode){
	var truthBeTold = window.confirm("�����Ҫɾ����? ������ȷ����������������ȡ����ֹͣ��");
    if(!truthBeTold) return;
	frmQueryList.workItemCode.value=workItemCode;
	frmQueryList.actionFlag.value="DeleteFlag";
	frmQueryList.submit();
}
function doModify(workItemCode){
	frmQueryList.workItemCode.value=workItemCode;
	var strAction="DocSeqUpdate.jsp?workItemCode="+workItemCode;
	frmQueryList.action=strAction;
	frmQueryList.actionFlag.value="UpdateFlag";
	frmQueryList.submit();
}
function openList(flowInid){
	var w=window.screen.width-10;
	var h=window.screen.height-55;
	var sStyle="width="+w+"px,height="+h+"px,left=0px,top=0px,scrollbars=yes,resizable=yes";
	var sUrl="/FlowEngineWeb/workflow/FlowFrame.jsp?action=0&flowInid="+flowInid;
	window.open(sUrl,"",sStyle);
}
</script>
<body bgcolor="#ffffff">
<table width="100%" cellpadding="3" cellspacing="1" class="boarder">
  <tr class="headline-bg">
   <%
    for (int i=0;i<vTableColumn.size();i++) {
        //������ȡ������ֶ���ʾ
      	columnList =(String)vTableColumn.elementAt(i);
      	int length=columnList.length();
      	if(contentList==null) contentList="";
	else{
	 columnPercent =columnList.substring( length-2,length);
  	 if(db.toInt(columnPercent,0)==0) { //���û��������Ϊ�ٷֱȣ�������20��
         	columnPercent=columnPercent.valueOf(100/(vTableColumn.size()))+"%" ;
	 	columnList=columnList;
         }else{
		columnPercent=columnPercent+"%";
	 	columnList=columnList.substring(0, length-2);
         }
	}
        //System.out.println(columnPercent+columnList);
   %>
	<td width="<%=columnPercent%>"><div align="center"><strong><%=columnList%></strong></div></td>
   <% }%>
  </tr>
  <%
   //��0��Ԫ���Ǽ�¼�������������������ݴ�1��ʼ
    for (int i=1;i<vResult.size();i++) {
      Vector vResultRow=new Vector();
      vResultRow=(Vector)vResult.elementAt(i);	//������ȡ������ֶ���ʾ
  %>
  <tr class="content-bg">
  	<%
  	  for (int j=0;j<vTableColumn.size();j++) {
      		contentList =(String)vResultRow.elementAt(j);
      		if(contentList==null) contentList="";
  	%>
    <td><a style="cursor:hand;" onclick="javacript:openList()"><%=contentList%></a></td>
    <% }%>
    </tr>
    <%} %>
 <tr class="headline-bg">
    <td colspan="1" align="left">��<%=pageNo%>ҳ/��<%=pageCount%>ҳ����<%=count%>����¼��</td>
    <td colspan="<%=columnSize-1%>" align="right">
    <%if (pageNo==1){
      out.print("��ҳ ��һҳ");
      }else{
  %>
  <a href="javascript:toUrl('1','<%=pageSize%>','<%=sTableName%>');" >��ҳ</a>  <a  href="javascript:toUrl('<%=pageNo-1%>','<%=pageSize%>','<%=sTableName%>');">��һҳ</a>
  <% } %>
  <% if (pageNo+1>pageCount){
       out.print ("��һҳ βҳ");
     }else{
  %>
  <a  href="javascript:toUrl('<%=pageNo+1%>','<%=pageSize%>','<%=sTableName%>');">��һҳ</a> <a  href="javascript:toUrl('<%=pageCount%>','<%=pageSize%>','<%=sTableName%>');">βҳ</a>
  <% }
  %>
    </td>
    </tr>
</table>
<form name="frmQueryList">
<input type="hidden" name="actionFlag" value="">
</form>
<h1> </h1>
<%} else
	out.print("���� tableName ��Ϊ��");
%>
</body>
</html>

