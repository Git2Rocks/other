<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="flowengineweb.*" %>
<%@ page import="flowengineforjava.util.BaseToolJB" %>
<%@ page import="java.util.Hashtable" %>
<%@ page import="flowengineforjava.util.RecordSet" %>
<%@ page import="flowengineforjava.structure.FormControlHtmlData" %>

<%
  //ȡ��·������
  String sCommonPath="",sPublicPath="";
  sCommonPath = SysPara.getCommonPath(request);
  sPublicPath = SysPara.getPublicPath(request);
%>

<script type="text/javascript" src="<%=sCommonPath%>Include/Common.js"></script>
<%
  //ǿ��ҳ��ˢ��
  response.setHeader("Pragma","No-cache");
  response.setHeader("Cache-Control","no-cache");
  response.setDateHeader("Expires", 0);
  //myFlowEngine.initialize(pageContext,false);
  long flowInid = 21104;//Integer.parseInt(request.getParameter("flowInid"));
  long stepInid = -1;//Integer.parseInt(request.getParameter("stepInid"));
  String title="",formula="";
  RecordSet rs=null;
  //�Ƿ��д�ӡ���ģ��,ȱʡΪû��.
  boolean hasTemplet=false;
  try{
  	BaseToolJB  baseTool=new BaseToolJB("dx13107");

    FormControlHtmlData fchd = baseTool.getFormLib().getFormControlHtmlData(flowInid,stepInid);
    title =fchd.getTitle();
    formula =fchd.getFormula();
    rs =fchd.getControlHtmlData();
    hasTemplet=true;
    //�����ģ��Ļ���ʹ��ģ��������html,���û������ģ��,����ʹ�þɵķ�ʽ����ʾ.
    if(fchd.hasTemplet()){
      out.print(fchd.toHTML());
    }
    else{
      %>
      <html>
      <head>
      <meta http-equiv="Content-Type" content="text/html; charset=GBK">
        <link rel="stylesheet" type="text/css" href="<%=sCommonPath%>Css/AdvancedPrint.css">
      </head>
      <body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0" scroll="auto" style="background-color:white;">
      <table width="85%" border="0" cellspacing="0" cellpadding="0" align="center">
        <tr>
          <td align="left" valign="bottom" class="PrintEx_Title1">
            <%=formula%>
          </td>
        </tr>
        <% if (title != null && !title.equals("")){ %>
        <tr>
          <td align="center" valign="middle" class="PrintEx_Title2">
            <%=title%>
          </td>
        </tr>
        <% } %>
        <tr>
          <td width="100%">
            <table width="100%" border="1" cellspacing="0" cellpadding="0" class="outline" bordercolor="#007CA6">
              <tr>
                <td class="content_title" width="12%">����</td>
                <td class="content_title" width="88%">����</td>
              </tr>
              <%while(rs.next()){
              String fieldDesc = (String)rs.getObject("fieldDesc");
              String fieldValue = (String)rs.getObject("fieldValue");
              if(fieldDesc == null || fieldDesc.equals(""))
              fieldDesc = "&nbsp;";
              if(fieldValue == null || fieldValue.equals(""))
              fieldValue = "&nbsp;";
              %>
              <tr>
                <td class="content_td_left" width="12%"><%=fieldDesc%></td>
                <td class="content_td_right" width="88%"><%=fieldValue%></td>
              </tr>
              <%}%>
            </table>
</td>
        </tr>
      </table>
      </body>
      </html>
      <%
      }
    }catch(Exception e){
      e.printStackTrace();
    //out.println("<script type='text/javascript'>AlertWindow('"+sPublicPath+"','����ӡʧ�ܣ�');top.close();</script>");
    out.println("<script type='text/javascript'>alert('"+sPublicPath+"-����ӡʧ�ܣ�');</script>");
    return;
  }
%>
