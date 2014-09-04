/*************************************************************************
	> File Name: test_chararray.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-30 08:36:48
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int remove_duplicate_md5(int *num, int *len)
{
	int tlen = *len;

	for(int i=0; i<tlen; i++) {
		for(int j=tlen-1; j>i;j--) {
			if(num[i] == num[j]) {
				for(int k=j;k<tlen-1;k++) {
					num[k] = num[k+1];
				}
				tlen -= 1;
			}

		}
	}

	*len = tlen;
	
	return tlen;
}

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
	int num[12] = {2,3,4,5,5,5,6,7,7,1,1,1};
	int len = 12;

	for(int i=0;i<len;i++) {
		printf("%d ",num[i]);
	}

	printf("\n");


	remove_duplicate_md5(num,&len);
	//fun(name);

	for(int i=0;i<len;i++) {
		printf("%d ",num[i]);
	}

	printf("\n");

	return 0;
}
