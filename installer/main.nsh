; The name of the installer
Name "snowball"

; To change from default installer icon:
;Icon "snowball.ico"

; The setup filename
OutFile "snowball_Setup.exe"

; The default installation directory
InstallDir $bin\Release\

; Registry key to check for directory (so if you install again, it will
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\snowball" "Install_Dir"

RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "snowball (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there (you can add more File lines too)
  File "snowball.exe"
  ; Wildcards are allowed:
  ; File *.dll
  ; To add a folder named MYFOLDER and all files in it recursively, use this EXACT syntax:
  ; File /r MYFOLDER\*.*
  ; See: https://nsis.sourceforge.io/Reference/File
  ; MAKE SURE YOU PUT ALL THE FILES HERE IN THE UNINSTALLER TOO

  File "..\..\libsnowballrt.so"

  CopyFiles /SILENT /FILESONLY "$INSTDIR\lib" "..\..\libsnowballrt.so"

  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\snowball "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\snowball" "DisplayName" "snowball"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\snowball" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\snowball" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\snowball" "NoRepair" 1
  WriteUninstaller "$INSTDIR\uninstall.exe"

SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts (required)"
  SectionIn RO

  CreateDirectory "$SMPROGRAMS\snowball"
  CreateShortcut "$SMPROGRAMS\snowball\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\snowball\snowball.lnk" "$INSTDIR\snowball.exe" "" "$INSTDIR\snowball.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\snowball"
  DeleteRegKey HKLM SOFTWARE\snowball

  ; Remove files and uninstaller
  ; MAKE SURE NOT TO USE A WILDCARD. IF A
  ; USER CHOOSES A STUPID INSTALL DIRECTORY,
  ; YOU'LL WIPE OUT OTHER FILES TOO
  Delete $INSTDIR\snowball.exe
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\snowball\*.*"

  ; Remove directories used (only deletes empty dirs)
  RMDir "$SMPROGRAMS\snowball"
  RMDir "$INSTDIR"

SectionEnd