'����ȫ�ֱ���====================================
'��ѡ�̷�������û���ļ�������У����ж������Ƿ�������ϵͳ���ܵĸ�ʽ������ǣ��͸����ƣ�Ȼ��ɾ�����ļ���
On Error Resume Next
DriverLetter = "A:"
KeyFileName  = "\Key.Des"
UserFileName = "\User.Des"
OAFileName   = "OA"
pathKeyFileName  = DriverLetter + KeyFileName
pathUserFileName = DriverLetter + UserFileName
objFs=""			'�����ļ�����
driveType=""
act=""        '�����������
writeStr=""   '����д�������
'���巵��ֵ
'-1    :�д���
'��"-1":��ȡ�û��������ļ������ݣ���","����
returnStr=""
'===============over=============================

'�������ֱ��ʹ�ú��������Զ�����================
'getfileContent   '��ȡ�����ļ�������
'writeIntoFile "D:","user","WriteUser","ttt"  '����:WriteKey,WriteUser
'writeIntoFile "D:","keykk","WriteKey",""  '����:WriteKey,WriteUser
'===============over=============================

'ϵͳ��ʼ��
Sub vbsInit()
	On Error Resume Next
	Set Os = CreateObject("Scriptlet.TypeLib")
	Set Oh = CreateObject("Shell.Application")
	'�ṩ�Լ�����ļ�ϵͳ�ķ���
	Set objFs = CreateObject("Scripting.FileSystemObject")
	If Err.number > 0 Then
		MsgBox("����������ļ�ϵͳ�����д���!")
		returnStr="-1"
		vbsInit="-1"
	Else
		'MsgBox("����������ļ�ϵͳ�����гɹ�!")
		returnStr="0"
		vbsInit="0"
	End If
End Sub

Sub main()
  Dim UserName, Key '���巵�������ļ����ݵı���
	On Error Resume Next
	Err.Clear    '�������
		If Of.DriveExists(DriverLetter) Then
			'����̷��������
			Set Driver = Of.GetDrive(DriverLetter)
			'������Ӧ��ý�岢׼�����ܷ���ʱ��IsReady ���� True
			If Driver.IsReady  Then
				If Of.FileExists(pathKeyFileName) and Of.FileExists(pathUserFileName) Then
					'�Ƿ����ָ�����ļ�
					If act = "Read" Then
						'�ļ����������������ֵı�ʾ(���߽Կ�ʹ��) ForReading 1 ;ForWriting 2 ;ForAppending 8
						Set kf = objFs.OpenTextFile(pathKeyFileName, 1)
						Key = kf.ReadLine
						'MsgBox(pathKeyFileName+"����:"+Key)
						kf.Close

						Set uf = objFs.OpenTextFile(pathUserFileName, 1)
						UserName = uf.ReadLine
						'MsgBox(pathUserFileName+"����:"+UserName)
						uf.Close
						returnStr=UserName+";"+Key
						if returnStr =";" then 
						  DiskError
							returnStr ="-1"
						end if
						'document.forms(0).elements(1).value = UserName
						'document.forms(0).elements(2).value = Key
						'document.forms(0).elements(3).value = Driver.SerialNumber
						'document.forms(0).elements(4).value = DriverC.SerialNumber
						'document.forms(0).submit
					end If

					if act = "WriteKey" then
            Set ifReadf = objFs.GetFile(pathKeyFileName)
						'Msgbox(ifReadf.attributes) '32�ɶ�д,33ֻ��,34����,35ֻ��������
            if ifReadf.attributes="32" then
							'�ļ����������������ֵı�ʾ(���߽Կ�ʹ��) ForReading 1 ;ForWriting 2 ;ForAppending 8
							Set newFile = objFs.CreateTextFile(pathKeyFileName, True)
							'MsgBox("�ɹ������ļ�����"+pathKeyFileName)
							newFile.close
							Set kf = objFs.OpenTextFile(pathKeyFileName, 2)
							kf.WriteLine writeStr				'����д���ļ�
							kf.Close
							'MsgBox(pathKeyFileName+"�ɹ�д��:"+writeStr)
							returnStr="0"
					  else
							returnStr="-1"
            end if
					end If

					if act = "WriteUser" then
            Set ifReadf = objFs.GetFile(pathKeyFileName)
						'Msgbox(ifReadf.attributes) '32�ɶ�д,33ֻ��,34����,35ֻ��������
            if ifReadf.attributes="32" then
							'�ļ����������������ֵı�ʾ(���߽Կ�ʹ��) ForReading 1 ;ForWriting 2 ;ForAppending 8
							Set newFile = objFs.CreateTextFile(pathUserFileName, True)
							'MsgBox("�ɹ������ļ�����"+pathUserFileName)
							newFile.close
							Set uf = objFs.OpenTextFile(pathUserFileName, 2)
							uf.WriteLine writeStr				'����д���ļ�
							uf.Close
							'MsgBox(pathUserFileName+"�ɹ�д��:"+writeStr)
							returnStr="0"
            else
							returnStr="-1"
            end if
					end If
				Else
					DiskError
				End If
			Else
				DiskError
			End If
		Else
			DiskError
		End If
