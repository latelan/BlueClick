/*************************************************************************
	> File Name: test_structs.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-29 16:04:19
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"

int fun(struct resource_type *res)
{
	for(int i=0;i<10;i++) {
//		sprintf(res[i]->name,"%d",i);
		strcpy(res[i].name,"zhang");
	}
}
int main()
{
	struct resource_type res[10];

	fun(res);

	for(int i=0;i<10;i++){
		printf("No: %d Name:%s\n",i,res[i].name);
	}
}
