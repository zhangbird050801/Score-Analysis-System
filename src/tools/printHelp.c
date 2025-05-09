#include "tools/printHelp.h"

int get_display_width(const char *str) {
    wchar_t wstr[256];
    mbstowcs(wstr, str, 256); // 将多字节字符串转为宽字符
    return wcswidth(wstr, wcslen(wstr));
}

void print_centered(const char *str, int column_width) {
    int str_width = get_display_width(str);
    if (str_width >= column_width) {
        printf("%s", str); // 过长直接输出（或截断）
        return;
    }
    int left_pad = (column_width - str_width) / 2;
    int right_pad = column_width - str_width - left_pad;
    printf("%*s%s%*s", left_pad, "", str, right_pad, "");
}