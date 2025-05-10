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

// TODO: 分年级
void analyzeGrade() {
    int count = 0;  // 学生总数
    char majorId[MAX_ID_LENGTH];
    printf("请输入专业ID: ");
    scanf("%s", majorId);
    student **students = getStudentByMajor(majorId, &count);

    int subNum = students[0]->subjectNum;
    // 输出表头
    
    printf("+-----------------------------\n");
    printf("| 专业名称：%-20s |\n",getMajorByIdx(majorId));
    printf("+----------------------------+\n");
    printf("| %-32s |\n", "科目成绩分析");
    printf("+----------------------------+\n");
    printf("| 科目名   | 平均分 | 最高分 | 最低分 | 不及格 | 60~69 | 70~79 | 80~89 | 90+  |\n");
    printf("+----------+--------+--------+--------+--------+-------+-------+-------+------+\n");
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
         float avg = (float)total / count;
         // 使用颜色区分不及格人数
         printf("| ");
        print_centered(getSubjectByIdx(students[0]->scores[i].id), 8);  // 科目名宽度为6（原%-6s）
        printf(" | %6.2f | %6.2f | %6.2f | \e[31m%6d\e[0m | %5d | %5d | %5d | %4d |\n",
           avg, s_max, s_min, failCount, range[0], range[1], range[2], range[3]);
}

    printf("+----------+--------+--------+--------+--------+-------+-------+-------+------+\n");
    printf("\n");
}

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
        // 输出表头
    printf("+------------+--------+--------+--------+--------+-------+-------+-------+------+\n");
    printf("|   科目名   | 平均分 | 最高分 | 最低分 | 不及格 | 60~69 | 70~79 | 80~89 | 90+  |\n");
    printf("+------------+--------+--------+--------+--------+-------+-------+-------+------+\n");
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
        
        printf("| ");
        print_centered(getSubjectByIdx(students[0]->scores[i].id), 10);  // 科目名称居中
        printf(" | %6.2f | %6.2f | %6.2f | \e[31m%6d\e[0m | %5d | %5d | %5d | %4d |\n",
            (float)total / classcount,
            s_max,
            s_min,
            failCount,
            range[0], range[1], range[2], range[3]);
        }
        printf("+------------+--------+--------+--------+--------+-------+-------+-------+------+\n");
        printf("\n");
    }



