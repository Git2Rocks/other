rem
rem This file put SVN revision num into H9000 *.exe property
rem ���ļ�ʹ�þ���·���������ع������������°汾��д�����ɵ�exe�ļ�
rem 

set PATH=%PATH%;C:\Program Files\TortoiseSVN\bin

cd d:\home\ems\system\plc\v4.0a\src\

SubWCRev.exe . plccmd.rc  plccmd1.rc -f
rc.exe /l 0x804 /fo "Debug\plccmd.res" /d "_AUTOVERSION"  "plccmd1.rc" 
del plccmd1.rc
