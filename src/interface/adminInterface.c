#include "interface/interface.h"

// TODO: handler 创建
static HANDLE handler[] = {addUser};

// TODO: adminInterface 创建
void adminInterface(){
    makeInterface(ADMIN,handler);
}
// TODO: 增加 User 用户(也就是教师) 需要提示输入用户名，然后是密码
void addUser(){
    char name[MAX_NAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("请输入新用户的姓名：");
    scanf("%s",name);
    printf("请输入新用户的密码：");
    scanf("%s",password);
    addNewUser(name,password);
}