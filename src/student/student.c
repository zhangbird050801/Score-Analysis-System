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

        // 测试用
        // printStudent(stu); 

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

    stu->next = studentById[idxById];
    stu->next = studentByName[idxByName];

    studentById[idxById] = stu;
    studentByName[idxByName] = stu;
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
        printf("未找到名字为%s的学生",name);
    }
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

    double sum, credits = 0;
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
    // TODO: 添加头部信息提示
    // 学号 姓名 专业 年级 班级 (不打印学科数目) 学科编号 学科分数 平均学分绩点 加权分数
    printf("%s %s %s %d %d \n", stu->id, stu->name, getMajorByIdx(stu->major), \
        stu->grade, stu->classId
    );
    for(int i = 0; i < stu->subjectNum; i ++) {
        printf("%s %.2lf ", getSubjectByIdx(stu->scores[i].id), stu->scores[i].score);
    }
    printf("\n");
    
    printf("GPA: %.2lf\n",countAverageGPA(stu));
    printf("WAM: %.2lf\n",getWAM(stu));

}
