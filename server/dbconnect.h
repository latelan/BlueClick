/*************************************************************************
	> File Name: dbconect.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 20:50:55
 ************************************************************************/

#ifndef dbconnect__h
#define dbconnect__h

#include "common.h"
#include "/usr/include/mysql/mysql.h"

#define HOST "localhost"
#define USER "blueclick"
#define PASSWORD "blueclick.com"
#define DATABASE "db_blueclick"
#define TBL_RESOURCE "tbl_resource"
#define TBL_RESOURCE_OWNER "tbl_resource_owner"
#define TBL_RESOURCE_TAGS "tbl_resource_tags"

MYSQL *open();

int add_share_resource(const struct resource_type *res);
int query_res_md5(const char *key, char *res_md5);
int query_res_info(const char *res_md5, struct resource_type *resinfo);

#endif
