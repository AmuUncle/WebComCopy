@echo ��ʼ���ɰ�װ����
@echo off

set CUR_PATH=%~dp0
set PATH=C:\Qt\Qt5.6.3\5.6.3\msvc2015\bin;%PATH%

cd ..\bin
windeployqt --no-opengl-sw --no-translations WeComCopy.exe 

cd %CUR_PATH%
echo ������װ��, �����Ȱ�װNSIS��װ�������ߣ����趨��ϵͳĿ¼��
  "C:\Program Files\NSIS\makensis.exe" WeComCopy.nsi 

