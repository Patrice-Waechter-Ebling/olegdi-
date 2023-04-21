# Microsoft Developer Studio Project File - Name="olegdi+" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=olegdi+ - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "olegdi+.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "olegdi+.mak" CFG="olegdi+ - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "olegdi+ - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 5
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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /Gr /Zp16 /MT /w /W0 /GX /O2 /I "C:\Program Files (x86)\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc0c /d "NDEBUG"
# ADD RSC /l 0xc0c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../release/olegdi+_x86.exe" /libpath:"C:\Program Files (x86)\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Lib"
# Begin Target

# Name "olegdi+ - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\olegdi+.cpp"
# End Source File
# Begin Source File

SOURCE=".\olegdi+.rc"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\olegdi+.h"
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Autheur.ico
# End Source File
# Begin Source File

SOURCE=..\res\Autheur.ico
# End Source File
# Begin Source File

SOURCE=..\res\bin1.bin
# End Source File
# Begin Source File

SOURCE=..\res\CodeBarre.ico
# End Source File
# Begin Source File

SOURCE=..\res\DISK06.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Electro.ico
# End Source File
# Begin Source File

SOURCE=.\res\fond.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico128.ico
# End Source File
# Begin Source File

SOURCE=".\res\olegdi+.ico"
# End Source File
# Begin Source File

SOURCE=".\res\olegdi+.rc2"
# End Source File
# End Group
# End Target
# End Project
