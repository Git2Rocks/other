<%@ page contentType="text/html;charset=GBK" %>
<%@ page import="java.util.*"%>
<%@ page import="java.sql.*"%>
<%@ page import="java.io.*"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head></head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��һ�����ݿ�����������дǩ��jpgͼƬ������һ�����ݿ�</title>
<body>
��һ�����ݿ���������ӡ��jpgͼƬ������һ�����ݿ�
<%

request.setCharacterEncoding("GBK");
  String result="";
  String fileName="";
  String user = request.getRemoteUser();
  String actionFlag=request.getParameter("actionFlag");
  if(actionFlag==null) actionFlag="";
  if(actionFlag.equals("submit")){
  	
  	Connection cn = null;
  	Statement st = null;
  	ResultSet rs= null;

  try {
    String dbUrl = "jdbc:oracle:thin:@10.1.0.108:1521:oanet";
    String dbUser = "company";
    String dbPassWord = "1qaz2wsx";
    //Ҫ�޸�1
    //�ҳ��˿�����ݲ������¿��е���Щ��¼
    String sql = "select USER_CODE,USER_SIGN  "
								+" from  zjcompany.usersign where not exists "
								+"( select * from usersign where zjcompany.usersign.USER_CODE=usersign.USER_CODE )";
    System.out.println("sql���:"+sql);
    Class.forName("oracle.jdbc.driver.OracleDriver");
    cn = DriverManager.getConnection(dbUrl, dbUser,dbPassWord);
    System.out.println(dbUrl+" "+dbUser+" "+dbPassWord);
    st = cn.createStatement();
    rs = st.executeQuery(sql);
    int i=0,size=0; 
    String strI="";
    while(rs.next()){
    			i++;
    			//Ҫ�޸�2
    			fileName="c:\\company_picture\\zj\\"+rs.getString("USER_CODE")+".jpg";
   				System.out.println("�ļ�����"+fileName);
          File file = new File(fileName);//�ļ���
					//�ֽ���
          InputStream in =  rs.getBinaryStream("USER_SIGN");//�ļ�����
          FileOutputStream fout = new FileOutputStream(file);          
          int c;
					while ((c = in.read()) != -1){
						fout.write(c);  //���ֽ���д���ļ��Ƚϰ�ȫ�����ٶȽ���
						size++;
					}
					System.out.println("д���ļ�size:"+size);
				
				  //�ļ���
          FileInputStream fin = new FileInputStream(file);
          size= fin.available();				
          System.out.println("�������ݿ�size:"+size);
					PreparedStatement ps = cn.prepareStatement("insert into usersign(USER_CODE ,USER_SIGN) values(?,?)");
					ps.setString(1,rs.getString("USER_CODE"));
					ps.setBinaryStream(2,fin,size); //д�����ݿ���Ҫ�ļ����ſ���.
					ps.executeUpdate();
          cn.commit();
          fout.close();

    }
    rs.close();
    cn.close();
    result="�����ɹ�";
  }
  catch (Exception e) {
    System.out.println("��ȡ���ݿ���Ϣ����,��ϸ��ϢΪ:" + e.getMessage());
    result="����ʧ�ܣ�";
  }
  finally {
    try{
      if (cn != null) rs.close();
    }catch(Exception e){}
  }


  //��ʾ���
  //out.print(result);
}
%>
</body>
<form name="getImgInto" action="getStamperInto.jsp" method="POST">
	<input name="actionFlag" type="hidden" id="actionFlag" value="submit">
	<input type="Submit" name="other_funtion" value="������дǩ��" align="MIDDLE"> 
</form>
�������:<%=result%><br>
</html>