package com.bitc.jk.xmis.util;

public class DBSchema {
	public class Contract {

		public static final String TableName = "xmis.con_��ͬ";

		public static final String ContractID = "��ͬID";

		public static final String ContractNo = "��ͬ���";

		public static final String ContractName = "��ͬ����";

		public static final String Abbreviation = "���";

		public static final String ParentID = "����ͬID";
		
		public static final String ParentContractNo = "contractNo";
		
		public static final String ParentContractAbb = "abbreviation";

		public static final String SignatureDate = "ǩ������";

		public static final String BuyerID = "�׷���˾ID";

		public static final String DeptIDOfBuyer = "�׷�����ID";

		public static final String Buyer = "�׷���˾";
		public static final String BuyerAbb = "aCompany_abb";

		//public static final String DeptNameOfBuyer = "�׷�����";
		public static final String DeptNameOfBuyer = "aDept_name";
		

		public static final String VendorID = "�ҷ���˾ID";

		public static final String DeptIDOfVendor = "�ҷ�����ID";

		public static final String VendorName = "�ҷ���˾";
		public static final String VendorAbb = "bCompany_abb";

//		public static final String DeptNameOfVendor = "�ҷ�����";
		public static final String DeptNameOfVendor = "bDept_name";

		public static final String ContractAmt = "��ͬ�ܶ�";
		public static final String ContractAmtCount = "��ͬ����";

		public static final String CurrencyID = "����ID";

		public static final String CurrencyName = "��������";

		public static final String ContractTypeID = "��ͬ����ID";

		public static final String ContractTypeName = "��ͬ����";

		public static final String BuyerRepresentativeID = "�׷�����ID";

		public static final String BuyerRepresentativeSurname = "�׷���������";

		public static final String BuyerRepresentativeName = "�׷���������";
		
		public static final String VendorRepName = "bEmp_name";

		public static final String VendorRepresentativeID = "�ҷ�����ID";

		public static final String VendorRepresentativeSurname = "�ҷ���������";

		public static final String VendorRepresentativeName = "�ҷ���������";

		public static final String ContractSummary = "��ͬ��Ҫ";

		public static final String BuyerRepName = "aEmp_name";
		public static final String Remark = "��ע";
		
		public static final String RegisterID = "�Ǽ���ID";

		public static final String RegisterSurname = "�Ǽ�������";

		public static final String RegisterName = "�Ǽ�������";
		
		public static final String RepName = "cEmp_name";

		public static final String UpdateDate = "����ʱ��";

		public static final String SourceTypeID = "��ͬ��Դ����ID";

		public static final String SourceTypeName = "��ͬ��Դ����";

		public static final String GovermentContractSourceID = "�����ͬ��ԴID";

		public static final String GovermentContractSourceName = "�����ͬ��Դ";
		
		public static final String WarrantyStartDate = "�ʱ�����";
		
		public static final String WarrantyEndDate = "�ʱ���ֹ";
		
		public static final String WarrantyDefinition = "�ʱ��ڶ���";
		
		public static final String WarrantyLimit = "�ʱ�����";
		
		public static final String WarrantyUnit = "�ʱ��ڼ�����λ";
		
		public static final String DeliveryID = "������ϵ��ID";
		
		public static final String DeliveryName = "delivery_name";

	}
	
	public class GovernmentContractSource{
		public static final String TableName = "xmis.con_�����ͬ��Դ";
		public static final String GovermentContractSourceID = "�����ͬ��ԴID";
		public static final String GovermentContractSourceName = "����";
		public static final String CompanyID = "��Դ��λID";
		public static final String DepartmentID = "��Դ����ID";
		public static final String FundingLimit = "�����������";
		public static final String CurrencyTypeID = "����ID";
		public static final String Specialty = "�ص�";
		public static final String Template = "����ģ��";
		public static final String UpdateDate = "�������";
		public static final String UpdateID = "�����";
		public static final String Actived = "�Ƿ����";
	}
	
