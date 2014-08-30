/*************************************************************************
	> File Name: my_recv.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-22 15:06:04
 ************************************************************************/

#ifndef __MY_RECV_H
#define __MY_RECV_H

#define BUFSIZE 1024
void my_err(const char *err_string, int line);
int my_recv(int conn_fd, char *data_buf, int len);

#endif
