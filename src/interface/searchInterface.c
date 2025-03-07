#include "interface/interface.h"

static HANDLE handler[] = {searchById, searchByName};

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
    student *stu = searchByStudentId(id);
    
    if(stu == NULL) {
        errorFindingStudent();
        failureMessage();
        return;
    }

    printStudent(stu);
}

// TODO: 根据姓名查找学生
void searchByName() {

}