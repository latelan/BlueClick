/*************************************************************************
	> File Name: test.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 10:20:46
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "client_info.h"

extern struct client_info client_list;
extern int clientnum;

int main()
{
	struct client_info client;
	strcpy(client.mac, "mac");
	strcpy(client.ip, "ip");
	client.listenport = 33443;

	add_client(&client);
	
	print_client_list();
}
