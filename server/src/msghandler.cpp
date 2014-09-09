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
#include "loadbalance.h"

#define TCP_BUFFER_SIZE 1500
#define UDP_BUFFER_SIZE 1500
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

	/* debug */
//	printf("udp buf: %s\n",buf);
	cJSON *msg = cJSON_Parse(buf);
	if(!msg) {
		return -1;
	}

	memset(msgtype,'\0',strlen(msgtype));
	strcpy(msgtype,cJSON_GetObjectItem(msg,"MsgType")->valuestring);
	if(strcmp(MSG_ONLINE,msgtype) == 0) { /* msg online */
		struct client_info client;
		json_to_msg_client_info(buf,&client); /* convert buf to json */

		add_to_online_list(clist,&client); /* add into online client list */

		struct server_info server;
		strcpy(server.ip,server_ip);
		strcpy(server.reserved,"nulled");

		server_info_to_json(server_buf,&server); /* convert server info to json */

      	/* debug */
//		printf("send buf: %s\n",server_buf);
		sendto(sockfd,server_buf,strlen(server_buf)+1,0,(struct sockaddr*)&client_address,client_addrlength);
		
		cJSON_Delete(msg);
		return 0;
	}
	else if(strcmp(MSG_HEARTBEAT,msgtype) == 0) { /* msg heartbeat */
		char *clientmac;
		clientmac = cJSON_GetObjectItem(msg,"ClientMAC")->valuestring;
		heartbeat(clist,clientmac); /* heartbeat test */
		
		free(clientmac);
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
	
	/* debug */
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
		
		cJSON *child = NULL;
		child = cJSON_GetObjectItem(msg,"QueryKey");
		if(child == NULL) { /* not found child */
			cJSON_Delete(msg);
			return 0;
		}
		
		if(strlen(cJSON_GetObjectItem(msg,"QueryKey")->valuestring) <= 1) { /* key is shorter */
			cJSON_Delete(msg);
			return 0;
		}
		struct queryres query;
		strcpy(query.key, cJSON_GetObjectItem(msg,"QueryKey")->valuestring);
		
		/* debug */
		//printf("QueryKey: %s\n",query.key);

		/* query database */
		struct resource_type res[10];
		int len = 10;
		char *text = NULL;
		get_res_list(query,res,&len);
		text = res_list_to_json(res,len);
		
		/* debug */
		printf("send: %s\n",text);
		
		/* response query msg */
		send(sockfd,text,strlen(text)+1, 0);

		free(text);
	}
	else if (strcmp(MSG_GET_PUSH,msgtype) == 0) { /* get push */
		/* debug */
		//printf("MsgType: MSG_GET_PUSH\n");
		
		/* get want number */
		int numwanted = cJSON_GetObjectItem(msg,"NumWanted")->valueint;

		/* default push method */
		struct resource_type share_res[10];
		int len = numwanted;
		
		get_push_list(share_res,&len); /* get push list */

		char *text = NULL;
		text = res_list_to_json(share_res,len); /* convert res list to json */

		/* debug */
		//printf("send: %s\n",text);

		/* response query msg */
		send(sockfd,text,strlen(text)+1, 0);
		
		free(text);
	}
	else if (strcmp(MSG_SHARE_RES,msgtype) == 0) { /* share resource */
		printf("MsgType: MSG_SHARE_RES\n");
		
		struct resource_share share_res;
		json_to_resource_share(buf,&share_res); /* convert json to resource share */

		
		add_share_resource(&share_res); /* add share resource into db */  
		
		/* debug */
		//printf("Resource: Name:%s, Tag:%s, Size:%s, MD5:%s, Owner:%s, PieceCount:%d\n",
		//		share_res.name,share_res.tag,share_res.size,share_res.md5,
		//		share_res.mac,share_res.piececount);
	}
	else if (strcmp(MSG_DOWNLOAD_RES,msgtype) == 0) { /* download resource */
		/* debug */
		//printf("MsgType: MSG_DOWNLOAD_RES\n");

		struct download_req msgreq;
		struct peer_info peers[20];
		int len = 1;

		json_to_download_req(buf,&msgreq); /*convert json to download_req */
	
		/* debug */
		//printf("download_req: ip:%s, md5:%s, numwant:%d, event:%s\n",msgreq.clientip,msgreq.md5,msgreq.numwant,msgreq.event);

	
		loadbalance_on_server(clist,&msgreq,peers,&len); /* algorithm loadbalance on server */		
		char *text = NULL;
		text = peer_info_to_json(peers,len); /* convert peer_info to json */

		/* debug */
		printf("Downloaded: %s\n",text);

		send(sockfd,text,strlen(text)+1, 0);
	}
	else if(strcmp(MSG_QUIT,msgtype) == 0) { /* quit */
		printf("MsgType: MSG_QUIT\n");
		char *clientip;
		clientip = cJSON_GetObjectItem(msg,"ClientIP")->valuestring;
		printf("quit ip: %s\n",clientip);
		del_from_online_list(clist,clientip);

		print_clist(clist);		
	}
	free(msg);

	return 0;
}

/* alarm signal handler */
void signalarm_handler(int signo) 
{
	online_checkout_handler();

	alarm(SPAN_CHECKOUT);
}
