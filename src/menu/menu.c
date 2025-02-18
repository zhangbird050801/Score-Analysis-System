#include "interface/interface.h"

/**
 * @brief: 不同菜单的提示
 */
static const char *menuPrompts[MENU_NUMBER] = {"\
    +============+============+==============+========+ \n\
    | 1.教师登录 | 2.用户注册 | 3.管理员登录 | 4.退出 | \n\
    +============+============+==============+========+ \n", \
    "\
    +============+============+================+============+ \n\
    | 1.我是买家 | 2.我是卖家 | 3.个人信息管理 | 4.注销登陆 | \n\
    +============+============+================+============+ \n"
};

static const char *menuName[MENU_NUMBER] = {"Main"};

static const char *tapNum[MENU_NUMBER] = {"\t\t      "};

const int optionNumber[MENU_NUMBER] = {4};

/**
 * @brief: 操作提示
 * @param type 菜单类型
 */
static void promptMessage(Menu type){
    printf("%s%s%s Menu%s\n", tapNum[type], REVERSE, menuName[type], RESET);
    printf("%s\n%s请输入您的操作:%s ", menuPrompts[type], FRONT_GREEN, RESET);
}; 

/**
 * @brief 获取用户操作
 * @param type 菜单类型
 * @return res 返回用户选择的操作
 */
int menu(Menu type)
{
    PromptMessage(type);
    char buffer[MAX_LEN]; 
    int res;
    scanf("%s", buffer);
    res = atoi(buffer);
    while(1) {
        if(res >= 1 && res <= optionNumber[type]) break;
        failureMessage();
        printf("%s请输入您的操作:%s ", FRONT_GREEN, RESET);
        scanf("%s", buffer);
        res = atoi(buffer);
    }
    return res;
}