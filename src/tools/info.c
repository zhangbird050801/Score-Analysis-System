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

/**
 * @brief 获取当前时间
 * @return 时间字符串
 */
char* getTime() {
    time_t time_now;
    time(&time_now);

    struct tm* TIME = localtime(&time_now);

    // 增加缓冲区大小到64字节，足够处理任何情况
    char* s = (char*)malloc(64 * sizeof(char));
    if (s == NULL) {
        return NULL;
    }

    snprintf(s, 64, "%04d-%02d-%02d %02d:%02d:%02d", 
            TIME->tm_year + 1900, TIME->tm_mon + 1, TIME->tm_mday,
            TIME->tm_hour, TIME->tm_min, TIME->tm_sec);

    return s;
}


/**
 * @brief 获取UTF-8字符的字节长度
 * @param str 指向字符的指针
 * @return 字符的字节数，如果不是有效UTF-8字符返回1
 */
int getUTF8CharLength(const char* str) {
    if (!str) return 0;
    
    unsigned char c = (unsigned char)str[0];
    
    if (c < 0x80) {
        return 1;  // ASCII字符
    } else if ((c & 0xE0) == 0xC0) {
        return 2;  // 2字节UTF-8字符
    } else if ((c & 0xF0) == 0xE0) {
        return 3;  // 3字节UTF-8字符（中文）
    } else if ((c & 0xF8) == 0xF0) {
        return 4;  // 4字节UTF-8字符
    }
    
    return 1;  // 默认返回1，避免死循环
}

/**
 * @brief 将UTF-8字符串分解为字符数组
 * @param str 输入字符串
 * @param chars 输出的字符数组
 * @param maxChars 最大字符数
 * @return 实际字符数量
 */
int splitUTF8String(const char* str, char chars[][8], int maxChars) {
    if (!str) return 0;
    
    int count = 0;
    int pos = 0;
    int len = strlen(str);
    
    while (pos < len && count < maxChars) {
        int charLen = getUTF8CharLength(str + pos);
        if (charLen == 0) {
            pos++;  // 跳过无效字符
            continue;
        }
        
        // 复制字符
        strncpy(chars[count], str + pos, charLen);
        chars[count][charLen] = '\0';
        
        pos += charLen;
        count++;
    }
    
    return count;
}