!define APPNAME "Countdown"
!define COMPANYNAME "Anthony Shoumikhin"

outfile "InstallCountdown.exe"
!define HELPURL "http://shoumikh.in"

RequestExecutionLevel admin
installDir "$PROGRAMFILES\${APPNAME}"

section

    setOutPath "$INSTDIR"

    file "Countdown.exe"
    file "QtCore4.dll"
    file "QtGui4.dll"

    writeUninstaller "$INSTDIR\uninstall.exe"

    createDirectory "$SMPROGRAMS\${APPNAME}"
    createShortCut "$SMPROGRAMS\${APPNAME}\Countdown.lnk" "$INSTDIR\Countdown.exe"
    createShortCut "$SMPROGRAMS\${APPNAME}\uninstall.lnk" "$INSTDIR\uninstall.exe"

sectionEnd

section "Uninstall"

    delete "$SMPROGRAMS\${APPNAME}\uninstall.lnk"
    delete "$SMPROGRAMS\${APPNAME}\Countdown.lnk"
    rmDir "$SMPROGRAMS\${APPNAME}"

    delete "$INSTDIR\Countdown.exe"
    delete "$INSTDIR\QtCore4.dll"
    delete "$INSTDIR\QtGui4.dll"

    delete "$INSTDIR\uninstall.exe"
    rmDir "$INSTDIR"

sectionEnd