	public class ContractType{
		public static final String TableName = "xmis.con_��ͬ����";
		public static final String ContractTypeID = "��ͬ����ID";
		public static final String ContractTypeName = "��ͬ����";
	}
	
	
	public class ContractSourceType{
		public static final String TableName = "xmis.con_��ͬ��Դ����";
		public static final String ContractSourceTypeID = "��ͬ��Դ����ID";
		public static final String ContractSourceTypeName = "��ͬ��Դ����";
	}	
	
	public class CurrencyType {
		public static final String TableName = "xmis.sys_����";
		public static final String CurrencyID = "����ID";
		public static final String CurrencyName = "��������";
		public static final String ExchangeRate = "������һ���";
		public static final String CurrenyGraph = "���ҷ���";
		public static final String ExchangedAmt = "�һ����";
	}

	public class Employee {
		public static final String TableName = "xmis.hr_��Ա";

		public static final String ID = "��ԱID";

		public static final String LastName = "����";

		public static final String FirstName = "����";
		
		public static final String IDCard = "���֤��";

		public static final String SexID = "�Ա�ID";

		public static final String OfficeAddressID = "�칫��ַID";

		public static final String HomeAddress = "��ͥ��ַ";

		public static final String Position = "ְ��";

		public static final String MobileNo = "�ƶ��绰";

		public static final String OfficeTelNo = "��λ�绰";

		public static final String ExtNo = "��λ�ֻ�";

		public static final String HomeTelNo = "סլ�绰";

		public static final String FaxNo = "�������";

		public static final String Email = "�����ʼ�";

		public static final String SpouseName = "��ż����";

		public static final String IssueName = "��������";

		public static final String NativePlace = "����";

		public static final String EduicationLevelID = "ѧ��ID";

		public static final String Remark = "��ע";

		public static final String WebSite = "��ҳ";

		public static final String PoliticalStatus = "������òID";

		public static final String Hobby = "����";

		public static final String Specialty = "�س�";

		public static final String Photo = "��Ƭ";

		public static final String MaritalStatus = "����״̬ID";

		public static final String UpdateID = "�޸���ID";

		public static final String UpdateDate = "�޸�ʱ��";

		public static final String Password = "����";

		public static final String DisabledFlag = "����";

		public static final String ContralFile = "�����ļ�";

		public static final String LoginName = "��¼��";
		
		public static final String JoinDate = "��ְ����";
		public static final String Birthday = "��������";
		public static final String ZipCode = "��ͥ�ʱ�";
		public static final String IssueSex = "��Ů�Ա�";
		public static final String imgName = "��Ƭ�ļ���";
		
		public static final String aEmpName = "aEmp_name";
		public static final String bEmpName = "bEmp_name";
	}

	public class DeptBelongToDept {
		public static final String TableName = "xmis.org_���Ź������ű�";

		public static final String DeptID = "����ID";

		public static final String ParentsID = "������ID";

	}

	public class Department {
		public static final String TableName = "xmis.org_����";

		public static final String DepartmentID = "����ID";

		public static final String DepartmentName = "��������";

		public static final String Abbreviation = "������д";

		public static final String TelephoneNo1 = "�绰1";

		public static final String FaxNo1 = "����1";

		public static final String TelephoneNo2 = "�绰2";

		public static final String FaxNo2 = "����2";

		public static final String ManagerID = "������ID";

		public static final String ContactID = "��ϵ��ID";

		public static final String WebSite = "��ַ";

		public static final String Email = "����";

		public static final String QtyOfMember = "����";

		public static final String Address = "��ַ";
		
		public static final String DisabledFlag = "����";

	}

	public class ProjectTask {
		public static final String TableName = "xmis.prj_��Ŀ�����";

		public static final String ProjectTaskID = "��Ŀ����ID";

		public static final String ProjectID = "��ĿID";

		public static final String SponsorID = "������ID";

		public static final String AssigedToDeptID = "�нӲ���ID";

		public static final String TaskScheme = "���鷽��";

		public static final String TaskDifficulty = "�����ѵ�";

		public static final String RegularTaskID = "��������ID";

		public static final String TaskETADate = "�������ʱ��";

		public static final String TaskTypeID = "��������ID";

	}

	public class Project {

