/*************************************************************************
	> File Name: loadbalance.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-09-03 17:59:57
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "dbconnect.h"
#include "online_client.h"

#define MAX_DOWNLOAD_QUEUE 20	/* 最大下载队列长度 */

extern struct online_list *clist;
struct res_download_node dqueue[MAX_DOWNLOAD_QUEUE]; /* 下载队列 */
int len_dqueue;

/**
 * function: loadbalance algorithm on server
 * parameters: clist  - online client list
 * 				req   - download request info
 * 				peers - available connected peer list
 * return: void
 */
void loadbalance_on_server(struct online_list *clist,
		struct download_req *req,
		struct peer_info *peers,
		int *len)
{
	/* query mac list by md5 */
	char mac_list[10][32];
	int len_mac = 0;
	
	query_macs_by_md5(req->md5,mac_list,&len_mac);

	struct client_info client;

	*len = 0;
	for(int i=0;i<20;i++) {
		if(!is_in_online_list(clist,mac_list[i])) {
			get_client_by_mac(clist,mac_list[i],&client);
			strcpy(peers[*len].ip,client.ip);
			peers[*len].port = client.listenport;
			peers[*len].availablepieces = 0;
			peers[*len].availableconnections = 0;
			*len += 1;
		}
	}

	//TODO
	
}
