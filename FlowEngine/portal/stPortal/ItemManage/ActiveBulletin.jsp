<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="java.util.*,java.sql.*"%>
<%@ page import="baseserverjb.BaseServerClient,baseserverjb.IFramework"%>

<%!
  public Hashtable getSheetNameHt(){
    Hashtable ht = new Hashtable();
    ht.put("��������","/STPublish/view/ViewFolder.jsp?folder_code=71_72_75");//��������
    ht.put("�����³�Ͷ�ʾ��߹���ίԱ��","/STPublish/view/ViewFolder.jsp?folder_code=71_72_75");//�����³�Ͷ�ʾ��߹���ίԱ��
    ht.put("���¾�","/STPublish/view/ViewFolder.jsp?folder_code=71_72_75");//���¾�
    
    ht.put("�齭����","/STPublish/view/ViewFolder.jsp?folder_code=71_73_212");//�齭Ͷ�ʼ���
    ht.put("�б�����","/STPublish/view/ViewFolder.jsp?folder_code=71_73_212");//�б�����
    ht.put("֧������","/STPublish/view/ViewFolder.jsp?folder_code=71_73_212");//֧������
    ht.put("��Ϣ���칫��","/STPublish/view/ViewFolder.jsp?folder_code=71_73_212");//��Ϣ���칫��
    ht.put("���»�","/STPublish/view/ViewFolder.jsp?folder_code=71_73_212");//���»�   
    
    ht.put("�齭�ܳа�����","/STPublish/view/ViewFolder.jsp?folder_code=71_74_261");//�齭�ܳа�����
  
    return ht;
  }
%>
<%
  //System.out.println("test:aaaaaaaaaaaaaaaaaa");
  
  String user = request.getRemoteUser();
  if(user==null)
  	user="admin_hs";
  //System.out.println("��ǰ�û���"+user);
  
  String framName = null;
  String bulletinUrl = null;
  String dept =null;

  Connection cn = null;
  Statement st = null;
  ResultSet rs= null;

  BaseServerClient bsc=new BaseServerClient(user);
  IFramework ifw= bsc.getFramework();
  String framSeq2=ifw.getDeptSeqFromRoot(user,1);
  
  try {
    String dbUrl = "jdbc:oracle:thin:@10.1.0.108:1521:oanet";
    String dbUser = "company";
    String dbPassWord = "1qaz2wsx";
    
    //String sql = "select framName2 from V_RPT_FRAMEDEPARTMENT where user_code = '" + user + "'";
    String sql = "select FRAM_NAME from FRAMEWORK where FRAM_SEQ = '" + framSeq2 + "'";
    //out.println("sql���:"+sql);
    Class.forName("oracle.jdbc.driver.OracleDriver");
    cn = DriverManager.getConnection(dbUrl, dbUser,dbPassWord);
    st = cn.createStatement();
    rs = st.executeQuery(sql);
    if (rs.next()){
      framName = rs.getString(1);
    }
  }
  catch (Exception e) {
    out.println("��ȡ�û�������������,��ϸ��ϢΪ:" + e.getMessage());
  }
  finally {
    try{
      if (cn != null) rs.close();
    }catch(Exception e){}
  }

  System.out.println("��ǰ���ţ�"+framName);
 
  Hashtable bulletinUrlHt = getSheetNameHt();
  bulletinUrl = (String)bulletinUrlHt.get(framName);
  if (framName == null || framName.equals("")){
      //������û���û�з�������֯�ܹ���,����ʾ"�˲���Ƹ"
      bulletinUrl = "/STPublish/view/ViewFolder.jsp?folder_code=71_263";
  }
  //���߲��������ļ���������˾��,����ʾ"�˲���Ƹ"
  if (bulletinUrl == null || bulletinUrl.equals("")){
    bulletinUrl = "/STPublish/view/ViewFolder.jsp?folder_code=71_263";
  }
  //System.out.println("��ǰurlΪ��"+bulletinUrl);
  response.sendRedirect(bulletinUrl);
%>
