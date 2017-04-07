<%@ page language="java"
	import="java.util.*,java.text.SimpleDateFormat,com.bitc.jk.xmis.util.Type,com.bitc.jk.xmis.util.WebUtil,com.bitc.jk.xmis.util.WebKeys,com.zhuozhengsoft.pageoffice.*"
	pageEncoding="gb2312"%>
<%@ taglib uri="http://java.pageoffice.cn" prefix="po"%>
<%
	//******************************׿��PageOffice�����ʹ��*******************************
	PageOfficeCtrl poCtrl1 = new PageOfficeCtrl(request);
	poCtrl1.setServerPage(request.getContextPath()+"/poserver.zz"); //���б���

	String directPath = (String) getServletContext().getAttribute(
			WebKeys.Session_Application_Cfg_AttachedPath) ;// ��Ӳ���е�·��
	String path = request.getSession().getServletContext().getRealPath("officialdocument");
	WordDocument worddoc = new WordDocument();
	//����Ҫ����word�ļ���λ���ֶ�������ǩ,��ǩ�����ԡ�PO_��Ϊǰ׺
	//��DataRegion��ֵ,ֵ����ʽΪ��"[word]word�ļ�·��[/word]��[excel]excel�ļ�·��[/excel]��[image]ͼƬ·��[/image]"
	
	
	//�������
	String formId = Type.getString(request.getParameter("form_id"));
		
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		 String appTime ="";
		 String deptTime="";
		 String specTime ="";
		 String direTime = "";
		 String sendYear ="";
		 String sendMonth ="";
		 String sendDay ="";
		 String appYear ="";
		 String appMonth ="";
		 String appDay ="";
		if(Type.getDateTime(request.getParameter("app_datetime")) !=null){
		  appTime = sdf.format(Type.getDateTime(request.getParameter("app_datetime")));
		  appYear = appTime.substring(0,4);
		  appMonth = ((Type.getDateTime(request.getParameter("app_datetime"))).getMonth()+1)+"";
		  appDay = (Type.getDateTime(request.getParameter("app_datetime"))).getDate()+"";
		}
		if(Type.getDateTime(request.getParameter("app_dept_approved_datetime"))!=null){
	      deptTime = sdf.format(Type.getDateTime(request.getParameter("app_dept_approved_datetime")));
		}
		if(Type.getDateTime(request.getParameter("app_spec_approved_datetime"))!=null){
		 specTime = sdf.format(Type.getDateTime(request.getParameter("app_spec_approved_datetime")));
		}
		if(Type.getDateTime(request.getParameter("app_direc_approved_datetime"))!=null){
		 direTime = sdf.format(Type.getDateTime(request.getParameter("app_direc_approved_datetime")));
		 sendYear = direTime.substring(0,4);
		 sendMonth = ((Type.getDateTime(request.getParameter("app_direc_approved_datetime"))).getMonth()+1)+"";
		 sendDay = (Type.getDateTime(request.getParameter("app_direc_approved_datetime"))).getDate()+"";
		}
	DataTag deptTag = worddoc.openDataTag("[��ǩ�쵼]");
	deptTag.setValue(Type.getString(request.getParameter("HQ_name")));
	
	DataTag spcTag = worddoc.openDataTag("[�ֹ��쵼]");
	spcTag.setValue(Type.getString(request.getParameter("app_spec_leader_name"))+ "           "+specTime);
	
	DataTag dirTag = worddoc.openDataTag("[�����쵼]");
	dirTag.setValue(Type.getString(request.getParameter("app_direc_leader_name"))+"           "+direTime);
	
	DataTag appUser = worddoc.openDataTag("[������]");
	appUser.setValue(Type.getString(request.getParameter("app_user_name")));
	
	DataTag summary = worddoc.openDataTag("[ժҪ]");
	summary.setValue(Type.getString(request.getParameter("summary")));
	
	DataTag attFile = worddoc.openDataTag("[����1]");
	attFile.setValue(Type.getString(request.getParameter("attFile")));
	
	DataTag external_name = worddoc.openDataTag("[���ͻ���]");
	external_name.setValue(Type.getString(request.getParameter("external_name")));
	
	
	//DataTag title = worddoc.openDataTag("[����]");
	//title.setValue(Type.getString(request.getParameter("title")));
	
	DataTag appyear = worddoc.openDataTag("[yyyy]");
	appyear.setValue(appYear);
	
	DataTag appmonth = worddoc.openDataTag("[mm]");
	appmonth.setValue(appMonth);
	
	DataTag appday = worddoc.openDataTag("[dd]");
	appday.setValue(appDay);
	
	DataTag sendyear = worddoc.openDataTag("[��]");
	sendyear.setValue(sendYear);
	
	DataTag sendmonth = worddoc.openDataTag("[��]");
	sendmonth.setValue(sendMonth);
	
	DataTag sendday = worddoc.openDataTag("[��]");
	sendday.setValue(sendDay);
	//����
	DataRegion data1 = worddoc.openDataRegion("PO_ZW");
	data1.setValue("[word]"+directPath+"����"+formId+".doc[/word]");
	poCtrl1.setWriter(worddoc);
	poCtrl1.setCaption("Ԥ�����");

	//���ز˵���
	poCtrl1.setMenubar(false);
	//�����Զ��幤����
	poCtrl1.setCustomToolbar(false);
	poCtrl1.setSaveFilePage("SaveShowFile.jsp");

	poCtrl1.webOpen(path+"\\document.doc", OpenModeType.docNormalEdit, WebUtil.getCurrentEmployee().getUserName());
	poCtrl1.setTagId("PageOfficeCtrl1"); //���б���
	
	
%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>��̨��̲���Word�ļ�����������</title>
	</head>
	<body>
		<form id="form1">
			<div style="width: auto; height: 700px;">
				<!--**************   PageOffice �ͻ��˴��뿪ʼ    ************************-->
				<po:PageOfficeCtrl id="PageOfficeCtrl1">
				</po:PageOfficeCtrl>
				<!--**************   PageOffice �ͻ��˴������    ************************-->
			</div>
		</form>
	</body>
</html>