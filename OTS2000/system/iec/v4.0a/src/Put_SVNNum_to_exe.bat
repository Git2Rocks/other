rem
rem This file put SVN revision num into H9000 *.exe property
rem ���ļ�ʹ�þ���·���������ع������������°汾��д�����ɵ�exe�ļ�
rem 

echo %0 %1

set rc=%1.rc
set rc_tmp=%1.tmp
set subWCRev="C:\Program Files\TortoiseSVN\bin\SubWCRev.exe"
set res=Debug\%1.res

if not exist %subWCRev% goto end 
%subWCRev% . %rc%  %rc_tmp% -f
echo build %rc_tmp%

if not exist %rc_tmp% goto end 
rc.exe /l 0x804 /fo %res% /d "_AUTOVERSION"  %rc_tmp% 
echo build %res%

del %rc_tmp%

:end