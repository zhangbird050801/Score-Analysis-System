#include "tools/hint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char* FILEPATH = "src/Data/MaxId.txt";

// type: U-用户
// ID 只和时间顺序有关，如果有数据被删了，ID 也不会被新的 ID 填补

/**
 * @brief 生成 id
 * @param s
 * @param type
 */
void generateId(char* s, char type) {
    int uid;
    uid = 0;

    FILE* ptr = fopen(FILEPATH, "r");
    
    if(ptr == NULL){
        failureMessage();
        return ;
    }
    else{
        fscanf(ptr, "%d", &uid);
        fclose(ptr);
    }
    
    int ID = 0;
    switch(type)
    {
        case 'U': 
            ID = uid ++;
            break;
    }

    sprintf(s, "%c%05d", type, ID); // 向 s 中写入 %c%05d 这样的字符串
    ptr = fopen(FILEPATH, "w");
    fprintf(ptr, "%d\n", uid);
    fclose(ptr);
}

char* getTime() {
    time_t time_now;
    time(&time_now);

    struct tm* TIME = localtime(&time_now);

    char* s = (char*)malloc(20 * sizeof(char));
    if (s == NULL) {
        return NULL;
    }

    snprintf(s, 20, "%d-%02d-%02d %02d:%02d:%02d", 
            TIME->tm_year + 1900, TIME->tm_mon + 1, TIME->tm_mday,
            TIME->tm_hour, TIME->tm_min, TIME->tm_sec);

    return s;
}