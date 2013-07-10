;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Name and file
  Name "qtDbf 0.9.1"
  OutFile "qtDbf-0.9.1-install.exe"

  ;Default installation folder
  InstallDir "c:\Program Files\qtDbf"

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Variables

  Var StartMenuFolder
;--------------------------------
;Interface Configuration

  !define MUI_WELCOMEFINISHPAGE_BITMAP "welcome.bmp" ; optional
  !define MUI_ICON "qtDbf.ico" ; optional
  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP "header.bmp" ; optional
  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !define MUI_LICENSEPAGE_CHECKBOX
  !insertmacro MUI_PAGE_LICENSE "license.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY

  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Hevele-Hegyi-Istvan\qtDbf" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
  !insertmacro MUI_PAGE_INSTFILES
  !define MUI_FINISHPAGE_RUN $INSTDIR\qtDbf.exe
  !define MUI_FINISHPAGE_RUN_NOTCHECKED
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Application" SecExec
  SetOutPath "$INSTDIR"
  SectionIn RO
  file QtDbf.exe
  file qt.conf

  ;Store installation folder
  WriteRegStr HKCU "Software\Hevele-Hegyi-Istvan\qtDbf" "" $INSTDIR

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\qtDbf.lnk" "$INSTDIR\qtDbf.exe"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstaller.lnk" "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

Section "Languages" SecLang

  SetOutPath "$INSTDIR\lang"
  file lang\*.qm
  
SectionEnd

Section "Required dll-s" SecDlls

  SetOutPath "$INSTDIR"
  
  file *.dll

  SetOutPath "$INSTDIR\plugins\sqldrivers"
  file plugins\sqldrivers\*.dll

  SetOutPath "$INSTDIR\plugins\imageformats"
  file plugins\imageformats\*.dll

SectionEnd

Section "Help" SecForm

  SetOutPath "$INSTDIR\help"
  
  file help\*.*

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecExec ${LANG_ENGLISH} "Installing the application"
  LangString DESC_SecLang ${LANG_ENGLISH} "Installing the language files"
  LangString DESC_SecDlls ${LANG_ENGLISH} "Installing required dll-s"
  LangString DESC_SecForm ${LANG_ENGLISH} "Installing the help files"

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecExec} $(DESC_SecExec)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecLang} $(DESC_SecLang)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDlls} $(DESC_SecDlls)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecForm} $(DESC_SecForm)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  Delete "$SMPROGRAMS\$StartMenuFolder\qtDbf.lnk" 
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstaller.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"

  Delete "$INSTDIR\lang\*.*"
  RMDir "$INSTDIR\lang"

  Delete "$INSTDIR\help\*.*"
  RMDir "$INSTDIR\help"

  Delete "$INSTDIR\plugins\sqldrivers\*.*"
  RMDir "$INSTDIR\plugins\sqldrivers"

  Delete "$INSTDIR\plugins\imageformats\*.*"
  RMDir "$INSTDIR\plugins\imageformats"

  RMDir "$INSTDIR\plugins"

  Delete "$INSTDIR\*.*"

  RMDir "$INSTDIR"

;  DeleteRegKey HKCU "Software\Hevele-Hegyi-Istvan"

SectionEnd