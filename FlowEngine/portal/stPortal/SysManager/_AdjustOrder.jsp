<%@ page contentType="text/html; charset=gb2312" errorPage="../include/error.jsp"%>
<%@ page language="java" import="java.util.*" %>
<jsp:useBean id="oSys" scope="session" class="jbportal.classServiceBean" />
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
	//��������
    int sReturn = -1;
	String m_SQL=request.getParameter("HOrder");
    if (m_SQL == null)
      m_SQL = "";
	sReturn = oManager.AdjustModuOrder(m_SQL);
	if (sReturn >=0){
    }
	else{
      out.println("htmRenderErrorMessage(\"����������������ˢ�º����ԣ�\",\"\")");
    }
%>