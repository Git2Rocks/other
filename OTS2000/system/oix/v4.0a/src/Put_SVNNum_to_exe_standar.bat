rem
rem This file put SVN revision num into H9000 *.exe property
rem ���ļ�ʹ�þ���·���������ع������������°汾��д�����ɵ�exe�ļ�
rem 
rem

set PATH=%PATH%;d:\Program Files\TortoiseSVN\bin

cd d:\home\ems\system\oix\v4.0a\src\

SubWCRev.exe . oix.rc   oix1.rc -f
rc.exe /l 0x804 /fo "oix.res" /d "_AUTOVERSION"  "oix1.rc" 
del "oix1.rc"