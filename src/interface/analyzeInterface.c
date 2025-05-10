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

void analyzeGrade() {
    int count = 0;
    char majorId[MAX_ID_LENGTH];
    printf("请输入专业ID: ");
    scanf("%s", majorId);
    
    student **students = getStudentByMajor(majorId, &count);
    if (count == 0) {
        printf("未找到该专业的学生记录\n");
        return;
    }
    
    int subNum = students[0]->subjectNum;
    
    // 打印表头
    printAnalysisHeader(getMajorByIdx(majorId), -1);
    
    // 逐科目分析
    for (int i = 0; i < subNum; i++) {
        // 收集该科目的所有学生成绩
        double *scores = malloc(count * sizeof(double));
        for (int j = 0; j < count; j++) {
            scores[j] = students[j]->scores[i].score;
        }
        
        // 分析成绩
        ScoreAnalysis analysis;
        analyzeScores(scores, count, &analysis);
        
        // 打印分析结果
        printScoreAnalysis(getSubjectByIdx(students[0]->scores[i].id), &analysis);
        
        free(scores);
    }
    printf("\n");
    free(students);
}

void analyzeClass() {
    int count = 0;
    char majorId[MAX_ID_LENGTH];
    int classId;
    
    printf("请输入专业ID: ");
    scanf("%s", majorId);
    
    printf("请输入班级: ");
    scanf("%d", &classId);
    
    student **students = getStudentByMajor(majorId, &count);
    if (count == 0) {
        printf("未找到该专业的学生记录\n");
        return;
    }
    
    // 过滤该班级的学生
    int classCount = 0;
    for (int i = 0; i < count; i++) {
        if (students[i]->classId == classId) {
            classCount++;
        }
    }
    
    if (classCount == 0) {
        printf("未找到该班级的学生记录\n");
        free(students);
        return;
    }
    
    int subNum = students[0]->subjectNum;
    
    // 打印表头
    printAnalysisHeader(getMajorByIdx(majorId), classId);
    
    // 逐科目分析
    for (int i = 0; i < subNum; i++) {
        // 收集该班级该科目的所有学生成绩
        double *scores = malloc(classCount * sizeof(double));
        int scoreIndex = 0;
        
        for (int j = 0; j < count; j++) {
            if (students[j]->classId == classId) {
                scores[scoreIndex++] = students[j]->scores[i].score;
            }
        }
        
        // 分析成绩
        ScoreAnalysis analysis;
        analyzeScores(scores, classCount, &analysis);
        
        // 打印分析结果
        printScoreAnalysis(getSubjectByIdx(students[0]->scores[i].id), &analysis);
        
        free(scores);
    }
    printf("\n");

    free(students);
}


void printAnalysisHeader(const char *majorName, int classId) {
    printf("+-------------------------------------------------------------------------------+\n");
    if (classId == -1) {
        printf("| 专业名称：%-20s                                                    |\n", majorName);
    } else {
        printf("| 专业名称：%-20s  班级：%-4d                                        |\n", majorName, classId);
    }
    printf("+-------------------------------------------------------------------------------+\n");
    printf("| %-44s                                        |\n", "科目成绩分析");
    printf("+------------+--------+--------+--------+--------+-------+-------+-------+------+\n");
    printf("|   科目名   | 平均分 | 最高分 | 最低分 | 不及格 | 60~69 | 70~79 | 80~89 | 90+  |\n");
    printf("+------------+--------+--------+--------+--------+-------+-------+-------+------+\n");
}

void analyzeScores(double *scores, int count, ScoreAnalysis *result) {
    result->total = 0;
    result->max = 0;
    result->min = 100;
    result->failCount = 0;
    memset(result->range, 0, sizeof(result->range));
    
    for (int i = 0; i < count; i++) {
        double score = scores[i];
        result->total += score;
        result->max = max(result->max, score);
        result->min = min(result->min, score);
        
        if (score < 60) {
            result->failCount++;
        } else if (score < 70) {
            result->range[0]++;
        } else if (score < 80) {
            result->range[1]++;
        } else if (score < 90) {
            result->range[2]++;
        } else {
            result->range[3]++;
        }
    }
    result->avg = result->total / count;
}

void printScoreAnalysis(const char *subjectName, ScoreAnalysis *analysis) {
    printf("| ");
    print_centered(subjectName, 10);
    printf(" | %6.2f | %6.2f | %6.2f | \e[31m%6d\e[0m | %5d | %5d | %5d | %4d |\n",
        analysis->avg, analysis->max, analysis->min, analysis->failCount,
        analysis->range[0], analysis->range[1], analysis->range[2], analysis->range[3]);
    printf("+------------+--------+--------+--------+--------+-------+-------+-------+------+\n");
}
