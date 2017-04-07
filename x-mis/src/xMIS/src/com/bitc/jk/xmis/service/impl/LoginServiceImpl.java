//Source file: D:\\Ted Li\\X-MIS\\src\\xMIS-source\\com\\bitc\\jk\\xmis\\service\\Impl\\LoginServiceImpl.java

package com.bitc.jk.xmis.service.impl;

import java.util.List;

import org.apache.log4j.Logger;

import com.bitc.jk.xmis.dao.OrganizationDAO;
import com.bitc.jk.xmis.model.EmployeeObj;
import com.bitc.jk.xmis.service.LoginService;
import com.bitc.jk.xmis.util.WebKeys;


public class LoginServiceImpl implements LoginService {
	private static Logger logger = Logger.getLogger(LoginServiceImpl.class);

	private OrganizationDAO organizationDAO;

	/**
	 * @roseuid 4C19886300CB
	 */
	public LoginServiceImpl() {

	}

	/**
	 * @param loginName
	 * @param password
	 * @return com.bitc.jk.xmis.model.EmployeeObj
	 * @roseuid 4C198C3B009C
	 */
	public EmployeeObj userValidete(String loginName, String password)
			throws Exception {
		try {
//			Calendar c = Calendar.getInstance();
//			c.setTime(new Date(System.currentTimeMillis()));
//
//			if (c.get(Calendar.DATE) == 1)
//				organizationDAO.doBookLunchAddress();

			return organizationDAO.userValidete(loginName, password);

		} catch (Exception e) {
			e.printStackTrace();
			throw e;
		}

	}
	
