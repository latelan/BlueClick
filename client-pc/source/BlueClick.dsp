# Microsoft Developer Studio Project File - Name="BlueClick" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BlueClick - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BlueClick.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BlueClick.mak" CFG="BlueClick - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BlueClick - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BlueClick - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BlueClick - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 netapi32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BlueClick - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 netapi32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BlueClick - Win32 Release"
# Name "BlueClick - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AnimateButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BlueClick.cpp
# End Source File
# Begin Source File

SOURCE=.\BlueClick.rc
# End Source File
# Begin Source File

SOURCE=.\BlueClickDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BuffreeEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\BuffreeHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BuffreeListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BuffreeMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BuffreeTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Converter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDownloadList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewShare.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgResourceList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgServerSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSplash.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSuspension.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSystemSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgThemeSelecter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUploadList.cpp
# End Source File
# Begin Source File

SOURCE=.\DownloadSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\DownloadThread.cpp
# End Source File
# Begin Source File

SOURCE=.\FileMD5.cpp
# End Source File
# Begin Source File

SOURCE=.\Json.cpp
# End Source File
# Begin Source File

SOURCE=.\ListenSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\OnlineSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\QuerySocket.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceThread.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TransStatic.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AnimateButton.h
# End Source File
# Begin Source File

SOURCE=.\BlueClick.h
# End Source File
# Begin Source File

SOURCE=.\BlueClickDlg.h
# End Source File
# Begin Source File

SOURCE=.\BuffreeEdit.h
# End Source File
# Begin Source File

SOURCE=.\BuffreeHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BuffreeListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BuffreeMessageBox.h
# End Source File
# Begin Source File

SOURCE=.\BuffreeTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Converter.h
# End Source File
# Begin Source File

SOURCE=.\DlgDownloadList.h
# End Source File
# Begin Source File

SOURCE=.\DlgNewShare.h
# End Source File
# Begin Source File

SOURCE=.\DlgResourceList.h
# End Source File
# Begin Source File

SOURCE=.\DlgServerSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgSplash.h
# End Source File
# Begin Source File

SOURCE=.\DlgSuspension.h
# End Source File
# Begin Source File

SOURCE=.\DlgSystemSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgThemeSelecter.h
# End Source File
# Begin Source File

SOURCE=.\DlgUploadList.h
# End Source File
# Begin Source File

SOURCE=.\DownloadSocket.h
# End Source File
# Begin Source File

SOURCE=.\DownloadThread.h
# End Source File
# Begin Source File

SOURCE=.\FileMD5.h
# End Source File
# Begin Source File

SOURCE=.\Json.h
# End Source File
# Begin Source File

SOURCE=.\ListenSocket.h
# End Source File
# Begin Source File

SOURCE=.\OnlineSocket.h
# End Source File
# Begin Source File

SOURCE=.\QuerySocket.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchSocket.h
# End Source File
# Begin Source File

SOURCE=.\ServiceSocket.h
# End Source File
# Begin Source File

SOURCE=.\ServiceThread.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TransStatic.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BlueClick.ico
# End Source File
# Begin Source File

SOURCE=.\res\BlueClick.rc2
# End Source File
# Begin Source File

SOURCE=.\res\LOGO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
