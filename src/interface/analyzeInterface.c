#include "interface/interface.h"

static HANDLE handler[] = {analyzeGrade, analyzeClass};

void analyzeInterface() {
    makeInterface(ANALYZE, handler);
}

/**
 * @brief 返回较大值
 */
double max(double a, double b) {
    return a > b ? a : b;
}

/**
 * @brief 返回较小值
 */
double min(double a, double b) {
    return a < b ? a : b;
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
        double s_max = 0;
        double s_min = 100;
        int failCount = 0;
        int range[5] = {0}; // 60~69, 70~79, 80~89, 90~
        
        for(int j = 0; j < count; j ++) {
            int score = students[j]->scores[i].score;
            total += score;
            s_max = max(s_max, score);
            s_min = min(s_min, score);
            
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
        
        printf("科目%d(%s): 平均分: %.2f, 最高分: %.2lf, 最低分: %.2lf, 不及格人数: %d, ", i + 1, getSubjectByIdx(students[0]->scores[i].id), (float)total / count, s_max, s_min, failCount);
        printf("60~69分人数: %d, 70~79分人数: %d, 80~89分人数: %d, 90分以上人数: %d\n", range[0], range[1], range[2], range[3]); 
    }

    printf("\n");
}

// TODO: 班级成绩分析
void analyzeClass() {
    
        int count = 0;  // 学生总数
        char majorId[MAX_ID_LENGTH];
        int classId;
        int classcount = 0;
    
        // 输入专业ID和班级
        printf("请输入专业ID: ");
        scanf("%s", majorId);
        
        printf("请输入班级: ");
        scanf("%d", &classId);

        printf("专业: %s   班级: %d\n", getMajorByIdx(majorId), classId);
    
        // 获取指定专业和班级的学生数据
        student **students = getStudentByMajor(majorId, &count);
        for(int b = 0; b < count; b++){

            student *stu = students[b];
            if(stu->classId == classId){
                classcount++;
            }
        }
        int subNum = students[0]->subjectNum;
    
        // 按科目统计成绩
        for (int i = 0; i < subNum; i++) {
            int total = 0;
            double s_max = 0;
            double s_min = 100;
            int failCount = 0;
            int range[5] = {0}; // 60~69, 70~79, 80~89, 90~
    
            for (int j = 0; j < count; j++) {
                student *stu = students[j];

                if(stu->classId == classId){
                    int score = students[j]->scores[i].score;
                    total += score;
                    s_max = max(s_max, score);
                    s_min = min(s_min, score);
    
                    if (score < 60) {
                    failCount++;
                    } else if (score < 70) {
                    range[0]++;
                    } else if (score < 80) {
                    range[1]++;
                    } else if (score < 90) {
                    range[2]++;
                    } else {
                    range[3]++;
                    }
            }
        }
    
            // 输出统计结果
            printf("科目%d(%s): 平均分: %.2f  最高分: %.2lf  最低分: %.2lf  不及格人数: %d ",
                i + 1, getSubjectByIdx(students[0]->scores[i].id),
                (float)total / classcount, s_max, s_min, failCount);
            printf("60~69分人数: %d  70~79分人数: %d  80~89分人数: %d  90分以上人数: %d\n",
                range[0], range[1], range[2], range[3]);
            
        }
        printf("\n");
    }



