/*************************************************************************
	> File Name: test_db.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 21:17:32
 ************************************************************************/

#include <stdio.h>
#include "common.h"
#include "dbconnect.h"

int main()
{
	struct resource_type res = {"Children of Earth","3.5M","40FBB9FD5CD299F95A032D2B4F705432",3456,"2014-08-28 21:20:32"};

	struct resource_type resinfo;
	char key[10] = "韩寒";
	char md5[33];
//	add_share_resource(&res);
	query_res_md5(key,md5);
	query_res_info(md5,&resinfo);

	printf("%s\n",resinfo.name);
	printf("%s\n",resinfo.size);
	printf("%s\n",resinfo.md5);
	printf("%d\n",resinfo.piececount);
	printf("%s: %s\n",key,md5);
	return 0;
}
