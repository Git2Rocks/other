rem
rem This file put SVN revision num into H9000 *.exe property
rem ���ļ�ʹ�þ���·���������ع������������°汾��д�����ɵ�exe�ļ�
rem 

set PATH=%PATH%;C:\Program Files\TortoiseSVN\bin

cd d:\home\ems\system\plc\v4.0a\src\

SubWCRev.exe . plcmon.rc  plcmon1.rc -f
rc.exe /l 0x804 /fo "Debug\plcmon.res" /d "_AUTOVERSION"  "plcmon1.rc" 
del plcmon1.rc
