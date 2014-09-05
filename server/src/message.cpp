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

void json_to_msg_client_info(char *text, struct client_info *client) 
{
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
	cJSON *json;

	json = cJSON_Parse(text);
	if(!json) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else {
		strcpy(qres->key,cJSON_GetObjectItem(json, "ClientIP")->valuestring);
	}
}

void json_to_resource_share(char *text, struct resource_share *res)
{
	cJSON *json;

	json = cJSON_Parse(text);
	if(!json) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else {
		cJSON *child = cJSON_GetObjectItem(json,"Resource");
		strcpy(res->name,cJSON_GetObjectItem(child,"ResName")->valuestring);
		strcpy(res->tag,cJSON_GetObjectItem(child,"ResTag")->valuestring);
		strcpy(res->size,cJSON_GetObjectItem(child,"ResSize")->valuestring);
		strcpy(res->md5,cJSON_GetObjectItem(child,"ResMD5")->valuestring);
		strcpy(res->mac,cJSON_GetObjectItem(child,"ResOwner")->valuestring);
		res->piececount = cJSON_GetObjectItem(child,"ResPieceCount")->valueint;
	}
}

void json_to_download_req(char *text, struct download_req *req)
{
	cJSON *json;

	json = cJSON_Parse(text);
	if(!json) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else {
		strcpy(req->clientip,cJSON_GetObjectItem(json, "ClientIP")->valuestring);
		strcpy(req->md5,cJSON_GetObjectItem(json,"ResMD5")->valuestring);
		req->numwant = cJSON_GetObjectItem(json,"NumWant")->valueint;
		strcpy(req->event,cJSON_GetObjectItem(json,"Event")->valuestring);
	}
}

void server_info_to_json(char *text, struct server_info *server)
{
	cJSON *root;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "MsgType", "MsgOnlineResponse");
	cJSON_AddStringToObject(root, "ServerIP", server->ip);
	cJSON_AddStringToObject(root, "Reserved", "null");
	
	char *out;
	out = cJSON_PrintUnformatted(root);
	strcpy(text,out);

	free(out);
}

char* res_list_to_json(struct resource_type *res, int len)
{
	cJSON *root,*fmt, *sub;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root,"MsgType","ResList");
	cJSON_AddNumberToObject(root,"ResCount",len);
	cJSON_AddItemToObject(root,"Resource",sub = cJSON_CreateArray());
	for(int i=0;i<len;i++) {
		cJSON_AddItemToArray(sub,fmt=cJSON_CreateObject());
		cJSON_AddStringToObject(fmt,"ResName",res[i].name);
		cJSON_AddStringToObject(fmt,"ResSize",res[i].size);
		cJSON_AddStringToObject(fmt,"ResMD5",res[i].md5);
		cJSON_AddNumberToObject(fmt,"ResPieceCount",res[i].piececount);
	}

	return cJSON_PrintUnformatted(root);
}

char *peer_info_to_json(struct peer_info *peers, int len)
{
	cJSON *root,*sub,*fmt;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root,"MsgType","MsgClientList");
	cJSON_AddNumberToObject(root,"ClientCount",len);
	cJSON_AddItemToObject(root,"Client",sub = cJSON_CreateArray());
	for(int i=0;i<len;i++) {
		cJSON_AddItemToArray(sub,fmt=cJSON_CreateObject());
		cJSON_AddStringToObject(fmt,"ClientIP",peers[i].ip);
		cJSON_AddNumberToObject(fmt,"ClientPort",peers[i].port);
		cJSON_AddNumberToObject(fmt,"AvailablePieces",peers[i].availablepieces);
		cJSON_AddNumberToObject(fmt,"AvailableConnections",peers[i].availableconnections);
	}
	
	return cJSON_PrintUnformatted(root);
}
