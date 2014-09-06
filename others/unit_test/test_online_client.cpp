/*************************************************************************
	> File Name: test_online_client.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 23:12:22
 ************************************************************************/

#include <stdio.h>
#include "common.h"
#include "online_client.h"

void print_clist(struct online_list *clist)
{
	struct client *p = clist->onlist;
	get_online_num(clist);
	get_total_num(clist);
	printf("\nclientnum: %d totalclient: %d\n",clist->clientnum,clist->totalclient);
	while(p->next) {
		p = p->next;
		printf("Online: %d,MAC: %s,IP: %s,ListenPort: %d,Heartbeats: %d\n",
				p->online,p->mac,p->ip,p->listenport,p->heartbeats);
	}
	printf("\n");
}

int main()
{
	struct online_list *clist;
	clist = create_online_list();

	if(!clist) {
		printf("create_online_list failed.\n");
	}
	struct client_info clt = {"84-4B-F5-83-9D-CB","192.168.0.12",33443,3};
	char mac[] = "84-4B-F5-83-9D-CB";

	struct client_info client[6] = {
		{"84-4B-F5-83-9D-CB","192.168.0.12",33443,3},
		{"74-4B-F5-83-9D-CB","192.168.0.12",33443,3},
		{"64-4B-F5-83-9D-CB","192.168.0.12",33443,3},
		{"54-4B-F5-83-9D-CB","192.168.0.12",33443,3},
		{"44-4B-F5-83-9D-CB","192.168.0.12",33443,3}
	};


	/* test add new client */
	for(int i=0; i<5; i++) {
		add_to_online_list(clist,&client[i]);
	}
	print_clist(clist);
	printf("clientnum: %d\n",clist->clientnum);

	/* test delete client */
	for(int i=0; i<5; i++) {
		del_from_online_list(clist,client[i].mac);
	}

	print_clist(clist);

	for(int i=0; i<5; i++) {
		add_to_online_list(clist,&client[i]);
	}
	/* test set offline */
	set_offline(clist,mac);
	print_clist(clist);


	/* test set online */
	set_online(clist,mac);
	print_clist(clist);
	

	/* test heartbeats */
	for(int i=0;i<5;i++) {
		online_checkout_handler(clist);
		print_clist(clist);
		getchar();
	}
	

	set_online(clist,mac);
	print_clist(clist);

	/* test get client by mac */
	struct client_info clientinfo;
	int ret = get_client_by_mac(clist,mac,&clientinfo);
	if(ret == 0) {
		printf("%s %s %d %d\n",clientinfo.mac,clientinfo.ip,clientinfo.listenport,clientinfo.heartbeats);
	}
}
