//Source file: D:\\Ted Li\\X-MIS\\src\\xMIS-source\\com\\bitc\\jk\\xmis\\model\\CompanyObj.java

package src;

import java.sql.Date;

public class CompanyObj {
	private int companyID;

	private String companyName;

	private String abbreviation;

	private int businessRelationID; // "ҵ���ϵID";

	private int addressID; // "��ַID";
	
	private String address;

	private String telephoneNo1; // "�绰1" ;

	private String faxNo1; // "����1";

	private String telephoneNo2; // "�绰2";

	private String faxNo2; // "����2";

	private String webSite; // "��ַ";

	private String emailAddress; // "����";

	private String bankName; // "��������";

	private String accountNo; // "�˺�";

	private String taxNo; // "˰��";

	private int companyScaleID; // "��˾��ģID";

	private String companyScaleName; // "��˾��ģ";

	private String companyScaleDefinition; // "��˾��ģ����";

	private int legalRepresentativeID; // "���˴���ID";

	private int legalRepresentativeName; // "���˴���";

	private int contactPersonID; // "��ϵ��ID" ;

	private int contactPersonName; // "��ϵ��" ;

	private int customerLevelID; // "�ͻ�����ID";

	private int customerLevelName; // "�ͻ���������";

	private int customerLevelDefinition; // "�ͻ���������";

	private int creditLevelID; // "���õȼ�ID";

	private int creditLevelName; // "���õȼ�����";

	private int creditLevelDefinition; // "���õȼ�����";

	private String organizationCode; // "��������";

	private double registeredCapital; // "ע���ʽ�" ;

	private String remark; // "��ע";

	private int customerSourceID; // "�ͻ���ԴID" ;

	private String bsinessScope; // "��Ӫ��Χ";

	private int updateID; // "�޸���ID";

	private int updaterName; // "�޸���;

	private Date updateDate; // "�޸�ʱ��";

	private int securityLevelID; // "���ܼ���";

	/**
	 * @roseuid 4C1F03AE0138
	 */
	public CompanyObj() {

	}

	/**
	 * @return the abbreviation
	 */
	public String getAbbreviation() {
		return abbreviation;
	}

	/**
	 * @param abbreviation the abbreviation to set
	 */
	public void setAbbreviation(String abbreviation) {
		this.abbreviation = abbreviation;
	}

	/**
	 * @return the accountNo
	 */
	public String getAccountNo() {
		return accountNo;
	}

	/**
	 * @param accountNo the accountNo to set
	 */
	public void setAccountNo(String accountNo) {
		this.accountNo = accountNo;
	}

	/**
	 * @return the address
	 */
	public String getAddress() {
		return address;
	}

	/**
	 * @param address the address to set
	 */
	public void setAddress(String address) {
		this.address = address;
	}

	/**
	 * @return the addressID
	 */
	public int getAddressID() {
		return addressID;
	}

	/**
	 * @param addressID the addressID to set
	 */
	public void setAddressID(int addressID) {
		this.addressID = addressID;
	}

	/**
	 * @return the bankName
	 */
	public String getBankName() {
		return bankName;
	}

	/**
	 * @param bankName the bankName to set
	 */
	public void setBankName(String bankName) {
		this.bankName = bankName;
	}

	/**
	 * @return the bsinessScope
	 */
	public String getBsinessScope() {
		return bsinessScope;
	}

	/**
	 * @param bsinessScope the bsinessScope to set
	 */
	public void setBsinessScope(String bsinessScope) {
		this.bsinessScope = bsinessScope;
	}

	/**
	 * @return the businessRelationID
	 */
	public int getBusinessRelationID() {
		return businessRelationID;
	}

	/**
	 * @param businessRelationID the businessRelationID to set
	 */
	public void setBusinessRelationID(int businessRelationID) {
		this.businessRelationID = businessRelationID;
	}

	/**
	 * @return the companyID
	 */
	public int getCompanyID() {
		return companyID;
	}

	/**
	 * @param companyID the companyID to set
	 */
	public void setCompanyID(int companyID) {
		this.companyID = companyID;
	}

	/**
	 * @return the companyName
	 */
	public String getCompanyName() {
		return companyName;
	}

	/**
	 * @param companyName the companyName to set
	 */
	public void setCompanyName(String companyName) {
		this.companyName = companyName;
	}

