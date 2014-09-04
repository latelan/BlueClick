; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBlueClickDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BlueClick.h"

ClassCount=17
Class1=CBlueClickApp
Class2=CBlueClickDlg
Class3=CAboutDlg

ResourceCount=18
Resource1=IDD_BLUECLICK_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_DLGRESOURCELIST_DIALOG
Class4=CDlgResourceList
Resource4=IDD_DLGTHEMESELECTER_DIALOG
Class5=CDlgDownloadList
Resource5=IDD_DLGUPLOADLIST_DIALOG
Class6=CDlgUploadList
Resource6=IDR_MENU_SYSTEM
Class7=CDlgSplash
Resource7=IDD_DLGSERVERSETTING_DIALOG
Resource8=IDD_ABOUTBOX
Resource9=IDR_MENU_DOWNLOAD
Resource10=IDD_BUFFREEMESSAGEBOX_DIALOG
Resource11=IDD_DLGSYSTEMSETTING_DIALOG
Class8=CBuffreeMessageBox
Class9=CUdpSocket
Resource12=IDR_MENU_RESOURCE
Class10=CDlgSystemSetting
Resource13=IDD_DLGSUSPENSION_DIALOG
Class11=CDlgServerSetting
Resource14=IDD_DLGNEWSHARE_DIALOG
Class12=CDlgSuspension
Resource15=IDD_DLGDOWNLOADLIST_DIALOG
Resource16=IDD_DLGSPLASH_DIALOG
Class13=CDlgNewShare
Resource17=IDR_MENU_UPLOAD
Class14=CDlgThemeSelecter
Class15=CBuffreeEdit
Class16=CServiceSocket
Class17=CQuerySocket
Resource18=IDR_MENU_SUSPENSION

[CLS:CBlueClickApp]
Type=0
HeaderFile=BlueClick.h
ImplementationFile=BlueClick.cpp
Filter=N
LastObject=CBlueClickApp

[CLS:CBlueClickDlg]
Type=0
HeaderFile=BlueClickDlg.h
ImplementationFile=BlueClickDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CBlueClickDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=BlueClickDlg.h
ImplementationFile=BlueClickDlg.cpp
Filter=W
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_BLUECLICK_DIALOG]
Type=1
Class=CBlueClickDlg
ControlCount=15
Control1=IDC_BUTTON_THEME,button,1342242816
Control2=IDC_BUTTON_MENU,button,1342242816
Control3=IDC_BUTTON_MIN,button,1342242816
Control4=IDC_BUTTON_CANCEL,button,1342242816
Control5=IDC_BUTTON_RESOURCE_LIST_TAB,button,1342242816
Control6=IDC_BUTTON_DOWNLOAD_LIST_TAB,button,1342242816
Control7=IDC_BUTTON_UPLOAD_LIST_TAB,button,1342242816
Control8=IDC_TREE_IDC_TREE_DOWNLOAD,SysTreeView32,1342251136
Control9=IDC_STATIC_TAB,static,1342308352
Control10=IDC_EDIT_SEARCH,edit,1342242816
Control11=IDC_BUTTON_SEARCH,button,1342242817
Control12=IDC_STATIC_CAPTION,static,1342308352
Control13=IDC_STATIC_LOGO,static,1342177294
Control14=IDC_STATIC_STATUS,static,1342308352
Control15=IDC_STATIC_PEER_NUM_ONLINE,static,1342308352

[DLG:IDD_DLGRESOURCELIST_DIALOG]
Type=1
Class=CDlgResourceList
ControlCount=1
Control1=IDC_LIST_RESOURCE,SysListView32,1342243841

[CLS:CDlgResourceList]
Type=0
HeaderFile=DlgResourceList.h
ImplementationFile=DlgResourceList.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=CDlgResourceList

[DLG:IDD_DLGDOWNLOADLIST_DIALOG]
Type=1
Class=CDlgDownloadList
ControlCount=1
Control1=IDC_LIST_UPLOAD,SysListView32,1342243841

[CLS:CDlgDownloadList]
Type=0
HeaderFile=DlgDownloadList.h
ImplementationFile=DlgDownloadList.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgDownloadList

[DLG:IDD_DLGUPLOADLIST_DIALOG]
Type=1
Class=CDlgUploadList
ControlCount=1
Control1=IDC_LIST_UPLOAD,SysListView32,1342243841

[CLS:CDlgUploadList]
Type=0
HeaderFile=DlgUploadList.h
ImplementationFile=DlgUploadList.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_MENUITEM_DELETE_SHARE

