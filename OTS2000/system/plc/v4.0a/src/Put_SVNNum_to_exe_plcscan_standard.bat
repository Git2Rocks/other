rem
rem This file put SVN revision num into H9000 *.exe property
rem ���ļ�ʹ�þ���·���������ع������������°汾��д�����ɵ�exe�ļ�
rem 

set PATH=%PATH%;C:\Program Files\TortoiseSVN\bin

cd d:\home\ems\system\plc\v4.0a\src\

SubWCRev.exe . plcscan.rc  plcscan1.rc -f
rc.exe /l 0x804 /fo "Debug\plcscan.res" /d "_AUTOVERSION"  "plcscan1.rc" 
del plcscan1.rc
