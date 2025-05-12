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
        printf("请输入第 %s%s%d%s 门课程的成绩: ", BOLD, FRONT_YELLOW, i + 1, RESET);
        double score;
        scanf("%lf", &score);
        strcpy(stu->scores[i].id, subjectId);
        stu->scores[i].score = score;
    }

    addStudent(stu);
    addStudentSuccess();
}

/**
 * @brief 修改学生成绩
 */
void modifyScore() {
    printf("请输入学号：");
    char id[MAX_ID_LENGTH];
    scanf("%s", id);
    student *stu = searchStudentById(id);
    
    if(stu == NULL) {
        errorFindingStudent();
        failureMessage();
        return;
    }
    
    printAllGrades(stu);
    
    bool tem = true;
    while(tem){
        printf("请输入要修改的课程序号: ");
        char subjectId[MAX_ID_LENGTH];
        scanf("%s", subjectId);
        int i = 0;
        for( i = 0; i < stu->subjectNum; i ++){
            if(strcmp(stu->scores[i].id,subjectId) == 0){
                printf("请输入新的成绩: ");
                double tmp;
                scanf("%lf", &tmp);
                stu->scores[i].score = tmp;
                printf ("学号%s的%s成绩修改成功!\n",id,getSubjectByIdx(subjectId));
                break;
            }
        }
        if(i == stu->subjectNum){
            printf("没有找到该课程!\n");
        }
        printf("是否继续修改: yes(输入y) or %sno(输入n)%s: ",FRONT_RED,RESET);
        char c;
        scanf(" %c", &c);
        if(c == 'n'){
            tem = false;
        }

        printf("\n");
    }
}







