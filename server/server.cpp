#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include "common.h"
#include "tools.h"
#include "message.h"

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE 512
#define UDP_BUFFER_SIZE 1024
#define MAX_CLIENT_NUMBER 200

int *workthread(void *);

void debug(const char *err_string, int line)
{
	fprintf(stderr,"line: %d ",line);
	perror(err_string);
	exit(1);
}

int setnonblocking( int fd )
{
	int old_option = fcntl( fd, F_GETFL );
	int new_option = old_option | O_NONBLOCK;
	fcntl( fd, F_SETFL, new_option );
	return old_option;
}

void addfd( int epollfd, int fd )
{
	epoll_event event;
	event.data.fd = fd;
	//event.events = EPOLLIN | EPOLLET;
	event.events = EPOLLIN;
	epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
	setnonblocking( fd );
}

int main( int argc, char* argv[] )
{
	if( argc <= 2 )
	{
		printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
		return 1;
	}
	const char* ip = argv[1];
	int port = atoi( argv[2] );

	int ret = 0;
	struct sockaddr_in address;
	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );

	int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
	assert( listenfd >= 0 );

	ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
	assert( ret != -1 );

	ret = listen( listenfd, 5 );
	assert( ret != -1 );

	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );
	int udpfd = socket( PF_INET, SOCK_DGRAM, 0 );
	assert( udpfd >= 0 );

	ret = bind( udpfd, ( struct sockaddr* )&address, sizeof( address ) );
	assert( ret != -1 );

	epoll_event events[ MAX_EVENT_NUMBER ];
	int epollfd = epoll_create( 5 );
	assert( epollfd != -1 );
	addfd( epollfd, listenfd );
	addfd( epollfd, udpfd );

	while( 1 )
	{
		int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
		if ( number < 0 )
		{
			printf( "epoll failure\n" );
			break;
		}

		for ( int i = 0; i < number; i++ )
		{
			int sockfd = events[i].data.fd;
			if ( sockfd == listenfd )
			{/* new tcp connect */
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof( client_address );
				int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
				addfd( epollfd, connfd );
			}
			else if ( sockfd == udpfd )
			{
				char buf[ UDP_BUFFER_SIZE ];
				memset( buf, '\0', UDP_BUFFER_SIZE );
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof( client_address );

				ret = recvfrom( udpfd, buf, UDP_BUFFER_SIZE-1, 0, ( struct sockaddr* )&client_address, &client_addrlength );
				if( ret > 0 )
				{ // 客户端上线消息
					// 客户端心跳请求消息

					struct server_info server;
					strcpy(server.ip,"192.168.0.29");
					strcpy(server.reserved,"null");
					char buff[1024];

					server_info_to_json(buff,&server);
					printf("%s\n",buff);
					sendto( udpfd, buff, strlen(buff)+1, 0, ( struct sockaddr* )&client_address, client_addrlength );
					//				  printf("recv: %s\n",buf);
					struct client_info client;
					json_to_msg_client_info(buf, &client);
					printf("%s %s %d\n",client.ip,client.mac, client.listenport);

					// user online msg

				}
			}
			else if ( events[i].events & EPOLLIN )
			{
				// 接受客户端搜索消息
				// 接受下载请求消息
				// 接受客户端下载状态上报消息

				// 开新线程
				//pthread_t thid;

				//if(pthread_create(&thid, NULL, (void*)workthread,sockfd) != 0) {
				//	perror("pthread_create");
				//	exit(1);
				//}

			}
			else
			{
				printf( "something else happened \n" );
			}
		}
	}

	close( listenfd );
	return 0;
}

//int *workthread(void *arg)
//{
//	int ret;
//	char buf[ TCP_BUFFER_SIZE ];
//	memset( buf, '\0', TCP_BUFFER_SIZE );
//	ret = recv( sockfd, buf, TCP_BUFFER_SIZE-1, 0 );
//
//	if( ret < 0 ) {
//		if( ( errno != EAGAIN ) && ( errno != EWOULDBLOCK ) )
//			close( sockfd );
//	}
//	else if( ret == 0 )	{
//		close( sockfd );
//	}
//	
//	cJSON *msg = cJSON_Parse(buf);
//	if(!msg) {
//		debug("parse json",__LINE__);
//	}
//
//	char msgtype[64];
//	strcpy(msgtype,cJSON_GetObjectItem(msg,"MsgType")->valuestring);
//	if(strcmp(MSG_QUERY_RES,msgtype)){
//		// search resource
//		char key[256];
//		strcpy(key,cJSON_GetObjectItem(msg,"QueryKey")->valuestring);
//		// query database 
//		
//		// response query msg
//	}
//	else if (strcmp(MSG_GET_PUSH,msgtype)) {
//		// get push
//
//	}
//	else if (strcmp(MSG_DOWNLOAD_RES,msgtype)) {
//		// download resource
//		
//	}
//}
