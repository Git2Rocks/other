<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="baseserverjb.BaseServerClient,com.minstone.util.Base64Encoder" %>
<%@ page import="com.minstone.util.PublicLib" %>
<%@ page import="com.minstone.util.SQLPara" %>
<%@ page import="sun.jdbc.rowset.CachedRowSet" %>
<%@ page import="java.sql.*" %>
<%
  //��ֹʹ��cached
  //��ҳ��һ���ڹ�������ͳһ���칦�ܲ���ʹ�ã�����getRemoteUser�������ܵ���ʹ�ã�����ᱨ�û�������
  response.setHeader("Pragma", "No-cache");
  response.setHeader("Cache-Control", "no-cache");
  response.setDateHeader("Expires", 0);
  String userCode = request.getParameter("user_code"); //ϵͳ���ɵõ���ǰ��¼�û�
  if (userCode == null) userCode = "";
  int pageNo  = Integer.parseInt(request.getParameter("page"));
  if(pageNo==0) pageNo=1;
  //System.out.println("��"+pageNo +"ҳ");
%>
<%
  
  String currentUser = userCode;//request.getRemoteUser();
  if (currentUser == null) currentUser = "";
  String userName = "Web";
  //System.out.println("��ǰ�û���" + currentUser);

  int pageSize = 5;
  //pageNo = 1;//��һҳ
  long recordCount = 0;
  int isLastPage = 1;  //�����Ƿ������ҳ/��ҳ�İ�ť
  long readFlag = -1;

  String sTYPE = "";
  String sTITLE = "";
  String sSENDER = "";
  String sSENDTIME = "";
  String sSTATUS = "";
  String sURL = "";
  String sSYSTAG = "";
  String sMODAL = "";

  String procid = "";
  String entrid = "";
  String dataid = "";

  Connection cn = null;
  CachedRowSet rs = null;
  BaseServerClient bsc=new BaseServerClient(currentUser);
  userName=bsc.getFramework().getUserNameFromWizard(currentUser);//ȡ�û���������
  try {
    String sql = "SELECT PROC_NAME AS TITLE, ENTR_SEND AS SENDER, CONVERT(varchar(10),ENTR_STAR,120)  AS SENDTIME, "
            + "PROC_ID AS proc_id, ENTR_ID AS entr_id, DATA_REFC AS data_id,ACTI_NAME AS STATUS "
            + " FROM RECI_ENTR_ALL "
            + " WHERE PIIS_TERM = 0 "
            + " 	AND ( ENTR_STAT = 1 or ENTR_STAT = 2 ) "
            + " 	AND ENTR_ALCO = 0 "
            + " 	AND 1=1 "
            + " 	AND ( replace(ENTR_RECI,' ' ,'') ='" + userName + "' "
            + " 	  OR EXISTS ( SELECT 1 FROM USER_DATA , SYS_USER "
            + " 	   WHERE RECI_ENTR_ALL.DATA_REFC = USER_DATA.DATA_ID "
            + " 	   AND PROX_USER IN ('" + currentUser + "') "
            + " 	   AND USER_DATA.USER_CODE = SYS_USER.USER_CODE "
            + " 	   AND RECI_ENTR_ALL.ENTR_RECI = SYS_USER.USER_NAME) ) "
            + " 	ORDER BY SENDTIME DESC ,PROC_ID DESC , ENTR_ID DESC ";

    //System.out.println(userName+"sql���:"+sql);
    cn =bsc.getDataSource("exoa_ds").getConnection();
    //��ѯ�����б�
    rs = bsc.getRowSet(sql,cn,new SQLPara());
    recordCount=rs.size();
    rs.beforeFirst();
    int bookMark=(pageNo-1) * pageSize ;
     int intPageCount =(int) Math.ceil((recordCount+1)/(1.0d*pageSize));
     //System.out.println("pageNo:"+pageNo);
     //System.out.println("intPageCount:"+intPageCount);
     if(pageNo>=intPageCount){
       pageNo = intPageCount;
       isLastPage=1;
     }
     else
    	isLastPage = 0;
    	
     //System.out.println("pageSize:"+pageSize);
     //System.out.println("recordCount:"+recordCount);
     if(recordCount<=pageSize) isLastPage = 1;  //�����¼�������ڵ���һҳ������������һҳ����������
%>
    <?xml version="1.0" encoding="GB2312"?>
		<WORKLIST>
		  <PAGE><%=pageNo%></PAGE>
		  <TOTALRECORD><%=recordCount%></TOTALRECORD>
		  <ISLASTPAGE><%=isLastPage%></ISLASTPAGE>
  <%
    if(bookMark <= recordCount){
      if(pageNo >1) rs.absolute(bookMark);
      //System.out.println("��λ"+bookMark);
      int i=0;
      while (rs.next() && i<pageSize) {
      i++;
      //System.out.println("next��"+i);
    	//ͨ��odbcȡ���ݣ�һ��Ҫ��sql��˳��һ�����������
      sTITLE = rs.getString("TITLE");
      if (sTITLE == null) sTITLE = "";
      sTITLE = Base64Encoder.encode(sTITLE.getBytes());

      sSENDER =rs.getString("SENDER");
      if (sSENDER == null) sSENDER = "";
      sSENDER = Base64Encoder.encode(sSENDER.getBytes());

      sSENDTIME=rs.getString("SENDTIME");
      if (sSENDTIME == null) sSENDTIME = "";

      procid = rs.getString("proc_id");
      if (procid == null) procid = "";

      entrid = rs.getString("entr_id");
      if (entrid == null) entrid = "";

      dataid = rs.getString("data_id");
      if (dataid == null) dataid = "";

      sSTATUS=rs.getString("STATUS");
      if (sSTATUS == null) sSTATUS = "";
      //sSTATUS=new String(sSTATUS.getBytes("ISO8859-1"),"GBK");

      sURL = "/exoa2000/exflow/flowitem/default2.asp?userid=" + currentUser + "&amp;procid=" + procid + "&amp;entrid=" + entrid + "&amp;dataid=" + dataid;

  %>
  <LISTITEM>
    <TYPE>һ��</TYPE>
    <TITLE><%=sTITLE%></TITLE>
    <SENDER><%=sSENDER%></SENDER>
    <SENDTIME><%=sSENDTIME%></SENDTIME>
    <STATUS><%=sSTATUS%></STATUS>
    <URL><%=sURL%></URL>
    <SYSTAG>��չOA</SYSTAG>
    <MODAL>0</MODAL>
    <ISNOTICE>0</ISNOTICE>
  </LISTITEM>
  <%
    }
   }
  %>
</WORKLIST>
<%
  }
  catch (Exception e) {
    e.printStackTrace();
  }
  finally {
    PublicLib.closeConnection(cn);
    cn=null;
  }
%>
