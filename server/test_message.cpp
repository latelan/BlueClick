/*************************************************************************
	> File Name: test_message.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 11:13:19
 ************************************************************************/

#include <stdio.h>
#include "common.h"
#include "message.h"
#include "dbconnect.h"

int main()
{
	char *text = NULL;

	struct queryres key = {"梁静茹"};
	struct resource_type res[10];
	int len; 

	get_res_list(key,res,&len);

	res_list_to_json(text,res,len);

	printf(text);


}
