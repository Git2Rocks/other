<%@ page contentType="text/html; charset=GBK" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>Redister-Infomation</title>
<link href="common/style.css" rel="stylesheet" type="text/css">
</head>

<body>
<%
String m_result;
m_result=request.getParameter("regReturn");
%>
<table width="400"  border="0" align="center" cellpadding="0" cellspacing="0" style="BORDER-COLLAPSE: collapse">
  <tr>
    <td colspan="2"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
      <TR>
            <TD vAlign=top width=7><IMG height=22 alt="" src="images/rnavleft.gif" width=10></TD>
            <TD width="100%" class=SubTitleRed2><img src="images/arrow_write.gif" width="15" height="15" border="0" align="absmiddle"> ע����Ϣ</TD>
            <TD vAlign=top width=7><IMG height=22 alt="" src="images/rnavright.gif" width=10></TD>
        </TR>
    </table></td>
  </tr>

  <tr align="left">
    <td height="160" colspan="2" align="center" style="BORDER: #cccccc 1px solid; COLOR: black; BACKGROUND-COLOR: #f1f1f1">
    <%
    	if(m_result.equals("0"))
    	{
    %>
    ע��ɹ���
    <%
    	}
    	else if(m_result.equals("51"))
    	{
    %>
	���ݿ����
	<%
		}
		else if(m_result.equals("52"))
		{
	%>
	������û�������
	<%
		}
		else if(m_result.equals("53"))
		{
	%>
	���ݿ��������
	<%
		}
		else if(m_result.equals("120"))
		{
	%>
	�û�����
	<%
		}
		else if(m_result.equals("126"))
		{
	%>
	��Ա�鲻���ڻ��ظ�
	<%
		}
		else if(m_result.equals("123"))
		{
	%>
	���֤������
	<%
		}
		else
		{
	%>
	δ֪����
	<%
		}
	%>
    </td>
  </tr>
  <tr align="left">
  <%
  	if(m_result.equals("0"))
    {
  %>
    <td height="30" colspan="2" align="center" style="BORDER: #cccccc 1px solid; COLOR: black; BACKGROUND-COLOR: #f1f1f1">������Ա����������Ϻ����Ϳ��Ե�¼���ύ����ѯ������������ <a href="/" target="_top">������ҳ��¼..</a></td>
  <%
  	}
  	else
  	{
  %>
    <td height="30" colspan="2" align="center" style="BORDER: #cccccc 1px solid; COLOR: black; BACKGROUND-COLOR: #f1f1f1"> <a href="register.jsp">����ע��..</a></td>
  <%
  	}
  %>
  </tr>
</table>

</body>
</html>
