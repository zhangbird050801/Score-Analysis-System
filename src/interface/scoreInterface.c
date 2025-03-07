#include "interface/interface.h"

static HANDLE handler[] = {inputScore, modifyScore};

void scoreInterface() {
    makeInterface(SCORE, handler);
}

/**
 * @brief 录入学生及成绩
 */
void inputScore() {
    char id[MAX_ID_LENGTH], name[MAX_NAME_LENGTH], majorId[MAX_ID_LENGTH], subjectId[MAX_ID_LENGTH];
    int grade, classId, subjectNum;

    printf("请输入学号：");
    scanf("%s", id);

    if(searchStudentById(id) != NULL) {
        addStudentError();
        return;
    }

    printf("请输入学生姓名: ");
    scanf("%s", name);
    printf("请输入学生专业序号: ");
    scanf("%s", majorId);

    // TODO: 如果该专业序号不存在，则添加

    printf("请输入学生年级: ");
    scanf("%d", &grade);
    printf("请输入学生班级序号: ");
    scanf("%d", &classId);
    printf("请输入学生课程数: ");
    scanf("%d", &subjectNum);

    student *stu = (student *)malloc(sizeof(student));
    strcpy(stu->id, id);
    strcpy(stu->name, name);
    strcpy(stu->major, majorId);
    stu->grade = grade;
    stu->classId = classId;
    stu->subjectNum = subjectNum;
    for(int i = 0; i < subjectNum; i ++) {
        printf("请输入第 %s%s%d%s 门课程的课程号: ", BOLD, FRONT_YELLOW, i + 1, RESET);
        scanf("%s", subjectId);

        // TODO: 如果该课程号不存在，则添加

        printf("请输入第 %s%s%d%s 门课程的成绩: ", BOLD, FRONT_YELLOW, i + 1, RESET);
        double score;
        scanf("%lf", &score);
        strcpy(stu->scores[i].id, subjectId);
        stu->scores[i].score = score;
    }

    addStudent(stu);
    addStudentSuccess();
}

// TODO: 修改成绩
void modifyScore() {
    
}