; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBlueClickDlg
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BlueClick.h"

ClassCount=6
Class1=CBlueClickApp
Class2=CBlueClickDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CButtonUI
Class5=CBuffreeHeaderCtrl
Class6=CBuffreeListCtrl
Resource3=IDD_BLUECLICK_DIALOG

[CLS:CBlueClickApp]
Type=0
HeaderFile=BlueClick.h
ImplementationFile=BlueClick.cpp
Filter=N

[CLS:CBlueClickDlg]
Type=0
HeaderFile=BlueClickDlg.h
ImplementationFile=BlueClickDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_SCROLLBAR_LIST

[CLS:CAboutDlg]
Type=0
HeaderFile=BlueClickDlg.h
ImplementationFile=BlueClickDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BLUECLICK_DIALOG]
Type=1
Class=CBlueClickDlg
ControlCount=7
Control1=IDC_CANCEL_BUTTON,button,1342242816
Control2=IDC_MIN_BUTTON,button,1342242816
Control3=IDC_MENU_BUTTON,button,1342242816
Control4=IDC_THEME_BUTTON,button,1342242816
Control5=IDC_LIST_RESOURCE,SysListView32,1342178305
Control6=IDC_BUTTON_INSERT,button,1342242816
Control7=IDC_TREE_DOWNLOAD,SysTreeView32,1342255232

[CLS:CButtonUI]
Type=0
HeaderFile=ButtonUI.h
ImplementationFile=ButtonUI.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC

[CLS:CBuffreeHeaderCtrl]
Type=0
HeaderFile=BuffreeHeaderCtrl.h
ImplementationFile=BuffreeHeaderCtrl.cpp
BaseClass=CHeaderCtrl
Filter=D
VirtualFilter=JWC

[CLS:CBuffreeListCtrl]
Type=0
HeaderFile=BuffreeListCtrl.h
ImplementationFile=BuffreeListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CBuffreeListCtrl

