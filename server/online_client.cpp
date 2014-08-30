/*************************************************************************
	> File Name: online_client.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 20:43:55
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"

/* init a online_list */
struct online_list *create_online_list()
{
	struct online_list *onlinelist;
	onlinelist = new struct online_list;
	onlinelist->clientnum = 0;
	onlinelist->totalclient = 0;
	onlinelist->onlist = NULL;

	return onlinelist;
}

/* add a new client into online_list */
int add_to_online_list(struct online_list *clientlist, struct client_info *newclient)
{
	struct client *p, *nclient;

	if(!clientlist) {
		return -1;
	}

	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
		if(strcmp(p->mac,newclient->mac) == 0) {
			p->online = FLAG_ONLINE;
			strcpy(p->ip,newclient->ip);
			p->listenport = newclient->listenport;
			p->heartbeats = newclient->heartbeats;

			clientlist->clientnum +=1;			
			return 0;
		}
	}
	
	if(clientlist->clientnum >= MAX_CLIENT_ONLINE) {
		return -1;
	}

	nclient = new struct client;
	nclient->online = FLAG_ONLINE;
	strcpy(nclient->mac,newclient->mac);
	strcpy(nclient->ip,newclient->ip);
	nclient->listenport = newclient->listenport;
	nclient->heartbeats = MAX_HEARTBEAT_NUM;
	nclient->next = NULL;

	p->next = nclient;
	clientlist->clientnum +=1;
	clientlist->totalclient += 1;

	return 0;
}

/* delete a client from online_list */
int del_from_online_list(struct online_list *clientlist, char *mac)
{
	if(!clientlist) {
		return -1;
	}

	struct client *p;
	p = clientlist->onlist;

	while(p->next) {
		p = p->next;
		if(strcpy(mac,p->mac) == 0) {
			p->online = FLAG_OFFLINE;
			clientlist->clientnum -= 1;

			break;
		}
	}

	return 0;
}

/* test mac of client is online */
int is_online(struct online_list *clientlist, char *mac)
{
	if(!clientlist) {
		return -1;
	}

	struct client *p;
	p = clientlist->onlist;
	while(p->next) {
		if((strcmp(mac,p->mac) == 0) 
			&& p->online == FLAG_ONLINE) {
			return 0; /* ret 0 when online */
		}
	}

	return -1; /* ret -1 when offline or not found */
}