		public static final String TableName = "xmis.prj_��Ŀ";

		public static final String ProjectID = "��ĿID";

		public static final String ProjectCode = "��Ŀ����";
		
		public static final String ProjectName = "��Ŀ����";

		public static final String ContractID = "��Ŀ��ͬID";

		public static final String StartDate = "��������";

		public static final String ProjectStatusID = "��Ŀ״̬ID";

		public static final String ProjectTypeID = "��Ŀ����ID";
	}

	public class ProjectStatus{
		public static final String TableName = "xmis.prj_��Ŀ״̬";

		public static final String ProjectStatusID = "��Ŀ״̬ID";
		public static final String ProjectStatusName = "��Ŀ״̬";
		public static final String ProjectStatusDescription = "��Ŀ״̬����";
		public static final String SelfDefinitionFlag = "�Ƿ��Զ���";
	}
	
	
	public class PaymentCondition{
		public static final String TableName = "xmis.con_�տ�������";
		public static final String ContractID = "��ͬID";
		public static final String PaymentConditionID = "�տ�����ID";
		public static final String PaymentConditionDescription = "�տ���������";
		public static final String ProjectStatusID = "��Ӧ��Ŀ״̬";
		public static final String ProjectStatusName = "��Ŀ״̬";
		public static final String DelayDays = "�ӳ�����";
		public static final String PaymentDate = "�տ�����";
		public static final String PaymentDateDisplayed = "payment_date";
		public static final String ManualFlag = "�ֶ�����";
		public static final String PaymentPercent = "�տ�ٷֱ�";
		public static final String PaymentAmt = "�տ���";			
		public static final String ManualReason = "�ֶ�����ԭ��";	
		
	}
	
	public class PaymentConditionManualLog{
		public static final String TableName = "xmis.con_�տ������ֶ������";
		public static final String LogID = "���ID";
		public static final String ContractID = "��ͬID";
		public static final String PaymentConditionID = "�տ�����ID";
		public static final String PaymentDate = "�տ�����";
		public static final String PaymentPercent = "�տ�ٷֱ�";
		public static final String PaymentAmt = "�տ���";			
		public static final String ChangedReason = "���ԭ��";	
		public static final String ChangedDate = "�������";	
		public static final String ChangedID = "�����";	
		
		
	}	
	
	/*
	 * Merge to �տ���ϸ��
	 */
	public class PaymentDetail {
		public static final String TableName = "xmis.con_������ϸ��";

		public static final String PaymentID = "����ID";

		public static final String PaymentAmt = "������";

		public static final String PaymentDate = "��������";

		public static final String TransactorID = "������";

		public static final String ScanAttachment = "Ʊ��ɨ��";

		public static final String ContractID = "��ͬID";
	}

	public class ChargedDetail {
		public static final String TableName = "xmis.con_�տ���ϸ��";

		public static final String ChargedID = "�տ�ID";

		public static final String ChargedAmt = "�տ���";

		public static final String ChargedDate = "�տ�����";
		public static final String ChargedDateDisplayed = "chargedDate";

		public static final String TransactorID = "������";

		public static final String ScanAttachment = "Ʊ��ɨ��";

		public static final String ContractID = "��ͬID";
		
		public static final String UpdateID = "�Ǽ���";
		
		public static final String UpdateDate = "�Ǽ�����";
		public static final String UpdateDateDisplay = "updateDate";
		
		public static final String UnChargedAmtTotal = "δ�տ���ϼ�";

		public static final String TotalAmtByID = "�տ�ϼ�";
		
		public static final String ChargedAmtTotalSum = "�տ��ܼ�";
		
		public static final String UnChargedAmtTotalSum = "δ�տ��ܼ�";
		
		public static final String ChargedRemark = "��ע";
		

	}

