/*************************************************************************
	> File Name: msghandler.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-31 21:11:41
 ************************************************************************/

#ifndef msghandler__h
#define msghandler__h

/* debug */
void debug(const char *err_string, int line);

/* udp message handler */
int msg_udp_handler(int sockfd, struct online_list *clientlist);

/* tcp message handler */
int msg_tcp_handler(int sockfd, struct online_list *clientlist);

/* alarm signal handler */
void signalarm_handler(int signo);

#endif
