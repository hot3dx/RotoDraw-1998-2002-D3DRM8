# Microsoft Developer Studio Project File - Name="RotoDraw3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RotoDraw3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RotoDraw3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RotoDraw3D.mak" CFG="RotoDraw3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RotoDraw3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RotoDraw3D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RotoDraw3D - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "RotoDraw3D - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 d3d9.lib d3drm.lib ddraw.lib dxguid.lib d3dxof.lib kernel32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "RotoDraw3D - Win32 Release"
# Name "RotoDraw3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3dpic.cpp
# End Source File
# Begin Source File

SOURCE=.\BuyMeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraMoveRotationDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraMoveRotationVars.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\color.cpp
# End Source File
# Begin Source File

SOURCE=.\CopyPosRotScaleCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\cubedx.cpp
# End Source File
# Begin Source File

SOURCE=.\D3DXFile.cpp
# End Source File
# Begin Source File

SOURCE=.\data3d.cpp
# End Source File
# Begin Source File

SOURCE=.\Geometry.cpp
# End Source File
# Begin Source File

SOURCE=.\grid.cpp
# End Source File
# Begin Source File

SOURCE=.\hdxpaletteio.cpp
# End Source File
# Begin Source File

SOURCE=.\hobfileio.cpp
# End Source File
# Begin Source File

SOURCE=.\hobread.cpp
# End Source File
# Begin Source File

SOURCE=.\hobwrite.cpp
# End Source File
# Begin Source File

SOURCE=.\keytoheaven.cpp
# End Source File
# Begin Source File

SOURCE=.\MaterialDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MaterialDlgHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\PicHelpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RotoDraw3D.cpp
# End Source File
# Begin Source File

SOURCE=.\RotoDraw3D.rc
# End Source File
# Begin Source File

SOURCE=.\RotoDraw3DDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RotoSplash.cpp
# End Source File
# Begin Source File

SOURCE=.\sceneobjects.cpp
# End Source File
# Begin Source File

SOURCE=.\scroll.cpp
# End Source File
# Begin Source File

SOURCE=.\SetObjectSizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tetra.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3dpic.h
# End Source File
# Begin Source File

SOURCE=.\BuyMeDlg.h
# End Source File
# Begin Source File

SOURCE=.\CameraMoveRotationDialog.h
# End Source File
# Begin Source File

SOURCE=.\CameraMoveRotationVars.h
# End Source File
# Begin Source File

SOURCE=.\ClipTexture.h
# End Source File
# Begin Source File

SOURCE=.\color.h
# End Source File
# Begin Source File

SOURCE=.\CopyPosRotScaleCtrl.h
# End Source File
# Begin Source File

SOURCE=.\cubedx.h
# End Source File
# Begin Source File

SOURCE=.\D3DCamera.h
# End Source File
# Begin Source File

SOURCE=.\D3DFile.h
# End Source File
# Begin Source File

SOURCE=.\data3d.h
# End Source File
# Begin Source File

SOURCE=.\Geometry.h
# End Source File
# Begin Source File

SOURCE=.\globalvars.h
# End Source File
# Begin Source File

SOURCE=.\grid.h
# End Source File
# Begin Source File

SOURCE=.\hdxdatatypes.h
# End Source File
# Begin Source File

SOURCE=.\hdxpaletteio.h
# End Source File
# Begin Source File

SOURCE=.\hobfileio.h
# End Source File
# Begin Source File

SOURCE=.\hobread.h
# End Source File
# Begin Source File

SOURCE=.\hobwrite.h
# End Source File
# Begin Source File

SOURCE=.\MaterialDlg.h
# End Source File
# Begin Source File

SOURCE=.\MaterialDlgHelp.h
# End Source File
# Begin Source File

SOURCE=.\PicHelpDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RotoDraw3D.h
# End Source File
# Begin Source File

SOURCE=.\RotoDraw3DDlg.h
# End Source File
# Begin Source File

SOURCE=.\RotoSplash.h
# End Source File
# Begin Source File

SOURCE=.\sceneobjects.h
# End Source File
# Begin Source File

SOURCE=.\scroll.h
# End Source File
# Begin Source File

SOURCE=.\SetObjectSizeDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tetra.h
# End Source File
# Begin Source File

SOURCE=.\xfiledefines.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\RotoDraw3D.ico
# End Source File
# Begin Source File

SOURCE=.\res\RotoDraw3D.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
