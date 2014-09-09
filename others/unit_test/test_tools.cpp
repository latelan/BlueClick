/*************************************************************************
	> File Name: test_tools.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-09-01 16:55:04
 ************************************************************************/

#include <stdio.h>
#include "tools.h"

int main()
{
	char key[] = "key1,key2,key3";
	char tag[32];

	int num = get_tag_num(key,',');
//	for(int i=0;i<num+1;i++) {
		
		get_tag_by_index(key,tag,2);

		printf("tag %d: %s\n",2,tag);
//	}

	return 0;
}
