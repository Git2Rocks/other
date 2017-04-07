package com.bitc.jk.xmis.web;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.Serializable;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.springframework.context.ApplicationContext;
import org.springframework.web.context.support.WebApplicationContextUtils;

import com.bitc.jk.xmis.model.AttachmentFile;
import com.bitc.jk.xmis.model.EmployeeObj;
import com.bitc.jk.xmis.service.impl.ContractServiceImpl;
import com.bitc.jk.xmis.service.impl.OrganizationServiceImpl;
import com.bitc.jk.xmis.util.Type;
import com.bitc.jk.xmis.util.WebKeys;
import com.jspsmart.upload.File;
import com.jspsmart.upload.SmartUpload;
import com.jspsmart.upload.SmartUploadException;

public class FileUploadDownload extends HttpServlet implements Serializable {

	private static Logger logger = Logger.getLogger(FileUploadDownload.class);

	private Object getServiceImplObj(int serviceName) {

		ApplicationContext context = WebApplicationContextUtils
				.getWebApplicationContext(getServletContext());

		Object serviceImplObj = new Object();
		switch (serviceName) {
		case WebKeys.ServiceImpl_Object_Organization:
			serviceImplObj = (OrganizationServiceImpl) context
					.getBean("organizationServiceImpl");
			break;
		case WebKeys.ServiceImpl_Object_Contract:
			serviceImplObj = (ContractServiceImpl) context
					.getBean("contractServiceImpl");
			break;
		}

		return serviceImplObj;
	}