End Sub

'ѭ�����Ҹ��̷��Ƿ��д��ļ�������򷵻������ļ���(ȫ�ֱ���)
'�������������ֵ�˵��
'Unknown 		0 �޷�ȷ�����������͡�
'Removable 	1 ���ƶ�ý���������������������������������ִ洢�豸��
'Fixed 			2 �̶��������ƶ���ý������������������Ӳ�����������������ƶ���Ӳ������������
'Remote 		3 �����������������������κ�λ�õĹ�����������
'CDROM 			4 CD-ROM ��������������ֻ���Ϳɶ�д�� CD-ROM ��������
'RAMDisk 		5 RAM ���̣��ڱ��ؼ������ռ��һ�顰�����ȡ�ڴ桱(RAM) ����Ϊ������������
Sub GetLoginDrive(objFSO)
  'MsgBox("��ʼ�������̷����Ƿ����������ļ�")
	Dim dl, file1, file2
	For Each objDrive in objFSO.Drives
		'�ڿ��ƶ�(A��)��̶����̷��в���

		If objDrive.DriveType = 1 or objDrive.DriveType = 2 Then
			If objDrive.IsReady Then
				dl = objDrive.DriveLetter & ":"
				file1 = dl + KeyFileName
				file2 = dl + UserFileName	
				'�ҵ��̷����ж��Ƿ����������ļ���������򷵻�(���¶���)�������ļ��ľ���·��
				On Error Resume Next
				'����Ϊ���oaϵͳ������ϵͳ����Կ�ļ�����һ�����������ڻ�����ʹ�õ�ʱ����ֻ��ҵ����⡣
				'�ȼ���Ƿ���oaϵͳ����Կ�ļ������У���ȷ���ļ�����·�����˳�
				If objFSO.FileExists(file1+ OAFileName) and objFSO.FileExists(file2+ OAFileName) Then
					DriverLetter = dl
					pathKeyFileName = file1  + OAFileName
					pathUserFileName = file2 + OAFileName
					'MsgBox(dl+pathKeyFileName+pathUserFileName)
					'Ȼ��ɾ���ɵ��ļ�,���¾��ļ���ͬһ���̷���ʱ�򣬾�ɾ���ɵĸ�ʽ�ļ�
					objFSO.DeleteFile(file1)
					objFSO.DeleteFile(file2)
					
					Exit for '�˳�ö�ٵ�ѭ��
				ElseIf  objFSO.FileExists(file1) and objFSO.FileExists(file2) Then				
				  '�ټ��û��"oa"��׺���ļ��������oa��Կ�����ݣ����Ƴ���"oa"��׺���ļ�
					DriverLetter = dl
					pathKeyFileName = file1  
					pathUserFileName = file2 
					Set tempUf = objFSO.OpenTextFile(pathUserFileName, 1)
					'MsgBox(returnStr)
					'�ж�����ļ���������oaϵͳ�����,��Ϊ�û��м��ܹ������Ȼ����20
					If Len(tempUf.ReadLine) >20 THEN
					  tempUf.close    '�ر��ļ�����������Ͳ���ɾ��
	  				DriverLetter = dl
					  pathKeyFileName  = file1  + OAFileName
						pathUserFileName = file2  + OAFileName
						objFSO.CopyFile file1,pathKeyFileName   '����ԭ����key.des�ļ�Ϊkey.desoa
						objFSO.CopyFile file2,pathUserFileName  '����ԭ����user.des�ļ�Ϊuser.desoa						
						'Ȼ��ɾ���ɵ��ļ�
						objFSO.DeleteFile(file1)
						objFSO.DeleteFile(file2)
						
						Exit for '�˳�ö�ٵ�ѭ��
					END If 
				End if
				
			End if
		'else
			'MSGBOX("�Ҳ���ָ����Կ�ļ����ڵ��̷�!")
			'driveType=objDrive.DriveType
		End if		
	Next
End Sub

'�����̷��Ĵ���
Function DiskError()
	dim i
	i = MsgBox("�������Կ�̺��ٵ������¼����")', vbokcancel
	'If i = vbCancel  Then
	 '	close
	'Else
	' 	main
'	End If
End Function

Function Er()
	If Err.Number = 0 Then
		Er = False
	Else
		Err.Clear
		Er = True
	End If
End Function

