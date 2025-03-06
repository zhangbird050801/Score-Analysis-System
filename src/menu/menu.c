#include "interface/interface.h"

/**
 * @brief: 不同菜单的提示
 */
static const char *menuPrompts[MENU_NUMBER] = {"\
    +============+==============+========+ \n\
    | 1.教师登录 | 2.管理员登录 | 3.退出 | \n\
    +============+==============+========+ \n", \
    "\
    +============+============+============+==================+================+============+ \n\
    | 1.成绩排序 | 2.成绩分析 | 3.成绩查询 | 4.成绩录入与修改 | 5.个人信息修改 | 6.注销登录 | \n\
    +============+============+============+==================+================+============+ \n", \
    "\
    +================+========+ \n\
    | 1.添加学生 | 2.返回 | \n\
    +================+========+ \n",
    " ",\
    " ",\
    "\
    +================+========+ \n\
    | 1.通过学号查询 | 2.返回 | \n\
    +================+========+ \n",
    "\
    +================+========+ \n\
    | 1.添加学生成绩 | 2.返回 | \n\
    +================+========+\n",\
    "\
    +================+========+ \n\
    | 1.修改个人密码 | 2.返回 | \n\
    +================+========+\n"
};

static const char *menuName[MENU_NUMBER] = {"Main", "User", "Admin", "Sort", "Analyze", "Search", "Score", "Modify"};

static const char *tapNum[MENU_NUMBER] = {"\t\t   ", "\t\t\t\t\t      ", "\t\t", "\t\t", "\t\t", "\t\t", "\t\t", "\t\t"};

const int optionNumber[MENU_NUMBER] = {3, 6, 2, 2, 2, 2, 2, 2};

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
    promptMessage(type);
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