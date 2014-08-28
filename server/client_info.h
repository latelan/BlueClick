/*************************************************************************
	> File Name: client_info.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 13:17:13
 ************************************************************************/

#ifndef client_info__h
#define client_info__h

int has_client(const char *mac);
int add_client(struct client_info *newclient);
void print_client_list();

#endif
