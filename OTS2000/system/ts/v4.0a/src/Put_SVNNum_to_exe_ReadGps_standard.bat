rem
rem This file put SVN revision num into H9000 *.exe property
rem ���ļ�ʹ�þ���·���������ع������������°汾��д�����ɵ�exe�ļ�
rem 

set PATH=%PATH%;C:\Program Files\TortoiseSVN\bin

cd d:\home\ems\system\ts\v4.0a\src\

SubWCRev.exe . ReadGps.rc  ReadGps1.rc -f
rc.exe /l 0x804 /fo "Debug\ReadGps.res" /d "_AUTOVERSION"  "ReadGps1.rc" 
del ReadGps1.rc
