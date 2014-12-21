#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "online_client.h"
#include "msghandler.h"
#include "datetime.h"

#define MAX_EVENT_NUMBER 1024
#define MAX_CLIENT_NUMBER 200

const char *server_ip = NULL; /* server ip */
const char *server_port = NULL; /*server port */

struct online_list *clist;	/* online client list */
static bool stop = false;

void handler_sigint(int signo)
{
	printf("server is stopping...\n");
	stop = true;
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

void logmaker(const char *string)
{
	FILE *fp;
	time_t now;
	struct tm *nowtime;
	char strtime[20];
	char *path = NULL;
	char log[1024];

	now = time(NULL);
	nowtime = localtime(&now);
	sprintf(strtime,"%04d-%02d-%02d.log",nowtime->tm_year+1900,nowtime->tm_mon+1,nowtime->tm_mday);
	path = (char *)malloc(sizeof(char)*(strlen(LOG_PATH)+strlen(strtime)+1));
	sprintf(path,"%s%s",LOG_PATH,strtime);

	fp = fopen(path,"a+");
	if(!fp)
	{
		printf("Error: cannot open the log file.\n");
		return;
	}

	fprintf(fp,"%s %s\n",get_curr_time(),string);

	fclose(fp);

	return;
}

int main( int argc, char* argv[] )
{
	if( argc <= 2 )
	{
		printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
		return 1;
	}

	printf("Server is starting...\n");

	const char* ip = argv[1];
	int port = atoi( argv[2] );

	server_ip = argv[1];
	server_port = argv[2];
	clist = create_online_list();

	int ret = 0;

	/* set tcp socket */
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

	/* set udp socket */
	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );
	int udpfd = socket( PF_INET, SOCK_DGRAM, 0 );
	assert( udpfd >= 0 );

	ret = bind( udpfd, ( struct sockaddr* )&address, sizeof( address ) );
	assert( ret != -1 );

	/* add epoll event */
	epoll_event events[ MAX_EVENT_NUMBER ];
	int epollfd = epoll_create( 5 );
	assert( epollfd != -1 );
	addfd( epollfd, listenfd );
	addfd( epollfd, udpfd );

	/* set signal alarm */
	signal(SIGINT,handler_sigint);
//	raise(SIGALRM);
	
	logmaker("Server is running...");
	while( !stop) 	{
		int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
		if ( number < 0 ) {
			perror("epoll_wait");
			break;
		}

		for ( int i = 0; i < number; i++ ) {
			int sockfd = events[i].data.fd;
			if ( sockfd == listenfd ) {/* new tcp connect */
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof( client_address );
				int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
				addfd( epollfd, connfd );
			}
			else if ( sockfd == udpfd ) {/* udp */
				msg_udp_handler(udpfd,clist);
				print_clist(clist);

			}
			else if ( events[i].events & EPOLLIN ) {/* tcp */
				msg_tcp_handler(sockfd,clist);
			} 
			else {
				printf( "something else happened \n" );
			}
		}
	}

	close( listenfd );
	return 0;
}
