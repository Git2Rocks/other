//ͨ��HTTPЭ���¼EPORTAL�ʼ�ϵͳ
��������sUserId �û�ID��
��������sPassword �û����롣
function logonEportal(sCertUrl,sUserId,sPassword)
{
	var strURL;
	var xhreq;
	xhreq = new ActiveXObject("Microsoft.XMLHTTP");
	strUrl =sCertUrl+"?userid="+sUserId;
	strUrl += "&pass="+sPassword;
	xhreq.open("POST", strUrl, false);
	xhreq.send();
	// If we got "OK" back, then consider the post successful.
	if("OK" == xhreq.statusText){
		//do something here.
	}
	else
		alert( xhreq.statusText );
}
//ͨ��HTTPЭ�鷢���ֻ�����
��������MSGID
OAϵͳ��дֵ������Ϣ��ţ�8λ���֣�ÿ�첻���ظ���
��������SPID
OAϵͳ��дֵ��JSCNC
��������APPID
OAϵͳ��дֵ��OA
��������RECEIVER
OAϵͳ��дֵ�����շ��ֻ�����
��������SENDDATE
OAϵͳ��дֵ���������ڣ���ʽ��yyyymmdd��
��������SENDTIME
OAϵͳ��дֵ������ʱ�䣬��ʽ��hhmmss��
��������CONTENTS
OAϵͳ��дֵ������Ϣ���ݣ�70�����ֻ�140��Ӣ�ģ�
OAϵͳ����ʹ��HTTP Э��Ӧ���ͷ�������ִ�н����RET_CODE:   0   �ɹ�  -1  ʧ��	  ERR_MSG ʧ��ԭ��
function sendMMS(sSendUrl,sMsgId,sSpid,sAppId,sReceiver,sSendDate,sSendTime,sContents){
	var strURL;
	var xhreq;
	if(sSendUrl==null || sSendUrl==""){
		alert("����Ϣ�������ص�ַΪ�գ�")
		return false;
	}
	if(sMsgId==null || sMsgId==""){
		alert("����Ϣ���Ϊ�գ�");
		return false;
	}
	if(sReceiver==null || sReceiver==""){
		alert("��������ն���Ϣ���ֻ����룡");
		return false;
	}
	if(sContents==null || sContents==""){
		alert("����Ϣ�����ݲ���Ϊ�գ���");
		return false;
	}
	if(sAppId==null)
		sAppId="OA";
	if(sSpid==null)
		sSpid="JSCNC";
	xhreq = new ActiveXObject("Microsoft.XMLHTTP");
	strUrl =sSendUrl+"?MSGID="+sMsgId;
	strUrl += "&SPID="+sSpid;
	strUrl += "&APPID="+sAppId;
	strUrl += "&RECEIVER="+sReceiver;
	strUrl += "&SENDDATE="+sSendDate;
	strUrl += "&SENDTIME="+sSendTime;
	strUrl += "&CONTENTS="+sContents;
	xhreq.open("POST", strUrl, false);
	xhreq.send();
	// If we got "OK" back, then consider the post successful.
	if("OK" == xhreq.statusText){
		//do something here.
	}
	else
		alert( xhreq.statusText );
}