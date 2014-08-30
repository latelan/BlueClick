/*************************************************************************
	> File Name: test_chararray.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 08:36:48
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int fun(char name[][20])
{
	for(int i=0;i<10;i++) {
		strcpy(name[i],"zhang");
	}

	return 0;
}

int main()
{
	char name[10][20];

	fun(name);

	for(int i=0;i<10;i++) {
		printf("%s\n",name[i]);
	}

	return 0;

}
