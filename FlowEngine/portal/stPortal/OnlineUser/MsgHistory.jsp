<%@ page language="java" import="java.util.*" pageEncoding="GBK"%>

<%
    String rootpath= request.getContextPath();
%>
<html>
	<head>
		<title>��ʷ��¼</title>
		<LINK REL="stylesheet" HREF="<%=rootpath%>/stPortal/Common/Css/Public.css" TYPE="text/css">

		<link rel="stylesheet" type="text/css"
			href="<%=rootpath%>/stPortal/Common/Css/publicquery.css">
		<script language="javascript" src="<%=rootpath%>/stPortal/Common/Include/publicquery.js"></script>
		<script language="javascript" src="<%=rootpath%>/stPortal/Common/Include/Common.js"></script>
		<script type="text/javascript">
		function selDept(){
			openFrameList('dept','deptCode',3,0,1,2,'',1,1,1,'','','','',1);
		}
		
		function showDetail(){
		var sRecordID = getSingleSelected();
      	if (sRecordID==null) return;
     	 window.open("<%=rootpath%>/stPortal/portalSvl?service=msg&func=getbyid&sendid="+sRecordID,"","");
		}
		
		function search(){
		var dept=form1.dept.value;
		var sender=form1.sender.value;
		var content=form1.content.value;
		var spath="<%=rootpath%>/stPortal/portalSvl?service=msg&func=oldMsgs";
		if(dept!=null && dept!="") 
		spath+="&dept="+dept;
		if(sender!=null & sender!="") 
		spath+="&sender="+sender;
		if(content!=null && content!="") 
		spath+="&content="+content;
		window.location=spath;
		}
</script>
	</head>

	<body>
		<div id="choose">
			<form	action="" name="form1">
				<table width="80%" >
					<tr>
						<td align="left">
							�� �ţ�
							<input type="text" name="dept" value="" readonly>
							<input type="hidden" name="deptCode">
							&nbsp;
							<input type="button" value="ѡ��" name="choise"
								onclick="selDept();">
						</td>
						<td align="right">
							�û�����:
							<input type="text" name="sender">
						</td>
					</tr>
					<tr>
						<td>
							�� �ݣ�
							<input type="text" name="content">
						</td>
						&nbsp;
						<td>
							<input type="button"  onclick="search();" value="����">
						</td>
					</tr>
				</table>
			</form>
		</div>

		<div>
			<table width="100%" width="100%" align="center" border="0"
				cellspacing="0" cellpadding="0">
				<tr>
					<td>
					<%=request.getAttribute("DataList")%>

					</td>
				</tr>
				<tr>
					<td>
					<%=request.getAttribute("Navigation")%>
					</td>
				</tr>
			</table>
		</div>

	</body>
</html>
