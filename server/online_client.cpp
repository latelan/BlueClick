/*************************************************************************
	> File Name: online_client.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 20:43:55
 ************************************************************************/

#include <stdio.h>
#include "common.h"

/* init a online_list */
struct online_list *create_online_list()
{
	struct online_list *onlinelist;
	onlinelist = new struct online_list;
	online_list->clientnum = 0;
	online_list->onlist = NULL;

	return onlinelist;
}

/* add a new client into online_list */
int add_to_online_list(struct online_list *clientlist, struct client *newclient)
{
	if(clientlist == NULL) {
		return -1;
	}

	struct online_list *p;
	struct client *nclient;

	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
	}

	nclient = new struct client;
	strcpy(nclient->mac,newclient->mac);
	strcpy(nclient->ip,newclient->ip);
	nclient->listenport = newclient->listenport;
	nclient->heartbeats = MAX_HEARTBEAT_NUM;
	nclient->next = NULL;

	p->next = nclient;
	
	return 0;
}
/* delete a client from online_list */
int del_from_online_list(struct online_list *clientlist, char *ip)
{
	if(clientlist == NULL) {
		return -1;
	}

	struct client *pre,*p;
	pre = client->onlist;
	p = pre->next;

	while(p->next) {
		if(strcpy(ip,p->ip) == 0) {
			p->online = 0;
		}
		pre = p;
		p = p->next;
	}


}
