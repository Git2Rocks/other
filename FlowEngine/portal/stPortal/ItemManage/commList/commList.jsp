<%@ page contentType="text/html; charset=GBK" %>
<%@ page errorPage="../errorPage.jsp" %>
<%@ page import="minstone.ItemManage.BaseDbManage"%>
<%@ page import="minstone.ItemManage.WorkItem"%>
<%@ page import="java.util.Vector,java.util.Hashtable,java.util.Enumeration"%>
<%@ page import="oamodule.publiclib.util.RecordSetObject"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��־�б�</title>
<link rel="stylesheet" type="text/css" href="../Common/Public.css">
</head>
<%
	request.setCharacterEncoding("GBK");
	BaseDbManage db=new BaseDbManage(request.getRemoteUser());
	String tableName="";//ͨ�õı���
	String condition=request.getRemoteUser();	//����
	String selCon="",txtCon="";
	String listName0="";	//��ʾ�ֶ�0��5��
	String listName1="";
	String listName2="";
	String listName3="";
	String listName4="";
	String listName5="";

	String actionFlag=request.getParameter("actionFlag");
	/*��ѯ������Ͽ�ʼ��������������������*/
	String mode = request.getParameter("mode");
        if (mode ==null)     mode="SEARCH";
        Hashtable hshParam =(Hashtable)session.getAttribute("SEARCH_PARAM");
        //��ѯ�ֶεı���
	selCon=request.getParameter("selCon");
	txtCon=request.getParameter("txtCon");
	condition=request.getParameter("condition");

        if(hshParam !=null){
            condition=(String)hshParam.get("condition");
            selCon=(String)hshParam.get("selCon");
            txtCon=(String)hshParam.get("txtCon");
            if(condition ==null) condition="";
	    if(selCon ==null) selCon="";
	    if(txtCon ==null) txtCon="";
            else {
            	selCon=txtCon.substring(0,1);//��hasȡ��Ҫȥ��ǰ���selCon
            	txtCon=txtCon.substring(1);//��hasȡ��Ҫȥ��ǰ���selCon

            	}
        }
        if("SEARCH".equals(mode)){
          condition=request.getParameter("condition");
          selCon=request.getParameter("selCon");
          txtCon=request.getParameter("txtCon");
          hshParam = new Hashtable();//Ҫ��ѯ���ֶ����֣��ֶ�ֵ
          if(condition!=null && !"".equals(condition)){
            hshParam.put("condition",condition);
            hshParam.put("creater",condition);
          }
	  if(txtCon!=null && !"".equals(txtCon) && selCon!=null && !"".equals(selCon))
            hshParam.put("txtCon",selCon+txtCon);

          session.setAttribute("SEARCH_PARAM", hshParam);
          response.sendRedirect("commList.jsp?mode=SHOW");//��ͻ��˷���һ����ʱ�ض�����Ϣ
          return;
        }
	/*��ѯ������Ͻ�����������������������*/

	//ÿҳ����Ϊ10��
	String sPageSize = request.getParameter("pagesize");
	if(sPageSize==null) sPageSize="0";
	int pageSize=0;
	pageSize=Integer.parseInt(sPageSize);

	if(actionFlag==null) actionFlag="";
	if(actionFlag.equals("DeleteFlag")){
        	db.delDocSeq(listName0);
    	}
        //RecordSetObject rsoLiverBed=db.getDocSeq();

        tableName=(String)request.getParameter("tableName");
        if(tableName==null || tableName.equals("")) tableName="V_YW_DSJ";
	//�ڼ�ҳ��ҳ��
        String pageStr=(String)request.getParameter("pageNo");
        if(pageStr==null || pageStr.equals(""))
          pageStr="1";
        int pageNo = java.lang.Integer.parseInt(pageStr);
        if(pageNo==0) pageNo=1;
        //ÿҳ����Ϊ10��
        if(pageSize==0)   pageSize = 10;
	//�õ�����������������������
        Vector vResult=new Vector();
        vResult=db.getCommList(pageNo,pageSize,tableName,hshParam);
        //���㷭ҳ����
        int count=Integer.parseInt((String)vResult.elementAt(0));
        int pageCount=(int)((count-1)/pageSize + 1);
%>
<script language="javascript" type="">

//��ѯ����ҳ������
function toUrl(num,pagesize,tableName){
    //alert(num);
    window.location.href="commList.jsp?mode=SHOW&tableName="+tableName+"&pageNo="+num+"&pagesize="+pagesize;
}
//��ӡ�б�
function doPrint(){
  document.frmPost.action="commList_Print.jsp";
  document.frmPost.target="_blank";
  document.frmPost.submit();
}
//��ѯ
function funSubmit(){
  document.frmPost.action="commList.jsp";
  document.frmPost.target="";
  document.frmPost.submit();
}
//��ղ�ѯ����
function doClean(){
  document.frmPost.selCon.value ="";
  document.frmPost.txtCon.value ="";
 }
