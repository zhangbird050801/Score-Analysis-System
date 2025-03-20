#include "interface/interface.h"

static HANDLE handler[] = {sortByGrade, sortByClass};

void sortInterface() {
    makeInterface(SORT, handler);
}

// TODO: 按照专业年级排序
void sortByGrade() {

}

// TODO: 按照班级排序
void sortByClass() {

}