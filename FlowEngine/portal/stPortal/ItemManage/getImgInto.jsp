<%@ page contentType="text/html;charset=GBK" %>
<%@ page import="java.util.*"%>
<%@ page import="java.sql.*"%>
<%@ page import="java.io.*"%>
<%@ page import="minstone.ItemManage.BaseDbManage"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head></head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��һ�����ݿ���������ӡ��jpgͼƬ������һ�����ݿ�</title>
<body>
��һ�����ݿ���������ӡ��jpgͼƬ������һ�����ݿ�
<%

//ע�⣺Ҫ�޸�FRAM_SEQ�ֶ�Ҫ��һ���������ڵ�ֵ�����̹����߲ſ��Կ�������
BaseDbManage db=new BaseDbManage(request.getRemoteUser());
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
    String dbUrl =db.getDBUrl();// "jdbc:oracle:thin:@10.1.0.108:1521:oanet";
    String dbUser =db.getDBUrl();// "company";
    String dbPassWord =db.getDBPassWord();// "1qaz2wsx";
    //Ҫ�޸�1
    String sql = "select V_MARK_CODE ,FRAM_SEQ ,V_MARK_NAME,V_MARK_DESC,V_MARK_CONT from zcbcompany.WF_WATERMARK";
    System.out.println("sql���:"+sql);
    Class.forName("oracle.jdbc.driver.OracleDriver");
    cn = DriverManager.getConnection(dbUrl, dbUser,dbPassWord);
    System.out.println(dbUrl+" "+dbUser+" "+dbPassWord);
    st = cn.createStatement();
    rs = st.executeQuery(sql);
    int i=0,size=0;  //Ҫ�޸�2 i
    String strI="";
    while(rs.next()){
    			i++;
    			//Ҫ�޸�3
    			fileName="c:\\"+rs.getString("V_MARK_NAME")+".jpg";
   				System.out.println("�ļ�����"+fileName);
          File file = new File(fileName);//�ļ���
					//�ֽ���
          InputStream in =  rs.getBinaryStream("V_MARK_CONT");//�ļ�����
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
					PreparedStatement ps = cn.prepareStatement("insert into wf_watermark(V_MARK_CODE ,FRAM_SEQ ,V_MARK_NAME,V_MARK_DESC,V_MARK_CONT) values(?,?,?,?,?)");
					ps.setString(1,strI.valueOf(i));
					ps.setString(2,"3930");//rs.getString("FRAM_SEQ"));//Ȩ��Ϊ�գ����򹤾߿�����
					ps.setString(3,rs.getString("V_MARK_NAME"));
					ps.setString(4,"�ܳа�"+rs.getString("V_MARK_DESC"));//Ҫ�޸�4
					ps.setBinaryStream(5,fin,size); //д�����ݿ���Ҫ�ļ����ſ���.
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
<form name="getImgInto" action="getImgInto.jsp" method="POST">
	<input name="actionFlag" type="hidden" id="actionFlag" value="submit">
	<input type="Submit" name="other_funtion" value="��������" align="MIDDLE">
</form>
�������:<%=result%><br>
</html>