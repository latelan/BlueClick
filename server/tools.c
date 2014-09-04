/*************************************************************************
  > File Name: tools.c
  > Author: latelan, coolboy1353@163.com
  > Created Time: 2014-08-28 15:02:09
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

/* convert string date to time_t format */
time_t str_to_time(const char *datetime)
{
	struct tm tm_time;
	time_t unixtime;
	strptime(datetime,"%Y-%m-%d %H:%M:%S",&tm_time);
	unixtime = mktime(&tm_time);

	return unixtime;
}

/* get current time */
char *get_curr_time(void)
{
	time_t now;
	struct tm *nowtime;
	char *strtime = NULL;

	now = time(NULL);
	nowtime = localtime(&now);

	strtime = new char[50];
	sprintf(strtime,"%04d-%02d-%02d %02d:%02d:%02d",
			nowtime->tm_year+1900,nowtime->tm_mon+1,
			nowtime->tm_mday,nowtime->tm_hour,
			nowtime->tm_min,nowtime->tm_sec);
	return strtime;
}

int get_tag_num(const char *tags, char fs)
{
	int num = 0;
	int i = 0;

	while(tags[i] != '\0') {
		if(tags[i] == fs) {
			num ++;
		}
		i++;
	}

	return num;
}

int get_tag_by_index(const char *key,char *tag,int index)
{
	char sp = ',';
	int k = 0;
	int l,r,m;
	int num = get_tag_num(key,sp);
	int len = strlen(key);

	if(index > num) {
		return -1;
	}

	l = 0;
	for(int i=0; i<len; i++) {
		if(key[i] == sp ) {
			k++;
			r = i;
			if(index == k-1) {
				m = 0;
				while(l<r) {
					tag[m++] = key[l++];
				}
				tag[m] = '\0';

				return 0;
			}
			else {
				l = i+1;
				r = l;
			}
		}
	}

	return -1;
}
