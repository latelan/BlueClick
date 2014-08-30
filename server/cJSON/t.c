/*************************************************************************
	> File Name: t.c
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 14:25:50
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

int main()
{
	char *out;
	char text[1024];
	cJSON *root, *fmt, *sub;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root,"MsgType","ResList");
	cJSON_AddNumberToObject(root,"ResCount", 4);
	cJSON_AddItemToObject(root,"Rescource",sub = cJSON_CreateArray());
//	cJSON_AddItemToArray(root,sub = cJSON_CreateObject());
	
	for(int i=0;i<3;i++) {
		cJSON_AddItemToArray(sub,fmt = cJSON_CreateObject());
		cJSON_AddStringToObject(fmt,"ResName","zhang");
		cJSON_AddStringToObject(fmt,"ResSize","567MB");
		cJSON_AddStringToObject(fmt,"ResMD5","40FBB9FD5CD299F95A032D2B4F705432");
		cJSON_AddNumberToObject(fmt,"ResPieceCount",3456);
	}

	out = cJSON_Print(root);

	printf("%s\n",out);
	strcpy(text,out);
	free(out);

	printf("%s\n",text);
}
