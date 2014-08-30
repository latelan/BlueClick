/*************************************************************************
	> File Name: common.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 09:45:07
 ************************************************************************/

#ifndef common__h
#define common__h

#define MSG_QUERY_RES "MsgQueryRes"
#define MSG_GET_PUSH  "MsgGetPush"
#define MSG_DOWNLOAD_RES "MsgDownloadRes"
#define MSG_HEARTBEAT	"MsgHeartbeat"

// online clients info
struct client_info {
	char mac[32];
	char ip[32];
	int listenport;
	int heartbeats;
};

// response client online request
struct server_info {
	char ip[32];
	char reserved[32];
};

// client search resource
struct queryres {
	char key[256];
};

// client download resource
struct downloadres {
	char md5[33];
};

// resource type
struct resource_type {
	char name[256];
	char size[64];
	char md5[33];
	int piececount;
};


#endif
