#include "interface/interface.h"

static HANDLE handler[] = {modifyPassword};

void modifyInterface() {
    makeInterface(MODIFY, handler);
}

/**
 * @brief 修改用户密码
 */
void modifyPassword() {
    User* user =  getUser(nowUser);

    char oldPassword[MAX_PASSWORD_LENGTH], newPassword[MAX_PASSWORD_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

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
            modifyPasswordSuccess();
        }
    }
}