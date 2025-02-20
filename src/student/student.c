#include "interface/interface.h"

static const char* FILEPATH = "src/Data/Student.txt";
static student *studentById[MAX_STUDENT_NUM];
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

        // printStudent(stu); 测试用

        totalStudent ++;
    }

    fclose(file);
}

/**
 * @brief 添加学生到哈希表中
 * @param stu 学生
 */
void addStudent(student *stu) {
    unsigned int idx = hash(stu->id);

    stu->next = studentById[idx];
    studentById[idx] = stu;
}

/**
 * @brief 通过学号查找学生
 * @param id 学号
 */
student *searchByStudentId(char *id) {
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

// TODO: 通过姓名查找学生，要处理同名的情况

// TODO: 计算学生平均学分绩点

// TODO: 计算学生加权分数


// TODO: 打印学生信息。并将专业编号转换为专业名称，将学科编号转换为学科名称。
//       并且要计算学生平均学分绩点，加权分数。
void printStudent(student *stu) {
    // TODO: 添加头部信息提示
    // 学号 姓名 专业 年级 班级 (不打印学科数目) 学科编号 学科分数 平均学分绩点 加权分数
    printf("%s %s %s %d %d\n", stu->id, stu->name, stu->major, \
        stu->grade, stu->classId
    );
    for(int i = 0; i < stu->subjectNum; i ++) {
        printf("%s %.2lf ", stu->scores[i].id, stu->scores[i].score);
    }
    printf("\n");
}
