<%@ page contentType="text/html; charset=GBK" %>
<jsp:useBean id="UserConform" scope="page" class="net.kingsoft.user.UserConform"/>
<%

	String mUserName;
	mUserName=request.getParameter("pUserName");

	if(mUserName!=null && !mUserName.equals("") )
		UserConform.delUser(mUserName);
		
%>
<script>
	alert("\���˺��Ѿ�ɾ���ɹ���");
	window.returnValue = "ok";
	window.close();
</script>
