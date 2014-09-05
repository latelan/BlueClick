/*************************************************************************
	> File Name: loadbalance.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-09-03 18:15:21
 ************************************************************************/

#ifndef loadbalance__h
#define loadbalance__h

void loadbalance_on_server(struct online_list *clist,struct download_req *req,struct peer_info *peers, int *len);

#endif
