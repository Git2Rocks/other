<%@ page contentType="text/html; charset=gb2312" errorPage="../include/error.jsp"%>
<jsp:useBean id="oManager" scope="session" class="jbportal.sysManagerBean" />
<%
	String m_Msg="";
    String m_partLayout = request.getParameter("partLayout");
	//�õ�����Ĳ���
	String m_modu_id = request.getParameter("modu_id");
    if(m_modu_id==null)
        m_modu_id = "";
	//���ݴ��������д��Ӧ��SQL���
	int sReturn = oManager.UpdatePartLayout(m_partLayout);
	response.sendRedirect("DragMine.jsp?modu_id=" + m_modu_id);
%>