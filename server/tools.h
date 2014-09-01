/*************************************************************************
	> File Name: tools.h
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-08-28 15:02:58
 ************************************************************************/

#ifndef tools__h
#define tools__h

#include <time.h>

void doit(char *text);
time_t str_to_time(const char *datetime);
char *get_curr_time(void);
int get_tag_num(const char *key,char sp);
int get_tag_by_index(const char *key,char *tag, int index);

#endif
