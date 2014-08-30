/*************************************************************************
	> File Name: test_db.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 21:17:32
 ************************************************************************/

#include <stdio.h>
#include "common.h"
#include "dbconnect.h"
#include "tools.h"
#include "message.h"

int main()
{
//	struct resource_type res = {"Children of Earth","3.5M","40FBB9FD5CD299F95A032D2B4F705432",3456};

	struct resource_type resinfo;
	char md5[10][33];
//	add_share_resource(&res);
//	query_res_md5(key,md5,&len);

//	for(int i=0;i<len;i++) {
//		printf("NO%d: %s\n",i,md5[i]);
//	}
//	query_res_info(md5[0],&resinfo);
	char *text = NULL;
	struct queryres key = {"梁静茹"};
	struct resource_type res[10];
	int len;

	get_res_list(key,res,&len);
	text = res_list_to_json(text,res,len);

	printf("%s\n",text);
//	for(int i=0;i<len;i++) {
//		printf("NO%d.name: %s size: %s md5: %s piececount: %d\n",i,res[i].name,res[i].size,res[i].md5,res[i].piececount);
//	}
	
	
	return 0;
}