	public class InvoiceDetail{
		public static final String TableName = "xmis.con_��Ʊ���߱�";
		public static final String ContractID = "��ͬID";
		public static final String InvoiceNo = "��Ʊ��";
		public static final String InvoiceAmt = "��Ʊ���";
		public static final String InvoiceDate = "��������";
		public static final String InvoiceDateDisplayed = "invocieDate";
		public static final String TransactorID = "������";
		public static final String ScanAttachment = "ɨ���";
		public static final String UpdateID = "�Ǽ���";
		public static final String UpdateDate = "�Ǽ�����";
		public static final String UpdateDateDisplayed = "updateDate";
		public static final String Remark = "��ע";
		public static final String InvoiceCode = "��Ʊ���";
		public static final String TotalAmtByID = "�ѿ���Ʊ���ϼ�";
		public static final String UnAccountAmtTotalSum = "�ѿ�Ʊδ���˽��ϼ�";
		
	}
	
	public class EmployeeBelongToDept {
		public static final String TableName = "xmis.hr_��Ա���Ź�ϵ��";

		public static final String EmployeeID = "��ԱID";

		public static final String DepartmentID = "����ID";

		public static final String Position = "ְ��";

		public static final String IsPartTime = "�Ƿ��ְ";
	}

	public class MemberOfProjectTask {
		public static final String TableName = "xmis.prj_��Ŀ�����Ա";

		public static final String ProjectTaskID = "��Ŀ����ID";

		public static final String MemberID = "��Ŀ��ԱID";

		public static final String TaskDescriptioin = "�е�����";

		public static final String IsLeader = "�Ƿ�����";
	}

	public class PlanOfProjectTask {
		public static final String TableName = "xmis.prj_������ȼƻ�";

		public static final String ProjectTaskID = "��Ŀ����ID";

		public static final String TaskName = "��������";

		public static final String BengineDate = "��ʼ����";

		public static final String EndDate = "��������";

		public static final String PreviousTaskID = "ǰ������ID";

		public static final String LeaderID = "������ID";

	}

	public class Address{
		public static final String TabelName = "xmis.add_��ַ";
		public static final String AddressID = "��ַID";
		public static final String CityID = "����ID";
		public static final String District = "����";
		public static final String ZipCode = "�ʱ�";
		public static final String AddressInfo = "��ϸ��ַ";
		
	}
	
	public class City{
		public static final String TableName = "xmis.add_����";
		public static final String CityID = "����ID";
		public static final String CityCode = "���б���";
		public static final String CityName = "��������";
		public static final String Abbreviation = "���м��";
		public static final String AreaCode = "����";
		public static final String ProvinceID = "ʡID";
		
		
	}
	
	public class Province{
		public static final String TableName = "xmis.add_ʡ";
		public static final String ProvinceID = "ʡID";
		public static final String ProvinceCode = "ʡ����";
		public static final String ProvinceName = "ʡ����";
		public static final String Abbreviation = "ʡ���";
		public static final String AreaID = "����ID";
	}

	public class DepartmentBelongToCompany{
		public static final String TabelName = "xmis.org_���Ź�����˾��";
		public static final String CompanyID = "��˾ID";
		public static final String DepartmentID = "����ID"; 
		public static final String DirectlyFlag = "�Ƿ�ֱ��";
	}
	
	public class Company{
		public static final String TableName = "xmis.org_��˾";
		public static final String CompanyID = "��˾ID";
		public static final String CompanyName = "��˾����";
		public static final String Abbreviation = "������д";
		public static final String BusinessRelationID = "ҵ���ϵID";
		public static final String AddressID = "��ַID";
		public static final String TelephoneNo1 = "�绰1" ;
		public static final String FaxNo1 = "����1";
		public static final String TelephoneNo2 = "�绰2";
		public static final String FaxNo2 = "����2";
		public static final String WebSite = "��ַ";
		public static final String EmailAddress = "����";
		public static final String BankName = "��������";
		public static final String AccountNo = "�˺�";
		public static final String TaxNo = "˰��";
		public static final String CompanyScaleID = "��˾��ģID";
		public static final String LegalRepresentativeID = "���˴���ID";
		public static final String ContactPersonID = "��ϵ��ID" ;
		public static final String CustomerLevelID = "�ͻ�����ID";
		public static final String CreditLevelID = "���õȼ�ID";
		public static final String OrganizationCode = "��������";
		public static final String RegisteredCapital = "ע���ʽ�" ;
		public static final String Remark = "��ע";
		public static final String CustomerSourceID = "�ͻ���ԴID" ;
		public static final String BusinessScope = "��Ӫ��Χ";
		public static final String UpdateID = "�޸���ID";
		public static final String UpdateDate = "�޸�ʱ��";
		public static final String SecurityLevelID = "���ܼ���";
	}
	
