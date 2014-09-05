/*************************************************************************
	> File Name: common.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 09:45:07
 ************************************************************************/

#ifndef common__h
#define common__h

#define MSG_QUERY_RES		"MsgQueryRes"
#define MSG_GET_PUSH  		"MsgGetPush"
#define MSG_DOWNLOAD_RES 	"MsgDownloadRes"
#define MSG_HEARTBEAT		"MsgHeartbeat"
#define MSG_ONLINE			"MsgOnline"
#define MSG_SHARE_RES		"MsgShareRes"
#define MSG_QUIT			"MsgQuit"

#define TAG_SEPERATOR		"#"

#define MAX_CLIENT_ONLINE 200
#define MAX_HEARTBEAT_NUM 3
#define FLAG_ONLINE 1
#define FLAG_OFFLINE 0

/* online clients info */
struct client_info {
	char mac[32];
	char ip[32];
	int listenport;
	int heartbeats;
};

/* response client online request */
struct server_info {
	char ip[32];
	char reserved[32];
};

/* client search resource */
struct queryres {
	char key[256];
};

/* client download resource */
struct downloadres {
	char md5[33];
};

/* resource type */
struct resource_type {
	char name[256];
	char size[64];
	char md5[33];
	int piececount;
};

/* share resource type */
struct resource_share {
	char name[256];
	char tag[512];
	char size[64];
	char md5[33];
	char mac[32];
	int piececount;
};

/* online client node */
struct client {
	int online;
	char mac[32];
	char ip[32];
	int listenport;
	int heartbeats;
	struct client *next;
};

/* online list */
struct online_list {
	int clientnum;
	int totalclient;
	struct client *onlist;
};

/* download request msg */
struct download_req {
	char clientip[32];
	char md5[33];
	int numwant;
	char event[32];
};

/* peer info */
struct peer_info {
	char ip[32];
	int port;
	int availablepieces;
	int availableconnections;
};

/* res download list node */
struct res_download_node {
	char md5[33];
	int requestnum;
	int completednum;
	struct download_info *dlist;
};

/* download client info */
struct peer_download_info {
	char clientip[32];
	int uploaded;
	int downloaded;
	int left;
	int availableconnections;
	char event[32];
};

#endif
