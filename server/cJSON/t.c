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
	cJSON *root, *fmt;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root,"MsgType","MsgOnine");
	cJSON_AddStringToObject(root,"ClientIP","192.168.0.25");
	cJSON_AddStringToObject(root,"ClientMac","123");
	cJSON_AddNumberToObject(root,"ListenPort",33443);
	
	out = cJSON_PrintUnformatted(root);

	printf("%s\n",out);
	strcpy(text,out);
	free(out);

	printf("%s\n",text);
}
