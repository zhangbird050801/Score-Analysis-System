#include "interface/interface.h"

static HANDLE handler[] = {analyzeGrade, analyzeClass};

void analyzeInterface() {
    makeInterface(ANALYZE, handler);
}

// TODO: 专业年级成绩分析
void analyzeGrade() {

}

// TODO: 班级成绩分析
void analyzeClass() {
    
}

// TODO: 平均成绩、最高分、最低分、不及格人数、60~69分人数、70~79分人数、80~89分人数、90分以上人数
