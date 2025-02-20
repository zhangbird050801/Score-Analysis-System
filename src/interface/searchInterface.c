#include "interface/interface.h"

// TODO:
static HANDLE handler[] = {searchById};

void searchInterface() {
    makeInterface(SEARCH, handler);
}

// TODO: 根据学号查找学生
void searchById(){
    printf("请输入学号：");
    char id[MAX_ID_LENGTH];
    scanf("%s", id);
    student *stu = searchByStudentId(id);
    
    if(stu == NULL) {
        printf("未找到学号为 %s 的学生\n", id);
        return;
    }

    // TODO: 打印学生信息
    printStudent(stu);
}

// TODO: 根据姓名查找学生