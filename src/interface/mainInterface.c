#include "interface/interface.h"
#include <termios.h>

static HANDLE handler[] = {userLogin, adminLogin};

/**
 * @brief 菜单逻辑
 * @param type 菜单类型
 * @param handler 处理函数
 */
void makeInterface(Menu type, HANDLE handler[])
{
    int op = menu(type);
    while(op != optionNumber[type]) {
        handler[op - 1](); 
        op = menu(type);
    }
}

/**
 * @brief 主界面
 */
void mainInterface() {
    makeInterface(MAIN, handler);
}

/**
 * @brief 用户登录
 */
void userLogin()
{
    getchar(); 

    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    getName(username);
    getPassword(password); 
    puts("");

    int flag = check(username, password); // -1 表示未查找到用户 1 表示查找到对应的用户
    
    if(flag == -1)
        errorFindingUser(), failureMessage();
    else if(check(username, password)) {
        userLoginSuccess(username);
    }
    else{
        loginFailureMessage();
        tryAgain(username, password, 3);
    }
}

/**
 * @brief 系统管理员登录
 */
void adminLogin() {
    getchar(); 

    char adminname[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    getName(adminname);
    getPassword(password); 
    puts("");

    if((strcmp(adminname,ADMIN_NAME) == 0)&&(strcmp(password,ADMIN_PASSWORD) == 0)){
        adminLoginSuccess();
    }else{
        loginFailureMessage();
    }
}

/**
 * @brief 管理员登陆成功
 */
void adminLoginSuccess(){
    loginSuccessMessage();
    adminInterface();
}

/**
 * @brief 用户登录成功
 * @param username 用户名
 */
void userLoginSuccess(char *username)
{
    nowUser = searchByUserName(username);
    loginSuccessMessage();
    userInterface();
}

/**
 * @brief 获取用户名
 * @param name 用户名
 */
void getName(char* name)
{
    printf("请输入用户名：");
    int i = 0;
    char c;
    while((c = getchar()) != '\n' && i < MAX_NAME_LENGTH - 1)
        name[i ++] = c;
    name[i] = '\0';
}

/**
 * @brief 获取密码
 * @param password 密码
 */
void getPassword(char* password) {
    struct termios oldAttr, newAttr;
    
    tcgetattr(fileno(stdin), &oldAttr);
    newAttr = oldAttr;
    newAttr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSAFLUSH, &newAttr);
    
    printf("请输入密码：");

    int i = 0;
    char c;
    while ((c = getchar()) != '\n' && i < MAX_PASSWORD_LENGTH - 1) {
        password[i++] = c;
        putchar('*'); 
    }
    password[i] = '\0';
    
    tcsetattr(fileno(stdin), TCSANOW, &oldAttr);
}

/**
 * @brief 重新尝试
 * @param username 用户名
 * @param password 密码
 * @param cnt 剩余尝试次数
 */
void tryAgain(char *username, char *password, int cnt) // 重新尝试
{
    if(cnt == 0){
        printf("%s%s%s您的次数已用完!\n%s", BOLD, UNDERLINE, FRONT_RED, RESET);
        exitMessage();
        exit(0);
    }
    printf("您还有 %s%s%s%d%s 次机会。", BOLD, UNDERLINE, FRONT_RED, cnt, RESET);
    getPassword(password);
    puts("");
    if(check(username, password)!= 1)
        tryAgain(username, password, cnt - 1);
    else
        userLoginSuccess(username);
}