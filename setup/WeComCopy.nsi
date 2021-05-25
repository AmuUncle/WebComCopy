; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

!include "x64.nsh" #---------����64λͷ�ļ�----------
!include "Library.nsh"
!define LIBRARY_X64

; ��װ�����ʼ���峣��
!define PRODUCT_NAME "WeComCopy"
!define PRODUCT_DISPLAY_NAME "vClient Pro"
!define PRODUCT_VERSION "v8.1"
!define PRODUCT_PUBLISHER "Kedacom"
!define PRODUCT_WEB_SITE "http://www.kedacom.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\${PRODUCT_NAME}.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor /SOLID LZMA

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; �������塣
!define MUI_FONT "Tahoma"
!define MUI_FONTSIZE "9"
!define MUI_FONT_HEADER "Tahoma"
!define MUI_FONTSIZE_HEADER "9"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "res\WeComCopy.ico"
!define MUI_UNICON "res\Uninstall.ico"
!define MUI_HEADERIMAGE                                ;���Ӱ�װ���̵�ͼƬ


; ����ѡ�񴰿ڳ�������
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME
; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES
; ��װ���ҳ��
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_LANGDLL
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\${PRODUCT_NAME}"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show
RequestExecutionLevel admin

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite on
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_DISPLAY_NAME}.lnk" "$INSTDIR\${PRODUCT_NAME}.exe"
  CreateShortCut "$DESKTOP\${PRODUCT_DISPLAY_NAME}.lnk" "$INSTDIR\${PRODUCT_NAME}.exe"
  File /r "..\bin\*"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\${PRODUCT_NAME}.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${PRODUCT_NAME}.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "${PRODUCT_NAME}" "$INSTDIR\${PRODUCT_NAME}.exe -b"
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
  next:
    FindProcDLL::FindProc "${PRODUCT_NAME}.exe"
        KillProcDLL::KillProc "${PRODUCT_NAME}.exe"
    Sleep 1000
    
    nsExec::Exec 'taskkill /F /IM ${PRODUCT_NAME}.exe'
    
	Pop $R0
	IntCmp $R0 1 isrun1 norun1 norun1
	isrun1:
	StrCmp $LANGUAGE "2052" 0 +4  ;�������ģ�1033:Ӣ��

	MessageBox MB_RETRYCANCEL  "��װ�����⵽ 360ɱ���������У����˳����򲢹ر������������!" IDRETRY true1 IDCANCEL false1
        true1:
              Goto next
       false1:
              Quit

        MessageBox MB_RETRYCANCEL "Setup has detected that 360 is running, exit the program and try again!" IDRETRY true_en1 IDCANCEL false_en1
        true_en1:
             Goto next
       false_en1:
            Goto norun1
	norun1:
	;FindProcDLL::FindProc "360tray.exe"
	Pop $R0
	IntCmp $R0 1 isrun2 norun2 norun2
	isrun2:
		StrCmp $LANGUAGE "2052" 0 +4  ;�������ģ�1033:Ӣ��
		MessageBox MB_RETRYCANCEL  "��װ�����⵽ 360ɱ���������У����˳����򲢹ر������������!" IDRETRY true2 IDCANCEL false2
		true2:
      Goto next
    false2:
      Quit
		MessageBox MB_RETRYCANCEL "Setup has detected that 360 is running, exit the program and try again!" IDRETRY true_en2 IDCANCEL false_en2
    true_en2:
      Goto next
    false_en2:
      Goto norun2
	norun2:

FunctionEnd

/******************************
 *  �����ǰ�װ���������������  *
 ******************************/
Function .onInstSuccess
    ExecShell "" "$INSTDIR\${PRODUCT_NAME}.exe" "-b"
FunctionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

Section Uninstall
  	; ���������Ŀ¼���ļ�������ļ���--˳���ܵߵ�
  RMDir /r "$INSTDIR\log"
  Delete "$INSTDIR\*.*"

  Delete "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\Website.lnk"
  Delete "$DESKTOP\${PRODUCT_DISPLAY_NAME}.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_DISPLAY_NAME}.lnk"
  Delete "$DOCUMENTS\${PRODUCT_NAME}\${PRODUCT_NAME}.ini"

  RMDir "$SMPROGRAMS\${PRODUCT_NAME}"

  RMDir /r "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  DeleteRegValue HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "${PRODUCT_NAME}"
  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
StrCmp $LANGUAGE "2052" 0 +3  ;�������ģ�1033:Ӣ��
  	MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name)���������е������" IDYES +4
  	Quit
  	MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove, $(^Name), and all its components?" IDYES +2
  	Quit
 FindProcDLL::FindProc "${PRODUCT_NAME}.exe"
    KillProcDLL::KillProc "${PRODUCT_NAME}.exe"
 Sleep 1000
 nsExec::Exec 'taskkill /F /IM ${PRODUCT_NAME}.exe'
 Delete "$INSTDIR\${PRODUCT_NAME}.exe"
 IfFileExists $INSTDIR\${PRODUCT_NAME}.exe 0 +7 ;ɾ��ʧ��, ���� +9
 StrCmp $LANGUAGE "2052" 0 +3  ;�������ģ�1033:Ӣ��
  	MessageBox MB_ICONINFORMATION|MB_OK "${PRODUCT_NAME}.exe �ļ���ռ�ã����˳�������!"
  	Goto +2
  	MessageBox MB_ICONINFORMATION|MB_OK "${PRODUCT_NAME}.exe File is occupied, the installation fails !"
  	Quit
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  StrCmp $LANGUAGE "2052" 0 +3  ;�������ģ�1033:Ӣ��
  	MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش����ļ�����Ƴ���"
  	Goto +2
  	MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) has been successfully removed from your computer."
FunctionEnd
