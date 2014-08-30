/*************************************************************************
	> File Name: test_online_client.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 23:12:22
 ************************************************************************/

#include <stdio.h>
#include "common.h"
#include "online_client.h"

int main()
{
	struct online_list *clist;
	clist = create_online_list();

	if(!clist) {
		printf("create_online_list failed.\n");
	}
	
	struct client_info client[6] = {{"84-4B-F5-83-9D-CB"，"192.168.0.12",33443,3}};//{"74-4B-F5-83-9D-CB"，"192.168.0.12",33443,3},{"64-4B-F5-83-9D-CB"，"192.168.0.12",33443,3},{"54-4B-F5-83-9D-CB"，"192.168.0.12",33443,3},{"44-4B-F5-83-9D-CB"，"192.168.0.12",33443,3}};

	for(int i=0; i<5; i++) {
		add_to_online_list(clist,&client[i]);
	}

	struct client *p = clist->onlist;
	while(p->next) {
		p = p->next;
		printf("Online: %d,MAC: %s,IP: %s,ListenPort: %d,Heartbeats: %d\n",
				p->online,p->mac,p->ip,p->listenport,p->heartbeats);
	}

}
