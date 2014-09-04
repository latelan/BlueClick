/*************************************************************************
	> File Name: online_client.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 20:43:55
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"

extern struct online_list *clist;

/* init a online_list */
struct online_list *create_online_list()
{
	struct online_list *onlinelist;
	struct client *headnode;

	headnode = new struct client;
	headnode->next = NULL;

	onlinelist = new struct online_list;
	onlinelist->clientnum = 0;
	onlinelist->totalclient = 0;
	onlinelist->onlist = headnode;

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
			p->heartbeats = MAX_HEARTBEAT_NUM;

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
		if(strcmp(mac,p->mac) == 0) {
			p->online = FLAG_OFFLINE;

			break;
		}
	}

	return 0;
}

/* test mac of client is online */
int is_in_online_list(struct online_list *clientlist, char *mac)
{
	if(!clientlist) {
		return -1;
	}

	struct client *p;
	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
		if((strcmp(mac,p->mac) == 0) 
			&& p->online == FLAG_ONLINE) {
			return 0; /* ret 0 when online */
		}
	}

	return -1; /* ret -1 when offline or not found */
}

/* set online flag */
int set_online(struct online_list *clientlist, char *mac) 
{
	if(!clientlist) {
		return -1;
	}

	struct client *p;
	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
		if(strcmp(mac,p->mac) == 0) {
			p->online = FLAG_ONLINE;
			break;
		}
	}

	return 0;
}

/* set offline flag */
int set_offline(struct online_list *clientlist, char *mac)
{	
	if(!clientlist) {
		return -1;
	}

	struct client *p;
	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
		if(strcmp(mac,p->mac) == 0) {
			p->online = FLAG_OFFLINE;
			break;
		}
	}

	return 0;
}

/* heartbeat test */
int heartbeat(struct online_list *clientlist, char *mac)
{
	if(!clientlist) {
		return -1;
	}

	struct client *p;
	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
		if(strcmp(mac,p->mac) == 0) {
			p->heartbeats = MAX_HEARTBEAT_NUM;
			break;
		}
	}

	return 0;
}

/* get sum of online clients */
int get_online_num(struct online_list *clientlist)
{
	if(!clientlist) {
		return 0;
	}
	
	int sum = 0;
	struct client *p;
	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
		if(p->online == FLAG_ONLINE) {
			sum += 1;
		}
	}
	clientlist->clientnum = sum;

	return sum;
}

/* get total num of client, include offline */
int get_total_num(struct online_list *clientlist)
{
	if(!clientlist) {
		return 0;
	}

	int total = 0;
	struct client *p;
	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
		total += 1;
	}
	clientlist->totalclient = total;

	return total;
}

/* online client checkout handler */
void online_checkout_handler()
{
	if(!clist) {
		return ;
	}

	struct client *p;
	p = clist->onlist;
	while(p->next) {
		p = p->next;
		if(p->online == FLAG_ONLINE) {
			p->heartbeats -= 1;
			if(p->heartbeats <= 0) {
				p->online = FLAG_OFFLINE;
				p->heartbeats = 0;
			}
		}
	}
}

/* get client info by mac */
int get_client_by_mac(struct online_list *clientlist, 
		char *mac, struct client_info *client)
{
	if(!clientlist) {
		return -1;
	}

	struct client *p;
	p = clientlist->onlist;
	while(p->next) {
		p = p->next;
		if(strcmp(mac,p->mac) == 0 ) {
			if(p->online == FLAG_ONLINE) {
				strcpy(client->mac,p->mac);
				strcpy(client->ip,p->ip);
				client->listenport = p->listenport;
				client->heartbeats = p->heartbeats;

				return 0;
			}
			break;
		}
	}

	return -1;
}

void print_clist(struct online_list *clist)
{
	struct client *p = clist->onlist;
	get_online_num(clist);
	get_total_num(clist);
	printf("\nclientnum:%d, totalclient:%d\n",clist->clientnum,clist->totalclient);
	while(p->next) {
		p = p->next;
		printf("Online:%d, MAC:%s, IP:%s, ListenPort:%d, Heartbeats:%d\n",
				p->online,p->mac,p->ip,p->listenport,p->heartbeats);
	}
	printf("\n");
}

