<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="com.minstone.report.ReportBean,com.minstone.util.database.RecordSetObject" %>
<%@ page import="com.minstone.util.Base64Encoder" %>
<html>
<head>
<title>
ҵ�񱨱���
</title>
</head>
<link href="../Common/Toolbar/Css/ToolBar.css" type="text/css" rel="stylesheet">
<link rel="stylesheet" type="text/css" href="../Common/Css/Public.css">
<link rel="stylesheet" type="text/css" href="../Common/Css/Query.css">
<link rel="stylesheet" type="text/css" href="../Common/ToolBar/Css/ToolBar.css">
<link rel="stylesheet" type="text/css" href="../Common/Css/Calendar.css">
<%!
  public String formatDate(String str){
    java.util.StringTokenizer stk = new java.util.StringTokenizer(str,"-");
    String year  = "";
    String month = "";
    String day   ="";
    int temp = 0;
    while (stk.hasMoreTokens()){
      year = stk.nextToken();
      month = stk.nextToken();
      temp = Integer.parseInt(month);
      if (temp>0&&temp<10)
        month = "0"+temp;
      day = stk.nextToken();
      temp = Integer.parseInt(day);
      if (temp>0&&temp<10)
        day = "0"+temp;
    }
    return year+"-"+month+"-"+day;
  }