</script>
<body bgcolor="#ffffff">
<form name="frmPost" action="commList.jsp" method="POST">
<table width="100%" class="TaskList_Table" border="0" cellspacing="0" cellpadding="0" align="center" style="padding-top:10px;padding-bottom:0px;padding-left:0px;">
  <tr><td valign="top" width="100%" class="searchUtil">
     <table width="100%" border="0" cellspacing="0" cellpadding="0" align="center">
          <tr>
            <td align="left">��ѡ����Ŀ������������ʽ����ʾ��һ�£�</td>
            <td align="left">
              <select name="selCon">
              	<option value="" <%="".equals(selCon)?"selected":""%> >��ѡ��...</option>
                <option value="0" <%="0".equals(selCon)?"selected":""%>>��������</option>
               	<option value="1" <%="1".equals(selCon)?"selected":""%>>��   ��</option>
		<option value="2" <%="2".equals(selCon)?"selected":""%>>��Ա����</option>
		<option value="3" <%="3".equals(selCon)?"selected":""%>>��ʼ����</option>
		<option value="4" <%="4".equals(selCon)?"selected":""%>>��������</option>
		<option value="5" <%="5".equals(selCon)?"selected":""%>>��Ҫ����</option>
              </select>
            </td>
            <td colspan="5" align="left">
            	 <input type="text" name="txtCon" value="<%=txtCon%>">
            </td>
          </tr>
          <tr>
            <td colspan="8" align="right"> <div align="right">
            	<input type="button" name="BtnSearch"  class="Btn_common" value="�� ѯ" onclick="javascript:funSubmit()">
		<input type="button" name="BtnPrint"  class="Btn_common" value="�� ӡ" onclick="javascript:doPrint();">
                <input type="button" name="clean"  class="Btn_common" value="�������" onclick="javascript:doClean()">
            </div></td>
          </tr>
        </table>
 </td></tr></table>
<table width="100%" cellpadding="3" cellspacing="1" class="boarder">
  <tr class="headline-bg">
    <td width="15%"><div align="center"><strong>��������</strong></div></td>
    <td width="15%"><div align="center"><strong>��   ��</strong></div></td>
    <td width="10%"><div align="center"><strong>��Ա����</strong></div></td>
    <td width="14%"><div align="center"><strong>��ʼ����</strong></div></td>
    <td width="14%"><div align="center"><strong>��������</strong></div></td>
    <td width="*"><div align="center"><strong>��Ҫ����</strong></div></td>
    <td width="5%">&nbsp;</td>
  </tr>
  <%
   //��0��Ԫ���Ǽ�¼�������������������ݴ�1��ʼ
    for (int i=1;i<vResult.size();i++) {
      Vector vResultRow=new Vector();
      vResultRow=(Vector)vResult.elementAt(i);	//������ȡ������ֶ���ʾ
      	listName0 =(String)vResultRow.elementAt(0);
      	listName1   =(String)vResultRow.elementAt(1);
      	listName2   =(String)vResultRow.elementAt(2);
        listName3   =(String)vResultRow.elementAt(3);
      	listName4   =(String)vResultRow.elementAt(4);
      	listName5=(String)vResultRow.elementAt(5);
      	if(listName0==null) listName0="";
	if(listName1==null) listName1="";
	if(listName2==null) listName2="";
	if(listName3==null) listName3="";
	if(listName4==null) listName4="";
	if(listName5==null) listName5="";
  %>
  <tr class="content-bg">
    <td><%=listName0%></td>
    <td><%=listName1%></td>
    <td><%=listName2%></td>
    <td><%=listName3%></td>
    <td><%=listName4%></td>
    <td><%=listName5%></td>
    <td>&nbsp;</td>
    <!--<td><div align="center"><img onclick=" " style="cursor:hand;" src="" width="16" height="16" alt=""></div></td>-->
  </tr>
   <%} %>
 <tr class="headline-bg">
    <td colspan="2" align="left">��<%=pageNo%>ҳ/��<%=pageCount%>ҳ����<%=count%>����¼��</td>
    <td colspan="6" align="right">
    <%if (pageNo==1){
      out.print("��ҳ ��һҳ");
      }else{
  %>
  <a href="javascript:toUrl('1','<%=pageSize%>','<%=tableName%>');" >��ҳ</a>  <a  href="javascript:toUrl('<%=pageNo-1%>','<%=pageSize%>','<%=tableName%>');">��һҳ</a>
  <% } %>
  <% if (pageNo+1>pageCount){
       out.print ("��һҳ βҳ");
     }else{
  %>
  <a  href="javascript:toUrl('<%=pageNo+1%>','<%=pageSize%>','<%=tableName%>');">��һҳ</a> <a  href="javascript:toUrl('<%=pageCount%>','<%=pageSize%>','<%=tableName%>');">βҳ</a>
  <% }
  %>
    </td>
    </tr>
</table>

<input type="hidden" name="listName0" value="">
<input type="hidden" name="condition" value="<%=condition%>">
<input type="hidden" name="mode" value="SEARCH">
<input type="hidden" name="actionFlag" value="">
</form>
<h1> </h1>
</body>
</html>

