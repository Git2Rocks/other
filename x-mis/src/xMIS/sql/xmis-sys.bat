/*
delete xmis.add_����
delete xmis.add_��ַ
delete xmis.add_ʡ
delete xmis.sys_����״̬
delete xmis.sys_����
delete xmis.sys_��͵�ַ��
delete xmis.sys_�Ա�
delete xmis.sys_������ò
delete xmis.con_��ͬ��Դ����
delete xmis.con_��ͬ����
*/


bcp "xmis.add_����" out "xmis.add_����.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.add_��ַ" out "xmis.add_��ַ.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.add_ʡ" out "xmis.add_ʡ.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.sys_����״̬" out "xmis.sys_����״̬.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.sys_����" out "xmis.sys_����.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.sys_��͵�ַ��" out "xmis.sys_��͵�ַ��.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.sys_�Ա�" out "xmis.sys_�Ա�.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.sys_������ò" out "xmis.sys_������ò.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.con_��ͬ��Դ����" out "xmis.con_��ͬ��Դ����.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  
bcp "xmis.con_��ͬ����" out "xmis.con_��ͬ����.txt" -c -q -S "192.169.11.140" -U "xmis-uat" -P "xmis"                  

bcp "xmis.add_����" in "xmis.add_����.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                  
bcp "xmis.add_��ַ" in "xmis.add_��ַ.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                  
bcp "xmis.add_ʡ" in "xmis.add_ʡ.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                  
bcp "xmis.sys_����״̬" in "xmis.sys_����״̬.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                  
bcp "xmis.sys_����" in "xmis.sys_����.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                  
bcp "xmis.sys_��͵�ַ��" in "xmis.sys_��͵�ַ��.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                 
bcp "xmis.sys_�Ա�" in "xmis.sys_�Ա�.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                  
bcp "xmis.sys_������ò" in "xmis.sys_������ò.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"  
bcp "xmis.con_��ͬ��Դ����" in "xmis.con_��ͬ��Դ����.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                  
bcp "xmis.con_��ͬ����" in "xmis.con_��ͬ����.txt" -c -q -S "192.169.11.6\JKGL" -U "xmis" -P "xmis"                  