[DLG:IDD_DLGSPLASH_DIALOG]
Type=1
Class=CDlgSplash
ControlCount=1
Control1=IDC_STATIC_SPLASH_MSG,static,1342308352

[CLS:CDlgSplash]
Type=0
HeaderFile=DlgSplash.h
ImplementationFile=DlgSplash.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=CDlgSplash

[MNU:IDR_MENU_DOWNLOAD]
Type=1
Class=CDlgDownloadList
Command1=ID_MENUITEM_CONTINUE_DOWNLOAD
Command2=ID_MENUITEM_PAUSE_DOWNLOAD
Command3=ID_MENUITEM_DELETE_DOWNLOAD
CommandCount=3

[MNU:IDR_MENU_RESOURCE]
Type=1
Class=?
Command1=ID_MENUITEM_START_DOWNLOAD
CommandCount=1

[MNU:IDR_MENU_UPLOAD]
Type=1
Class=?
Command1=ID_MENUITEM_NEW_SHARE
Command2=ID_MENUITEM_DELETE_SHARE
CommandCount=2

[MNU:IDR_MENU_SYSTEM]
Type=1
Class=?
Command1=ID_MENUITEM_SYSTEM_SETTING
Command2=ID_MENUITEM_ABOUT_US
Command3=ID_MENUITEM_QUIT_PROG
CommandCount=3

[DLG:IDD_BUFFREEMESSAGEBOX_DIALOG]
Type=1
Class=CBuffreeMessageBox
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_MSG,static,1342308353

[CLS:CBuffreeMessageBox]
Type=0
HeaderFile=BuffreeMessageBox.h
ImplementationFile=BuffreeMessageBox.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=CBuffreeMessageBox

[CLS:CUdpSocket]
Type=0
HeaderFile=UdpSocket.h
ImplementationFile=UdpSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[DLG:IDD_DLGSYSTEMSETTING_DIALOG]
Type=1
Class=CDlgSystemSetting
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SERVER_IPADDRESS,SysIPAddress32,1342242816
Control6=IDC_EDIT_SERVER_PORT,edit,1350631552

[CLS:CDlgSystemSetting]
Type=0
HeaderFile=DlgSystemSetting.h
ImplementationFile=DlgSystemSetting.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgSystemSetting

[DLG:IDD_DLGSERVERSETTING_DIALOG]
Type=1
Class=CDlgServerSetting
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_SERVER_PORT,edit,1350631552
Control6=IDC_SERVER_IPADDRESS,SysIPAddress32,1342242816

[CLS:CDlgServerSetting]
Type=0
HeaderFile=DlgServerSetting.h
ImplementationFile=DlgServerSetting.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgServerSetting

[DLG:IDD_DLGSUSPENSION_DIALOG]
Type=1
Class=CDlgSuspension
ControlCount=1
Control1=IDC_LOGO,static,1342177294

[CLS:CDlgSuspension]
Type=0
HeaderFile=DlgSuspension.h
ImplementationFile=DlgSuspension.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgSuspension

[MNU:IDR_MENU_SUSPENSION]
Type=1
Class=?
Command1=ID_SHOW
Command2=ID_EXIT
CommandCount=2

[DLG:IDD_DLGNEWSHARE_DIALOG]
Type=1
Class=CDlgNewShare
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BUTTON_SCAN,button,1342242816
Control6=IDC_EDIT_FILE_PATH,edit,1342242944
Control7=IDC_EDIT_FILENAME,edit,1342242944
Control8=IDC_EDIT_FILE_TAGS,edit,1342242944
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352

[CLS:CDlgNewShare]
Type=0
HeaderFile=DlgNewShare.h
ImplementationFile=DlgNewShare.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=CDlgNewShare

[DLG:IDD_DLGTHEMESELECTER_DIALOG]
Type=1
Class=CDlgThemeSelecter
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_THEME1,static,1342177294
Control4=IDC_STATIC_THEME2,static,1342177287

[CLS:CDlgThemeSelecter]
Type=0
HeaderFile=DlgThemeSelecter.h
ImplementationFile=DlgThemeSelecter.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATIC_THEME1

[CLS:CBuffreeEdit]
Type=0
HeaderFile=BuffreeEdit.h
ImplementationFile=BuffreeEdit.cpp
BaseClass=CEdit
Filter=W
LastObject=CBuffreeEdit

[CLS:CServiceSocket]
Type=0
HeaderFile=ServiceSocket.h
ImplementationFile=ServiceSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[CLS:CQuerySocket]
Type=0
HeaderFile=QuerySocket.h
ImplementationFile=QuerySocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CQuerySocket

