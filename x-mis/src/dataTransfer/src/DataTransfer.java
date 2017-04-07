package src;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.Types;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class DataTransfer {

	private static Connection jkglConn, xmisConn;

	private static int maxContractID;

	private static int maxAttachmentID;

	private static int pageSize = 100;

	private static Map companyOtherDeptMap = new LinkedHashMap();

	private static int maxEmpID;

	private static Connection getConnection(String type) throws Exception {

		Connection conn = null;

		String xmisDBType = "prod";

		String xmisProd = "192.169.11.6:4297";
		String xmisUAT = "192.169.11.140:1433";

		String urlStr = "jdbc:microsoft:sqlserver://"
				+ (type.equals("jkgl") ? xmisProd
						: (xmisDBType.equals("prod") ? xmisProd : xmisUAT))
				+ ";SelectMethod=Cursor";

		String user = ";User="
				+ (type.equals("jkgl") ? "ASPNET_USER" : (xmisDBType
						.equals("prod") ? "xmis" : "xmis-uat"));
		String pwd = ";Password=" + (type.equals("jkgl") ? "manager" : "xmis");
		String dbName = ";DatabaseName="
				+ (type.equals("jkgl") ? "JKGL" : "xmis");

		try {
			Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");

			conn = DriverManager.getConnection(urlStr + user + pwd + dbName);

			if (conn != null)
				System.out.println("++++++ " + type + " connection Successful!"
						+ "++++++ ");

		} catch (Exception e) {

			e.printStackTrace();
			throw new Exception("++++++ " + type + " connection failed"
					+ "++++++ ");
		}
		return conn;
	}

	private static List getDataListFromJKGL(String type) {

		ResultSet rs = null;
		List aList = new ArrayList();
		String sql = "";

		if (type.equals("emp"))
			sql = "select * from Ա��";

		else if (type.equals("crm"))
			sql = "select distinct(�׷�) from �����ͬ"
					+ " union select distinct(������ID) from ֧����ͬ";

		else if (type.equals("ʡ��"))
			sql = "select * from ʡ��";

		else if (type.equals("�����ͬ"))
			sql = "select * from �����ͬ order by �Զ����";

		else if (type.equals("�׷�����"))
			sql = "select DISTINCT �׷�,�׷����� from �����ͬ where �׷����� <> ''";

		else if (type.equals("�����ͬ׷�Ӻ�ͬ"))
			sql = "select *  from �����ͬ׷�Ӻ�ͬ";

		else if (type.equals("�����ͬ��������"))
			sql = "select *  from �����ͬ�������� ORDER BY ��Ŀ���,�Զ����";

		else if (type.equals("�����ͬ������ϸ"))
			sql = "select *  FROM dbo.�����ͬ���� ORDER BY ��Ŀ���, �Զ����";

		else if (type.equals("�����ͬ��Ŀ��Ա"))
			sql = "select *  from �����ͬ��Ŀ��Ա";

		else if (type.equals("�����ͬ�վ�"))
			sql = "select *  from �����ͬ�վ�  ORDER BY ��Ŀ���, �Զ����";

		else if (type.equals("�����ͬ��Ʊ"))
			sql = "select *  from �����ͬ��Ʊ  ORDER BY ��Ŀ���, �Զ����";

		else if (type.equals("�����ͬ�����ļ�"))
			sql = "select *  from �����ͬ�����ļ� ";

		else if (type.equals("֧����ͬ"))
			sql = "select * from ֧����ͬ order by �Զ����";

		else if (type.equals("֧����ͬ��Ӧ�����ͬ���"))
			sql = "select * from ֧����ͬ��Ӧ�����ͬ���";

		else if (type.equals("֧����ͬ����"))
			sql = "select *  FROM ֧����ͬ���� ORDER BY ֧����ͬ���, �Զ����";

		else if (type.equals("֧����ͬ�������"))
			sql = "select *  from ֧����ͬ������� ORDER BY ֧����ͬ���,�Զ����";

		else if (type.equals("֧����ͬ�����ļ�"))
			sql = "SELECT count(*) aCount FROM  ֧����ͬ�����ļ�";

		else if (type.indexOf("֧����ͬ�����ļ�_") == 0) {

			System.out.println(Type.GetInt(type.replace("֧����ͬ�����ļ�_", ""))
					* pageSize);

			// sql = "SELECT TOP 50 * FROM ֧����ͬ�����ļ�" +
			// " WHERE (�Զ���� > (SELECT MAX(�Զ����) FROM " +
			// "(SELECT TOP 50 * "+type.replace("֧����ͬ�����ļ�_", "")+" �Զ���� FROM
			// ֧����ͬ�����ļ� ORDER BY �Զ����) AS T)) " +
			// " ORDER BY �Զ����";

			sql = " SELECT TOP " + pageSize + " * FROM ֧����ͬ�����ļ� WHERE �Զ���� > ("
					+ " SELECT MAX(�Զ����) FROM (SELECT TOP " + pageSize
					* Type.GetInt(type.replace("֧����ͬ�����ļ�_", ""))
					+ " �Զ���� FROM ֧����ͬ�����ļ� ORDER BY �Զ����) AS T) "
					+ " ORDER BY �Զ����";
		}

		// System.out.println(sql);

		try {
			rs = jkglConn.prepareStatement(sql).executeQuery();

			ResultSetMetaData rsmd = rs.getMetaData();

			while (rs.next()) {
				Map map = new HashMap();
				for (int i = 0; i < rsmd.getColumnCount(); i++) {
					map.put(rsmd.getColumnName(i + 1), rs.getObject(i + 1));
				}

				aList.add(map);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				rs.close();
			} catch (Exception e) {
				e.printStackTrace();
			}

		}

		return aList;

	}

	private static int getDeptIDMapping(String dept) {

		int deptID = 0;
		// if(dept.equals("һ��") || dept.equals("����һ��"))
		if (dept.indexOf("һ��") > -1)
			deptID = 2;

		// else if(dept.equals("����") || dept.equals("���̶���"))
		else if (dept.indexOf("����") > -1)
			deptID = 3;

		// else if(dept.equals("����") || dept.equals("��������") ||
		// dept.equals("��Ͽ��") || dept.equals("��Ͽ���̲�"))
		else if (dept.indexOf("����") > -1 || dept.equals("��Ͽ��")
				|| dept.equals("��Ͽ���̲�"))
			deptID = 4;

		// else if(dept.equals("�Ĳ�") || dept.equals("�����Ĳ�"))
		else if (dept.indexOf("�Ĳ�") > -1)
			deptID = 5;

		else if (dept.equals("������"))
			deptID = 6;

		else if (dept.equals("��Ŀ����") || dept.equals("�����ҵ��")
				|| dept.equals("��ҵ��"))
			deptID = 7;

		else if (dept.equals("������"))
			deptID = 8;

		else if (dept.equals("�г���"))
			deptID = 9;

		else if (dept.equals("��������"))
			deptID = 10;

		return deptID;
	}

	private static Map doDataTransferForEmp() throws Exception {

		Map empMap = new LinkedHashMap();

		try {
			List empListFromJKGL = getDataListFromJKGL("emp");
			List empListForXMIS = new ArrayList();

			// logger.info(empListFromJKGL);
			int iCount = 0;
			for (Iterator i = empListFromJKGL.listIterator(); i.hasNext();) {

				Map map = (HashMap) i.next();
				EmployeeObj emp = new EmployeeObj();

				int mapsize = map.size();
				Iterator it = map.entrySet().iterator();

				for (int j = 0; j < mapsize; j++) {
					Map.Entry entry = (Map.Entry) it.next();

					// if (iCount == 0)
					// System.out.println(entry.getKey() + "=" +
					// entry.getValue());

					if (entry.getKey().equals("�Զ����")) {
						emp.setUserID(Type.GetInt(entry.getValue()));

						maxEmpID = maxEmpID > Type.GetInt(entry.getValue()) ? maxEmpID
								: Type.GetInt(entry.getValue());

					}

					else if (entry.getKey().equals("ID"))
						emp.setLoginName(Type.getString(entry.getValue()));

					else if (entry.getKey().equals("����")) {
						emp.setFirstName(Type.getString(entry.getValue())
								.substring(0, 1));
						emp.setLastName(Type.getString(entry.getValue())
								.substring(
										1,
										Type.getString(entry.getValue())
												.length()));

						// logger.info(emp.getFirstName() + emp.getLastName() +
						// "//");
					} else if (entry.getKey().equals("����"))
						emp.setPassword(Type.getString(entry.getValue()));
					else if (entry.getKey().equals("�Ա�"))
						emp.setSex(entry.getValue().equals("��") ? 1 : 0);
					else if (entry.getKey().equals("����ID"))
						emp.setDepartmentID(getDeptIDMapping(Type.getString(
								entry.getValue()).trim()));

				}

				// empMap.put(emp.getLoginName(), emp.getUserID());
				empMap.put(emp.getLoginName(), emp);
				empListForXMIS.add(emp);

				iCount++;
			}

			doDataTransferForEmp(empListForXMIS);
		} catch (Exception e) {
			e.printStackTrace();
			throw new Exception("=========== ��Ա����ת��ʧ��");

		}

		System.out.println("=========== ��Ա����ת���ɹ�");
		return empMap;

	}

	private static void doDataTransferForEmp(List aList) {

		String delSql = " DELETE xmis.hr_��Ա WHERE ��ԱID > 0 "
				+ " DELETE xmis.hr_��Ա���Ź�ϵ�� WHERE ��ԱID > 0 ";
		String insertSql = " insert into xmis.hr_��Ա(��ԱID,��¼��,����,����,�Ա�ID,�޸���ID,�޸�ʱ��) values (?,?,?,?,?,-1,GETDATE())"
				+ " insert into xmis.hr_��Ա���Ź�ϵ�� (��ԱID,����ID,�Ƿ��ְ) values (?,?,1)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				EmployeeObj emp = (EmployeeObj) aList.get(i);

				// System.out.println(emp.getFirstName() + emp.getLastName() +
				// "//");

				ps.setInt(1, emp.getUserID());
				ps.setString(2, emp.getLoginName());
				ps.setString(3, emp.getLastName());
				ps.setString(4, emp.getFirstName());
				ps.setInt(5, emp.getSex());

				ps.setInt(6, emp.getUserID());
				ps.setInt(7, emp.getDepartmentID());

				ps.addBatch();
			}

			ps.executeBatch();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	private static void doDataTransferForSupplementalContract(List aList) {

		String insertSql = "insert  into  xmis.con_��ͬ (��ͬID,��ͬ���,��ͬ����,���,ǩ������,�ҷ���˾ID,�ҷ�����ID,�׷���˾ID,��ͬ�ܶ�,"
				+ // 9
				"����ID,��ͬ����ID,�ҷ�����ID,��ͬ��Ҫ,��ע,�Ǽ���ID,����ʱ��, ����ͬID)  values " + // 17
				" (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				ContractObj con = (ContractObj) aList.get(i);

				ps.setInt(1, con.getContractID());
				ps.setString(2, con.getContractNo());
				ps.setString(3, con.getContractName());
				ps.setString(4, con.getAbbreviation());
				ps.setDate(5, con.getSignatureDate());

				ps.setInt(6, con.getVendorID());
				ps.setInt(7, con.getDeptIDOfVendor());
				ps.setInt(8, con.getBuyerID());
				ps.setDouble(9, con.getContractAmt());
				ps.setInt(10, con.getCurrencyID());
				ps.setInt(11, con.getContractTypeID());
				ps.setInt(12, con.getVendorRepresentativeID());
				ps.setString(13, con.getContractSummary());
				ps.setString(14, con.getRemark());
				ps.setInt(15, con.getRegisterID());
				ps.setDate(16, con.getUpdateDate());

				ps.setInt(17, con.getParentID());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== �����ͬ׷�Ӻ�ͬת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== �����ͬ׷�Ӻ�ͬת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// doDataTransferForPaymentContract
	private static void doDataTransferForPaymentContract(List aList) {

		String delSql = " DELETE xmis.con_��ͬ where ��ͬ����ID =2 ";
		String insertSql = "insert  into  xmis.con_��ͬ (��ͬID,��ͬ���,��ͬ����,���,ǩ������,�ҷ���˾ID,�ҷ�����ID,�׷���˾ID,��ͬ�ܶ�,"
				+ "����ID,��ͬ����ID,�ҷ�����ID,��ͬ��Ҫ,��ע,�Ǽ���ID,�ʱ�����,�ʱ��ڶ���,����ʱ��)  values  (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"
		// 18

		;

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				ContractObj con = (ContractObj) aList.get(i);

				ps.setInt(1, con.getContractID());
				ps.setString(2, con.getContractNo());
				ps.setString(3, con.getContractName());
				ps.setString(4, con.getAbbreviation());
				ps.setDate(5, con.getSignatureDate());

				ps.setInt(6, con.getVendorID());
				ps.setNull(7, Types.INTEGER);
				ps.setInt(8, con.getBuyerID());
				ps.setDouble(9, con.getContractAmt());
				ps.setInt(10, con.getCurrencyID());
				ps.setInt(11, con.getContractTypeID());
				ps.setNull(12, Types.INTEGER);
				ps.setString(13, con.getContractSummary());
				ps.setString(14, con.getRemark());
				ps.setInt(15, con.getRegisterID());
				ps.setNull(16, Types.DATE);
				ps.setNull(17, Types.VARCHAR);
				ps.setDate(18, con.getUpdateDate());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== ֧����ͬ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ֧����ͬ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	private static void doDataTransferForIncomeContract(List aList) {

		String delSql = " DELETE xmis.con_��ͬ " + "Delete  xmis.prj_��Ŀ ";
		String insertSql = "insert  into  xmis.con_��ͬ (��ͬID,��ͬ���,��ͬ����,���,ǩ������,�ҷ���˾ID,�ҷ�����ID,�׷���˾ID,��ͬ�ܶ�,"
				+ "����ID,��ͬ����ID,�ҷ�����ID,��ͬ��Ҫ,��ע,�Ǽ���ID,�ʱ�����,�ʱ��ڶ���,����ʱ��,�׷�����ID)  values  (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"
				+ // 19

				" insert into xmis.prj_��Ŀ(��ĿID , ��Ŀ���� , ��Ŀ���� , ��Ŀ��ͬID , ��������, ��Ŀ״̬ID ) values (?,?,?,?,?,-1)" // 20-24

		;

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				ContractObj con = (ContractObj) aList.get(i);

				ps.setInt(1, con.getContractID());
				ps.setString(2, con.getContractNo());
				ps.setString(3, con.getContractName());
				ps.setString(4, con.getAbbreviation());
				ps.setDate(5, con.getSignatureDate());

				ps.setInt(6, con.getVendorID());
				ps.setInt(7, con.getDeptIDOfVendor());
				ps.setInt(8, con.getBuyerID());
				ps.setDouble(9, con.getContractAmt());
				ps.setInt(10, con.getCurrencyID());
				ps.setInt(11, con.getContractTypeID());
				ps.setInt(12, con.getVendorRepresentativeID());
				ps.setString(13, con.getContractSummary());
				ps.setString(14, con.getRemark());
				ps.setInt(15, con.getRegisterID());
				ps.setDate(16, con.getWarrantyStartDate());
				ps.setString(17, con.getWarrantyDefinition());
				ps.setDate(18, con.getUpdateDate());
				ps.setInt(19, con.getBuyerRepresentativeID());


				ps.setInt(20, con.getProjectOBJ().getProjectID());
				ps.setString(21, con.getProjectOBJ().getProjectCode());
				ps.setString(22, con.getProjectOBJ().getProjectName());
				ps.setInt(23, con.getProjectOBJ().getContractID());
				ps.setDate(24, con.getProjectOBJ().getStartDate());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== ��ͬ&��Ŀ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ��ͬ&��Ŀ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// doDataTransferBuyerRepresentativeName(name id)
	private static Map doDataTransferBuyerRepresentativeName(List aList) {

		String insertSql = " insert into xmis.hr_��Ա(��ԱID,��¼��,����,����,�Ա�ID,�޸���ID,�޸�ʱ��) values (?,?,?,?,?,-1,GETDATE())" // 5
				+ " insert into xmis.hr_��Ա���Ź�ϵ�� (��ԱID,����ID,�Ƿ��ְ) values (?,?,1)" // 6,7
//				+ "   UPDATE xmis.con_��ͬ SET �׷�����ID = ? WHERE xmis.con_��ͬ.��ͬID = ? " // 8,9
		; //

		Map newBuyerMap = new LinkedHashMap(); 

		PreparedStatement ps = null;

		
		try {
			ps = xmisConn.prepareStatement(insertSql);

			for (int i = 0; i < aList.size(); i++) {
				String[] conMapping = (String[]) aList.get(i);
				
				ps.setInt(1, maxEmpID + i + 1);
				ps.setString(2, conMapping[0].length() > 3 ? conMapping[0]
						.substring(0, 3) : conMapping[0]);
				ps.setString(3, conMapping[0].substring(1, conMapping[0]
						.length()));

				ps.setString(4, conMapping[0].substring(0, 1));
				ps.setInt(5, 1);

				ps.setInt(6, maxEmpID + i + 1);
				ps.setInt(7, Type.GetInt(conMapping[1]));

//				ps.setInt(8, maxEmpID + i + 1);
//				ps.setInt(9, Type.GetInt(conMapping[2]));

				ps.addBatch();
				
				newBuyerMap.put(conMapping[2]+ "~" + conMapping[0], Type.getString(maxEmpID + i + 1));
			}

			ps.executeBatch();
			
			System.out.println("=========== ��ͬ�׷���Ա ����ת���ɹ�");
			

		} catch (Exception e) {
			System.out.println("=========== ��ͬ�׷���Ա ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return newBuyerMap;

	}

	private static void doDataTransferForCompany(Map aMap) {

		String delSql = " DELETE xmis.org_��˾ "
				+ "  DELETE xmis.org_���� WHERE ����ID > 10 "
				+ "DELETE xmis.xmis.org_���Ź�����˾�� WHERE ����ID > 10 ";
		String insertSql = " INSERT INTO xmis.org_��˾ "
				+ "( ��˾ID , ��˾���� , ������д , ҵ���ϵID , �޸�ʱ�� , �޸���ID)"
				+ " VALUES  (?,?,?,-1,getdate(),-1)" // 1-3

				+ " INSERT INTO xmis.org_����"
				+ " ( ����ID ,  �������� )"
				+ " VALUES  ( ?, '����')" // 4

				+ " INSERT INTO xmis.org_���Ź�����˾��"
				+ " ( ��˾ID, ����ID, �Ƿ�ֱ�� ) values (?,?,1) " // 5��6

		;

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);

			Iterator compaynIT = aMap.entrySet().iterator();
			for (int i = 1; i < aMap.size(); i++) {
				Map.Entry entry = (Map.Entry) compaynIT.next();
				// System.out.println(entry.getKey() + "==" + entry.getValue());

				ps.setInt(1, Type.GetInt(entry.getValue()));
				ps.setString(2, Type.getString(entry.getKey()));
				ps.setString(3, Type.getString(entry.getKey()));

				ps.setInt(4, 20 + i);

				ps.setInt(5, Type.GetInt(entry.getValue()));
				ps.setInt(6, 20 + i);

				ps.addBatch();

				// if(Type.getString(entry.getKey()).equals("���������ۺϿ������޹�˾"))
				// System.out.println("the other dept id = " + (20 +i));

				companyOtherDeptMap.put(Type.getString(entry.getKey()), 20 + i);

			}

			ps.executeBatch();
			System.out.println("=========== ��˾&��˾~������������ ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ��˾&��˾~������������ ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// doDataTransferForPaymentCondition
	private static void doDataTransferForPaymentCondition(List aList) {

		String delSql = " DELETE xmis.con_�տ������� ";
		String insertSql = "INSERT INTO xmis.con_�տ������� ( " + "			��ͬID ,"
				+ "          �տ�����ID ," + "          �տ��������� ," + "			�տ�ٷֱ� ,"
				+ "          �տ���,�ֶ�����,�ӳ�����,��Ӧ��Ŀ״̬) values (?,?,?,?,?,0,0,0)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				PaymentConditionObj pay = (PaymentConditionObj) aList.get(i);

				ps.setInt(1, pay.getContractID());
				ps.setInt(2, pay.getPaymentConditionID());
				ps.setString(3, pay.getDescription());
				ps.setInt(4, pay.getPaymentPercent());
				ps.setDouble(5, pay.getPamymentAmt());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== �տ���������ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== �տ���������ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// PayoutContractPaymentDetail
	private static void doDataTransferForPayoutContractPaymentDetail(List aList) {

		// String delSql = " DELETE xmis.con_�տ���ϸ�� ";
		String insertSql = "INSERT INTO xmis.con_�տ���ϸ��" + "        ( ��ͬID ,"
				+ "          �տ�ID ," + "          �տ��� ," + "          �տ����� ,"
				+ "          ������ ," + "          Ʊ��ɨ�� ," + "          �Ǽ��� ,"
				+ "          �Ǽ����� ," + "          ��ע"
				+ "        ) values (?,?,?,?,?,null,?,?,?)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			// xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				PaymentDetailObj pay = (PaymentDetailObj) aList.get(i);

				ps.setInt(1, pay.getContractID());
				ps.setInt(2, pay.getPaymentID());
				ps.setDouble(3, pay.getPaymentAmt());
				ps.setDate(4, pay.getPaymentDate());
				ps.setInt(5, pay.getTransactorID());
				ps.setInt(6, pay.getTransactorID());
				ps.setDate(7, pay.getPaymentDate());
				ps.setString(8, pay.getRemark());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== �տ���ϸ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== �տ���ϸ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// doDataTransferForPaymentDetail
	private static void doDataTransferForPaymentDetail(List aList) {

		String delSql = " DELETE xmis.con_�տ���ϸ�� ";
		String insertSql = "INSERT INTO xmis.con_�տ���ϸ��" + "        ( ��ͬID ,"
				+ "          �տ�ID ," + "          �տ��� ," + "          �տ����� ,"
				+ "          ������ ," + "          Ʊ��ɨ�� ," + "          �Ǽ��� ,"
				+ "          �Ǽ����� ," + "          ��ע"
				+ "        ) values (?,?,?,?,?,null,?,?,?)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				PaymentDetailObj pay = (PaymentDetailObj) aList.get(i);

				ps.setInt(1, pay.getContractID());
				ps.setInt(2, pay.getPaymentID());
				ps.setDouble(3, pay.getPaymentAmt());
				ps.setDate(4, pay.getPaymentDate());
				ps.setInt(5, pay.getTransactorID());
				ps.setInt(6, pay.getTransactorID());
				ps.setDate(7, pay.getPaymentDate());
				ps.setString(8, pay.getRemark());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== �տ���ϸ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== �տ���ϸ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// doDataTransferForReceipt
	private static void doDataTransferForReceipt(List aList) {

		String delSql = " DELETE xmis.con_�վ���ϸ�� ";
		String insertSql = "INSERT INTO xmis.con_�վ���ϸ��" + "        ( ��ͬID ,"
				+ "          �վ�ID ," + "          �վݽ�� ," + "          �վ����� ,"
				+ "          ������ ," + "          �Ǽ��� ," + "          �Ǽ����� ,"
				+ "          ��ע" + "        ) values (?,?,?,?,?,?,?,?)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				InvoiceObj inv = (InvoiceObj) aList.get(i);

				ps.setInt(1, inv.getContractID());
				ps.setInt(2, inv.getInvoiceID());
				ps.setDouble(3, inv.getInvoiceAMT());
				ps.setDate(4, inv.getInvoiceDate());
				ps.setInt(5, inv.getTransactorID());
				ps.setInt(6, inv.getTransactorID());
				ps.setDate(7, inv.getInvoiceDate());
				ps.setString(8, inv.getInvoiecRemark());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== �վ���ϸ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== �վ���ϸ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	private static void doDataTransferForPayoutContractInvoiceDetail(List aList) {

		// String delSql = " DELETE xmis.con_��Ʊ���߱� ";
		String insertSql = "INSERT INTO xmis.con_��Ʊ���߱�" + "        ( ��ͬID ,"
				+ "          ��Ʊ�� ," + "          ��Ʊ��� ," + "          �������� ,"
				+ "          ������ ," + "          ɨ��� ," + "          �Ǽ��� ,"
				+ "          �Ǽ����� ," + "          ��ע"
				+ "        ) values (?,?,?,?,?,null,?,?,?)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			// xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				InvoiceObj inv = (InvoiceObj) aList.get(i);

				ps.setInt(1, inv.getContractID());
				ps.setInt(2, inv.getInvoiceID());
				ps.setDouble(3, inv.getInvoiceAMT());
				ps.setDate(4, inv.getInvoiceDate());
				ps.setInt(5, inv.getTransactorID());
				ps.setInt(6, inv.getTransactorID());
				ps.setDate(7, inv.getInvoiceDate());
				ps.setString(8, inv.getInvoiecRemark());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== ֧����ͬ��Ʊ��ϸ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ֧����ͬ��Ʊ��ϸ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// doDataTransferForInvoiceDetail
	private static void doDataTransferForInvoiceDetail(List aList) {

		String delSql = " DELETE xmis.con_��Ʊ���߱� ";
		String insertSql = "INSERT INTO xmis.con_��Ʊ���߱�" + "        ( ��ͬID ,"
				+ "          ��Ʊ�� ," + "          ��Ʊ��� ," + "          �������� ,"
				+ "          ������ ," + "          ɨ��� ," + "          �Ǽ��� ,"
				+ "          �Ǽ����� ," + "          ��ע"
				+ "        ) values (?,?,?,?,?,null,?,?,?)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				InvoiceObj inv = (InvoiceObj) aList.get(i);

				ps.setInt(1, inv.getContractID());
				ps.setInt(2, inv.getInvoiceID());
				ps.setDouble(3, inv.getInvoiceAMT());
				ps.setDate(4, inv.getInvoiceDate());
				ps.setInt(5, inv.getTransactorID());
				ps.setInt(6, inv.getTransactorID());
				ps.setDate(7, inv.getInvoiceDate());
				ps.setString(8, inv.getInvoiecRemark());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== ��Ʊ��ϸ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ��Ʊ��ϸ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// doDataTransferForContractAttachemtn
	private static void doDataTransferForContractAttachment(List aList) {

		String delSql = " DELETE xmis.sys_���� "
				+ "DELETE xmis.sys_������������ "
				+ " insert into xmis.sys_������������ ( ������������ID ,"
				+ "          ������������ , "
				+ "          TableName,  FieldName) values(1,'xmis.con_��ͬ.','xmis.con_��ͬ','')";

		String insertSql = "INSERT INTO xmis.sys_����" + "        ( ����ID ,"
				+ "          �ϴ�ʱ�� ," + "          �ϴ��� ," + "          �ļ��� ,"
				+ "          �������� ," + "          ������������ID ,"
				+ "          REFID        )" + " values(?,?,?,?,?,?,?) ";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				AttachmentFile aFile = (AttachmentFile) aList.get(i);

				ps.setInt(1, i + 1);
				ps.setDate(2, aFile.getUploadDate());
				ps.setInt(3, aFile.getUploadID());
				ps.setString(4, aFile.getFileName());
				ps.setBytes(5, aFile.getContent());
				ps.setInt(6, 1);
				ps.setInt(7, aFile.getRefID());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== �����ͬ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== �����ͬ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	// doDataTransferForPayoutContractAttachemtn
	private static void doDataTransferForPayoutContractAttachment(List aList) {

		// String delSql = " DELETE xmis.sys_���� DELETE xmis.sys_������������ " +
		// " insert into xmis.sys_������������ ( ������������ID ," +
		// " ������������ , " +
		// " TableName, FieldName) values(1,'xmis.con_��ͬ.','xmis.con_��ͬ','')";

		String insertSql = "INSERT INTO xmis.sys_����" + "        ( ����ID ,"
				+ "          �ϴ�ʱ�� ," + "          �ϴ��� ," + "          �ļ��� ,"
				+ "          �������� ," + "          ������������ID ,"
				+ "          REFID        )" + " values(?,?,?,?,?,?,?) ";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			// xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				AttachmentFile aFile = (AttachmentFile) aList.get(i);

				ps.setInt(1, maxAttachmentID + 1);
				ps.setDate(2, aFile.getUploadDate());
				ps.setInt(3, aFile.getUploadID());
				ps.setString(4, aFile.getFileName());
				ps.setBytes(5, aFile.getContent());
				ps.setInt(6, 1);
				ps.setInt(7, aFile.getRefID());

				ps.addBatch();
				maxAttachmentID++;

			}

			ps.executeBatch();
			System.out.println("=========== ֧����ͬ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ֧����ͬ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	// doDataTransferForProjectMember
	private static void doDataTransferForProjectMember(List aList) {

		String delSql = " DELETE xmis.prj_��Ŀ�����  " + " delete xmis.prj_��Ŀ�����Ա "
				+ " delete xmis.prj_������ȼƻ�";
		String insertSql = "INSERT INTO xmis.prj_��Ŀ�����"
				+ "        ( ��Ŀ����ID ,"
				+ "          ��ĿID ,"
				+ "          ������ID ,"
				+ "          �нӲ���ID "
				+ "        )VALUES  (?,?,-1,?)"
				+ // 1,2,3
				"      INSERT INTO xmis.xmis.prj_��Ŀ�����Ա"
				+ "		    ( ��Ŀ����ID, ��Ŀ��ԱID, �Ƿ�����, ��ע )"
				+ "		VALUES  (?,?,1,?  )" // 4,5,6
				+ " INSERT INTO xmis.prj_������ȼƻ�"
				+ "        ( ��Ŀ����ID, ��ʼ����, �������� )" + "VALUES  ( ?,?,getdate())" // 7,8,9
		;

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				ProjectTaskObj task = (ProjectTaskObj) aList.get(i);

				ps.setInt(1, task.getTaskID());
				ps.setInt(2, task.getProjectID());
				ps.setInt(3, task.getAssigedToDeptID());

				ps.setInt(4, task.getTaskID());
				ps.setInt(5, task.getAssigedToEmpID());
				ps.setString(6, task.getRemark());

				ps.setInt(7, task.getTaskID());
				ps.setDate(8, task.getBeginDate());

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== ��Ŀ��Ա��ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ��Ŀ��Ա����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	private static void doDataTransferForProvince(Map aMap) {

		String delSql = " DELETE xmis.add_ʡ ";
		String insertSql = " INSERT INTO xmis.add_ʡ "
				+ "( ʡID, ʡ����, ʡ����, ʡ���, ����ID )" + " VALUES  (?,?,?,?,-1)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);

			Iterator compaynIT = aMap.entrySet().iterator();
			for (int i = 1; i < aMap.size(); i++) {
				Map.Entry entry = (Map.Entry) compaynIT.next();
				// System.out.println(entry.getKey() + "==" + entry.getValue());

				ps.setInt(1, Type.GetInt(entry.getValue()));
				ps.setString(2, Type.getString(entry.getKey()));
				ps.setString(3, Type.getString(entry.getKey()));
				ps.setString(4, Type.getString(entry.getKey()));

				ps.addBatch();

			}

			ps.executeBatch();
			System.out.println("=========== ʡ������ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ʡ������ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	// doDataTransferContractMapping
	private static void doDataTransferForContractMapping(List aList) {

		String delSql = " DELETE xmis.con_����֧����ͬ��Ӧ�� ";
		String insertSql = "INSERT INTO xmis.con_����֧����ͬ��Ӧ��"
				+ "        ( ��ӦID ," + "          �����ͬID ,"
				+ "          ֧����ͬID ," + "          ��� ," + "          ��ע"
				+ "        ) values (?,?,?,?,?)";

		// logger.info(aList.size());

		PreparedStatement ps = null;

		try {
			xmisConn.prepareStatement(delSql).execute();

			ps = xmisConn.prepareStatement(insertSql);
			// System.out.println(aList.size());

			for (int i = 0; i < aList.size(); i++) {
				String[] conMapping = (String[]) aList.get(i);

				ps.setObject(1, Type.GetInt(conMapping[0]));
				ps.setObject(2, Type.GetInt(conMapping[1]));
				ps.setObject(3, Type.GetInt(conMapping[2]));
				ps.setObject(4, Type.GetDouble(conMapping[3]));
				ps.setObject(5, conMapping[4]);

				ps.addBatch();
			}

			ps.executeBatch();
			System.out.println("=========== ����֧����ͬ��Ӧ����ת���ɹ�");

		} catch (Exception e) {
			System.out.println("=========== ����֧����ͬ��Ӧ����ת��ʧ��");
			e.printStackTrace();
		} finally {
			try {
				ps.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	private static Map doDataTransferForCompay() {

		Map companyMap = new LinkedHashMap();

		List companyListFromJKGL = getDataListFromJKGL("crm");

		int iCount = 10;
		for (Iterator i = companyListFromJKGL.listIterator(); i.hasNext();) {

			Map map = (HashMap) i.next();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();
			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				companyMap.put(entry.getValue(), iCount + 1);

				// logger.info(entry.getValue() + "=" +
				// companyMap.get(entry.getValue()));
			}
			iCount++;

		}

		companyMap.put("��ˮ�Ƽ�", 1);
		companyMap.put("��ˮ���Զ���", 2);
		companyMap.put("ˮ��Ժ", 3);
		// companyMap.put("�����ҵ��", 1);

		doDataTransferForCompany(companyMap);

		return companyMap;

	}

	private static void doDataTransferForProvince() {

		Map provinceMap = new LinkedHashMap();

		List provinceListFromJKGL = getDataListFromJKGL("ʡ��");

		for (Iterator i = provinceListFromJKGL.listIterator(); i.hasNext();) {

			Map map = (HashMap) i.next();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();
			int id = 0;
			String name = null;
			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				if (entry.getKey().equals("�Զ����"))
					id = Type.GetInt(entry.getValue());
				else if (entry.getKey().equals("����"))
					name = Type.getString(entry.getValue());

			}

			// System.out.println(id + " = " + name);

			provinceMap.put(name, id);

		}

		doDataTransferForProvince(provinceMap);

	}

	// doDataTransferForPayoutContractProject
	private static Map doDataTransferForPayoutContractProject(Map empMap,
			Map companyMap) {

		List incomeContractListFromJKGL = getDataListFromJKGL("֧����ͬ");
		List contractListForXMIS = new ArrayList();

		Map conProjMap = new LinkedHashMap();
		Map conMap = new LinkedHashMap();
		int iCount = 0;
		for (Iterator i = incomeContractListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			ContractObj con = new ContractObj();
			ProjectObj proj = new ProjectObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				con.setContractTypeID(2);
				con.setSourceTypeID(1);

				if (entry.getKey().equals("�Զ����")) {

					con.setContractID(maxContractID + 1);
				}

				else if (entry.getKey().equals("���"))
					con.setContractNo(Type.getString(entry.getValue()));

				// else if (entry.getKey().equals("��Ŀ���")) {
				// try{
				// conProjMap.get(Type.getString(entry.getValue()));
				// proj = null;
				// }catch(Exception e){
				// proj.setProjectID(conProjMap.size() + 1);
				// proj.setProjectCode(Type.getString(entry.getValue()));
				// }
				//
				//
				// }
				else if (entry.getKey().equals("��¼�û�����")) {
					try {
						con.setRegisterID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue()))).getUserID());
					} catch (Exception e) {
						con.setRegisterID(0);
					}

				} else if (entry.getKey().equals("ǩ������")) {
					con.setSignatureDate(Type.getDate(entry.getValue()));

				} else if (entry.getKey().equals("ȫ��")) {
					con.setContractName(Type.getString(entry.getValue()));
					con.setAbbreviation(Type.getString(entry.getValue()));

				} else if (entry.getKey().equals("��˾ID"))
					con.setBuyerID(Type.GetInt(companyMap.get(Type
							.getString(entry.getValue()))));
				else if (entry.getKey().equals("������ID"))
					con.setVendorID(Type.GetInt(companyMap.get(Type
							.getString(entry.getValue()))));
				else if (entry.getKey().equals("���ҵ�λ"))
					con.setCurrencyID(1);
				else if (entry.getKey().equals("��ͬ��"))
					con.setContractAmt(Type.GetDouble(entry.getValue()));

				else if (entry.getKey().equals("��ͬ��Ҫ"))
					con.setContractSummary(Type.getString(entry.getValue()));
				else if (entry.getKey().equals("��ע"))
					con.setRemark(Type.getString(entry.getValue()));
				else if (entry.getKey().equals("�����޸�"))
					con.setUpdateDate(Type.getDate(entry.getValue()));

			}

			conProjMap.put(con.getContractNo(), con);
			maxContractID = con.getContractID();
			contractListForXMIS.add(con);
			iCount++;
		}

		doDataTransferForPaymentContract(contractListForXMIS);

		return conProjMap;

	}

	private static Map doDataTransferForContractProject(Map empMap,
			Map companyMap, Map newBuyerMap) {

		List incomeContractListFromJKGL = getDataListFromJKGL("�����ͬ");
		List contractListForXMIS = new ArrayList();

		Map conProjMap = new LinkedHashMap();
		Map conMap = new LinkedHashMap();
		int iCount = 0;
		for (Iterator i = incomeContractListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			ContractObj con = new ContractObj();
			ProjectObj proj = new ProjectObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				con.setContractTypeID(1);
				con.setSourceTypeID(1);

				if (entry.getKey().equals("�Զ����")) {

					con.setContractID(Type.GetInt(entry.getValue()));
					proj.setContractID(con.getContractID());
				} else if (entry.getKey().equals("��Ŀ���")) {
					proj.setProjectID(iCount + 1);
					proj.setProjectCode(Type.getString(entry.getValue()));

				} else if (entry.getKey().equals("��¼�û�����")) {
					// con
					// .setRegisterID(Type.GetInt(empMap.get(entry
					// .getValue())));

					try {
						con.setRegisterID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue()))).getUserID());
					} catch (Exception e) {
						con.setRegisterID(0);
					}

				} else if (entry.getKey().equals("��ͬ���"))
					con.setContractNo(Type.getString(entry.getValue()));
				else if (entry.getKey().equals("ǩ������")) {
					con.setSignatureDate(Type.getDate(entry.getValue()));
					proj.setStartDate(con.getSignatureDate());
				} else if (entry.getKey().equals("��ͬ����")) {
					con.setContractName(Type.getString(entry.getValue()));
					proj.setProjectName(con.getContractName());
					con.setProjectOBJ(proj);
				} else if (entry.getKey().equals("���"))
					con.setAbbreviation(Type.getString(entry.getValue()));
				else if (entry.getKey().equals("�׷�")){
					con.setBuyer(Type.getString(entry.getValue()));
					con.setBuyerID(Type.GetInt(companyMap.get(Type
							.getString(entry.getValue()))));
				}
				else if (entry.getKey().equals("�ҷ�"))
					con.setVendorID(Type.GetInt(companyMap.get(Type
							.getString(entry.getValue()))));
				else if (entry.getKey().equals("���ҵ�λ"))
					con.setCurrencyID(1);
				else if (entry.getKey().equals("��ͬ�ܶ�"))
					con.setContractAmt(Type.GetDouble(entry.getValue()));
				else if (entry.getKey().equals("��������"))
					con.setDeptIDOfVendor(getDeptIDMapping(Type.getString(entry
							.getValue())));

				 else if (entry.getKey().equals("�׷�����")) {
					 con.setBuyerRepresentativeName(Type.getString(entry.getValue()));
				 }

				else if (entry.getKey().equals("�ҷ�����")) {

					// con.setVendorRepresentativeID(Type.GetInt(empMap.get(Type
					// .getString(entry.getValue()))));

					try {
						con.setVendorRepresentativeID(((EmployeeObj) empMap
								.get(Type.getString(entry.getValue())))
								.getUserID());
					} catch (Exception e) {
						con.setVendorRepresentativeID(0);
					}

				} else if (entry.getKey().equals("�ʱ���"))
					con.setWarrantyDefinition(Type.getString(entry.getValue()));
				else if (entry.getKey().equals("�ʱ���ʼʱ��"))
					con.setWarrantyStartDate(Type.getDate(entry.getValue()));
				else if (entry.getKey().equals("��ͬժҪ"))
					con.setContractSummary(Type.getString(entry.getValue()));
				else if (entry.getKey().equals("��ע"))
					con.setRemark(Type.getString(entry.getValue()));
				else if (entry.getKey().equals("�����޸�ʱ��"))
					con.setUpdateDate(Type.getDate(entry.getValue()));

			}
			// System.out.println(con.getProjectOBJ().getProjectID() + "//" +
			// con.getContractID());
			
			try{
				con.setBuyerRepresentativeID(Type.GetInt(newBuyerMap.get(con.getBuyer()
						+ "~" + con.getBuyerRepresentativeName())));
				
			} catch(Exception e){
				e.printStackTrace();
				con.setBuyerRepresentativeID(0);
			}
			
			conProjMap.put(con.getProjectOBJ().getProjectCode(), con);
			// conMap.put(con.getContractID(), con);
			maxContractID = con.getContractID();

			contractListForXMIS.add(con);
			iCount++;
		}

		doDataTransferForIncomeContract(contractListForXMIS);

		return conProjMap;

	}

	/* �����׷�Ӻ�ͬ */
	private static void doDataTransferForSupplementalContract(Map conProjMap) {

		List incomeContractListFromJKGL = getDataListFromJKGL("�����ͬ׷�Ӻ�ͬ");

		List contractListForXMIS = new ArrayList();

		int iCount = 0;
		for (Iterator i = incomeContractListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			ContractObj con = new ContractObj();
			ContractObj conParent = new ContractObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				con.setContractTypeID(1);
				con.setSourceTypeID(1);

				if (entry.getKey().equals("�Զ����")) {
					// con.setContractID(maxContractID + j + 1);
					con.setContractID(maxContractID + 1);
				} else if (entry.getKey().equals("��Ŀ���")) {

					conParent = (ContractObj) conProjMap.get(Type
							.getString(entry.getValue()));

					con.setContractNo(conParent.getContractNo().equals("") ? ""
							: conParent.getContractNo() + "-׷��");
					con.setParentID(conParent.getContractID());
					con.setRegisterID(conParent.getRegisterID());
					con
							.setContractName(conParent.getContractName()
									.equals("") ? "" : conParent
									.getContractName()
									+ " ׷��");
					con
							.setAbbreviation(conParent.getAbbreviation()
									.equals("") ? "" : conParent
									.getAbbreviation()
									+ " ׷��");
					con.setBuyerID(conParent.getBuyerID());
					con.setVendorID(conParent.getVendorID());
					con.setCurrencyID(1);
					con.setDeptIDOfVendor(conParent.getDeptIDOfVendor());
					con.setVendorRepresentativeID(conParent
							.getVendorRepresentativeID());
					con.setUpdateDate(conParent.getUpdateDate());

				}

				else if (entry.getKey().equals("ǩ������"))
					con.setSignatureDate(Type.getDate(entry.getValue()));

				else if (entry.getKey().equals("���"))
					con.setContractAmt(Type.GetDouble(entry.getValue()));

				else if (entry.getKey().equals("����"))
					con.setContractSummary(Type.getString(entry.getValue()));
				else if (entry.getKey().equals("��ע"))
					con.setRemark(Type.getString(entry.getValue()));

			}

			contractListForXMIS.add(con);
			maxContractID = con.getContractID();
			iCount++;
		}

		doDataTransferForSupplementalContract(contractListForXMIS);

	}

	private static void doDataTransferForPaymentCondition(Map conProjMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("�����ͬ��������");

		List contractListForXMIS = new ArrayList();

		int iCount = 1;
		int contractID = 0;
		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			PaymentConditionObj pay = new PaymentConditionObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {
					// pay.setPaymentConditionID(Type.GetInt(entry.getValue()));
					pay.setPaymentConditionID(iCount + 1);

				} else if (entry.getKey().equals("��Ŀ���")) {

					pay.setContractID(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID());
					if (contractID == ((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID())
						iCount++;
					else {
						iCount = 1;
						pay.setPaymentConditionID(iCount);
					}
				}

				else if (entry.getKey().equals("��������"))
					pay.setDescription(Type.getString(entry.getValue()));

				else if (entry.getKey().equals("�ٷֱ�"))

					// System.out.println(entry.getValue());
					pay.setPaymentPercent((int) Type
							.GetDouble(entry.getValue()));

				else if (entry.getKey().equals("���"))
					pay.setPamymentAmt(Type.GetDouble(entry.getValue()));

			}
			contractID = pay.getContractID();
			contractListForXMIS.add(pay);
			// iCount++;
		}

		doDataTransferForPaymentCondition(contractListForXMIS);
	}

	// doDataTransferForPayoutContractPaymentDetail
	private static void doDataTransferForPayoutContractPaymentDetail(
			Map payoutConProjMap, Map empMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("֧����ͬ����");

		List contractListForXMIS = new ArrayList();

		int iCount = 1;
		int contractID = 0;
		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			PaymentDetailObj pay = new PaymentDetailObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {
					pay.setPaymentID(iCount + 1);

				} else if (entry.getKey().equals("֧����ͬ���")) {

					pay.setContractID(((ContractObj) payoutConProjMap.get(Type
							.getString(entry.getValue()))).getContractID());
					if (contractID == ((ContractObj) payoutConProjMap.get(Type
							.getString(entry.getValue()))).getContractID())
						iCount++;
					else {
						iCount = 1;
						pay.setPaymentID(iCount);
					}
				}

				else if (entry.getKey().equals("���"))
					pay.setPaymentAmt(Type.GetDouble(entry.getValue()));

				else if (entry.getKey().equals("ʱ��"))
					pay.setPaymentDate(Type.getDate(entry.getValue()));

				else if (entry.getKey().equals("������")) {
					// pay.setTransactorID(Type.GetInt(empMap.get(entry
					// .getValue())));

					try {
						pay.setTransactorID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue()))).getUserID());
					} catch (Exception e) {
						pay.setTransactorID(0);
					}

				} else if (entry.getKey().equals("��ע"))
					pay.setRemark(Type.getString(entry.getValue()));

			}
			contractID = pay.getContractID();
			contractListForXMIS.add(pay);
			// iCount++;
		}

		doDataTransferForPayoutContractPaymentDetail(contractListForXMIS);
	}

	private static void doDataTransferForPaymentDetail(Map conProjMap,
			Map empMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("�����ͬ������ϸ");

		List contractListForXMIS = new ArrayList();

		int iCount = 1;
		int contractID = 0;
		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			PaymentDetailObj pay = new PaymentDetailObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {
					pay.setPaymentID(iCount + 1);

				} else if (entry.getKey().equals("��Ŀ���")) {

					pay.setContractID(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID());
					if (contractID == ((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID())
						iCount++;
					else {
						iCount = 1;
						pay.setPaymentID(iCount);
					}
				}

				else if (entry.getKey().equals("���"))
					pay.setPaymentAmt(Type.GetDouble(entry.getValue()));

				else if (entry.getKey().equals("����"))
					pay.setPaymentDate(Type.getDate(entry.getValue()));

				else if (entry.getKey().equals("������")) {
					// pay.setTransactorID(Type.GetInt(empMap.get(entry
					// .getValue())));

					try {
						pay.setTransactorID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue()))).getUserID());
					} catch (Exception e) {
						pay.setTransactorID(0);
					}

				} else if (entry.getKey().equals("��ע"))
					pay.setRemark(Type.getString(entry.getValue()));

			}
			contractID = pay.getContractID();
			contractListForXMIS.add(pay);
			// iCount++;
		}

		doDataTransferForPaymentDetail(contractListForXMIS);
	}

	private static void doDataTransferForProjectMember(Map conProjMap,
			Map empMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("�����ͬ��Ŀ��Ա");

		List contractListForXMIS = new ArrayList();

		int iCount = 1;
		int contractID = 0;
		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			ProjectTaskObj task = new ProjectTaskObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {
					task.setTaskID(Type.GetInt(entry.getValue()));

				} else if (entry.getKey().equals("��Ŀ���")) {

					task.setProjectID(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getProjectOBJ()
							.getProjectID());
					task.setBeginDate(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getSignatureDate());
				}

				else if (entry.getKey().equals("Ա��ID")) {
					try {
						task.setAssigedToEmpID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue()))).getUserID());
						task.setAssigedToDeptID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue())))
								.getDepartmentID());
					} catch (Exception e) {
						task.setAssigedToEmpID(0);
						task.setAssigedToDeptID(0);
					}
				} else if (entry.getKey().equals("��ע"))
					task.setRemark(Type.getString(entry.getValue()));

			}
			contractListForXMIS.add(task);
			// iCount++;
		}

		doDataTransferForProjectMember(contractListForXMIS);
	}

	// doDataTransferForReceipt
	private static void doDataTransferForReceipt(Map conProjMap, Map empMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("�����ͬ�վ�");

		List contractListForXMIS = new ArrayList();

		int iCount = 1;
		int contractID = 0;
		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			InvoiceObj inv = new InvoiceObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {
					inv.setInvoiceID(iCount + 1);

				} else if (entry.getKey().equals("��Ŀ���")) {

					inv.setContractID(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID());
					if (contractID == ((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID())
						iCount++;
					else {
						iCount = 1;
						inv.setInvoiceID(iCount);
					}
				}

				else if (entry.getKey().equals("���"))
					inv.setInvoiceAMT(Type.GetDouble(entry.getValue()));

				else if (entry.getKey().equals("����"))
					inv.setInvoiceDate(Type.getDate(entry.getValue()));

				else if (entry.getKey().equals("������")) {
					// pay.setTransactorID(Type.GetInt(empMap.get(entry
					// .getValue())));

					try {
						inv.setTransactorID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue()))).getUserID());
					} catch (Exception e) {
						inv.setTransactorID(0);
					}

				} else if (entry.getKey().equals("��ע"))
					inv.setInvoiecRemark(Type.getString(entry.getValue()));

			}
			contractID = inv.getContractID();
			contractListForXMIS.add(inv);
			// iCount++;
		}

		doDataTransferForReceipt(contractListForXMIS);
	}

	// doDataTransferForPayoutContractInvoice
	private static void doDataTransferForPayoutContractInvoice(
			Map payoutConProjMap, Map empMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("֧����ͬ�������");

		List contractListForXMIS = new ArrayList();

		int iCount = 1;
		int contractID = 0;
		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			InvoiceObj inv = new InvoiceObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {
					inv.setInvoiceID(iCount + 1);

				} else if (entry.getKey().equals("֧����ͬ���")) {

					inv.setContractID(((ContractObj) payoutConProjMap.get(Type
							.getString(entry.getValue()))).getContractID());
					if (contractID == ((ContractObj) payoutConProjMap.get(Type
							.getString(entry.getValue()))).getContractID())
						iCount++;
					else {
						iCount = 1;
						inv.setInvoiceID(iCount);
					}
				}

				else if (entry.getKey().equals("���")) {
					inv.setInvoiceAMT(Type.GetDouble(Type.getString(
							entry.getValue()).replaceAll(",", "")));

				} else if (entry.getKey().equals("ʱ��"))
					inv.setInvoiceDate(Type.getDate(entry.getValue()));

				else if (entry.getKey().equals("������")) {
					// pay.setTransactorID(Type.GetInt(empMap.get(entry
					// .getValue())));

					try {
						inv.setTransactorID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue()))).getUserID());
					} catch (Exception e) {
						inv.setTransactorID(0);
					}

				} else if (entry.getKey().equals("��ע"))
					inv.setInvoiecRemark(Type.getString(entry.getValue()));

			}
			contractID = inv.getContractID();
			contractListForXMIS.add(inv);
			// iCount++;
		}

		doDataTransferForPayoutContractInvoiceDetail(contractListForXMIS);
	}

	// doDataTransferForContractInvoice
	private static void doDataTransferForContractInvoice(Map conProjMap,
			Map empMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("�����ͬ��Ʊ");

		List contractListForXMIS = new ArrayList();

		int iCount = 1;
		int contractID = 0;
		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			InvoiceObj inv = new InvoiceObj();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {
					inv.setInvoiceID(iCount + 1);

				} else if (entry.getKey().equals("��Ŀ���")) {

					inv.setContractID(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID());
					if (contractID == ((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID())
						iCount++;
					else {
						iCount = 1;
						inv.setInvoiceID(iCount);
					}
				}

				else if (entry.getKey().equals("���"))
					inv.setInvoiceAMT(Type.GetDouble(entry.getValue()));

				else if (entry.getKey().equals("����"))
					inv.setInvoiceDate(Type.getDate(entry.getValue()));

				else if (entry.getKey().equals("������")) {
					// pay.setTransactorID(Type.GetInt(empMap.get(entry
					// .getValue())));

					try {
						inv.setTransactorID(((EmployeeObj) empMap.get(Type
								.getString(entry.getValue()))).getUserID());
					} catch (Exception e) {
						inv.setTransactorID(0);
					}

				} else if (entry.getKey().equals("��ע"))
					inv.setInvoiecRemark(Type.getString(entry.getValue()));

			}
			contractID = inv.getContractID();
			contractListForXMIS.add(inv);
			// iCount++;
		}

		doDataTransferForInvoiceDetail(contractListForXMIS);
	}

	// doDataTransferForPayoutContractAttachment
	private static void doDataTransferForPayoutContractAttachment(Map conProjMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("֧����ͬ�����ļ�");

		List contractListForXMIS = new ArrayList();
		int aCount = 0;

		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				if (entry.getKey().equals("aCount")) {

					if (Type.GetInt(entry.getValue()) / pageSize * pageSize == Type
							.GetInt(entry.getValue()))
						aCount = Type.GetInt(entry.getValue()) / pageSize;
					else
						aCount = Type.GetInt(entry.getValue()) / pageSize + 1;

				}
			}
		}

		for (int z = 1; z <= aCount; z++) {

			incomePaymentConditionListFromJKGL = getDataListFromJKGL("֧����ͬ�����ļ�_"
					+ z);

			contractListForXMIS = new ArrayList();

			for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
					.hasNext();) {

				Map map = (HashMap) i.next();
				AttachmentFile aFile = new AttachmentFile();

				int mapsize = map.size();
				Iterator it = map.entrySet().iterator();

				for (int j = 0; j < mapsize; j++) {
					Map.Entry entry = (Map.Entry) it.next();

					// if (iCount == 0)
					// System.out.println(entry.getKey() + "=" +
					// entry.getValue());

					if (entry.getKey().equals("�Զ����")) {

					} else if (entry.getKey().equals("֧����ͬ���")) {

						aFile.setRefID(((ContractObj) conProjMap.get(Type
								.getString(entry.getValue()))).getContractID());
						aFile.setUploadDate(((ContractObj) conProjMap.get(Type
								.getString(entry.getValue()))).getUpdateDate());
						aFile.setUploadID(((ContractObj) conProjMap.get(Type
								.getString(entry.getValue()))).getRegisterID());

					}

					else if (entry.getKey().equals("�ļ�����"))
						aFile.setFileName(Type.getString(entry.getValue()));

					else if (entry.getKey().equals("�ļ�����"))
						aFile.setContent((byte[]) entry.getValue());

				}
				contractListForXMIS.add(aFile);
				// iCount++;
			}

			doDataTransferForPayoutContractAttachment(contractListForXMIS);
		}

	}

	// doDataTransferForContractAttachment
	private static void doDataTransferForContractAttachment(Map conProjMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("�����ͬ�����ļ�");

		List contractListForXMIS = new ArrayList();

		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			AttachmentFile aFile = new AttachmentFile();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {

				} else if (entry.getKey().equals("��Ŀ���")) {

					aFile.setRefID(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getContractID());
					aFile.setUploadDate(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getUpdateDate());
					aFile.setUploadID(((ContractObj) conProjMap.get(Type
							.getString(entry.getValue()))).getRegisterID());

				}

				else if (entry.getKey().equals("�ļ�����"))
					aFile.setFileName(Type.getString(entry.getValue()));

				else if (entry.getKey().equals("�ļ�����"))
					aFile.setContent((byte[]) entry.getValue());

			}
			contractListForXMIS.add(aFile);
			// iCount++;
		}

		maxAttachmentID = contractListForXMIS.size();
		doDataTransferForContractAttachment(contractListForXMIS);
	}

	private static void doDataTransferForContractMapping(Map conProjMap,
			Map payoutConProjMap) {

		List incomePaymentConditionListFromJKGL = getDataListFromJKGL("֧����ͬ��Ӧ�����ͬ���");

		List contractListForXMIS = new ArrayList();

		for (Iterator i = incomePaymentConditionListFromJKGL.listIterator(); i
				.hasNext();) {

			Map map = (HashMap) i.next();
			String[] conMapping = new String[5];

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();

			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				// if (iCount == 0)
				// System.out.println(entry.getKey() + "=" + entry.getValue());

				if (entry.getKey().equals("�Զ����")) {
					conMapping[0] = Type.getString(entry.getValue());

				}

				else if (entry.getKey().equals("�����ͬ���"))
					try {
						conMapping[1] = Type
								.getString(((ContractObj) conProjMap.get(Type
										.getString(entry.getValue())))
										.getContractID());
					} catch (Exception e) {
						conMapping[1] = "-1";
					}

				else if (entry.getKey().equals("֧����ͬ���"))

					conMapping[2] = Type
							.getString(((ContractObj) payoutConProjMap.get(Type
									.getString(entry.getValue())))
									.getContractID());

				else if (entry.getKey().equals("���"))
					conMapping[3] = Type.getString(entry.getValue());

				else if (entry.getKey().equals("��ע"))
					conMapping[4] = Type.getString(entry.getValue());

			}
			contractListForXMIS.add(conMapping);
			// iCount++;
		}

		doDataTransferForContractMapping(contractListForXMIS);

	}

	private static Map doDataTransferForBuyerRepresentativeName() {

		// Map crmMap = new HashMap();

		List crmMapList = new ArrayList();

		List provinceListFromJKGL = getDataListFromJKGL("�׷�����");

		for (Iterator i = provinceListFromJKGL.listIterator(); i.hasNext();) {

			String[] crmMapStr = new String[3];
			Map map = (HashMap) i.next();

			int mapsize = map.size();
			Iterator it = map.entrySet().iterator();
			int id = 0;
			String name = null;
			for (int j = 0; j < mapsize; j++) {
				Map.Entry entry = (Map.Entry) it.next();

				if (entry.getKey().equals("�׷�")) {
					// if(Type.getString(entry.getValue()).equals("���������ۺϿ������޹�˾"))
					// System.out.println("the other dept id = " +
					// Type.GetInt(companyOtherDeptMap.get(Type.getString(entry.getValue()))));

					// id =
					// Type.GetInt(companyOtherDeptMap.get(Type.getString(entry.getValue())));
					crmMapStr[1] = Type.getString(companyOtherDeptMap.get(Type
							.getString(entry.getValue())));
					crmMapStr[2] = Type.getString(entry.getValue());
					
					
				} else if (entry.getKey().equals("�׷�����"))
					// name = Type.getString(entry.getValue());
					crmMapStr[0] = Type.getString(entry.getValue());

//				else if (entry.getKey().equals("��Ŀ���"))
//					crmMapStr[2] = Type.getString(((ContractObj) conProjMap
//							.get(Type.getString(entry.getValue())))
//							.getContractID());

			}

			// System.out.println(crmMapStr[1]+ " = " + crmMapStr[0]);
			
			crmMapList.add(crmMapStr);

			// crmMap.put(name, id);

		}

		return doDataTransferBuyerRepresentativeName(crmMapList);

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		System.out.println("Data Transfer start .......");
		try {
			jkglConn = getConnection("jkgl");
			xmisConn = getConnection("xmis");

			long l = new Date().getTime();
			xmisConn.setAutoCommit(false);

			/* 1  ��Ա & ��Ա���Ŷ�Ӧ */
			Map empMap = (LinkedHashMap) doDataTransferForEmp();

			/* 2  ��˾ Data */
			Map companyMap = (LinkedHashMap) doDataTransferForCompay();

			/* 3  ʡ�� */
			doDataTransferForProvince();

			/* ==== �����ͬ ϵ������ ===== */

			/* 4  �׷����� */
			Map newBuyerMap = doDataTransferForBuyerRepresentativeName();

			/* 5  �����ͬ & ��Ŀ���� */
			Map conProjMap = (LinkedHashMap) doDataTransferForContractProject(
					empMap, companyMap, newBuyerMap);

			/* 6  ����׷�Ӻ�ͬ */
			doDataTransferForSupplementalContract(conProjMap);

			/* 7  �����ͬ�������� */
			doDataTransferForPaymentCondition(conProjMap);

			/* 8  �����ͬ������ϸ */
			doDataTransferForPaymentDetail(conProjMap, empMap);

			/* 9  �����ͬ��Ŀ��Ա */
			doDataTransferForProjectMember(conProjMap, empMap);

			/* 10  �����ͬ��Ʊ */
			doDataTransferForContractInvoice(conProjMap, empMap);

			/* 11  �����ͬ�վ� */
			doDataTransferForReceipt(conProjMap, empMap);

			/* 12  �����ͬ�����ļ� */
			doDataTransferForContractAttachment(conProjMap);

			// /* �����ͬ�豸 */
			// doDataTransferForDevice(conProjMap);

			/* ==== ֧����ͬ ϵ������ ===== */

			/* 13  ֧����ͬ ��ͬID = ��������ͬID +�� */
			Map payoutConProjMap = (LinkedHashMap) doDataTransferForPayoutContractProject(
					empMap, companyMap);

			/* 14  �����ͬ ֧����ͬ ��Ӧ */
			doDataTransferForContractMapping(conProjMap, payoutConProjMap);

			/* 15  ֧����ͬ���� */
			doDataTransferForPayoutContractPaymentDetail(payoutConProjMap,
					empMap);

			/* 16  ֧����ͬ������� */
			doDataTransferForPayoutContractInvoice(payoutConProjMap, empMap);

			/* 17  ֧����ͬ�����ļ� */
			doDataTransferForPayoutContractAttachment(payoutConProjMap);

			// /* ֧����ͬ���� */
			// doDataTransferForPayoutContractDevice(conProjMap,
			// payoutConProjMap);

			xmisConn.commit();
			System.out.println(new Date().getTime() - l);
			System.out.println("DataTransfer OK!!");

		} catch (Exception e) {
			try {
				xmisConn.rollback();
			} catch (Exception ei) {
				ei.printStackTrace();
			}
			e.printStackTrace();

		} finally {
			try {
				if (jkglConn != null)
					jkglConn.close();
				if (xmisConn != null)
					xmisConn.close();

			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

}
