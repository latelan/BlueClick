/*************************************************************************
	> File Name: msghandler.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-31 18:54:14
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "common.h"
#include "cJSON.h"
#include "online_client.h"
#include "message.h"
#include "dbconnect.h"
#include "online_client.h"

#define TCP_BUFFER_SIZE 2048
#define UDP_BUFFER_SIZE 2048
#define SPAN_CHECKOUT 10
#define VARIFY_STRING "null"

extern const char *server_ip;
extern const char *server_port;
extern struct online_list *clist;

void debug(const char *err_string, int line) 
{
	fprintf(stderr,"line: %d ",line);
	perror(err_string);
	exit(1);
}

int msg_udp_handler(int sockfd,struct online_list *clientlist)
{
	char buf[ UDP_BUFFER_SIZE ];
	char server_buf[1024];
	char msgtype[32];
	struct sockaddr_in client_address;
	int ret;

	memset(buf, '\0',UDP_BUFFER_SIZE);
	socklen_t client_addrlength = sizeof(client_address);

	ret = recvfrom(sockfd,buf,UDP_BUFFER_SIZE-1,0,(struct sockaddr*)&client_address, &client_addrlength);
	if(ret <= 0) {
		return -1;
	}

	printf("udp buf: %s\n",buf);
	cJSON *msg = cJSON_Parse(buf);
	if(!msg) {
		return -1;
	}

	memset(msgtype,'\0',strlen(msgtype));
	strcpy(msgtype,cJSON_GetObjectItem(msg,"MsgType")->valuestring);
	if(strcmp(MSG_ONLINE,msgtype) == 0) { /* msg online */
		struct client_info client;
		json_to_msg_client_info(buf,&client);

		add_to_online_list(clist,&client); /* add into online client list */

		struct server_info server;
		strcpy(server.ip,server_ip);
		strcpy(server.reserved,"nulled");
		server_info_to_json(server_buf,&server);
		
		printf("send buf: %s\n",server_buf);
		sendto(sockfd,server_buf,strlen(server_buf)+1,0,(struct sockaddr*)&client_address,client_addrlength);

		return 0;
	}
	else if(strcmp(MSG_HEARTBEAT,msgtype) == 0) { /* msg heartbeat */
		char *clientmac;
		clientmac = cJSON_GetObjectItem(msg,"ClientMAC")->valuestring;
		heartbeat(clist,clientmac); /* heartbeat test */
		
		return 0;
	}

	return -1;
}


int msg_tcp_handler(int sockfd,struct online_list *clientlist)
{
	int ret;
	char buf[ TCP_BUFFER_SIZE ];
	memset( buf, '\0', TCP_BUFFER_SIZE );
	ret = recv( sockfd, buf, TCP_BUFFER_SIZE, 0 );

	if( ret < 0 ) {
		if( ( errno != EAGAIN ) && ( errno != EWOULDBLOCK ) ) {
			close( sockfd );
			return -1;
		}
	}
	else if( ret == 0 )	{
		close( sockfd );
		return -1;
	}
	
	cJSON *msg = cJSON_Parse(buf);
	char *out = cJSON_Print(msg);
	printf("recv buf: %s\n",out);
	free(out);

	if(!msg) {
		return -1;
		/* debug("parse json",__LINE__); */
	}

	char msgtype[64] = "";
	strcpy(msgtype,cJSON_GetObjectItem(msg,"MsgType")->valuestring);

	if(strcmp(MSG_QUERY_RES,msgtype) == 0) { 	/* search resource */
		printf("MsgType: MSG_QUERY_RES\n");
		struct queryres query;
		
		cJSON *child = NULL;
		child = cJSON_GetObjectItem(msg,"QueryKey");
		if(child == NULL) { /* not found child */
			return 0;
		}
		
		int l = strlen(cJSON_GetObjectItem(msg,"QueryKey")->valuestring);
		if(strlen(cJSON_GetObjectItem(msg,"QueryKey")->valuestring) <= 1) { /* key is shorter */
			cJSON_Delete(msg);
			return 0;
		}
		strcpy(query.key, cJSON_GetObjectItem(msg,"QueryKey")->valuestring);
		
		printf("QueryKey: %s\n",query.key);

		// query database 
		struct resource_type res[10];
		int len = 10;
		char *text = NULL;
		get_res_list(query,res,&len);
		text = res_list_to_json(text,res,len);
		
		// response query msg
		printf("send: %s\n",text);
		send(sockfd,text,strlen(text)+1, 0);

		free(text);
	}
	else if (strcmp(MSG_GET_PUSH,msgtype) == 0) { /* get push */
		printf("MsgType: MSG_GET_PUSH\n");
		/* get want number */
		int numwanted = cJSON_GetObjectItem(msg,"NumWanted")->valueint;

		/* default push method */
		struct queryres query = {"she"};
		struct resource_type res[10];
		int len;
		char *text = NULL;
	
		len = 10;
		if(numwanted < 10 || numwanted > 0) {
			len = numwanted;
		}

		get_res_list(query,res,&len);
		text = res_list_to_json(text,res,len);

		// response query msg
		printf("send: %s\n",text);
		send(sockfd,text,strlen(text)+1, 0);
		
		free(text);
	}
	else if (strcmp(MSG_SHARE_RES,msgtype) == 0) { /* share resource */
		printf("MsgType: MSG_SHARE_RES\n");
		
		struct resource_share share_res;
		
		cJSON *child = cJSON_GetObjectItem(msg,"Resource");
		strcpy(share_res.name,cJSON_GetObjectItem(child,"ResName")->valuestring);
		strcpy(share_res.tag,cJSON_GetObjectItem(child,"ResTag")->valuestring);
		strcpy(share_res.size,cJSON_GetObjectItem(child,"ResSize")->valuestring);
		strcpy(share_res.md5,cJSON_GetObjectItem(child,"ResMD5")->valuestring);
		strcpy(share_res.mac,cJSON_GetObjectItem(child,"ResOwner")->valuestring);
		share_res.piececount = cJSON_GetObjectItem(child,"ResPieceCount")->valueint;
		
		/* add share resource into db */
		add_share_resource(&share_res);
			
		printf("Resource: Name:%s, Tag:%s, Size:%s, MD5:%s, Owner:%s, PieceCount:%d\n",
				share_res.name,share_res.tag,share_res.size,share_res.md5,
				share_res.mac,share_res.piececount);

		printf("run to here\n");		

	}
	else if (strcmp(MSG_DOWNLOAD_RES,msgtype) == 0) { /* download resource */
		printf("MsgType: MSG_DOWNLOAD_RES\n");
		struct peer_info peers[5];
		int len = 1;
		strcpy(peers[0].ip,"192.168.0.2");
		peers[0].port = 6666;
		peers[0].downloaded = 1000;

		strcpy(peers[1].ip,"192.168.0.35");
		peers[1].port = 1235;
		peers[1].downloaded = 1001;

		char *text = NULL;
		text = peer_info_to_json(peers,len);

//		cJSON *msg = cJSON_Parse(msgbuf);
		printf("Downloaded: %s\n",text);

		send(sockfd,text,strlen(text)+1, 0);
	}

	free(msg);
}

/* alarm signal handler */
void signalarm_handler(int signo) 
{
	online_checkout_handler();

	alarm(SPAN_CHECKOUT);
}
