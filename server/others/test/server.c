/*************************************************************************
  > File Name: server.c
  > Author: latelan, coolboy1353@163.com
  > Created Time: 2014-08-22 14:10:37
 ************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "my_recv.h"

#define SERV_PORT	7788
#define LISTENQ		12

#define INVALID_USERINFO	'n'
#define VALID_USERINFO		'y'

#define USERNAME	0
#define PASSWORD	1

struct userinfo{
	char username[32];
	char password[32];
};
struct userinfo users[] = {
	{"linux","linux"},
	{"zyj","zyj"},
	{"tmp","tmp"},
	{"xiaoming","mingming"},
	{"guangtouqiang","qiang"}
};
int find_name(const char *name)
{

}
void send_data(int conn_fd, const char *string)
{

}
int main()
{
	int	sock_fd, conn_fd;
	int optval;
	int flag_recv = USERNAME;
	int ret;
	int name_num;
	pid_t pid;
	socklen_t cli_len;
	struct sockaddr_in cli_addr, serv_addr;
	char recv_buf[128];

	// 创建一个TCP套接字
	sock_fd = socket(AF_INET, SOCK_STREAM,0);
	if(sock_fd < 0) {
		my_err("socket",__LINE__);
	}

	// 设置该套接字使之可以重新绑定端口
	optval = 1;
	if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,
				(void *)&optval, sizeof(int)) < 0) {
		my_err("setsockopt",__LINE__);
	}

	// 初始化服务端地址结构
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 将套接字绑定到本地端口
	if(bind(sock_fd, (struct sockaddr *)&serv_addr, 
				sizeof(struct sockaddr_in)) < 0) {
		my_err("bind",__LINE__);
	}

	// 将套接字转化为监听套接字
	if(listen(sock_fd, LISTENQ) < 0) {
		my_err("listen",__LINE__);
	}

	cli_len = sizeof(struct sockaddr_in);
	while(1) {
		conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &cli_len);
		if(conn_fd < 0) {
			my_err("accept",__LINE__);
		}

		printf("accept a new client, ip:%s\n",inet_ntoa(cli_addr.sin_addr));
		if((pid = fork()) == 0) {
			while(1) {
				if((ret = recv(conn_fd, recv_buf,sizeof(recv_buf),0)) < 0) {
					perror("recv");
					exit(1);
				}
				recv_buf[ret-1] = '\0';

				if(flag_recv == USERNAME) {
					name_num = find_name(recv_buf);
					switch(name_num) {
						case -1:
							send_data(conn_fd,"n\n");
							break;
						case -2:
							exit(1);
							break;
						default:
							send_data(conn_fd,"y\n");
							flag_recv = PASSWORD;
							break;
					}
				}else if(flag_recv == PASSWORD) {
					if(strcmp(users[name_num].password,recv_buf) == 0) {
						send_data(conn_fd,"y\n");
						send_data(conn_fd,"Welcome login my tcp server\n");
						printf("%s login\n",users[name_num].username);
						break;
					}else {
						send_data(conn_fd,"n\n");
					}
				}
				close(sock_fd);
				close(conn_fd);
				exit(0);
			}
		} else {
			close(conn_fd);
		}
	}
	return 0;
}
