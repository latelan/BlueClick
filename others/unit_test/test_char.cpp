/*************************************************************************
	> File Name: test_char.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-29 10:38:50
 ************************************************************************/

#include <stdio.h>
#include <string.h>

void fun(char *md5)
{
	char tmp[53] = "123";
	strcpy(md5,tmp);
}

int main()
{
	char md5[33];

	fun(md5);

	printf("%s\n",md5);
}
