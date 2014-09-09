/*************************************************************************
	> File Name: test_gettime.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-09-01 15:51:13
 ************************************************************************/

#include <stdio.h>
#include "tools.h"

int main()
{
	char *p;
	p = get_curr_time();

	printf("%s\n",p);

	return 0;
}