	/**
	 * @return the companyScaleDefinition
	 */
	public String getCompanyScaleDefinition() {
		return companyScaleDefinition;
	}

	/**
	 * @param companyScaleDefinition the companyScaleDefinition to set
	 */
	public void setCompanyScaleDefinition(String companyScaleDefinition) {
		this.companyScaleDefinition = companyScaleDefinition;
	}

	/**
	 * @return the companyScaleID
	 */
	public int getCompanyScaleID() {
		return companyScaleID;
	}

	/**
	 * @param companyScaleID the companyScaleID to set
	 */
	public void setCompanyScaleID(int companyScaleID) {
		this.companyScaleID = companyScaleID;
	}

	/**
	 * @return the companyScaleName
	 */
	public String getCompanyScaleName() {
		return companyScaleName;
	}

	/**
	 * @param companyScaleName the companyScaleName to set
	 */
	public void setCompanyScaleName(String companyScaleName) {
		this.companyScaleName = companyScaleName;
	}

	/**
	 * @return the contactPersonID
	 */
	public int getContactPersonID() {
		return contactPersonID;
	}

	/**
	 * @param contactPersonID the contactPersonID to set
	 */
	public void setContactPersonID(int contactPersonID) {
		this.contactPersonID = contactPersonID;
	}

	/**
	 * @return the contactPersonName
	 */
	public int getContactPersonName() {
		return contactPersonName;
	}

	/**
	 * @param contactPersonName the contactPersonName to set
	 */
	public void setContactPersonName(int contactPersonName) {
		this.contactPersonName = contactPersonName;
	}

	/**
	 * @return the creditLevelDefinition
	 */
	public int getCreditLevelDefinition() {
		return creditLevelDefinition;
	}

	/**
	 * @param creditLevelDefinition the creditLevelDefinition to set
	 */
	public void setCreditLevelDefinition(int creditLevelDefinition) {
		this.creditLevelDefinition = creditLevelDefinition;
	}

	/**
	 * @return the creditLevelID
	 */
	public int getCreditLevelID() {
		return creditLevelID;
	}

	/**
	 * @param creditLevelID the creditLevelID to set
	 */
	public void setCreditLevelID(int creditLevelID) {
		this.creditLevelID = creditLevelID;
	}

	/**
	 * @return the creditLevelName
	 */
	public int getCreditLevelName() {
		return creditLevelName;
	}

	/**
	 * @param creditLevelName the creditLevelName to set
	 */
	public void setCreditLevelName(int creditLevelName) {
		this.creditLevelName = creditLevelName;
	}

	/**
	 * @return the customerLevelDefinition
	 */
	public int getCustomerLevelDefinition() {
		return customerLevelDefinition;
	}

	/**
	 * @param customerLevelDefinition the customerLevelDefinition to set
	 */
	public void setCustomerLevelDefinition(int customerLevelDefinition) {
		this.customerLevelDefinition = customerLevelDefinition;
	}

	/**
	 * @return the customerLevelID
	 */
	public int getCustomerLevelID() {
		return customerLevelID;
	}

	/**
	 * @param customerLevelID the customerLevelID to set
	 */
	public void setCustomerLevelID(int customerLevelID) {
		this.customerLevelID = customerLevelID;
	}

	/**
	 * @return the customerLevelName
	 */
	public int getCustomerLevelName() {
		return customerLevelName;
	}

	/**
	 * @param customerLevelName the customerLevelName to set
	 */
	public void setCustomerLevelName(int customerLevelName) {
		this.customerLevelName = customerLevelName;
	}

	/**
	 * @return the customerSourceID
	 */
	public int getCustomerSourceID() {
		return customerSourceID;
	}

	/**
	 * @param customerSourceID the customerSourceID to set
	 */
	public void setCustomerSourceID(int customerSourceID) {
		this.customerSourceID = customerSourceID;
	}

	/**
	 * @return the emailAddress
	 */
	public String getEmailAddress() {
		return emailAddress;
	}

	/**
	 * @param emailAddress the emailAddress to set
	 */
	public void setEmailAddress(String emailAddress) {
		this.emailAddress = emailAddress;
	}

	/**
	 * @return the faxNo1
	 */
	public String getFaxNo1() {
		return faxNo1;
	}

