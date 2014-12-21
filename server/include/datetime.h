#ifndef _DATATIME_H_
#define _DATATIME_H_

#include <time.h>

/* 将字符串时间转换为时间戳 */
time_t str_to_time(const char *datetime);

/* 获取当前时间 */
char *get_curr_time(void);

/* 计算stop_time - start_time 的差值 */
long diff_time_hour(const char *star_time, const char *stop_time);

#endif // _DATATIME_H_
