/*************************************************************************
	> File Name: message.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 15:53:18
 ************************************************************************/

#ifndef message__h
#define message__h

#include "common.h"

void json_to_msg_client_info(char *text, struct client_info *client);
void server_info_to_json(char *text, struct server_info *server);

char* res_list_to_json(char *text, struct resource_type *res, int len);

char *peer_info_to_json(struct peer_info *peers, int len);
#endif