	/**
	 * @param faxNo1 the faxNo1 to set
	 */
	public void setFaxNo1(String faxNo1) {
		this.faxNo1 = faxNo1;
	}

	/**
	 * @return the faxNo2
	 */
	public String getFaxNo2() {
		return faxNo2;
	}

	/**
	 * @param faxNo2 the faxNo2 to set
	 */
	public void setFaxNo2(String faxNo2) {
		this.faxNo2 = faxNo2;
	}

	/**
	 * @return the legalRepresentativeID
	 */
	public int getLegalRepresentativeID() {
		return legalRepresentativeID;
	}

	/**
	 * @param legalRepresentativeID the legalRepresentativeID to set
	 */
	public void setLegalRepresentativeID(int legalRepresentativeID) {
		this.legalRepresentativeID = legalRepresentativeID;
	}

	/**
	 * @return the legalRepresentativeName
	 */
	public int getLegalRepresentativeName() {
		return legalRepresentativeName;
	}

	/**
	 * @param legalRepresentativeName the legalRepresentativeName to set
	 */
	public void setLegalRepresentativeName(int legalRepresentativeName) {
		this.legalRepresentativeName = legalRepresentativeName;
	}

	/**
	 * @return the organizationCode
	 */
	public String getOrganizationCode() {
		return organizationCode;
	}

	/**
	 * @param organizationCode the organizationCode to set
	 */
	public void setOrganizationCode(String organizationCode) {
		this.organizationCode = organizationCode;
	}

	/**
	 * @return the registeredCapital
	 */
	public double getRegisteredCapital() {
		return registeredCapital;
	}

	/**
	 * @param registeredCapital the registeredCapital to set
	 */
	public void setRegisteredCapital(double registeredCapital) {
		this.registeredCapital = registeredCapital;
	}

	/**
	 * @return the remark
	 */
	public String getRemark() {
		return remark;
	}

	/**
	 * @param remark the remark to set
	 */
	public void setRemark(String remark) {
		this.remark = remark;
	}

	/**
	 * @return the securityLevelID
	 */
	public int getSecurityLevelID() {
		return securityLevelID;
	}

	/**
	 * @param securityLevelID the securityLevelID to set
	 */
	public void setSecurityLevelID(int securityLevelID) {
		this.securityLevelID = securityLevelID;
	}

	/**
	 * @return the taxNo
	 */
	public String getTaxNo() {
		return taxNo;
	}

	/**
	 * @param taxNo the taxNo to set
	 */
	public void setTaxNo(String taxNo) {
		this.taxNo = taxNo;
	}

	/**
	 * @return the telephoneNo1
	 */
	public String getTelephoneNo1() {
		return telephoneNo1;
	}

	/**
	 * @param telephoneNo1 the telephoneNo1 to set
	 */
	public void setTelephoneNo1(String telephoneNo1) {
		this.telephoneNo1 = telephoneNo1;
	}

	/**
	 * @return the telephoneNo2
	 */
	public String getTelephoneNo2() {
		return telephoneNo2;
	}

	/**
	 * @param telephoneNo2 the telephoneNo2 to set
	 */
	public void setTelephoneNo2(String telephoneNo2) {
		this.telephoneNo2 = telephoneNo2;
	}

	/**
	 * @return the updateDate
	 */
	public Date getUpdateDate() {
		return updateDate;
	}

	/**
	 * @param updateDate the updateDate to set
	 */
	public void setUpdateDate(Date updateDate) {
		this.updateDate = updateDate;
	}

	/**
	 * @return the updateID
	 */
	public int getUpdateID() {
		return updateID;
	}

	/**
	 * @param updateID the updateID to set
	 */
	public void setUpdateID(int updateID) {
		this.updateID = updateID;
	}

	/**
	 * @return the updaterName
	 */
	public int getUpdaterName() {
		return updaterName;
	}

	/**
	 * @param updaterName the updaterName to set
	 */
	public void setUpdaterName(int updaterName) {
		this.updaterName = updaterName;
	}

	/**
	 * @return the webSite
	 */
	public String getWebSite() {
		return webSite;
	}

	/**
	 * @param webSite the webSite to set
	 */
	public void setWebSite(String webSite) {
		this.webSite = webSite;
	}


}
