#include "interface/interface.h"

static const char* FILEPATH = "src/Data/User.txt"; 
static User users[MAX_USER_NUMBER]; 
static int totalUser = 0; 

/**
 * @brief 获取用户
 * @param idx 用户编号
 */
User *getUser(int idx) {
    return users + idx; //users[idx]
}

/**
 * @brief 加载用户
 */
void loadUser() {
    FILE *ptr = fopen(FILEPATH, "r");
    
    while(fscanf(ptr, "%s%s%s", users[totalUser].id, \
        users[totalUser].name, users[totalUser].password) != EOF) {
            totalUser ++;
    }

    fclose(ptr);
}

/**
 * @brief 输出用户到文件
 */
void outUser() {
    FILE *ptr = fopen(FILEPATH, "w");

    for(int i = 0; i < totalUser; i ++) {
        fprintf(ptr, "%s %s %s\n", users[i].id, \
            users[i].name, users[i].password);
    }
    fclose(ptr);
}

/**
 * @brief 核验用户密码
 * @param name 用户名
 * @param pwd 密码
 * @return 1 表示核验成功 0 表示核验失败 -1 表示未查找到用户
 */
int check(char *name, char *pwd) {
    int idx = searchByUserName(name);
    if(idx == -1) return -1;
    return strcmp(users[idx].password, pwd) == 0;
}

/**
 * @brief 根据用户名查找用户
 * @param name 用户名
 * @return -1 表示未查找到用户 否则返回用户下标
 */
int searchByUserName(char *name) {
    for(int i = 0; i < totalUser; i ++) {
        if(strcmp(users[i].name, name) == 0) return i;
    }
    return -1;
}

// TODO: 二分查找
int searchByUserId(char *id) {
    
}

/**
 * @brief 添加新用户
 * @param name 用户名
 * @param password 密码
 */
void addNewUser(char* name,char* password){
    User user;
    generateId(user.id, 'U');
    strcpy(user.name,name);
    strcpy(user.password,password);
    users[totalUser ++] = user;
    addUserSuccess();
}