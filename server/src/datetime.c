#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "datetime.h"
/**
 * 功能：将字符串datetime转换为time_t
 * 参数：datetime - 时间字符串
 * 返回值：unixtime - 该字符串的时间戳
 */
time_t str_to_time(const char *datetime)
{
	struct tm tm_time;
	time_t unixtime;
	strptime(datetime,"%Y-%m-%d %H:%M:%S",&tm_time);
	unixtime = mktime(&tm_time);
	return unixtime;
}
/**
 * 功能：获取当前时间
 * 参数：无
 * 返回值：strtime - 形如 "2014-05-26 12:14:22"
 *                   的时间字符串
 */
char *get_curr_time(void)
{
	time_t now;
	struct tm *nowtime;
	char *strtime = NULL; 

	now = time(NULL);
	nowtime = localtime(&now);

	strtime = (char *)malloc(sizeof(char)*50);
	sprintf(strtime,"%04d-%02d-%02d %02d:%02d:%02d",nowtime->tm_year+1900,nowtime->tm_mon+1,nowtime->tm_mday,nowtime->tm_hour,nowtime->tm_min,nowtime->tm_sec);
	
	return strtime;
}
/**
 * 功能：计算time0到time1经历的小时，不足一小时算一小时
 * 参数：time1 - 字符串时间1
 * 		 time0 - 字符串时间0
 * 返回值：时间差值，单位为小时
 */
long diff_time_hour(const char *start_time,const char *stop_time)
{
	time_t oldtimep,newtimep;
	long hour;
	oldtimep = str_to_time(start_time);
	newtimep = str_to_time(stop_time);

	hour = difftime(newtimep,oldtimep) / 3600;

	if((long)difftime(newtimep,oldtimep)%3600 > 0)
	{
		hour += 1;
	}

	return hour;
}
/*
int main()
{
	char *time;
	int timep;
	time = get_curr_time();
	timep = str_to_time(time);
	printf("%s\n%d\n",time,timep);
}
*/
