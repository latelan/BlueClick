BlueClick
=========

蓝点局域网文件共享平台。

==========================
### 项目简介

  本项目由[Jensyn](https://github.com/Jensyn)、[latelan](https://github.com/latelan)、LiQian、GaoJingYi四人组成的Buffree团队于2014暑期为期20天的软酷实习期间完成。

  项目采用B/S架构设计，由Linux服务端、Windows客户端以及Android客户端组成。用户可通过客户端将文件的相关信息（文件大小、文件路径、完整性校验码等等）上传至服务器，而其他用户通过服务器查询获取文件的相关信息，与共享文件的客户端来建立连接，进行文件传输。在整个工作流程中，大部分的数据都是通过客户端-客户端（类P2P）来实现传输的，服务端只负责资源信息的查询以及客户端资源的调度，并不存储文件的真实数据。
    
  项目涉及的技术有：
  
  > Linux环境下的Socket I/O复用epoll技术、Android环境下的的TCP/IP数据传输技术，以及Windows环境下的MFC、界面自绘技术。
    
### 开发环境
  
  Linux服务端：
  
  > Ubuntu 14.04 / Gcc 4.4.7  / make 3.81
  
  Windows客户端：
  
  > Windows XP SP3 / VC6.0

  Android客户端：
  
  > Android 4.4 / Eclipse / ADT bundle for windows
  
### 编译及安装

  1.设备及环境
  
  > 为了编译安装本系统，您可能需要一台搭载Linux系统的服务器，至少一台搭载Windows（XP）的用来测试的机器，以及至少一部搭载Android系统的手机。
  
  > 有了基本的硬件设备以后，您可能还需要配置相关的软件环境来编译项目源码，例如在Linux服务器上，需要安装GCC编译器来编译系统服务端源码、Mysql数据库来存取系统交换的数据；Windows机器上需要安装VC6.0来编译Windows客户端源码，以及ADT、Eclipse来编译Android客户端源码。

  2.源码下载[下载](https://github.com/Jensyn/BlueClick/archive/master.zip)
  
  > 有了基本的设备环境后，从[这里](https://github.com/Jensyn/BlueClick/archive/master.zip)获取本项目的源码包，然后将服务端源码（ server/ ）上传至Linux服务器上，将Windows客户端源码（ client-pc ）以及Android客户端源码（client-Android）移至Windows机器上。

  3.编译及安装
  
  Linux服务端：
  
  > 编译：登录linux服务器，进入服务端源码所在路径（如'/home/xxx/BlueClick/server/'），使用make命令进行编译。相关命令如下：
  >> cd /home/xxx/BlueClick/server/ && make

  > 安装：无需安装。

  Windows客户端：
  
  > 编译：使用VC6.0打开Windows客户端源码，设置编译选项（Release），点击全部编译即可。
    
  > 安装：无需安装。
    
  Android客户端：
    
  > 编译：使用Eclipse打开Android客户端源码，编译无错后打包。
    
  > 安装：使用相关工具安装。

  4.项目配置
  
  Linux服务端：
      
  > 使用项目附带的sql脚本（server/docs/data.sql），导入项目Mysql数据库。
    
  Windows客户端：
    
  > 配置客户端所在路径下的config.ini文件中的服务端IP、端口,以及客户端资源服务模块监听的端口。
      
  Android客户端：
    
  > 暂无。
      
  5.运行项目
      
  Linux服务端：
    
  > 使用命令行执行编译后的server文件，命令参数如下
  >> ./server 127.0.0.1 5555
    
  > 如输出提示：
  >> server is running at 127.0.0.1:5555
  
  > 则说明运行正常。
    
  Windows客户端：
  
  > 将编译后的release/BlueClick.exe拷贝到client-pc目录下，双击运行，如果在短暂的连接提示后进入主界面则说明服务端及客户端配置正确；否则请检查服务器与客户端可否连通以及配置是否正确。
    
  Android客户端：
  
  > 略。
    
  6.Windows客户端使用说明

  > 启动客户端之前需启动服务端， 保证服务端正常工作，并且客户端机器可以Ping通服务端机器。

  > 客户端启动之后会进入欢迎页面，此阶段会检查本地配置文件：如果存在配置文件，则尝试连接配置文件中自定的服务器；如果配置文件不存在或者尝试连接失败，则创建默认配置文件，并在局域网内自动发现服务器，成功发现服务器则将服务器地址写入配置文件，然后连接服务端并进入主窗口，未发现服务器则退出；由于局域网环境的配置不同，不能保证发现服务器的功能在所有的环境下都可用，因此，启动客户端之前最好配置好服务器的IP以及端口信息。

  > 进入主窗口后，客户端会主动请求服务端返回推荐资源列表，并显示。注：首次安装后服务器没有资源信息，因此客户端不会显示推荐资源列表。
    
  > 通过上传模块选择本地文件将资源信息上传至服务器。
    
  > 通过搜索框搜索服务器资源。选择相关资源开始下载。下载后的文件默认放置在客户端程序所在路径下的Download子目录下。

### 技术实现
  
  1.数据传输格式：
  
  > 由于本系统采用Windows 、Linux、Android跨平台开发，因此在开发中难免会遇到一些数据类型以及编码上的差异。所以在开发的过程中各端之间的数据传输全部使用JSON格式。

  > 如：客户端启动后向服务端发送的上线请求消息格式如下：
  
    {
    
      "MsgType" : "MsgOnLine",
      
  	  "ClientIP": "192.168.1.23",
  	  
  	  "ClientMAC": "C8-9C-DC-61-03-9F",
  	  
  	  "ClientListenPort": 3443
  
    }

  2.资源上传下载
  
  > 考虑到减缓服务器负载、充分利用客户端资源，本系统在文件上传的过程中只向服务器发送文件的相关信息以及MD5校验和。客户端向服务端发送的资源上传消息格式如下：
  
    {
    
  	  "MsgType" : "MsgShareRes",
  	  
  	  "Resource" :
  	  
  	  {
  	  
  	  	"ResName" : "后会无期.rmvb",
  	  	
  	  	"ResTag" : "韩寒,平凡之路",
  	  	
  	  	"ResSize" : "956MB",
  	  	
  	  	"ResMD5" : "1C7D74B459AB47C0403BD27A2DEC77E2",
  	  	
  	  	"ResOwner" : "C8-9C-DC-61-03-9F",
  	  	
  	  	"ResPieceCount" : 3456
  	  	
  	  }	
  	  
    }

  > 在上传文件的同时，客户端会将上传的资源信息保存在本地的配置文件resource.list中，以二进制写入。本地保存的资源信息结构体格式如下：
  
    struct res_struct {
    
      "Name" : "资源名称",
    
      "Size" : "资源大小",
    
      "MD5" : "资源MD5校验码",
    
      "Path" : "资源所在路径"
  
    };

