<%@ page contentType="text/html; charset=GBK" %>
<%@ page import="suntek.report.structure.v10.FilterFieldObject,
                 suntek.report.structure.v10.FilterFieldStruct,
                 suntek.report.generator.ParametersGenerator,
                 java.util.Hashtable,
		 baseserverjb.BaseServerClient,
                 com.minstone.report.Base64Encoder,
                 java.sql.*"
%>
<%
  String m_sUser="",rpt_code="";
  Hashtable m_hs=null;
  byte[] btemp;
  int size;

  FilterFieldObject ffo=null;

  try{
    m_sUser = request.getRemoteUser();

  }catch(Exception e){
    out.println("��ȡ�������� generateFFO.jsp Error " + e.getMessage());
  }
  ffo=new FilterFieldObject();

  rpt_code=request.getParameter("rpt_code");//������
  size=new Integer(request.getParameter("size")).intValue();//��������
  for (int i=0;i<size;i++){
    int id=new Integer(request.getParameter("id"+i)).intValue();//���
    String list_id=request.getParameter("list_id"+i);//�б���
    String listName=request.getParameter("listName"+i);//�б�����
    String listValueType=request.getParameter("listValueType");
    btemp=listName.getBytes("iso8859-1");
    listName=new String(btemp);
    String fieldType=request.getParameter("fieldType"+i);//�ֶ�����
    btemp=fieldType.getBytes("iso8859-1");
    fieldType=new String(btemp);
    String fieldName=request.getParameter("fieldName"+i);//�ֶ�����
    btemp=fieldName.getBytes("iso8859-1");
    fieldName=new String(btemp);
    String operator=request.getParameter("operator"+i);//������
    btemp=operator.getBytes("iso8859-1");
    operator=new String(btemp);
    String desc=request.getParameter("desc"+i);//�ֶ�����
    //String desc=java.net.URLDecoder.decode(request.getParameter("desc"+i));//�ֶ�����
    btemp=desc.getBytes("iso8859-1");
    //desc=new String(btemp);
    String dataSource=request.getParameter("dataSource"+i);//
    String valueCol=request.getParameter("valueCol"+i);//ֵ��
    String displayCol=request.getParameter("displayCol"+i);//��ʾ��
    String andor=request.getParameter("andor"+i);//�������ӷ�
    btemp=andor.getBytes("iso8859-1");
    andor=new String(btemp);
    String defaultValue=request.getParameter("defaultValue"+i);//ȱʡֵ
    //String defaultValue=java.net.URLDecoder.decode(request.getParameter("defaultValue"+i));//ȱʡֵ
    //btemp=defaultValue.getBytes("iso8859-1");
    //defaultValue=new String(btemp);
    int iListValueType=listValueType==null?0:Integer.parseInt(listValueType);

    FilterFieldStruct ffs=new FilterFieldStruct();
    ffs.setRpt_code(rpt_code);
    ffs.setId(id);
    ffs.setList_id(list_id);
    ffs.setListName(listName);
    ffs.setListValueType(iListValueType);
    ffs.setFieldType(fieldType);
    ffs.setFieldName(fieldName);
    ffs.setOperator(operator);
    ffs.setDesc(desc);
    ffs.setDataSource(dataSource);
    ffs.setValueCol(valueCol);
    ffs.setDisplayCol(displayCol);
    ffs.setAndor(andor);
    ffs.setDefaultValue(defaultValue);

    ffo.addFilter(ffs);
  }

  String ret="";
  Connection metaConnection = null;
  try{
    metaConnection=BaseServerClient.getConnection(request.getRemoteUser());
    if (metaConnection!=null){
      ParametersGenerator temp=new ParametersGenerator(rpt_code,metaConnection);
      ret=temp.genrateSQLConditionE(ffo);
    }
    //��SQL����е������ַ��������ַ��滻,ʹ����ҳ���������ʱ������ִ���
	Base64Encoder base64=new Base64Encoder();
    ret=base64.encode(ret);
    //System.err.println("encodeC="+ret);
  }catch(Exception e){
    out.print("��ȡ�û���ѯ����ʧ�� generateFFO.jsp Error!");
  }finally{
    if(metaConnection != null)
      metaConnection.close();
  }
%>
<script language="javascript">
  window.parent.getSQL("<%=ret%>");//�򸸴��ڷ��ػ�ȡ���û���ѯ����
</script>