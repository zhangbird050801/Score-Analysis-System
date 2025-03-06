#include "interface/interface.h"

// TODO: handler 创建
static HANDLE handler[] = {inputScore, modifyScore};

void scoreInterface() {
    // TODO:
    // makeInterface(SCORE, handler);
}

void inputScore() {
    printf("请输入学号：");
    char id[MAX_ID_LENGTH];
    scanf("%s", id);
    printf("请输入学生姓名: ");
    char name[MAX_NAME_LENGTH];
    scanf("%s", name);
    printf("请输入学生专业序号: ");
    char majorId[MAX_ID_LENGTH];
    scanf("%d", majorId);
    printf("请输入学生班级序号: ");
    int classId;
    scanf("%d", &classId);
    printf("请输入学生课程数: ");
    int subjectNum;
    scanf("%d", &subjectNum);
    stu = (student *)malloc(sizeof(student));
    strcpy(stu->id, id);
    strcpy(stu->name, name);
    stu->majorId = majorId;
    stu->classId = classId;
    stu->subjectNum = subjectNum;
    for(int i = 0; i < subjectNum; i ++) {
        printf("请输入第 %d 门课程的课程号: ", i + 1);
        char subjectId[MAX_ID_LENGTH];
        scanf("%s", subjectId);
        printf("请输入第 %d 门课程的成绩: ", i + 1);
        double score;
        scanf("%lf", &score);
        strcpy(stu->scores[i].id, subjectId);
        stu->scores[i].score = score;
    }

}

// TODO: 修改成绩
void modifyScore() {
    
}