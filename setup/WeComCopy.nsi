; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

!include "x64.nsh" #---------加入64位头文件----------
!include "Library.nsh"
!define LIBRARY_X64

; 安装程序初始定义常量
!define PRODUCT_NAME "WeComCopy"
!define PRODUCT_DISPLAY_NAME "WeComCopy"
!define PRODUCT_VERSION "v8.1"
!define PRODUCT_PUBLISHER "Kedacom"
!define PRODUCT_WEB_SITE "http://www.kedacom.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\${PRODUCT_NAME}.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor /SOLID LZMA

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; 设置字体。
!define MUI_FONT "Tahoma"
!define MUI_FONTSIZE "9"
!define MUI_FONT_HEADER "Tahoma"
!define MUI_FONTSIZE_HEADER "9"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "res\WeComCopy.ico"
!define MUI_UNICON "res\Uninstall.ico"
!define MUI_HEADERIMAGE                                ;增加安装过程的图片


; 语言选择窗口常量设置
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_LANGDLL
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

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

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

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
	StrCmp $LANGUAGE "2052" 0 +4  ;简体中文，1033:英文

	MessageBox MB_RETRYCANCEL  "安装程序检测到 360杀毒正在运行，请退出程序并关闭浏览器后重试!" IDRETRY true1 IDCANCEL false1
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
		StrCmp $LANGUAGE "2052" 0 +4  ;简体中文，1033:英文
		MessageBox MB_RETRYCANCEL  "安装程序检测到 360杀毒正在运行，请退出程序并关闭浏览器后重试!" IDRETRY true2 IDCANCEL false2
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
 *  以下是安装程序的自启动部分  *
 ******************************/
Function .onInstSuccess
    ExecShell "" "$INSTDIR\${PRODUCT_NAME}.exe" "-b"
FunctionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
  	; 清除所有子目录的文件，清除文件夹--顺序不能颠倒
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

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
StrCmp $LANGUAGE "2052" 0 +3  ;简体中文，1033:英文
  	MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name)，及其所有的组件？" IDYES +4
  	Quit
  	MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove, $(^Name), and all its components?" IDYES +2
  	Quit
 FindProcDLL::FindProc "${PRODUCT_NAME}.exe"
    KillProcDLL::KillProc "${PRODUCT_NAME}.exe"
 Sleep 1000
 nsExec::Exec 'taskkill /F /IM ${PRODUCT_NAME}.exe'
 Delete "$INSTDIR\${PRODUCT_NAME}.exe"
 IfFileExists $INSTDIR\${PRODUCT_NAME}.exe 0 +7 ;删除失败, 跳到 +9
 StrCmp $LANGUAGE "2052" 0 +3  ;简体中文，1033:英文
  	MessageBox MB_ICONINFORMATION|MB_OK "${PRODUCT_NAME}.exe 文件被占用，请退出后重试!"
  	Goto +2
  	MessageBox MB_ICONINFORMATION|MB_OK "${PRODUCT_NAME}.exe File is occupied, the installation fails !"
  	Quit
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  StrCmp $LANGUAGE "2052" 0 +3  ;简体中文，1033:英文
  	MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
  	Goto +2
  	MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) has been successfully removed from your computer."
FunctionEnd
