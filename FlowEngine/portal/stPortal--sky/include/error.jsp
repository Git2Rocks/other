<%@ page contentType="text/html; charset=gb2312" errorPage="../include/error.jsp"%>
<%@ page import="java.io.*" isErrorPage="true" %>
<HTML>
<HEAD>
  <TITLE>Error!</TITLE>
</HEAD>
<BODY>

<H3>����: <%=exception%></H3>
<H3>��Ϣ: <%=exception.getMessage()%></H3>
<H3>������Ϣ: <%=exception.getLocalizedMessage()%></H3>
  <%
  StringWriter errorWriter = new StringWriter ();
  PrintWriter errorStream = new PrintWriter (errorWriter);
  exception.printStackTrace (errorStream);
  %>
  <P>��ջ����:
  <BLOCKQUOTE>
    <PRE><%=errorWriter%></PRE>
  </BLOCKQUOTE>
</BODY>
</HTML>
