/*************************************************************************
	> File Name: download_queue.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-09-03 20:15:28
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAX_DOWNLOAD_QUEUE 20

extern struct res_download_node dqueue[MAX_DOWNLOAD_QUEUE];
extern int len_dqueue;

/* init download queue */
void init_download_queue()
{
	for(int i=0;i<MAX_DOWNLOAD_QUEUE;i++) {
		dqueue[i].dlist = NULL;
	}

	len_dqueue = 0;
}

/* add a download node into dqueue */
int add_download_node(struct peer_download_info *newdown)
{
	return 0;	
}

/* delete a download node from dqueue */
int delete_download_node(char *md5)
{
	return 0;
}
