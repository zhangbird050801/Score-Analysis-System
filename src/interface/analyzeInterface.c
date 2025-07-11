#include "interface/interface.h"

static HANDLE handler[] = {analyzeGrade, analyzeClass, analyzeAllClasses};

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

/**
 * @brief 打印表头。classId 如果为 -1 不打印班级
 */
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

/**
 * @brief 分析成绩
 * @param scores 所有成绩
 * @param count 成绩数量
 * @param result 结果
 */
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

/**
 * @brief 打印成绩分析结果
 */
void printScoreAnalysis(const char *subjectName, ScoreAnalysis *analysis) {
    printf("| ");
    print_centered(subjectName, 10);
    printf(" | %6.2f | %6.2f | %6.2f | %s%6d%s | %5d | %5d | %5d | %4d |\n",
        analysis->avg, analysis->max, analysis->min, FRONT_RED, analysis->failCount, RESET,
        analysis->range[0], analysis->range[1], analysis->range[2], analysis->range[3]);
    printf("+------------+--------+--------+--------+--------+-------+-------+-------+------+\n");
}

/**
 * @brief 根据年级分析成绩
 */
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

/**
 * @brief 根据班级分析成绩
 */
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
            classCount++; // 统计该班级学生数量
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

/**
 * @brief 分析整个年级下所有班级的成绩
 */
void analyzeAllClasses() {
    int count = 0;
    int targetGrade;
    char majorId[MAX_ID_LENGTH];
    
    printf("请输入要分析的年级：");
    scanf("%d", &targetGrade);
    
    printf("请输入专业ID: ");
    scanf("%s", majorId);

    // 获取指定专业的所有学生
    student **allStudents = getStudentByMajor(majorId, &count);
    if (count == 0) {
        printf("未找到该专业的学生记录\n");
        return;
    }
    
    // 筛选出指定年级的学生
    student **students = malloc(count * sizeof(student*));
    int gradeStudentCount = 0;
    
    for (int i = 0; i < count; i++) {
        if (allStudents[i]->grade == targetGrade) {
            students[gradeStudentCount++] = allStudents[i];
        }
    }
    
    if (gradeStudentCount == 0) {
        printf("未找到 %d 年级该专业的学生记录\n", targetGrade);
        free(students);
        free(allStudents);
        return;
    }
    
    count = gradeStudentCount;  // 更新学生数量

    // 获取科目数量
    int subNum = students[0]->subjectNum;

    // 获取所有班级编号
    int *classIds = malloc(count * sizeof(int));
    int classCount = 0;

    for (int i = 0; i < count; i++) {
        int isExist = 0;
        for (int j = 0; j < classCount; j++) {
            if (classIds[j] == students[i]->classId) {
                isExist = 1;
                break;
            }
        }
        if (!isExist) {
            classIds[classCount++] = students[i]->classId;
        }
    }

    // 按班级逐科目分析
    for (int c = 0; c < classCount; c++) {
        int currentClass = classIds[c];

        // 计算当前班级的学生数
        int currentStudentCount = 0;
        for (int i = 0; i < count; i++) {
            if (students[i]->classId == currentClass) {
                currentStudentCount++;
            }
        }

        // 打印表头
        printAnalysisHeader(getMajorByIdx(majorId), currentClass);

        // 逐科目分析
        for (int i = 0; i < subNum; i++) {
            double *scores = malloc(currentStudentCount * sizeof(double));
            int scoreIndex = 0;

            for (int j = 0; j < count; j++) {
                if (students[j]->classId == currentClass) {
                    scores[scoreIndex++] = students[j]->scores[i].score;
                }
            }

            ScoreAnalysis analysis;
            analyzeScores(scores, currentStudentCount, &analysis);

            printScoreAnalysis(getSubjectByIdx(students[0]->scores[i].id), &analysis);

            free(scores);
        }

        printf("\n");
    }

    free(classIds);
    free(students);
    free(allStudents);
}