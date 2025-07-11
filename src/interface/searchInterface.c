#include "interface/interface.h"

static HANDLE handler[] = {searchById, searchByName, fuzzySearchByName};

void searchInterface() {
    makeInterface(SEARCH, handler);
}

/**
 * @brief 根据学号查找指定学生
 */
void searchById(){
    printf("请输入学号：");
    char id[MAX_ID_LENGTH];
    scanf("%s", id);
    student *stu = searchStudentById(id);
    
    if(stu == NULL) {
        errorFindingStudent();
        failureMessage();
        return;
    }

    printStudent(stu);
}

/**
 * @brief 根据姓名查找指定学生
 */
void searchByName() {
    printf("请输入要查找的学生姓名：");
    char name[MAX_NAME_LENGTH];
    scanf("%s",name);
    searchStudentByName(name);
}

/**
 * @brief 模糊搜索学生姓名
 */
void fuzzySearchByName() {
    printf("\n%s%s", BOLD, FRONT_BLUE);
    printf("+=====================================================================+\n");
    printf("│                             %s模糊搜索%s                                │\n", FRONT_YELLOW, FRONT_BLUE);
    printf("+=====================================================================+\n");
    printf("│  %s✓ 精确匹配:%s 输入完整或部分姓名                                     │\n", FRONT_GREEN, FRONT_BLUE);
    printf("│  %s✓ 相似匹配:%s 自动纠正输入错误                                       │\n", FRONT_GREEN, FRONT_BLUE);
    printf("│  %s✓ 智能算法:%s 基于编辑距离的模糊匹配                                 │\n", FRONT_GREEN, FRONT_BLUE);
    printf("+=====================================================================+\n");
    
    printf("\n%s请输入搜索关键字: %s", FRONT_GREEN, RESET);
    
    char namePattern[MAX_NAME_LENGTH];
    scanf("%s", namePattern);
    
    fuzzySearchStudentByName(namePattern);
}