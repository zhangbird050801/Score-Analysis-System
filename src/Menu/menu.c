#include "interface/interface.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

static const char *menuPrompts[MENU_NUMBER] = {"\
    +============+============+==============+========+ \n\
    | 1.教师登录 | 2.用户注册 | 3.管理员登录 | 4.退出 | \n\
    +============+============+==============+========+ \n"
};

static const char *menuName[MENU_NUMBER] = {"Main"};

static const char *tapNum[MENU_NUMBER] = {"\t\t      "};

static void PromptMessage(Menu type){
    printf("%s%s%s Menu%s\n", tapNum[type], REVERSE, menuName[type], RESET);
    printf("%s\n%s请输入您的操作:%s ", menuPrompts[type], FRONT_GREEN, RESET);
}; 

const int optionNumber[MENU_NUMBER] = {4};

int menu(Menu type)
{
    PromptMessage(type);
    char buffer[MAX_LEN]; 
    int res;
    scanf("%s", buffer);
    res = atoi(buffer);
    while(1)
    {
        if(res >= 1 && res <= optionNumber[type]) break;
        failureMessage();
        printf("%s请输入您的操作:%s ", FRONT_GREEN, RESET);
        scanf("%s", buffer);
        res = atoi(buffer);
    }
    return res;
}