/*************************************************************************
	> File Name: message.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 15:12:53
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "cJSON.h"

// 
void json_to_msg_client_info(char *text, struct client_info *client) 
{
	char *out;
	cJSON *json;
	
	json = cJSON_Parse(text);
	if(!json) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else {
		strcpy(client->ip,cJSON_GetObjectItem(json, "ClientIP")->valuestring);
		strcpy(client->mac,cJSON_GetObjectItem(json, "ClientMAC")->valuestring);
		client->listenport = cJSON_GetObjectItem(json, "ClientListenPort")->valueint;
	}

}

void json_to_msg_queryres(char *text, struct queryres *qres) 
{
	char *out;
	cJSON *json;

	json = cJSON_Parse(text);
	if(!json) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else {
		strcpy(qres->qres,cJSON_GetObjectItem(json, "ClientIP")->valuestring);
	}
}

void json_to_msg_downloadres(char *text, struct downloadres * dres)
{
	
}

void server_info_to_json(char *text, struct server_info *server)
{
	cJSON *root,*fmt;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "MsgType", "MsgOnlineResponse");
	cJSON_AddStringToObject(root, "ServerIP", server->ip);
	cJSON_AddStringToObject(root, "Reserved", "null");
	
	char *out;
	out = cJSON_PrintUnformatted(root);
	strcpy(text,out);

	free(out);
}

void res_info_to_json(char *text, struct resource_type *res, int len)
{
	cJSON *root,*fmt;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root,"MsgType","ResList");
	cJSON_AddNumberToObject(root,"ResCount",len);
	fmt = cJSON_CreateArray();
	for(int i=0;i<len;i++) {
		cJSON_AddItemToArray(root,)
	}
	cJSON_
}
