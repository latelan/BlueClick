Server
======
在开发过程中，此处放Server端代码。

目录结构  
include/ - 存放头文件  
  cJSON.h  
  client_info.h  
  common.h  常用数据结构  
  dbconnect.h  
  loadbalance.h  
  message.h  
  msghandler.h  
  online_client.h  
  tools.h  

src/ - 源文件  
  cJSON.cpp  json数据解析  
  client_info.cpp  客户端信息管理   
  dbconnect.cpp  数据库相关操作  
  download_queue.cpp  下载队列  
  loadbalance.cpp  负载均衡算法  
  message.cpp  通信消息封装和解析  
  msghandler.cpp  消息处理  
  online_client.cpp 在线客户端维护  
  server.cpp  服务端入口  
  tools.cpp 工具  