	public String buildLeftMenu(String treeName, EmployeeObj userDNA){
		
		String menuStr = "[";
		
		if(WebKeys.Tree_Menu_Name_myDeskMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_myDesk_MyHomePage + ",text:'" + "My Home Page" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_myDesk_WhatSNew + ",text:'" + "What\\'s New?" + "',leaf:true}"
			;
			
		}else if(WebKeys.Tree_Menu_Name_myTaskMenu.equals(treeName)){
				menuStr += "{id:" + WebKeys.Menu_ID_myTask_TaskReceipt + ",text:'" + "��������" + "',leaf:true},"
				+  "{id:" + WebKeys.Menu_ID_myTask_TaskExecute + ",text:'" + "ִ������" + "',leaf:true},"
				+  "{id:" + WebKeys.Menu_ID_myTask_TaskHistory + ",text:'" + "��ʷ����" + "',leaf:true}"
				;
				
		}else if(WebKeys.Tree_Menu_Name_ProjectMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_ProjectManagement_ProjectStart + ",text:'" + "��Ŀ����" + "',leaf:true},"
					+  "{id:" + WebKeys.Menu_ID_ProjectManagement_TaskAssign + ",text:'" + "�������" + "',leaf:true},"
					+  "{id:" + WebKeys.Menu_ID_ProjectManagement_InnerAcceptance + ",text:'" + "�ڲ�����" + "',leaf:true},"
					+  "{id:" + WebKeys.Menu_ID_ProjectManagement_ExternalAcceptance + ",text:'" + "�ⲿ����" + "',leaf:true},"
					+  "{id:" + WebKeys.Menu_ID_ProjectManagement_ContractChange + ",text:'" + "��ͬ���" + "',leaf:true},"
					+  "{id:" + WebKeys.Menu_ID_ProjectManagement_ProjectMaint + ",text:'" + "��Ŀά��" + "',leaf:true},"
					+  "{id:" + WebKeys.Menu_ID_ProjectManagement_LocaleReport + ",text:'" + "�ֳ���������" + "',leaf:true},"
					+  "{id:" + WebKeys.Menu_ID_ProjectManagement_CarryOverQuestion + ",text:'" + "�������⴦��" + "',leaf:true},"
					+  "{id:" + WebKeys.Menu_ID_ProjectManagement_IntegrationSearch + ",text:'" + "��Ŀ�ۺϲ�ѯ" + "',leaf:true}"
			;
			
		}else if(WebKeys.Tree_Menu_Name_ContractMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_ContractManagement_ContractEntry + ",text:'" + "��ͬ¼��" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_ContractManagement_InvoiceEntry + ",text:'" + "Ʊ���շ��Ǽ�" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_ContractManagement_PaymentEntry + ",text:'" + "��ͬ���׸��Ǽ�" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_ContractManagement_IntegrationSearch + ",text:'" + "��ͬ�ۺϲ�ѯ" + "',leaf:true}"
			;
			
		}else if(WebKeys.Tree_Menu_Name_MaterialMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_MaterialManagement_DevicePurchase + ",text:'" + "�豸�ɹ�" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_MaterialManagement_DeviceWarehouseEntry + ",text:'" + "�豸���Ǽ�" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_MaterialManagement_DeviceReceive + ",text:'" + "�豸����" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_ContractManagement_InvoiceEntry + ",text:'" + "Ʊ���շ��Ǽ�" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_MaterialManagement_DeviceReturnChange + ",text:'" + "���޸���" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_MaterialManagement_IntegrationSearch + ",text:'" + "������Ϣ��" + "',leaf:true}"
			;
			
		}else if(WebKeys.Tree_Menu_Name_MeetingMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_MeetingManagement_MeetingStart + ",text:'" + "���鷢��" + "',leaf:true}"
			;

		}else if(WebKeys.Tree_Menu_Name_CrmMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_CrmManagement_CRMEntry + ",text:'" + "�ͻ���Ϣ�Ǽ�" + "',leaf:true}"
			;

		}else if(WebKeys.Tree_Menu_Name_IssueMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_IssueManagement_IssueEntry + ",text:'" + "ȱ�ݵǼ�" + "',leaf:true}"
			;

		}else if(WebKeys.Tree_Menu_Name_OrganizationMenu.equals(treeName)){
				menuStr += "{id:" + WebKeys.Menu_ID_OrganizationManagement_OrganizationTree + ",text:'" + "��֯�ܹ�" + "',leaf:true},"
				+  "{id:" + WebKeys.Menu_ID_OrganizationManagement_GoOutEentry + ",text:'" + "����Ǽ�" + "',leaf:true},"
				+  "{id:" + WebKeys.Menu_ID_OrganizationManagement_BusinessTripEntry + ",text:'" + "����Ǽ�" + "',leaf:true},"
				+  "{id:" + WebKeys.Menu_ID_OrganizationManagement_DailyRecord + ",text:'" + "������־" + "',leaf:true},"
				+  "{id:" + WebKeys.Menu_ID_OrganizationManagement_VacationRequist + ",text:'" + "�ݼ�����" + "',leaf:true},"
				+  "{id:" + WebKeys.Menu_ID_OrganizationManagement_UserRightRequist + ",text:'" + "Ȩ������" + "',leaf:true}"
				;

		}else if(WebKeys.Tree_Menu_Name_ProductionMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_ProductionManagement_NewProduction + ",text:'" + "�²�Ʒ����" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_ProductionManagement_SubsequentDevelop + ",text:'" + "��������" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_ProductionManagement_ProductionRelease + ",text:'" + "��Ʒ����" + "',leaf:true}"
			;

		}else if(WebKeys.Tree_Menu_Name_WiKiMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_WiKiManagement_WikiEntry + ",text:'" + "���������" + "',leaf:true},"
			+  "{id:" + WebKeys.Menu_ID_WiKiManagement_IntegrationSearch + ",text:'" + "֪ʶ���ѯ" + "',leaf:true}"
			;

		}else if(WebKeys.Tree_Menu_Name_SuggestionMenu.equals(treeName)){
			menuStr += "{id:" + WebKeys.Menu_ID_SuggestionManagement_SuggestionEntry + ",text:'" + "��Ϣ�ɼ�" + "',leaf:true}"
			;

		}
		
		return menuStr + "]";
	}

	/**
	 * @param userID
	 * @return List
	 * @roseuid 4C198C3B0128
	 */
	public List getUserRight(int userID) {
		return null;
	}

	private void doLunchAddrssBook() {

	}

	public OrganizationDAO getOrganizationDAO() {
		return organizationDAO;
	}

	public void setOrganizationDAO(OrganizationDAO organizationDAO) {
		this.organizationDAO = organizationDAO;
	}
}