	public class CustomerLevel{
		public static final String TableName = "xmis.org_�ͻ�����";
		public static final String CustomerLevelID = "�ͻ�����ID";
		public static final String CustomerLevelName = "����";
		public static final String CustomerLevelDefinition = "����";
	}
	
	public class CreditLevel{
		public static final String TableName = "xmis.org_���õȼ�";
		public static final String CreditLevelID = "���õȼ�ID";
		public static final String CreditLevelName = "����";
		public static final String CreditLevelDefinition = "����";
	}
	
	public class BusinessRelation{
		public static final String TableName = "xmis.org_ҵ���ϵ";
		public static final String BusinessRelationID = "ҵ���ϵID";
		public static final String BusinessRelationName = "��ϵ����";
		public static final String BusinessRelationDefinition = "��ϵ����";
	}

	public class CompanyScale{
		public static final String TableName = "xmis.org_��˾��ģ";
		public static final String CompanyScaleID = "��˾��ģID";
		public static final String CompanyScaleName = "����";
		public static final String CompanyScaleDefinition = "����";
	}
	
	public class ContactPerson{
		public static final String TableName = "xmis.crm_��ϵ��";
		public static final String ContactPersonID = "��ϵ��ID";
		public static final String FirstName = "����";
		public static final String LastName = "����";
		public static final String CompanyID = "��˾ID";
		public static final String DepartmentID = "����ID";
		public static final String UpdateID = "�޸���ID";
		public static final String UpdateDate = "�޸�ʱ��";
	}
	
	public class EducationLevel{
		public static final String TableName = "xmis.sys_ѧ��";
		public static final String EducationLevelID = "ѧ��ID";
		public static final String EducationLevelName = "ѧ��";
		public static final String SchoolName = "��ҵԺУ";
		public static final String GraduationDate = "��ҵʱ��";
		public static final String Major = "רҵ";
		public static final String Remark = "��ע";
	}
	
	public class PoliticalStatus{
		public static final String TableName = "xmis.sys_������ò";
		public static final String PoliticalStatusID= "������òID";
		public static final String PoliticalStatusName = "������ò";
	}
	
	public class EmployeeLunchAddress{
		public static final String TableName = "xmis.hr_��͵�ַ�ǼǱ�";
		public static final String UpdateDate = "�������";
		public static final String EmployeeID = "��ԱID";
		public static final String LunchAddressID = "�͹�ID";
		public static final String UpdateID = "�����ID";
		public static final String BookedFlag = "ȷ�ϱ�־";
	}
	
	public class LunchAddress{
		public static final String TableName = "xmis.sys_��͵�ַ��";
		public static final String LunchAddressID = "�͹�ID";
		public static final String LunchAddressName = "�͹�����";
		public static final String LunchAddress = "�͹ݵ�ַ";
	}
	
	public class Attachment{
		public static final String TableName = "xmis.sys_����";
		public static final String AttachmentID = "����ID";
		public static final String UploadDate = "�ϴ�ʱ��";
		public static final String UploaderID = "�ϴ���";
		public static final String AttahcmentDesc ="��������";
		public static final String AttachmentName = "�ļ���";
		public static final String AttachmentContent = "��������";
		public static final String AttachmentTypeID = "������������ID";
		public static final String AttachmentKey = "��������ֶ�";
		public static final String REFID = "REFID";
		public static final String UploaderName = "uploader_name";
		public static final String UploadDisplayDate = "upload_date";
	}
	
	public class AttachmentType{
		public static final String TableName = "xmis.sys_������������";
		public static final String AttachmentTypeID = "������������ID";
		public static final String AttachmentTypeDesc = "������������";
		public static final String AttachmentTableName = "TableName";
		public static final String AttachmentFieldName = "FieldName";
	}
}
