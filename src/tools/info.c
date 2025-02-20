#include "tools/hint.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// 保留上一次最大的 ID
static const char* FILEPATH = "src/Data/maxId.txt";

// type: U-用户 S-学科
// ID 只和时间顺序有关，如果有数据被删了，ID 也不会被新的 ID 填补

/**
 * @brief 获取时间
 * @param {char*} s 
 * @return {*}
 */
void getTime(char* s) {
    // 计算当前日历时间 time_t 格式来存储时间
    time_t time_now;
    time(&time_now);

    // tm_year 从 1900 年算起
    // tm_mon 从 0 到 11

    struct tm* TIME = localtime(&time_now);
    sprintf(s, "%d-%d-%d", TIME->tm_year + 1900, TIME->tm_mon + 1, TIME->tm_mday);
}

/**
 * @brief 生成 id
 * @param s
 * @param type
 */
void generateId(char* s, char type) {
    int uid, sid;
    uid = sid = 0;

    FILE* ptr = fopen(FILEPATH, "r");
    
    if(ptr == NULL){
        failureMessage();
        return ;
    }
    else{
        fscanf(ptr, "%d%d", &uid, &sid);
        fclose(ptr);
    }
    
    int ID = 0;
    switch(type)
    {
        case 'U': 
            ID = uid ++;
            break;
        case 'T':
            ID = sid ++;
            break;
    }

    sprintf(s, "%c%05d", type, ID); // 向 s 中写入 %c%05d 这样的字符串
    ptr = fopen(FILEPATH, "w");
    fprintf(ptr, "%d %d\n", uid, sid);
    fclose(ptr);
}