#include "tools/printHelp.h"

/**
 * @brief 获取字符串的宽度
 */
int get_display_width(const char *str) {
    wchar_t wstr[256];
    mbstowcs(wstr, str, 256); 
    return wcswidth(wstr, wcslen(wstr));
}

/**
 * @brief 居中打印字符串
 */
void print_centered(const char *str, int column_width) {
    int str_width = get_display_width(str);
    if (str_width >= column_width) {
        printf("%s", str);
        return;
    }
    int left_pad = (column_width - str_width) / 2;
    int right_pad = column_width - str_width - left_pad;
    printf("%*s%s%*s", left_pad, "", str, right_pad, "");
}