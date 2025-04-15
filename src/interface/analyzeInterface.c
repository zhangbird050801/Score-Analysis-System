#include "interface/interface.h"

static HANDLE handler[] = {analyzeGrade, analyzeClass};

void analyzeInterface() {
    makeInterface(ANALYZE, handler);
}

// TODO: 专业年级成绩分析
void analyzeGrade() {
    int count = 0;  // 学生总数
    char majorId[MAX_ID_LENGTH];
    printf("请输入专业ID: ");
    scanf("%s", majorId);
    student **students = getStudentByMajor(majorId, &count);

    int subNum = students[0]->subjectNum;
    
    for(int i = 0; i < subNum; i ++) {
        int total = 0;
        int max = 0;
        int min = 100;
        int failCount = 0;
        int range[5] = {0}; // 60~69, 70~79, 80~89, 90~
        
        for(int j = 0; j < count; j ++) {
            int score = students[j]->scores[i].score;
            total += score;
            if(score > max) {
                max = score;
            }
            if(score < min) {
                min = score;
            }
            if(score < 60) {
                failCount ++;
            } else if(score < 70) {
                range[0] ++;
            } else if(score < 80) {
                range[1] ++;
            } else if(score < 90) {
                range[2] ++;
            } else {
                range[3] ++;
            }
        }
        
        printf("科目%d(%s): 平均分: %.2f, 最高分: %d, 最低分: %d, 不及格人数: %d, ", i + 1, getSubjectByIdx(students[0]->scores[i].id), (float)total / count, max, min, failCount);
        printf("60~69分人数: %d, 70~79分人数: %d, 80~89分人数: %d, 90分以上人数: %d\n", range[0], range[1], range[2], range[3]); 
    }

    printf("\n");
}

// TODO: 班级成绩分析
void analyzeClass() {
    
}