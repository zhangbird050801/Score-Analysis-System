#include "interface/interface.h"

// TODO: 定义 handler 
static HANDLE handler[] = {modifyPassword};

void modifyInterface() {
    makeInterface(MODIFY, handler);
}

// TODO: 修改个人密码(User) 
// hint: 用户登录之后 nowUser 保存着用户下标
void modifyPassword() {
    User* user =  getUser(nowUser);

    char oldPassword[MAX_PASSWORD_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("请输入原密码: ");
    scanf("%s", oldPassword);

    if (strcmp(user->password, oldPassword) != 0) {
        printf("原密码错误！\n");
       
    }else{
            printf("请输入新密码: ");
            scanf("%s", newPassword);

            printf("请再次输入新密码: ");
            scanf("%s", confirmPassword);

            if (strcmp(newPassword, confirmPassword) != 0) {
                modifyPasswordError();
                failureMessage();
            }else{
                strcpy(user->password, newPassword);
                modifyPasswardSuccess();
            }

    
    }
}