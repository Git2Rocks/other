<%@ page language="java"
	import="java.util.*,com.bitc.jk.xmis.util.WebKeys,com.bitc.jk.xmis.util.Type,com.zhuozhengsoft.pageoffice.*,com.zhuozhengsoft.pageoffice.wordwriter.*"
	pageEncoding="gb2312"%>
<%@page import="com.bitc.jk.xmis.util.WebUtil"%>
<%@ taglib uri="http://java.pageoffice.cn" prefix="po"%>
<%
	
%>
<%
	//******************************׿��PageOffice�����ʹ��*******************************
	String path = request.getContextPath();
	PageOfficeCtrl poCtrl1 = new PageOfficeCtrl(request);
	poCtrl1.setServerPage(request.getContextPath() + "/poserver.zz"); //���б���
	//���ز˵���
	poCtrl1.setTitlebar(false); //���ر�����
	poCtrl1.setMenubar(false); //���ز˵���
	//if (!(Type.getInteger(request.getParameter("zw")) == 1)) {
		poCtrl1.setCustomToolbar(false);//�����Զ��幤����
	//}
	poCtrl1.setOfficeToolbars(true);//����Office������
	//
	//poCtrl1.addCustomToolButton("����","Save()",1);

	//poCtrl1.addCustomToolButton("�Ӹ�ӡ��", "InsertSeal()", 2);
	//poCtrl1.addCustomToolButton("ǩ��", "AddHandSign()", 3);
	//poCtrl1.addCustomToolButton("��֤ӡ��", "VerifySeal()", 5);
	//poCtrl1.addCustomToolButton("�޸�����", "ChangePsw()", 0);
	//poCtrl1.addCustomToolButton("����ӡ��", "EditHandSign()", 9);
	//���ñ���ҳ��
	poCtrl1.setSaveFilePage("SaveFile.jsp");
	//��Word�ļ�
	String directPath = (String) getServletContext().getAttribute(
			WebKeys.Session_Application_Cfg_AttachedPath);// ��Ӳ���е�·��
	if (Type.getInteger(request.getParameter("zw")) == 1) {
		poCtrl1.webOpen(
				directPath
						+ "����"
						+ Type.getString(request
								.getParameter("form_id")) + ".doc",
				OpenModeType.docNormalEdit, WebUtil
						.getCurrentEmployee().getUserName());
	} else {
		poCtrl1.webOpen(
				directPath
						+ "����"
						+ Type.getString(request
								.getParameter("form_id")) + ".doc",
				OpenModeType.docNormalEdit, WebUtil
						.getCurrentEmployee().getUserName());
	}
	poCtrl1.setTagId("PageOfficeCtrl1"); //���б���
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title></title>
<link href="../images/csstg.css" rel="stylesheet" type="text/css" />

</head>
<body>
<form id="form2"></form>
<!-- ****************************PageOffice ����ͻ��˱��************************************* -->
<script type="text/javascript">
	function Save() {
		document.getElementById("PageOfficeCtrl1").WebSave();
	}
	function InsertSeal() {
		try {
			document.getElementById("PageOfficeCtrl1").ZoomSeal.AddSeal();
		} catch (e) {
		}
	}
	function AddHandSign() {
		document.getElementById("PageOfficeCtrl1").ZoomSeal.AddHandSign();
	}
	function VerifySeal() {
		document.getElementById("PageOfficeCtrl1").ZoomSeal.VerifySeal();
	}
	function ChangePsw() {
		document.getElementById("PageOfficeCtrl1").ZoomSeal.ShowSettingsBox();
	}
	function EditHandSign() {
		window.location = "../adminseal.do";
	}
</script>
<!-- ****************************PageOffice ����ͻ��˱�̽���************************************* -->
<po:PageOfficeCtrl id="PageOfficeCtrl1" />
</body>
</html>
