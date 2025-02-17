#include "tools/hint.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void getTime(char* s)
{
    // 计算当前日历时间 time_t 格式来存储时间
    time_t time_now;
    time(&time_now);

    // tm_year 从 1900 年算起
    // tm_mon 从 0 到 11

    struct tm* TIME = localtime(&time_now);
    sprintf(s, "%d-%d-%d", TIME->tm_year + 1900, TIME->tm_mon + 1, TIME->tm_mday);
}