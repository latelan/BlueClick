/*************************************************************************
	> File Name: client_info.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 09:57:04
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAX_CLIENT_NUMBER 200

struct client_info client_list[MAX_CLIENT_NUMBER];
int clientnum = 0;

// check mac in client_list
int has_client(const char *mac)
{
	for(int i=0;i<clientnum; ++i) {
		if( strcmp(mac,client_list[i].mac) == 0) {
			return i;
		}
	}

	return -1;
}

// add a new client to client_list
int add_client(struct client_info *newclient)
{
	if(clientnum > MAX_CLIENT_NUMBER){
		return -1;
	}
	
	int index = has_client(newclient->mac);
	if(index == -1) {
		index = clientnum++;
	}
	strcpy(client_list[index].mac,newclient->mac);
	strcpy(client_list[index].ip,newclient->ip);
	client_list[index].listenport = newclient->listenport;

	return 0;
}

void print_client_list()
{
	for(int i=0; i<clientnum;++i) {
		printf("client: %d\n",i);
		printf(" mac: %s\n",client_list[i].mac);
		printf(" ip: %s\n",client_list[i].ip);
		printf(" listenport: %d\n\n",client_list[i].listenport);
	}
}
///**
// * Function: create a new client list
// * params: client_list - pointer
// * return: success - 0, fail - -1
// */
//int create_client_list(struct client_list *client_list)
//{
//	if(client_list != NULL) {
//		delete [] client_list->clients;
//		delete [] client_list;
//	}
//	
//	client_list = new struct client_list;
//	client_list->clientnum = 0;
//	client_list->clients = NULL;
//	return 0;
//}
//
//// add a new client to client_list
//int add_client(struct client_list *client_list, const struct client_info *newclient)
//{
//	if(!client_list) {
//		return -1;
//	}
//
//
//	struct client_info *p;
//	p = client_list->clients;
//	while(!p->next) {
//		p = p->next;
//	}
//
//	struct client_info *newclient = new struct client_info;
//	client_info = *newclient;
//	p->next = client_info;
//	client_info->next = NULL;
//	client_list->clientnum +=1;
//
//	return 0;
//}
//
//void print_client_list(struct client_list *client_list)
//{
//	if(!client_list) {
//		return -1;
//	}
//
//	int num = client_list->clientnum;
//	int counter = 0;
//	struct client_info *p;
//	p = client_list->clients;
//	while(!p->next) {
//		counter ++;
//		printf("client: %d\n",counter);
//		printf(" mac: %s\n",p->mac);
//		printf(" ip: %s\n",p->ip);
//		printf(" listenport: %d\n\n",p->listenport);
//		p=p->next;
//	}
//
//	return 0;
//}
