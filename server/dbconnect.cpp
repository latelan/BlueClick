#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/mysql/mysql.h"
#include "common.h"
#include "dbconnect.h"

const char *host = HOST;
const char *user = USER;
const char *password = PASSWORD;
const char *database = DATABASE;
const char *tbl_rescource = TBL_RESOURCE;
const char *tbl_rescource_owner = TBL_RESOURCE_OWNER;
const char *tbl_rescource_tags = TBL_RESOURCE_TAGS;

/* 全局mysql连接变量 */

/**
 * 功能：打开数据库
 * 参数：host - 数据库服务主机
 *       user - 用户名
 *       password - 密码
 *       database - 数据库名
 * 返回值：MYSQL 句柄
 */
MYSQL *open()
{
	MYSQL *mysql;

	mysql = mysql_init(NULL);
	mysql_options(mysql,MYSQL_SET_CHARSET_NAME,"utf8");
	if(mysql == NULL)
	{
		printf("mysql_init failed!\n");
		return NULL;
	}

	mysql = mysql_real_connect(mysql,host,user,password,database,0,NULL,0);
	if(mysql == 0)
	{
		printf("mysql_real connect failed!\n");
		return NULL;
	}
	return mysql;
}
/**
 * 功能：添加分享资源
 * 参数：res_name - 资源名称
 *		 res_size - 资源大小
 *		 res_md5 - 资源md5
 *		 res_piececount - 资源分片数
 *		 res_sharetime - 分享时间
 *	返回值：添加成功返回0，失败返回1，数据库内部错误返回-1
 */
int add_share_resource(const struct resource_type *res)
{
	
	MYSQL *mysql = NULL;
	char query_str[512];
	int affect_rows;

	if(mysql == NULL) {
		mysql = open();
	}
	
	/* 检查是否为已分享 */
	sprintf(query_str,"INSERT INTO tbl_resource(f_res_name,\
		f_res_size,f_res_md5,f_res_piececount) VALUES('%s',\
		'%s','%s','%d')", res->name,res->size,res->md5,res->piececount);
	if(mysql_query(mysql,query_str)) {
		fprintf(stderr,"Error: %s\n",mysql_error(mysql));
		return -1;
	}

	affect_rows = mysql_affected_rows(mysql);
	mysql_close(mysql);
	if(affect_rows > 0) {
		return 0;
	}

	return -1;
}

/**
 * 功能：根据一个关键字搜索资源md5
 * 参数：key - 搜索关键字
 *		 res_md5 - 返回值，资源md5
 *返回值：成功查询返回0，所得md5放在_md5中，败返回-1
 */
int query_res_md5(const char *key, char *res_md5)
{
	MYSQL *mysql = NULL;
	char query_str[256];
	MYSQL_RES *result;
	MYSQL_ROW query_rows;

	if(mysql == NULL) {
		mysql = open();
	}

	sprintf(query_str,"SELECT f_res_md5 FROM tbl_resource_tags WHERE f_res_tags = '%s'",key);
	if(mysql_query(mysql,query_str)) {
		fprintf(stderr,"Error: %s\n",mysql_error(mysql));
		return -1;
	}

	result = mysql_use_result(mysql);

	if((query_rows = mysql_fetch_row(result)) != NULL) {
		// ret res_md5
		strcpy(res_md5, query_rows[0]);
		mysql_close(mysql);
		
		return 0;
	}
	mysql_close(mysql);

	return -1;
}

/**
 * 功能：根据MD5检索资源名称，资源大小，资源分片数
 * 参数：res_md5 - 资源MD5
 *		 resinfo 返回值，资源info
 * 返回值：成功查询返回0，查询结果放在res_name和res_piececount，失败返回-1
 */
int query_res_info(const char *res_md5,
	struct resource_type *resinfo)
{
	MYSQL *mysql = NULL;
	char query_str[512];
	MYSQL_RES *result;
	MYSQL_ROW query_rows;

	if(mysql == NULL) {
		mysql = open();
	}

//	sprintf(query_str,"SELECT tbl_resource.f_res_name,tbl_resource.f_res_size, tbl_resource.f_res_piececount,tbl_resource_owner.f_res_sharetime FROM tbl_resource,tbl_resource_owner WHERE tbl_resource.f_res_md5 = '%s' and tbl_resource.f_res_md5 = tbl_resource_owner.f_res_md5)",res_md5);
	sprintf(query_str,"SELECT f_res_name,f_res_size, f_res_piececount FROM tbl_resource WHERE f_res_md5 = '%s'",res_md5);
	printf("%s\n",query_str);		
	if(mysql_query(mysql,query_str)) {
		fprintf(stderr,"Error: %s\n",mysql_error(mysql));
		return -1;
	}

	result = mysql_use_result(mysql);
	if((query_rows = mysql_fetch_row(result)) != NULL) {
		// 提取结果放入reslist中
		strcpy(resinfo->name,query_rows[0]);
		strcpy(resinfo->size,query_rows[1]);
		strcpy(resinfo->md5,res_md5);
		resinfo->piececount = atoi(query_rows[2]);

		mysql_close(mysql);
		return 0;
	}

	mysql_close(mysql);
	return -1;
}


/**
 * 功能：根据资源MD5检索资源提供方
 * 参数：res_md5 - 资源md5
 *		 res_owner - 返回值，资源提供方
 *		 res_sharetime 返回值，共享时间
 * 返回值：成功查询返回0，
 */
int query_res_owner_sharetime(const char *res_md5,
		char *res_owner,
		char *res_sharetime)
{

}
