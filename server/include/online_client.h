/*************************************************************************
	> File Name: online_client.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 23:13:18
 ************************************************************************/

#ifndef online_client__h
#define online_client__h

#include "common.h"

/* init a online client list */
struct online_list *create_online_list();

/* add a new client into online lsit */
int add_to_online_list(struct online_list *clientlist, struct client_info *newclient);

/* delete a client from online list */
int del_from_online_list(struct online_list *clientlist, char *ip);

/* test mac of client whether online */
int is_in_online_list(struct online_list *clientlist, char *mac);

/* set online flag */
int set_online(struct online_list *clientlist, char *mac);

/* set offline flag */
int set_offline(struct online_list *clientlist, char *mac);

/* heartbeat record */
int heartbeat(struct online_list *clientlist, char *mac);

/* get sum of online clients */
int get_online_num(struct online_list *clientlist);

/* get total num of client,include offline */
int get_total_num(struct online_list *clientlist);

/* online client checkout handler */
/* void online_checkout_handler(struct online_list *clientlist); */
void online_checkout_handler();

/* get client info by mac */
int get_client_by_mac(struct online_list *clientlist, char *mac, struct client_info *client);

void print_clist(struct online_list *clist);
#endif 
