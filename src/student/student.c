#include "interface/interface.h"

static const char* FILEPATH = "src/Data/Student.txt";
static student *studentById[MAX_STUDENT_NUM];
static student *studentByName[MAX_STUDENT_NUM];
static int totalStudent = 0;

/**
 * @brief 哈希函数
 * @param str 字符串
 */
unsigned int hash(char *str) {
    unsigned int hash = 0;
    while(*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % MAX_STUDENT_NUM;
}

/**
 * @brief 从文件中加载学生信息
 */
void loadStudent() {
    FILE *file = fopen(FILEPATH, "r");

    char line[MAX_LINE_LENGTH];
    while(fgets(line, sizeof(line), file)) {
        // 跳过空行 否则会出现段错误
        if (line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        student *stu = (student *)malloc(sizeof(student));

        sscanf(line, "%s %s %s %d %d %d", stu->id, stu->name, stu->major, \
            &stu->grade, &stu->classId, &stu->subjectNum
        );
        
        char *ptr = line;
        // 跳过前面的信息
        for(int i = 0; i < 6; i ++) 
            ptr = strchr(ptr, ' ') + 1;

        for(int i = 0; i < stu->subjectNum; i ++) {
            char subjectId[MAX_ID_LENGTH];
            double score;
            sscanf(ptr, "%s %lf", subjectId, &score);
            strcpy(stu->scores[i].id, subjectId);
            stu->scores[i].score = score;
            ptr = strchr(ptr, ' ') + 1;
            ptr = strchr(ptr, ' ') + 1;
        }

        addStudent(stu);

        totalStudent ++;
    }

    fclose(file);
}

/**
 * @brief 输出学生信息到文件
 */
void outStudent() {
    FILE *ptr = fopen(FILEPATH, "w");

    for(int i = 0; i < MAX_STUDENT_NUM; i ++) {
        student *stu = studentById[i];
        while (stu != NULL) {
            fprintf(ptr, "%s %s %s %d %d %d ", stu->id, stu->name,
                    stu->major, stu->grade, stu->classId, stu->subjectNum);

            for (int j = 0; j < stu->subjectNum; j++) {
                fprintf(ptr, "%s %.2lf ", stu->scores[j].id, stu->scores[j].score);
            }
            fprintf(ptr, "\n");

            stu = stu->next;
        }
    }

    fclose(ptr);
}

/**
 * @brief 添加学生到哈希表中
 * @param stu 学生
 */
void addStudent(student *stu) {
    unsigned int idxById = hash(stu->id);
    unsigned int idxByName = hash(stu->name);

    student *newNodeById = malloc(sizeof(student));
    *newNodeById = *stu; 
    newNodeById->next = studentById[idxById];
    studentById[idxById] = newNodeById;

    student *newNodeByName = malloc(sizeof(student));
    *newNodeByName = *stu; 
    newNodeByName->next = studentByName[idxByName];
    studentByName[idxByName] = newNodeByName;
}

/**
 * @brief 通过学号查找学生
 * @param id 学号
 */
student *searchStudentById(char *id) {
    unsigned int idx = hash(id);
    student *stu = studentById[idx];
    while(stu != NULL) {
        if(strcmp(stu->id, id) == 0) {
            return stu;
        }
        stu = stu->next;
    }
    return NULL;
}

/**
 * @brief 打印学生的各门课程成绩
 * @param stu 学生
 */
void printAllGrades(student *stu) {
    printf("\n+======================== 学生成绩 ======================+\n");
    printf("| ");print_centered("课程ID", 10);    
    printf(" | ");print_centered("课程名称", 30);  
    printf(" | ");print_centered("成绩", 8); printf(" |\n");
    printf("+------------+--------------------------------+----------+\n");
    for (int i = 0; i < stu->subjectNum; i++) {
        printf("| %-10s | ", stu->scores[i].id);  // 课程ID左对齐
        print_centered(getSubjectByIdx(stu->scores[i].id), 30);
        printf(" | %-8.2lf |\n", stu->scores[i].score); // 成绩右对齐
    }
    printf("+========================================================+\n\n");
}

/**
 * @brief 通过姓名查找学生
 * @param name 姓名
 */
void searchStudentByName(char *name){
    unsigned int idx = hash(name);
    student *stu = studentByName[idx];
    int key = 0; 

    while (stu) {
        if (strcmp(stu->name, name) == 0) {
            printf("姓名: %s   学号:%s\n", stu->name, stu->id);
            printStudent(stu);
            printf("\n");
            key = 1;
        }
        stu = stu->next;
    }

    if(key == 0){
        printf("未找到名字为 %s 的学生\n", name);
    }
}

/**
 * @brief 通过姓名和学号查找学生
 * @param name 姓名
 * @param id 学号
 */
student *searchStudentByNameAndId(char *name, char *id) {
    unsigned int idx = hash(name);
    student *stu = studentByName[idx];

    while (stu) {
        if (strcmp(stu->name, name) == 0 && strcmp(stu->id, id) == 0) {
            return stu;
        }
        stu = stu->next;
    }

    return NULL;
}

/**
 * @brief 计算单科绩点（60分以下绩点为0）
 */
double countGPA(double score){
    if(score>=60){
        double gpa = 5 - (100 - score)/10;
        return gpa;
    }else{
        return 0.0;
    }
}

/**
 * @brief 计算平均绩点
 * @param stu 学生
 */
double countAverageGPA(student *stu){
    double sum = 0, credits = 0;
    int i = 0;
    for(i = 0;i < stu->subjectNum;i++){
        sum = sum + countGPA(stu->scores[i].score) * getCreditByIdx(stu->scores[i].id);
        credits += getCreditByIdx(stu->scores[i].id);
    }
    return sum / credits;

}

/**
 * @brief 计算加权平均分
 * @param stu 学生
 */
double getWAM(student *stu){
    double sum = 0,credits = 0;
    int i = 0;
    for(i = 0;i < stu->subjectNum;i ++){
        sum = sum + stu->scores[i].score * getCreditByIdx(stu->scores[i].id);
        credits += getCreditByIdx(stu->scores[i].id);
    }
    return sum / credits;
}

/**
 * @brief 打印学生信息
 * @param stu 学生
 */
void printStudent(student *stu) {
    printInfo();

    int failSubjects = 0;//不及格科目
    double totalCredit = 0;//总学分
    Queue q;
    initQueue(&q);

    for(int i = 0; i < stu->subjectNum; i ++) {
        // printf("%s %.2lf ", getSubjectByIdx(stu->scores[i].id), stu->scores[i].score);
        if(stu->scores[i].score < 60) {
            failSubjects ++;

            failSubject fail;
            strcpy(fail.name, getSubjectByIdx(stu->scores[i].id));
            fail.score = stu->scores[i].score;
            enqueue(&q, fail);
        }else{
            totalCredit += getCreditByIdx(stu->scores[i].id);
        }
    }

    printf("| %s | %s | %-14s |   %d   | %4d | %-12.2lf | %-8.2lf | %8d | %-12.2lf |       %s%s%s%d%s        | \n", stu->id, stu->name, getMajorByIdx(stu->major), \
        stu->grade, stu->classId, countAverageGPA(stu), getWAM(stu), stu->subjectNum, totalCredit, FRONT_RED, BOLD, UNDERLINE, failSubjects, RESET
    );

    printf("+============+======+============+========+======+==============+==========+==========+==============+================+\n");

    for(int i = 0; i < failSubjects; i++) {
        printf("不及格科目: %s %.2lf\n", first(&q).name, first(&q).score);
        dequeue(&q);
    }

    printAllGrades(stu);
}

/**
 * @brief 比较函数
 * @param a 
 * @param b
 */
int compare(const void *a, const void *b) {
    student *stuA = *(student **)a;
    student *stuB = *(student **)b;

    if(stuA->grade != stuB->grade) {
        return (stuA->grade > stuB->grade) ? 1 : -1;
    }

    double GPA_A = countAverageGPA(stuA);
    double GPA_B = countAverageGPA(stuB);

    if (GPA_A > GPA_B) {
        return -1; // GPA_A 在前
    } 
    if (GPA_A < GPA_B) {
        return 1;  // GPA_B 在前
    } 

    return strcmp(stuA->id, stuB->id);

}

/**
 * @brief 获取某专业所有学生
 */
student **getStudentByMajor(const char *majorId, int *count) {
    student **students = malloc(MAX_STUDENT_NUM * sizeof(student *)); // 动态分配数组
    int tmpCount = 0;

    for (int i = 0; i < MAX_STUDENT_NUM; i++) {
        student *stu = studentById[i];
        while (stu) {
            if (strcmp(stu->major, majorId) == 0) {
                students[tmpCount++] = stu;
            }
            stu = stu->next;
        }
    }

    *count = tmpCount; // 返回学生数量
    return students;   // 返回学生数组
}

/**
 * @brief 根据班级获取学生
 */
student **getStudentByClass(const char *majorId, int grade, int class, int *count) {
    student **students = malloc(MAX_STUDENT_NUM * sizeof(student *)); // 动态分配数组
    int tmpCount = 0;

    for (int i = 0; i < MAX_STUDENT_NUM; i++) {
        student *stu = studentById[i];
        while (stu) {
            if (strcmp(stu->major, majorId) == 0 && grade == stu->grade && class == stu->classId) {
                students[tmpCount++] = stu;
            }
            stu = stu->next;
        }
    }

    *count = tmpCount; // 返回学生数量
    return students;   // 返回学生数组
}

void printStudentByClass(const char *majorId, int grade, int class){
    int count = 0;

    student **students = getStudentByClass(majorId, grade, class, &count);

    quickSort(students, 0, count - 1, sizeof(student *), compare);

    int rank = 0;
    int sameNum = 1;

    printf("\t+=====================================================+\n");
    printf("\t| 年级: %d   班级：%d                                |\n", grade, class);
    printf("\t+------+------------+------+------------+------+------+\n");
    printf("\t| 排名 |    学号    | 姓名 |    专业    | 年级 | GPA  |\n");
    printf("\t+------+------------+------+------------+------+------+\n");

    char PATH[256];
    snprintf(PATH,sizeof(PATH),"src/Data/Sort/%s-%d-%d.txt",majorId,grade,class);
    FILE *ptr = fopen(PATH,"w");
    fprintf(ptr,"排名\t学号\t\t姓名\t\t专业\t\t年级\tGPA\n");

    for(int i = 0; i < count; i++) {
        student *stu = students[i];

        // 处理并列排名： GPA相同，排名不变
        if(i > 0  && (countAverageGPA(students[i - 1]) - countAverageGPA(stu)) < 1e-7) {
            sameNum = sameNum + 1;
        } else {
            rank = rank + sameNum;
            sameNum = 1;
        }
    
        printf("\t| %-4d | %-8s | %-6s | %-14s | %-4d | %.2f |\n", 
        rank, stu->id, stu->name, getMajorByIdx(stu->major), 
        stu->grade, countAverageGPA(stu));

        fprintf(ptr, "%-4d\t%-8s\t%-8s\t%-8s\t%-4d\t%.2f\n", 
        rank, stu->id, stu->name, getMajorByIdx(stu->major), 
        stu->grade, countAverageGPA(stu));
    }

    printf("\t+=====================================================+\n\n");
    fclose(ptr);
    free(students);
}

/**
 * @brief 打印专业的学生信息
 * @param majorId 专业ID
 */
void printStudentByMajor(const char *majorId) {
    int count = 0;

    char PATH[256]; 
    FILE *ptr = NULL; // 初始化文件指针

    student **students = getStudentByMajor(majorId, &count);

    // 使用 quickSort 对学生数组排序
    quickSort(students, 0, count - 1, sizeof(student *), compare);

    int rank = 1;
    int currentGrade = -1;
    int tmpSame = 1;

    for (int i = 0; i < count; i++) {
        student *stu = students[i];
        
        // 如果年级发生变化，关闭之前的文件并打开新的文件
        if (currentGrade != stu->grade) {
            if (ptr != NULL) {
                fclose(ptr); // 关闭之前的文件
            }

            currentGrade = stu->grade; // 更新当前年级

            snprintf(PATH, sizeof(PATH), "src/Data/Sort/%s-%d.txt", majorId, currentGrade); 
            ptr = fopen(PATH, "w"); // 打开新的文件

            if (ptr == NULL) {
                perror("文件打开失败");
                free(students);
                return;
            }

            fprintf(ptr, "排名\t学号\t\t姓名\t\t专业\t\t年级\tGPA\n");

            printf("\t+=====================================================+\n");
            printf("\t| 年级: %d                                            |\n", stu->grade);                     
            printf("\t+------+------------+------+------------+------+------+\n");
            printf("\t| 排名 |    学号    | 姓名 |    专业    | 年级 | GPA  |\n");
            printf("\t+------+------------+------+------------+------+------+\n");

            rank = 0; // 重置排名
            tmpSame = 1; // 重置并列计数
        }
        
        // 处理并列排名： GPA相同，排名不变
        if (i > 0 && students[i - 1]->grade == stu->grade && 
            (countAverageGPA(students[i - 1]) - countAverageGPA(stu)) < 1e-7) {
            tmpSame += 1;
        } else {
            rank += tmpSame;
            tmpSame = 1;
        }
        
        printf("\t| %-4d | %-8s | %-6s | %-14s | %-4d | %.2f |\n", 
            rank, stu->id, stu->name, getMajorByIdx(stu->major), 
            stu->grade, countAverageGPA(stu));
        fprintf(ptr, "%-4d\t%-8s\t%-8s\t%-8s\t%-4d\t%.2f\n", 
            rank, stu->id, stu->name, getMajorByIdx(stu->major), 
            stu->grade, countAverageGPA(stu));
    }

    printf("\t+=====================================================+\n\n");

    if (ptr != NULL) {
        fclose(ptr); // 关闭最后一个文件
    }
    free(students);
}

/**
 * @brief 快速排序算法
 */
void quickSort(void *base, int left, int right, size_t size, int (*cmp)(const void *, const void *)) {
    if (left >= right) {
        return;
    }

    // 选择基准元素
    char *pivot = (char *)base + left * size;
    int i = left, j = right;

    while (i < j) {
        // 从右向左找到第一个小于基准的元素
        while (i < j && cmp((char *)base + j * size, pivot) >= 0) {
            j--;
        }
        // 从左向右找到第一个大于基准的元素
        while (i < j && cmp((char *)base + i * size, pivot) <= 0) {
            i++;
        }
        // 交换 i 和 j 指向的元素
        if (i < j) {
            char temp[size];
            memcpy(temp, (char *)base + i * size, size);
            memcpy((char *)base + i * size, (char *)base + j * size, size);
            memcpy((char *)base + j * size, temp, size);
        }
    }

    // 将基准元素放到正确的位置
    char temp[size];
    memcpy(temp, pivot, size);
    memcpy(pivot, (char *)base + i * size, size);
    memcpy((char *)base + i * size, temp, size);

    // 递归排序左右两部分
    quickSort(base, left, i - 1, size, cmp);
    quickSort(base, i + 1, right, size, cmp);
}