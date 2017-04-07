<%@ page language="java"
	import="java.util.*,java.text.SimpleDateFormat,com.bitc.jk.xmis.util.Type,com.zhuozhengsoft.pageoffice.FileMakerCtrl,com.bitc.jk.xmis.util.WebUtil,com.bitc.jk.xmis.util.WebKeys,com.zhuozhengsoft.pageoffice.*,com.zhuozhengsoft.pageoffice.wordwriter.*;"
	pageEncoding="gb2312"%>
<%@ taglib uri="http://java.pageoffice.cn" prefix="po"%>
<%
	//******************************׿��PageOffice�����ʹ��*******************************
	FileMakerCtrl fmCtrl = new FileMakerCtrl(request);
	fmCtrl.setServerPage(request.getContextPath() + "/poserver.zz");

	String formId = Type.getString(request.getParameter("form_id"));
	String directPath = (String) getServletContext().getAttribute(
			WebKeys.Session_Application_Cfg_AttachedPath);// ��Ӳ���е�·��
	String basepath = request.getSession().getServletContext()
			.getRealPath("officialdocument");
	int document_type_id = Type.GetInt(request
			.getParameter("document_type_id"));
	WordDocument worddoc = new WordDocument();
	worddoc.setDisableWindowRightClick(true);
	//����Ҫ����word�ļ���λ���ֶ�������ǩ,��ǩ�����ԡ�PO_��Ϊǰ׺
	//��DataRegion��ֵ,ֵ����ʽΪ��"[word]word�ļ�·��[/word]��[excel]excel�ļ�·��[/excel]��[image]ͼƬ·��[/image]"

	//�������

	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	String sendYear = "";
	if (Type.getDateTime(request.getParameter("approved_datetime")) != null) {
		String direTime = sdf.format(Type.getDateTime(request
				.getParameter("approved_datetime")));
		sendYear = direTime.substring(0, 4);
	}
	
	String ext_name = Type.getString(request.getParameter("external_name"));
	if(!"".equals(ext_name)){
		DataRegion external_name = worddoc.openDataRegion("PO_ext_name");
		external_name.setValue(ext_name+"��");
	}

	DataRegion year = worddoc.openDataRegion("PO_Year");
	year.setValue(sendYear);

	DataTag title = worddoc.openDataTag("[����]");
	title.setValue(Type.getString(request.getParameter("title")));
	String file_flag = Type
			.getString(request.getParameter("file_flag")).trim();
	DataRegion flag = worddoc.openDataRegion("PO_FLAG");
	flag.setValue(file_flag);

	String app_direc_leader_name = Type.getString(request
			.getParameter("app_direc_leader_name"));
	DataRegion leader_name = worddoc.openDataRegion("PO_leader_name");
	leader_name.setValue(app_direc_leader_name);
	DataTag attFile = worddoc.openDataTag("[����]");
	if ("".equals(Type.getString(request.getParameter("attFile")))) {
		attFile.setValue("");
	} else {
		attFile.setValue("������"
				+ Type.getString(request.getParameter("attFile")));
	}
	//����
	DataRegion data1 = worddoc.openDataRegion("PO_ZW");
	data1.setValue("[word]" + directPath + "����" + formId
			+ ".doc[/word]");

	String path = request.getSession().getServletContext()
			.getRealPath("officialdocument");
	fmCtrl.setSaveFilePage("SaveFile.jsp?formId=" + formId);//��Ҫ�����ļ������б���
	fmCtrl.setWriter(worddoc);
	fmCtrl.setJsFunction_OnProgressComplete("OnProgressComplete()");
	if ("����բ��".equals(file_flag)) {
		if (document_type_id == 1) {
			fmCtrl.fillDocumentAs(path + "\\xingwen.doc",
					DocumentOpenType.Word, "����" + formId + ".doc");
		} else if (document_type_id == 3) {
			fmCtrl.fillDocumentAs(path + "\\xingwen3.doc",
					DocumentOpenType.Word, "����" + formId + ".doc");
		}
	} else if ("����բ��".equals(file_flag)) {
		if (document_type_id == 1) {
			fmCtrl.fillDocumentAs(path + "\\xingwen4.doc",
					DocumentOpenType.Word, "����" + formId + ".doc");
		} else if (document_type_id == 3) {
			fmCtrl.fillDocumentAs(path + "\\xingwen2.doc",
					DocumentOpenType.Word, "����" + formId + ".doc");
		}
	}

	fmCtrl.setTagId("FileMakerCtrl1"); //���б���
%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>�ϳ�����</title>
</head>
<script language="javascript" type="text/javascript">
	function OnProgressComplete() {
		alert("�������ɳɹ���");
		window.close();
	}
</script>
<body>
<form id="form1">
<div style="width: auto; height: 700px;"><!--**************   PageOffice �ͻ��˴��뿪ʼ    ************************-->
<po:FileMakerCtrl id="FileMakerCtrl1" /> <!--**************   PageOffice �ͻ��˴������    ************************-->
</div>
</form>
<h3>���ںϳ����ģ����Եȡ�����</h3>
</body>
</html>