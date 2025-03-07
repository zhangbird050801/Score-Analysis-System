#include "interface/interface.h"

static HANDLE handler[] = {addUser};

void adminInterface(){
    makeInterface(ADMIN, handler);
}

/**
 * @brief 增加用户
 */
void addUser(){
    char name[MAX_NAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("请输入新用户的用户名：");
    scanf("%s",name);

    // 该用户名已经存在
    if(searchByUserName(name) != -1){
        addUserError();
        failureMessage();
        return;
    }

    printf("请输入新用户的密码：");
    scanf("%s",password);

    addNewUser(name,password);
}