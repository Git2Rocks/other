<%@ page contentType="text/html; charset=gb2312" %>
<%@ page language="java" errorPage="../include/error.jsp"%>
<HTML>
<HEAD>
<TITLE>ϵͳ����</TITLE>
</HEAD>
<%
	String m_modu_id=request.getParameter("modu_id");
%>
<!--ҳ������ start-->
  <frameset rows="*" cols="*,0" frameborder="1" BORDER="1" FRAMESPACING="1" BORDERCOLOR="#9999CC">
	<frame src="DragMine.jsp?modu_id=<%=m_modu_id%>" name="main" scrolling="YES">
	<frame src="" name="update" >
</frameset>
</HTML>