%>
<%
  String sAction=request.getParameter("actionType");
  if(sAction==null) sAction="";
  if(sAction.equals("")){
    String sType=request.getParameter("iType");
    String sTypeDesc=request.getParameter("type_desc");
    String sReportCode=request.getParameter("rpt_code");
    String currentUser=request.getRemoteUser();
    if(sType==null) sType="-2";
    int iType=Integer.parseInt(sType);
    ReportBean reportBean=new ReportBean(currentUser);
    RecordSetObject rsoReportList=reportBean.queryReportListByType(iType);
%>
<script language="javascript" src="../Common/Include/QueryList.js"></script>
<script language="javascript" src="../Common/Include/Common.js"></script>
<script language="javascript" src="../Common/Include/Calendar.js"></script>
<script language="javascript" src="../Common/Include/i_CheckInput.js"></script>
<script language="javascript" src="../Common/ToolBar/Include/WebToolBar.js"></script>
<script language="javascript">
  function openHtmlReport(rpt_code){
    //window.open(window.open("/report/genreport?aType=HTML&aRetcodeOrName="+rpt_code+"&isOpenByCode=1&aWhereClause=IDE9MQ==","",""))
    window.open("/report/genreport?aType=HTML&aRetcodeOrName="+rpt_code+"&isOpenByCode=1","","")
  }
  function openExcelReport(rpt_code){
    window.open("/report/genreport?aType=XLS&aRetcodeOrName="+rpt_code+"&isOpenByCode=1","","")
  }
  function setDateSelect() {
    dNow = new Date();
    iScrap = dNow.getFullYear();
    for (i=0; i<60; i++)
    {
      objNewOpt = document.createElement("OPTION");
      objNewOpt.text = (iScrap - i);
      objNewOpt.value = (iScrap - i);
      if(i==1) objNewOpt.selected=true;
      queryInputForm.year.options.add(objNewOpt);
    }
  }
  function openReport(){
    var iGenType=getRadioSelectedValue("genType");
    if(iGenType=="1")
      openExcelReport("<%=sReportCode%>");
    else
      openHtmlReport("<%=sReportCode%>");
  }
  function getRadioSelectedValue(name){
    var radios=document.all.item(name);
    var oValue=null;
    if(radios!=null){
      if(radios.length>0){
        for(i=0;i<radios.length;i++){
          if(radios[i].checked){
            oValue=radios[i].value;
            break;
          }
        }
      }
      else{
        if(radios.checked)
          oValue=radios.value;
      }
    }
    return oValue;
  }
  function changeShowTypeStatus(){
    var oValue=getRadioSelectedValue("showType");
    if(oValue!=null && oValue=="byyearmonth"){
      document.all.item("fromDate").disabled=true;
      document.all.item("toDate").disabled=true;
      document.all.item("year").disabled=false;
      document.all.item("threemonths").disabled=false;
      document.all.item("month").disabled=false;
    }
    else{
      document.all.item("year").disabled=true;
      document.all.item("threemonths").disabled=true;
      document.all.item("month").disabled=true;
      document.all.item("fromDate").disabled=false;
      document.all.item("toDate").disabled=false;
    }
  }
  function selectAllArea(){
    var i=0;
    if(document.all.item("cb14").checked){
      var oCbs=document.all.item("cb");
      for(i=0;i<oCbs.length;i++)
        oCbs(i).disabled=true;
    }
    else{
      var oCbs=document.all.item("cb");
      for(i=0;i<oCbs.length;i++)
        oCbs(i).disabled=false;
    }
  }
</script>
<style>
A{
  color:blue;
}
A.report_link:link
{
    FONT-WEIGHT: normal;
    FONT-SIZE: 1em;
    CURSOR: hand;
    COLOR: blue;
    FONT-FAMILY: verdana;
    TEXT-DECORATION: none
}
A.report_link:hover
{
    FONT-WEIGHT: normal;
    FONT-SIZE: 1em;
    CURSOR: hand;
    COLOR: red;
    FONT-FAMILY: verdana;
    TEXT-DECORATION: none
}
A.report_link:visited
{
    FONT-WEIGHT: normal;
    FONT-SIZE: 1em;
    CURSOR: hand;
    COLOR: brown;
    FONT-FAMILY: verdana;
    TEXT-DECORATION: none
}
</style>
<body onload="Window_Onload()" leftmargin="0" rightmargin="0" bottommargin="0" topmargin="0">
  <form id="queryInputForm" action="operationreport.jsp" method="POST">
    <table width="60%" height="100%" border="0" align=center>
      <tr>
      <td width="100%" height="100%" align=center>
        <fieldset>
        <legend>�������ѯ������</legend>
          <table width="100%" border="1" cellspacing="0"  id="whereClause">
            <tr>
              <td align="right">
                <input type="radio" name="showType" checked value="byyearmonth" onclick="javascript:changeShowTypeStatus();">
                <B>���꼾��:</B>
              </td>
              <td>
              ���
              <select name="year">
                <option value=""></option>
              </select>
              ����
                <select name="threemonths">
                  <option value=0></option>
                  <option value=1>��һ����</option>
                  <option value=2>�ڶ�����</option>
                  <option value=3>��������</option>
                  <option value=4>���ļ���</option>
                </select>
              �·�
              <select name="month">
                <option value=0></option>
                <option value=01>һ��</option>
                <option value=02>����</option>
                <option value=03>����</option>
                <option value=04>����</option>
                <option value=05>����</option>
                <option value=06>����</option>
                <option value=07>����</option>
                <option value=08>����</option>
                <option value=09>����</option>
                <option value=10>ʮ��</option>
                <option value=11>ʮһ��</option>
                <option value=12>ʮ����</option>
              </select>
            </td>
            </tr>
            <tr>
              <td align="right">
                  <input type="radio" name="showType" value="bytime" onclick="javascript:changeShowTypeStatus();">
                <B>��ʱ���:</B>
              </td>
              <td>
                ��
                <input name="fromDate" type="text" disabled readonly size="15" onclick="javascript:calendar(fromDate);">
                ��
                <input name="toDate" type="text" disabled readonly size="15" onclick="javascript:calendar(toDate);">
              </td>
            </tr>
            <!--
            <tr>
            <td align="right"><B>ͳ�Ʒ���:</B>
            </td>
            <td align="center">
              <input type="radio" name="statType" checked value="0">�����ŷ��·�ͳ��
              <input type="radio" name="statType" value="1">���·ݷֲ���ͳ��
            </td>
            </tr>
            -->
            <tr>
              <td  align="right"><B>��ѡ�����:</B></td>
              <td style="vertical-align: middle">
                <input type="checkbox" name="cb" disabled value="1">�Ͼ�&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="2">����&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="3">��&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="4">����&nbsp;&nbsp;&nbsp;&nbsp;
                <br>
                <input type="checkbox" name="cb" disabled value="5">��ͨ&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="6">����&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="7">�γ�&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="8">����&nbsp;&nbsp;&nbsp;&nbsp;
                <br>
                <input type="checkbox" name="cb" disabled value="9">����&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="10">���Ƹ�&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="11">����&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="checkbox" name="cb" disabled value="12">̩��&nbsp;&nbsp;&nbsp;&nbsp;
                <br>
                <input type="checkbox" name="cb" disabled value="13">��Ǩ&nbsp;&nbsp;&nbsp;&nbsp;
                <br><input type="checkbox" name="cb14" checked value="14" onclick="javascript:selectAllArea();">���е���
              </td>
            </tr>
            <tr>
            <td align="right"><B>��������:</B>
            </td>
            <td align="center">
              <input type="radio" name="genType" checked value="0">HTML��ʽ
              <input type="radio" name="genType" value="1">EXCEL��ʽ
            </td>
            </tr>
            <tr>
            <td align="right" colspan=2>
              <br>
              <input type="hidden" name="actionType" value="openReport">
              <input type="hidden" name="rpt_code" value="<%=sReportCode%>">
              <input type="submit" class="btn1" name="btnOK" value="ȷ��" id="btnOK">&nbsp;
              <input type="reset" class="btn1" name="btnCancel" value="����" id="btnCancel">
              <br>
            </td>
            </tr>
            </table>
        </fieldset>
      </td>
      <tr>
    </table>
  </form>
</body>
</html>
<script language="javascript">
  setDateSelect();
</script>
<%}else{%>
<script language="javascript">
  function openHtmlReport(rpt_code,sWhere){
    window.parent.frames("ReportCenterMain").location="/report/genreport?aType=HTML&aRetcodeOrName="+rpt_code+"&isOpenByCode=1&aWhereClause="+sWhere;
  }
  function openExcelReport(rpt_code,sWhere){
    window.parent.frames("ReportCenterMain").location="/report/genreport?aType=XLS&aRetcodeOrName="+rpt_code+"&isOpenByCode=1&aWhereClause="+sWhere;
  }
</script>
<%
  String sShowType=request.getParameter("showType");
  String sRptCode=request.getParameter("rpt_code");
  String sGenType=request.getParameter("genType");
  String sAllArea=request.getParameter("cb14");
  String[] sAreas=request.getParameterValues("cb");
  String sYear=request.getParameter("year");
  String sMonth=request.getParameter("month");
  String sThreeMonths=request.getParameter("threemonths");
  String sFromDate=request.getParameter("fromDate");
  String sToDate=request.getParameter("toDate");
  String sWhere="(1=1)";
  if(sYear==null) sYear="";
  if(sMonth==null) sMonth="";
  if(sThreeMonths==null) sThreeMonths="";
  if(sFromDate==null) sFromDate="";
  if(sToDate==null) sToDate="";
  /*
  out.println("showType="+sShowType);
  out.println("rpt_code="+sRptCode);
  out.println("year="+sYear);
  out.println("month="+sMonth);
  out.println("threemonths="+sThreeMonths);
  out.println("sFromDate"+sFromDate);
  out.println("sToDate"+sToDate);
  out.println("genType="+sGenType);
  out.println("allArea="+sAllArea);
  */
  String timeCond="";
  if(sShowType.equals("byyearmonth")){
    if(!sYear.equals("")){
      if(!sThreeMonths.equals("") && !sThreeMonths.equals("0")){
        int iTM=Integer.parseInt(sThreeMonths);
        java.sql.Date startDate=null;
        java.sql.Date endDate=null;
        switch(iTM){
          case 1:
            timeCond="C_MYDATE>='"+sYear+"-01-01' and C_MYDATE<='"+sYear+"-03-31'";
            break;
          case 2:
            timeCond="C_MYDATE>='"+sYear+"-04-01' and C_MYDATE<='"+sYear+"-06-31'";
            break;
          case 3:
            timeCond="C_MYDATE>='"+sYear+"-07-01' and C_MYDATE<='"+sYear+"-09-31'";
            break;
          case 4:
            timeCond="C_MYDATE>='"+sYear+"-10-01' and C_MYDATE<='"+sYear+"-12-31'";
            break;
        }
      }
      else{
        if(!sMonth.equals("") && !sMonth.equals("0")){
          timeCond="C_MYDATE>='"+sYear+"-"+sMonth+"-01' and C_MYDATE<='"+sYear+"-"+sMonth+"-31'";
        }
        else{
          timeCond="C_MYDATE>='"+sYear+"-01-01' and C_MYDATE<='"+sYear+"-12-31'";
        }
      }
    }
  }
  else{
    if(!sFromDate.equals("")){
      timeCond="C_MYDATE>='"+formatDate(sFromDate)+"'";
    }
    if(!sToDate.equals("")){
      if(timeCond.equals("")){
        timeCond="C_MYDATE<='"+formatDate(sToDate)+"'";
      }
      else{
        timeCond=timeCond+" AND "+"C_MYDATE<='"+formatDate(sToDate)+"'";
      }
    }
  }
  String sCityIds="";
  if(sAllArea==null){
    if(sAreas!=null){
      sCityIds="cityid in(";
      for(int i=0;i<sAreas.length;i++){
        if(i==0)
          sCityIds+=sAreas[i];
        else
          sCityIds+=(","+sAreas[i]);
      }
      sCityIds+=")";
      if(sCityIds.equals("cityid in()")) sCityIds=" cityid='-1'";
    }
  }
  if(!timeCond.equals(""))
    sWhere=sWhere+" AND("+timeCond+")";
  if(!sCityIds.equals(""))
    sWhere=sWhere+" AND("+sCityIds+")";
  //out.println("CONDITION="+sWhere);
  Base64Encoder base64=new Base64Encoder();
  sWhere=base64.encode(sWhere);
  base64=null;
  //out.println("Encode_CONDITION="+sWhere);
%>
  <table width="100%" height="100%" border="0">
    <tr>
      <td align="center"><b><font color="red" size="6">�������ɱ������Ժ�......</font></b></td>
    </tr>
  </table>
<%
  out.println("<script language=\"javascript\">");
  if(sGenType.equals("0")){
    out.println("openHtmlReport('"+sRptCode+"','"+sWhere+"')");
  }
  else{
    out.println("openExcelReport('"+sRptCode+"','"+sWhere+"')");
  }
  out.println("</script>");
%>
  </body>
  </html>
<%}%>