	public void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		logger.info("-----------> HttpServlet &type="
				+ request.getParameter("type") );
		int type = Type.getInteger(request.getParameter("type")).intValue();
		switch (type) {
		case WebKeys.Upload_Application_UserPhoto_Type:
			doUploadUserPic(request, response);
			break;
		case WebKeys.Upload_Application_Download_Type:
			doDownloadAttachment(request, response);
			break;
		default:
			doUploadContractAttachment(request, response);
			break;
		}
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// this.doPost(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
	}

	public void doUploadUserPic(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		logger.info("---> pic upload..." + request.getParameter("userid"));

		String filePath = WebKeys.AttachmentWebPath;
		String messages = "";
		String messageTitle = "";
		String picURL = "";
		boolean flag = false;

		SmartUpload su = new SmartUpload();
		su.setCharSet("utf-8");
		long maxsize = 2 * 1024 * 1024; // ����ÿ���ϴ��ļ��Ĵ�С��Ϊ2MB
		String allowedFilesList = "jpg,gif,bmp,png";
		String denidFilesList = "exe,bat,jsp,htm,html,,";

		String photoAddr = "";

		try {
			EmployeeObj userDNA = (EmployeeObj) request.getSession()
					.getAttribute(WebKeys.Session_Attribute_Name_UserDNA);

			if (userDNA == null) {
				request.setAttribute(
						WebKeys.Request_Attribute_Name_LoginFailed,
						WebKeys.Request_Attribute_Name_ReLogin_Value);
				throw new Exception("Timeout!");
			} else {

				su.initialize(this.getServletConfig(), request, response); // ��ʼ��
				su.setMaxFileSize(maxsize); // �����ϴ��ļ��Ĵ�С
				su.setAllowedFilesList(allowedFilesList); // ���������ϴ����ļ�����
				su.setDeniedFilesList(denidFilesList);

				su.upload(); // �ϴ��ļ�

				File file = su.getFiles().getFile(0); // ��ȡ�ϴ����ļ�����Ϊֻ�ϴ���һ���ļ������Կ�ֱ�ӻ�ȡ

				if (!file.isMissing()) { // ���ѡ�����ļ�

					logger.info(file.getFileName());

					String now = new Date().getTime() + ""; // ��ȡ��ǰʱ�䲢��ʽ��Ϊ�ַ���
					// photoAddr = filePath + now + "." + file.getFileExt(); //
					// filePathֵ
					photoAddr = filePath + request.getParameter("userid") + "."
							+ file.getFileExt();

					file.saveAs(photoAddr, File.SAVEAS_VIRTUAL);
					messages = "ͼƬ�ϴ��ɹ�";
					messageTitle = "�ɹ�";

					picURL = WebKeys.AttachmentURL
							+ request.getParameter("userid") + "."
							+ file.getFileExt();

					OrganizationServiceImpl o = (OrganizationServiceImpl) this
							.getServiceImplObj(WebKeys.ServiceImpl_Object_Organization);

					if (o.doSaveUserPhoto(Integer.parseInt(request
							.getParameter("userid")), request
							.getParameter("userid")
							+ "." + file.getFileExt(), userDNA.getUserID()) > 0) {
						messages = "ͼƬ�ϴ��ɹ�";
						messageTitle = "�ɹ�";
						flag = true;
					} else {
						messages = "ͼƬ�ϴ�ʧ��";
						messageTitle = "ʧ��";
					}

				} else {
					messages = "��ѡ��Ҫ�ϴ����ļ���";
					messageTitle = "��ʾ";
				}
			}

		} catch (java.lang.SecurityException e) {
			messageTitle = "�ϴ��ļ�ʧ��";

			if (e.getMessage().indexOf("(1105)") > 0)
				messages = "ͼƬ��С��С��2M";
			else if (e.getMessage().indexOf("(1010)") > 0)
				messages = "ͼƬ����ֻ����Ϊ��JPG,GIF,BMP,PNG";
		} catch (SmartUploadException e) {
			messages = "�ϴ��ļ�ʧ�ܣ�";
			messageTitle = "�ϴ��ļ�ʧ��";
		} catch (Exception e) {
			e.printStackTrace();
			messages = "�ϴ��ļ�ʧ�ܣ������µ�¼���ٲ�����лл";
			messageTitle = "�ϴ��ļ�ʧ��";

		}

		logger.info(messages);

		// request.setAttribute("messages", messages);
		// request.getRequestDispatcher(forward).forward(request, response);

		// JSONObject jObject = new JSONObject();

		// try {
		// jObject.put("success", true);
		// } catch (Exception e) {
		// e.printStackTrace();
		// }
		// response.getWriter().print(jObject.toString());
		try {

			// ���سɹ���ʶ
			// response.getWriter().write(jObject.toString());
			response.setContentType("text/html; charset=utf-8");
			response.getWriter().write(
					"{success:" + String.valueOf(flag) + ",message:'"
							+ messages + "',messageTitle:'" + messageTitle
							+ "',picPath:'" + picURL + "'}");
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				response.getWriter().close();

			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

	public void doUploadContractAttachment(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		logger.info("---> attchment upload..." + request.getParameter("conID"));

		String directPath = request.getRealPath("/ ");

		logger.info(directPath);

		String messages = "";
		String messageTitle = "";
		int contractID=0;
		boolean flag = false;

		SmartUpload su = new SmartUpload();
		su.setCharSet("utf-8");

		long maxsize = 6 * 1024 * 1024; // ����ÿ���ϴ��ļ��Ĵ�С��Ϊ6MB
		String allowedFilesList = WebKeys.Upload_File_Type_Allowed_Contract;
		String denidFilesList = WebKeys.Upload_File_Type_Denfid_Contract;

		String photoAddr = "";

		try {
			EmployeeObj userDNA = (EmployeeObj) request.getSession()
					.getAttribute(WebKeys.Session_Attribute_Name_UserDNA);

			if (userDNA == null) {
				request.setAttribute(
						WebKeys.Request_Attribute_Name_LoginFailed,
						WebKeys.Request_Attribute_Name_ReLogin_Value);
				throw new Exception("Timeout!");
			} else {

				su.initialize(this.getServletConfig(), request, response); // ��ʼ��
				su.setMaxFileSize(maxsize); // �����ϴ��ļ��Ĵ�С
				su.setAllowedFilesList(allowedFilesList); // ���������ϴ����ļ�����
				su.setDeniedFilesList(denidFilesList);

				su.upload(); // �ϴ��ļ�
				
				File file = su.getFiles().getFile(0); // ��ȡ�ϴ����ļ�����Ϊֻ�ϴ���һ���ļ������Կ�ֱ�ӻ�ȡ

				if (!file.isMissing()) { // ���ѡ�����ļ�

					photoAddr = WebKeys.AttachmentWebPath + file.getFileName();
					file.saveAs(photoAddr, File.SAVEAS_VIRTUAL);
					java.io.File ioFile = new java.io.File(directPath.trim()
							+ photoAddr);
					InputStream inStream = new FileInputStream(ioFile);
					
					byte[] content = new byte[file.getSize()];

					AttachmentFile attFile = new AttachmentFile();
					attFile
							.setRefID(Type
									.GetInt(su.getRequest().getParameter("conID")));
					
					attFile.setRefType(Type.GetInt(su.getRequest().getParameter("conType")));
					attFile.setRefName(Type.getString(su.getRequest().getParameter("conName")));
					
					attFile.setFileName(file.getFileName());
					attFile.setFileSize(file.getSize());
					attFile.setContent(content);
					attFile.setUploadID(userDNA.getUserID());
					attFile.setFis(inStream);

					ContractServiceImpl contractService = (ContractServiceImpl) getServiceImplObj(WebKeys.ServiceImpl_Object_Contract);

					switch(Type.getInteger(request.getParameter("type")).intValue()){
					case WebKeys.Upload_Application_Contract_Type:
						contractID = contractService.doSaveAttachmentForContract(attFile);
						break;
					case WebKeys.Upload_Application_PaymentInfo_Type:
						contractID = contractService.doSaveAttachmentForPayment(attFile);
						break;

					case WebKeys.Upload_Application_InvoiceInfo_Type:
						contractID = contractService.doSaveAttachmentForInvoice(attFile);
						break;
					}
					
//					inStream.close();
					if (contractID > 0) {
						messages = "�����ϴ��ɹ�";
						messageTitle = "�ɹ�";
						flag = true;
					} else {
						messages = "�����ϴ�ʧ��";
						messageTitle = "ʧ��";
					}
				} else {
					messages = "��ѡ��Ҫ�ϴ����ļ���";
					messageTitle = "��ʾ";
				}

			}

		} catch (java.lang.SecurityException e) {
			e.printStackTrace();
			// messages = "��������ֻ����Ϊ��JPG, GIF, BMP, PNG����ͼƬ�ߴ�С��6M";
			messageTitle = "�ϴ��ļ�ʧ��";

			if (e.getMessage().indexOf("(1105)") > 0)
				messages = "������С��С��6M";
			else if (e.getMessage().indexOf("(1010)") > 0)
				messages = "��������ֻ����Ϊ��"+WebKeys.Upload_File_Type_Err_Msg_Contract;
			else if (e.getMessage().indexOf("(1015)") > 0)
				//messages = "�������Ͳ�����exe,bat,jsp,htm,html";
				messages = "��������ֻ����Ϊ��"+WebKeys.Upload_File_Type_Err_Msg_Contract;
			
		} catch (SmartUploadException e) {
			messages = "�ϴ��ļ�ʧ�ܣ�";
			messageTitle = "�ϴ��ļ�ʧ�ܣ������²�����";
		} catch (Exception e) {
			e.printStackTrace();
			messages = "�ϴ��ļ�ʧ�ܣ������µ�¼���ٲ�����лл";
			messageTitle = "�ϴ��ļ�ʧ��";

		}

		logger.info(messages);

		// request.setAttribute("messages", messages);
		// request.getRequestDispatcher(forward).forward(request, response);

		// JSONObject jObject = new JSONObject();

		// try {
		// jObject.put("success", true);
		// } catch (Exception e) {
		// e.printStackTrace();
		// }
		// response.getWriter().print(jObject.toString());
		try {

			// ���سɹ���ʶ
			// response.getWriter().write(jObject.toString());
			response.setContentType("text/html; charset=utf-8");
			response.getWriter().write(
					"{success:" + String.valueOf(flag) + ",message:'"
							+ messages + "',messageTitle:'" + messageTitle
							+ "',contractID:'" + String.valueOf(contractID) 
							//+ "', attTypeID:'" + String.valueOf(attTypeID)
							+ "'}");

		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				response.getWriter().close();

			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

	public void doDownloadAttachment(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		logger.info("---> attchment download..."
				+ request.getParameter("attID"));
		
		String directPath = request.getRealPath("/ ").trim() + WebKeys.AttachmentWebPath ;;
		
//		logger.info("start 1= " + new java.sql.Time(System.currentTimeMillis()).toString());
		String fileName = ((ContractServiceImpl) getServiceImplObj(WebKeys.ServiceImpl_Object_Contract))
				.getAttachmentByID(Type.GetInt(request.getParameter("attID")), directPath);


		logger.info(fileName);

//		logger.info("start 2= " + new java.sql.Time(System.currentTimeMillis()).toString());

		try{
			// download with smartupload
			SmartUpload sua = new SmartUpload();
			sua.initialize(this.getServletConfig(), request, response);
			sua.setContentDisposition(null); // �趨contentDispositionΪnull�Խ�ֹ������Զ����ļ�,��֤������Ӻ��������ļ�
			sua.downloadFile(fileName, "application/x-msdownload");
			
		} catch (Exception e) {
			e.printStackTrace();
//			messages = "�ϴ��ļ�ʧ�ܣ������µ�¼���ٲ�����лл";
//			messageTitle = "�ϴ��ļ�ʧ��";

		}
		
//		logger.info("start 3= " + new java.sql.Time(System.currentTimeMillis()).toString());
		
	}


}
