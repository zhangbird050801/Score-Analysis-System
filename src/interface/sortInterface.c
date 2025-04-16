#include "interface/interface.h"

static HANDLE handler[] = {sortByGrade, sortByClass};

void sortInterface() {
    makeInterface(SORT, handler);
}

/**
 * @brief 按照专业ID排序
 */
void sortByGrade() {
    printf("请输入专业ID: ");
    char majorId[MAX_ID_LENGTH];
    scanf("%s", majorId);
    printStudentByMajor(majorId);
}

/**
 * @brief 按照年级和班级排序
 */
void sortByClass() {

    printf("请输入专业ID: ");
    char majorId[MAX_ID_LENGTH];
    scanf("%s", majorId);

    printf("请输入年级: ");
    int grade;
    scanf("%d", &grade);

    printf("请输入班级: ");
    int classID;
    scanf("%d", &classID);

    printStudentByClass(majorId,grade,classID);
}
