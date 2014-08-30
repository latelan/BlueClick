/*************************************************************************
  > File Name: tools.c
  > Author: latelan, coolboy1353@163.com
  > Created Time: 2014-08-28 15:02:09
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "message.h"
#include "dbconnect.h"

void doit(char *text)
{
	char *out;cJSON *json;

	json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);
		cJSON_Delete(json);
		printf("%s\n",out);
		free(out);
	}
}
