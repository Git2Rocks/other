<%@ page contentType="text/html; charset=gb2312" errorPage="../../include/error.jsp"%>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
	oManager.RestoreModuleSetting(); //�ָ�ģ��ȱʡ����
    response.sendRedirect("ModuleMain.jsp");
%>
