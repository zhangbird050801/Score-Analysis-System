#include "interface/interface.h"

static HANDLE handler[] = {sortByGrade, sortByClass};

void sortInterface() {
    makeInterface(SORT, handler);
}

// TODO: 按照专业年级排序
void sortByGrade() {
    printf("请输入专业ID: ");
    char majorId[MAX_ID_LENGTH];
    scanf("%s", majorId);
    printStudentByMajor(majorId);
}

// TODO: 按照班级排序
void sortByClass() {

}