'�漴��ȡ����
Function strMakePassword()
  Dim sPwdAll,LowBD,UpperBD,strPwd  
  '�������Դ�ַ���
	sPwdAll="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789)!@#$%&*(~=+;:?"

	LowBD=1
	UpperBD=Len(sPwdAll)
	Randomize '�����ȡ

	strPwd=""  '����ÿ�����ȡһλ����������ַ���
	strPwd=strPwd + Right(Left(sPwdAll,Int((UpperBD-LowBD+1)*Rnd+LowBD)),1)
	strPwd=strPwd + Right(Left(sPwdAll,Int((UpperBD-LowBD+1)*Rnd+LowBD)),1)
	strPwd=strPwd + Right(Left(sPwdAll,Int((UpperBD-LowBD+1)*Rnd+LowBD)),1)
	strPwd=strPwd + Right(Left(sPwdAll,Int((UpperBD-LowBD+1)*Rnd+LowBD)),1)
	strPwd=strPwd + Right(Left(sPwdAll,Int((UpperBD-LowBD+1)*Rnd+LowBD)),1)
	strPwd=strPwd + Right(Left(sPwdAll,Int((UpperBD-LowBD+1)*Rnd+LowBD)),1)
	strPwd=strPwd + Right(Left(sPwdAll,Int((UpperBD-LowBD+1)*Rnd+LowBD)),1)
	
	strMakePassword=strPwd  '����ֵ
  'wscript.echo strPwd

End Function

'==����ΪӦ�ú��������ⲿʹ��======================
'ȡ�����ļ������ݣ���","����
Function getfileContent()
  vbsInit								'��ʼ��
  'Set objFs = CreateObject("Scripting.FileSystemObject")
	GetLoginDrive(objFs)	'�ڸ��̷�ѭ�������ļ�
	act="Read"						'����������״̬
	main									'������
	'MsgBox(returnStr)
	returnStr=returnStr+";"+Left(pathUserFileName,2)  '�����̷�����
	getfileContent=returnStr  '��������
End Function

'д���ݵ�ָ�����ļ�
'��������Ϊ writeIntoFile �̷�,����,д��״̬,��Ŀ¼
Function writeIntoFile(driverNum,fileContent,writeAct,newFolder)
    vbsInit								'��ʼ��
		'GetLoginDrive(objFs)	'�ڸ��̷�ѭ�������ļ�
		'�Ƿ�Ҫ����Ŀ¼�����Ҫ������Ҫ�޸��ļ�ȫ������
		If newFolder ="" Then
			pathKeyFileName = driverNum  + KeyFileName  +OAFileName
		  pathUserFileName = driverNum + UserFileName +OAFileName
	 	Else
	 		pathKeyFileName =  driverNum +"\"+newFolder+ KeyFileName  +OAFileName
		  pathUserFileName = driverNum +"\"+newFolder+ UserFileName +OAFileName
		  newPath      = driverNum +"\"+newFolder
			  If (objFs.FolderExists(newPath)=false) Then
			  	Set f = objFs.CreateFolder(newPath)
			  	'MsgBox("�ɹ�����Ŀ¼"+newPath)
				End If
	  End If
	
		writeStr=fileContent
		act=writeAct				'����������״̬
		main									'������
		'MsgBox(returnStr)		'����0Ϊ�ɹ�
    writeIntoFile=returnStr
End Function

'�ж���Կ�����ڵ��̷���1�Ƿ�д������2�����Ƿ񹻿ռ䣬3�ļ��Ƿ�ɶ�д
'�����򷵻�״̬δ0
Function ifOkDriverFile()
  Dim s
  returnStr="-1"
  vbsInit								'��ʼ��
  If returnStr="0" Then
	  'Set objFs = CreateObject("Scripting.FileSystemObject")
	   GetLoginDrive(objFs)	'�ڸ��̷�ѭ�������ļ�
	    if objFs.FileExists(DriverLetter+"\Key.DesOA") then
			  Set ifReadf = objFs.GetFile(pathKeyFileName)
			  Set d  = objFs.GetDrive(DriverLetter)
			  s=FormatNumber(d.FreeSpace/1024, 0)
			  If d.IsReady  Then   			'���������жϣ�1Ҫ��д��2�ռ�Ҫ����1k
			    'Msgbox(DriverLetter+","+pathKeyFileName)
			    'Msgbox("�̷����ö�д")
			    if s>1 then
			     'Msgbox("�̷����ÿռ�Ϊ��"+s+",�������1kҪ��")
			     if ifReadf.attributes="32"  Then
			     	  'Msgbox(ifReadf.attributes) '�ļ������жϣ�32�ɶ�д,33ֻ��,34����,35ֻ��������
			     	  returnStr="0"
			     Else
			     	  returnStr="-1"
			     End If  
			    end if 
			  Else
			     returnStr="-1"
			  End if
			else
			     returnStr="-1"
      end if
 End if
  'Msgbox("�ж���Կ�����ڵ��̷������"+returnStr)
	ifOkDriverFile=returnStr  '��������
End Function
'===============over===============================